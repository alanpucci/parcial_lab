#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Cliente.h"
#include "Sale.h"
#define BUFFER_SIZE 4096

/** \brief Parsea los datos de los clientes desde un archivo(modo texto).
 *
 * \param pFile FILE*: Direccion del archivo
 * \param clientList LinkedList*: Puntero a la LinkedList
 * \return (-1) Si algo salio mal o (0) si todo esta bien
 *
 */
int parser_clientFromText(FILE* pFile , LinkedList* clientList)
{
	int retornar=-1;
	char bufferId[BUFFER_SIZE];
	char bufferName[BUFFER_SIZE];
	char bufferLastName[BUFFER_SIZE];
	char bufferCuit[BUFFER_SIZE];
	Cliente* bufferClient;
	if(pFile!=NULL && clientList!=NULL)
	{
		do
		{
			if(fscanf(pFile, "%[^,],%[^,],%[^,],%[^\n]\n",bufferId,bufferName,bufferLastName,bufferCuit)==4)
			{
				bufferClient = cliente_newWithParametersTxt(bufferId, bufferName, bufferLastName, bufferCuit);
				ll_add(clientList, bufferClient);
				retornar=0;
			}
			else
			{
				cliente_delete(bufferClient);
			}
		}while(feof(pFile)==0);
	}
    return retornar;
}

/** \brief Parsea los datos de las ventas desde un archivo(modo texto).
 *
 * \param pFile FILE*: Direccion del archivo
 * \param sellList LinkedList*: Puntero a la LinkedList
 * \return (-1) Si algo salio mal o (0) si todo esta bien
 *
 */
int parser_sellFromText(FILE* pFile , LinkedList* sellList)
{
	int retornar=-1;
	char bufferIdSell[BUFFER_SIZE];
	char bufferIdClient[BUFFER_SIZE];
	char bufferPosterQty[BUFFER_SIZE];
	char bufferFileName[BUFFER_SIZE];
	char bufferZone[BUFFER_SIZE];
	char bufferState[BUFFER_SIZE];
	Sale* bufferSell;
	if(pFile!=NULL && sellList!=NULL)
	{
		do
		{
			if(fscanf(pFile, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n",bufferIdSell, bufferIdClient,bufferPosterQty,bufferFileName,bufferZone, bufferState)==6)
			{
				bufferSell = sale_newWithParametersTxt(bufferIdClient, bufferIdSell, bufferPosterQty, bufferFileName, bufferZone, bufferState);
				ll_add(sellList, bufferSell);
				retornar=0;
			}
			else
			{
				sale_delete(bufferSell);
			}
		}while(feof(pFile)==0);
	}
    return retornar;
}
