#include "pch.h"
#include "code_generate.h"

code_generate::code_generate()
{
	project_path = "./system_design/c_project/";
	//xml_system_design = "D:/Project/tool_sm/tool_sm/system_design/system_design.xml";	
	xml_system_design = "./system_design/system_design.xml";
	doc.LoadFile(xml_system_design);
}
code_generate::~code_generate()
{
}
void code_generate::GenerateCode()
{
	tinyxml2::XMLElement* root = doc.RootElement();

	tinyxml2::XMLElement* module_node = root->FirstChildElement("Module");
	while (module_node != 0)
	{
		AddModule(module_node);
		module_node = module_node->NextSiblingElement("Module");
	}
}
void code_generate::AddModule(tinyxml2::XMLElement* module)
{
	CString module_name = module->Attribute("name");
	CString module_path = project_path + module_name;
	CString file_h_path = module_path + "/" + module_name + "_data.h";
	CString file_c_path = module_path + "/" + module_name + "_data.c";
	CString str_line;
	FILE *pfile_h = NULL;
	FILE* pfile_c = NULL;
	
	RemoveDirectory(module_path);
	bool result = CreateDirectoryA(module_path, NULL);

	fopen_s(&pfile_h, file_h_path, "w+");
	ATLASSERT(pfile_h != NULL);
	fopen_s(&pfile_c, file_c_path, "w+");
	ATLASSERT(pfile_c != NULL);

	//file start
	str_line.Format(_T("#ifndef _%s_DATA_H_\n"), module_name);
	fwrite(str_line, strlen(str_line), 1, pfile_h);

	//include	
	str_line.Format(_T("#include \"%s_type.h\n\n"), module_name);
	fwrite(str_line, strlen(str_line), 1, pfile_h);
	str_line.Format(_T("#include \"rte_sm_type.h\"\n"));
	fwrite(str_line, strlen(str_line), 1, pfile_c);
	str_line.Format(_T("#include \"rte_health_monitor_type.h\"\n"));
	fwrite(str_line, strlen(str_line), 1, pfile_c);
	str_line.Format(_T("#include \"%s.h\"\n"), module_name);
	fwrite(str_line, strlen(str_line), 1, pfile_c);
	str_line.Format(_T("#include \"%s_config.h\"\n"), module_name);
	fwrite(str_line, strlen(str_line), 1, pfile_c);
	str_line.Format(_T("#include \"%s_data.h\"\n"), module_name);
	fwrite(str_line, strlen(str_line), 1, pfile_c);

	//module
	str_line.Format(_T("extern Ts_StateMachine g_%s_sm;\n"), module_name);
	fwrite(str_line, strlen(str_line), 1, pfile_h);

	str_line.Format(_T("Ts_StateMachine g_%s_sm = {\n"), module_name);
	fwrite(str_line, strlen(str_line), 1, pfile_c);
	str_line.Format(_T("    %s,\n"), module->Attribute("id"));
	fwrite(str_line, strlen(str_line), 1, pfile_c);
	str_line.Format(_T("    %s,\n"), module->FirstChildElement("StateCount")->GetText());
	fwrite(str_line, strlen(str_line), 1, pfile_c);
	str_line.Format(_T("    %s,\n"), module->FirstChildElement("DefaultState")->GetText());
	fwrite(str_line, strlen(str_line), 1, pfile_c);
	str_line.Format(_T("    g_%s_buff_state,\n"), module_name);
	fwrite(str_line, strlen(str_line), 1, pfile_c);
	str_line.Format(_T("    & g_%s_state_jump_map,\n"), module_name);
	fwrite(str_line, strlen(str_line), 1, pfile_c);
	str_line.Format(_T("    %s,\n"), "Te_StateIdentify_Idle");
	fwrite(str_line, strlen(str_line), 1, pfile_c);
	str_line.Format(_T("    %s,\n"), "Te_StateIdentify_Idle");
	fwrite(str_line, strlen(str_line), 1, pfile_c);
	str_line.Format(_T("    %s\n"), "Te_StateIdentify_Idle");
	fwrite(str_line, strlen(str_line), 1, pfile_c);
	str_line.Format(_T("};\n"));
	fwrite(str_line, strlen(str_line), 1, pfile_c);
	
	AddStateManager(module_name, module, pfile_h, pfile_c);
	AddStateJumpMap(module_name, pfile_h, pfile_c);
	// file end
	str_line = "\n#endif\n";
	fwrite(str_line, strlen(str_line), 1, pfile_h);

	fclose(pfile_h);
	fclose(pfile_c);
}

