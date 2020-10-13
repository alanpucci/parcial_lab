#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>

#include "advertisement.h"
#include "cliente.h"
#include "info.h"
#include "utn.h"

static int idGenerate(void);

/**
 * \brief Function to add an Advertisement asking for the client ID, sector number, and the ad text
 * \param Advertisement *list: Pointer to an Advertisement array
 * \param int len: Advertisement array length
 * \param Client *clientList: Pointer to an Client array
 * \param int clientLen: Client array length
 * \return (-1) if something went wrong, (0) if everything is OK.
 */
int advertisement_add(Advertisement *list, int len, Client *clientList, int clientLen)
{
	int retornar = -1;
	Advertisement buffer;
	int index;
	int clientIndex;
	if(list != NULL && len > 0 && client_searchForNoEmpty(clientList, clientLen) == 0)
	{
		if(advertisement_searchEmpty(list, len, &index) == 0 && index >= 0 && client_print(clientList, clientLen) == 0 &&
		   utn_getInt("\n\nIngrese el ID del cliente: ", "\nERROR! Ingrese un ID valido: ", &buffer.clientID, 2, 1, 9999)==0 &&
		   client_findById(clientList, clientLen, buffer.clientID, &clientIndex) == 0 &&
		   utn_getInt("\nIngrese el numero de rubro: ", "\nERROR! Ingrese un numero de rubro valido: ", &buffer.sector, 2, SECTOR_MIN, SECTOR_MAX)==0 &&
		   utn_getStringAlphanumeric("\nIngrese el texto del aviso: ", "\nERROR! Ingrese caracteres validos: ", buffer.adText, 2, ADTEXT_SIZE)==0)
		{
			buffer.id = idGenerate();
			buffer.isEmpty = FALSE;
			buffer.isActive = TRUE;
			list[index] = buffer;
			retornar = 0;
			printf("\nID para el nuevo aviso: %d", list[index].id);
		}
	}
	return retornar;
}

/**
 * \brief Function pause an advertisement searched by ID (put isActive field on FALSE)
 * \param Advertisement *list: Pointer to an Advertisement array
 * \param int len: Length of the array
 * \param Client *clientList: Pointer to an Client array
 * \param int clientLen: Client array length
 * \return (-1) if something went wrong, (0) if everything is OK.
 */

int advertisement_pauseAd(Advertisement *list, int len, Client *clientList, int clientLen)
{
	int retornar = -1;
	int id;
	int index;
	int choosedOption;
	if(list != NULL && len > 0 && clientList != NULL && clientLen>0 && advertisement_searchForNoEmpty(list, len) == 0 && advertisement_searchForActive(list, len) == 1)
	{
		advertisement_print(list, len);
		if(utn_getInt("\n\nIngrese el id de la publicacion a pausar: ", "\nError! Ingrese un ID valido: ", &id, 2, 1, 999) == 0 && advertisement_findById(list, len, id, &index)==0 &&
		   list[index].isActive == TRUE && advertisement_printClientInfoByAdId(list, len, clientList, clientLen, id) == 0 &&
		   utn_getInt("\n\nQuiere pausar esta publicidad? presione 1 para SI o 2 para NO: " , "\nERROR! Ingrese 1 o 2 ", &choosedOption, 2, 1, 2)==0 && choosedOption == 1)
		{
			list[index].isActive = FALSE;
			retornar = 0;
		}
	}
	return retornar;
}

/**
 * \brief Function reanude an advertisement searched by ID (put isActive field on TRUE)
 * \param Advertisement *list: Pointer to an Advertisement array
 * \param int len: Length of the array
 * \param Client *clientList: Pointer to an Client array
 * \param int clientLen: Client array length
 * \return (-1) if something went wrong, (0) if everything is OK.
 */
int advertisement_reanudeAd(Advertisement *list, int len, Client *clientList, int clientLen)
{
	int retornar = -1;
	int id;
	int index;
	int choosedOption;
	if(list != NULL && len > 0 && clientList != NULL && clientLen>0 && advertisement_searchForNoEmpty(list, len) == 0 && advertisement_searchForActive(list, len) == 0)
	{
		advertisement_print(list, len);
		if(utn_getInt("\nIngrese el id de la publicacion a reanudar: ", "\nError! Ingrese un ID valido: ", &id, 2, 1, 999) == 0 && advertisement_findById(list, len, id, &index)==0 &&
		   list[index].isActive == FALSE && advertisement_printClientInfoByAdId(list, len, clientList, clientLen, id) == 0 &&
		   utn_getInt("\n\nQuiere reanudar esta publicidad? presione 1 para SI o 2 para NO: ", "\nERROR! Ingrese 1 o 2 ", &choosedOption, 2, 1, 2)==0 && choosedOption == 1)
		{
			list[index].isActive = TRUE;
			retornar = 0;
		}
	}
	return retornar;
}

