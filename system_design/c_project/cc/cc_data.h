#ifndef _cc_DATA_H_
#include "cc_type.h

extern Ts_StateMachine g_cc_sm;
extern Ts_StateManager g_cc_buff_state[];
extern Ts_StateCooperate g_cc_cooperate_ready;
extern Ts_CooperateStep g_cc_cooperate_ready_buff_step;
extern Ts_StateException g_cc_exception_ready;
extern Ts_BusinessCheck g_cc_buff_business_exception_ready[];
extern Ts_BranchContext g_cc_buff_branch_ready[];
extern Ts_StateTask g_cc_buff_task_ready[];
extern Ts_StateCooperate g_cc_cooperate_init;
extern Ts_CooperateStep g_cc_cooperate_init_buff_step;
extern Ts_StateException g_cc_exception_init;
extern Ts_BusinessCheck g_cc_buff_business_exception_init[];
extern Ts_BranchContext g_cc_buff_branch_init[];
extern Ts_StateTask g_cc_buff_task_init[];
extern Ts_StateCooperate g_cc_cooperate_idle;
extern Ts_CooperateStep g_cc_cooperate_idle_buff_step;
extern Ts_StateException g_cc_exception_idle;
extern Ts_BusinessCheck g_cc_buff_business_exception_idle[];
extern Ts_BranchContext g_cc_buff_branch_idle[];
extern Ts_StateTask g_cc_buff_task_idle[];
extern Ts_StateCooperate g_cc_cooperate_terminate;
extern Ts_CooperateStep g_cc_cooperate_terminate_buff_step;
extern Ts_StateException g_cc_exception_terminate;
extern Ts_BusinessCheck g_cc_buff_business_exception_terminate[];
extern Ts_BranchContext g_cc_buff_branch_terminate[];
extern Ts_StateTask g_cc_buff_task_terminate[];
extern Ts_StateJumpMap g_cc_state_jump_map;

#endif
