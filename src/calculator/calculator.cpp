#include "calculator.h"

#include <iostream>

#include "ui_calculator.h"

calculator::calculator(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::calculator) {
  ui->setupUi(this);
  std::locale().global(std::locale("C"));

  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(slot_casual_symb()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(slot_casual_symb()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(slot_casual_symb()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(slot_casual_symb()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(slot_casual_symb()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(slot_casual_symb()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(slot_casual_symb()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(slot_casual_symb()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(slot_casual_symb()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(slot_casual_symb()));
  connect(ui->pushButton_pi, SIGNAL(clicked()), this, SLOT(slot_casual_symb()));
  connect(ui->pushButton_x, SIGNAL(clicked()), this, SLOT(slot_casual_symb()));
  connect(ui->pushButton_dot, SIGNAL(clicked()), this,
          SLOT(slot_casual_symb()));

  connect(ui->pushButton_div, SIGNAL(clicked()), this,
          SLOT(slot_operator_button()));
  connect(ui->pushButton_plus, SIGNAL(clicked()), this,
          SLOT(slot_operator_button()));
  connect(ui->pushButton_mult, SIGNAL(clicked()), this,
          SLOT(slot_operator_button()));
  connect(ui->pushButton_minus, SIGNAL(clicked()), this,
          SLOT(slot_operator_button()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this,
          SLOT(slot_operator_button()));
  connect(ui->pushButton_pow, SIGNAL(clicked()), this,
          SLOT(slot_operator_button()));

  connect(ui->pushButton_lb, SIGNAL(clicked()), this, SLOT(slot_casual_symb()));
  connect(ui->pushButton_rb, SIGNAL(clicked()), this, SLOT(slot_casual_symb()));

  connect(ui->pushButton_sin, SIGNAL(clicked()), this,
          SLOT(slot_func_button()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this,
          SLOT(slot_func_button()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this,
          SLOT(slot_func_button()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this,
          SLOT(slot_func_button()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this,
          SLOT(slot_func_button()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this,
          SLOT(slot_func_button()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this,
          SLOT(slot_func_button()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(slot_func_button()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this,
          SLOT(slot_func_button()));

  connect(ui->pushButton_clear, SIGNAL(clicked()), this,
          SLOT(slot_clear_button()));

  connect(ui->pushButton_eq, SIGNAL(clicked()), this, SLOT(slot_eq_button()));

  ui->x2->setMaximum(10e6), ui->x2->setMinimum(-10e6), ui->x2->setValue(1);
  ui->x1->setMaximum(10e6), ui->x1->setMinimum(-10e6), ui->x1->setValue(-1);
  ui->y2->setMaximum(10e6), ui->y2->setMinimum(-10e6), ui->y2->setValue(1);
  ui->y1->setMaximum(10e6), ui->y1->setMinimum(-10e6), ui->y1->setValue(-1);

  ui->payment_freq->addItems(pay_freq);
  ui->dur_type->addItems(dur_list);
  ui->cred_type->addItems(cred_ty);
  ui->cred_dur_type->addItems(dur_list);
}

calculator::~calculator() {
  // std::for_each(a_cb_list.begin(), a_cb_list.end(), [](QComboBox *t){delete
  // t;});//lamba for delete
  delete ui;
}

void calculator::slot_casual_symb() {
  QPushButton *button = (QPushButton *)sender();
  if (ui->equation->text().length() == 1 && ui->equation->text() == "0")
    ui->equation->setText(button->text());
  else
    ui->equation->setText(ui->equation->text() + button->text());
}

void calculator::slot_operator_button() {
  QPushButton *button = (QPushButton *)sender();
  ui->equation->setText(ui->equation->text() + button->text());
}

void calculator::slot_func_button() {
  QPushButton *button = (QPushButton *)sender();
  if (ui->equation->text().length() == 1 && ui->equation->text() == "0")
    ui->equation->setText(button->text() + "(");
  else
    ui->equation->setText(ui->equation->text() + button->text() + "(");
}

void calculator::slot_clear_button() { ui->equation->setText(""); }
void calculator::print_graphic(char *pn) {
  int err = 0, size = 10000;
  double minx = ui->x1->value(), maxx = ui->x2->value(), miny = ui->y1->value(),
         maxy = ui->y2->value(), step = 0;
  step = (maxx - minx) / size;
  QVector<double> X(size), Y(size);
  int i = 0;
  for (double x = minx; x <= maxx && i < size && !err; x += step) {
    X[i] = x;
    Y[i++] = calculate_from_pn(pn, 1, x, &err);
  }
  ui->graphic->addGraph();
  if (!err) {
    ui->graphic->graph(0)->setData(X, Y);
    ui->graphic->xAxis->setLabel("X");
    ui->graphic->yAxis->setLabel("Y");
    ui->graphic->xAxis->setRange(minx, maxx);
    ui->graphic->yAxis->setRange(miny, maxy);
    ui->graphic->replot();
  } else
    if_err(1);
}
void calculator::if_err(int err) {
  if (err) ui->equation->setText("ERROR");
}
void calculator::slot_eq_button() {
  std::string label = ui->equation->text().toStdString();
  const char *eq = label.c_str();
  int err = 0, xflag = 0, calc_val = 0;
  char *pn = to_polish_notation(eq, &err, &xflag);
  double x = 0;
  if (ui->x1->value() >= ui->x2->value() || ui->y1->value() >= ui->y2->value())
    err = 1;
  if (!xflag && !err) {
    x = calculate_from_pn(pn, 0, 0.0, &err), calc_val = 1;
  } else {
    if (!err) {
      if (!ui->const_x_toggle->isChecked())
        this->print_graphic(pn);
      else
        x = calculate_from_pn(pn, 1, ui->const_x_value->value(), &err),
        calc_val = 1;
    } else
      if_err(1);
  }
  if (calc_val) ui->equation->setText(QString::number(x, 'f'));
  free(pn);
}

void calculator::on_plus_ad_clicked() {
  int r = ui->ad_list->rowCount();
  QComboBox *buff_cb = new QComboBox(this);
  QDoubleSpinBox *buff_db = new QDoubleSpinBox(this);
  QDateTimeEdit *buff_dt = new QDateTimeEdit(this);
  buff_cb->addItems(freq_ty);
  a_cb_list.push_back(buff_cb);  //для удаления
  std::cout << r << std::endl;
  ui->ad_list->insertRow(r);
  buff_db->setMaximum(1000000000);
  buff_db->setMinimum(0);
  buff_dt->setDisplayFormat("dd.MM.yyyy");
  ui->ad_list->setCellWidget(r, 0, buff_dt);
  ui->ad_list->setCellWidget(r, 1, buff_db);
  ui->ad_list->setCellWidget(r, 2, buff_cb);
}

void calculator::on_minus_ad_clicked() {
  int r = ui->ad_list->rowCount() - 1;
  ui->ad_list->removeRow(r);
}

void calculator::on_plus_with_clicked() {
  int r = ui->r_list->rowCount();
  QComboBox *buff_cb = new QComboBox(this);
  QDoubleSpinBox *buff_db = new QDoubleSpinBox(this);
  QDateTimeEdit *buff_dt = new QDateTimeEdit(this);
  buff_cb->addItems(freq_ty);
  r_cb_list.push_back(buff_cb);  //для удаления
  std::cout << r << std::endl;
  ui->r_list->insertRow(r);
  buff_db->setMaximum(1000000000);
  buff_db->setMinimum(0);
  buff_dt->setDisplayFormat("dd.MM.yyyy");
  ui->r_list->setCellWidget(r, 0, buff_dt);
  ui->r_list->setCellWidget(r, 1, buff_db);
  ui->r_list->setCellWidget(r, 2, buff_cb);
  QDoubleSpinBox *test =
      static_cast<QDoubleSpinBox *>(ui->r_list->cellWidget(0, 1));
  QComboBox *test1 = static_cast<QComboBox *>(ui->r_list->cellWidget(0, 2));
  std::cout << test->value() << " " << test1->currentText().toStdString()
            << std::endl;
}

void calculator::on_minus_with_clicked() {
  int r = ui->r_list->rowCount() - 1;
  ui->r_list->removeRow(r);
}

void calculator::on_pushButton_clicked() {
  calculator::on_minus_ad_clicked();
  calculator::on_minus_with_clicked();
}

void calculator::on_pushButton_10_clicked() {
  QDateTime tmp = ui->start_date->dateTime();
  time_t st_d = tmp.toSecsSinceEpoch(), buff = 0;
  double deposit = ui->dep_val->value(), tax = ui->tax_db->value(),
         ir = ui->interest_rate->value();
  int cap = ui->ir_cap_but->isChecked(),
      payment_freq = pay_freq_type[ui->payment_freq->currentText()];
  int n_a = ui->ad_list->rowCount(),
      r_a = ui->r_list->rowCount();  //размер пополний и снятий
  unit *ads = (unit *)calloc(n_a, sizeof(unit)),
       *rms = (unit *)calloc(r_a, sizeof(unit));
  if (ads == NULL || rms == NULL) exit(0);
  int duration = ui->duration->value() *
                 dur_t_list[ui->dur_type->currentText()];  //рассчет срока
  QDateTimeEdit *buff_dt;
  QDoubleSpinBox *buff_db;
  QComboBox *buff_cb;
  tmp = tmp.addMonths(duration);
  time_t end_d = tmp.toSecsSinceEpoch();  //дата окончания
  double tmp_db = 0;
  struct tm *temp;
  int tmp_freq = 0, error = 0;
  QString result;
  for (int i = 0; i < n_a; i++) {
    buff_dt = static_cast<QDateTimeEdit *>(ui->ad_list->cellWidget(i, 0));
    tmp = buff_dt->dateTime();
    buff = tmp.toSecsSinceEpoch();
    temp = localtime(&buff);
    ads[i].date = *temp;
    buff_db = static_cast<QDoubleSpinBox *>(ui->ad_list->cellWidget(i, 1));
    tmp_db = buff_db->value();
    ads[i].amount = tmp_db;
    buff_cb = static_cast<QComboBox *>(ui->ad_list->cellWidget(i, 2));
    tmp_freq = pay_freq_type[buff_cb->currentText()];
    ads[i].freq = tmp_freq;
    std::cout << "frequency: " << ads[i].freq << std::endl;
  }
  for (int i = 0; i < r_a; i++) {
    buff_dt = static_cast<QDateTimeEdit *>(ui->r_list->cellWidget(i, 0));
    tmp = buff_dt->dateTime();
    buff = tmp.toSecsSinceEpoch();
    temp = localtime(&buff);
    rms[i].date = *temp;
    buff_db = static_cast<QDoubleSpinBox *>(ui->r_list->cellWidget(i, 1));
    tmp_db = buff_db->value();
    rms[i].amount = -tmp_db;
    buff_cb = static_cast<QComboBox *>(ui->r_list->cellWidget(i, 2));
    tmp_freq = pay_freq_type[buff_cb->currentText()];
    rms[i].freq = tmp_freq;
  }
  if (st_d == 0 || deposit == 0 || ir == 0) error = 1;
  res_info fin;
  fin.deposit = 0, fin.gained = 0, fin.taxes = 0;
  if (!error)
    fin = res(ads, rms, n_a, r_a, st_d, end_d, ir, deposit, cap, tax,
              payment_freq),
    tmp.setSecsSinceEpoch(fin.date);
  if (fin.taxes < 0.1) fin.taxes = 0;
  if (!error)
    result = "Deposit withdrawal: " + tmp.toString("dd.MM.yyyy") +
             " | Interest rate gained: " + QString::number(fin.gained, 'f', 2) +
             " | Taxes payed: " + QString::number(fin.taxes, 'f', 2) +
             " | Deposit: " + QString::number(fin.deposit, 'f', 2);
  else
    result = "ERROR";
  ui->result->setText(result);
  free(ads), free(rms);
}

void calculator::on_deposit_clear_button_clicked() {
  while (ui->ad_list->rowCount()) ui->ad_list->removeRow(0);
  while (ui->r_list->rowCount()) ui->r_list->removeRow(0);
  ui->start_date->setDateTime(
      QDateTime::fromString("01.01.2000", "dd.MM.yyyy"));
  ui->dep_val->setValue(0);
  ui->duration->setValue(0);
  ui->interest_rate->setValue(0);
  ui->tax_db->setValue(0);
  ui->result->setText("");
}

void calculator::on_credit_calc_button_clicked() {
  double debt = ui->credit_amount->value(), ir = ui->credit_ir->value();
  int dur =
      ui->cred_duration->value() * dur_t_list[ui->cred_dur_type->currentText()];
  std::cout << "dur: " << dur << std::endl;
  credit_info res;
  QString result;
  int error = 0;
  if (dur == 0 || debt == 0 || ir == 0) error = 1;
  if (ui->cred_type->currentText() == "annuity" && !error)
    res = result_an(dur, ir, debt),
    result =
        "Monthly payment:" + QString::number(res.monthly_payment[0], 'f', 2) +
        " | Overpayment: " + QString::number(res.overpayment, 'f', 2) +
        " | Total debt: " + QString::number(res.total_debt, 'f', 2);
  else if (!error)
    res = result_dif(dur, ir, debt),
    result =
        "Monthly payment:" + QString::number(res.monthly_payment[1], 'f', 2) +
        " - " + QString::number(res.monthly_payment[0], 'f', 2) +
        " | Overpayment: " + QString::number(res.overpayment, 'f', 2) +
        " | Total debt: " + QString::number(res.total_debt, 'f', 2);
  else
    result = "ERROR";
  ui->credit_result->setText(result);
}

void calculator::on_creddit_clear_button_clicked() {
  ui->credit_result->setText("");
  ui->credit_amount->setValue(0);
  ui->credit_ir->setValue(0);
  ui->cred_duration->setValue(0);
}