/**
 * \brief Function to remove an advertisement searched by ID
 * \param Advertisement *list: Pointer to an Advertisement array
 * \param int len: Length of the array
 * \param int id: receive the ID to be search
 * \return (-1) if something went wrong, (0) if everything is OK
*/
int advertisement_remove(Advertisement *list, int len, int id)
{
	int retornar = -1;
	if(list!=NULL && len>0)
	{
		for(int i=0;i<len;i++)
		{
			if(advertisement_findByClientId(list, len, id)>-1)
			{
				list[i].isEmpty = TRUE;
			}
		}
		retornar = 0;
	}
	return retornar;
}

/**
 * \brief Function to print a client info searched by an advertisement ID
 * \param Advertisement *list: Pointer to an Advertisement array
 * \param int len: Length of the array
 * \param Client *clientList: Pointer to an Client array
 * \param int clientLen: Client array length
 * \param int id: receive the ID to be search
 * \return (-1) if something went wrong, (0) if everything is OK
 */
int advertisement_printClientInfoByAdId(Advertisement *list, int len, Client *clientList, int clientLen, int id)
{
	int retornar=-1;
	int index;
	if(list!=NULL && len>0 && clientList!=NULL && clientLen>0 && clientLen>0 && id>0 && client_findById(clientList, len, id, &index)==0)
	{
		printf("\nCliente: \nNombre: %s - Apellido: %s - Cuit: %s", clientList[index].name, clientList[index].lastName, clientList[index].cuit);
		retornar = 0;
	}
	return retornar;
}


/**
 * \brief Function to print all the Advertisements in the array
 * \param Advertisement *list: Pointer to an Advertisement array
 * \param int len: Length of the array
 * \return (-1) if something went wrong, (0) if everything is OK
 */
int advertisement_print(Advertisement *list, int len)
{
	int retorno = -1;
	if(list != NULL && len > 0)
	{
		printf("\n|| ESTADO: || 1 = activo || 0 = pausado ||");
		for(int i=0;i<len;i++)
		{
			if(list[i].isEmpty == FALSE)
			{
				printf("\nID: %d - Estado: %d - texto: %s",list[i].id, list[i].isActive,list[i].adText);
				retorno = 0;
			}
		}
	}
	return retorno;
}

/**
 * \brief Function to count how many ads has a client searched by ID
 * \param Advertisement *list: Pointer to an Advertisement array
 * \param int len: Length of the array
 * \param int id: receive the ID to be search
 * \param int *pCounter: Pointer of the counter
 * \return (-1) if something went wrong, (0) if everything is OK
 */
int advertisement_adCounterPerClient(Advertisement *adList, int adLen, int id, int *pCounter)
{
	int retornar=-1;
	int counter=0;
	if(adList!=NULL && adLen>0)
	{
		for(int i=0;i<adLen;i++)
		{
			if(adList[i].clientID == id)
			{
				counter++;
			}
		}
		*pCounter = counter;
		retornar = 0;
	}
	return retornar;
}

/**
 * \brief Function to count how many active ads has a client searched by ID
 * \param Advertisement *list: Pointer to an Advertisement array
 * \param int len: Length of the array
 * \param int id: receive the ID to be search
 * \param int *pCounter: Pointer of the counter
 * \return (-1) if something went wrong, (0) if everything is OK
 */
int advertisement_activeAdCounterPerClient(Advertisement *adList, int adLen, int id, int *pCounter)
{
	int retornar=-1;
	int counter=0;
	if(adList!=NULL && adLen>0)
	{
		for(int i=0;i<adLen;i++)
		{
			if(adList[i].clientID == id && adList[i].isActive == TRUE)
			{
				counter++;
			}
		}
		*pCounter = counter;
		retornar = 0;
	}
	return retornar;
}

/**
 * \brief Function to count how many paused ads have an Advertisement array
 * \param Advertisement *list: Pointer to an Advertisement array
 * \param int len: Length of the array
 * \param int *pCounter: Pointer of the counter
 * \return (-1) if something went wrong, (0) if everything is OK
 */
int advertisement_pausedAdsQty(Advertisement *adList, int adLen, int *pCounter)
{
	int retornar=-1;
	int counter=0;
	if(adList!=NULL && adLen>0)
	{
		for(int i=0;i<adLen;i++)
		{
			if(adList[i].isActive == FALSE)
			{
				counter++;
				retornar=0;
			}
		}
		*pCounter = counter;
	}
	return retornar;
}

/**
 * \brief Function to search in the advertisement array for an no empty field
 * \param Advertisement *list: Pointer to an Advertisement array
 * \param int len: Length of the array
 * \return (-1) if something went wrong, (0) if everything is OK
 */
int advertisement_searchForNoEmpty(Advertisement *list, int len)
{
	int retornar = -1;
	if(list != NULL && len > 0)
	{
		for(int i=0; i<len; i++)
		{
			if(list[i].isEmpty == FALSE)
			{
				retornar = 0;
				break;
			}
		}
	}
	return retornar;
}

