#include <iostream>
#include <string>

#include <rle.h>
#include <lz78.h>

using namespace std;

int main()
{

    string textoOriginal = "AAAABBBCCDAA";

    cout << "Test RLE" << endl;

    string textoComprimido = comprimirRLE(textoOriginal);
    cout << "Texto comprimido: " << textoComprimido << endl;

    string textoDescomprimido = descomprimirRLE(textoComprimido);
    cout << "Texto restaurado: " << textoDescomprimido << endl;

    if (textoOriginal == textoDescomprimido) {
        cout << "\nOK" << endl;
    } else {
        cout << "\nNo" << endl;
    }


    return 0;
}
