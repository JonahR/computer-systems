bool D_stall = 
	E_icode in { IMRMOBL, IPOPL } &&
	E_dst in {d_srcA, d_srcB}
