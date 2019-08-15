void testall(void){

   fprintf(stderr, "\n--------------------\
------------------------------------\
   \nThe following are results of testing:\
   \ntesting start.\n");

   testingtestmain();
   testingtestinstruction();
   testingtestinstrctlst();
   testingtestFDLTRT();
   testingtestvarnum();
   testingtestvar();
   testingtestnum();
   testingtestdo();
   testingtestset();
   testingtestpolish();
   testingtestop();
   testingto_digit();
   testingto_num();
   testingtesthome();
   testingtestmove();
   testingtestdirection();
   testingtestcolor();

   fprintf(stderr, "testing success.\
   \n-------------------------------\
-------------------------\n");

}

void testingtestmain(void){

   prog *a = (prog*)malloc(SIZE_OF_PROG);
   turtle *b = (turtle*)malloc(SIZE_OF_TURTLE);
   var *c = (var*)malloc(SIZE_OF_VAR);
   SDL_Simplewin sw;

   /*if the first word checked is not '{', return false.*/
   strcpy(a->wrds[0],"a");
   a->testcnt = 0;
   a->cwcnt = 1;
   b->x = WWIDTH/2;
   b->y = WHEIGHT/2;
   b->previousangle = 270;
   c->numofpolivar=0;
   c->numofvar = 0;
   fprintf(stderr, "testingtestmain case 1:");
   assert(testmain(a, b, c, &sw)==0);
   a->testcnt = 0;
   a->cwcnt = 1;
   b->x = WWIDTH/2;
   b->y = WHEIGHT/2;
   b->previousangle = 270;
   c->numofpolivar=0;
   c->numofvar = 0;
   strcpy(a->wrds[0]," ");
   fprintf(stderr, "testingtestmain case 2:");
   assert(testmain(a, b, c, &sw)==0);
   a->testcnt = 0;
   a->cwcnt = 1;
   b->x = WWIDTH/2;
   b->y = WHEIGHT/2;
   b->previousangle = 270;
   c->numofpolivar=0;
   c->numofvar = 0;
   fprintf(stderr, "testingtestmain case 3:");
   strcpy(a->wrds[0],"}");
   assert(testmain(a, b, c, &sw)==0);

   /*if the first word checked is "{"
     and the rest is a <INSTRCTLST>,
      return true.
    */
   strcpy(a->wrds[0],"{");
   strcpy(a->wrds[1],"FD");
   strcpy(a->wrds[2],"30");
   strcpy(a->wrds[3],"}");
   a->testcnt = 0;
   a->cwcnt = 4;
   b->x = WWIDTH/2;
   b->y = WHEIGHT/2;
   b->previousangle = 270;
   c->numofpolivar=0;
   c->numofvar = 0;
   assert(testmain(a, b, c, &sw)==1);

   free(a);
   free(b);
   free(c);

}

void testingtestinstrctlst(void){

   prog *a = (prog*)malloc(SIZE_OF_PROG);
   turtle *b = (turtle*)malloc(SIZE_OF_TURTLE);
   var *c = (var*)malloc(SIZE_OF_VAR);
   SDL_Simplewin sw;

   /*if the word checked is '}', return true. */
   strcpy(a->wrds[0],"}");
   a->testcnt = 0;
   a->cwcnt = 1;
   b->x = WWIDTH/2;
   b->y = WHEIGHT/2;
   b->previousangle = 270;
   c->numofpolivar=0;
   c->numofvar = 0;
   assert(testinstrctlst(a, b, c, &sw)==1);

   /*if the rest part fulfills <INSTRUCTION>+<INSTRCTLST>,
      return true.
    */
   a->testcnt=0;
   strcpy(a->wrds[0],"FD");
   strcpy(a->wrds[1],"30");
   strcpy(a->wrds[2],"}");
   a->testcnt = 0;
   a->cwcnt = 3;
   b->x = WWIDTH/2;
   b->y = WHEIGHT/2;
   b->previousangle = 270;
   c->numofpolivar=0;
   c->numofvar = 0;
   assert(testinstrctlst(a, b, c, &sw)==1);

   /*if the rest part doesn't fulfill
      <INSTRUCTION>+<INSTRCTLST>, nor '{', return true.
    */
   a->testcnt=0;
   strcpy(a->wrds[0],"{");
   strcpy(a->wrds[1],"30");
   strcpy(a->wrds[2],"}");
   a->testcnt = 0;
   a->cwcnt = 1;
   b->x = WWIDTH/2;
   b->y = WHEIGHT/2;
   b->previousangle = 270;
   c->numofpolivar=0;
   c->numofvar = 0;
   fprintf(stderr, "testingtestinstrctlst case 7:");
   assert(testinstrctlst(a, b, c, &sw)==0);

   free(a);
   free(b);
   free(c);

}

