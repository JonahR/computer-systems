int e_valA = [
	M_icode in { IMRMOVL, IPOPL } && (E_icode in { IPUSHL, IRMMOVL } && M_dstM == E_srcA ): m_valM;
	1 : E_valA;  # Use valA from stage pipe register
];

bool F_stall =
	# Conditions for a load/use hazard
	## Set this to the new load/use condition
	E_icode in { IMRMOVL, IPOPL } && !(D_icode in { IPUSHL, IRMMOVL } && E_dstM == d_srcA) &&
        E_dstM in { d_srcA, d_srcB} ||
	# Stalling at fetch while ret passes through pipeline
	IRET in { D_icode, E_icode, M_icode };

bool D_stall =
	# Conditions for a load/use hazard
	## Set this to the new load/use condition
	E_icode in { IMRMOVL, IPOPL } && !(D_icode in { IPUSHL, IRMMOVL } && E_dstM == d_srcA) &&
        	 E_dstM in { d_srcA, d_srcB};

bool D_bubble =
	# Mispredicted branch
	(E_icode == IJXX && !e_Cnd) ||
	# Stalling at fetch while ret passes through pipeline
	# but not condition for a load/use hazard
	!(E_icode in { IMRMOVL, IPOPL } && !(D_icode in { IPUSHL, IRMMOVL } && E_dstM == d_srcA) &&
        E_dstM in { d_srcA, d_srcB}) && IRET in { D_icode, E_icode, M_icode };

bool E_bubble =
	# Mispredicted branch
	(E_icode == IJXX && !e_Cnd) ||
	# Conditions for a load/use hazard
	## Set this to the new load/use condition
	E_icode in { IMRMOVL, IPOPL } && !(D_icode in { IPUSHL, IRMMOVL } && E_dstM == d_srcA) &&
    	 E_dstM in { d_srcA, d_srcB};
