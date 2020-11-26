#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Cliente.h"
#include "Sale.h"
#include "Linkedlist.h"
#include "parser.h"
#include "utn.h"
#include "Controller.h"
#define BUFFER_SIZE 4096

static int controller_searchMaxId(LinkedList* list, int (*pFunc)(void*,int*));
static int controller_isCuitRegistered(LinkedList* clientList, char* cuit);

/** \brief Cargar los clientes desde un archivo que recibimos por parametro
 * \param char* path: Recibimos el nombre del archivo
 * \param LinkedList* clientList: Puntero a la lista de clientes
 * \return (-1) si algo salio mal (0) si Ok
 */
int controller_loadClientFromText(char* path, LinkedList* clientList)
{
	int retornar=-1;
	FILE* pFile;
	if(path!=NULL && clientList!=NULL)
	{

		pFile = fopen(path, "r");
		if(pFile!=NULL && !parser_clientFromText(pFile, clientList))
		{
			retornar=0;
		}
		else
		{
			printf("\nEl archivo no existe");
		}
		fclose(pFile);
	}
    return retornar;
}

/** \brief Cargar las ventas desde un archivo que recibimos por parametro
 * \param char* path: Recibimos el nombre del archivo
 * \param LinkedList* sellList: Puntero a la lista de ventas
 * \return (-1) si algo salio mal (0) si Ok
 */
int controller_loadSaleFromText(char* path, LinkedList* sellList)
{
	int retornar=-1;
	FILE* pFile;
	if(path!=NULL && sellList!=NULL)
	{

		pFile = fopen(path, "r");
		if(pFile!=NULL && !parser_sellFromText(pFile, sellList))
		{
			retornar=0;
		}
		else
		{
			printf("\nEl archivo no existe");
		}
		fclose(pFile);
	}
    return retornar;
}

/** \brief Agregar un cliente a nuestra lista de clientes
 * \param LinkedList* clientList: Puntero a la lista de clientes
 * \return (-1) si algo salio mal (0) si Ok
 */
int controller_addClient(LinkedList* clientList)
{
	int retornar=-1;
	char bufferName[NAME_SIZE];
	char bufferLastName[NAME_SIZE];
	char bufferCuit[CUIT_SIZE];
	int bufferId;
	Cliente* bufferClient;
	if(clientList!=NULL)
	{
		if( !utn_getString("Ingrese el nombre del nuevo cliente: ", "\nERROR!", bufferName, 2, NAME_SIZE) &&
			!utn_getString("Ingrese el apellido del cliente: ", "\nERROR!", bufferLastName, 2, NAME_SIZE) &&
			!utn_getCuit("Ingrese el cuit del nuevo cliente: ", "\nERROR!", bufferCuit, 2, CUIT_SIZE))
		{
			if(!controller_isCuitRegistered(clientList, bufferCuit))
			{
				retornar=0;
				bufferId = controller_searchMaxId(clientList, cliente_getId);
				printf("\nID para el nuevo cliente: %d", bufferId);
				bufferClient = cliente_newWithParameters(bufferId, bufferName, bufferLastName, bufferCuit);
				ll_add(clientList, bufferClient);
			}
			else
			{
				printf("\nCuit ya registrado");
			}
		}
		else
		{
			printf("\nError en la obtencion de los datos");
		}
	}
	return retornar;
}

/** \brief Agregar una venta a nuestra lista de ventas
 * \param LinkedList* clientList: Puntero a la lista de clientes
 * \param LinkedList* sellList: Puntero a la lista de ventas
 * \return (-1) si algo salio mal (0) si Ok
 */