void testingtestinstruction(void){

   prog *a = (prog*)malloc(SIZE_OF_PROG);
   turtle *b = (turtle*)malloc(SIZE_OF_TURTLE);
   var *c = (var*)malloc(SIZE_OF_VAR);
   SDL_Simplewin sw;

   /*if the rest part fulfills <FD>, return true.*/
   strcpy(a->wrds[0],"FD");
   strcpy(a->wrds[1],"30");
   strcpy(a->wrds[2],"}");
   a->testcnt = 0;
   a->cwcnt = 3;
   b->x = WWIDTH/2;
   b->y = WHEIGHT/2;
   b->previousangle = 270;
   c->numofpolivar=0;
   c->numofvar = 0;
   assert(testinstruction(a, b, c, &sw)==1);

   /*if the rest part fulfills <LT>, return true.*/
   strcpy(a->wrds[0],"LT");
   strcpy(a->wrds[1],"30");
   strcpy(a->wrds[2],"}");
   a->testcnt = 0;
   a->cwcnt = 3;
   b->x = WWIDTH/2;
   b->y = WHEIGHT/2;
   b->previousangle = 270;
   c->numofpolivar=0;
   c->numofvar = 0;
   assert(testinstruction(a, b, c, &sw)==1);

   /*if the rest part fulfills <RT>, return true.*/
   strcpy(a->wrds[0],"RT");
   strcpy(a->wrds[1],"30");
   strcpy(a->wrds[2],"}");
   a->testcnt = 0;
   a->cwcnt = 3;
   b->x = WWIDTH/2;
   b->y = WHEIGHT/2;
   b->previousangle = 270;
   c->numofpolivar=0;
   c->numofvar = 0;
   assert(testinstruction(a, b, c, &sw)==1);

   /*if the rest part fulfills <DO>, return true.*/

   strcpy(a->wrds[0],"DO");
   strcpy(a->wrds[1],"A");
   strcpy(a->wrds[2],"FROM");
   strcpy(a->wrds[3],"1");
   strcpy(a->wrds[4],"TO");
   strcpy(a->wrds[5],"8");
   strcpy(a->wrds[6],"{");
   strcpy(a->wrds[7],"FD");
   strcpy(a->wrds[8],"30");
   strcpy(a->wrds[9],"}");
   a->testcnt = 0;
   a->cwcnt = 10;
   b->x = WWIDTH/2;
   b->y = WHEIGHT/2;
   b->previousangle = 270;
   c->numofpolivar=0;
   c->numofvar = 0;
   assert(testinstruction(a, b, c, &sw)==1);

   /*if the rest part fulfills <SET>, return true.*/

   strcpy(a->wrds[0],"SET");
   strcpy(a->wrds[1],"C");
   strcpy(a->wrds[2],":=");
   strcpy(a->wrds[3],"A");
   strcpy(a->wrds[4],"1.5");
   strcpy(a->wrds[5],"*");
   strcpy(a->wrds[6],";");
   strcpy(a->wrds[7],"FD");
   strcpy(a->wrds[8],"C");
   strcpy(a->wrds[9],"RT");
   strcpy(a->wrds[10],"62");
   strcpy(a->wrds[11],"}");
   strcpy(a->wrds[12],"}");
   a->testcnt = 0;
   a->cwcnt = 13;
   b->x = WWIDTH/2;
   b->y = WHEIGHT/2;
   b->previousangle = 270;
   c->numofpolivar=0;
   c->numofvar = 0;
   assert(testinstruction(a, b, c, &sw)==1);

   free(a);
   free(b);
   free(c);

}


