// Funcions per crear la matriu de codificació
// Autor: Isaac Pizarro Contreras
// NIU: 1636421

int calcul_potencia(int p, int a, int potencia){
    int a_final = a;
    if(potencia == 0){
        return 1;
    }
    while(potencia > 1){
        a_final = (a_final * a) % p;
        potencia--;
    }
    a_final = a_final % p;
    return a_final;
}

void crea_matriu_vandermonde(int p, int files, int cols, int m[][cols]){
    int a_primitiu = element_primitiu(p);
    for(int i = 0; i < files; i++) {
        for(int j = 0; j < cols; j++) {
            m[i][j] = calcul_potencia(p, a_primitiu, i*j);;
        }
    }
    return;
}