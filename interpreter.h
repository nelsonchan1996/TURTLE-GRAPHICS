#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <SDL.h>

/* Font stuff */
typedef unsigned short fntrow;

#define FNTWIDTH (sizeof(fntrow)*8)
#define FNTHEIGHT 18
#define FNTCHARS 96
#define FNT1STCHAR 32
#define MAXNUMTOKENS 100
#define MAXTOKENSIZE 100
#define WWIDTH 800
#define WHEIGHT 600
#define SDL_8BITCOLOUR 256
#ifndef M_PI
#define M_PI 3.14159265358979323846
#define SIZE_OF_PROG 10000
#define SIZE_OF_TURTLE 10000
#define SIZE_OF_VAR 10000
#define INITIAL_ANGEL 270
#define COLAR_RED 84
#define COLAR_YELLOW 135
#define COLAR_BLUE 159

typedef struct prog{
  char wrds[MAXNUMTOKENS][MAXTOKENSIZE];
  int cwcnt;
  int testcnt;
}prog;

typedef struct turtle{
  double x;
  double y;
  double previousangle;
  int start;
  int end;
}turtle;

typedef struct variable{
   double value;
   int cwvariable;
   int cwvariable2;
   double cwpolivar;
   int numofpolivar;
   int numofvar;
   char cwop;
}var;

/* All info required for windows/renderer & event loop */
struct SDL_Simplewin {
   SDL_bool finished;
   SDL_Window *win;
   SDL_Renderer *renderer;
   SDL_Texture *display;
};
typedef struct SDL_Simplewin SDL_Simplewin;

int testmain(prog* p, turtle* t, var* v,
   SDL_Simplewin *sw);
int testinstruction(prog* p, turtle* t, var* v,
   SDL_Simplewin *sw);
int testinstrctlst(prog* p, turtle* t, var* v,
   SDL_Simplewin *sw);
int testFDLTRT(prog* p, turtle* t, var* v,
   SDL_Simplewin *sw);
int testvarnum(prog *p);
int testvar(prog *p);
int testnum(prog *p);
void testbracket(prog *p);
int testdo(prog* p, turtle* t, var* v,
   SDL_Simplewin *sw);
int testset(prog* p, var* v);
int testpolish(prog* p, var* v);
int testop(prog* p);
int to_digit(char c);
double to_num(char* c, var* v);

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

void Neill_SDL_Init(SDL_Simplewin *sw);
void Neill_SDL_Events(SDL_Simplewin *sw);
void Neill_SDL_SetDrawColour(SDL_Simplewin *sw,
   Uint8 r, Uint8 g, Uint8 b);
void Neill_SDL_RenderFillCircle(SDL_Renderer *rend,
   int cx, int cy, int r);
void Neill_SDL_RenderDrawCircle(SDL_Renderer *rend,
   int cx, int cy, int r);
void Neill_SDL_DrawChar(SDL_Simplewin *sw,
   fntrow fontdata[FNTCHARS][FNTHEIGHT],
   unsigned char chr, int ox, int oy);
void Neill_SDL_DrawString(SDL_Simplewin *sw,
   fntrow fontdata[FNTCHARS][FNTHEIGHT],
   char *str, int ox, int oy);
void Neill_SDL_ReadFont(
  fntrow fontdata[FNTCHARS][FNTHEIGHT],char *fname);
void Neill_SDL_UpdateScreen(SDL_Simplewin *sw);

#endif
