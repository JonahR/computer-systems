int srcB = [
	icode in { IOPL, IRMMOVL, IMRMOVL } : rB;
	icode in { IPUSH, IPOPL, ICALL, IRET } : RESP;
	1 : RNONE;
];