int controller_addSale(LinkedList* clientList, LinkedList* sellList)
{
	int retornar=-1;
	int bufferIdClient;
	int bufferIdSale;
	int index;
	int bufferPosterQty;
	char bufferFileName[POSTER_SIZE];
	int bufferZone;
	Sale* bufferSale;
	if(clientList!=NULL)
	{
		if( !controller_print(clientList, cliente_print) && !utn_getInt("\nIngrese el ID del cliente: ", "\nERROR!", &bufferIdClient, 2, 1, 999999) &&
			!controller_findByIdGen(clientList, cliente_getId, bufferIdClient, &index))
		{
			if( !utn_getInt("\nIngrese la cantidad de afiches a vender: ", "\nERROR!", &bufferPosterQty, 2, 1, 99999) &&
				!utn_getStringAlphanumeric("\nIngrese el nombre del archivo: ", "\nERROR!", bufferFileName, 2, POSTER_SIZE) &&
				!utn_getInt("\nIngrese la zona donde se pegaran los afiches: \n1)CABA\n2)ZONA SUR\n3)ZONA OESTE", "\nERROR!", &bufferZone, 2, 1, 3))
			{
				retornar=0;
				bufferIdSale = controller_searchMaxId(sellList, sale_getSaleId);
				printf("\nID para la venta: %d", bufferIdSale);
				bufferSale = sale_newWithParameters(bufferIdClient, bufferIdSale, bufferPosterQty, bufferFileName, bufferZone, 0);
				ll_add(sellList, bufferSale);
			}
			else
			{
				printf("\nError en la obtencion de datos");
			}
		}
		else
		{
			printf("\nID cliente no existente");
		}
	}
	return retornar;
}

/** \brief Modificar una venta NO cobrada
 * \param LinkedList* clientList: Puntero a la lista de clientes
 * \param LinkedList* sellList: Puntero a la lista de ventas
 * \return (-1) si algo salio mal (0) si Ok
 */
int controller_modifySale(LinkedList* clientList, LinkedList* sellList)
{
	int retornar=-1;
	LinkedList* bufferSaleList;
	int bufferId;
	int indexSale;
	int indexClient;
	Cliente* bufferClient;
	Sale* bufferSale;
	int choosenOption;
	int bufferInt;
	char bufferString[POSTER_SIZE];
	if(clientList!=NULL && sellList!=NULL)
	{
		bufferSaleList = ll_cloneFilter(sellList, sale_isSold);
		if( !controller_print(bufferSaleList, sale_print) && !utn_getInt("\nIngrese el ID de la venta a modificar: ", "\nERROR!", &bufferId, 2, 1, 99999) &&
			!controller_findByIdGen(sellList, sale_getSaleId, bufferId, &indexSale))
		{
			bufferSale = ll_get(sellList, indexSale);
			if(sale_isSold(bufferSale) && !sale_getClientId(bufferSale, &bufferId) && !controller_findByIdGen(clientList, cliente_getId, bufferId, &indexClient))
			{
				bufferClient = ll_get(clientList, indexClient);
				cliente_print(bufferClient);
				if( !utn_getInt("\n\nIngrese el campo a modificar:\n1)Cantidad de afiches\n2)Nombre del archivo\n3)Zona\n4)Volver atras\n> > OPCION: ", "\nERROR!", &choosenOption, 2, 1, 4))
				{
					switch(choosenOption)
					{
						case 1:
							if( !utn_getInt("\nIngrese la nueva cantidad de afiches: ", "\nERROR!", &bufferInt, 2, 1, 999999) && !sale_setPosterQty(bufferSale, bufferInt))
							{
								ll_set(sellList, indexSale, bufferSale);
								retornar=0;
							}
						break;
						case 2:
							if( !utn_getStringAlphanumeric("\nIngrese el nuevo nombre del archivo: ", "\nERROR!", bufferString, 2, POSTER_SIZE) &&
								!sale_setFileName(bufferSale, bufferString))
							{
								ll_set(sellList, indexSale, bufferSale);
								retornar=0;
							}
						break;
						case 3:
							if( !utn_getInt("\nIngrese la nueva zona: ", "\nERROR!", &bufferInt, 2, 1, 3) && !sale_setZone(bufferSale, bufferInt))
							{
								ll_set(sellList, indexSale, bufferSale);
								retornar=0;
							}
						break;
					}
				}
			}
			else
			{
				printf("\nID de venta 'a cobrar' no encontrado!\n");
			}
		}
		else
		{
			printf("\nID no encontrado!\n");
		}
	}
	return retornar;
}

