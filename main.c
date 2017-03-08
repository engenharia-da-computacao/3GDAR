#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "libs/utils.c"

void verificarArquivos(){
    verificaArquivo(BD_DOADORES);
    verificaArquivo(BD_ORGS);
    verificaArquivo(BD_REQUERIMENTOS);
}

main(){
    verificaArquivos();
	configConsole();
    goMenuPrincipal();
}
