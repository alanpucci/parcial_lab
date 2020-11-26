#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Sale.h"
#define BUFFER_SIZE 4096

static int isValidInt(char* string);
static int isAlphaNumeric(char* pResultado);


/** \brief Uso de malloc para obtener una nueva direccion de memoria
 * 	\return la nueva direccion de memoria
 */
Sale* sale_new()
{
	return (Sale*) malloc(sizeof(Sale));
}

/** \brief Dar de alta una venta recibiendo los parametros
 * \param int clientId: Recibo el id del cliente
 * \param int posterId: Recibo el id de la venta
 * \param int posterQty: Recibo la cantidad de afiches
 * \param char* posterName: Recibo el nombre del archivo
 * \param int zone: Recibo la localidad
 * \param int state: Recibo el estado de la venta
 * \return la direccion de memoria de la venta con todos sus datos cargados o NULL en caso de que algo haya salido mal
 */
Sale* sale_newWithParameters(int clientId, int posterId, int posterQty, char* posterName, int zone, int state)
{
	Sale* this = sale_new();
	if(this!=NULL)
	{
		if( !sale_setClientId(this, clientId) && !sale_setSaleId(this, posterId) && !sale_setPosterQty(this, posterQty) &&
			!sale_setFileName(this, posterName) && !sale_setZone(this, zone) && !sale_setState(this, state))
		{
			return this;
		}
		else
		{
			sale_delete(this);
		}
	}
	return NULL;
}

/** \brief Dar de alta una venta recibiendo los parametros como texto
 * \param char* clientId: Recibo el id del cliente en forma de texto
 * \param char* posterId: Recibo el id de la venta en forma de texto
 * \param char* posterQty: Recibo la cantidad de afiches
 * \param char* posterName: Recibo el nombre del archivo
 * \param char* zone: Recibo la localidad
 * \param char* state: Recibo el estado de la venta
 * \return la direccion de memoria de la venta con todos sus datos cargados o NULL en caso de que algo haya salido mal
 */

Sale* sale_newWithParametersTxt(char* clientId, char* posterId, char* posterQty, char* posterName, char* zone, char* state)
{
	Sale* this = sale_new();
	if(this!=NULL)
	{
		if( !sale_setClientIdTxt(this, clientId) && !sale_setSaleIdTxt(this, posterId) && !sale_setPosterQtyTxt(this, posterQty) &&
			!sale_setFileName(this, posterName) && !sale_setZoneTxt(this, zone) && !sale_setStateTxt(this, state))
		{
			return this;
		}
		else
		{
			sale_delete(this);
		}
	}
	return NULL;
}

/** \brief Borra la direccion de memoria reservada de una venta
 *  \param Sale* this: Puntero de la venta
 *
 */
void sale_delete(Sale* this)
{
	free(this);
}

/** \brief Obtengo el id del cliente
 * \param void* this: Puntero void
 * \param int* pResult: Pasaje por referencia del id del cliente
 * \return (0) Si todo esta OK o (-1) Si algo salio mal
 */

int sale_getClientId(void* this, int* pResult)
{
	int retornar=-1;
	Sale* bufferSale;
	if(this!=NULL)
	{
		bufferSale = (Sale*) this;
		*pResult = bufferSale->clientId;
		retornar=0;
	}
	return retornar;
}

/** \brief Obtengo el id de la venta
 * \param void* this: Puntero void
 * \param int* pResult: Pasaje por referencia del id de la venta
 * \return (0) Si todo esta OK o (-1) Si algo salio mal
 */
int sale_getSaleId(void* this, int* pResult)
{
	int retornar=-1;
	Sale* bufferSale;
	if(this!=NULL)
	{
		bufferSale = (Sale*) this;
		*pResult = bufferSale->sellId;
		retornar=0;
	}
	return retornar;
}

/** \brief Obtengo la cantidad de afiches
 * \param void* this: Puntero void
 * \param int* pResult: Pasaje por referencia de la cantidad de afiches
 * \return (0) Si todo esta OK o (-1) Si algo salio mal
 */
int sale_getPosterQty(void* this, int* pResult)
{
	int retornar=-1;
	Sale* bufferSale;
	if(this!=NULL)
	{
		bufferSale = (Sale*) this;
		*pResult = bufferSale->posterQty;
		retornar=0;
	}
	return retornar;
}