void testingtestFDLTRT(void){

   prog *a = (prog*)malloc(SIZE_OF_PROG);
   turtle *b = (turtle*)malloc(SIZE_OF_TURTLE);
   var *c = (var*)malloc(SIZE_OF_VAR);
   SDL_Simplewin sw;

   /*if the word checked fulfills <VARNUM>,
     return ture, otherwise return false.
    */
   strcpy(a->wrds[0],"A");
   a->testcnt = 0;
   a->cwcnt = 1;
   assert(testFDLTRT(a, b, c, &sw)==1);
   strcpy(a->wrds[0],"30");
   a->testcnt = 0;
   a->cwcnt = 1;
   assert(testFDLTRT(a, b, c, &sw)==1);

   /*the new angle should be the previousangle + newangle,
     the distance moved should be equal to the distance
     between the previous point and the new one.
    */
   strcpy(a->wrds[0],"FD");
   strcpy(a->wrds[1],"30");
   a->testcnt = 1;
   a->cwcnt = 13;
   b->x = 1;
   b->y = 1;
   b->previousangle = 270;
   assert(testFDLTRT(a, b, c, &sw)==1);
   assert(b->x-(1+1*cos((b->previousangle)*
   M_PI/180))<0.001);
   assert(b->y-(1+1*sin((b->previousangle)*
   M_PI/180))<0.001);

   strcpy(a->wrds[0],"LT");
   strcpy(a->wrds[1],"30");
   a->testcnt = 1;
   a->cwcnt = 13;
   b->x = 1;
   b->y = 1;
   b->previousangle = 270;
   assert(testFDLTRT(a, b, c, &sw)==1);
   assert(b->previousangle-270-30<0.0001);

   strcpy(a->wrds[0],"LT");
   strcpy(a->wrds[1],"30");
   a->testcnt = 1;
   a->cwcnt = 13;
   b->x = 1;
   b->y = 1;
   b->previousangle = 270;
   assert(testFDLTRT(a, b, c, &sw)==1);
   assert(b->previousangle-270+30<0.0001);

   free(a);
   free(b);
   free(c);

}

void testingtestdo(void){

   prog *a = (prog*)malloc(SIZE_OF_PROG);
   turtle *b = (turtle*)malloc(SIZE_OF_TURTLE);
   var *c = (var*)malloc(SIZE_OF_VAR);
   SDL_Simplewin sw;

   /*if the rest part fulfills the structure
    <VAR> "FROM" <VARNUM> "TO"
    <VARNUM> "{" <INSTRCTLST>,
    return true.
    */
   strcpy(a->wrds[0],"A");
   strcpy(a->wrds[1],"FROM");
   strcpy(a->wrds[2],"1");
   strcpy(a->wrds[3],"TO");
   strcpy(a->wrds[4],"8");
   strcpy(a->wrds[5],"{");
   strcpy(a->wrds[6],"FD");
   strcpy(a->wrds[7],"30");
   strcpy(a->wrds[8],"}");
   strcpy(a->wrds[9],"}");
   a->testcnt = 0;
   a->cwcnt = 10;
   assert(testdo(a, b, c, &sw)==1);

   strcpy(a->wrds[0],"4");
   strcpy(a->wrds[1],"FROM");
   strcpy(a->wrds[2],"1");
   strcpy(a->wrds[3],"TO");
   strcpy(a->wrds[4],"8");
   strcpy(a->wrds[5],"{");
   strcpy(a->wrds[6],"FD");
   strcpy(a->wrds[7],"30");
   strcpy(a->wrds[8],"}");
   strcpy(a->wrds[9],"}");
   a->testcnt = 0;
   a->cwcnt = 10;
   fprintf(stderr, "testingtestdo case 23:");
   assert(testdo(a, b, c, &sw)==0);

   free(a);
   free(b);
   free(c);

}

