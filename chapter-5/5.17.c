void inner4(vec_ptr u, vec_prt v, data_t *dest)
{
	long int i;
	int length = vec_length(u);
	data_t *udata = get_vec_start(u);
	data_t *vdata = get_vec_start(v);
	data_t sum = (data_t) 0;

	data_t acc1 = (data_t) 0;	
	data_t acc2 = (data_t) 0;	
	data_t acc3 = (data_t) 0;	
	data_t acc4 = (data_t) 0;	

	for (i = 0; i < length-3; i++) {
		acc1 = acc1 + (udata[i] * vdata[i]);
		acc2 = acc2 + (udata[i+1] * vdata[i+1]);
		acc3 = acc3 + (udata[i+2] * vdata[i+2]);
		acc4 = acc4 + (udata[i+3] * vdata[i+3]);
	}

	for (; i < length; i++) {
		acc1 = acc1 + (udata[i] * vdata[i]);
	}

	*dest = acc1 + acc2 + acc3 + acc4 ;
}

/*

A. The load units limit the performance to a CPE of 2.0 because the processor can only issue 1 load per clock cycle
and each element requires 2 interations.
 
B. This is because IA32 ISAs do not have enough registers to store all 4 accumulator values and load values.
*/
