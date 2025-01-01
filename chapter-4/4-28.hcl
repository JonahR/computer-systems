int f_stat = [
	imem_error : SADR;
	!instr_valid : SINS;
	icode == IHALT : SHLT;
	1 : SAOK;
];

dff