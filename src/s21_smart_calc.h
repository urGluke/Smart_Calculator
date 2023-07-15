#ifndef S21_SMART_CALC_H_
#define S21_SMART_CALC_H_

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

#define STACK_OVERFLOW -100
#define STACK_UNDERFLOW -101
#define OUT_OF_MEMORY -102

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

typedef struct stack_c{
	char *data;
	size_t size;
	size_t top;
}stack_c;


typedef struct stack_d{
	double *data;
	size_t size;
	size_t top;
}stack_d;


stack_c* create_stack_c();
void resize_c(stack_c *stack); 
void delete_stack_c(stack_c **stack);
void push_c(stack_c *stack, char val);
char pop_c(stack_c *stack);
stack_d* create_stack_d();
void resize_d(stack_d *stack);
void delete_stack_d(stack_d **stack);
void push_d(stack_d *stack, double val);
double pop_d(stack_d *stack);
int prior_chq(char op);
char *num_to_pn(const char *eq, int *shift, int *xf, int *last_op, int *error, int *last_num);
char *op_to_pn(const char *eq, stack_c *stack, int *shift, int *balance, int *err, int *last_op, int *last_num);
char *to_polish_notation(const char *eq, int *err, int *xflag);
int op_type(char op);
double num_to_dbl(char *pn, int *shift);
double binar(char op, double x1, double x2);
double unar(char op, double x);
double calculate_from_pn(char *pn, int xflag, double x, int *err);
double calc_for_tests(const char *eq, int *err);

#endif // S21_SMART_CALC_H_



