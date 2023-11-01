#include <iostream>
#include <fstream>
#include <cstring>

const int TAMTOKEN = 50;  // Tamaño máximo de las palabras
const int MAX_ELEMENTOS = 50000;  // Máximo número de palabras en el diccionario

void Diccionario(
    const char* szNombre,
    char szPalabras[][TAMTOKEN],
    int iEstadisticas[],
    int& iNumElementos
) {
    // ... (Código de la función Diccionario)
}

void ClonaPalabras(
    char* szPalabraLeida,
    char szPalabrasSugeridas[][TAMTOKEN],
    int& iNumSugeridas
) {
    // ... (Código de la función ClonaPalabras)
}

void ListaCandidatas(
    char szPalabrasSugeridas[][TAMTOKEN],
    int iNumSugeridas,
    char szPalabras[][TAMTOKEN],
    int iEstadisticas[],
    int iNumElementos,
    char szListaFinal[][TAMTOKEN],
    int iPeso[],
    int& iNumLista
) {
    // ... (Código de la función ListaCandidatas)
}

int main() {
    char szPalabras[MAX_ELEMENTOS][TAMTOKEN];
    int iEstadisticas[MAX_ELEMENTOS];
    int iNumElementos;
    char szPalabraLeida[TAMTOKEN];
    char szPalabrasSugeridas[MAX_ELEMENTOS][TAMTOKEN];
    int iNumSugeridas;
    char szListaFinal[MAX_ELEMENTOS][TAMTOKEN];
    int iPeso[MAX_ELEMENTOS];
    int iNumLista;

    // Llama a la función Diccionario para cargar el archivo
    Diccionario("nombre_archivo.txt", szPalabras, iEstadisticas, iNumElementos);

    // Solicita al usuario una palabra a corregir
    std::cout << "Ingrese la palabra a corregir: ";
    std::cin >> szPalabraLeida;

    // Llama a la función ClonaPalabras para obtener palabras sugeridas
    ClonaPalabras(szPalabraLeida, szPalabrasSugeridas, iNumSugeridas);

    // Llama a la función ListaCandidatas para obtener una lista final ordenada
    ListaCandidatas(szPalabrasSugeridas, iNumSugeridas, szPalabras, iEstadisticas, iNumElementos, szListaFinal, iPeso, iNumLista);

    // Imprime la lista final de palabras sugeridas
    std::cout << "Palabras sugeridas ordenadas por peso:" << std::endl;
    for (int i = 0; i < iNumLista; i++) {
        std::cout << szListaFinal[i] << " (Peso: " << iPeso[i] << ")" << std::endl;
    }

    return 0;
}