void testingtestset(void){

   prog *a = (prog*)malloc(SIZE_OF_PROG);
   var *c = (var*)malloc(SIZE_OF_VAR);

  /*if the rest part fulfills the structure
    <VAR> ":=" <POLISH>,
    return true.
   */
  strcpy(a->wrds[0],"C");
  strcpy(a->wrds[1],":=");
  strcpy(a->wrds[2],"A");
  strcpy(a->wrds[3],"1.5");
  strcpy(a->wrds[4],"*");
  strcpy(a->wrds[5],";");
  strcpy(a->wrds[6],"FD");
  strcpy(a->wrds[7],"C");
  strcpy(a->wrds[8],"RT");
  strcpy(a->wrds[9],"62");
  strcpy(a->wrds[10],"}");
  strcpy(a->wrds[11],"}");
  a->testcnt = 0;
  a->cwcnt = 12;
  c->numofpolivar=0;
  c->numofvar = 0;
  c['A'].value = 10;
  assert(testset(a, c)==1);
  assert(c['C'].value-15<0.001);

  free(a);
  free(c);

}

void testingtestpolish(void){

   prog *a = (prog*)malloc(SIZE_OF_PROG);
   var *c = (var*)malloc(SIZE_OF_VAR);

    /*if the rest part fulfills the structure
      <OP> <POLISH> or <VARNUM> <POLISH> or ";",
      return true.
     */
   strcpy(a->wrds[0],";");
   a->testcnt = 0;
   a->cwcnt = 1;
   c->numofpolivar=0;
   c->numofvar = 0;
   assert(testpolish(a, c)==1);

   strcpy(a->wrds[0],"A");
   strcpy(a->wrds[1],"1.5");
   strcpy(a->wrds[2],"*");
   strcpy(a->wrds[3],";");
   strcpy(a->wrds[4],"FD");
   strcpy(a->wrds[5],"C");
   strcpy(a->wrds[6],"RT");
   strcpy(a->wrds[7],"62");
   strcpy(a->wrds[8],"}");
   strcpy(a->wrds[9],"}");
   a->testcnt = 0;
   a->cwcnt = 10;
   c->numofpolivar=0;
   c->numofvar = 0;
   assert(testpolish(a, c)==1);

   free(a);
   free(c);

}

void testingtestvarnum(void){

   prog *a = (prog*)malloc(SIZE_OF_PROG);

   /*if the word checked fulfills <VAR> or number,
     return ture, otherwise return false.
    */
   strcpy(a->wrds[0],"A");
   a->testcnt = 0;
   a->cwcnt = 0;
   assert(testvarnum(a)==1);
   strcpy(a->wrds[0],"30");
   a->testcnt = 0;
   a->cwcnt = 0;
   assert(testvarnum(a)==1);

   free(a);

}

void testingtestvar(void){

   prog *a = (prog*)malloc(SIZE_OF_PROG);

  /*if the word checked fulfills <VAR>,
    return ture, otherwise return false.
   */
   strcpy(a->wrds[0],"A");
   a->testcnt = 0;
   a->cwcnt = 1;
   assert(testvar(a)==1);
   a->testcnt = 0;
   a->cwcnt = 1;
   strcpy(a->wrds[0],"30");
   assert(testvar(a)==0);
   a->testcnt = 0;
   a->cwcnt = 1;
   strcpy(a->wrds[0],"AB");
   assert(testvar(a)==0);
   a->testcnt = 0;
   a->cwcnt = 1;
   strcpy(a->wrds[0],"}");
   assert(testvar(a)==0);
   a->testcnt = 0;
   a->cwcnt = 1;
   strcpy(a->wrds[0],"+");
   assert(testvar(a)==0);

   free(a);

}

void testingtestnum(void){

   prog *a = (prog*)malloc(SIZE_OF_PROG);

  /*if the word checked is a number,
    return ture, otherwise return false.
   */
   a->testcnt = 0;
   a->cwcnt = 1;
   strcpy(a->wrds[0],"30");
   assert(testnum(a)==1);
   a->testcnt = 0;
   a->cwcnt = 1;
   strcpy(a->wrds[0],"0");
   assert(testnum(a)==1);
   a->testcnt = 0;
   a->cwcnt = 1;

   free(a);

}

