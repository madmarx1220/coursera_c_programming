#include <stdio.h>
#include <stdlib.h>

struct _retire_info {
  int months;
  double contribution;
  double rate_of_return;
};
typedef struct _retire_info retire_info;


double  balance_calculation (int startAge, double initial, retire_info information) {
  double balance = initial;
  for(int i = 0; i < information.months; i++) {
    printf("Age %3d month %2d you have $%.2f\n", (startAge+i)/12, (startAge+i)%12, balance);
    balance = balance + information.contribution + balance * information.rate_of_return;
  }
  return balance;
}


void retirement (int startAge,   //in months
                 double initial, //initial savings in dollars
                 retire_info working, //info about working
                 retire_info retired) {//info about being retired
  double  balance = balance_calculation(startAge, initial, working);
  balance = balance_calculation(startAge+working.months, balance, retired);
}

  
int main(void) {
  retire_info working, retired;
  working.months = 489;
  working.contribution = 1000;
  working.rate_of_return = 0.045/12.0;
  retired.months = 384;
  retired.contribution = -4000;
  retired.rate_of_return = 0.01/12.0;
  int startAge = 327;
  double initial = 21345;
  retirement(startAge, initial, working, retired);

  return EXIT_SUCCESS;
}
 
