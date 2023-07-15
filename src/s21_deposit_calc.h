#ifndef S21_DEPOSIT_CALC_H_
#define S21_DEPOSIT_CALC_H_

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

typedef struct unit { 
 struct tm date; 
 double amount; 
 int freq; 
}unit; 

typedef struct bank_info { 
 struct tm date; 
 double dep; 
 double dif; 
 double per_ad;
 double taxes;
}bnk; 
 
typedef struct result {
    time_t date;
    double gained;
    double taxes;
    double deposit;
} res_info;

res_info res(unit *ads, unit *rems, int n_a, int n_r, time_t st_d, time_t end_d, double per, double dep, int cap, double tax, int payment_f);

#endif //S21_DEPOSIT_CALC_H_