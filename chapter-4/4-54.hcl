## What address should instruction be fetched at
int f_pc = [
	# Mispredicted branch.  Fetch at incremented PC
	M_icode == IJXX && M_ifun != UNCOND && M_Cnd : M_valA;
	# Completion of RET instruction.
	W_icode == IRET : W_valM;
	# Default: Use predicted value of PC
	1 : F_predPC;
];

# Predict next value of PC
int f_predPC = [
	# BNT: This is where you'll change the branch prediction rule
	f_icode in { ICALL } : f_valC;
	f_icode in { IJXX } && f_ifun in { UNCOND } : f_valC;
	f_icode in { IJXX } : f_valP;
	1 : f_valP;
];

## Generate valA in execute stage
int e_valA = [
	E_icode in { IJXX } && E_ifun != UNCOND && e_Cnd: E_valC;
	1 : E_valA;
];

bool D_bubble =
	# Mispredicted branch
	(E_icode == IJXX && E_ifun != UNCOND && e_Cnd) ||
	# Stalling at fetch while ret passes through pipeline
	# but not condition for a load/use hazard
	!(E_icode in { IMRMOVL, IPOPL } && E_dstM in { d_srcA, d_srcB }) &&
	  IRET in { D_icode, E_icode, M_icode };

# Should I stall or inject a bubble into Pipeline Register E?
# At most one of these can be true.
bool E_stall = 0;
bool E_bubble =
	# Mispredicted branch
	(E_icode == IJXX && E_ifun != UNCOND && e_Cnd) ||
	# Conditions for a load/use hazard
	E_icode in { IMRMOVL, IPOPL } &&
	 E_dstM in { d_srcA, d_srcB};