void code_generate::AddStateManager(CString module_name, tinyxml2::XMLElement* module,
	FILE* pfile_h ,FILE* pfile_c)
{
	CString str_line;
	CString state_id = "";
	CString state_name = "";
	//state
	str_line.Format(_T("extern Ts_StateManager g_%s_buff_state[];\n"), module_name);
	fwrite(str_line, strlen(str_line), 1, pfile_h);

	tinyxml2::XMLElement* state_list = module->FirstChildElement("StateManagerList");
	tinyxml2::XMLElement* state_node = state_list->FirstChildElement("StateManager");
	str_line.Format(_T("Ts_StateManager g_%s_buff_state[] =\n{\n"), module_name);
	fwrite(str_line, strlen(str_line), 1, pfile_c);
	while (state_node != 0)
	{
		state_name = state_node->Attribute("name");
		state_id = state_node->Attribute("id");
		str_line.Format(_T("    {\n"));
		fwrite(str_line, strlen(str_line), 1, pfile_c);
		str_line.Format(_T("        %s,\n"), state_id);
		fwrite(str_line, strlen(str_line), 1, pfile_c);
		str_line.Format(_T("        %s,\n"), state_node->FirstChildElement("FinishDest")->GetText());
		fwrite(str_line, strlen(str_line), 1, pfile_c);
		str_line.Format(_T("        %s,\n"), state_node->FirstChildElement("ExceptDest")->GetText());
		fwrite(str_line, strlen(str_line), 1, pfile_c);
		CString mid_str = state_node->FirstChildElement("StateBeginTask")->GetText();
		if (strcmp(mid_str, "NULL") == 0)
		{
			str_line.Format(_T("        NULL,\n"));
		}
		else
		{
			str_line.Format(_T("        & g_%s_buff_task_%s[%s],\n"), module_name, state_name, state_node->FirstChildElement("StateBeginTask")->GetText());
		}
		fwrite(str_line, strlen(str_line), 1, pfile_c);
		str_line.Format(_T("        & g_%s_exception_%s,\n"), module_name, state_name);
		fwrite(str_line, strlen(str_line), 1, pfile_c);
		str_line.Format(_T("        & g_%s_cooperate_%s,\n"), module_name, state_name);
		fwrite(str_line, strlen(str_line), 1, pfile_c);
		str_line.Format(_T("        NULL,\n"));
		fwrite(str_line, strlen(str_line), 1, pfile_c);
		str_line.Format(_T("        NULL\n"));
		fwrite(str_line, strlen(str_line), 1, pfile_c);
		str_line.Format(_T("    },\n"));
		fwrite(str_line, strlen(str_line), 1, pfile_c);
		str_line.Format(_T("};\n"));
		fwrite(str_line, strlen(str_line), 1, pfile_c);
		
		AddStateCooperate(module_name, state_name, state_node, pfile_h, pfile_c);
		AddStateException(module_name, state_name, state_node, pfile_h, pfile_c);
		AddStateBranch(module_name, state_name, state_node, pfile_h, pfile_c);
		AddStateTask(module_name, state_name, state_node, pfile_h, pfile_c);
		state_node = state_node->NextSiblingElement("StateManager");
	}
}
void code_generate::AddStateJumpMap(CString module_name,
	FILE* pfile_h , FILE* pfile_c)
{
	CString str_line;
	
	//state jump map
	str_line.Format(_T("extern Ts_StateJumpMap g_%s_state_jump_map;\n"), module_name);
	fwrite(str_line, strlen(str_line), 1, pfile_h);

	str_line.Format(_T("Ts_StateJumpMap g_%s_state_jump_map = {0};\n"), module_name);
	fwrite(str_line, strlen(str_line), 1, pfile_c);
}
void code_generate::AddStateCooperate(CString module_name, CString state_name, tinyxml2::XMLElement* state_node,
	FILE* pfile_h, FILE* pfile_c)
{
	CString str_line;
	CString step_id = "";
	//state cooperate
	str_line.Format(_T("extern Ts_StateCooperate g_%s_cooperate_%s;\n"), module_name, state_name);
	fwrite(str_line, strlen(str_line), 1, pfile_h);

	tinyxml2::XMLElement* state_cooperate = state_node->FirstChildElement("StateCooperate");	
	str_line.Format(_T("Ts_StateCooperate g_%s_cooperate_%s =\n{\n"), module_name, state_name);
	fwrite(str_line, strlen(str_line), 1, pfile_c);
	str_line.Format(_T("    %s,\n"), state_node->Attribute("id"));
	fwrite(str_line, strlen(str_line), 1, pfile_c);
	str_line.Format(_T("    %s,\n"), state_cooperate->Attribute("style"));
	fwrite(str_line, strlen(str_line), 1, pfile_c);
	str_line.Format(_T("    %s,\n"), state_cooperate->Attribute("step_count"));
	fwrite(str_line, strlen(str_line), 1, pfile_c);
	str_line.Format(_T("    g_%s_cooperate_%s_buff_step,\n"), module_name, state_name);
	fwrite(str_line, strlen(str_line), 1, pfile_c);
	str_line.Format(_T("    0,\n"));
	fwrite(str_line, strlen(str_line), 1, pfile_c);
	str_line.Format(_T("    Te_StateCooperateResultSucc,\n"));
	fwrite(str_line, strlen(str_line), 1, pfile_c);
	str_line.Format(_T("    %s,\n"), state_cooperate->Attribute("limit"));
	fwrite(str_line, strlen(str_line), 1, pfile_c);
	str_line.Format(_T("    0\n"));
	fwrite(str_line, strlen(str_line), 1, pfile_c);
	str_line.Format(_T("};\n"));
	fwrite(str_line, strlen(str_line), 1, pfile_c);

	//cooperate step buff
	tinyxml2::XMLElement* cooperate_step = state_cooperate->FirstChildElement("CooperateStep");
	tinyxml2::XMLElement* state_depend;
	str_line.Format(_T("extern Ts_CooperateStep g_%s_cooperate_%s_buff_step;\n"), module_name, state_name);
	fwrite(str_line, strlen(str_line), 1, pfile_h);

	str_line.Format(_T("Ts_CooperateStep g_%s_cooperate_%s_buff_step =\n{\n"), module_name, state_name);
	fwrite(str_line, strlen(str_line), 1, pfile_c);
	
	while (cooperate_step != 0)
	{
		step_id = cooperate_step->Attribute("step_id");
		str_line.Format(_T("    {\n"));
		fwrite(str_line, strlen(str_line), 1, pfile_c);
		str_line.Format(_T("        %s,\n"), step_id);
		fwrite(str_line, strlen(str_line), 1, pfile_c);
		str_line.Format(_T("        %s,\n"), cooperate_step->Attribute("buff_count"));
		fwrite(str_line, strlen(str_line), 1, pfile_c);
		str_line.Format(_T("        g_%s_cooperate_%s_buff_depend_%s\n"), module_name, state_name, step_id);
		fwrite(str_line, strlen(str_line), 1, pfile_c);
		str_line.Format(_T("    },\n"));
		fwrite(str_line, strlen(str_line), 1, pfile_c);
		str_line.Format(_T("};\n"));
		fwrite(str_line, strlen(str_line), 1, pfile_c);

		//state depend buff
		str_line.Format(_T("extern Ts_StateDepend g_%s_cooperate_%s_buff_depend_%s;\n"), module_name, state_name, step_id);
		fwrite(str_line, strlen(str_line), 1, pfile_h);

		str_line.Format(_T("Ts_StateDepend g_%s_cooperate_%s_buff_depend_%s =\n{\n"), module_name, state_name, step_id);
		fwrite(str_line, strlen(str_line), 1, pfile_c);
		state_depend = cooperate_step->FirstChildElement("StateDepend");
		while (state_depend != 0)
		{
			str_line.Format(_T("    {\n"));
			fwrite(str_line, strlen(str_line), 1, pfile_c);
			str_line.Format(_T("        %s,\n"), state_depend->Attribute("depend_module_id"));
			fwrite(str_line, strlen(str_line), 1, pfile_c);
			str_line.Format(_T("        %s,\n"), state_depend->Attribute("depend_state_mid"));
			fwrite(str_line, strlen(str_line), 1, pfile_c);
			str_line.Format(_T("        %s\n"), state_depend->Attribute("depend_state_dst"));
			fwrite(str_line, strlen(str_line), 1, pfile_c);
			str_line.Format(_T("    },\n"));
			fwrite(str_line, strlen(str_line), 1, pfile_c);
			state_depend = state_depend->NextSiblingElement("StateDepend");
		}
		str_line.Format(_T("};\n"));
		fwrite(str_line, strlen(str_line), 1, pfile_c);

		cooperate_step = cooperate_step->NextSiblingElement("CooperateStep");
	}
}

