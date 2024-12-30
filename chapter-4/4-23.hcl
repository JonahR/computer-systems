int mem_date = [
	icode == ICALL : valP;
	icode == { IPUSHL, IRMMOVL } : valA;
];
