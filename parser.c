/*main program*/

int main(int argc, char** argv)
{

   FILE *fp;
   prog *p = (prog*)malloc(SIZE_OF_PROG);

   fp = fopen(argv[1], "r");
   if(!fp){
      fprintf(stderr, "Can't open %s\n", argv[1]);
      exit(2);
   }

   if(argc != 2){
      fprintf(stderr, "Error in input.\n");
   }

   p->cwcnt = 0;
   p->testcnt = 0;

   /*scan the words from the turtle program
     and assign each into an array called wrds
    */
   while(fscanf(fp, "%s", p->wrds[p->cwcnt])==1){
      p->cwcnt++;
   };
   fclose(fp);
   /*testing starts*/
   if (testmain(p)==1) {
      testbracket(p);
      fprintf(stderr, "\n%s:Parse OK.\n", argv[1]);
      free(p);
   }

   else{
      free(p);
   }

   testall();

   exit(2);

}
/*the first test function tests if the first word
  of the turtle program is a bracket and if it is,
  check if the amount of brackets matched, and if so,
  checks if the rest of the program is an instructionlist.
 */
int testmain(prog* p){

   if(strcmp(p->wrds[0],"{")==0){
      p->testcnt++;
    /*  testbracket(p);*/
      return testinstrctlst(p);
   }

   else{
     fprintf(stderr, "Error in testmain: expect '{'\
(word %d)\n", p->testcnt);
     return 0;
   }

}
/*this function tests if the number of brackets match,
  and if not, prints the error and exit.
 */
void testbracket(prog *p){

   int n;
   int cnt = 0;

   for(n=0; n<=p->cwcnt; n++){
      if (strcmp(p->wrds[n],"{")==0){
         cnt++;
      }
      if (strcmp(p->wrds[n],"}")==0){
         cnt--;
      }
   }

   if(cnt>0){
      fprintf(stderr, "Error: Lack %d }.\n", cnt);
      exit(2);
    }

   if(cnt<0){
      fprintf(stderr, "Error: %d Extraneous }.\n", -cnt);
      exit(2);
   }

}
/*this function tests if the rest of the program
  fulfills the sturcture of an instructionlist
 */
int testinstrctlst(prog* p){

   if(strcmp((p->wrds[p->testcnt]), "}")==0){
      return 1;
   }

   else if(testinstruction(p)==1){
      p->testcnt++;
      return testinstrctlst(p);
   }

   else{
      fprintf(stderr, "Error in instructionlist.\
(word %d)\n", p->testcnt+1);
      return 0;
   }

}
/*this function tests if the rest of the program
  fulfills the sturcture of an instruction by comparing
  the current test word with key words such as
  'FD' and 'DO', if matched, send prog to the next
  test function.
 */
int testinstruction(prog* p){

   if(strcmp(p->wrds[p->testcnt], "FD")==0||
   strcmp(p->wrds[p->testcnt], "LT" )==0||
   strcmp(p->wrds[p->testcnt], "RT")==0){
      p->testcnt++;
      if(testFDLTRT(p)==1){
         return 1;
      }
      else{
         fprintf(stderr, "Error in instruction(FDLTRT).\
(word %d)\n", p->testcnt);
         return 0;
      }
   }

   else if(strcmp(p->wrds[p->testcnt], "DO")==0){
      p->testcnt++;
      if(testdo(p)==1){
         return 1;
      }
      else{
         fprintf(stderr, "Error in instruction(DO).\
(word %d)\n", p->testcnt);
         return 0;
      }
   }

  else if(strcmp(p->wrds[p->testcnt], "SET")==0){
     p->testcnt++;
     if(testset(p)==1){
        return 1;
     }
     else{
        fprintf(stderr, "Error in instruction(SET).\
(word %d)\n", p->testcnt);
        return 0;
     }
  }

  else{
     fprintf(stderr, "Error in instruction.\
(word %d)\n", p->testcnt);
     return 0;
   }

}
/*this function tests if the rest of the program
  fulfills the sturcture of FD/LT/RT.
 */
int testFDLTRT(prog* p){

   if((p->wrds[p->testcnt] == NULL) ||
   (testvarnum(p))!=1){
     fprintf(stderr, "Error in FDLTRT.\
(word %d)\n", p->testcnt);
     return 0;
  }

   else{return 1;}

}
/*this function tests if current word is a variable
  or number, and return 1 if it is.
 */
int testvarnum(prog* p){

   if(testnum(p)==1){return 1;}

   else if(testvar(p)==1){return 1;}

   else{
      return 0;
   }

}
/*this function tests if current word is a variable
  and return 1 if it is.
 */
int testvar(prog* p){

   int n = strlen(p->wrds[p->testcnt]);
   if(n>1){return 0;}

   else if(p->wrds[p->testcnt][0]<'A'||
    p->wrds[p->testcnt][0]>'Z'){return 0;}

   else{return 1;}

}
/*this function tests if current word is a number
  and return 1 if it is.
 */
