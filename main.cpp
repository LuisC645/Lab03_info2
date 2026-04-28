#include <iostream>
#include <string>
#include "rle.h"
#include "lz78.h"
#include "encript.h"

using namespace std;

int main() {
    string textoOriginalRLE;

    // Param
    int n = 3;
    unsigned char clave = 0x5A;

    cout << "Test RLE: " << endl;
    cin >> textoOriginalRLE;

    // Comprimir
    string textoComprimido = comprimirRLE(textoOriginalRLE);
    cout << "Texto comprimido: " << textoComprimido << endl;

    // Descomprimir
    cout << "\nTest encriptacion" << endl;
    string textoRest = descomprimirRLE(textoComprimido);

    if (textoOriginalRLE == textoRest) {
        cout << "OK, gracias a lucho" << endl;
    } else {
        cout << "Malo, culpa de bolo" << endl;
    }

    // Test encript

    string textoEncriptado = encriptarString(textoComprimido, n, clave);
    cout << "Texto encriptado: " << textoEncriptado << endl;

    string textoDesencriptado = desencriptarString(textoEncriptado, n, clave);
    cout << "Texto desencriptado: " << textoDesencriptado << endl;

    string textoRestaurado = descomprimirRLE(textoDesencriptado);

    if (textoOriginalRLE == textoRestaurado) {
        cout << "\nOK gracias a lucho otra vez" << endl;
    } else {
        cout << "\nMalo, culpa de bolo como siempre" << endl;
    }

    // -----------------------------------------------------------------

    const int MAX_BUFFER = 10000;
    char textoEntrada[MAX_BUFFER];

    cout << "\n\nTest LZ78" << endl;
    cin >> textoEntrada;

    DatosComprimidos comprimidoLZ = comprimirLZ78(textoEntrada);

    cout << "Texto comprimido LZ78 (Pares): ";

    for (int i = 0; i < comprimidoLZ.cantidad; ++i) {

        cout << "(" << comprimidoLZ.pares[i].indice << ", ";

        if (comprimidoLZ.pares[i].c == '\0') cout << "'\\0'";
        else cout << "'" << comprimidoLZ.pares[i].c << "'";

        cout << ") ";
    }
    cout << endl;

    char* textoRestauradoLZ = descomprimirLZ78(comprimidoLZ);

    if (comparar(textoEntrada, textoRestauradoLZ)) {
        cout << "OK, gracias a bolo" << endl;
    } else {
        cout << "Malo, culpa de lucho" << endl;
    }

    delete[] textoRestauradoLZ;
    liberarMemoria(comprimidoLZ);

    return 0;

    // -----------------------------------------------------------------


    // falta implementacion
}
