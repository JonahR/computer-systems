bool set_cc = E_icode == IOPL &&
	(!M_stat in {HLT, ADR, INS} ||
	!W_stat in {HLT, ADR, INS})
