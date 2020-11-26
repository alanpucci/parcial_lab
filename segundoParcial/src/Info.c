#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Cliente.h"
#include "Linkedlist.h"
#include "parser.h"
#include "utn.h"
#include "Controller.h"
#include "Sale.h"

static int controller_clientMaxPosterQty(LinkedList* clientList, LinkedList* sellList);
static int controller_clientMinPosterQty(LinkedList* clientList, LinkedList* sellList);
static int controller_sellMaxPosterQty(LinkedList* clientList, LinkedList* sellList);

int controller_report(LinkedList* clientList, LinkedList* sellList)
{
	int retornar=-1;
	int choosenOption;
	LinkedList* bufferSaleList = ll_cloneFilter(sellList, sale_isNotSold);
	if(clientList!=NULL && sellList!=NULL)
	{
		if( !utn_getInt("\nIngrese una opcion:\n"
						"1)Cliente al que se le vendio mas afiches\n"
						"2)Cliente al que se le vendio menos afiches\n"
						"3)Sale con mas afiches vendidos\n"
						"4)Volver atras\n> > OPCION: ",
						"\nERROR!", &choosenOption, 2, 1, 4))
		{
			switch(choosenOption)
			{
			case 1:
				if(!controller_clientMaxPosterQty(clientList, bufferSaleList))
				{
					retornar=0;
				}
			break;
			case 2:
				if(!controller_clientMinPosterQty(clientList, bufferSaleList))
				{
					retornar=0;
				}
			break;
			case 3:
				if(!controller_sellMaxPosterQty(clientList, bufferSaleList))
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
			if(bufferClient!=NULL && !cliente_getId(bufferClient, &bufferClientId) && !ll_reduceInt(sellList, sale_sameIdCharged, bufferClientId, &currentCounter))
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
			if(bufferClient!=NULL && !cliente_getId(bufferClient, &bufferClientId) && !ll_reduceInt(sellList, sale_sameIdCharged, bufferClientId, &currentCounter))
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
			if(bufferClient!=NULL && !cliente_getId(bufferClient, &bufferClientId) && !ll_reduceInt(sellList, sale_sameIdCharged, bufferClientId, &currentCounter))
			{
				if((i==0 || minQty>currentCounter))
				{
					minQty = currentCounter;
				}
			}
		}
		printf("\nEl/los cliente/s con menos afiches es/son: \n");
		for(int i=0;i<ll_len(clientList);i++)
		{
			bufferClient = ll_get(clientList, i);
			if(bufferClient!=NULL && !cliente_getId(bufferClient, &bufferClientId) && !ll_reduceInt(sellList, sale_sameIdCharged, bufferClientId, &currentCounter))
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
	int bufferIdSale;
	int bufferIdClient;
	int clientIndex;
	char bufferCuit[CUIT_SIZE];
	int bufferState;
	Sale* bufferSale;
	Cliente* bufferClient;
	if(clientList!=NULL && sellList!=NULL)
	{
		retornar=0;
		for(int i=0;i<ll_len(sellList);i++)
		{
			bufferSale = ll_get(sellList, i);
			if(bufferSale!=NULL && !sale_getPosterQty(bufferSale, &bufferPosterQty) && !sale_getState(bufferSale, &bufferState))
			{
				if((i==0 || maxPosterQty<bufferPosterQty) && bufferState==1)
				{
					maxPosterQty=bufferPosterQty;
				}
			}
		}
		printf("\nLa/las venta/s con mas afiches vendidos es/son: \n");
		for(int i=0;i<ll_len(sellList);i++)
		{
			bufferSale = ll_get(sellList, i);
			if(bufferSale!=NULL && !sale_getPosterQty(bufferSale, &bufferPosterQty) && !sale_getState(bufferSale, &bufferState))
			{
				if( bufferPosterQty==maxPosterQty && bufferState==1 && !sale_getClientId(bufferSale, &bufferIdClient) &&
					!sale_getSaleId(bufferSale, &bufferIdSale)  && !controller_findByIdGen(clientList, cliente_getId, bufferIdClient, &clientIndex))
				{
					bufferClient = ll_get(clientList, clientIndex);
					if(bufferClient!=NULL && !cliente_getCuit(bufferClient, bufferCuit))
					{
						printf("\nID venta: %d - Cuit cliente: %s", bufferIdSale, bufferCuit);
					}
				}
			}
		}
	}
	return retornar;
}