/** \brief Cobrar una venta NO cobrada
 * \param LinkedList* clientList: Puntero a la lista de clientes
 * \param LinkedList* sellList: Puntero a la lista de ventas
 * \return (-1) si algo salio mal (0) si Ok
 */
int controller_chargePoster(LinkedList* clientList, LinkedList* sellList)
{
	int retornar=-1;
	LinkedList* bufferSaleList;
	int bufferId;
	int indexSale;
	int indexClient;
	Cliente* bufferClient;
	Sale* bufferSale;
	int bufferInt;
	if(clientList!=NULL && sellList!=NULL)
	{
		bufferSaleList = ll_cloneFilter(sellList, sale_isSold);
		if( !controller_print(bufferSaleList, sale_print) && !utn_getInt("\nIngrese el ID de la venta a cobrar: ", "\nERROR!", &bufferId, 2, 1, 99999) &&
			!controller_findByIdGen(sellList, sale_getSaleId, bufferId, &indexSale))
		{
			bufferSale = ll_get(sellList, indexSale);
			if(sale_isSold(bufferSale) && !sale_getClientId(bufferSale, &bufferId) && !controller_findByIdGen(clientList, cliente_getId, bufferId, &indexClient))
			{
				bufferClient = ll_get(clientList, indexClient);
				cliente_print(bufferClient);
				if( !utn_getInt("\n\nDesea cobrar esta venta?\nPresione 1 para cobrar o 2 para volver atras: ", "\nERROR!", &bufferInt, 2, 1, 2) &&
					bufferInt==1 && !sale_setState(bufferSale, 1))
				{
					ll_set(sellList, indexSale, bufferSale);
					retornar=0;
				}
				else
				{
					printf("\nVenta NO cobrada\n");
				}
			}
			else
			{
				printf("\nID no encontrado!\n");
			}
		}
		else
		{
			printf("\nID no encontrado!\n");
		}
	}
	return retornar;
}


/** \brief Guardar en un archivo los clientes con las ventas NO cobradas
 * \param LinkedList* clientList: Puntero a la lista de clientes
 * \param LinkedList* sellList: Puntero a la lista de ventas
 * \return (-1) si algo salio mal (0) si Ok
 */
int controller_saveClientsWithUnchargedPosters(LinkedList* clientList, LinkedList* sellList)
{
	int retornar=-1;
	Cliente* bufferClient;
	FILE* pFile;
	LinkedList* bufferSaleList;
	int counter;
	int bufferId;
	char bufferName[NAME_SIZE];
	char bufferLastName[NAME_SIZE];
	char bufferCuit[CUIT_SIZE];
	if(clientList!=NULL && sellList!=NULL)
	{
		bufferSaleList = ll_cloneFilter(sellList, sale_isSold);
		pFile = fopen("a_cobrar.txt", "w");
		if(pFile!=NULL)
		{
			fprintf(pFile, "id,nombre,apellido,cuit,ventas_a_cobrar\n");
			for(int i=0;i<ll_len(clientList);i++)
			{
				bufferClient = ll_get(clientList, i);
				if( !cliente_getId(bufferClient, &bufferId) && !cliente_getName(bufferClient, bufferName) &&
					!cliente_getLastName(bufferClient, bufferLastName) && !cliente_getCuit(bufferClient, bufferCuit))
				{
					if(!ll_reduceInt(bufferSaleList, sale_sameId, bufferId ,&counter) && counter!=0)
					{
						fprintf(pFile, "%d,%s,%s,%s,%d\n", bufferId, bufferName, bufferLastName, bufferCuit, counter);
					}
				}
			}
		}
		retornar=0;
		fclose(pFile);
	}
	return retornar;
}

/** \brief Guardar en un archivo los clientes con las ventas cobradas
 * \param LinkedList* clientList: Puntero a la lista de clientes
 * \param LinkedList* sellList: Puntero a la lista de ventas
 * \return (-1) si algo salio mal (0) si Ok
 */