void code_generate::AddStateException(CString module_name, CString state_name, tinyxml2::XMLElement* state_node,
	FILE* pfile_h, FILE* pfile_c)
{
	CString str_line;

	//state exception
	str_line.Format(_T("extern Ts_StateException g_%s_exception_%s;\n"), module_name, state_name);
	fwrite(str_line, strlen(str_line), 1, pfile_h);

	tinyxml2::XMLElement* state_exception = state_node->FirstChildElement("StateException");
	str_line.Format(_T("Ts_StateException g_%s_exception_%s =\n{\n"), module_name, state_name);
	fwrite(str_line, strlen(str_line), 1, pfile_c);
	str_line.Format(_T("    %s,\n"), state_node->Attribute("id"));
	fwrite(str_line, strlen(str_line), 1, pfile_c);
	str_line.Format(_T("    %s,\n"), state_exception->FirstChildElement("StateDest")->GetText());
	fwrite(str_line, strlen(str_line), 1, pfile_c);
	str_line.Format(_T("    %s,\n"), state_exception->FirstChildElement("FallbackLevel")->GetText());
	fwrite(str_line, strlen(str_line), 1, pfile_c);
	str_line.Format(_T("    {\n"));
	fwrite(str_line, strlen(str_line), 1, pfile_c);
	str_line.Format(_T("        false,\n"));
	fwrite(str_line, strlen(str_line), 1, pfile_c);
	str_line.Format(_T("        %s\n"), state_exception->FirstChildElement("CooperateException")->FirstChildElement("FallbackLevel")->GetText());
	fwrite(str_line, strlen(str_line), 1, pfile_c);
	str_line.Format(_T("    },\n"));
	fwrite(str_line, strlen(str_line), 1, pfile_c);
	str_line.Format(_T("    {\n"));
	fwrite(str_line, strlen(str_line), 1, pfile_c);
	str_line.Format(_T("        Te_FallbackLevel_None,\n"));
	fwrite(str_line, strlen(str_line), 1, pfile_c);
	str_line.Format(_T("        %s,\n"), state_exception->FirstChildElement("BusinessExceptionList")->Attribute("buff_count"));
	fwrite(str_line, strlen(str_line), 1, pfile_c);
	str_line.Format(_T("        g_%s_buff_business_exception_%s\n"), module_name, state_name);
	fwrite(str_line, strlen(str_line), 1, pfile_c);
	str_line.Format(_T("    },\n"));
	fwrite(str_line, strlen(str_line), 1, pfile_c);
	str_line.Format(_T("};\n"));
	fwrite(str_line, strlen(str_line), 1, pfile_c);

	//business exception buff
	tinyxml2::XMLElement* business_exception_list = state_exception->FirstChildElement("BusinessExceptionList");
	tinyxml2::XMLElement* business_exception = business_exception_list->FirstChildElement("BusinessException");
	str_line.Format(_T("extern Ts_BusinessCheck g_%s_buff_business_exception_%s[];\n"), module_name, state_name);
	fwrite(str_line, strlen(str_line), 1, pfile_h);

	str_line.Format(_T("Ts_BusinessCheck g_%s_buff_business_exception_%s[] =\n{\n"), module_name, state_name);
	fwrite(str_line, strlen(str_line), 1, pfile_c);
	while (business_exception != 0)
	{
		str_line.Format(_T("    {\n"));
		fwrite(str_line, strlen(str_line), 1, pfile_c);
		str_line.Format(_T("        %s,\n"), business_exception->FirstChildElement("FallbackLevel")->GetText());
		fwrite(str_line, strlen(str_line), 1, pfile_c);
		str_line.Format(_T("        %s,\n"), business_exception->FirstChildElement("BusinessCheck")->GetText());
		fwrite(str_line, strlen(str_line), 1, pfile_c);
		str_line.Format(_T("        %s,\n"), business_exception->FirstChildElement("Result")->GetText());
		fwrite(str_line, strlen(str_line), 1, pfile_c);
		str_line.Format(_T("    },\n"));
		fwrite(str_line, strlen(str_line), 1, pfile_c);
		business_exception = business_exception->NextSiblingElement("BusinessException");
	}
	str_line.Format(_T("};\n"));
	fwrite(str_line, strlen(str_line), 1, pfile_c);
}

void code_generate::AddStateBranch(CString module_name, CString state_name, tinyxml2::XMLElement* state_node,
	FILE* pfile_h, FILE* pfile_c)
{
	CString str_line;

	//state exception
	str_line.Format(_T("extern Ts_BranchContext g_%s_buff_branch_%s[];\n"), module_name, state_name);
	fwrite(str_line, strlen(str_line), 1, pfile_h);

	tinyxml2::XMLElement* state_branch_list = state_node->FirstChildElement("StateBranchList");
	tinyxml2::XMLElement* state_branch = state_branch_list->FirstChildElement("StateBranch");
	str_line.Format(_T("Ts_BranchContext g_%s_buff_branch_%s[] =\n{\n"), module_name, state_name);
	fwrite(str_line, strlen(str_line), 1, pfile_c);
	while (state_branch != 0)
	{
		str_line.Format(_T("    {\n"));
		fwrite(str_line, strlen(str_line), 1, pfile_c);
		str_line.Format(_T("        %s,\n"), state_branch->Attribute("type"));
		fwrite(str_line, strlen(str_line), 1, pfile_c);
		str_line.Format(_T("        %s,\n"), state_branch->Attribute("limit"));
		fwrite(str_line, strlen(str_line), 1, pfile_c);
		str_line.Format(_T("        0,\n"));
		fwrite(str_line, strlen(str_line), 1, pfile_c);
		str_line.Format(_T("        0,\n"));
		fwrite(str_line, strlen(str_line), 1, pfile_c);
		str_line.Format(_T("    },\n"));
		fwrite(str_line, strlen(str_line), 1, pfile_c);
		state_branch = state_branch->NextSiblingElement("StateBranch");
	}
	str_line.Format(_T("};\n"));
	fwrite(str_line, strlen(str_line), 1, pfile_c);
}

void code_generate::AddStateTask(CString module_name, CString state_name, tinyxml2::XMLElement* state_node,
	FILE* pfile_h, FILE* pfile_c)
{
	CString str_line;

	//state exception
	str_line.Format(_T("extern Ts_StateTask g_%s_buff_task_%s[];\n"), module_name, state_name);
	fwrite(str_line, strlen(str_line), 1, pfile_h);

	tinyxml2::XMLElement* state_task_list = state_node->FirstChildElement("StateTaskList");
	tinyxml2::XMLElement* state_task = state_task_list->FirstChildElement("StateTask");
	tinyxml2::XMLElement* work_pair = NULL;
	tinyxml2::XMLElement* branch = NULL;
	str_line.Format(_T("Ts_StateTask g_%s_buff_task_%s[] =\n{\n"), module_name, state_name);
	fwrite(str_line, strlen(str_line), 1, pfile_c);
	while (state_task != 0)
	{
		str_line.Format(_T("    {\n"));
		fwrite(str_line, strlen(str_line), 1, pfile_c);
		work_pair = state_task->FirstChildElement("WorkPair");
		str_line.Format(_T("        {\n"));
		fwrite(str_line, strlen(str_line), 1, pfile_c);
		str_line.Format(_T("            %s,\n"), work_pair->FirstChildElement("ConditonResult")->GetText());
		fwrite(str_line, strlen(str_line), 1, pfile_c);
		str_line.Format(_T("            %s,\n"), work_pair->FirstChildElement("WorkCondition")->GetText());
		fwrite(str_line, strlen(str_line), 1, pfile_c);
		str_line.Format(_T("            %s,\n"), work_pair->FirstChildElement("WorkPerformance")->GetText());
		fwrite(str_line, strlen(str_line), 1, pfile_c);
		str_line.Format(_T("        },\n"));
		fwrite(str_line, strlen(str_line), 1, pfile_c);
		branch = state_task->FirstChildElement("Branch");
		if (strcmp(branch->Attribute("id"), "NULL") == 0)
		{
			str_line.Format(_T("        NULL,\n"));
		}
		else
		{
			str_line.Format(_T("        & g_%s_buff_branch_%s[%s],\n"), module_name, state_name, branch->Attribute("id"));
		}
		fwrite(str_line, strlen(str_line), 1, pfile_c);
		str_line.Format(_T("        %s,\n"), branch->Attribute("localization"));
		fwrite(str_line, strlen(str_line), 1, pfile_c);
		if (strcmp(work_pair->Attribute("order_next"),"NULL") == 0)
		{
			str_line.Format(_T("        NULL,\n"));
		}
		else
		{
			str_line.Format(_T("        & g_%s_buff_task_%s[%s],\n"), module_name, state_name, work_pair->Attribute("order_next"));
		}
		fwrite(str_line, strlen(str_line), 1, pfile_c);
		if (strcmp(work_pair->Attribute("parallel_next"), "NULL") == 0)
		{
			str_line.Format(_T("        NULL,\n"));
		}
		else
		{
			str_line.Format(_T("        & g_%s_buff_task_%s[%s],\n"), module_name, state_name, work_pair->Attribute("parallel_next"));
		}
		fwrite(str_line, strlen(str_line), 1, pfile_c);
		str_line.Format(_T("        NULL,\n"));
		fwrite(str_line, strlen(str_line), 1, pfile_c);
		str_line.Format(_T("        NULL,\n"));
		fwrite(str_line, strlen(str_line), 1, pfile_c);
		str_line.Format(_T("    },\n"));
		fwrite(str_line, strlen(str_line), 1, pfile_c);
		state_task = state_task->NextSiblingElement("StateTask");
	}
	str_line.Format(_T("};\n"));
	fwrite(str_line, strlen(str_line), 1, pfile_c);
}