/** \brief Obtengo el nombre del archivo
 * \param void* this: Puntero void
 * \param char* pResult: Pasaje por referencia del nombre del archivo
 * \return (0) Si todo esta OK o (-1) Si algo salio mal
 */
int sale_getFileName(void* this, char* pResult)
{
	int retornar=-1;
	Sale* bufferSale;
	if(this!=NULL)
	{
		retornar=0;
		bufferSale = (Sale*) this;
		strncpy(pResult, bufferSale->posterName, POSTER_SIZE);
	}
	return retornar;
}

/** \brief Obtengo la localidad
 * \param void* this: Puntero void
 * \param int* pResult: Pasaje por referencia de la localidad
 * \return (0) Si todo esta OK o (-1) Si algo salio mal
 */
int sale_getZone(void* this, int* pResult)
{
	int retornar=-1;
	Sale* bufferSale;
	if(this!=NULL)
	{
		bufferSale = (Sale*) this;
		*pResult = bufferSale->zone;
		retornar=0;
	}
	return retornar;
}

/** \brief Obtengo el estado de la venta
 * \param void* this: Puntero void
 * \param int* pResult: Pasaje por referencia del estado de la venta
 * \return (0) Si todo esta OK o (-1) Si algo salio mal
 */
int sale_getState(void* this, int* pResult)
{
	int retornar=-1;
	Sale* bufferSale;
	if(this!=NULL)
	{
		bufferSale = (Sale*) this;
		*pResult = bufferSale->state;
		retornar=0;
	}
	return retornar;
}

/** \brief Asigno el id del cliente
 * \param void* this: Puntero void
 * \param int clientId: Recibo el id del cliente a asignar
 * \return (0) Si todo esta OK o (-1) Si algo salio mal
 */
int sale_setClientId(void* this, int clientId)
{
	int retornar=-1;
	Sale* bufferSale;
	if(this!=NULL && clientId>-1)
	{
		bufferSale = (Sale*) this;
		bufferSale->clientId = clientId;
		retornar=0;
	}
	return retornar;
}

/** \brief Asigno el id del cliente en forma de texto
 * \param void* this: Puntero void
 * \param char* clientId: Recibo el id en forma de texto del cliente a asignar
 * \return (0) Si todo esta OK o (-1) Si algo salio mal
 */
int sale_setClientIdTxt(void* this, char* clientId)
{
	int retornar=-1;
	Sale* bufferSale;
	if(this!=NULL && clientId!=NULL && isValidInt(clientId))
	{
		bufferSale = (Sale*) this;
		bufferSale->clientId = atoi(clientId);
		retornar=0;
	}
	return retornar;
}

/** \brief Asigno el id de la venta en forma de texto
 * \param void* this: Puntero void
 * \param int sellId: Recibo el id del cliente a asignar
 * \return (0) Si todo esta OK o (-1) Si algo salio mal
 */
int sale_setSaleId(void* this, int sellId)
{
	int retornar=-1;
	Sale* bufferSale;
	if(this!=NULL && sellId>-1)
	{
		bufferSale = (Sale*) this;
		bufferSale->sellId = sellId;
		retornar=0;
	}
	return retornar;
}

/** \brief Asigno el id de la venta en forma de texto
 * \param void* this: Puntero void
 * \param int sellId: Recibo el id en forma de texto de la venta a asignar
 * \return (0) Si todo esta OK o (-1) Si algo salio mal
 */
int sale_setSaleIdTxt(void* this, char* sellId)
{
	int retornar=-1;
	Sale* bufferSale;
	if(this!=NULL && sellId!=NULL && isValidInt(sellId))
	{
		bufferSale = (Sale*) this;
		bufferSale->sellId = atoi(sellId);
		retornar=0;
	}
	return retornar;
}

/** \brief Asigno la cantidad de afiches
 * \param void* this: Puntero void
 * \param int posterQty: Recibo la cantida de afiches a asignar
 * \return (0) Si todo esta OK o (-1) Si algo salio mal
 */
int sale_setPosterQty(void* this, int posterQty)
{
	int retornar=-1;
	Sale* bufferSale;
	if(this!=NULL && posterQty>-1)
	{
		bufferSale = (Sale*) this;
		bufferSale->posterQty = posterQty;
		retornar=0;
	}
	return retornar;
}

