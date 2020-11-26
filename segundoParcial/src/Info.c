#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Cliente.h"
#include "Venta.h"
#include "Linkedlist.h"
#include "parser.h"
#include "utn.h"
#include "Controller.h"

static int controller_clientMaxPosterQty(LinkedList* clientList, LinkedList* sellList);
static int controller_clientMinPosterQty(LinkedList* clientList, LinkedList* sellList);
static int controller_sellMaxPosterQty(LinkedList* clientList, LinkedList* sellList);

int controller_report(LinkedList* clientList, LinkedList* sellList)
{
	int retornar=-1;
	int choosenOption;
	LinkedList* bufferSellList = ll_cloneFilter(sellList, venta_isNotSold);
	if(clientList!=NULL && sellList!=NULL)
	{
		if( !utn_getInt("\nIngrese una opcion:\n"
						"1)Cliente al que se le vendio mas afiches\n"
						"2)Cliente al que se le vendio menos afiches\n"
						"3)Venta con mas afiches vendidos\n"
						"4)Volver atras\n> > OPCION: ",
						"\nERROR!", &choosenOption, 2, 1, 4))
		{
			switch(choosenOption)
			{
			case 1:
				if(!controller_clientMaxPosterQty(clientList, bufferSellList))
				{
					retornar=0;
				}
			break;
			case 2:
				if(!controller_clientMinPosterQty(clientList, bufferSellList))
				{
					retornar=0;
				}
			break;
			case 3:
				if(!controller_sellMaxPosterQty(clientList, bufferSellList))
				{
					retornar=0;
				}
			break;
			}
		}
	}
	return retornar;
}

static int controller_clientMaxPosterQty(LinkedList* clientList, LinkedList* sellList)
{
	int retornar=-1;
	int maxQty;
	int currentCounter;
	int bufferClientId;
	Cliente* bufferClient;
	if(clientList!=NULL && sellList!=NULL)
	{
		retornar=0;
		for(int i=0;i<ll_len(clientList);i++)
		{
			bufferClient = ll_get(clientList, i);
			if(bufferClient!=NULL && !cliente_getId(bufferClient, &bufferClientId) && !ll_reduceInt(sellList, venta_sameId, bufferClientId, &currentCounter))
			{
				if(i==0 || maxQty<currentCounter)
				{
					maxQty = currentCounter;
				}
			}
		}
		printf("\nEl/los cliente/s con mas afiches es/son: \n");
		for(int i=0;i<ll_len(clientList);i++)
		{
			bufferClient = ll_get(clientList, i);
			if(bufferClient!=NULL && !cliente_getId(bufferClient, &bufferClientId) && !ll_reduceInt(sellList, venta_sameId, bufferClientId, &currentCounter))
			{
				if(currentCounter == maxQty)
				{
					cliente_print(bufferClient);
				}
			}
		}
	}
	return retornar;
}

static int controller_clientMinPosterQty(LinkedList* clientList, LinkedList* sellList)
{
	int retornar=-1;
	int minQty;
	int currentCounter;
	int bufferClientId;
	Cliente* bufferClient;
	if(clientList!=NULL && sellList!=NULL)
	{
		retornar=0;
		for(int i=0;i<ll_len(clientList);i++)
		{
			bufferClient = ll_get(clientList, i);
			if(bufferClient!=NULL && !cliente_getId(bufferClient, &bufferClientId) && !ll_reduceInt(sellList, venta_sameId, bufferClientId, &currentCounter))
			{
				if(i==0 || minQty>currentCounter)
				{
					minQty = currentCounter;
				}
			}
		}
		printf("\nEl/los cliente/s con menos afiches es/son: \n");
		for(int i=0;i<ll_len(clientList);i++)
		{
			bufferClient = ll_get(clientList, i);
			if(bufferClient!=NULL && !cliente_getId(bufferClient, &bufferClientId) && !ll_reduceInt(sellList, venta_sameId, bufferClientId, &currentCounter))
			{
				if(currentCounter == minQty)
				{
					cliente_print(bufferClient);
				}
			}
		}
	}
	return retornar;
}

static int controller_sellMaxPosterQty(LinkedList* clientList, LinkedList* sellList)
{
	int retornar=-1;
	int bufferPosterQty;
	int maxPosterQty;
	int bufferIdSell;
	int bufferIdClient;
	int clientIndex;
	char bufferCuit[CUIT_SIZE];
	Venta* bufferSell;
	Cliente* bufferClient;
	if(clientList!=NULL && sellList!=NULL)
	{
		retornar=0;
		for(int i=0;i<ll_len(sellList);i++)
		{
			bufferSell = ll_get(sellList, i);
			if(bufferSell!=NULL && !venta_getPosterQty(bufferSell, &bufferPosterQty))
			{
				if(i==0 || maxPosterQty<bufferPosterQty)
				{
					maxPosterQty=bufferPosterQty;
				}
			}
		}
		printf("\nLa/las venta/s con mas afiches vendidos es/son: \n");
		for(int i=0;i<ll_len(sellList);i++)
		{
			bufferSell = ll_get(sellList, i);
			if(bufferSell!=NULL && !venta_getPosterQty(bufferSell, &bufferPosterQty))
			{
				if( bufferPosterQty==maxPosterQty && !venta_getClientId(bufferSell, &bufferIdClient) &&
					!venta_getSellId(bufferSell, &bufferIdSell)  && !controller_findByIdGen(clientList, cliente_getId, bufferIdClient, &clientIndex))
				{
					bufferClient = ll_get(clientList, clientIndex);
					if(bufferClient!=NULL && !cliente_getCuit(bufferClient, bufferCuit))
					{
						printf("\nID venta: %d - Cuit cliente: %s", bufferIdSell, bufferCuit);
					}
				}
			}
		}
	}
	return retornar;
}