void code_generate::GetModuleList(CStringArray &result)
{
	tinyxml2::XMLElement* root = doc.RootElement();

	tinyxml2::XMLElement* module_node = root->FirstChildElement("Module");
	while (module_node != 0)
	{
		result.Add(module_node->Attribute("name"));
		module_node = module_node->NextSiblingElement("Module");
	}
}
tinyxml2::XMLElement* code_generate::GetModuleElement(CString module)
{
	if (module == "") return NULL;
	tinyxml2::XMLElement* result;
	tinyxml2::XMLElement* root = doc.RootElement();
	CString str_line;
	tinyxml2::XMLElement* module_node = root->FirstChildElement("Module");
	while (module_node != 0)
	{
		if (module_node->Attribute("name") == module)
			return module_node;
		module_node = module_node->NextSiblingElement("Module");
	}
	module_node = root->InsertNewChildElement("Module");
	module_node->SetAttribute("name", module);
	module_node->SetAttribute("id", "Te_ModuleIdentify_" + module);
	tinyxml2::XMLElement* mid_mode = module_node->InsertNewChildElement("StateCount");
	str_line.Format(_T("TE_%s_STATE_COUNT"), module);
	mid_mode->SetText(str_line);

	module_node->InsertNewChildElement("StateJumpMap");
	module_node->InsertNewChildElement("StateManagerList");
	module_node->InsertNewChildElement("DefaultState");
	
	return module_node;
}
void code_generate::GetStateList(CString module, CStringArray& state_list)
{
	if (module == "") return;
	tinyxml2::XMLElement* state_node = GetModuleElement(module)->FirstChildElement("StateManagerList")->FirstChildElement("StateManager");
	while (state_node != 0)
	{
		state_list.Add(state_node->Attribute("name"));
		state_node = state_node->NextSiblingElement("StateManager");
	}
}
tinyxml2::XMLElement* code_generate::GetStateElement(CString module, CString state)
{
	if (module == "" || state == "") return NULL;
	tinyxml2::XMLElement* state_node = GetModuleElement(module)->FirstChildElement("StateManagerList")->FirstChildElement("StateManager");
	while (state_node != 0)
	{
		if (state_node->Attribute("name") == state)
			return state_node;
		state_node = state_node->NextSiblingElement("StateManager");
	}
	return NULL;
}
CString code_generate::GetStateFinishDest(CString module, CString state)
{
	if (state == "")
	{
		return "";
	}
	tinyxml2::XMLElement* state_node = GetStateElement(module, state);
	if (state_node == 0) return "";

	CString str_line = state_node->FirstChildElement("FinishDest")->GetText();
	int pos = str_line.ReverseFind('_');
	return str_line.Right(strlen(str_line) - pos - 1);
}
CString code_generate::GetStateExceptDest(CString module, CString state)
{
	if (state == "")
	{
		return "";
	}
	tinyxml2::XMLElement* state_node = GetStateElement(module, state);
	if (state_node == 0) return "";

	CString str_line = state_node->FirstChildElement("ExceptDest")->GetText();
	int pos = str_line.ReverseFind('_');
	return str_line.Right(strlen(str_line) - pos - 1);
}
CString code_generate::GetStateBeginTask(CString module, CString state)
{
	if (state == "")
	{
		return "";
	}
	tinyxml2::XMLElement* state_node = GetStateElement(module, state);
	if (state_node == 0) return "";

	return state_node->FirstChildElement("StateBeginTask")->GetText();
}
CString code_generate::GetStateCFBL(CString module, CString state)
{
	if (state == "")
	{
		return "";
	}
	tinyxml2::XMLElement* state_node = GetStateElement(module, state);
	if (state_node == 0) return "";

	CString str_line = state_node->FirstChildElement("StateException")\
		->FirstChildElement("CooperateException")\
		->FirstChildElement("FallbackLevel")->GetText();
	return str_rmsub(str_line,"Te_FallbackLevel_");
}
void code_generate::GetStateBeFunction(CString module, CString state, CStringArray& result)
{
	if (state == "")
	{
		return;
	}
	tinyxml2::XMLElement* state_node = GetStateElement(module, state);
	if (state_node == 0) return;
	tinyxml2::XMLElement* list_node = state_node->FirstChildElement("StateException")\
		->FirstChildElement("BusinessExceptionList");
	if (list_node == 0) return;
	tinyxml2::XMLElement* state_be = list_node->FirstChildElement("BusinessException");

	while (state_be != 0)
	{
		result.Add(state_be->FirstChildElement("BusinessCheck")->GetText());
		state_be = state_be->NextSiblingElement("BusinessException");
	}
}
void code_generate::GetStateBeLevel(CString module, CString state, CStringArray& result)
{
	if (state == "")
	{
		return;
	}
	CString str_line;
	tinyxml2::XMLElement* state_node = GetStateElement(module, state);
	if (state_node == 0) return;
	tinyxml2::XMLElement* list_node = state_node->FirstChildElement("StateException")\
		->FirstChildElement("BusinessExceptionList");
	if (list_node == 0) return;
	tinyxml2::XMLElement* state_be = list_node->FirstChildElement("BusinessException");

	while (state_be != 0)
	{
		str_line = state_be->FirstChildElement("FallbackLevel")->GetText();
		result.Add(str_rmsub(str_line,"Te_FallbackLevel_"));
		state_be = state_be->NextSiblingElement("BusinessException");
	}
}
void code_generate::GetStateBeResult(CString module, CString state, CStringArray& result)
{
	if (state == "")
	{
		return;
	}
	CString str_line;
	tinyxml2::XMLElement* state_node = GetStateElement(module, state);
	if (state_node == 0) return;
	tinyxml2::XMLElement* list_node = state_node->FirstChildElement("StateException")\
		->FirstChildElement("BusinessExceptionList");
	if (list_node == 0) return;
	tinyxml2::XMLElement* state_be = list_node->FirstChildElement("BusinessException");

	while (state_be != 0)
	{
		str_line = state_be->FirstChildElement("Result")->GetText();
		result.Add(str_rmsub(str_line, "Te_WorkReuslt_"));
		state_be = state_be->NextSiblingElement("BusinessException");
	}
}
CString code_generate::GetStateCooperateStyle(CString module, CString state)
{
	if (state == "")
	{
		return "";
	}
	tinyxml2::XMLElement* state_node = GetStateElement(module, state);
	if (state_node == 0) return "";

	CString str_line = state_node->FirstChildElement("StateCooperate")\
		->Attribute("style");
	return str_rmsub(str_line, "Te_StateCooperateStyle_");
}
void code_generate::GetStateCoopStep(CString module, CString state, CStringArray& result)
{
	if (state == "")
	{
		return;
	}
	tinyxml2::XMLElement* state_node = GetStateElement(module, state);
	if (state_node == 0) return;
	tinyxml2::XMLElement* state_coop = state_node->FirstChildElement("StateCooperate")\
		->FirstChildElement("CooperateStep");
	while (state_coop != 0)
	{
		CString coop_step = state_coop->Attribute("step_id");
		int depend_cnt = _ttoi(state_coop->Attribute("buff_count"));
		for (int i = 0; i < depend_cnt; i++)
		{
			result.Add(coop_step);
		}
		state_coop = state_coop->NextSiblingElement("CooperateStep");
	}
}
void code_generate::GetStateDependModule(CString module, CString state, CStringArray& result)
{
	if (state == "")
	{
		return;
	}
	CString str_line;
	tinyxml2::XMLElement* state_node = GetStateElement(module, state);
	if (state_node == 0) return;
	tinyxml2::XMLElement* state_coop = state_node->FirstChildElement("StateCooperate")\
		->FirstChildElement("CooperateStep");
	while (state_coop != 0)
	{
		tinyxml2::XMLElement* state_depend = state_coop->FirstChildElement("StateDepend");
		while (state_depend != 0)
		{
			str_line = state_depend->Attribute("depend_module_id");
			result.Add(str_rmsub(str_line,"Te_ModuleIdentify_"));
			state_depend = state_depend->NextSiblingElement("StateDepend");
		}
		state_coop = state_coop->NextSiblingElement("CooperateStep");
	}
}
void code_generate::GetStateDependStateMid(CString module, CString state, CStringArray& result)
{
	if (state == "")
	{
		return;
	}
	CString str_line;
	tinyxml2::XMLElement* state_node = GetStateElement(module, state);
	if (state_node == 0) return;
	tinyxml2::XMLElement* state_coop = state_node->FirstChildElement("StateCooperate")\
		->FirstChildElement("CooperateStep");
	while (state_coop != 0)
	{
		tinyxml2::XMLElement* state_depend = state_coop->FirstChildElement("StateDepend");
		while (state_depend != 0)
		{
			str_line = state_depend->Attribute("depend_state_mid");
			int pos = str_line.ReverseFind('_');
			str_line = str_line.Right(strlen(str_line) - pos - 1);
			result.Add(str_line);
			state_depend = state_depend->NextSiblingElement("StateDepend");
		}
		state_coop = state_coop->NextSiblingElement("CooperateStep");
	}
}
void code_generate::GetStateDependStateDst(CString module, CString state, CStringArray& result)
{
	if (state == "")
	{
		return;
	}
	CString str_line;
	tinyxml2::XMLElement* state_node = GetStateElement(module, state);
	if (state_node == 0) return;
	tinyxml2::XMLElement* state_coop = state_node->FirstChildElement("StateCooperate")\
		->FirstChildElement("CooperateStep");
	while (state_coop != 0)
	{
		tinyxml2::XMLElement* state_depend = state_coop->FirstChildElement("StateDepend");
		while (state_depend != 0)
		{
			str_line = state_depend->Attribute("depend_state_dst");
			int pos = str_line.ReverseFind('_');
			str_line = str_line.Right(strlen(str_line) - pos - 1);
			result.Add(str_line);
			state_depend = state_depend->NextSiblingElement("StateDepend");
		}
		state_coop = state_coop->NextSiblingElement("CooperateStep");
	}
}
void code_generate::GetStateBid(CString module, CString state, CStringArray& result)
{
	if (state == "")
	{
		return;
	}
	tinyxml2::XMLElement* state_node = GetStateElement(module, state);
	if (state_node == 0) return;
	tinyxml2::XMLElement* state_br = state_node->FirstChildElement("StateBranchList")\
		->FirstChildElement("StateBranch");
	while (state_br != 0)
	{
		result.Add(state_br->Attribute("id"));
		state_br = state_br->NextSiblingElement("StateBranch");
	}
}
void code_generate::GetStateBtype(CString module, CString state, CStringArray& result)
{
	if (state == "")
	{
		return;
	}
	CString str_line;
	tinyxml2::XMLElement* state_node = GetStateElement(module, state);
	if (state_node == 0) return;
	tinyxml2::XMLElement* state_br = state_node->FirstChildElement("StateBranchList")\
		->FirstChildElement("StateBranch");
	while (state_br != 0)
	{
		str_line = state_br->Attribute("type");
		result.Add(str_rmsub(str_line, "Te_BranchType_"));
		state_br = state_br->NextSiblingElement("StateBranch");
	}
}
void code_generate::GetStateBlimit(CString module, CString state, CStringArray& result)
{
	if (state == "")
	{
		return;
	}
	tinyxml2::XMLElement* state_node = GetStateElement(module, state);
	if (state_node == 0) return;
	tinyxml2::XMLElement* state_br = state_node->FirstChildElement("StateBranchList")\
		->FirstChildElement("StateBranch");
	while (state_br != 0)
	{
		result.Add(state_br->Attribute("limit"));
		state_br = state_br->NextSiblingElement("StateBranch");
	}
}