int controller_saveClientsWithChargedPosters(LinkedList* clientList, LinkedList* sellList)
{
	int retornar=-1;
	Cliente* bufferClient;
	FILE* pFile;
	LinkedList* bufferSaleList;
	int counter;
	int bufferId;
	char bufferName[NAME_SIZE];
	char bufferLastName[NAME_SIZE];
	char bufferCuit[CUIT_SIZE];
	if(clientList!=NULL && sellList!=NULL)
	{
		bufferSaleList = ll_cloneFilter(sellList, sale_isNotSold);
		pFile = fopen("cobrados.txt", "w");
		if(pFile!=NULL)
		{
			fprintf(pFile, "id,nombre,apellido,cuit,ventas_cobradas\n");
			for(int i=0;i<ll_len(clientList);i++)
			{
				bufferClient = ll_get(clientList, i);
				if( !cliente_getId(bufferClient, &bufferId) && !cliente_getName(bufferClient, bufferName) &&
					!cliente_getLastName(bufferClient, bufferLastName) && !cliente_getCuit(bufferClient, bufferCuit))
				{
					if(!ll_reduceInt(bufferSaleList, sale_sameId, bufferId ,&counter) && counter!=0)
					{
						fprintf(pFile, "%d,%s,%s,%s,%d\n", bufferId, bufferName, bufferLastName, bufferCuit, counter);
					}
				}
			}
		}
		retornar=0;
		fclose(pFile);
	}
	return retornar;
}

/** \brief Busca en la lista de empleados el maximo id y retorna ese valor + 1
 * \param LinkedList* list: Puntero a la lista
 * \param int pFunc: Funcion criterio que recibe dos parametros
 * \return el valor del maximo id encontrado + 1 o (-1) si algo salio mal
 */
static int controller_searchMaxId(LinkedList* list, int (*pFunc)(void*,int*))
{
	int retornar=-1;
	int len = ll_len(list);
	void* bufferEntity;
	int id;
	int maxId;
	if(list!=NULL)
	{
		for(int i=0;i<len;i++)
		{
			bufferEntity = ll_get(list, i);
			if(!pFunc(bufferEntity, &id))
			{
				if(i==0 || id>maxId)
				{
					maxId = id;
				}
			}
		}
		retornar = maxId+1;
	}
	return retornar;
}

/** \brief Busca en la lista el id que pasamos por parametro y compara a traves de una funcion criterio, devuelve el indice por referencia
 * \param LinkedList* list: Puntero a la lista
 * \param int pFunc: Funcion criterio que recibe dos parametros
 * \param int id: Recibimos el id a comparar
 * \param int* index: Devolvemos por referencia el indice encontrado
 * \return (-1) si algo salio mal o (0) si OK
 */
int controller_findByIdGen(LinkedList* list, int (*pFunc)(void*,int*), int id, int* index)
{
	int retornar=-1;
	int len = ll_len(list);
	int bufferId;
	void* bufferEntity;
	if(list!=NULL && id>0 && index!=NULL)
	{
		for(int i=0;i<len;i++)
		{
			bufferEntity = ll_get(list, i);
			if(!pFunc(bufferEntity, &bufferId) && bufferId == id)
			{
				retornar = 0;
				*index = i;
				break;
			}
		}
	}
	return retornar;
}

/** \brief Funcion para verificar si el cuit que recibimos por parametro ya es de un cliente existente
 * \param LinkedList* clientList: Puntero a la lista de clientes
 * \param char* cuit: Recibimos el cuit a comparar
 * \return (-1) si algo salio mal o (0) si OK
 */
