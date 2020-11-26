#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Venta.h"
#define BUFFER_SIZE 4096

static int isValidInt(char* string);
static int isAlphaNumeric(char* pResultado);


/** \brief Uso de malloc para obtener una nueva direccion de memoria
 * 	\return la nueva direccion de memoria
 */
Venta* venta_new()
{
	return (Venta*) malloc(sizeof(Venta));
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
Venta* venta_newWithParameters(int clientId, int posterId, int posterQty, char* posterName, int zone, int state)
{
	Venta* this = venta_new();
	if(this!=NULL)
	{
		if( !venta_setClientId(this, clientId) && !venta_setSellId(this, posterId) && !venta_setPosterQty(this, posterQty) &&
			!venta_setFileName(this, posterName) && !venta_setZone(this, zone) && !venta_setState(this, state))
		{
			return this;
		}
		else
		{
			venta_delete(this);
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

Venta* venta_newWithParametersTxt(char* clientId, char* posterId, char* posterQty, char* posterName, char* zone, char* state)
{
	Venta* this = venta_new();
	if(this!=NULL)
	{
		if( !venta_setClientIdTxt(this, clientId) && !venta_setSellIdTxt(this, posterId) && !venta_setPosterQtyTxt(this, posterQty) &&
			!venta_setFileName(this, posterName) && !venta_setZoneTxt(this, zone) && !venta_setStateTxt(this, state))
		{
			return this;
		}
		else
		{
			venta_delete(this);
		}
	}
	return NULL;
}

/** \brief Borra la direccion de memoria reservada de una venta
 *  \param Venta* this: Puntero de la venta
 *
 */
void venta_delete(Venta* this)
{
	free(this);
}

/** \brief Obtengo el id del cliente
 * \param void* this: Puntero void
 * \param int* pResult: Pasaje por referencia del id del cliente
 * \return (0) Si todo esta OK o (-1) Si algo salio mal
 */

int venta_getClientId(void* this, int* pResult)
{
	int retornar=-1;
	Venta* bufferSell;
	if(this!=NULL)
	{
		bufferSell = (Venta*) this;
		*pResult = bufferSell->clientId;
		retornar=0;
	}
	return retornar;
}

/** \brief Obtengo el id de la venta
 * \param void* this: Puntero void
 * \param int* pResult: Pasaje por referencia del id de la venta
 * \return (0) Si todo esta OK o (-1) Si algo salio mal
 */
int venta_getSellId(void* this, int* pResult)
{
	int retornar=-1;
	Venta* bufferSell;
	if(this!=NULL)
	{
		bufferSell = (Venta*) this;
		*pResult = bufferSell->sellId;
		retornar=0;
	}
	return retornar;
}

/** \brief Obtengo la cantidad de afiches
 * \param void* this: Puntero void
 * \param int* pResult: Pasaje por referencia de la cantidad de afiches
 * \return (0) Si todo esta OK o (-1) Si algo salio mal
 */
int venta_getPosterQty(void* this, int* pResult)
{
	int retornar=-1;
	Venta* bufferSell;
	if(this!=NULL)
	{
		bufferSell = (Venta*) this;
		*pResult = bufferSell->posterQty;
		retornar=0;
	}
	return retornar;
}

/** \brief Obtengo el nombre del archivo
 * \param void* this: Puntero void
 * \param char* pResult: Pasaje por referencia del nombre del archivo
 * \return (0) Si todo esta OK o (-1) Si algo salio mal
 */
int venta_getFileName(void* this, char* pResult)
{
	int retornar=-1;
	Venta* bufferSell;
	if(this!=NULL)
	{
		retornar=0;
		bufferSell = (Venta*) this;
		strncpy(pResult, bufferSell->posterName, POSTER_SIZE);
	}
	return retornar;
}

/** \brief Obtengo la localidad
 * \param void* this: Puntero void
 * \param int* pResult: Pasaje por referencia de la localidad
 * \return (0) Si todo esta OK o (-1) Si algo salio mal
 */
int venta_getZone(void* this, int* pResult)
{
	int retornar=-1;
	Venta* bufferSell;
	if(this!=NULL)
	{
		bufferSell = (Venta*) this;
		*pResult = bufferSell->zone;
		retornar=0;
	}
	return retornar;
}

/** \brief Obtengo el estado de la venta
 * \param void* this: Puntero void
 * \param int* pResult: Pasaje por referencia del estado de la venta
 * \return (0) Si todo esta OK o (-1) Si algo salio mal
 */
int venta_getState(void* this, int* pResult)
{
	int retornar=-1;
	Venta* bufferSell;
	if(this!=NULL)
	{
		bufferSell = (Venta*) this;
		*pResult = bufferSell->state;
		retornar=0;
	}
	return retornar;
}

/** \brief Asigno el id del cliente
 * \param void* this: Puntero void
 * \param int clientId: Recibo el id del cliente a asignar
 * \return (0) Si todo esta OK o (-1) Si algo salio mal
 */
int venta_setClientId(void* this, int clientId)
{
	int retornar=-1;
	Venta* bufferSell;
	if(this!=NULL && clientId>-1)
	{
		bufferSell = (Venta*) this;
		bufferSell->clientId = clientId;
		retornar=0;
	}
	return retornar;
}

/** \brief Asigno el id del cliente en forma de texto
 * \param void* this: Puntero void
 * \param char* clientId: Recibo el id en forma de texto del cliente a asignar
 * \return (0) Si todo esta OK o (-1) Si algo salio mal
 */
int venta_setClientIdTxt(void* this, char* clientId)
{
	int retornar=-1;
	Venta* bufferSell;
	if(this!=NULL && clientId!=NULL && isValidInt(clientId))
	{
		bufferSell = (Venta*) this;
		bufferSell->clientId = atoi(clientId);
		retornar=0;
	}
	return retornar;
}

/** \brief Asigno el id de la venta en forma de texto
 * \param void* this: Puntero void
 * \param int sellId: Recibo el id del cliente a asignar
 * \return (0) Si todo esta OK o (-1) Si algo salio mal
 */
int venta_setSellId(void* this, int sellId)
{
	int retornar=-1;
	Venta* bufferSell;
	if(this!=NULL && sellId>-1)
	{
		bufferSell = (Venta*) this;
		bufferSell->sellId = sellId;
		retornar=0;
	}
	return retornar;
}

/** \brief Asigno el id de la venta en forma de texto
 * \param void* this: Puntero void
 * \param int sellId: Recibo el id en forma de texto de la venta a asignar
 * \return (0) Si todo esta OK o (-1) Si algo salio mal
 */
int venta_setSellIdTxt(void* this, char* sellId)
{
	int retornar=-1;
	Venta* bufferSell;
	if(this!=NULL && sellId!=NULL && isValidInt(sellId))
	{
		bufferSell = (Venta*) this;
		bufferSell->sellId = atoi(sellId);
		retornar=0;
	}
	return retornar;
}

/** \brief Asigno la cantidad de afiches
 * \param void* this: Puntero void
 * \param int posterQty: Recibo la cantida de afiches a asignar
 * \return (0) Si todo esta OK o (-1) Si algo salio mal
 */
int venta_setPosterQty(void* this, int posterQty)
{
	int retornar=-1;
	Venta* bufferSell;
	if(this!=NULL && posterQty>-1)
	{
		bufferSell = (Venta*) this;
		bufferSell->posterQty = posterQty;
		retornar=0;
	}
	return retornar;
}

/** \brief Asigno la cantidad de afiches en forma de texto
 * \param void* this: Puntero void
 * \param int posterQty: Recibo la cantidad de afiches a asignar en forma de texto
 * \return (0) Si todo esta OK o (-1) Si algo salio mal
 */
int venta_setPosterQtyTxt(void* this, char* posterQty)
{
	int retornar=-1;
	Venta* bufferSell;
	if(this!=NULL && posterQty!=NULL && isValidInt(posterQty))
	{
		bufferSell = (Venta*) this;
		bufferSell->posterQty = atoi(posterQty);
		retornar=0;
	}
	return retornar;
}

/** \brief Asigno el nombre del archivo
 * \param void* this: Puntero void
 * \param char* posterName: recibo el nombre del archivo a asignar
 * \return (0) Si todo esta OK o (-1) Si algo salio mal
 */
int venta_setFileName(void* this, char* posterName)
{
	int retornar=-1;
	Venta* bufferSell;
	if(this!=NULL && posterName!=NULL && isAlphaNumeric(posterName))
	{
		bufferSell = (Venta*) this;
		strncpy(bufferSell->posterName, posterName, POSTER_SIZE);
		retornar=0;
	}
	return retornar;
}

/** \brief Asigno la localidad
 * \param void* this: Puntero void
 * \param int zone: Recibo la zona a asignar
 * \return (0) Si todo esta OK o (-1) Si algo salio mal
 */
int venta_setZone(void* this, int zone)
{
	int retornar=-1;
	Venta* bufferSell;
	if(this!=NULL && (zone>0 && zone<5))
	{
		bufferSell = (Venta*) this;
		bufferSell->zone = zone;
		retornar=0;
	}
	return retornar;
}

/** \brief Asigno la localidad en forma de texto
 * \param void* this: Puntero void
 * \param int zone: Recibo la zona a asignar en forma de texto
 * \return (0) Si todo esta OK o (-1) Si algo salio mal
 */
int venta_setZoneTxt(void* this, char* zone)
{
	int retornar=-1;
	Venta* bufferSell;
	if(this!=NULL && zone!=NULL && isValidInt(zone))
	{
		bufferSell = (Venta*) this;
		bufferSell->zone = atoi(zone);
		retornar=0;
	}
	return retornar;
}

/** \brief Asigno el estado de la venta
 * \param void* this: Puntero void
 * \param int state: Recibo el estado de la venta a asignar
 * \return (0) Si todo esta OK o (-1) Si algo salio mal
 */
int venta_setState(void* this, int state)
{
	int retornar=-1;
	Venta* bufferSell;
	if(this!=NULL && (state==0 || state==1))
	{
		bufferSell = (Venta*) this;
		bufferSell->state = state;
		retornar=0;
	}
	return retornar;
}

/** \brief Asigno el estado de la venta en forma de texto
 * \param void* this: Puntero void
 * \param int state: Recibo el estado de la venta a asignar en forma de texto
 * \return (0) Si todo esta OK o (-1) Si algo salio mal
 */
int venta_setStateTxt(void* this, char* state)
{
	int retornar=-1;
	Venta* bufferSell;
	if(this!=NULL && state!=NULL && isValidInt(state))
	{
		bufferSell = (Venta*) this;
		bufferSell->state = atoi(state);
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
 * \void* this: Puntero a void que luego convertiremos en un tipo de dato Venta
 * \return (-1) si algo salio mal (0) si todo esta OK
 */
int venta_print(void* this)
{
	int retornar=-1;
	Venta* bufferSell;
	int bufferIdClient;
	int bufferIdSell;
	int bufferPosterQty;
	char bufferFileName[POSTER_SIZE];
	int bufferZone;
	int bufferState;
	char bufferZoneString[BUFFER_SIZE];
	char bufferStateString[BUFFER_SIZE];
	if(this!=NULL)
	{
		retornar=0;
		bufferSell = (Venta*) this;
		if( !venta_getClientId(bufferSell, &bufferIdClient) && !venta_getSellId(bufferSell, &bufferIdSell) && !venta_getPosterQty(bufferSell, &bufferPosterQty) &&
			!venta_getFileName(bufferSell, bufferFileName) && !venta_getZone(bufferSell, &bufferZone) && !venta_getState(bufferSell, &bufferState))
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
					bufferIdSell, bufferIdClient, bufferPosterQty, bufferFileName, bufferZoneString, bufferStateString);
		}
	}
	return retornar;
}

/**
 * \brief Funcion para corroborar si una venta NO esta cobrada
 * \void* this: Puntero a void que luego convertiremos en un tipo de dato Venta
 * \return (-1) si algo salio mal (0) si todo esta OK
 */
int venta_isSold(void* this)
{
	int retornar=-1;
	Venta* bufferSell;
	int bufferState;
	if(this!=NULL)
	{
		retornar=0;
		bufferSell = (Venta*) this;
		if(!venta_getState(bufferSell, &bufferState) && bufferState==0)
		{
			retornar=1;
		}
	}
	return retornar;
}

/**
 * \brief Funcion para corroborar si una venta ESTA cobrada
 * \void* this: Puntero a void que luego convertiremos en un tipo de dato Venta
 * \return (-1) si algo salio mal (0) si todo esta OK
 */
int venta_isNotSold(void* this)
{
	int retornar=-1;
	Venta* bufferSell;
	int bufferState;
	if(this!=NULL)
	{
		retornar=1;
		bufferSell = (Venta*) this;
		if(!venta_getState(bufferSell, &bufferState) && bufferState==0)
		{
			retornar=0;
		}
	}
	return retornar;
}

/**
 * \brief Funcion para comparar id que recibimos por parametro y el id del cliente en una venta
 * \void* this: Puntero a void que luego convertiremos en un tipo de dato Venta
 * \void* id: Puntero a void que luego convertiremos en un int
 * \return (-1) si algo salio mal (0) si todo esta OK
 */
int venta_sameId(void* this, void* id)
{
	int retornar=0;
	int bufferClientId;
	int bufferId = (int) id;
	Venta* bufferSell = (Venta*) this;
	if( !venta_getClientId(bufferSell, &bufferClientId))
	{
		if(bufferClientId == bufferId)
		{
			retornar=1;
		}
	}
	return retornar;
}
