


// Performance Monitoring Events for 3rd Generation Intel Core Processors Code Name IvyTown-IVT V7 8/16/2013 1:32:19 PM
struct TopDown {

  using Type= unsigned int;
  using Conf= unsigned long long;


  static constexpr unsigned int CODE_ARITH__FPU_DIV_ACTIVE = 0x530114;
  static constexpr unsigned int CODE_BACLEARS__ANY = 0x531FE6;
  static constexpr unsigned int CODE_BR_INST_RETIRED__NEAR_TAKEN = 0x5320C4;
  static constexpr unsigned int CODE_BR_MISP_RETIRED__ALL_BRANCHES = 0x5300C5;
  static constexpr unsigned int CODE_CPU_CLK_UNHALTED__REF_TSC = 0x530300;
  static constexpr unsigned int CODE_CPU_CLK_UNHALTED__THREAD = 0x530200;
  static constexpr unsigned int CODE_CYCLE_ACTIVITY__CYCLES_NO_EXECUTE = 0x45304A3;
  static constexpr unsigned int CODE_CYCLE_ACTIVITY__STALLS_L1D_PENDING = 0xC530CA3;
  static constexpr unsigned int CODE_CYCLE_ACTIVITY__STALLS_L2_PENDING = 0x55305A3;
  static constexpr unsigned int CODE_CYCLE_ACTIVITY__STALLS_LDM_PENDING = 0x65306A3;
  static constexpr unsigned int CODE_DSB2MITE_SWITCHES__PENALTY_CYCLES = 0x5302AB;
  static constexpr unsigned int CODE_FP_COMP_OPS_EXE__SSE_PACKED_DOUBLE = 0x531010;
  static constexpr unsigned int CODE_FP_COMP_OPS_EXE__SSE_PACKED_SINGLE = 0x534010;
  static constexpr unsigned int CODE_FP_COMP_OPS_EXE__SSE_SCALAR_DOUBLE = 0x538010;
  static constexpr unsigned int CODE_FP_COMP_OPS_EXE__SSE_SCALAR_SINGLE = 0x532010;
  static constexpr unsigned int CODE_FP_COMP_OPS_EXE__X87 = 0x530110;
  static constexpr unsigned int CODE_ICACHE__IFETCH_STALL = 0x530480;
  static constexpr unsigned int CODE_IDQ__ALL_DSB_CYCLES_4_UOPS = 0x4531879;
  static constexpr unsigned int CODE_IDQ__ALL_DSB_CYCLES_ANY_UOPS = 0x1531879;
  static constexpr unsigned int CODE_IDQ__ALL_MITE_CYCLES_4_UOPS = 0x4532479;
  static constexpr unsigned int CODE_IDQ__ALL_MITE_CYCLES_ANY_UOPS = 0x1532479;
  static constexpr unsigned int CODE_IDQ__MS_SWITCHES = 0x1573079;
  static constexpr unsigned int CODE_IDQ__MS_UOPS = 0x533079;
  static constexpr unsigned int CODE_IDQ_UOPS_NOT_DELIVERED__CORE = 0x53019C;
  static constexpr unsigned int CODE_IDQ_UOPS_NOT_DELIVERED__CYCLES_0_UOPS_DELIV__CORE = 0x453019C;
  static constexpr unsigned int CODE_ILD_STALL__LCP = 0x530187;
  static constexpr unsigned int CODE_INST_RETIRED__ANY = 0x530100;
  static constexpr unsigned int CODE_INT_MISC__RECOVERY_CYCLES = 0x153030D;
  static constexpr unsigned int CODE_ITLB_MISSES__WALK_DURATION = 0x530485;
  static constexpr unsigned int CODE_L1D_PEND_MISS__PENDING = 0x530148;
  static constexpr unsigned int CODE_L1D_PEND_MISS__PENDING_CYCLES = 0x1530148;
  static constexpr unsigned int CODE_LSD__CYCLES_4_UOPS = 0x45301A8;
  static constexpr unsigned int CODE_LSD__CYCLES_ACTIVE = 0x15301A8;
  static constexpr unsigned int CODE_LSD__UOPS = 0x5301A8;
  static constexpr unsigned int CODE_MACHINE_CLEARS__COUNT  = 0x15701C3;
  static constexpr unsigned int CODE_MEM_LOAD_UOPS_RETIRED__L1_MISS = 0x5308D1;
  static constexpr unsigned int CODE_MEM_LOAD_UOPS_RETIRED__LLC_HIT = 0x5304D1;
  static constexpr unsigned int CODE_MEM_LOAD_UOPS_RETIRED__LLC_MISS = 0x5320D1;
  static constexpr unsigned int CODE_RESOURCE_STALLS__SB = 0x5308A2;
  static constexpr unsigned int CODE_RS_EVENTS__EMPTY_CYCLES = 0x53015E;
  static constexpr unsigned int CODE_RS_EVENTS__EMPTY_END  = 0x1D7015E;
  static constexpr unsigned int CODE_UOPS_EXECUTED__CYCLES_GE_1_UOP_EXEC = 0x15301B1;
  static constexpr unsigned int CODE_UOPS_EXECUTED__CYCLES_GE_2_UOPS_EXEC = 0x25301B1;
  static constexpr unsigned int CODE_UOPS_EXECUTED__THREAD = 0x5301B1;
  static constexpr unsigned int CODE_UOPS_ISSUED__ANY = 0x53010E;
  static constexpr unsigned int CODE_UOPS_RETIRED__RETIRE_SLOTS = 0x5302C2;

