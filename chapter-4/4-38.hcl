bool E_bubble = E_icode == IJXX && !e_Cnd || 
	(E_icode in { IMRMOVL, IPOPL } &&
	E_dstM in {d_srcA, d_srcB})