/** \brief Asigno la cantidad de afiches en forma de texto
 * \param void* this: Puntero void
 * \param int posterQty: Recibo la cantidad de afiches a asignar en forma de texto
 * \return (0) Si todo esta OK o (-1) Si algo salio mal
 */
int sale_setPosterQtyTxt(void* this, char* posterQty)
{
	int retornar=-1;
	Sale* bufferSale;
	if(this!=NULL && posterQty!=NULL && isValidInt(posterQty))
	{
		bufferSale = (Sale*) this;
		bufferSale->posterQty = atoi(posterQty);
		retornar=0;
	}
	return retornar;
}

/** \brief Asigno el nombre del archivo
 * \param void* this: Puntero void
 * \param char* posterName: recibo el nombre del archivo a asignar
 * \return (0) Si todo esta OK o (-1) Si algo salio mal
 */
int sale_setFileName(void* this, char* posterName)
{
	int retornar=-1;
	Sale* bufferSale;
	if(this!=NULL && posterName!=NULL && isAlphaNumeric(posterName))
	{
		bufferSale = (Sale*) this;
		strncpy(bufferSale->posterName, posterName, POSTER_SIZE);
		retornar=0;
	}
	return retornar;
}

/** \brief Asigno la localidad
 * \param void* this: Puntero void
 * \param int zone: Recibo la zona a asignar
 * \return (0) Si todo esta OK o (-1) Si algo salio mal
 */
int sale_setZone(void* this, int zone)
{
	int retornar=-1;
	Sale* bufferSale;
	if(this!=NULL && (zone>0 && zone<5))
	{
		bufferSale = (Sale*) this;
		bufferSale->zone = zone;
		retornar=0;
	}
	return retornar;
}

/** \brief Asigno la localidad en forma de texto
 * \param void* this: Puntero void
 * \param int zone: Recibo la zona a asignar en forma de texto
 * \return (0) Si todo esta OK o (-1) Si algo salio mal
 */
int sale_setZoneTxt(void* this, char* zone)
{
	int retornar=-1;
	Sale* bufferSale;
	if(this!=NULL && zone!=NULL && isValidInt(zone))
	{
		bufferSale = (Sale*) this;
		bufferSale->zone = atoi(zone);
		retornar=0;
	}
	return retornar;
}

/** \brief Asigno el estado de la venta
 * \param void* this: Puntero void
 * \param int state: Recibo el estado de la venta a asignar
 * \return (0) Si todo esta OK o (-1) Si algo salio mal
 */
int sale_setState(void* this, int state)
{
	int retornar=-1;
	Sale* bufferSale;
	if(this!=NULL && (state==0 || state==1))
	{
		bufferSale = (Sale*) this;
		bufferSale->state = state;
		retornar=0;
	}
	return retornar;
}

/** \brief Asigno el estado de la venta en forma de texto
 * \param void* this: Puntero void
 * \param int state: Recibo el estado de la venta a asignar en forma de texto
 * \return (0) Si todo esta OK o (-1) Si algo salio mal
 */
int sale_setStateTxt(void* this, char* state)
{
	int retornar=-1;
	Sale* bufferSale;
	if(this!=NULL && state!=NULL && isValidInt(state))
	{
		bufferSale = (Sale*) this;
		bufferSale->state = atoi(state);
		retornar=0;
	}
	return retornar;
}

/**
 * \brief Funcion para validar si la cadena de caracteres que recibimos corresponde a un entero
 * \char* string: Es la cadena de caracteres que vamos a validar
 * \return (-1) si algo salio mal (0) si todo esta OK
 */

static int isValidInt(char* string)
{
	int retorno = 1;
	int i = 0;

	if(string!=NULL && strlen(string)>0)
	{
		if(string[0]=='-')
		{
			i=1;
		}
		for(;i<strlen(string);i++)
		{
			if(string[i]>'9' || string[i]<'0')
			{
				retorno=0;
				break;
			}
		}
	}
	return retorno;
}

/**
 * \brief Funcion para validar si el array de caracteres que recibe es una cadena de texto, incluido numeros, espacios y puntiaciones
 * \param char pResultado: Es el string que vamos a validar
 * \return (-1) si algo salio mal (0) si todo esta OK
 */