void code_generate::GetStateTaskid(CString module, CString state, CStringArray& result)
{
	if (state == "")
	{
		return;
	}
	tinyxml2::XMLElement* state_node = GetStateElement(module, state);
	if (state_node == 0) return;
	tinyxml2::XMLElement* state_task = state_node->FirstChildElement("StateTaskList")\
		->FirstChildElement("StateTask");
	while (state_task != 0)
	{
		result.Add(state_task->Attribute("id"));
		state_task = state_task->NextSiblingElement("StateTask");
	}
}

void code_generate::GetStateTaskBid(CString module, CString state, CStringArray& result)
{
	if (state == "")
	{
		return;
	}
	tinyxml2::XMLElement* state_node = GetStateElement(module, state);
	if (state_node == 0) return;
	tinyxml2::XMLElement* state_task = state_node->FirstChildElement("StateTaskList")\
		->FirstChildElement("StateTask");
	while (state_task != 0)
	{
		result.Add(state_task->FirstChildElement("Branch")->Attribute("id"));
		state_task = state_task->NextSiblingElement("StateTask");
	}
}
void code_generate::GetStateTaskBloc(CString module, CString state, CStringArray& result)
{
	if (state == "")
	{
		return;
	}
	CString str_line;
	tinyxml2::XMLElement* state_node = GetStateElement(module, state);
	if (state_node == 0) return;
	tinyxml2::XMLElement* state_task = state_node->FirstChildElement("StateTaskList")\
		->FirstChildElement("StateTask");
	while (state_task != 0)
	{
		str_line = state_task->FirstChildElement("Branch")->Attribute("localization");
		result.Add(str_rmsub(str_line,"Te_Branch_"));
		state_task = state_task->NextSiblingElement("StateTask");
	}
}
void code_generate::GetStateTaskOrderNext(CString module, CString state, CStringArray& result)
{
	if (state == "")
	{
		return;
	}
	tinyxml2::XMLElement* state_node = GetStateElement(module, state);
	if (state_node == 0) return;
	tinyxml2::XMLElement* state_task = state_node->FirstChildElement("StateTaskList")\
		->FirstChildElement("StateTask");
	while (state_task != 0)
	{
		result.Add(state_task->FirstChildElement("WorkPair")->Attribute("order_next"));
		state_task = state_task->NextSiblingElement("StateTask");
	}
}
void code_generate::GetStateTaskParallelNext(CString module, CString state, CStringArray& result)
{
	if (state == "")
	{
		return;
	}
	tinyxml2::XMLElement* state_node = GetStateElement(module, state);
	if (state_node == 0) return;
	tinyxml2::XMLElement* state_task = state_node->FirstChildElement("StateTaskList")\
		->FirstChildElement("StateTask");
	while (state_task != 0)
	{
		result.Add(state_task->FirstChildElement("WorkPair")->Attribute("parallel_next"));
		state_task = state_task->NextSiblingElement("StateTask");
	}
}
void code_generate::GetStateTaskConditionRslt(CString module, CString state, CStringArray& result)
{
	if (state == "")
	{
		return;
	}
	CString str_line;
	tinyxml2::XMLElement* state_node = GetStateElement(module, state);
	if (state_node == 0) return;
	tinyxml2::XMLElement* state_task = state_node->FirstChildElement("StateTaskList")\
		->FirstChildElement("StateTask");
	while (state_task != 0)
	{
		str_line = state_task->FirstChildElement("WorkPair")->FirstChildElement("ConditonResult")->GetText();
		result.Add(str_rmsub(str_line, "Te_WorkReuslt_"));
		state_task = state_task->NextSiblingElement("StateTask");
	}
}
void code_generate::GetStateTaskWorkCondition(CString module, CString state, CStringArray& result)
{
	if (state == "")
	{
		return;
	}
	tinyxml2::XMLElement* state_node = GetStateElement(module, state);
	if (state_node == 0) return;
	tinyxml2::XMLElement* state_task = state_node->FirstChildElement("StateTaskList")\
		->FirstChildElement("StateTask");
	while (state_task != 0)
	{
		result.Add(state_task->FirstChildElement("WorkPair")->FirstChildElement("WorkCondition")->GetText());
		state_task = state_task->NextSiblingElement("StateTask");
	}
}
void code_generate::GetStateTaskWorkPerformance(CString module, CString state, CStringArray& result)
{
	if (state == "")
	{
		return;
	}
	tinyxml2::XMLElement* state_node = GetStateElement(module, state);
	if (state_node == 0) return;
	tinyxml2::XMLElement* state_task = state_node->FirstChildElement("StateTaskList")\
		->FirstChildElement("StateTask");
	while (state_task != 0)
	{
		result.Add(state_task->FirstChildElement("WorkPair")->FirstChildElement("WorkPerformance")->GetText());
		state_task = state_task->NextSiblingElement("StateTask");
	}
}

