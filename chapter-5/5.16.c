void inner4(vec_ptr u, vec_prt v, data_t *dest)
{
	long int i;
	int length = vec_length(u);
	data_t *udata = get_vec_start(u);
	data_t *vdata = get_vec_start(v);
	data_t sum = (data_t) 0;

	for (i = 0; i < length-3; i++) {
		sum = sum + (udata[i] * vdata[i]) + (udata[i+1] * vdata[i+1]) + (udata[i+2] * vdata[i+2]) + (udata[i+3] * vdata[i+3]);
	}

	for (; i < length; i++) {
		sum = sum + (udata[i] * vdata[i]);
	}

	*dest = sum;
}

/*

A. No version of the inner product procedure can have a CPE lower than 2.0 because each element requires 2 load operations and the load unit can only issue one load
every clock cycle.

B. 4 way loop unrolling did not decrease the CPE of floating-point data because we reach the throughput limits without loop
unrolling. 

*/
