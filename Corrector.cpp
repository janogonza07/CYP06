/*****************************************************************************************************************
	UNIVERSIDAD NACIONAL AUTONOMA DE MEXICO
	FACULTAD DE ESTUDIOS SUPERIORES -ARAGON-

	Computadoras y programacion. 
	(c) Ponga su nombre y numero de cuenta aqui.
	
	Quiso decir: Programa principal de la aplicacion de la distancia de Levenstein.
	
******************************************************************************************************************/


#include "stdafx.h"
#include <string.h>
#include "corrector.h"
#define DEPURAR 1


//Funciones publicas del proyecto
/*****************************************************************************************************************
	DICCIONARIO: Esta funcion crea el diccionario completo
	char *	szNombre				:	Nombre del archivo de donde se sacaran las palabras del diccionario	
	char	szPalabras[][TAMTOKEN]	:	Arreglo con las palabras completas del diccionario
	int		iEstadisticas[]			:	Arreglo con el numero de veces que aparecen las palabras en el diccionario
	int &	iNumElementos			:	Numero de elementos en el diccionario
******************************************************************************************************************/
void	Diccionario			(char *szNombre, char szPalabras[][TAMTOKEN], int iEstadisticas[], int &iNumElementos)
{
	FILE* fpDicc;
	char linea[4000];
	char palabraDetectada[TAMTOKEN];
	int i;
	int indicePD;
	//variables para el uso en burbujazo
	int posicion; int pasada; char aux[TAMTOKEN];;
	iNumElementos = 0;
	// abrir el achivo
	if (DEPURAR == 1)
		printf("%s", szNombre);

	fopen_s(&fpDicc, szNombre, "r");
	if (fpDicc != NULL)
	{
		
		if (DEPURAR == 1)
			printf("\nSi lo pude abrir");

		indicePD = 0;
		while (!feof(fpDicc))
		{
			fgets(linea, sizeof(linea), fpDicc);
			if (DEPURAR == 1)
				printf("\n%s\n", linea);

			for (i = 0; i < strlen(linea); i++)
			{
				// Detectar una palabra
				if (linea[i] == ' ')
				{
					// Eliminar los espacios en blanco como palabras
					if (indicePD > 0)
					{
						palabraDetectada[indicePD] = '\0';
						// Convertir palabra a minúsculas
						for (int k = 0; k < indicePD; k++) {
							palabraDetectada[k] = towlower(palabraDetectada[k]);
						}

						// Buscar la palabra en szPalabras
						int palabraExistente = 0;
						int j;
						for (j = 0; j < iNumElementos; j++)
						{
							if (strcmp(szPalabras[j], palabraDetectada) == 0)
							{
								// La palabra ya existe, incrementa la estadística
								iEstadisticas[j]++;
								palabraExistente = 1;
							}
						}

						if (!palabraExistente)
						{
							// La palabra no existe, agrégala al final de szPalabras
							strcpy_s(szPalabras[iNumElementos], TAMTOKEN, palabraDetectada);
							iEstadisticas[iNumElementos] = 1;
							iNumElementos++;
						}

						if (DEPURAR == 1)
							//printf("\np: %s", palabraDetectada);

							indicePD = 0;
					}
				}
				else
				{
					if (linea[i] != '(' && linea[i] != ')')
					{
						if (linea[i] != ',')
						{
							if (linea[i] != '.')
							{
								if (linea[i] != ';')
								{

									if (linea[i] != '-') 
									{
										if (linea[i] != '"')
										{


											palabraDetectada[indicePD] = linea[i];
											indicePD++;
										}
									}
								}
							}
						}
					}
				}
			}


				
			if (DEPURAR == 1)
				printf("\nNumPalabras: %i\n", iNumElementos);
			
			// burbujazo
			for (pasada = 0; pasada < iNumElementos - 1; pasada++)
			{
				for (posicion = 0; posicion < iNumElementos - 1; posicion++)
				{
					if (strcmp(szPalabras[posicion], szPalabras[posicion + 1]) > 0)
					{
						//realizar el intercambio
				        strcpy_s(aux,szPalabras[posicion]);
						strcpy_s(szPalabras[posicion], szPalabras[posicion + 1]);
						strcpy_s(szPalabras[posicion + 1], aux);
					}
				}
			}

			//fin burbujazo 
		}

		fclose(fpDicc);
	}
	else
	{
		if (DEPURAR == 1)
			printf("\nNo lo pude abrir");
	}
}

