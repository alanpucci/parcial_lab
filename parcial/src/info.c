#include <stdio.h>
#include <stdlib.h>
#include "utn.h"
#include "cliente.h"
#include "advertisement.h"
#include "info.h"

/**
 * \brief Function to print each ad that a client has (searched by ID)
 * \param Client *clientList: Pointer to an Client array
 * \param int clientLen: Client array length
 * \param Advertisement *adList: Pointer to an Advertisement array
 * \param int adLen: Length of the array
 * \param int id: receive the ID to be search
 * \return (-1) if something went wrong, (0) if everything is OK
 */
int info_printAdsByClientID(Client *clientList, int clientLen, Advertisement *adList, int adLen, int id)
{
	int retorno=-1;
	int clientIndex;
	if(clientList!=NULL && clientLen>0 && adList!=NULL && adLen>0 && id>0)
	{
		if(client_findById(clientList, clientLen, id, &clientIndex)==0)
		{
			printf("\nID cliente: %d - Nombre: %s - Apellido: %s - CUIT: %s", clientList[clientIndex].id, clientList[clientIndex].name, clientList[clientIndex].lastName, clientList[clientIndex].cuit);
			if(advertisement_findByClientId(adList, adLen, clientList[clientIndex].id)==0)
			{
				for(int i=0;i<adLen;i++)
				{
					if(adList[i].clientID==clientList[clientIndex].id)
					{
						printf("\n> > > ID publicacion: %d - Estado: %d - texto: %s",adList[i].id, adList[i].isActive, adList[i].adText);
					}
				}
			}
			else
			{
				printf(" y no tiene anuncios");
			}
			retorno=0;
		}
		else
		{
			printf("\nCliente no encontrado");
		}
	}
	return retorno;
}

/**
 * \brief Function to print clients and how many active ads has
 * \param Client *clientList: Pointer to an Client array
 * \param int clientLen: Client array length
 * \param Advertisement *adList: Pointer to an Advertisement array
 * \param int adLen: Length of the array
 * \return (-1) if something went wrong, (0) if everything is OK
 */
int info_printClientsAndActiveAds(Client *clientList, int clientLen, Advertisement *adList, int adLen)
{
	int retornar = -1;
	int adCounter;
	if(clientList!=NULL && clientLen>0 && adList!=NULL && adLen>0 && client_searchForNoEmpty(clientList, clientLen)==0)
	{
		for(int i=0;i<clientLen;i++)
		{
			if(clientList[i].isEmpty == FALSE && advertisement_activeAdCounterEachClient(adList, adLen, clientList[i].id, &adCounter)==0)
			{
				printf("\nID cliente: %d - Nombre: %s - Apellido: %s - CUIT: %s - Cantidad de anuncios activos: %d", clientList[i].id, clientList[i].name, clientList[i].lastName, clientList[i].cuit, adCounter);
				retornar=0;
			}
		}
	}
	return retornar;
}

/**
 * \brief Function to report the client with more ads, how many paused ads are and the sector number with more ads
 * \param Client *clientList: Pointer to an Client array
 * \param int clientLen: Client array length
 * \param Advertisement *adList: Pointer to an Advertisement array
 * \param int adLen: Length of the array
 * \return (-1) if something went wrong, (0) if everything is OK
 */
int info_report(Client *clientList, int clientLen, Advertisement *adList, int adLen)
{
	int retornar = -1;
	int option;
	int adsCounter;
	if(clientList!=NULL && clientLen>0 && adList!=NULL && adLen>0 && client_searchForNoEmpty(clientList, clientLen)==0 && advertisement_searchForNoEmpty(adList, adLen)==0)
	{
		do
		{
			if(utn_getInt("\nElija una opcion: \n1)Cliente con mas avisos\n2)Cantidad de avisos pausados\n3)Rubro con mas avisos\n4)Salir ", "\nERROR! Elija una opcion valida", &option, 2, 1, 4)==0)
			{
				switch(option)
				{
				case 1:
					if(info_clientWithMaxAdQty(clientList, clientLen, adList, adLen)==0)
					{
						retornar=0;
					}
				break;
				case 2:
					if(advertisement_pausedAdsQty(adList, adLen, &adsCounter)==0)
					{
						printf("\nCantidad de avisos pausados: %d\n", adsCounter);
						retornar=0;
					}
					else
					{
						printf("\nNo hay avisos pausados\n");
					}
				break;
				case 3:
					if(advertisement_sectorMaxQtyAds(adList, adLen)==0)
					{
						retornar=0;
					}
					else
					{
						printf("\nNo hay rubros cargados\n");
					}
				break;
				}
			}
		}while(option != 4);
	}
	return retornar;
}

/**
 * \brief Function to find the client with more ads quantity
 * \param Client *clientList: Pointer to an Client array
 * \param int clientLen: Client array length
 * \param Advertisement *adList: Pointer to an Advertisement array
 * \param int adLen: Length of the array
 * \return (-1) if something went wrong, (0) if everything is OK
 */
int info_clientWithMaxAdQty(Client *clientList, int clientLen, Advertisement *adList, int adLen)
{
	int retornar=-1;
	int currentCounter;
	int maxCounter;
	int index;
	Client bufferMax;
	if(clientList!=NULL && clientLen>0 && adList!=NULL && adLen>0)
	{
		for(int i=0;i<clientLen;i++)
		{
			advertisement_adCounterEachClient(adList, adLen, clientList[i].id, &currentCounter);
			if(i==0 || currentCounter>maxCounter)
			{
				maxCounter = currentCounter;
				bufferMax = clientList[i];
			}
		}
		if(client_findById(clientList, clientLen, bufferMax.id, &index)==0)
		{
			printf("\nEl cliente con mas avisos es: %s %s, CUIT: %s\n", clientList[index].name, clientList[index].lastName, clientList[index].cuit);
			retornar = 0;
		}
	}
	return retornar;
}
