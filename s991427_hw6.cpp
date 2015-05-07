#include <stdio.h>            
#include <stdlib.h>             
double E(int c, double a);
void main(int argc, char *argv[])
{
  double     lambda;            // Total arrival rate
  double     mu;                // Service rate for each server
  int        num_servers;       // Number of servers
  double     a;                 // Total offered load for Erlang-B calculation
  double     rho;               // Utilization for Erlang-C calculation
  double     prob_block;        // Erlang-B blocking probability
  double     prob_queue;        // Erlang-C queueing probability

  // Check if sufficient command line parameters
  if (argc < 4)
  {
    printf("Usage is 'erlang lambda mu num_servers' where lambda is the \n");
    printf("overall arrival rate, mu the per server service rate, and   \n");
    printf("num_server the number of servers                            \n");
    exit(1);
  }

  // Output a banner
  printf("------------------------------------------------ erlang.c -----\n");

  // Assign parameters from entered argv[]
  lambda = atof(argv[1]);
  mu = atof(argv[2]);
  num_servers = atoi(argv[3]);

  // Compute Erlang-B blocking probability using recursive function E()
  a = lambda / mu;
  prob_block = E(num_servers, a);

  // Directly compute Erlang-C queueing probability from Erlang-B probability
  rho = a / num_servers;
  prob_queue = prob_block / (1 - rho + (rho * prob_block));

  // Output input parameters and Erlang probabilities
  printf("lambda = %f  mu = %f  num_servers = %d \n",
    lambda, mu, num_servers);
  printf("rho = %f \n", rho);
  printf("Pr[block] (ErlangB) = %f \n", prob_block);
  if (rho < 1.0)
    printf("Pr[queue] (ErlangC) = %f \n", prob_queue);
  else
    printf("Pr[queue] (ErlangC) = undefined (utilization >= 1.0) \n");
  printf("---------------------------------------------------------------\n");

  system("PAUSE");
 
}


double E(int c, double a)
{
  double     e_last;            // Last E() value

  if (c == 0)
    return(1.0);
  else
    return((a * (e_last = E(c - 1, a))) / (c + a * e_last));
}