void code_generate::Save2Xml()
{
	doc.SaveFile(xml_system_design);
}

void code_generate::SaveNewModule(CString module, CString default_state)
{
	if (module == "")
	{
		return;
	}
	tinyxml2::XMLElement* root = doc.RootElement();	
	tinyxml2::XMLElement* module_node = GetModuleElement(module);
	tinyxml2::XMLElement* mid_mode;
	CString str_line;
	if (module_node == 0)
	{
		module_node = root->InsertNewChildElement("Module");
		module_node->SetAttribute("name", module);
		module_node->SetAttribute("id", "Te_ModuleIdentify_"+module);		

		mid_mode = module_node->InsertNewChildElement("StateCount");
		str_line.Format(_T("TE_%s_STATE_COUNT"), module);
		mid_mode->SetText(str_line);	

		module_node->InsertNewChildElement("StateJumpMap");
		module_node->InsertNewChildElement("StateManagerList");
		module_node->InsertNewChildElement("DefaultState");
	}
	if (default_state != "")
	{
		mid_mode = module_node->FirstChildElement("DefaultState");
		str_line.Format(_T("TE_%s_STATE_%s"), module, default_state);
		mid_mode->SetText(str_line);
	}
}

void code_generate::SaveState(CString module, CString state)
{
	tinyxml2::XMLElement* state_node = GetStateElement(module, state);
	tinyxml2::XMLElement* mid_mode = GetModuleElement(module)->FirstChildElement("StateManagerList");
	CString str_line;
	if (state_node == 0)
	{
		state_node = mid_mode->InsertNewChildElement("StateManager");
		state_node->SetAttribute("name", state);
		str_line.Format(_T("TE_%s_STATE_%s"), module, state);
		state_node->SetAttribute("id", str_line);

		mid_mode = state_node->InsertNewChildElement("FinishDest");
		mid_mode = state_node->InsertNewChildElement("ExceptDest");
		mid_mode = state_node->InsertNewChildElement("StateBeginTask");
		mid_mode = state_node->InsertNewChildElement("StateException");
		mid_mode->InsertNewChildElement("StateDest");
		mid_mode->InsertNewChildElement("FallbackLevel");		
		mid_mode->InsertNewChildElement("CooperateException")->InsertNewChildElement("FallbackLevel");
		mid_mode->InsertNewChildElement("BusinessExceptionList")->SetAttribute("buff_count", "");

		mid_mode = state_node->InsertNewChildElement("StateCooperate");
		mid_mode = state_node->InsertNewChildElement("StateBranchList");
		mid_mode = state_node->InsertNewChildElement("StateTaskList");
	}
}

void code_generate::SaveStateFinishDest(CString module, CString state, CString input)
{
	tinyxml2::XMLElement* state_node = GetStateElement(module, state);
	tinyxml2::XMLElement* mid_mode;
	CString str_line;
	if (state_node != 0)
	{
		mid_mode = state_node->FirstChildElement("FinishDest");
		str_line.Format(_T("TE_%s_STATE_%s"), module, input);
		mid_mode->SetText(str_line);
	}
}

void code_generate::SaveStateExceptDest(CString module, CString state, CString input)
{
	tinyxml2::XMLElement* state_node = GetStateElement(module, state);
	tinyxml2::XMLElement* mid_mode;
	CString str_line;
	if (state_node != 0)
	{
		str_line.Format(_T("TE_%s_STATE_%s"), module, input);
		mid_mode = state_node->FirstChildElement("ExceptDest");
		mid_mode->SetText(str_line);

		mid_mode = state_node->FirstChildElement("StateException")->FirstChildElement("StateDest");
		if (mid_mode == 0)
		{
			mid_mode = state_node->FirstChildElement("StateException")->\
				InsertNewChildElement("FallbackLevel");
			mid_mode->SetText("Te_FallbackLevel_None");
			mid_mode = state_node->FirstChildElement("StateException")->\
				InsertNewChildElement("StateDest");			
		}
		
		mid_mode->SetText(str_line);
	}
}

void code_generate::SaveStateBeginTask(CString module, CString state, CString input)
{
	tinyxml2::XMLElement* state_node = GetStateElement(module, state);
	tinyxml2::XMLElement* mid_mode;
	CString str_line;
	if (state_node != 0)
	{
		mid_mode = state_node->FirstChildElement("StateBeginTask");
		mid_mode->SetText(input);
	}
}

void code_generate::SaveStateCFBL(CString module, CString state, CString input)
{
	tinyxml2::XMLElement* state_node = GetStateElement(module, state);
	tinyxml2::XMLElement* mid_node;
	tinyxml2::XMLElement* se_node;
	CString str_line;
	if (state_node != 0)
	{
		se_node = state_node->FirstChildElement("StateException");
		if (se_node->FirstChildElement("CooperateException") == 0)
		{
			mid_node = se_node->InsertNewChildElement("CooperateException");
			mid_node = mid_node->InsertNewChildElement("FallbackLevel");
		}
		str_line.Format(_T("Te_FallbackLevel_%s"), input);
		se_node->FirstChildElement("CooperateException")\
			->FirstChildElement("FallbackLevel")->SetText(str_line);
	}
}

void code_generate::SaveStateCooperateStyle(CString module, CString state, CString input)
{
	tinyxml2::XMLElement* state_node = GetStateElement(module, state);
	tinyxml2::XMLElement* mid_mode;
	CString str_line;
	if (state_node != 0)
	{
		str_line.Format(_T("Te_StateCooperateStyle_%s"), input);
		state_node->FirstChildElement("StateCooperate")\
			->SetAttribute("style", str_line);
	}
}

void code_generate::SaveStateBeFunction(CString module, CString state, CStringArray& input)
{
	tinyxml2::XMLElement* state_node = GetStateElement(module, state);
	tinyxml2::XMLElement* mid_node;
	tinyxml2::XMLElement* be_node;
	tinyxml2::XMLElement* list_node;
	int buff_cnt = input.GetCount();
	if (state_node != 0 && buff_cnt > 0)
	{
		mid_node = state_node->FirstChildElement("StateException");
		list_node = mid_node->FirstChildElement("BusinessExceptionList");
		if (list_node == 0)
		{
			list_node = state_node->FirstChildElement("StateException")\
				->InsertNewChildElement("BusinessExceptionList");
		}
		list_node->DeleteChildren();
		
		for (int i = 0; i < buff_cnt; i++)
		{
			if (input[i] == "")
			{
				buff_cnt--;
				break;
			}
				
			be_node = list_node->InsertNewChildElement("BusinessException");
			mid_node = be_node->InsertNewChildElement("BusinessCheck");
			mid_node->SetText(input[i]);
			be_node->InsertNewChildElement("FallbackLevel");
			be_node->InsertNewChildElement("Result");
		}
		list_node->SetAttribute("buff_count", buff_cnt);
	}
}

