/*main program*/

int main(int argc, char** argv)
{

   FILE *fp;
   prog *p = (prog*)malloc(SIZE_OF_PROG);
   turtle *t = (turtle*)malloc(SIZE_OF_TURTLE);
   var *v = (var*)malloc(SIZE_OF_VAR);

   SDL_Simplewin sw;
   Neill_SDL_Init(&sw);

   fp = fopen(argv[1], "r");
      if(!fp){
         fprintf(stderr, "Can't open %s\n", argv[1]);
         exit(1);
   }
   if(argc != 2){
      fprintf(stderr, "Error in input.\n");
   }

   p->cwcnt = 0;
   p->testcnt = 0;
   t->x = WWIDTH/2;
   t->y = WHEIGHT/2;
   t->previousangle = INITIAL_ANGEL;
   v->numofpolivar=0;
   v->numofvar = 0;
   /*scan the words from the turtle program
     and assign each into an array called wrds
    */
   while(fscanf(fp, "%s", p->wrds[p->cwcnt])==1){
     p->cwcnt++;
   };
   fclose(fp);
   /*testing starts*/
   if (testmain(p, t, v, &sw)==1) {
      SDL_Delay(3000);
      SDL_Quit();
      atexit(SDL_Quit);
      fprintf(stderr, "\n%s:Parse OK.\n", argv[1]);
      testall();
   }

   free(p);
   free(t);
   free(v);

   exit(2);

}
/*the first test function tests if the first word
  of the turtle program is a bracket and if it is,
  check if the amount of brackets matched, and if so,
  checks if the rest of the program is an instructionlist.
 */