/**
 * \brief Function to search in the advertisement array if there's any active
 * \param Advertisement *list: Pointer to an Advertisement array
 * \param int len: Length of the array
 * \return (1) is there any active field TRUE or (0) if not
 */
int advertisement_searchForActive(Advertisement *list, int len)
{
	int retornar = 0;
	if(list != NULL && len > 0)
	{
		for(int i=0; i<len; i++)
		{
			if(list[i].isActive == TRUE)
			{
				retornar = 1;
				break;
			}
		}
	}
	return retornar;
}

/**
 * \brief Function to init isEmpty to TRUE and -1 to ID field of an Advertisement array
 * \param Advertisement *list: Pointer to an Advertisement array
 * \param int len: Length of the array
 * \return (-1) if something went wrong, (0) if everything is OK
 */
int advertisement_init(Advertisement* list, int len)
{
	int retornar = -1;
	if(list != NULL && len > 0)
	{
		for(int i=0;i<len;i++)
		{
			list[i].isEmpty = TRUE;
			list[i].isActive = -1;
			list[i].id = -1;
		}
		retornar = 0;
	}
	return retornar;
}

/**
 * \brief Function that returns the first index found on an Advertisement array that is empty
 * \param Advertisement *list: Pointer to an Advertisement array
 * \param int len: Length of the array
 * \param int *pIndex: pointer of the index
 * \return (-1) if something went wrong, (0) if everything is OK
 */
int advertisement_searchEmpty(Advertisement *list, int len, int *pIndex)
{
	int retornar = -1;
	if(list != NULL)
	{
		for(int i = 0; i < len; i++)
		{
			if(list[i].isEmpty == TRUE && list[i].id == -1)
			{
				retornar = 0;
				*pIndex = i;
				break;
			}
		}
	}
	return retornar;
}

/**
 * \brief Function to auto-generate an ID
 * \return the id
 */
static int idGenerate(void)
{
	static int id=0;
	id = id+1;
	return id;
}

/**
 * \brief Function to find an Advertisement index receiving an id
 * \param Advertisement *list: Pointer to an Advertisement array
 * \param int len: Length of the array
 * \param int id: receive the id to be searched
 * \return the index or (-1) if something went wrong
 */
int advertisement_findById(Advertisement *list, int len, int id, int *pIndex)
{
	int retornar = -1;
	if(list != NULL && len > 0 && id > 0)
	{
		for(int i=0; i < len; i++)
		{
			if(list[i].id==id && list[i].isEmpty==FALSE && (list[i].isActive==TRUE || list[i].isActive==FALSE))
			{
				*pIndex = i;
				retornar = 0;
				break;
			}
		}
	}
	return retornar;
}

/**
 * \brief Function to find an Advertisement index receiving a client ID
 * \param Advertisement *list: Pointer to an Advertisement array
 * \param int len: Length of the array
 * \param int id: receive the id to be searched
 * \return the index or (-1) if something went wrong
 */
int advertisement_findByClientId(Advertisement *list, int len, int id)
{
	int retornar = -1;
	if(list != NULL && len > 0 && id > 0)
	{
		for(int i=0;i<len;i++)
		{
			if(list[i].clientID==id && list[i].isEmpty==FALSE && (list[i].isActive==TRUE || list[i].isActive==FALSE))
			{
				retornar = i;
				break;
			}
		}
	}
	return retornar;
}

/**
 * \brief Function to compare sectors counter and find the max
 * \param Advertisement *list: Pointer to an Advertisement array
 * \param int len: Length of the array
 * \return the index or (-1) if something went wrong
 */
int advertisement_sectorMaxQtyAds(Advertisement *list, int len)
{
	int retornar=-1;
	int currentCounter=0;
	int maxCounter;
	Advertisement aux;
	if(list!=NULL && len>0)
	{
		for(int i=0;i<len;i++)
		{
			if(list[i].isEmpty == FALSE && advertisement_equalSectorQty(list,len,list[i].sector, &currentCounter)==0)
			{
				if(i==0 || currentCounter>maxCounter)
				{
					maxCounter = currentCounter;
					aux = list[i];
					retornar=0;
				}
			}
		}
		printf("\nEl rubro con mas avisos es el: %d\n", aux.sector);
	}
	return retornar;
}

/**
 * \brief Function to count how many times a sector is repeated in the Advertisement array
 * \param Advertisement *list: Pointer to an Advertisement array
 * \param int len: Length of the array
 * \param int sector: receive the sector to be searched
 * \param int *pCounter: pointer of the counter
 * \return the index or (-1) if something went wrong
 */
int advertisement_equalSectorQty(Advertisement *list, int len, int sector, int *pCounter)
{
	int retornar=-1;
	int counter=0;
	if(list!=NULL && len>0)
	{
		for(int i=0;i<len;i++)
		{
			if(list[i].isEmpty == FALSE && list[i].sector == sector)
			{
				counter++;
				retornar=0;
			}
		}
		*pCounter = counter;
	}
	return retornar;
}