int testnum(prog* p){

   int n = strlen(p->wrds[p->testcnt])-1;
   int t;

   for(t=0; t<n; t++){
      if((p->wrds[p->testcnt][t]!='.')&&
       (p->wrds[p->testcnt][t]<='0'||
       p->wrds[p->testcnt][t]>='9')){
      return 0;
      }
   }

   return 1;

}
/*this function tests if the rest of the program
  fulfills the sturcture of DO, that is,
  <VAR> "FROM" <VARNUM> "TO"<VARNUM> "{" <INSTRCTLST>
 */
int testdo(prog* p){

   if(testvar(p)==1){
      p->testcnt++;

      if(strcmp(p->wrds[p->testcnt], "FROM" )==0){
         p->testcnt++;

         if(testvarnum(p)==1){
            p->testcnt++;

            if(strcmp(p->wrds[p->testcnt], "TO" )==0){
               p->testcnt++;

               if(testvarnum(p)==1){
                  p->testcnt++;

                  if(strcmp(p->wrds[p->testcnt],
                     "{" )==0){
                     p->testcnt++;
                     return testinstrctlst(p);
                  }

                  else{
                     fprintf(stderr,
                       "Error in DO: expect '{'.\
(word %d)\n", p->testcnt);
                     return 0;
                  }
               }

               else{
                  fprintf(stderr,
                    "Error in DO: expect var or num.\
(word %d)\n", p->testcnt);
                  return 0;
               }
            }

            else{
               fprintf(stderr,
                  "Error in DO: expect 'TO'.\
(word %d)\n", p->testcnt);
               return 0;
            }
         }

         else{
            fprintf(stderr,
               "Error in DO: expect var or num.\
(word %d)\n", p->testcnt);
            return 0;
         }
      }

      else{
         fprintf(stderr,
            "Error in DO: expect 'FROM'\
(word %d)\n", p->testcnt);
         return 0;
      }
   }

   else{
      fprintf(stderr,
         "Error in DO: expect variable.\
(word %d)\n", p->testcnt);
      return 0;
   }

}
/*this function tests if the rest of the program
  fulfills the sturcture of SET.
*/
int testset(prog* p){

   if(testvar(p)==1){
      p->testcnt++;

      if(strcmp(p->wrds[p->testcnt], ":=")==0) {
         p->testcnt++;

         if(testpolish(p)==1){
            return 1;
         }

         else{
           fprintf(stderr,
              "Error in SET: expect polish.\
(word %d)\n", p->testcnt);
           return 0;
         }
      }

      else{
         fprintf(stderr, "Error in SET: expect':='.\
(word %d)\n", p->testcnt);
         return 0;
      }
   }

   else{
      fprintf(stderr, "Error in SET: expect variable.\
(word %d)\n", p->testcnt);
      return 0;
   }

}
/*this function tests if the rest of the program
  fulfills the sturcture of POLISH
 */
int testpolish(prog* p){

   if(strcmp(p->wrds[p->testcnt], ";")==0){
      return 1;
   }

   else if((testop(p)==1)){
      p->testcnt++;
      return testpolish(p);
   }

   else if((testvarnum(p)==1)){
      p->testcnt++;
      return testpolish(p);
   }

   else{
      fprintf(stderr, "Error in POLISH.\
(word %d)\n", p->testcnt);
      return 0;
   }

}
/*this function tests if the word tested is an operator*/
int testop(prog* p){

   if(strcmp(p->wrds[p->testcnt], "+")==0||
   strcmp(p->wrds[p->testcnt], "-" )==0||
   strcmp(p->wrds[p->testcnt], "*" )==0||
   strcmp(p->wrds[p->testcnt], "/")==0){
      return 1;
   }

   else{return 0;}

}
/*input the character of a number, this function
  returns a real number, which is used for to_num.
 */
int to_digit(char c){

   switch(c){
      case '0':
         return 0;
      case '1':
         return 1;
      case '2':
         return 2;
      case '3':
         return 3;
      case '4':
         return 4;
      case '5':
         return 5;
      case '6':
         return 6;
      case '7':
         return 7;
      case '8':
         return 8;
      case '9':
         return 9;
      default:return 0;
   }

}
/*input the string of an interger or double,
  this function returns the real number.
 */
double to_num(char* c){

   int stringlength = (int)strlen(c);
   int floatpoint = 0;
   double integersum = 0;
   double doublesum = 0;
   int n;

   for(n=0; n<stringlength; n++){
      if(c[n] == '.'){
         floatpoint = n;
      }
   }

   if(floatpoint != 0){
      for(n=0; n<stringlength-floatpoint; n++){
         integersum = integersum + to_digit(c[n])*
         (int)pow(10, (floatpoint-n-1));
      }
      for(n=floatpoint+1; n<stringlength; n++){
         doublesum = doublesum + to_digit(c[n])*
         (double)pow(10, (n-stringlength));
      }
      return (double)(integersum+doublesum);
   }

   else{
      for(n=0; n<stringlength; n++){
      integersum = integersum + to_digit(c[n])*
      (int)pow(10, (stringlength-n-1));
      }
   return(double)(integersum);
   }

}
