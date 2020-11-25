#include <stdio.h>
#include <stdlib.h>
#include "utn.h"
#define ARRAY_SIZE 4096

/** \brief Imprime el menu y devuelve por referencia la opcion elegida
 *
 * \param int *pResult: Pasaje por referencia de la opcion elegida
 * \param int attemps: Numero de reintentos posibles
 * \param int min: Numero minime permitido
 * \param int max: Numero maximo permitido
 * \return (-1) Si algo salio mal o (0) si todo esta bien
 *
 */
int utn_getMenu(int *pResult, int attemps, int min, int max)
{
	int retorno = -1;
	char bufferString[ARRAY_SIZE];
	int bufferInt;

	if(pResult != NULL && attemps >= 0 && min <= max)
	{
		do
		{
			printf("\nElija una opcion: \n"
					"1) Agregar cliente\n"
					"2) Vender afiches\n"
					"3) Modificar venta\n"
					"4) Cobrar venta\n"
					"5) Generar informe de cobros\n"
					"6) Generar informe de deudas\n"
					"7) Generar estadisticas\n"
					"> > OPCION:");
			if(myGets(bufferString, ARRAY_SIZE) == 0 && isInt(bufferString) == 1)
			{
				bufferInt = atoi(bufferString);
				if(bufferInt >= min && bufferInt<= max)
				{
					*pResult = bufferInt;
					retorno = 0;
					break;
				}
				else
				{
					printf("\nError! elija una opcion valida");
					attemps--;
				}

			}
			else
			{
				printf("Error! elija una opcion valida");
				attemps--;
			}
		}while(attemps >= 0);
	}
	return retorno;
}
