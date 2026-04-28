#include <iostream>
#include <string>
#include "rle.h"

using namespace std;

int main() {
    string textoOriginalRLE;

    cout << "Test RLE" << endl;
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

    return 0;
}
