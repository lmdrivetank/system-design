#ifndef _bb_DATA_H_
#include "bb_type.h

extern Ts_StateMachine g_bb_sm;
extern Ts_StateManager g_bb_buff_state[];
extern Ts_StateCooperate g_bb_cooperate_idle;
extern Ts_CooperateStep g_bb_cooperate_idle_buff_step;
extern Ts_StateDepend g_bb_cooperate_idle_buff_depend_0;
extern Ts_StateDepend g_bb_cooperate_idle_buff_depend_;
extern Ts_StateException g_bb_exception_idle;
extern Ts_BusinessCheck g_bb_buff_business_exception_idle[];
extern Ts_BranchContext g_bb_buff_branch_idle[];
extern Ts_StateTask g_bb_buff_task_idle[];
extern Ts_StateCooperate g_bb_cooperate_init;
extern Ts_CooperateStep g_bb_cooperate_init_buff_step;
extern Ts_StateDepend g_bb_cooperate_init_buff_depend_0;
extern Ts_StateDepend g_bb_cooperate_init_buff_depend_;
extern Ts_StateException g_bb_exception_init;
extern Ts_BusinessCheck g_bb_buff_business_exception_init[];
extern Ts_BranchContext g_bb_buff_branch_init[];
extern Ts_StateTask g_bb_buff_task_init[];
extern Ts_StateJumpMap g_bb_state_jump_map;

#endif