  static constexpr int PipelineWidth = 4;

  static constexpr int METRIC_COUNT=7;
  static constexpr int METRIC_OFFSET=3;
  static constexpr int NGROUPS=4;


  Type types[NGROUPS][METRIC_COUNT] = {
    {
      PERF_TYPE_HARDWARE, // PERF_COUNT_HW_CPU_CYCLES
      PERF_TYPE_SOFTWARE, // PERF_COUNT_SW_CPU_CLOCK
      PERF_TYPE_SOFTWARE, // PERF_COUNT_SW_TASK_CLOCK
      PERF_TYPE_RAW,
      PERF_TYPE_RAW,
      PERF_TYPE_RAW,
      PERF_TYPE_RAW
    },
   {
      PERF_TYPE_HARDWARE, // PERF_COUNT_HW_CPU_CYCLES
      PERF_TYPE_SOFTWARE, // PERF_COUNT_SW_CPU_CLOCK
      PERF_TYPE_SOFTWARE, // PERF_COUNT_SW_TASK_CLOCK
      PERF_TYPE_RAW,
      PERF_TYPE_RAW,
      PERF_TYPE_RAW,
      PERF_TYPE_RAW
    },
   {
      PERF_TYPE_HARDWARE, // PERF_COUNT_HW_CPU_CYCLES
      PERF_TYPE_SOFTWARE, // PERF_COUNT_SW_CPU_CLOCK
      PERF_TYPE_SOFTWARE, // PERF_COUNT_SW_TASK_CLOCK
      PERF_TYPE_RAW,
      PERF_TYPE_RAW,
      PERF_TYPE_RAW,
      PERF_TYPE_RAW
    },
   {
      PERF_TYPE_HARDWARE, // PERF_COUNT_HW_CPU_CYCLES
      PERF_TYPE_SOFTWARE, // PERF_COUNT_SW_CPU_CLOCK
      PERF_TYPE_SOFTWARE, // PERF_COUNT_SW_TASK_CLOCK
      PERF_TYPE_RAW,
      PERF_TYPE_RAW,
      PERF_TYPE_RAW,
      PERF_TYPE_RAW
    }
  };


  Conf confs[NGROUPS][METRIC_COUNT]= {
    {
      PERF_COUNT_HW_CPU_CYCLES,
      PERF_COUNT_SW_CPU_CLOCK,
      PERF_COUNT_SW_TASK_CLOCK,
      CODE_IDQ_UOPS_NOT_DELIVERED__CORE,
      CODE_UOPS_RETIRED__RETIRE_SLOTS,
      CODE_CYCLE_ACTIVITY__CYCLES_NO_EXECUTE
    },
    {
      PERF_COUNT_HW_CPU_CYCLES,
      PERF_COUNT_SW_CPU_CLOCK,
      PERF_COUNT_SW_TASK_CLOCK,
      CODE_UOPS_ISSUED__ANY,
      CODE_UOPS_RETIRED__RETIRE_SLOTS,
      CODE_INT_MISC__RECOVERY_CYCLES
    },
    {
      PERF_COUNT_HW_CPU_CYCLES,
      PERF_COUNT_SW_CPU_CLOCK,
      PERF_COUNT_SW_TASK_CLOCK,
      CODE_UOPS_EXECUTED__CYCLES_GE_1_UOP_EXEC,
      CODE_UOPS_EXECUTED__CYCLES_GE_2_UOPS_EXEC,
      CODE_RS_EVENTS__EMPTY_CYCLE
    },
    {
      PERF_COUNT_HW_CPU_CYCLES,
      PERF_COUNT_SW_CPU_CLOCK,
      PERF_COUNT_SW_TASK_CLOCK,
      CODE_CYCLE_ACTIVITY__STALLS_LDM_PENDING,
      CODE_RESOURCE_STALLS__SB,
      CODE_ARITH__FPU_DIV_ACTIVE
    }
  };

  double CYCLES() const { }
  double SLOTS() const { return PipelineWidth*CYCLES();}


  double frontendBound() const { return IDQ_UOPS_NOT_DELIVERED__CORE() / SLOTS();}
  double backendBound() const { 1. - ( frontendBound() + badSpeculation() + retiring() ); 
  double badSpecutation() const { 
    return ( UOPS_ISSUED__ANY() - UOPS_RETIRED__RETIRE_SLOTS() + 
	     PipelineWidth * INT_MISC__RECOVERY_CYCLES()) / SLOTS();
  }
  double retiring() {
    return UOPS_RETIRED__RETIRE_SLOTS() / SLOTS();
  }


  double backendBundAtEXE_stalls() const {
    return CYCLE_ACTIVITY__CYCLES_NO_EXECUTE() + UOPS_EXECUTED__CYCLES_GE_1_UOP_EXEC() 
      - UOPS_EXECUTED_CYCLES_GE_2_UOPS_EXEC() - RS_EVENTS__EMPTY_CYCLES();
  }


  double memBoundFraction() const {
    return (CYCLE_ACTIVITY__STALLS_LDM_PENDING() + RESOURCE_STALLS__SB() ) 
      / ( backendBoundAtEXE_stalls() + RESOURCE_STALLS__SB() );


    double coreBound() const {
      return backendBundAtEXE_stalls()/CYCLES() - memBoundFraction();
    }

    double divideBound() const {
      return ARITH__FPU_DIV_ACTIVE()/CYCLES();
    }

};
