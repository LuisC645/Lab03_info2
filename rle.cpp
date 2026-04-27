#include "rle.h"
#include <cctype> // isdigit()

using namespace std;

string comprimirRLE(const string& textoOriginal) {

    if (textoOriginal.empty()){
        return "";
    }

    string textoComprimido = "";
    unsigned short contador = 1;

    for (unsigned int i = 1; i <= textoOriginal.length(); ++i) {

        // Char igual al anterior
        if (i < textoOriginal.length() && textoOriginal[i] == textoOriginal[i - 1]){
            contador++;
        } else{
            // Reiniciar cont
            textoComprimido += to_string(contador) + textoOriginal[i - 1];
            contador = 1;
        }
    }
    return textoComprimido;
}

string descomprimirRLE(const string& textoComprimido) {

    string textoDescomprimido = "";
    string numeroStr = "";

    for (unsigned short i = 0; i < textoComprimido.length(); ++i) {

        // Guardar Num (pueden haber mas de 1)
        if (isdigit(textoComprimido[i])) {
            numeroStr += textoComprimido[i];
        } else {
            // Letra? guardar num
            int repeticiones = stoi(numeroStr);
            textoDescomprimido.append(repeticiones, textoComprimido[i]);
            numeroStr = "";
        }
    }

    return textoDescomprimido;
}
