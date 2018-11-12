
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "doOperator.h"
#include "tokenStack.h"
#include "lexical.h"

static int op_quit(struct tokenStack *stack);
static int op_print(struct tokenStack *stack);
static int op_dump(struct tokenStack *stack);
static int op_add(struct tokenStack *stack);
static int op_multiply(struct tokenStack *stack);
static int op_divide(struct tokenStack *stack);
static int op_minus(struct tokenStack *stack);
static int op_less(struct tokenStack *stack);
static int op_lessEqual(struct tokenStack *stack);
static int op_mod(struct tokenStack *stack);
static int op_greatEqual(struct tokenStack *stack);
static int op_greater(struct tokenStack *stack);
static int op_equal(struct tokenStack *stack);

static struct operator_struct {
  char *name;
  int (*fn_ptr)(struct tokenStack *);
} ops[] = {
  {"quit", op_quit},
  {"print", op_print},
  {"dump", op_dump},
  {"+", op_add},{"*", op_multiply},{"-", op_minus},{"/", op_divide},{"MOD", op_mod}
  ,{"LE", op_lessEqual},{"GE", op_greatEqual},{"GT", op_greater},{"LT", op_less},{"EQ", op_equal}
  ,{(char *)NULL, (int(*)(struct tokenStack *)) NULL}
};


/* YOU WRITE THIS */
static int popInt(struct tokenStack *s)
{
  return atoi(popTokenStack(s)->symbol);
}

/* YOU WRITE THIS */
static void pushInt(struct tokenStack *s, int v)
{
	struct lexToken *c=allocToken();
	c->kind=LEX_TOKEN_NUMBER;
	stpcpy(c->symbol,gcvt(v));
	pushTokenStack(s,c);
}

int doOperator(struct tokenStack *stack, char *o) 
{
  struct operator_struct *op = ops;
  for(op=ops;op->name != (char *)NULL; op++) {
    if(!strcmp(op->name, o))
      return op->fn_ptr(stack);
  }
  return(-1);
}

/*ARGSUSED*/
static int op_quit(struct tokenStack *stack)
{
  printf("[quit]\n");
  exit(0);
  /*NOTREACHED*/
}

static int op_print(struct tokenStack *stack)
{
  struct lexToken *t = popTokenStack(stack);
  printToken(stdout, t);
  freeToken(t);
  return(0);
}

static int op_dump(struct tokenStack *stack)
{
  struct lexToken *t = popTokenStack(stack);
  dumpToken(stdout, t);
  freeToken(t);
  return(0);
}

static int op_add(struct tokenStack *stack)
{
  int v1, v2;
  v1 = popInt(stack);
  v2 = popInt(stack);
  pushInt(stack, v1+v2);
  return(0);
}
static int op_multiply(struct tokenStack *stack)
{
  int v1, v2;
  v1 = popInt(stack);
  v2 = popInt(stack);
  pushInt(stack, v1*v2);
  return(0);
}
static int op_divide(struct tokenStack *stack)
{
  int v1, v2;
  v1 = popInt(stack);
  v2 = popInt(stack);
  pushInt(stack, v1/v2);
  return(0);
}

static int op_minus(struct tokenStack *stack)
{
  int v1, v2;
  v1 = popInt(stack);
  v2 = popInt(stack);
  pushInt(stack, v1-v2);
  return(0);
}
static int op_greater(struct tokenStack *stack)
{
  int v1, v2;
  v1 = popInt(stack);
  v2 = popInt(stack);
  if(v1>v2) pushInt(stack, 1);
  else pushInt(stack, 0);
  return(0);
}

static int op_less(struct tokenStack *stack)
{
  int v1, v2;
  v1 = popInt(stack);
  v2 = popInt(stack);
  if(v1<v2) pushInt(stack, 1);
  else pushInt(stack, 0);
  return(0);
}
static int op_greatEqual(struct tokenStack *stack)
{
  int v1, v2;
  v1 = popInt(stack);
  v2 = popInt(stack);
  if(v1>=v2) pushInt(stack, 1);
  else pushInt(stack, 0);
  return(0);
}
static int op_lessEqual(struct tokenStack *stack)
{
  int v1, v2;
  v1 = popInt(stack);
  v2 = popInt(stack);
  if(v1<=v2) pushInt(stack, 1);
  else pushInt(stack, 0);
  return(0);
}
static int op_equal(struct tokenStack *stack)
{
  int v1, v2;
  v1 = popInt(stack);
  v2 = popInt(stack);
  if(v1==v2) pushInt(stack, 1);
  else pushInt(stack, 0);
  return(0);
}
static int op_mod(struct tokenStack *stack)
{
  int v1;
  v1 = popInt(stack);
  pushInt(stack, v1);pushInt(stack, v1);
  else pushInt(stack, 0);
  return(0);
}
