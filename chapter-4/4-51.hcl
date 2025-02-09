################ Pipeline Register Control #########################

# Should I stall or inject a bubble into Pipeline Register F?
# At most one of these can be true.
bool F_bubble = 0;
bool F_stall =
	# Modify the following to stall the update of pipeline register F
	0 ||
	# Stalling at fetch while ret passes through pipeline
		IRET in { D_icode, E_icode, M_icode } ||
	(d_srcA in { e_dstE, E_dstM, M_dstM, M_dstE, W_dstM, W_dstE} && d_srcA != RNONE) ||
	(d_srcB in { e_dstE, E_dstM, M_dstM, M_dstE, W_dstM, W_dstE} && d_srcB != RNONE);

# Should I stall or inject a bubble into Pipeline Register D?
# At most one of these can be true.
bool D_stall = 
	# Modify the following to stall the instruction in decode
	(d_srcA in { e_dstE, E_dstM, M_dstM, M_dstE, W_dstM, W_dstE} && d_srcA != RNONE) ||
	(d_srcB in { e_dstE, E_dstM, M_dstM, M_dstE, W_dstM, W_dstE} && d_srcB != RNONE);

bool D_bubble =
	# Mispredicted branch
	((E_icode == IJXX && !e_Cnd) ||
	# Stalling at fetch while ret passes through pipeline
	!(E_icode in { IMRMOVL, IPOPL } && E_dstM in { d_srcA, d_srcB }) &&
	# but not condition for a generate/use hazard
	!0 &&
	  IRET in { D_icode, E_icode, M_icode }) &&
	!((d_srcA in { e_dstE, E_dstM, M_dstM, M_dstE, W_dstM, W_dstE} && d_srcA != RNONE) ||
	(d_srcB in { e_dstE, E_dstM, M_dstM, M_dstE, W_dstM, W_dstE} && d_srcB != RNONE));

# Should I stall or inject a bubble into Pipeline Register E?
# At most one of these can be true.
bool E_stall = 0;
bool E_bubble =
	# Mispredicted branch
	(E_icode == IJXX && !e_Cnd) ||
	# Modify the following to inject bubble into the execute stage
	(d_srcA in { e_dstE, E_dstM, M_dstM, M_dstE, W_dstM, W_dstE} && d_srcA != RNONE) ||
	(d_srcB in { e_dstE, E_dstM, M_dstM, M_dstE, W_dstM, W_dstE} && d_srcB != RNONE);

# Should I stall or inject a bubble into Pipeline Register M?
# At most one of these can be true.
bool M_stall = 0;
# Start injecting bubbles as soon as exception passes through memory stage
bool M_bubble = m_stat in { SADR, SINS, SHLT } || W_stat in { SADR, SINS, SHLT };

# Should I stall or inject a bubble into Pipeline Register W?
bool W_stall = W_stat in { SADR, SINS, SHLT };
bool W_bubble = 0;
#/* $end pipe-all-hcl */