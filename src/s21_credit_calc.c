#include "s21_credit_calc.h"

credit_info result_dif(int dur, double ir, double debt) {
  ir = ir / 100 / 12;
  credit_info res;
  double orig_debt = debt, tmp = 0, min = debt, max = 0, n_debt = 0;
  ;
  for (int i = 0; i < dur; i++) {
    tmp = debt * ir + orig_debt / dur;
    debt = debt - orig_debt / dur;
    if (tmp > max) max = tmp;
    if (tmp < min) min = tmp;
    n_debt += tmp;
    printf("payment: %.2f\n", tmp);
  }
  printf("mp: %.2f | ov: %2.f | td: %2.f\n", min, n_debt - orig_debt, n_debt);
  res.monthly_payment[0] = min;
  res.monthly_payment[1] = max;
  res.overpayment = n_debt - orig_debt;
  res.total_debt = n_debt;
  return res;
}
credit_info result_an(int dur, double ir, double debt) {
  ir = ir / 100 / 12;
  credit_info res;
  double monthly_payment =
             debt * (ir * pow(1 + ir, dur)) / (pow(1 + ir, dur) - 1),
         n_debt = monthly_payment * dur;

  res.monthly_payment[0] = monthly_payment;
  res.monthly_payment[1] = 0;
  res.overpayment = n_debt - debt;
  res.total_debt = n_debt;
  printf("mp: %.2f | ov: %2.f | td: %2.f\n", n_debt / dur, n_debt - debt,
         n_debt);
  return res;
}
