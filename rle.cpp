#include "rle.h"
#include <string>

using namespace std;

string comprimirRLE(const string& textoOriginal) {

    if (textoOriginal.empty()) return "";

    string textoComprimido = "";
    unsigned int contador = 1;

    for (unsigned int i = 1; i <= textoOriginal.length(); ++i) {
        if (i < textoOriginal.length() && textoOriginal[i] == textoOriginal[i - 1]) {
            contador++;
        } else {
            // Delimitador
            textoComprimido += to_string(contador) + "-" + textoOriginal[i - 1];
            contador = 1;
        }
    }

    return textoComprimido;
}

string descomprimirRLE(const string& textoComprimido) {

    string textoDescomprimido = "";
    unsigned int i = 0;

    while (i < textoComprimido.length()) {

        size_t posDel = textoComprimido.find('-', i);

        int repeticiones = stoi(textoComprimido.substr(i, posDel - i));

        textoDescomprimido.append(repeticiones, textoComprimido[posDel + 1]);

        i = posDel + 2;
    }

    return textoDescomprimido;
}
