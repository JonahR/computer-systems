int f_icode = [
	imem_error : INOP;
	D_icode == IPOPL: IPOP2;
	1: imem_icode;
];

bool instr_valid = f_icode in
	{ INOP, IHALT, IRRMOVL, IIRMOVL, IRMMOVL, IMRMOVL,
	  IOPL, IJXX, ICALL, IRET, IPUSHL, IPOPL, IPOP2 };

bool need_regids =
	f_icode in { IRRMOVL, IOPL, IPUSHL, IPOPL, IPOP2,
		     IIRMOVL, IRMMOVL, IMRMOVL };

int d_srcA = [
	D_icode in { IRRMOVL, IRMMOVL, IOPL, IPUSHL, IPOP2  } : D_rA;
	D_icode in { IRET } : RESP;
	1 : RNONE; # Don't need register
];

int d_srcB = [
	D_icode in { IOPL, IRMMOVL, IMRMOVL  } : D_rB;
	D_icode in { IPUSHL, IPOPL, ICALL, IRET, IPOP2 } : RESP;
	1 : RNONE;  # Don't need register
];

int d_dstM = [
	D_icode in { IMRMOVL, IPOP2 } : D_rA;
	1 : RNONE;  # Don't write any register
];

## Select input A to ALU
int aluA = [
	E_icode in { IRRMOVL, IOPL } : E_valA;
	E_icode in { IIRMOVL, IRMMOVL, IMRMOVL } : E_valC;
	E_icode in { ICALL, IPUSHL, IPOP2 } : -4;
	E_icode in { IRET, IPOPL } : 4;
	# Other instructions don't need ALU
];

int aluB = [
	E_icode in { IRMMOVL, IMRMOVL, IOPL, ICALL,
		     IPUSHL, IRET, IPOPL, IPOP2 } : E_valB;
	E_icode in { IRRMOVL, IIRMOVL } : 0;
	# Other instructions don't need ALU
];

int mem_addr = [
	M_icode in { IRMMOVL, IPUSHL, ICALL, IMRMOVL, IPOP2 } : M_valE;
	M_icode in { IRET } : M_valA;
	# Other instructions don't need address
];

bool mem_read = M_icode in { IMRMOVL, IPOP2, IRET };

bool F_stall =
	# Conditions for a load/use hazard
	E_icode in { IMRMOVL, IPOP2 } &&
	 E_dstM in { d_srcA, d_srcB } ||
	# Stalling at fetch while ret passes through pipeline
	IRET in { D_icode, E_icode, M_icode };

bool D_stall =
	# Conditions for a load/use hazard
	E_icode in { IMRMOVL, IPOP2 } &&
	 E_dstM in { d_srcA, d_srcB };

bool D_bubble =
	# Mispredicted branch
	(E_icode == IJXX && !e_Cnd) ||
	# Stalling at fetch while ret passes through pipeline
	# but not condition for a load/use hazard
	!(E_icode in { IMRMOVL, IPOP2 } && E_dstM in { d_srcA, d_srcB }) &&
	# 1W: This condition will change
	  IRET in { D_icode, E_icode, M_icode };

bool E_bubble =
	# Mispredicted branch
	(E_icode == IJXX && !e_Cnd) ||
	# Conditions for a load/use hazard
	E_icode in { IMRMOVL, IPOP2 } &&
	 E_dstM in { d_srcA, d_srcB};
