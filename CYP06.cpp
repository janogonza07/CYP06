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
    iNumLista = 0;  // Inicializar el contador de palabras en la lista final

    // Para cada palabra sugerida, buscarla en el diccionario y calcular su peso
    for (int i = 0; i < iNumSugeridas; i++) {
        char palabraSugerida[TAMTOKEN];
        strcpy(palabraSugerida, szPalabrasSugeridas[i]);

        // Buscar la palabra sugerida en el diccionario
        for (int j = 0; j < iNumElementos; j++) {
            if (strcmp(szPalabras[j], palabraSugerida) == 0) {
                // Calcular el peso de la palabra sugerida (basado en su frecuencia en el diccionario)
                iPeso[iNumLista] = iEstadisticas[j];
                strcpy(szListaFinal[iNumLista], palabraSugerida);
                iNumLista++;
                break;
            }
        }
    }

    // Ordenar la lista final de palabras sugeridas por peso
    for (int i = 0; i < iNumLista - 1; i++) {
        for (int j = i + 1; j < iNumLista; j++) {
            if (iPeso[i] < iPeso[j]) {
                // Intercambiar palabras y pesos
                char tempPalabra[TAMTOKEN];
                int tempPeso = iPeso[i];

                strcpy(tempPalabra, szListaFinal[i]);
                strcpy(szListaFinal[i], szListaFinal[j]);
                strcpy(szListaFinal[j], tempPalabra);

                iPeso[i] = iPeso[j];
                iPeso[j] = tempPeso;
            }
        }
    }
}
