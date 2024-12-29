int aluB = [
	icode in { IOPL, IRMMOVL, IMRMOVL, IPUSHL, IPOPL, ICALL, IRET } : valB;
	icode in { IRRMOVL, IIRMOVL } : 0;
];
