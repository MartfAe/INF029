
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "AnaMutim20241160001.h"

int quantidadeDeDias(int mes, int ano){
  switch(mes){
    case 4: case 6: case 9: case 11: return 30;
    case 2: return anoBissexto(ano) ? 29 : 28;
    default: return 31;
  }
}

char normalizarAcento(char c) {
    unsigned char uc = (unsigned char)c;
    switch (uc) {
        case 'á': case 'à': case 'â': case 'ã': case 'Á': case 'À': case 'Â': case 'Ã': return 'a';
        case 'é': case 'è': case 'ê': case 'É': case 'È': case 'Ê': return 'e';
        case 'í': case 'ì': case 'î': case 'Í': case 'Ì': case 'Î': return 'i';
        case 'ó': case 'ò': case 'ô': case 'õ': case 'Ó': case 'Ò': case 'Ô': case 'Õ': return 'o';
        case 'ú': case 'ù': case 'û': case 'Ú': case 'Ù': case 'Û': return 'u';
        case 'ç': case 'Ç': return 'c';
        default: return tolower(uc);
    }
}