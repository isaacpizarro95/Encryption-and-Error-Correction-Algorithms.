// Funcions per gestionar els arguments de la funció main
// Autor: Isaac Pizarro Contreras
// NIU: 1636421

#include "isaac.h"

void check_valors(char *argument[], int *p, int *k){
    if(argument[1][1] == 'p') assignacio_p_k(p, argument[1]);
    else if(argument[1][1] == 'k') assignacio_p_k(k, argument[1]);

    if(argument[2][1] == 'p') assignacio_p_k(p, argument[2]);
    else if(argument[2][1] == 'k') assignacio_p_k(k, argument[2]);
}

// ** REVISAR EL TAMANY DE AUX QUE DEPENDRA DE LA LLARGADA DEL NOMBRE P i K ** //
void assignacio_p_k(int *nou_valor, char *argument){
    char aux[2];
    for(int i = 0; i < 2; i++){
        aux[i] = argument[i+3];
    }
    *nou_valor = atoi(aux);
}