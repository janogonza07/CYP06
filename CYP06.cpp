void ClonaPalabras(
    char* szPalabraLeida,
    char szPalabrasSugeridas[][TAMTOKEN],
    int& iNumSugeridas
) {
    iNumSugeridas = 0;  // Inicializar el contador de palabras sugeridas

    // Supresión de caracteres
    int len = strlen(szPalabraLeida);
    for (int i = 0; i < len; i++) {
        // Crear una nueva palabra sin el caracter i
        char palabraSugerida[TAMTOKEN];
        int pos = 0;
        for (int j = 0; j < len; j++) {
            if (j != i) {
                palabraSugerida[pos++] = szPalabraLeida[j];
            }
        }
        palabraSugerida[pos] = '\0';

        // Agregar la palabra sugerida a la lista
        strcpy(szPalabrasSugeridas[iNumSugeridas], palabraSugerida);
        iNumSugeridas++;
    }

    // Sustitución de caracteres
    for (int i = 0; i < len; i++) {
        for (char c = 'a'; c <= 'z'; c++) {
            if (szPalabraLeida[i] != c) {
                // Crear una nueva palabra con la sustitución
                char palabraSugerida[TAMTOKEN];
                strcpy(palabraSugerida, szPalabraLeida);
                palabraSugerida[i] = c;

                // Agregar la palabra sugerida a la lista
                strcpy(szPalabrasSugeridas[iNumSugeridas], palabraSugerida);
                iNumSugeridas++;
            }
        }
    }

    // Transposición de caracteres
    for (int i = 0; i < len - 1; i++) {
        // Crear una nueva palabra con la transposición
        char palabraSugerida[TAMTOKEN];
        strcpy(palabraSugerida, szPalabraLeida);
        std::swap(palabraSugerida[i], palabraSugerida[i + 1]);

        // Agregar la palabra sugerida a la lista
        strcpy(szPalabrasSugeridas[iNumSugeridas], palabraSugerida);
        iNumSugeridas++;
    }

    // Inserción de caracteres
    for (int i = 0; i <= len; i++) {
        for (char c = 'a'; c <= 'z'; c++) {
            // Crear una nueva palabra con la inserción
            char palabraSugerida[TAMTOKEN];
            int pos = 0;
            for (int j = 0; j < len + 1; j++) {
                if (j == i) {
                    palabraSugerida[pos++] = c;
                }
                else {
                    palabraSugerida[pos++] = szPalabraLeida[j - (j > i ? 1 : 0)];
                }
            }
            palabraSugerida[pos] = '\0';

            // Agregar la palabra sugerida a la lista
            strcpy(szPalabrasSugeridas[iNumSugeridas], palabraSugerida);
            iNumSugeridas++;
        }
    }

    // Ordenar la lista de palabras sugeridas alfabéticamente
    for (int i = 0; i < iNumSugeridas - 1; i++) {
        for (int j = i + 1; j < iNumSugeridas; j++) {
            if (strcmp(szPalabrasSugeridas[i], szPalabrasSugeridas[j]) > 0) {
                // Intercambiar palabras
                char temp[TAMTOKEN];
                strcpy(temp, szPalabrasSugeridas[i]);
                strcpy(szPalabrasSugeridas[i], szPalabrasSugeridas[j]);
                strcpy(szPalabrasSugeridas[j], temp);
            }
        }
    }
}



