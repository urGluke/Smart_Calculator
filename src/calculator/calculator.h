#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QDateTime>
#include <QDebug>
#include <QMainWindow>
#include <QMap>
#include <QTableWidgetItem>
#include <QVector>
#include <algorithm>

#include "qcustomplot.h"
extern "C" {
#include "../s21_credit_calc.h"
#include "../s21_deposit_calc.h"
#include "../s21_smart_calc.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class calculator;
}
QT_END_NAMESPACE

class calculator : public QMainWindow {
  Q_OBJECT

 public:
  calculator(QWidget *parent = nullptr);
  ~calculator();

 signals:
  void buttonsignal();

 private:
  Ui::calculator *ui;

 private slots:
  void slot_casual_symb();
  void slot_operator_button();
  void slot_func_button();
  void slot_clear_button();
  void slot_eq_button();
  void print_graphic(char *pn);
  void if_err(int err);

  void on_plus_ad_clicked();

  void on_minus_ad_clicked();

  void on_plus_with_clicked();

  void on_minus_with_clicked();

  void on_pushButton_clicked();

  void on_pushButton_10_clicked();

  void on_deposit_clear_button_clicked();

  void on_credit_calc_button_clicked();

  void on_creddit_clear_button_clicked();

 private:
  QVector<QComboBox *> a_cb_list;
  QVector<QComboBox *> r_cb_list;
  const QStringList pay_freq = {"daily", "monthly", "every quarter",
                                "twice a year", "once a year"};
  const QStringList freq_ty = {"once", "monthly", "every quarter",
                               "twice a year", "once a year"};
  const QStringList dur_list = {"months", "years"};
  const QMap<QString, int> dur_t_list = {{"months", 1}, {"years", 12}};
  const QMap<QString, int> pay_freq_type = {
      {"once", 0},          {"daily", 100},      {"monthly", 1},
      {"every quarter", 3}, {"twice a year", 6}, {"once a year", 12}};
  const QStringList cred_ty = {"annuity", "differential"};
};

#endif  // CALCULATOR_H
