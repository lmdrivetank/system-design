#ifndef _aa_DATA_H_
#include "aa_type.h

extern Ts_StateMachine g_aa_sm;
extern Ts_StateManager g_aa_buff_state[];
extern Ts_StateCooperate g_aa_cooperate_idle;
extern Ts_CooperateStep g_aa_cooperate_idle_buff_step;
extern Ts_StateDepend g_aa_cooperate_idle_buff_depend_0;
extern Ts_StateException g_aa_exception_idle;
extern Ts_BusinessCheck g_aa_buff_business_exception_idle[];
extern Ts_BranchContext g_aa_buff_branch_idle[];
extern Ts_StateTask g_aa_buff_task_idle[];
extern Ts_StateCooperate g_aa_cooperate_init;
extern Ts_CooperateStep g_aa_cooperate_init_buff_step;
extern Ts_StateDepend g_aa_cooperate_init_buff_depend_0;
extern Ts_StateDepend g_aa_cooperate_init_buff_depend_1;
extern Ts_StateException g_aa_exception_init;
extern Ts_BusinessCheck g_aa_buff_business_exception_init[];
extern Ts_BranchContext g_aa_buff_branch_init[];
extern Ts_StateTask g_aa_buff_task_init[];
extern Ts_StateJumpMap g_aa_state_jump_map;

#endif
