void swap(int *xp, int *yp)
{
    *xp = *xp + *yp;
    *yp = *xp - *yp;
    *xp = *xp - *yp;
}

// If this program is called with memory aliasing, then *xp and *yp will be 0.
