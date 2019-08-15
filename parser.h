#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#define MAXNUMTOKENS 100
#define MAXTOKENSIZE 100
#define SIZE_OF_PROG 10000

typedef struct prog{
  char wrds[MAXNUMTOKENS][MAXTOKENSIZE];
  int cwcnt;
  int testcnt;
}prog;

int testmain(prog* p);
int testinstruction(prog* p);
int testinstrctlst(prog* p);
int testFDLTRT(prog* p);
int testvarnum(prog *p);
int testvar(prog *p);
int testnum(prog *p);
void testbracket(prog *p);
int testdo(prog* p);
int testset(prog* p);
int testpolish(prog* p);
int testop(prog* p);
int to_digit(char c);
double to_num(char* c);

void testall(void);
void testingtestmain(void);
void testingtestinstrctlst(void);
void testingtestinstruction(void);
void testingtestFDLTRT(void);
void testingtestvarnum(void);
void testingtestvar(void);
void testingtestnum(void);
void testingtestdo(void);
void testingtestset(void);
void testingtestpolish(void);
void testingtestop(void);
void testingto_digit(void);
void testingto_num(void);
