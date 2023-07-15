#ifndef S21_CREDIT_CALC_H_
#define S21_CREDIT_CALC_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct credit_info {
    double monthly_payment[2];
    double overpayment;
    double total_debt;
}credit_info;

credit_info result_dif(int dur, double ir, double debt);
credit_info result_an(int dur, double ir, double debt);

#endif //S21_CREDIT_CALC_H_