void code_generate::SaveStateBeLevel(CString module, CString state, CStringArray& input)
{
	tinyxml2::XMLElement* state_node = GetStateElement(module, state);
	tinyxml2::XMLElement* mid_node;
	CString str_line;
	if (state_node != 0 && input.GetCount() > 0)
	{
		mid_node = state_node->FirstChildElement("StateException")\
			->FirstChildElement("BusinessExceptionList")\
			->FirstChildElement("BusinessException");

		for (int i = 0; i < input.GetCount(); i++)
		{
			if (input[i] == "")
			{
				break;
			}
			str_line.Format(_T("Te_FallbackLevel_%s"), input[i]);
			mid_node->FirstChildElement("FallbackLevel")->SetText(str_line);
			mid_node = mid_node->NextSiblingElement("BusinessException");
		}
	}
}

void code_generate::SaveStateBeResult(CString module, CString state, CStringArray& input)
{
	tinyxml2::XMLElement* state_node = GetStateElement(module, state);
	tinyxml2::XMLElement* mid_node;
	CString str_line;
	if (state_node != 0 && input.GetCount() > 0)
	{
		mid_node = state_node->FirstChildElement("StateException")\
			->FirstChildElement("BusinessExceptionList")\
			->FirstChildElement("BusinessException");

		for (int i = 0; i < input.GetCount(); i++)
		{
			if (input[i] == "")
			{
				break;
			}
			str_line.Format(_T("Te_WorkReuslt_%s"), input[i]);
			mid_node->FirstChildElement("Result")->SetText(str_line);
			mid_node = mid_node->NextSiblingElement("BusinessException");
		}
	}
}

void code_generate::SaveStateCoopStep(CString module, CString state, CStringArray& input)
{
	tinyxml2::XMLElement* state_node = GetStateElement(module, state);
	tinyxml2::XMLElement* sc_node;
	tinyxml2::XMLElement* step_node = NULL;
	CString step_id = "";
	int step_count = 0;
	int buff_cnt = 0;
	if (state_node != 0 && input.GetCount() > 0)
	{
		sc_node = state_node->FirstChildElement("StateCooperate");
		sc_node->DeleteChildren();

		for (int i = 0; i < input.GetCount(); i++)
		{
			if (input[i] == "")
			{
				break;
			}
			step_count++;
			if (step_id != input[i])
			{
				step_id = input[i];
				step_node = sc_node->InsertNewChildElement("CooperateStep");
				buff_cnt = 1;
				step_node->InsertNewChildElement("StateDepend");
				step_node->SetAttribute("step_id", step_id);
			}
			else
			{
				buff_cnt++;
				step_node->InsertNewChildElement("StateDepend");
			}
			
			step_node->SetAttribute("buff_count", buff_cnt);
		}
		sc_node->SetAttribute("step_count", step_count);
	}
}

void code_generate::SaveStateDependModule(CString module, CString state, CStringArray& input)
{
	tinyxml2::XMLElement* state_node = GetStateElement(module, state);
	tinyxml2::XMLElement* mid_node;
	tinyxml2::XMLElement* step_node;
	CString step_id = "";
	CString str_line;
	int buff_cnt = 0;
	if (state_node != 0 && input.GetCount() > 0)
	{
		mid_node = state_node->FirstChildElement("StateCooperate");
		step_node = mid_node->FirstChildElement("CooperateStep");
		mid_node = step_node->FirstChildElement("StateDepend");

		for (int i = 0; i < input.GetCount(); i++)
		{
			if (input[i] == "")
			{
				break;
			}
			str_line.Format(_T("Te_ModuleIdentify_%s"), input[i]);
			mid_node->SetAttribute("depend_module_id", str_line);

			mid_node = mid_node->NextSiblingElement("StateDepend");
			if (mid_node == 0)
			{
				step_node = step_node->NextSiblingElement("CooperateStep");
				if (step_node == 0)
				{
					break;
				}
				mid_node = step_node->FirstChildElement("StateDepend");
			}
		}
	}
}

void code_generate::SaveStateDependStateMid(CString module, CString state, CStringArray& input)
{
	tinyxml2::XMLElement* state_node = GetStateElement(module, state);
	tinyxml2::XMLElement* mid_node;
	tinyxml2::XMLElement* step_node;
	CString step_id = "";
	CString str_line;
	int buff_cnt = 0;
	if (state_node != 0 && input.GetCount() > 0)
	{

		mid_node = state_node->FirstChildElement("StateCooperate");
		step_node = mid_node->FirstChildElement("CooperateStep");
		mid_node = step_node->FirstChildElement("StateDepend");

		for (int i = 0; i < input.GetCount(); i++)
		{
			if (input[i] == "")
			{
				break;
			}
			str_line.Format(_T("TE_%s_STATE_%s"), mid_node->Attribute("depend_module_id"), input[i]);
			mid_node->SetAttribute("depend_state_mid", str_line);

			mid_node = mid_node->NextSiblingElement("StateDepend");
			if (mid_node == 0)
			{
				step_node = step_node->NextSiblingElement("CooperateStep");
				if (step_node == 0)
				{
					break;
				}
				mid_node = step_node->FirstChildElement("StateDepend");
			}
		}
	}
}

void code_generate::SaveStateDependStateDst(CString module, CString state, CStringArray& input)
{
	tinyxml2::XMLElement* state_node = GetStateElement(module, state);
	tinyxml2::XMLElement* mid_node;
	tinyxml2::XMLElement* step_node;
	CString step_id = "";
	CString str_line;
	int buff_cnt = 0;
	if (state_node != 0 && input.GetCount() > 0)
	{
		mid_node = state_node->FirstChildElement("StateCooperate");
		step_node = mid_node->FirstChildElement("CooperateStep");
		mid_node = step_node->FirstChildElement("StateDepend");

		for (int i = 0; i < input.GetCount(); i++)
		{
			if (input[i] == "")
			{
				break;
			}
			str_line.Format(_T("TE_%s_STATE_%s"), mid_node->Attribute("depend_module_id"), input[i]);
			mid_node->SetAttribute("depend_state_dst", str_line);

			mid_node = mid_node->NextSiblingElement("StateDepend");
			if (mid_node == 0)
			{
				step_node = step_node->NextSiblingElement("CooperateStep");
				if (step_node == 0)
				{
					break;
				}
				mid_node = step_node->FirstChildElement("StateDepend");
			}
		}
	}
}

void code_generate::SaveStateBid(CString module, CString state, CStringArray& input)
{
	tinyxml2::XMLElement* state_node = GetStateElement(module, state);
	tinyxml2::XMLElement* mid_node;
	tinyxml2::XMLElement* br_node;

	if (state_node != 0 && input.GetCount() > 0)
	{
		mid_node = state_node->FirstChildElement("StateBranchList");
		mid_node->DeleteChildren();

		for (int i = 0; i < input.GetCount(); i++)
		{
			if (input[i] == "")
			{
				break;
			}
			br_node = mid_node->InsertNewChildElement("StateBranch");
			br_node->SetAttribute("id", input[i]);
		}
	}
}

