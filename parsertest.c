
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

   fprintf(stderr, "testing success.\
   \n-------------------------------\
-------------------------\n");

}

void testingtestmain(void){

   prog *a = (prog*)malloc(sizeof(prog));

   /*if the first word checked is not '{', return false.*/
   strcpy(a->wrds[0],"a");
   a->testcnt = 0;
   a->cwcnt = 1;
   fprintf(stderr, "testingtestmain case 1:");
   assert(testmain(a)==0);
   a->testcnt = 0;
   a->cwcnt = 1;
   strcpy(a->wrds[0]," ");
   fprintf(stderr, "testingtestmain case 2:");
   assert(testmain(a)==0);
   a->testcnt = 0;
   a->cwcnt = 1;
   fprintf(stderr, "testingtestmain case 3:");
   strcpy(a->wrds[0],"}");
   assert(testmain(a)==0);

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
   assert(testmain(a)==1);

   free(a);

}

void testingtestinstrctlst(void){

   prog *a = (prog*)malloc(sizeof(prog));
   /*if the word checked is '}', return true. */
   strcpy(a->wrds[0],"}");
   a->testcnt = 0;
   a->cwcnt = 1;
   assert(testinstrctlst(a)==1);

   /*if the rest part fulfills <INSTRUCTION>+<INSTRCTLST>,
      return true.
    */
   a->testcnt=0;
   strcpy(a->wrds[0],"FD");
   strcpy(a->wrds[1],"30");
   strcpy(a->wrds[2],"}");
   a->testcnt = 0;
   a->cwcnt = 3;
   assert(testinstrctlst(a)==1);

   /*if the rest part doesn't fulfill
      <INSTRUCTION>+<INSTRCTLST>, nor '{', return true.
    */
   a->testcnt=0;
   strcpy(a->wrds[0],"{");
   a->testcnt = 0;
   a->cwcnt = 1;
   fprintf(stderr, "testingtestinstrctlst case 7:");
   assert(testinstrctlst(a)==0);

   free(a);

}

void testingtestinstruction(void){

   prog *a = (prog*)malloc(SIZE_OF_PROG);

   /*if the rest part fulfills <FD>, return true.*/
   strcpy(a->wrds[0],"FD");
   strcpy(a->wrds[1],"30");
   strcpy(a->wrds[2],"}");
   a->testcnt = 0;
   a->cwcnt = 3;
   assert(testinstruction(a)==1);

   /*if the rest part fulfills <LT>, return true.*/
   strcpy(a->wrds[0],"LT");
   strcpy(a->wrds[1],"30");
   strcpy(a->wrds[2],"}");
   a->testcnt = 0;
   a->cwcnt = 3;
   assert(testinstruction(a)==1);

   /*if the rest part fulfills <RT>, return true.*/
   strcpy(a->wrds[0],"RT");
   strcpy(a->wrds[1],"30");
   strcpy(a->wrds[2],"}");
   a->testcnt = 0;
   a->cwcnt = 3;
   assert(testinstruction(a)==1);

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
   assert(testinstruction(a)==1);

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
   assert(testinstruction(a)==1);

   strcpy(a->wrds[0],"DO");
   strcpy(a->wrds[1],"A");
   strcpy(a->wrds[2],"FROM");
   strcpy(a->wrds[3],"1");
   strcpy(a->wrds[4],"TO");
   strcpy(a->wrds[5],"8");
   strcpy(a->wrds[6],"FD");
   strcpy(a->wrds[7],"30");
   a->testcnt = 0;
   a->cwcnt = 9;
   fprintf(stderr, "testingtestinstrctlst case 13:");
   assert(testinstruction(a)==0);

   free(a);

}

void testingtestFDLTRT(void){

   prog *a = (prog*)malloc(SIZE_OF_PROG);

   /*if the word checked fulfills <VARNUM>,
     return ture, otherwise return false.
    */
   strcpy(a->wrds[0],"A");
   a->testcnt = 0;
   a->cwcnt = 1;
   assert(testFDLTRT(a)==1);
   strcpy(a->wrds[0],"30");
   a->testcnt = 0;
   a->cwcnt = 1;
   assert(testFDLTRT(a)==1);
   strcpy(a->wrds[0],"AB");
   a->testcnt = 0;
   a->cwcnt = 1;
   fprintf(stderr, "testingtestFDLTRT case 16:");
   assert(testFDLTRT(a)==0);

   free(a);

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

   free(a);

}

void testingtestdo(void){

   prog *a = (prog*)malloc(SIZE_OF_PROG);

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
   assert(testdo(a)==1);

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
   assert(testdo(a)==0);

   free(a);

}

void testingtestset(void){

   prog *a = (prog*)malloc(SIZE_OF_PROG);

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
  assert(testset(a)==1);

  strcpy(a->wrds[0],"4");
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
  fprintf(stderr, "testingtestset case 25:");
  assert(testset(a)==0);

  strcpy(a->wrds[0],"4");
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
  a->testcnt = 0;
  a->cwcnt = 11;
  fprintf(stderr, "testingtestset case 26:");
  assert(testset(a)==0);

  free(a);

}

void testingtestpolish(void){

   prog *a = (prog*)malloc(SIZE_OF_PROG);

    /*if the rest part fulfills the structure
      <OP> <POLISH> or <VARNUM> <POLISH> or ";",
      return true.
     */
   strcpy(a->wrds[0],";");
   a->testcnt = 0;
   a->cwcnt = 1;
   assert(testpolish(a)==1);

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
   assert(testpolish(a)==1);

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

   assert(to_num("30")-30<0.0001);
   assert(to_num("1.5")-1.5<0.0001);

}