static int controller_isCuitRegistered(LinkedList* clientList, char* cuit)
{
	int retornar=-1;
	Cliente* bufferClient;
	char bufferCuit[CUIT_SIZE];
	if(clientList!=NULL && cuit!=NULL)
	{
		retornar=0;
		for(int i=0;i<ll_len(clientList);i++)
		{
			bufferClient = ll_get(clientList, i);
			if(bufferClient!=NULL && !cliente_getCuit(bufferClient, bufferCuit))
			{
				if(!strncmp(bufferCuit, cuit,CUIT_SIZE))
				{
					retornar=1;
				}
			}
		}
	}
	return retornar;
}

/** \brief Funcion para imprimir una lista
 * \param LinkedList* clientList: Puntero a la lista de clientes
 * \param pFunc: funcion criterio para determinar que lista imprimimos
 * \return (-1) si algo salio mal o (0) si OK
 */
int controller_print(LinkedList* list, int (*pFunc)(void*))
{
	int retornar=-1;
	if(list!=NULL && pFunc!=NULL)
	{
		retornar=0;
		ll_map(list, pFunc);
		printf("\n---------------------------------------------------------------------\n");
	}
	return retornar;
}

/** \brief Funcion para guardar la lista de los clientes en un archivo como texto
 * \param char* path: Recibimos la direccion del archivo donde vamos a guardar
 * \param LinkedList* clientList: Puntero a la lista de clientes
 * \return (-1) si algo salio mal o (0) si OK
 */
int controller_saveClientAsText(char* path, LinkedList* clientList)
{
	int retornar=-1;
	FILE* pFile;
	Cliente* bufferClient;
	int bufferId;
	char bufferName[NAME_SIZE];
	char bufferLastName[NAME_SIZE];
	char bufferCuit[CUIT_SIZE];
	if(path!=NULL && clientList!=NULL)
	{
		pFile = fopen(path, "w");
		if(pFile!=NULL)
		{
			fprintf(pFile, "id,nombre,apellido,cuit\n");
			retornar=0;
			for(int i=0;i<ll_len(clientList);i++)
			{
				bufferClient = ll_get(clientList, i);
				if(bufferClient!=NULL)
				{
					if( !cliente_getId(bufferClient, &bufferId) && !cliente_getName(bufferClient, bufferName) &&
						!cliente_getLastName(bufferClient, bufferLastName) && !cliente_getCuit(bufferClient, bufferCuit))
					{
						fprintf(pFile, "%d,%s,%s,%s\n",bufferId, bufferName, bufferLastName, bufferCuit);

					}

				}
			}

		}
		fclose(pFile);
	}
	return retornar;
}

/** \brief Funcion para guardar la lista de las ventas en un archivo como texto
 * \param char* path: Recibimos la direccion del archivo donde vamos a guardar
 * \param LinkedList* sellList: Puntero a la lista de ventas
 * \return (-1) si algo salio mal o (0) si OK
 */
int controller_saveSalesAsText(char* path, LinkedList* sellList)
{
	int retornar=-1;
	FILE* pFile;
	Sale* bufferSale;
	int bufferIdSale;
	int bufferIdClient;
	int bufferPosterQty;
	char bufferFileName[POSTER_SIZE];
	int bufferZone;
	int bufferState;
	if(path!=NULL && sellList!=NULL)
	{
		pFile = fopen(path, "w");
		if(pFile!=NULL)
		{
			fprintf(pFile, "id_venta,id_cliente,cantidad_afiches,nombre_archivo,zona,estado\n");
			retornar=0;
			for(int i=0;i<ll_len(sellList);i++)
			{
				bufferSale = ll_get(sellList, i);
				if( !sale_getSaleId(bufferSale, &bufferIdSale) && !sale_getClientId(bufferSale, &bufferIdClient) && !sale_getPosterQty(bufferSale, &bufferPosterQty) &&
					!sale_getFileName(bufferSale, bufferFileName) && !sale_getZone(bufferSale, &bufferZone) && !sale_getState(bufferSale, &bufferState))
				{
					fprintf(pFile, "%d,%d,%d,%s,%d,%d\n",bufferIdSale,bufferIdClient,bufferPosterQty,bufferFileName,bufferZone,bufferState);
				}
			}
		}
		fclose(pFile);
	}
	return retornar;
}
