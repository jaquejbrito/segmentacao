#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>


double loss_func(double res, double a0, int n, int beta){

    return res + a0 / pow(n, beta);
}


void curve_fit(double *Y, double *X, int n, double *a, double *b)
{


}



void segment(double loss_threshold, double maximum_off, double a0, int beta)
{

  int max_seg = 500;
  int min_seg = 3;
  FILE *myFile= fopen("data.dat", "r");

  int k=0;

  double X[max_seg+2], Y[max_seg+2];
  double last_loss = INFINITY, loss;
  double a, b;
  double res;


  //Reading the first point
  if(fscanf(myFile, "%lf %lf", &X[0], &Y[0])!=EOF)
  {
    k=1;

    //Streaming from a file
    while (fscanf(myFile, "%lf %lf", &X[k], &Y[k])!=EOF)
    {
      //Checking for an Off
      if( k > max_seg || X[k] - X[k-1] > maximum_off)
      {
        printf(" It is a cut %d\n", k-1);
        X[0] = X[k];
        Y[0] = Y[k];
        k=0;
      }
      else if(k >= min_seg)
      {
        a = 0.0;
        b = 0.0;

        // Fitting
        curve_fit(X, Y, k, &a, &b);

        res = 0.;
        for(int i=0; i <= k; i++)
        {
          res += pow( Y[i] -  ( X[i]*a + b ), 2);
        }

        loss = loss_func(res, a0, k, beta);

        if( loss > loss_threshold)
        {
          printf(" It is a cut %d\n", k-1);
          X[0] = X[k];
          Y[0] = Y[k];
          k=1;
          last_loss = INFINITY;
        }

      }
      k+=1;
    }
  }
}




int main()
{
//  segment();

}
