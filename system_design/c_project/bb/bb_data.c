#include "rte_sm_type.h"
#include "rte_health_monitor_type.h"
#include "bb.h"
#include "bb_config.h"
#include "bb_data.h"
Ts_StateMachine g_bb_sm = {
    Te_ModuleIdentify_bb,
    TE_bb_STATE_COUNT,
    TE_bb_STATE_idle,
    g_bb_buff_state,
    & g_bb_state_jump_map,
    Te_StateIdentify_Idle,
    Te_StateIdentify_Idle,
    Te_StateIdentify_Idle
};
Ts_StateManager g_bb_buff_state[] =
{
    {
        TE_bb_STATE_idle,
        idle,
        idle,
        NULL,
        & g_bb_exception_idle,
        & g_bb_cooperate_idle,
        NULL,
        NULL
    },
};
Ts_StateCooperate g_bb_cooperate_idle =
{
    TE_bb_STATE_idle,
    Te_StateCooperateStyle_Steady,
    (null),
    g_bb_cooperate_idle_buff_step,
    0,
    Te_StateCooperateResultSucc,
    (null),
    0
};
Ts_CooperateStep g_bb_cooperate_idle_buff_step =
{
    {
        0,
        1,
        g_bb_cooperate_idle_buff_depend_0
    },
};
Ts_StateDepend g_bb_cooperate_idle_buff_depend_0 =
{
    {
        cc,
        idle,
        idle
    },
};
    {
        ,
        3,
        g_bb_cooperate_idle_buff_depend_
    },
};
Ts_StateDepend g_bb_cooperate_idle_buff_depend_ =
{
    {
        ,
        ,
        
    },
    {
        ,
        ,
        
    },
    {
        ,
        ,
        
    },
};
Ts_StateException g_bb_exception_idle =
{
    TE_bb_STATE_idle,
    idle,
    Te_FallbackLevel_None,
    {
        false,
        Te_FallbackLevel_D
    },
    {
        Te_FallbackLevel_None,
        3,
        g_bb_buff_business_exception_idle
    },
};
Ts_BusinessCheck g_bb_buff_business_exception_idle[] =
{
    {
        Te_FallbackLevel_D,
        fb1,
        Te_WorkReuslt_Fail,
    },
    {
        (null),
        (null),
        (null),
    },
    {
        (null),
        (null),
        (null),
    },
};
Ts_BranchContext g_bb_buff_branch_idle[] =
{
};
Ts_StateTask g_bb_buff_task_idle[] =
{
};
    {
        TE_bb_STATE_init,
        ready,
        terminate,
        & g_bb_buff_task_init[0],
        & g_bb_exception_init,
        & g_bb_cooperate_init,
        NULL,
        NULL
    },
};
Ts_StateCooperate g_bb_cooperate_init =
{
    TE_bb_STATE_init,
    Te_StateCooperateStyle_Negotiating,
    (null),
    g_bb_cooperate_init_buff_step,
    0,
    Te_StateCooperateResultSucc,
    (null),
    0
};
Ts_CooperateStep g_bb_cooperate_init_buff_step =
{
    {
        0,
        1,
        g_bb_cooperate_init_buff_depend_0
    },
};
Ts_StateDepend g_bb_cooperate_init_buff_depend_0 =
{
    {
        cc,
        init,
        ready
    },
};
    {
        ,
        3,
        g_bb_cooperate_init_buff_depend_
    },
};
Ts_StateDepend g_bb_cooperate_init_buff_depend_ =
{
    {
        ,
        ,
        
    },
    {
        ,
        ,
        
    },
    {
        ,
        ,
        
    },
};
Ts_StateException g_bb_exception_init =
{
    TE_bb_STATE_init,
    terminate,
    Te_FallbackLevel_None,
    {
        false,
        Te_FallbackLevel_B
    },
    {
        Te_FallbackLevel_None,
        3,
        g_bb_buff_business_exception_init
    },
};
Ts_BusinessCheck g_bb_buff_business_exception_init[] =
{
    {
        Te_FallbackLevel_B,
        fb2,
        Te_WorkReuslt_Succ,
    },
    {
        (null),
        (null),
        (null),
    },
    {
        (null),
        (null),
        (null),
    },
};
Ts_BranchContext g_bb_buff_branch_init[] =
{
};
Ts_StateTask g_bb_buff_task_init[] =
{
    {
        {
            Te_WorkReuslt_Succ,
            cb1,
            wb1,
        },
        NULL,
        Te_Branch_Mid,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        {
            (null),
            (null),
            (null),
        },
        & g_bb_buff_branch_init[],
        ,
        & g_bb_buff_task_init[],
        & g_bb_buff_task_init[],
        NULL,
        NULL,
    },
    {
        {
            (null),
            (null),
            (null),
        },
        & g_bb_buff_branch_init[],
        ,
        & g_bb_buff_task_init[],
        & g_bb_buff_task_init[],
        NULL,
        NULL,
    },
    {
        {
            (null),
            (null),
            (null),
        },
        & g_bb_buff_branch_init[],
        ,
        & g_bb_buff_task_init[],
        & g_bb_buff_task_init[],
        NULL,
        NULL,
    },
    {
        {
            (null),
            (null),
            (null),
        },
        & g_bb_buff_branch_init[],
        ,
        & g_bb_buff_task_init[],
        & g_bb_buff_task_init[],
        NULL,
        NULL,
    },
    {
        {
            (null),
            (null),
            (null),
        },
        & g_bb_buff_branch_init[],
        ,
        & g_bb_buff_task_init[],
        & g_bb_buff_task_init[],
        NULL,
        NULL,
    },
    {
        {
            (null),
            (null),
            (null),
        },
        & g_bb_buff_branch_init[],
        ,
        & g_bb_buff_task_init[],
        & g_bb_buff_task_init[],
        NULL,
        NULL,
    },
    {
        {
            (null),
            (null),
            (null),
        },
        & g_bb_buff_branch_init[],
        ,
        & g_bb_buff_task_init[],
        & g_bb_buff_task_init[],
        NULL,
        NULL,
    },
};
Ts_StateJumpMap g_bb_state_jump_map = {0};
