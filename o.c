/* Компилятор языка О (о.с) */
#include <string.h>
#include <stdio.h>

#include "text.h"
#include "scan.h"
#include "ovm.h"
#include "scan.h"
#include "gen.h"
#include "location.h"
#include "pars.h"
#include "error.h"


void Init(void) {
    puts("\r после ");
    ResetText();
    if(ResetError)
        Error(Message);
    InitScan();
    InitGen();
}

void Done(void) {
    CloseText();
}

int main(int argc, char *argv[]) {
    puts("\r Компилятор языка О");
    if(argc <= 1)
        Path = NULL;
    else
        Path = argv[1];
    Init(); /* Инициализация */
    Compile(); /* Компиляция */
    Run(); /* Выполнение */
    Done(); /* Завершение */
    return 0;
}