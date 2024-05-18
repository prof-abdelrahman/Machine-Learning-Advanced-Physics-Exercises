void diluted_PT(int num_T, short int **spin_cfg, int num_n, int N,
int *next, short int *e, double *T,
int *exch, int *tries)
{
  int t, t1, t2; /* loop variables */
  int i; /* index of spin to be flipped */
  double beta1, beta2; /* inverse temperatures */
  double dE; /* energy difference */
  double r_num; /* random number */
  double acc; /* acceptance probability */
  short int *tmp; /* temporary pointer to spin configuration */
  short int *tmp2; /* temporary pointer to spin configuration */

  for(t=0; t<num_T-1; t++)
  {
    t1 = t;
    t2 = t+1;
    beta1 = 1.0/T[t1];
    beta2 = 1.0/T[t2];
    dE = diluted_energy(spin_cfg[t2], num_n, N, next, e) -
    diluted_energy(spin_cfg[t1], num_n, N, next, e);
    tries[t]++;
    if(dE<0.0)
    {
      exch[t]++;
      tmp = spin_cfg[t1];
      spin_cfg[t1] = spin_cfg[t2];
      spin_cfg[t2] = tmp;
    }
    else
    {
      r_num = drand48(); /* random number in [0,1] */
      acc = exp(-dE*(beta2-beta1));
      if(r_num<acc)
      {
        exch[t]++;
        tmp = spin_cfg[t1];
        spin_cfg[t1] = spin_cfg[t2];
        spin_cfg[t2] = tmp;
      }
    }
  }
}
