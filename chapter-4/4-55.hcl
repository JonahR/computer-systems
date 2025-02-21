int f_pc = [
	# Mispredicted branch. Condition is false. Predicted jump to target.
	M_icode == IJXX && M_ifun != UNCOND && !M_Cnd && M_valE < M_valA : M_valA; # We want to use valP
	# Mispredicted branch. Condition is true. Predicted jump to PC.
	M_icode == IJXX && M_ifun != UNCOND && M_Cnd && M_valE >= M_valA : M_valE; # We want to use valC
	# Completion of RET instruction.
	W_icode == IRET : W_valM;
	# Default: Use predicted value of PC
	1 : F_predPC;
];

# Predict next value of PC
int f_predPC = [
	# Predict unconditional jumps and call as taken.
	f_icode in { ICALL } : f_valC;
    f_icode in { IJXX } && f_ifun in { UNCOND } : f_valC;
    # BBTFNT backward branch is taken
    f_icode in { IJXX } && f_valC < f_valP : f_valC;
	1 : f_valP;
];

bool D_bubble =
	# Mispredicted branch
	# BBTFNT: This condition will change
    E_icode == IJXX && E_ifun != UNCOND && !e_Cnd && E_valC < E_valA ||
    E_icode == IJXX && E_ifun != UNCOND && e_Cnd && E_valC >= E_valA ||
	# Stalling at fetch while ret passes through pipeline
	# but not condition for a load/use hazard
	!(E_icode in { IMRMOVL, IPOPL } && E_dstM in { d_srcA, d_srcB }) &&
	  IRET in { D_icode, E_icode, M_icode };


bool E_bubble =
	# BBTFNT: This condition will change
	E_icode == IJXX && E_ifun != UNCOND && !e_Cnd && E_valC < E_valA ||
    E_icode == IJXX && E_ifun != UNCOND && e_Cnd && E_valC >= E_valA ||
	# Conditions for a load/use hazard
	E_icode in { IMRMOVL, IPOPL } &&
	 E_dstM in { d_srcA, d_srcB};

