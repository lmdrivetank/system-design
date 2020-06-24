#include "rte_sm_type.h"
#include "rte_health_monitor_type.h"
#include "cc.h"
#include "cc_config.h"
#include "cc_data.h"
Ts_StateMachine g_cc_sm = {
    Te_ModuleIdentify_cc,
    TE_cc_STATE_COUNT,
    TE_cc_STATE_ready,
    g_cc_buff_state,
    & g_cc_state_jump_map,
    Te_StateIdentify_Idle,
    Te_StateIdentify_Idle,
    Te_StateIdentify_Idle
};
Ts_StateManager g_cc_buff_state[] =
{
    {
        TE_cc_STATE_ready,
        (null),
        (null),
        & g_cc_buff_task_ready[(null)],
        & g_cc_exception_ready,
        & g_cc_cooperate_ready,
        NULL,
        NULL
    },
};
Ts_StateCooperate g_cc_cooperate_ready =
{
    TE_cc_STATE_ready,
    ,
    (null),
    g_cc_cooperate_ready_buff_step,
    0,
    Te_StateCooperateResultSucc,
    (null),
    0
};
Ts_CooperateStep g_cc_cooperate_ready_buff_step =
{
Ts_StateException g_cc_exception_ready =
{
    TE_cc_STATE_ready,
    (null),
    Te_FallbackLevel_None,
    {
        false,
        (null)
    },
    {
        Te_FallbackLevel_None,
        1,
        g_cc_buff_business_exception_ready
    },
};
Ts_BusinessCheck g_cc_buff_business_exception_ready[] =
{
    {
        Te_FallbackLevel_A,
        f1,
        Te_WorkReuslt_Succ,
    },
};
Ts_BranchContext g_cc_buff_branch_ready[] =
{
};
Ts_StateTask g_cc_buff_task_ready[] =
{
};
    {
        TE_cc_STATE_init,
        idle,
        terminate,
        & g_cc_buff_task_init[(null)],
        & g_cc_exception_init,
        & g_cc_cooperate_init,
        NULL,
        NULL
    },
};
Ts_StateCooperate g_cc_cooperate_init =
{
    TE_cc_STATE_init,
    ,
    (null),
    g_cc_cooperate_init_buff_step,
    0,
    Te_StateCooperateResultSucc,
    (null),
    0
};
Ts_CooperateStep g_cc_cooperate_init_buff_step =
{
Ts_StateException g_cc_exception_init =
{
    TE_cc_STATE_init,
    terminate,
    Te_FallbackLevel_None,
    {
        false,
        (null)
    },
    {
        Te_FallbackLevel_None,
        1,
        g_cc_buff_business_exception_init
    },
};
Ts_BusinessCheck g_cc_buff_business_exception_init[] =
{
    {
        Te_FallbackLevel_A,
        f1,
        Te_WorkReuslt_Succ,
    },
};
Ts_BranchContext g_cc_buff_branch_init[] =
{
};
Ts_StateTask g_cc_buff_task_init[] =
{
};
    {
        TE_cc_STATE_idle,
        (null),
        (null),
        & g_cc_buff_task_idle[(null)],
        & g_cc_exception_idle,
        & g_cc_cooperate_idle,
        NULL,
        NULL
    },
};
Ts_StateCooperate g_cc_cooperate_idle =
{
    TE_cc_STATE_idle,
    ,
    (null),
    g_cc_cooperate_idle_buff_step,
    0,
    Te_StateCooperateResultSucc,
    (null),
    0
};
Ts_CooperateStep g_cc_cooperate_idle_buff_step =
{
Ts_StateException g_cc_exception_idle =
{
    TE_cc_STATE_idle,
    (null),
    Te_FallbackLevel_None,
    {
        false,
        (null)
    },
    {
        Te_FallbackLevel_None,
        1,
        g_cc_buff_business_exception_idle
    },
};
Ts_BusinessCheck g_cc_buff_business_exception_idle[] =
{
    {
        Te_FallbackLevel_A,
        f1,
        Te_WorkReuslt_Succ,
    },
};
Ts_BranchContext g_cc_buff_branch_idle[] =
{
};
Ts_StateTask g_cc_buff_task_idle[] =
{
};
    {
        TE_cc_STATE_terminate,
        (null),
        (null),
        & g_cc_buff_task_terminate[(null)],
        & g_cc_exception_terminate,
        & g_cc_cooperate_terminate,
        NULL,
        NULL
    },
};
Ts_StateCooperate g_cc_cooperate_terminate =
{
    TE_cc_STATE_terminate,
    ,
    (null),
    g_cc_cooperate_terminate_buff_step,
    0,
    Te_StateCooperateResultSucc,
    (null),
    0
};
Ts_CooperateStep g_cc_cooperate_terminate_buff_step =
{
Ts_StateException g_cc_exception_terminate =
{
    TE_cc_STATE_terminate,
    (null),
    Te_FallbackLevel_None,
    {
        false,
        (null)
    },
    {
        Te_FallbackLevel_None,
        1,
        g_cc_buff_business_exception_terminate
    },
};
Ts_BusinessCheck g_cc_buff_business_exception_terminate[] =
{
    {
        Te_FallbackLevel_A,
        f1,
        Te_WorkReuslt_Succ,
    },
};
Ts_BranchContext g_cc_buff_branch_terminate[] =
{
};
Ts_StateTask g_cc_buff_task_terminate[] =
{
};
Ts_StateJumpMap g_cc_state_jump_map = {0};
