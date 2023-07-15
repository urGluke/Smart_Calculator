#include "s21_smart_calc.h"

stack_c *create_stack_c() {
  stack_c *out = NULL;
  out = malloc(sizeof(stack_c));
  if (out == NULL) exit(OUT_OF_MEMORY);
  out->size = 2;
  out->data = malloc(out->size * sizeof(char));
  if (out->data == NULL) free(out), exit(OUT_OF_MEMORY);
  out->top = 0;
  return out;
}
void delete_stack_c(stack_c **stack) {
  free((*stack)->data);
  free(*stack);
  stack = NULL;
}
void resize_c(stack_c *stack) {
  stack->size++;
  stack->data = realloc(stack->data, stack->size * sizeof(char));
  if (stack->data == NULL) printf("stk_c re ov\n"), exit(STACK_OVERFLOW);
}
void push_c(stack_c *stack, char val) {
  if (stack->top >= stack->size) resize_c(stack);
  stack->data[stack->top++] = val;
}
char pop_c(stack_c *stack) {
  if (stack->top == 0) printf("stk_c p und\n"), exit(STACK_UNDERFLOW);
  stack->top--;
  return stack->data[stack->top];
}
char peek_c(const stack_c *stack) {
  if (stack->top <= 0) printf("stk_c pe und\n"), exit(STACK_UNDERFLOW);
  return stack->data[stack->top - 1];
}
stack_d *create_stack_d() {
  stack_d *out = NULL;
  out = malloc(sizeof(stack_d));
  if (out == NULL) exit(OUT_OF_MEMORY);
  out->size = 2;
  out->data = malloc(out->size * sizeof(double));
  if (out->data == NULL) free(out), exit(OUT_OF_MEMORY);
  out->top = 0;
  return out;
}
void delete_stack_d(stack_d **stack) {
  free((*stack)->data);
  free(*stack);
  stack = NULL;
}
void resize_d(stack_d *stack) {
  stack->size++;
  stack->data = realloc(stack->data, stack->size * sizeof(double));
  if (stack->data == NULL) exit(STACK_OVERFLOW);
}
void push_d(stack_d *stack, double val) {
  if (stack->top >= stack->size) resize_d(stack);
  stack->data[stack->top++] = val;
}
double pop_d(stack_d *stack) {
  if (stack->top == 0) printf("stk_d p und\n"), exit(STACK_UNDERFLOW);
  stack->top--;
  return stack->data[stack->top];
}
double peek_d(const stack_d *stack) {
  if (stack->top <= 0) printf("stk_d pe und\n"), exit(STACK_UNDERFLOW);
  return stack->data[stack->top - 1];
}
int prior_chq(char op) {
  int p = 0;
  switch (op) {
    case '~':
    case '`':
    case 'c':
    case 's':
    case 't':
    case 'a':
    case 'i':
    case 'n':
    case 'q':
    case 'l':
    case 'g':
      p = 4;
      break;
    case '^':
      p = 3;
      break;
    case '(':
      p = -1;
      break;
    case '+':
    case '-':
      p = 1;
      break;
    case '*':
    case 'm':
    case '/':
      p = 2;
      break;
      // case ' ': p = -2; break;
  }
  return p;
}