void code_generate::SaveStateBtype(CString module, CString state, CStringArray& input)
{
	tinyxml2::XMLElement* state_node = GetStateElement(module, state);
	tinyxml2::XMLElement* mid_node;
	tinyxml2::XMLElement* br_node;
	CString str_line;
	if (state_node != 0 && input.GetCount() > 0)
	{
		mid_node = state_node->FirstChildElement("StateBranchList");
		br_node = mid_node->FirstChildElement("StateBranch");
		for (int i = 0; i < input.GetCount(); i++)
		{			
			if (input[i] == "")
			{
				break;
			}
			str_line.Format(_T("Te_BranchType_%s"), input[i]);
			br_node->SetAttribute("type", str_line);
			br_node = br_node->NextSiblingElement("StateBranch");
		}
	}
}

void code_generate::SaveStateBlimit(CString module, CString state, CStringArray& input)
{
	tinyxml2::XMLElement* state_node = GetStateElement(module, state);
	tinyxml2::XMLElement* mid_node;
	tinyxml2::XMLElement* br_node;

	if (state_node != 0 && input.GetCount() > 0)
	{
		mid_node = state_node->FirstChildElement("StateBranchList");
		br_node = mid_node->FirstChildElement("StateBranch");
		for (int i = 0; i < input.GetCount(); i++)
		{
			br_node->SetAttribute("limit", input[i]);
			br_node = br_node->NextSiblingElement("StateBranch");
		}
	}
}

void code_generate::SaveStateTaskid(CString module, CString state, CStringArray& input)
{
	tinyxml2::XMLElement* state_node = GetStateElement(module, state);
	tinyxml2::XMLElement* mid_node;
	tinyxml2::XMLElement* task_node;
	tinyxml2::XMLElement* list_node;

	if (state_node != 0 && input.GetCount() > 0)
	{
		list_node = state_node->FirstChildElement("StateTaskList");
		list_node->DeleteChildren();

		for (int i = 0; i < input.GetCount(); i++)
		{
			task_node = list_node->InsertNewChildElement("StateTask");
			task_node->SetAttribute("id", input[i]);

			task_node->InsertNewChildElement("Branch");
			mid_node = task_node->InsertNewChildElement("WorkPair");
			mid_node->InsertNewChildElement("ConditonResult");
			mid_node->InsertNewChildElement("WorkCondition");
			mid_node->InsertNewChildElement("WorkPerformance");
		}
	}
}

void code_generate::SaveStateTaskBid(CString module, CString state, CStringArray& input)
{
	tinyxml2::XMLElement* state_node = GetStateElement(module, state);
	tinyxml2::XMLElement* mid_node;
	tinyxml2::XMLElement* task_node;

	if (state_node != 0 && input.GetCount() > 0)
	{
		mid_node = state_node->FirstChildElement("StateTaskList");
		task_node = mid_node->FirstChildElement("StateTask");

		for (int i = 0; i < input.GetCount(); i++)
		{
			task_node->FirstChildElement("Branch")->SetAttribute("id", input[i]);
			task_node = task_node->NextSiblingElement("StateTask");
		}
	}
}

void code_generate::SaveStateTaskBloc(CString module, CString state, CStringArray& input)
{
	tinyxml2::XMLElement* state_node = GetStateElement(module, state);
	tinyxml2::XMLElement* mid_node;
	tinyxml2::XMLElement* task_node;
	CString str_line;
	if (state_node != 0 && input.GetCount() > 0)
	{
		mid_node = state_node->FirstChildElement("StateTaskList");
		task_node = mid_node->FirstChildElement("StateTask");

		for (int i = 0; i < input.GetCount(); i++)
		{
			str_line.Format(_T("Te_Branch_%s"), input[i]);
			task_node->FirstChildElement("Branch")->SetAttribute("localization", str_line);
			task_node = task_node->NextSiblingElement("StateTask");
		}
	}
}

void code_generate::SaveStateTaskOrderNext(CString module, CString state, CStringArray& input)
{
	tinyxml2::XMLElement* state_node = GetStateElement(module, state);
	tinyxml2::XMLElement* mid_node;
	tinyxml2::XMLElement* task_node;

	if (state_node != 0 && input.GetCount() > 0)
	{
		mid_node = state_node->FirstChildElement("StateTaskList");
		task_node = mid_node->FirstChildElement("StateTask");

		for (int i = 0; i < input.GetCount(); i++)
		{
			task_node->FirstChildElement("WorkPair")->SetAttribute("order_next", input[i]);
			task_node = task_node->NextSiblingElement("StateTask");
		}
	}
}

void code_generate::SaveStateTaskParallelNext(CString module, CString state, CStringArray& input)
{
	tinyxml2::XMLElement* state_node = GetStateElement(module, state);
	tinyxml2::XMLElement* mid_node;
	tinyxml2::XMLElement* task_node;

	if (state_node != 0 && input.GetCount() > 0)
	{
		mid_node = state_node->FirstChildElement("StateTaskList");
		task_node = mid_node->FirstChildElement("StateTask");

		for (int i = 0; i < input.GetCount(); i++)
		{
			task_node->FirstChildElement("WorkPair")->SetAttribute("parallel_next", input[i]);
			task_node = task_node->NextSiblingElement("StateTask");
		}
	}
}

void code_generate::SaveStateTaskConditionRslt(CString module, CString state, CStringArray& input)
{
	tinyxml2::XMLElement* state_node = GetStateElement(module, state);
	tinyxml2::XMLElement* mid_node;
	tinyxml2::XMLElement* task_node;
	CString str_line;
	if (state_node != 0 && input.GetCount() > 0)
	{
		mid_node = state_node->FirstChildElement("StateTaskList");
		task_node = mid_node->FirstChildElement("StateTask");

		for (int i = 0; i < input.GetCount(); i++)
		{
			str_line.Format(_T("Te_WorkReuslt_%s"), input[i]);
			task_node->FirstChildElement("WorkPair")->FirstChildElement("ConditonResult")->\
				SetText(str_line);
			task_node = task_node->NextSiblingElement("StateTask");
		}
	}
}

void code_generate::SaveStateTaskWorkCondition(CString module, CString state, CStringArray& input)
{
	tinyxml2::XMLElement* state_node = GetStateElement(module, state);
	tinyxml2::XMLElement* mid_node;
	tinyxml2::XMLElement* task_node;

	if (state_node != 0 && input.GetCount() > 0)
	{
		mid_node = state_node->FirstChildElement("StateTaskList");
		task_node = mid_node->FirstChildElement("StateTask");

		for (int i = 0; i < input.GetCount(); i++)
		{
			task_node->FirstChildElement("WorkPair")->FirstChildElement("WorkCondition")->\
				SetText(input[i]);
			task_node = task_node->NextSiblingElement("StateTask");
		}
	}
}

void code_generate::SaveStateTaskWorkPerformance(CString module, CString state, CStringArray& input)
{
	tinyxml2::XMLElement* state_node = GetStateElement(module, state);
	tinyxml2::XMLElement* mid_node;
	tinyxml2::XMLElement* task_node;

	if (state_node != 0 && input.GetCount() > 0)
	{
		mid_node = state_node->FirstChildElement("StateTaskList");
		task_node = mid_node->FirstChildElement("StateTask");

		for (int i = 0; i < input.GetCount(); i++)
		{
			task_node->FirstChildElement("WorkPair")->FirstChildElement("WorkPerformance")->\
				SetText(input[i]);
			task_node = task_node->NextSiblingElement("StateTask");
		}
	}
}



CString code_generate::str_rmsub(CString src, CString sub)
{
	if (strlen(src) > strlen(sub))
		return src.Right(strlen(src) - strlen(sub));
	else
		return src;
}