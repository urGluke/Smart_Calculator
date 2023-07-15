#include "s21_deposit_calc.h"

//           add list   withd list  ads num  wit num  start time   end time ir
//           percent  deposit     capitlis  tax perc   payout freq
res_info res(unit *ads, unit *rems, int n_a, int n_r, time_t st_d, time_t end_d,
             double per, double dep, int cap, double tax, int payment_f) {
  bnk out;
  time_t tmp = 0;
  int t_diff = 0;
  per = per / 100;
  tax = tax / 100;
  double diff = 0, daily_per = 0;
  const int daysec = 60 * 60 * 24;
  struct tm *cur = localtime(&st_d), *tem = localtime(&st_d);
  struct tm payment_date = *cur;
  // printf("cur: %d.%d.%d\n", cur->tm_mday, cur->tm_mon, cur->tm_year);
  out.date = *tem, out.dep = dep, out.dif = dep, out.per_ad = 0;
  char s[20] = {0}, s1[20] = {0};
  res_info fin;
  fin.gained = 0, fin.deposit = 0, fin.taxes = 0;
  switch (payment_f) {
    case 1:
      payment_date.tm_mon += 1;
      printf("freq:%d\n", payment_f);
      break;
    case 3:
      payment_date.tm_mon += 3;
      printf("freq:%d\n", payment_f);
      break;
    case 6:
      payment_date.tm_mon += 6;
      printf("freq:%d\n", payment_f);
      break;
    case 12:
      payment_date.tm_year += 1;
      printf("freq:%d\n", payment_f);
      break;
    case 100:
      payment_date.tm_mday++;
      printf("freq:%d\n", payment_f);
      break;
  }
  while (mktime(cur) < end_d) {
    for (int i = 0; i < n_a; i++) {
      if (mktime(&ads[i].date) == mktime(cur))
        diff += ads[i].amount, ads[i].date.tm_mon += ads[i].freq;
    }
    for (int i = 0; i < n_r; i++) {
      if (mktime(&rems[i].date) == mktime(cur))
        diff += rems[i].amount, rems[i].date.tm_mon += rems[i].freq;
    }
    if (out.dep + diff < 0) diff = 0;
    if (cur->tm_year % 4 == 0 && cur->tm_year % 1000 != 0)
      daily_per = per / 366;
    else
      daily_per = per / 365;
    if (!n_a && !n_r && payment_f != 100) {
      switch (payment_f) {
        case 1:
          cur->tm_mon += 1;
          break;
        case 3:
          cur->tm_mon += 3;
          break;
        case 6:
          cur->tm_mon += 6;
          break;
        case 12:
          cur->tm_year += 1;
          break;
      }
    } else
      cur->tm_mday++;
    tmp = mktime(cur);
    cur = localtime(&tmp);
    if (mktime(cur) == mktime(&payment_date)) {
      t_diff = (tmp - mktime(&out.date)) / daysec;
      out.date = payment_date;
      // out[k].date = localtime(&tmp);
      // printf("eq check: %.2lu|%.2lu||t_diff: %d\n", mktime(&payment_date),
      // mktime(cur), t_diff);
      if (cap)
        out.per_ad = out.dep * (double)t_diff * daily_per,
        out.dif = out.per_ad + diff, out.dep = out.dep + out.dif;
      else
        out.per_ad = out.dep * (double)t_diff * daily_per, out.dif = diff,
        out.dep = out.dep + out.dif;
      fin.gained += out.per_ad;
      switch (payment_f) {
        case 1:
          payment_date.tm_mon += 1;
          break;
        case 3:
          payment_date.tm_mon += 3;
          break;
        case 6:
          payment_date.tm_mon += 6;
          break;
        case 12:
          payment_date.tm_year += 1;
          break;
        case 100:
          payment_date.tm_mday++;
          break;
      }
      diff = 0;
      strftime(s, 20, "%d.%m.%Y", cur);
      strftime(s1, 20, "%d.%m.%Y", cur);
      printf(
          "cur: %s | payment_date: %s| interest rate: %.2f | dep ad: %.2f | "
          "deposit: %2.f | daily_per: %.8f\n",
          s, s1, out.per_ad, out.dif, out.dep, daily_per);
    }
  }
  fin.taxes = fin.gained * tax;
  printf("IR: %.2f\n", fin.gained);
  fin.date = mktime(&out.date), fin.deposit = out.dep;
  if (!fin.taxes) fin.taxes = fin.gained * tax;
  // printf("K%d\n", k);
  return fin;
}