/*****************************************************************************************************************
	ListaCandidatas: Esta funcion recupera desde el diccionario las palabras validas y su peso
	Regresa las palabras ordenadas por su peso
	char	szPalabrasSugeridas[][TAMTOKEN],	//Lista de palabras clonadas
	int		iNumSugeridas,						//Lista de palabras clonadas
	char	szPalabras[][TAMTOKEN],				//Lista de palabras del diccionario
	int		iEstadisticas[],					//Lista de las frecuencias de las palabras
	int		iNumElementos,						//Numero de elementos en el diccionario
	char	szListaFinal[][TAMTOKEN],			//Lista final de palabras a sugerir
	int		iPeso[],							//Peso de las palabras en la lista final
	int &	iNumLista)							//Numero de elementos en la szListaFinal
******************************************************************************************************************/
void	ListaCandidatas(
	char	szPalabrasSugeridas[][TAMTOKEN],	//Lista de palabras clonadas
	int		iNumSugeridas,						//Lista de palabras clonadas
	char	szPalabras[][TAMTOKEN],				//Lista de palabras del diccionario
	int		iEstadisticas[],					//Lista de las frecuencias de las palabras
	int		iNumElementos,						//Numero de elementos en el diccionario
	char	szListaFinal[][TAMTOKEN],			//Lista final de palabras a sugerir
	int		iPeso[],							//Peso de las palabras en la lista final
	int& iNumLista)							//Numero de elementos en la szListaFinal

{
	iNumLista = 0;

	// Ordenar las sugerencias según su peso (frecuencia en el diccionario)
	for (int i = 0; i < iNumSugeridas - 1; i++)
	{
		for (int j = 0; j < iNumSugeridas - i - 1; j++)
		{
			// Comparar por frecuencia en el diccionario (peso)
			if (iEstadisticas[j] < iEstadisticas[j + 1])
			{
				// Realizar el intercambio
				char temp[TAMTOKEN];
				strcpy_s(temp, TAMTOKEN, szPalabrasSugeridas[j]);
				strcpy_s(szPalabrasSugeridas[j], TAMTOKEN, szPalabrasSugeridas[j + 1]);
				strcpy_s(szPalabrasSugeridas[j + 1], TAMTOKEN, temp);

				// Intercambiar frecuencias
				int tempEstadistica = iEstadisticas[j];
				iEstadisticas[j] = iEstadisticas[j + 1];
				iEstadisticas[j + 1] = tempEstadistica;
			}
		}
	}

	// Asignar memoria para la lista final
	szListaFinal = new char* [iNumSugeridas];
	iPeso = new int[iNumSugeridas];

	// Agregar las palabras sugeridas a la lista final
	for (int i = 0; i < iNumSugeridas; i++)
	{
		szListaFinal[i] = new char[TAMTOKEN];
		strcpy_s(szListaFinal[i], TAMTOKEN, szPalabrasSugeridas[i]);
		iPeso[i] = iEstadisticas[i];
		iNumLista++;
	}
}


