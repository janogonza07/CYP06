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
						// Convertir palabra a min�sculas
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
								// La palabra ya existe, incrementa la estad�stica
								iEstadisticas[j]++;
								palabraExistente = 1;
							}
						}

						if (!palabraExistente)
						{
							// La palabra no existe, agr�gala al final de szPalabras
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

	//Sustituya estas lineas por su c�digo
	strcpy(szListaFinal[0], szPalabrasSugeridas[0]); //la palabra candidata
	iPeso[0] = iEstadisticas[0];			// el peso de la palabra candidata

	iNumLista = 1;							//Una sola palabra candidata
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

	// Operaci�n de eliminaci�n
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

	// Operaci�n de trasposici�n
	for (int i = 0; i < strlen(szPalabraLeida) - 1; i++)
	{
		char palabraTraspuesta[TAMTOKEN];
		strcpy(palabraTraspuesta, szPalabraLeida);
		char temp = palabraTraspuesta[i];
		palabraTraspuesta[i] = palabraTraspuesta[i + 1];
		palabraTraspuesta[i + 1] = temp;
		strcpy(szPalabrasSugeridas[iNumSugeridas++], palabraTraspuesta);
	}

	// Operaci�n de sustituci�n e inserci�n
	for (int i = 0; i <= strlen(szPalabraLeida); i++)
	{
		iNumSugeridas = 0;

		// Operaci�n de eliminaci�n
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

		// Operaci�n de trasposici�n
		for (int i = 0; i < strlen(szPalabraLeida) - 1; i++)
		{
			char palabraTraspuesta[TAMTOKEN];
			strcpy(palabraTraspuesta, szPalabraLeida);
			char temp = palabraTraspuesta[i];
			palabraTraspuesta[i] = palabraTraspuesta[i + 1];
			palabraTraspuesta[i + 1] = temp;
			strcpy(szPalabrasSugeridas[iNumSugeridas++], palabraTraspuesta);
		}

		// Operaci�n de sustituci�n e inserci�n
		for (int i = 0; i <= strlen(szPalabraLeida); i++)
		{
			for (char c = 'a'; c <= 'z'; c++)
			{
				char palabraModificada[TAMTOKEN];
				int index = 0;
				for (int k = 0; k < strlen(szPalabraLeida) + 1; k++)
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
		}
	}
}
//Una sola palabra sugerida
