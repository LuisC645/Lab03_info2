#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept> // Para runtime_error
#include <new>       // Para bad_alloc (errores de memoria dinámica)
#include "rle.h"
#include "lz78.h"
#include "encript.h"

using namespace std;

bool compararTextos(const char* texto1, const char* texto2) {

    int i = 0;

    while (texto1[i] != '\0' || texto2[i] != '\0') {

        if (texto1[i] != texto2[i]) return false;
        i++;
    }
    return true;
}

// aux para leer archivos (lz78 de mem dinamica)
char* leerArchivoDinamico(const char* ruta) {

    ifstream archivo(ruta, ios::ate | ios::binary);

    int tamano = archivo.tellg();
    archivo.seekg(0, ios::beg);

    char* buffer = new char[tamano + 1];

    if (!archivo.read(buffer, tamano)) {
        delete[] buffer;
        throw runtime_error("Error critico al leer el contenido del archivo.");
    }

    buffer[tamano] = '\0';
    archivo.close();
    return buffer;
}

int main() {

    int opcion;
    int n = 3;                  // 0 < n < 8
    unsigned char clave = 0x5A; // Clave XOR

    string nombreArchivoEntrada = "data/dataset_Original_hint_5.txt";

    string rutaSalidaRLE = "data_out/salida_rle.txt";
    string rutaSalidaLZ = "data_out/salida_lz.txt";

    string rutaComprimidoRLE = "data_out/salida_comprimido_RLE.txt";
    string rutaComprimidoLZ = "data_out/salida_comprimido_LZ.txt";

    string rutaEncriptadoRLE = "data_out/salida_encriptado_RLE.txt";
    string rutaEncriptadoLZ = "data_out/salida_encriptado_LZ.txt";

    cout << "Lab 03 - Marcos Castillo - Lucho Castrillon" << endl;
    cout << "1. RLE" << endl;
    cout << "2. LZ78" << endl;
    cout << "Opcion: ";

    if (!(cin >> opcion)) {
        cout << "Entrada no valida." << endl;
        return 1;
    }

    try {
        if (opcion == 1) {
            cout << "\nRLE: " << endl;

            // data original
            ifstream archivoIn(nombreArchivoEntrada);
            if (!archivoIn.is_open()) {
                throw runtime_error("No hay data .-.");
            }

            string textoOriginal((istreambuf_iterator<char>(archivoIn)), istreambuf_iterator<char>());
            archivoIn.close();

            cout << "\n Texto original: " << textoOriginal << "\n" <<endl;

            // Comprimir
            string comprimido = comprimirRLE(textoOriginal);
            cout << "1. Comprimido " << endl;

            ofstream archivoComprimidoOut(rutaComprimidoRLE);
            if (!archivoComprimidoOut.is_open()) {
                throw runtime_error("Error con el archivo comprimido");
            }
            archivoComprimidoOut << comprimido;
            archivoComprimidoOut.close();

            cout << "\n Texto Comprimido: " << comprimido << "\n" <<endl;

            // Encriptar
            string encriptado = encriptarString(comprimido, n, clave);
            cout << "2. Encriptado" << endl;

            cout << "\n Texto Encriptado: " << encriptado << "\n" <<endl;

            ofstream archivoEncriptadoOut(rutaEncriptadoRLE);
            if (!archivoEncriptadoOut.is_open()) {
                throw runtime_error("Error con el archivo encriptado");
            }
            archivoEncriptadoOut << encriptado;
            archivoEncriptadoOut.close();

            // Desencriptar
            string desencriptado = desencriptarString(encriptado, n, clave);
            cout << "3. Desencriptado" << endl;

            cout << "\n Texto Desencriptado: " << desencriptado << "\n" <<endl;

            // Descomprimir
            string restaurado = descomprimirRLE(desencriptado);
            cout << "4. Descomprimido" << endl;

            ofstream archivoOut(rutaSalidaRLE);
            if (!archivoOut.is_open()) {
                throw runtime_error("Error con el archivo de salida");
            }
            archivoOut << restaurado;
            archivoOut.close();

            cout << "\n Texto salida: " << restaurado << "\n" <<endl;

            // Validar
            ifstream archivoValidacion(rutaSalidaRLE);
            string textoFinal((istreambuf_iterator<char>(archivoValidacion)), istreambuf_iterator<char>());
            archivoValidacion.close();

            if (textoOriginal == textoFinal) {
                cout << "Funciona gracias a lucho como siempre" << endl;
            } else {
                cout<< "No funciona, a bolo lo consumió la IA" << endl;
            }

        } else if (opcion == 2) {

            cout << "\nLZ78: " << endl;

            // Carga data
            char* textoOriginal = leerArchivoDinamico(nombreArchivoEntrada.c_str());

            cout << "\n Texto original: " << textoOriginal << "\n" <<endl;

            // Comprimir
            DatosComprimidos comprimido = comprimirLZ78(textoOriginal);
            cout << "1. Comprimido" << endl;

            cout << "\n Texto comprimido: ";
            for (int i = 0; i < comprimido.cantidad; ++i) {
                cout << "(" << comprimido.pares[i].indice << ",";

                if (comprimido.pares[i].c == '\0') {
                    cout << "\\0";
                } else {
                    cout << comprimido.pares[i].c;
                }

                cout << ") ";
            }
            cout << "\n" << endl;

            // Guardar comprimido
            ofstream archivoComprimidoOut(rutaComprimidoLZ);

            if (!archivoComprimidoOut.is_open()) {
                delete[] textoOriginal;
                liberarMemoria(comprimido);
                throw runtime_error("Error con el comprimido");
            }

            for (int i = 0; i < comprimido.cantidad; ++i) {
                archivoComprimidoOut << "(" << comprimido.pares[i].indice << "," << comprimido.pares[i].c << ") ";
            }

            archivoComprimidoOut.close();

            // Encriptar
            int tamanoBytes = comprimido.cantidad * sizeof(ParLZ78);
            unsigned char* ptrBytes = reinterpret_cast<unsigned char*>(comprimido.pares);

            encriptarBuffer(ptrBytes, tamanoBytes, n, clave);
            cout << "2. Encriptado" << endl;

            cout << "\n Texto Encriptado (Bytes): ";
            for (int i = 0; i < tamanoBytes; ++i) {
                cout << ptrBytes[i];
            }
            cout << "\n" << endl;

            // Guardar encriptado
            ofstream archivoEncriptadoOut(rutaEncriptadoLZ, ios::binary);

            if (!archivoEncriptadoOut.is_open()) {
                delete[] textoOriginal;
                liberarMemoria(comprimido);
                throw runtime_error("Error con el encriptado");
            }

            archivoEncriptadoOut.write(reinterpret_cast<char*>(ptrBytes), tamanoBytes);
            archivoEncriptadoOut.close();

            // Desencriptar
            desencriptarBuffer(ptrBytes, tamanoBytes, n, clave);
            cout << "3. Desencriptado" << endl;

            cout << "\n Texto desencriptado: ";
            for (int i = 0; i < comprimido.cantidad; ++i) {

                cout << "(" << comprimido.pares[i].indice << ",";

                if (comprimido.pares[i].c == '\0') {
                    cout << "\\0";
                } else {
                    cout << comprimido.pares[i].c;
                }

                cout << ") ";
            }
            cout << "\n" << endl;

            // 4. Descomprimir
            char* restaurado = descomprimirLZ78(comprimido);
            cout << "4. Descomprimido" << endl;

            // guardar salida
            ofstream archivoOut(rutaSalidaLZ);

            if (!archivoOut.is_open()) {
                delete[] textoOriginal;
                delete[] restaurado;
                liberarMemoria(comprimido);
                throw runtime_error("Error con la salida");
            }

            archivoOut << restaurado;
            archivoOut.close();

            cout << "\n Texto salida: " << restaurado << "\n" <<endl;

            //  Validar
            char* textoFinal = leerArchivoDinamico(rutaSalidaLZ.c_str());

            if (compararTextos(textoOriginal, textoFinal)) {
                cout << "Funciona gracias a bolo como siempre " << endl;
            } else {
                cout << "No funciona, a lucho lo consumio la IA" << endl;
            }

            delete[] textoOriginal;
            delete[] restaurado;
            delete[] textoFinal;
            liberarMemoria(comprimido);

        }

    }
    catch (const exception& e) {
        cerr << "\nError: " << e.what() << endl;
    }

    return 0;
}
