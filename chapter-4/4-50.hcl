
bool instr_valid = icode in 
	{ INOP, IHALT, IRRMOVL, IIADDL, IIRMOVL, ILEAVE, IRMMOVL, IMRMOVL,
	       IOPL, IJXX, ICALL, IRET, IPUSHL, IPOPL };
int srcA = [
	icode in { IRRMOVL, IRMMOVL, IOPL, IPUSHL  } : rA;
	icode in { IPOPL, IRET } : RESP;
	icode in { ILEAVE } : REBP;
	1 : RNONE; # Don't need register
];
int srcB = [
	icode in { IIADDL, IOPL, IRMMOVL, IMRMOVL  } : rB;
	icode in { IPUSHL, IPOPL, ICALL, IRET } : RESP;
	icode in { ILEAVE } : REBP;
	1 : RNONE;  # Don't need register
];
int dstE = [
	icode in { IRRMOVL } && Cnd : rB;
	icode in { IIADDL, IIRMOVL, IOPL} : rB;
	icode in { ILEAVE, IPUSHL, IPOPL, ICALL, IRET } : RESP;
	1 : RNONE;  # Don't write any register
];
int dstM = [
	icode in { IMRMOVL, IPOPL } : rA;
	icode in { ILEAVE } : REBP;
	1 : RNONE;  # Don't write any register
];
int aluA = [
	icode in { IRRMOVL, IOPL } : valA;
	icode in { IIADDL, IIRMOVL, IRMMOVL, IMRMOVL } : valC;
	icode in { ICALL, IPUSHL } : -4;
	icode in { ILEAVE, IRET, IPOPL } : 4;
	# Other instructions don't need ALU
];
int aluB = [
	icode in { ILEAVE, IIADDL, IRMMOVL, IMRMOVL, IOPL, ICALL, 
		      IPUSHL, IRET, IPOPL } : valB;
	icode in { IRRMOVL, IIRMOVL } : 0;
	# Other instructions don't need ALU
];
bool mem_read = icode in { ILEAVE, IMRMOVL, IPOPL, IRET };
int mem_addr = [
	icode in { IRMMOVL, IPUSHL, ICALL, IMRMOVL } : valE;
	icode in { ILEAVE, IPOPL, IRET } : valA;
	# Other instructions don't need address
];
