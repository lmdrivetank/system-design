#include "rte_sm_type.h"
#include "rte_health_monitor_type.h"
#include "aa.h"
#include "aa_config.h"
#include "aa_data.h"
Ts_StateMachine g_aa_sm = {
    Te_ModuleIdentify_AA,
    TE_ADS_COUNT,
    TE_aa_STATE_idle,
    g_aa_buff_state,
    & g_aa_state_jump_map,
    Te_StateIdentify_Idle,
    Te_StateIdentify_Idle,
    Te_StateIdentify_Idle
};
Ts_StateManager g_aa_buff_state[] =
{
    {
        TE_ADS_IDLE,
        TE_ADS_IDLE,
        TE_ADS_IDLE,
        NULL,
        & g_aa_exception_idle,
        & g_aa_cooperate_idle,
        NULL,
        NULL
    },
};
Ts_StateCooperate g_aa_cooperate_idle =
{
    TE_ADS_IDLE,
    Te_StateCooperateStyle_Steady,
    1,
    g_aa_cooperate_idle_buff_step,
    0,
    Te_StateCooperateResultSucc,
    5,
    0
};
Ts_CooperateStep g_aa_cooperate_idle_buff_step =
{
    {
        0,
        4,
        g_aa_cooperate_idle_buff_depend_0
    },
};
Ts_StateDepend g_aa_cooperate_idle_buff_depend_0 =
{
    {
        Te_ModuleIdentify_Cybertron,
        TE_ADS_IDLE,
        TE_ADS_IDLE
    },
    {
        Te_ModuleIdentify_LeanControl,
        TE_ADS_IDLE,
        TE_ADS_IDLE
    },
    {
        Te_ModuleIdentify_LeanLocalization,
        TE_ADS_IDLE,
        TE_ADS_IDLE
    },
    {
        Te_ModuleIdentify_VCI,
        TE_ADS_IDLE,
        TE_ADS_IDLE
    },
};
Ts_StateException g_aa_exception_idle =
{
    TE_ADS_IDLE,
    TE_ADS_IDLE,
    Te_FallbackLevel_None,
    {
        false,
        Te_FallbackLevel_None
    },
    {
        Te_FallbackLevel_None,
        2,
        g_aa_buff_business_exception_idle
    },
};
Ts_BusinessCheck g_aa_buff_business_exception_idle[] =
{
    {
        Te_FallbackLevel_None,
        check_function1,
        Te_WorkReuslt_Succ,
    },
    {
        Te_FallbackLevel_None,
        check_function2,
        Te_WorkReuslt_Succ,
    },
};
Ts_BranchContext g_aa_buff_branch_idle[] =
{
    {
        Te_BranchType_Switch,
        1,
        0,
        0,
    },
    {
        Te_BranchType_ParallelOr,
        2,
        0,
        0,
    },
    {
        Te_BranchType_ParallelWith,
        3,
        0,
        0,
    },
};
Ts_StateTask g_aa_buff_task_idle[] =
{
    {
        {
            Te_WorkReuslt_Succ,
            function_ptr1,
            function_ptr2,
        },
        & g_aa_buff_branch_idle[0],
        Te_Branch_Begin,
        & g_aa_buff_task_idle[1],
        NULL,
        NULL,
        NULL,
    },
    {
        {
            Te_WorkReuslt_Succ,
            function_ptr3,
            function_ptr4,
        },
        & g_aa_buff_branch_idle[0],
        Te_Branch_First,
        & g_aa_buff_task_idle[3],
        & g_aa_buff_task_idle[2],
        NULL,
        NULL,
    },
    {
        {
            Te_WorkReuslt_Succ,
            function_ptr5,
            function_ptr6,
        },
        & g_aa_buff_branch_idle[0],
        Te_Branch_First,
        & g_aa_buff_task_idle[3],
        NULL,
        NULL,
        NULL,
    },
    {
        {
            Te_WorkReuslt_Succ,
            function_ptr7,
            function_ptr8,
        },
        & g_aa_buff_branch_idle[0],
        Te_Branch_End,
        NULL,
        NULL,
        NULL,
        NULL,
    },
};
    {
        TE_aa_STATE_init,
        init ,
        ready,
        & g_aa_buff_task_init[0],
        & g_aa_exception_init,
        & g_aa_cooperate_init,
        NULL,
        NULL
    },
};
Ts_StateCooperate g_aa_cooperate_init =
{
    TE_aa_STATE_init,
    Te_StateCooperateStyle_Negotiating,
    (null),
    g_aa_cooperate_init_buff_step,
    0,
    Te_StateCooperateResultSucc,
    (null),
    0
};
Ts_CooperateStep g_aa_cooperate_init_buff_step =
{
    {
        0,
        2,
        g_aa_cooperate_init_buff_depend_0
    },
};
Ts_StateDepend g_aa_cooperate_init_buff_depend_0 =
{
    {
        bb,
        init,
        ready
    },
    {
        cc,
        init,
        ready
    },
};
    {
        1,
        1,
        g_aa_cooperate_init_buff_depend_1
    },
};
Ts_StateDepend g_aa_cooperate_init_buff_depend_1 =
{
    {
        dd,
        init,
        ready
    },
};
Ts_StateException g_aa_exception_init =
{
    TE_aa_STATE_init,
    ready,
    Te_FallbackLevel_None,
    {
        false,
        Te_FallbackLevel_A
    },
    {
        Te_FallbackLevel_None,
        1,
        g_aa_buff_business_exception_init
    },
};
Ts_BusinessCheck g_aa_buff_business_exception_init[] =
{
    {
        Te_FallbackLevel_A,
        f1,
        Te_WorkReuslt_Succ,
    },
};
Ts_BranchContext g_aa_buff_branch_init[] =
{
    {
        Te_BranchType_ParallelWith,
        2,
        0,
        0,
    },
};
Ts_StateTask g_aa_buff_task_init[] =
{
    {
        {
            Te_WorkReuslt_Succ,
            c1,
            w1,
        },
        NULL,
        Te_Branch_Mid,
        & g_aa_buff_task_init[1],
        NULL,
        NULL,
        NULL,
    },
    {
        {
            Te_WorkReuslt_Succ,
            c2,
            w2,
        },
        & g_aa_buff_branch_init[0],
        Te_Branch_Begin,
        & g_aa_buff_task_init[2],
        NULL,
        NULL,
        NULL,
    },
    {
        {
            Te_WorkReuslt_Succ,
            c3,
            w3,
        },
        & g_aa_buff_branch_init[0],
        Te_Branch_First,
        & g_aa_buff_task_init[4],
        & g_aa_buff_task_init[3],
        NULL,
        NULL,
    },
    {
        {
            Te_WorkReuslt_Succ,
            c4,
            w4,
        },
        & g_aa_buff_branch_init[0],
        Te_Branch_First,
        & g_aa_buff_task_init[4],
        NULL,
        NULL,
        NULL,
    },
    {
        {
            Te_WorkReuslt_Succ,
            c5,
            w5,
        },
        & g_aa_buff_branch_init[0],
        Te_Branch_End,
        NULL,
        NULL,
        NULL,
        NULL,
    },
};
Ts_StateJumpMap g_aa_state_jump_map = {0};