char *num_to_pn(const char *eq, int *shift, int *xf, int *last_op, int *error,
                int *last_num) {
  const char *nms = "0123456789.";
  char *num = (char *)calloc(3, sizeof(char));
  int dots = 0;
  int i = 0, sh = *shift;
  if (eq[sh] == 'x' || eq[sh] == 'X')
    num[i++] = 'x', sh++, *xf = 1;
  else if (eq[sh] == 'p' && eq[sh + 1] == 'i')
    num[i++] = 'p', sh += 2;
  else {
    while (strchr(nms, eq[sh]) != NULL && eq[sh]) {
      if (eq[sh] == '.') dots++;
      num[i++] = eq[sh++];
      num = (char *)realloc(num, (i + 2) * sizeof(char));
    }
  }
  num[i++] = ' ', num[i] = '\0';
  if (dots > 1 || *last_num) *error = 1;
  *last_op = 0, *last_num = 1;
  *shift = sh;
  return num;
}
char *op_to_pn(const char *eq, stack_c *stack, int *shift, int *balance,
               int *err, int *last_op, int *last_num) {
  char op = 0, *tmp = (char *)calloc(2, sizeof(char));
  const char *solo = "+-/*^()";
  int i = 0, sh = *shift;
  if (eq[sh] == '-' && *last_op)
    op = '~', sh++;
  else if (eq[sh] == '+' && *last_op)
    op = '`', sh++;
  else if (strchr(solo, eq[sh]) != NULL) {
    if ((sh == 0 || (unsigned long)sh == strlen(eq) - 1) &&
        op_type(eq[sh]) == 2)
      *err = 1, printf("bin op frs/last\n");
    else
      op = eq[sh], sh++;
  } else if (eq[sh] == 's' && eq[sh + 1] == 'i' && eq[sh + 2] == 'n' &&
             eq[sh + 3] == '(')
    op = 's', sh += 3;
  else if (eq[sh] == 'c' && eq[sh + 1] == 'o' && eq[sh + 2] == 's' &&
           eq[sh + 3] == '(')
    op = 'c', sh += 3;
  else if (eq[sh] == 't' && eq[sh + 1] == 'a' && eq[sh + 2] == 'n' &&
           eq[sh + 3] == '(')
    op = 't', sh += 3;
  else if (eq[sh] == 'a' && eq[sh + 1] == 'c' && eq[sh + 2] == 'o' &&
           eq[i + 3] == 's' && eq[sh + 4] == '(')
    op = 'a', sh += 4;
  else if (eq[sh] == 'a' && eq[sh + 1] == 's' && eq[sh + 2] == 'i' &&
           eq[sh + 3] == 'n' && eq[sh + 4] == '(')
    op = 'i', sh += 4;
  else if (eq[sh] == 'a' && eq[sh + 1] == 't' && eq[sh + 2] == 'a' &&
           eq[sh + 3] == 'n' && eq[sh + 4] == '(')
    op = 'n', sh += 4;
  else if (eq[sh] == 's' && eq[sh + 1] == 'q' && eq[sh + 2] == 'r' &&
           eq[sh + 3] == 't' && eq[sh + 4] == '(')
    op = 'q', sh += 4;
  else if (eq[sh] == 'l' && eq[sh + 1] == 'n' && eq[sh + 2] == '(')
    op = 'l', sh += 2;
  else if (eq[sh] == 'l' && eq[sh + 1] == 'o' && eq[sh + 2] == 'g' &&
           eq[sh + 3] == '(')
    op = 'g', sh += 3;
  else if (eq[sh] == 'm' && eq[sh + 1] == 'o' && eq[sh + 2] == 'd')
    op = 'm', sh += 3;
  else
    printf("unrec char: %c\n", eq[sh]), *err = 1;
  printf("op: %c\n", op);
  if (op == ')' && *last_op) *err = 1, printf("op bef cl br\n");
  if (op_type(op) == 2 && (*last_op && peek_c(stack) != ')'))
    *err = 1, printf("bin op after op: %c\n", op);
  if (*last_num && (op == '(' || prior_chq(op) == 4))
    *err = 1, printf("no oper before func\n");
  if (*balance == 0 && op == ')')
    printf("2 much lf br\n"), *err = 1;
  else if (op == '(')
    push_c(stack, '('), *balance -= 1;
  else if (op == ')') {
    *balance += 1;
    while (stack->top && peek_c(stack) != '(' && !*err) {
      tmp[i++] = pop_c(stack), tmp[i++] = ' ';
      tmp = (char *)realloc(tmp, (i + 2) * sizeof(char));
    }
    pop_c(stack);
    if (stack->top && op_type(peek_c(stack)) == 1) {
      tmp[i++] = pop_c(stack), tmp[i++] = ' ';
      tmp = (char *)realloc(tmp, (i + 2) * sizeof(char));
    }
    tmp[i] = '\0';
  } else {
    // if(stack->top)	printf("st_p: %c|%d || op: %c|%d\n",
    // peek_c(stack),prior_chq(peek_c(stack)), op, prior_chq(op));
    while (stack->top && prior_chq(peek_c(stack)) >= prior_chq(op) && !*err &&
           prior_chq(op) < 3) {
      tmp[i++] = pop_c(stack), tmp[i++] = ' ';
      tmp = (char *)realloc(tmp, (i + 2) * sizeof(char));
    }
    tmp[i] = '\0';
    push_c(stack, op);
  }
  if (!*err && op != ')') *last_op = 1, *last_num = 0;
  *shift = sh;
  return tmp;
}
char *to_polish_notation(const char *eq, int *err, int *xflag) {
  char *pn = (char *)calloc(2, sizeof(char));
  char *tmp;
  int i = 0, k = 0, blnc = 0, error = 0, xf = 0, last_op = 1, last_num = 0;
  char *nums = "0123456789.pxX", *ops = "+-*/^()acgilmnoqrst";
  stack_c *stack = create_stack_c();
  while (i < (int)strlen(eq) && !error) {
    if (eq[i] == ' ') {
      i++;
      continue;
    } else if (strchr(nums, eq[i]) != NULL)
      tmp = num_to_pn(eq, &i, &xf, &last_op, &error, &last_num);
    else if (strchr(ops, eq[i]) != NULL)
      tmp = op_to_pn(eq, stack, &i, &blnc, &error, &last_op, &last_num);
    else {
      error = 1;
      break;
    }
    k += strlen(tmp);
    pn = (char *)realloc(pn, (k + 1) * sizeof(char));
    strcat(pn, tmp);
    free(tmp);
  }
  if (stack->top && !error) {
    pn = (char *)realloc(pn, (k + 2 + stack->size * 2) * sizeof(char));
    while (stack->top) {
      pn[k++] = pop_c(stack), pn[k++] = ' ';
    }
    pn[k] = '\0';
  }
  if (blnc || error) printf("to_pol\n"), *err = 1;
  delete_stack_c(&stack);
  *xflag = xf;
  return pn;
}
//+-* /^()acgilmnoqrst"
int op_type(char op) {
  int tp = 0;
  switch (op) {
    case '+':
    case '-':
    case '*':
    case '/':
    case 'm':
    case '^':
      tp = 2;
      break;
    case 'a':
    case 'c':
    case 'g':
    case 'i':
    case 'l':
    case 'n':
    case 'o':
    case 'q':
    case 'r':
    case 's':
    case 't':
    case '~':
      tp = 1;
      break;
  }
  return tp;
}
double num_to_dbl(char *pn, int *shift) {
  double x = 0;
  int sh = *shift, i = 0;
  char *nums = "0123456789.";
  char *num = (char *)calloc(2, sizeof(char));
  if (pn[sh] == 'p')
    x = M_PI;
  else {
    while (strchr(nums, pn[sh]) != NULL) {
      num = (char *)realloc(num, (i + 2) * sizeof(char));
      num[i++] = pn[sh++];
    }
    num[i] = '\0';
    x = atof(num);
  }
  *shift = sh;
  free(num);
  return x;
}
double binar(char op, double x1, double x2) {
  double res = 0;
  if (op == '+')
    res = x1 + x2;
  else if (op == '-')
    res = x1 - x2;
  else if (op == '*')
    res = x1 * x2;
  else if (op == '/')
    res = x1 / x2;
  else if (op == 'm')
    res = fmod(x1, x2);
  else if (op == '^')
    res = pow(x1, x2);
  return res;
}
double unar(char op, double x) {
  double res = 0;
  if (op == 'c')
    res = cos(x);
  else if (op == 's')
    res = sin(x);
  else if (op == 't')
    res = tan(x);
  else if (op == 'a')
    res = acos(x);
  else if (op == 'i')
    res = asin(x);
  else if (op == 'n')
    res = atan(x);
  else if (op == 'q')
    res = sqrt(x);
  else if (op == 'l')
    res = log(x);
  else if (op == 'g')
    res = log10(x);
  else if (op == '~')
    res = 0 - x;
  return res;
}
double calculate_from_pn(char *pn, int xflag, double x, int *err) {
  stack_d *stack = create_stack_d();
  char *nums = "0123456789.px";
  double x1 = 0, x2 = 0, res = 0;
  for (int i = 0; i < (int)strlen(pn); i++) {
    if (pn[i] == ' ' || pn[i] == '`')
      continue;
    else if (xflag && pn[i] == 'x')
      push_d(stack, x);
    else if (strchr(nums, pn[i]) != NULL)
      push_d(stack, num_to_dbl(pn, &i));
    else {
      if (op_type(pn[i]) == 2)
        x2 = pop_d(stack), x1 = pop_d(stack),
        push_d(stack, binar(pn[i], x1, x2));
      else if (op_type(pn[i]) == 1)
        push_d(stack, unar(pn[i], pop_d(stack)));
      else
        printf("calc_from\n"), *err = 1;
    }
    printf("pn: %s || stk_top: %f\n", pn, peek_d(stack));
  }
  res = pop_d(stack);
  delete_stack_d(&stack);
  return res;
}

double calc_for_tests(const char *eq, int *err) {
  double res = 0;
  int xf = 0;
  char *pn = to_polish_notation(eq, err, &xf);
  if (!(*err)) res = calculate_from_pn(pn, xf, 0.0, err);
  if (pn != NULL) free(pn);
  return res;
}
