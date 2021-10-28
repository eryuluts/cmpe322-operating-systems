/*
 * Init barrier to wait for n number of threads.
 * RETURN:
 * 0 on success
 * -1 on error
 */
int Init(int nthreads);

/*
 * Identifies the barrier point. All threads released when required
 * number of threads reach to this point.
 * RETURN:
 * 0 on success
 * -1 on error
 */
int BarrierPoint();