static int isAlphaNumeric(char* pResultado)
{
	int retorno = 1;
	int i;
	if(pResultado != NULL)
	{
		for(i=0;pResultado[i] != '\0';i++)
		{
			if(pResultado[i]!=' ' && pResultado[i]!=',' && pResultado[i]!='.' && (pResultado[i]<'a' || pResultado[i]>'z') && (pResultado[i]<'A' || pResultado[i]>'Z') && (pResultado[i]<'0' || pResultado[i]>'9'))
			{
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}

/**
 * \brief Funcion para imprimir todos los datos de una venta
 * \void* this: Puntero a void que luego convertiremos en un tipo de dato Sale
 * \return (-1) si algo salio mal (0) si todo esta OK
 */
int sale_print(void* this)
{
	int retornar=-1;
	Sale* bufferSale;
	int bufferIdClient;
	int bufferIdSale;
	int bufferPosterQty;
	char bufferFileName[POSTER_SIZE];
	int bufferZone;
	int bufferState;
	char bufferZoneString[BUFFER_SIZE];
	char bufferStateString[BUFFER_SIZE];
	if(this!=NULL)
	{
		retornar=0;
		bufferSale = (Sale*) this;
		if( !sale_getClientId(bufferSale, &bufferIdClient) && !sale_getSaleId(bufferSale, &bufferIdSale) && !sale_getPosterQty(bufferSale, &bufferPosterQty) &&
			!sale_getFileName(bufferSale, bufferFileName) && !sale_getZone(bufferSale, &bufferZone) && !sale_getState(bufferSale, &bufferState))
		{
			switch(bufferZone)
			{
				case 1:
					sprintf(bufferZoneString, "CABA");
				break;
				case 2:
					sprintf(bufferZoneString, "ZONA SUR");
				break;
				case 3:
					sprintf(bufferZoneString, "ZONA OESTE");
				break;
			}
			if(bufferState)
			{
				sprintf(bufferStateString, "COBRADO");
			}
			else
			{
				sprintf(bufferStateString, "A COBRAR");
			}
			printf("\nID venta: %d - ID cliente: %d - Cantidad: %d - Nombre archivo: %s - Zona: %s - Estado: %s",
					bufferIdSale, bufferIdClient, bufferPosterQty, bufferFileName, bufferZoneString, bufferStateString);
		}
	}
	return retornar;
}

/**
 * \brief Funcion para corroborar si una venta NO esta cobrada
 * \void* this: Puntero a void que luego convertiremos en un tipo de dato Sale
 * \return (-1) si algo salio mal (0) si todo esta OK
 */
int sale_isSold(void* this)
{
	int retornar=-1;
	Sale* bufferSale;
	int bufferState;
	if(this!=NULL)
	{
		retornar=0;
		bufferSale = (Sale*) this;
		if(!sale_getState(bufferSale, &bufferState) && bufferState==0)
		{
			retornar=1;
		}
	}
	return retornar;
}

/**
 * \brief Funcion para corroborar si una venta ESTA cobrada
 * \void* this: Puntero a void que luego convertiremos en un tipo de dato Sale
 * \return (-1) si algo salio mal (0) si todo esta OK
 */
int sale_isNotSold(void* this)
{
	int retornar=-1;
	Sale* bufferSale;
	int bufferState;
	if(this!=NULL)
	{
		retornar=1;
		bufferSale = (Sale*) this;
		if(!sale_getState(bufferSale, &bufferState) && bufferState==0)
		{
			retornar=0;
		}
	}
	return retornar;
}

/**
 * \brief Funcion para comparar id que recibimos por parametro y el id del cliente en una venta
 * \void* this: Puntero a void que luego convertiremos en un tipo de dato Sale
 * \void* id: Puntero a void que luego convertiremos en un int
 * \return (-1) si algo salio mal (0) si todo esta OK
 */
int sale_sameId(void* this, void* id)
{
	int retornar=0;
	int bufferClientId;
	int bufferId = (int) id;
	Sale* bufferSale = (Sale*) this;
	if( !sale_getClientId(bufferSale, &bufferClientId))
	{
		if(bufferClientId == bufferId)
		{
			retornar=1;
		}
	}
	return retornar;
}
