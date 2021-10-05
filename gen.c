#include <limits.h>
#include <stdlib.h>
#include <string.h>

#include "scan.h"
#include "table.h"
#include "ovm.h"
#include "error.h"

int PC;

void InitGen(void) {
   PC = 0;
}

void Gen(int Cmd) {
   if( PC < MEMSIZE )
      M[PC++] = Cmd;
   else
      Error("¥¤®áâ â®ç­® ¯ ¬ïâ¨ ¤«ï ª®¤ ");
}

void Fixup(int A) {
   while( A > 0 ) {
      int temp = M[A-2];
      M[A-2] = PC;
      A = temp;
   }
}

void GenAbs(void) {
   Gen(cmDup);
   Gen(0);
   Gen(PC+3);
   Gen(cmIfGE);
   Gen(cmNeg);
}

void GenMin(void) {
   Gen(INT_MAX);
   Gen(cmNeg);
   Gen(1);
   Gen(cmSub);
}

void GenOdd(void) {
   Gen(2);
   Gen(cmMod);
   Gen(1);
   Gen(0); /* €¤à¥á ¯¥à¥å®¤  ¢¯¥à¥¤ */
   Gen(cmIfNE);
}

void GenConst(int C) {
   Gen(abs(C));
   if ( C < 0 )
      Gen(cmNeg);
}

void GenComp(tLex Lex) {
   Gen(0); /* €¤à¥á ¯¥à¥å®¤  ¢¯¥à¥¤ */
   switch( Lex ) {
   case lexEQ : Gen(cmIfNE); break;
   case lexNE : Gen(cmIfEQ); break;
   case lexLE : Gen(cmIfGT); break;
   case lexLT : Gen(cmIfGE); break;
   case lexGE : Gen(cmIfLT); break;
   case lexGT : Gen(cmIfLE); break;
   }
}

void GenAddr(tObj* X) {
   Gen(X->Val);   /*‚ â¥ªãéãî ïç¥©ªã  ¤à¥á ¯à¥¤ë¤ãé¥© + 2*/
   X->Val = PC+1; /*€¤à¥á+2 = PC+1*/
}

void AllocateVariables(void) {
   char msg[256];
   tObj* VRef;        /*‘áë«ª  ­  ¯¥à¥¬¥­­ãî ¢ â ¡«¨æ¥ ¨¬¥­*/
   VRef = FirstVar(); /* ©â¨ ¯¥à¢ãî ¯¥à¥¬¥­­ãî            */
   while( VRef != NULL ) {
      if ( VRef->Val == 0 ) {
         strcpy(msg, "¥à¥¬¥­­ ï ");
         strcat(msg, VRef->Name);
         strcat(msg,  " ­¥ ¨á¯®«ì§ã¥âáï");
         Warning(msg);
         }
      else if( PC < MEMSIZE ) {
         Fixup(VRef->Val); /*€¤à¥á­ ï ¯à¨¢ï§ª  ¯¥à¥¬¥­­®©*/
         PC++;
         }
      else
         Error("¥¤®áâ â®ç­® ¯ ¬ïâ¨ ¤«ï ¯¥à¥¬¥­­ëå");
      VRef = NextVar();       /* ©â¨ á«¥¤ãîéãî ¯¥à¥¬¥­­ãî*/
   }
}
