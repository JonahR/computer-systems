int d_destE = [
	D_icode in { IRRMOVL } : D_rB;
	D_icode in { IIRMOVL, IOPL } : D_rB;
	D_icode in { IPUSHL, IPOPL, ICALL, IRET } : RESP;
	1 : RNONE;
];