/*****************************************************************************************************************
	ClonaPalabras: toma una palabra y obtiene todas las combinaciones y permutaciones requeridas por el metodo
	char *	szPalabraLeida,						// Palabra a clonar
	char	szPalabrasSugeridas[][TAMTOKEN], 	//Lista de palabras clonadas
	int &	iNumSugeridas)						//Numero de elementos en la lista
******************************************************************************************************************/
void	ClonaPalabras(
	char* szPalabraLeida,						// Palabra a clonar
	char	szPalabrasSugeridas[][TAMTOKEN], 	//Lista de palabras clonadas
	int& iNumSugeridas)						//Numero de elementos en la lista
{
	iNumSugeridas = 0;
	

	// Ciclo para letras del alfabeto
	for (char c = 'a'; c <= 'z'; c++) {
		char palabraModificada[TAMTOKEN];
		palabraModificada[0] = c;
		strcpy(palabraModificada + 1, szPalabraLeida);
		strcpy(szPalabrasSugeridas[iNumSugeridas++], palabraModificada);
	}

	// Ciclo para vocales acentuadas en su forma ASCII
	const char vocalesAcentuadas[] = { '\xA0', '\x82', '\xA1', '\xA2', '\xA3' };
	for (int i = 0; i < sizeof(vocalesAcentuadas); i++) {
		char palabraModificada[TAMTOKEN];
		palabraModificada[0] = vocalesAcentuadas[i];
		strcpy(palabraModificada + 1, szPalabraLeida);
		strcpy(szPalabrasSugeridas[iNumSugeridas++], palabraModificada);
	}
	

	// Operación de eliminación
	for (int i = 0; i < strlen(szPalabraLeida); i++)
	{
		char palabraEliminada[TAMTOKEN];
		int index = 0;
		for (int j = 0; j < strlen(szPalabraLeida); j++)
		{
			if (j != i)
			{
				palabraEliminada[index++] = szPalabraLeida[j];
			}
		}
		palabraEliminada[index] = '\0';
		strcpy(szPalabrasSugeridas[iNumSugeridas++], palabraEliminada);
	}





	// Operación de trasposición
	for (int i = 0; i < strlen(szPalabraLeida) - 1; i++)
	{
		char palabraTraspuesta[TAMTOKEN];
		strcpy(palabraTraspuesta, szPalabraLeida);
		char temp = palabraTraspuesta[i];
		palabraTraspuesta[i] = palabraTraspuesta[i + 1];
		palabraTraspuesta[i + 1] = temp;
		strcpy(szPalabrasSugeridas[iNumSugeridas++], palabraTraspuesta);
	}

	// Operación de sustitución e inserción con vocales acentuadas en código ASCII
	const char* vocalesAcentuadasASCII[] = { "\xA0", "\x82", "\xA1", "\xA2", "\xA3"};

	for (int i = 0; i <= strlen(szPalabraLeida); i++)
	{
		for (char c = 'a'; c <= 'z'; c++)
		{
			char palabraModificada[TAMTOKEN];
			int index = 0;
			for (int k = 0; k < strlen(szPalabraLeida)+1; k++)
			{
				if (k == i)
				{
					palabraModificada[index++] = c;
				}
				else if (k != strlen(szPalabraLeida))
				{
					palabraModificada[index++] = szPalabraLeida[k];
				}
			}
			palabraModificada[index] = '\0';
			strcpy(szPalabrasSugeridas[iNumSugeridas++], palabraModificada);
		}
		
         // Agregar vocales acentuadas en código ASCII
		for (int j = 0; j < 5; j++) // 6 es la longitud del array vocalesAcentuadasASCII
		{
			char palabraModificada[TAMTOKEN];
			int index = 0;
			for (int k = 0; k < strlen(szPalabraLeida) + 1; k++)
			{
				if (k == i)
				{
					strcpy(palabraModificada + index, vocalesAcentuadasASCII[j]);
					index += strlen(vocalesAcentuadasASCII[j]);
				}
				else if (k != strlen(szPalabraLeida))
				{
					palabraModificada[index++] = szPalabraLeida[k];
				}
			}
			palabraModificada[index] = '\0';
			strcpy(szPalabrasSugeridas[iNumSugeridas++], palabraModificada);
		}
	}
	
}

