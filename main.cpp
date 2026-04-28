#include <iostream>
#include <string>
#include "rle.h"
#include "lz78.h"

using namespace std;

int main() {
    string textoOriginalRLE;

    cout << "Test RLE: " << endl;
    cin >> textoOriginalRLE;

    cout << "\nTexto original: " << textoOriginalRLE << endl;

    // Comprimir
    string textoComprimido = comprimirRLE(textoOriginalRLE);
    cout << "Texto comprimido: " << textoComprimido << endl;

    // Descomprimir
    string textoRestaurado = descomprimirRLE(textoComprimido);

    if (textoOriginalRLE == textoRestaurado) {
        cout << "OK, gracias a lucho" << endl;
    } else {
        cout << "Malo, culpa de bolo" << endl;
    }


    string textoInput;

    cout << "\n\nTest LZ78" << endl;
    cin >> textoInput;

    const char* textoOriginalLZ = textoInput.c_str();

    DatosComprimidos comprimidoLZ = comprimirLZ78(textoOriginalLZ);

    char* textoRestauradoLZ = descomprimirLZ78(comprimidoLZ);

    if (textoInput == string(textoRestauradoLZ)) {
        cout << "OK, gracias a bolo" << endl;
    } else {
        cout << "Malo, culpa de lucho" << endl;
    }


    // liberar memoria
    delete[] textoRestauradoLZ;
    liberarMemoria(comprimidoLZ);

    return 0;
}