void testingtestop(void){

   prog *a = (prog*)malloc(SIZE_OF_PROG);

   /*if the word checked is "+" or "−" or "*" or "/"
     return true.
    */
   a->testcnt = 0;
   a->cwcnt = 1;
   strcpy(a->wrds[0],"+");
   assert(testop(a)==1);
   strcpy(a->wrds[0],"-");
   assert(testop(a)==1);
   strcpy(a->wrds[0],"*");
   assert(testop(a)==1);
   strcpy(a->wrds[0],"/");
   assert(testop(a)==1);

   strcpy(a->wrds[0],"1");
   assert(testop(a)==0);
   strcpy(a->wrds[0],"A");
   assert(testop(a)==0);
   strcpy(a->wrds[0],".");
   assert(testop(a)==0);
   strcpy(a->wrds[0],"}");
   assert(testop(a)==0);

   free(a);

}

void testingto_digit(void){

   assert(to_digit('0')==0);
   assert(to_digit('1')==1);
   assert(to_digit('2')==2);
   assert(to_digit('3')==3);
   assert(to_digit('4')==4);
   assert(to_digit('5')==5);
   assert(to_digit('6')==6);
   assert(to_digit('7')==7);
   assert(to_digit('8')==8);
   assert(to_digit('9')==9);

}

void testingto_num(void){

   var *c = (var*)malloc(sizeof(var));
   assert(to_num("30", c)-30<0.0001);
   assert(to_num("1.5", c)-1.5<0.0001);

   free(c);

}

void testingtesthome(void){

   turtle *b = (turtle*)malloc(SIZE_OF_TURTLE);

   b->previousangle=100;
   b->x = 200;
   b->y = 200;
   testhome(b);
   assert(b->previousangle - INITIAL_ANGEL < 0.0001);
   assert(b->x - WWIDTH/2 < 0.0001);
   assert(b->y - WHEIGHT/2 < 0.0001);

   free(b);

}

void testingtestmove(void){

   prog *a = (prog*)malloc(SIZE_OF_PROG);
   turtle *b = (turtle*)malloc(SIZE_OF_TURTLE);
   var *c = (var*)malloc(SIZE_OF_VAR);

   strcpy(a->wrds[0],"300");
   strcpy(a->wrds[1],"300");
   a->testcnt = 0;
   b->previousangle = 100;
   b->x = 200;
   b->y = 200;
   assert(testmove(a, b, c)==1);
   assert(b->x - 300 < 0.0001);
   assert(b->y - 300 < 0.0001);

   free(a);
   free(b);
   free(c);

}

void testingtestdirection(void){

   prog *a = (prog*)malloc(SIZE_OF_PROG);
   turtle *b = (turtle*)malloc(SIZE_OF_TURTLE);
   a->testcnt = 0;
   strcpy(a->wrds[0],"UP");
   assert(testdirection(a, b)==1);
   strcpy(a->wrds[0],"DOWN");
   assert(testdirection(a, b)==1);
   strcpy(a->wrds[0],"LEFT");
   assert(testdirection(a, b)==1);
   strcpy(a->wrds[0],"RIGHT");
   assert(testdirection(a, b)==1);

   free(a);
   free(b);

}

void testingtestcolor(void){

   prog *a = (prog*)malloc(SIZE_OF_PROG);
   SDL_Simplewin sw;

   a->testcnt = 0;
   strcpy(a->wrds[0],"RED");
   assert(testsetcolor(a, &sw)==1);
   strcpy(a->wrds[0],"BLUE");
   assert(testsetcolor(a, &sw)==1);
   strcpy(a->wrds[0],"GREEN");
   assert(testsetcolor(a, &sw)==1);
   strcpy(a->wrds[0],"YELLOW");
   assert(testsetcolor(a, &sw)==1);
   strcpy(a->wrds[0],"WHITE");
   assert(testsetcolor(a, &sw)==1);

   free(a);

}