int testmain(prog* p, turtle* t, var* v,
   SDL_Simplewin *sw){

   if(strcmp(p->wrds[0],"{")==0){
      p->testcnt++;
      testbracket(p);
      return testinstrctlst(p, t, v, sw);
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
int testinstrctlst(prog* p, turtle* t, var* v,
   SDL_Simplewin *sw){

   if(strcmp((p->wrds[p->testcnt]), "}")==0){
      return 1;
   }

   else if(testinstruction(p, t, v, sw)==1){
      p->testcnt++;
      return testinstrctlst(p, t, v, sw);
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
int testinstruction(prog* p, turtle* t, var* v,
   SDL_Simplewin *sw){

   if(strcmp(p->wrds[p->testcnt], "FD")==0||
   strcmp(p->wrds[p->testcnt], "LT" )==0||
   strcmp(p->wrds[p->testcnt], "RT")==0){
      p->testcnt++;
      if(testFDLTRT(p, t, v, sw)==1){
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
      if(testdo(p, t, v, sw)==1){
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
      if(testset(p, v)==1){
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
  also, it calculates the distance to be moved
  and the angles by the previousangle, previous
  position and the new number scanned.
 */
int testFDLTRT(prog* p, turtle* t, var* v,
   SDL_Simplewin *sw){

   int a = p->wrds[p->testcnt][0];
   int b = v[a].value;

   if((p->wrds[p->testcnt] == NULL) ||
    (testvarnum(p))!=1){
      fprintf(stderr, "Error in FDLTRT.\n");
      return 0;
   }

   else{
      double FD_distance = to_num(p->wrds[p->testcnt], v);

      if(strcmp(p->wrds[p->testcnt-1], "LT")==0){

         if(testnum(p)==1){
         t->previousangle=(t->previousangle)
          -to_num(p->wrds[p->testcnt], v);
         }

         else{
         t->previousangle=(t->previousangle)-b;
         }
      }

      else if(strcmp(p->wrds[p->testcnt-1], "RT")==0){

         if(testnum(p)==1){
         t->previousangle=(t->previousangle)
         +to_num(p->wrds[p->testcnt], v);
         }

         else{
         t->previousangle=(t->previousangle)+b;
         }
      }

      else if(strcmp(p->wrds[p->testcnt-1], "FD")==0){
         turtle* temp = (turtle*)malloc(sizeof(turtle));
         temp->x = t->x;
         temp->y = t->y;
         (t->x) = (t->x) + (FD_distance *
            cos((t->previousangle)*M_PI/180));
         (t->y) = (t->y) + (FD_distance *
            sin((t->previousangle)*M_PI/180));
         Neill_SDL_SetDrawColour(sw, COLAR_RED,
            COLAR_YELLOW, COLAR_BLUE);
         SDL_RenderDrawLine(sw->renderer, temp->x,
            temp->y, t->x, t->y);
         Neill_SDL_UpdateScreen(sw);
         Neill_SDL_Events(sw);
         SDL_Delay(20);
      }
      return 1;
   }

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
    p->wrds[p->testcnt][0]>'Z'){
      return 0;
   }

   else{return 1;}

}
/*this function tests if current word is a number
  and return 1 if it is.
 */
int testnum(prog* p){

   int n = strlen(p->wrds[p->testcnt])-2;
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
  and if so, stores the variable's value into the
  structure var, copy the prog to temp and start
  the loop util the variable reach its max value.
 */
int testdo(prog* p, turtle* t, var* v, SDL_Simplewin *sw){
   int n;
   prog* temp = (prog*)malloc(sizeof(prog));
   turtle* temp2 = (turtle*)malloc(sizeof(turtle));
   temp->cwcnt = p->cwcnt;
   temp->testcnt = p->testcnt;

   for(n= 0; n<=(temp->cwcnt); n++){
      strcpy(temp->wrds[n], p->wrds[n]);
   }

   temp2->x = t->x;
   temp2->y = t->y;
   temp2->previousangle = t->previousangle;
   temp2->start = t->start;
   temp2->end = t->end;

   if(testvar(p)==1){
      v->numofvar++;
      v[v->numofvar].cwvariable = p->wrds[p->testcnt][0];
      p->testcnt++;

      if(strcmp(p->wrds[p->testcnt], "FROM" )==0){
         p->testcnt++;

         if(testvarnum(p)==1){

            if(testnum(p)==1){
            t->start = to_num(p->wrds[p->testcnt], v);
            }

            else{
            int temp = p->wrds[p->testcnt][0];
            t->start = v[temp].value;
            }
            p->testcnt++;

            if(strcmp(p->wrds[p->testcnt], "TO" )==0){
               p->testcnt++;

               if(testvarnum(p)==1){

                  if(testnum(p)==1){
                     t->end =
                      to_num(p->wrds[p->testcnt], v);
                     p->testcnt++;
                  }

                  else{
                     int temp = p->wrds[p->testcnt][0];
                     t->start = v[temp].value;
                  }

                  if(strcmp(p->wrds[p->testcnt],
                     "{" )==0){
                     p->testcnt++;

                     while (t->start<t->end) {
                        v[v[v->numofvar].cwvariable].value
                         = t->start;
                        temp->cwcnt = p->cwcnt;
                        temp->testcnt = p->testcnt;

                        if(testinstrctlst(temp, temp2,
                           v, sw)==1){
                        t->start++;
                        }
                     }
                     v->numofvar--;
                     t->previousangle =
                      temp2->previousangle;
                     t->x = temp2->x;
                     t->y = temp2->y;

                     return testinstrctlst(p, t, v, sw);
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
  fulfills the sturcture of SET, and if so
  set the value of the variable and store it
  in the sturcture var.
*/
int testset(prog* p, var* v){

   if(testvar(p)==1){
      v->cwvariable2 = p->wrds[p->testcnt][0];
      p->testcnt++;

      if(strcmp(p->wrds[p->testcnt], ":=")==0) {
         p->testcnt++;

         if(testpolish(p, v)==1){
            return 1;
         }

         else{
           fprintf(stderr,
              "Error in SET: expect polish.\
(word %d)\n", p->testcnt);
           exit(2);
         }
      }

      else{
         fprintf(stderr, "Error in SET: expect':='.\
(word %d)\n", p->testcnt);
         exit(2);
      }
   }

   else{
      fprintf(stderr, "Error in SET: expect variable.\
(word %d)\n", p->testcnt);
      exit(2);
   }

}
/*this function tests if the rest of the program
  fulfills the sturcture of POLISH, and if so,
  calculate the value of variable using the variables
  stored in the sturcture called polivar.
 */
int testpolish(prog* p, var* v){

   if(strcmp(p->wrds[p->testcnt], ";")==0){

      if(v[0].cwop=='+'){
      v[v->cwvariable2].value = v[0].cwpolivar +
       v[1].cwpolivar;
      }

      else if(v[0].cwop=='-'){
      v[v->cwvariable2].value = v[0].cwpolivar -
       v[1].cwpolivar;
      }

      else if(v[0].cwop=='*'){
      v[v->cwvariable2].value = v[0].cwpolivar *
       v[1].cwpolivar;
      }

      else if(v[0].cwop=='/'){
      v[v->cwvariable2].value = v[0].cwpolivar /
       v[1].cwpolivar;
      }
      v->numofpolivar = 0;
      return 1;
   }

   else if((testop(p)==1)){
      v[0].cwop = p->wrds[p->testcnt][0];
      p->testcnt++;
      return testpolish(p, v);
   }

   else if((testvarnum(p)==1)){

      if(testvar(p)==1){
         int temp = p->wrds[p->testcnt][0];
         v[v->numofpolivar].cwpolivar = v[temp].value;
         v->numofpolivar++;
      }

      else{
         v[1].cwpolivar = to_num(p->wrds[p->testcnt], v);
         v->numofpolivar++;
      }
      p->testcnt++;

      if(testpolish(p, v)==1){
         return 1;
      }

      else{
         fprintf(stderr, "Error in POLISH: expecting varnum.\n");
         exit(2);
      }
    }

   else{
      fprintf(stderr, "Error in POLISH.\n");
      exit(2);
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
   else{
      return 0;
   }

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
double to_num(char* c, var* v){

   if(c[0]>='A'&&c[0]<='Z'){
      int a = (int)c[0];
      return v[a].value;
   }

   else{
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
            integersum = integersum +
             to_digit(c[n])*(int)pow(10, (floatpoint-n-1));
         }
         for(n=floatpoint+1; n<stringlength; n++){
            doublesum = doublesum +
             to_digit(c[n])*
             (double)pow(10, (n-stringlength));
         }
         return (double)(integersum+doublesum);
      }

   else{
      for(n=0; n<stringlength; n++){
         integersum = integersum +
          to_digit(c[n])*
          (int)pow(10, (stringlength-n-1));
      }
      return(double)(integersum);
   }
   }

}
