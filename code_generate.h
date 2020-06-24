#pragma once
#include <iostream>
#include <atlstr.h>
#include <Windows.h>
#include "tinyxml2.h"
#include <afx.h>

using namespace std;
class code_generate
{
public:
	code_generate();
	~code_generate();

private:
	CString project_path;
	CString xml_system_design;
	tinyxml2::XMLDocument doc;
public:
	void GenerateCode();
	void AddModule(tinyxml2::XMLElement* module);
	void AddStateManager(CString module_name, tinyxml2::XMLElement* module,
		FILE* pfile_h, FILE* pfile_c);
	void AddStateJumpMap(CString module_name, FILE* pfile_h, FILE* pfile_c);
	void AddStateCooperate(CString module_name, CString state_name, tinyxml2::XMLElement* state_node, FILE* pfile_h, FILE* pfile_c);
	void AddStateException(CString module_name, CString state_name, tinyxml2::XMLElement* state_node, FILE* pfile_h, FILE* pfile_c);
	void AddStateBranch(CString module_name, CString state_name, tinyxml2::XMLElement* state_node, FILE* pfile_h, FILE* pfile_c);
	void AddStateTask(CString module_name, CString state_name, tinyxml2::XMLElement* state_node, FILE* pfile_h, FILE* pfile_c);

public:
	void GetModuleList(CStringArray& result);
	tinyxml2::XMLElement* GetModuleElement(CString module);
	void GetStateList(CString module, CStringArray &state_list);
	tinyxml2::XMLElement* GetStateElement(CString module, CString state);
	CString GetStateFinishDest(CString module, CString state);
	CString GetStateExceptDest(CString module, CString state);
	CString GetStateBeginTask(CString module, CString state);
	CString GetStateCFBL(CString module, CString state);
	void GetStateBeFunction(CString module, CString state, CStringArray& result);
	void GetStateBeLevel(CString module, CString state, CStringArray& result);
	void GetStateBeResult(CString module, CString state, CStringArray& result);
	CString GetStateCooperateStyle(CString module, CString state);
	void GetStateCoopStep(CString module, CString state, CStringArray& result);
	void GetStateDependModule(CString module, CString state, CStringArray& result);
	void GetStateDependStateMid(CString module, CString state, CStringArray& result);
	void GetStateDependStateDst(CString module, CString state, CStringArray& result);
	void GetStateBid(CString module, CString state, CStringArray& result);
	void GetStateBtype(CString module, CString state, CStringArray& result);
	void GetStateBlimit(CString module, CString state, CStringArray& result);

	void GetStateTaskid(CString module, CString state, CStringArray& result);
	void GetStateTaskBid(CString module, CString state, CStringArray& result);
	void GetStateTaskBloc(CString module, CString state, CStringArray& result);
	void GetStateTaskOrderNext(CString module, CString state, CStringArray& result);
	void GetStateTaskParallelNext(CString module, CString state, CStringArray& result);
	void GetStateTaskConditionRslt(CString module, CString state, CStringArray& result);
	void GetStateTaskWorkCondition(CString module, CString state, CStringArray& result);
	void GetStateTaskWorkPerformance(CString module, CString state, CStringArray& result);

	void Save2Xml();
	void SaveNewModule(CString module, CString default_state);
	void SaveState(CString module, CString state);
	void SaveStateFinishDest(CString module, CString state, CString input);
	void SaveStateExceptDest(CString module, CString state, CString input);
	void SaveStateBeginTask(CString module, CString state, CString input);
	void SaveStateCFBL(CString module, CString state, CString input);
	void SaveStateCooperateStyle(CString module, CString state, CString input);

	void SaveStateBeFunction(CString module, CString state, CStringArray& input);
	void SaveStateBeLevel(CString module, CString state, CStringArray& input);
	void SaveStateBeResult(CString module, CString state, CStringArray& input);
	
	void SaveStateCoopStep(CString module, CString state, CStringArray& input);
	void SaveStateDependModule(CString module, CString state, CStringArray& input);
	void SaveStateDependStateMid(CString module, CString state, CStringArray& input);
	void SaveStateDependStateDst(CString module, CString state, CStringArray& input);
	void SaveStateBid(CString module, CString state, CStringArray& input);
	void SaveStateBtype(CString module, CString state, CStringArray& input);
	void SaveStateBlimit(CString module, CString state, CStringArray& input);

	void SaveStateTaskid(CString module, CString state, CStringArray& result);
	void SaveStateTaskBid(CString module, CString state, CStringArray& input);
	void SaveStateTaskBloc(CString module, CString state, CStringArray& input);
	void SaveStateTaskOrderNext(CString module, CString state, CStringArray& input);
	void SaveStateTaskParallelNext(CString module, CString state, CStringArray& input);
	void SaveStateTaskConditionRslt(CString module, CString state, CStringArray& input);
	void SaveStateTaskWorkCondition(CString module, CString state, CStringArray& input);
	void SaveStateTaskWorkPerformance(CString module, CString state, CStringArray& input);


	CString str_rmsub(CString src, CString sub);
};

