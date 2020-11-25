#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Venta.h"
#define BUFFER_SIZE 4096

static int isValidInt(char* string);
static int isAlphaNumeric(char* pResultado);

Venta* venta_new()
{
	return (Venta*) malloc(sizeof(Venta));
}

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

void venta_delete(Venta* this)
{
	free(this);
}

int venta_getClientId(Venta* this, int* pResult)
{
	int retornar=-1;
	if(this!=NULL)
	{
		*pResult = this->clientId;
		retornar=0;
	}
	return retornar;
}

int venta_getSellId(Venta* this, int* pResult)
{
	int retornar=-1;
	if(this!=NULL)
	{
		*pResult = this->sellId;
		retornar=0;
	}
	return retornar;
}

int venta_getPosterQty(Venta* this, int* pResult)
{
	int retornar=-1;
	if(this!=NULL)
	{
		*pResult = this->posterQty;
		retornar=0;
	}
	return retornar;
}

int venta_getFileName(Venta* this, char* pResult)
{
	int retornar=-1;
	if(this!=NULL)
	{
		retornar=0;
		strncpy(pResult, this->posterName, POSTER_SIZE);
	}
	return retornar;
}

int venta_getZone(Venta* this, int* pResult)
{
	int retornar=-1;
	if(this!=NULL)
	{
		*pResult = this->zone;
		retornar=0;
	}
	return retornar;
}

int venta_getState(Venta* this, int* pResult)
{
	int retornar=-1;
	if(this!=NULL)
	{
		*pResult = this->state;
		retornar=0;
	}
	return retornar;
}

int venta_setClientId(Venta* this, int clientId)
{
	int retornar=-1;
	if(this!=NULL && clientId>-1)
	{
		this->clientId = clientId;
		retornar=0;
	}
	return retornar;
}

int venta_setClientIdTxt(Venta* this, char* clientId)
{
	int retornar=-1;
	if(this!=NULL && clientId!=NULL && isValidInt(clientId))
	{
		this->clientId = atoi(clientId);
		retornar=0;
	}
	return retornar;
}

int venta_setSellId(Venta* this, int sellId)
{
	int retornar=-1;
	if(this!=NULL && sellId>-1)
	{
		this->sellId = sellId;
		retornar=0;
	}
	return retornar;
}

int venta_setSellIdTxt(Venta* this, char* sellId)
{
	int retornar=-1;
	if(this!=NULL && sellId!=NULL && isValidInt(sellId))
	{
		this->sellId = atoi(sellId);
		retornar=0;
	}
	return retornar;
}

int venta_setPosterQty(Venta* this, int posterQty)
{
	int retornar=-1;
	if(this!=NULL && posterQty>-1)
	{
		this->posterQty = posterQty;
		retornar=0;
	}
	return retornar;
}

int venta_setPosterQtyTxt(Venta* this, char* posterQty)
{
	int retornar=-1;
	if(this!=NULL && posterQty!=NULL && isValidInt(posterQty))
	{
		this->posterQty = atoi(posterQty);
		retornar=0;
	}
	return retornar;
}

int venta_setFileName(Venta* this, char* posterName)
{
	int retornar=-1;
	if(this!=NULL && posterName!=NULL && isAlphaNumeric(posterName))
	{
		strncpy(this->posterName, posterName, POSTER_SIZE);
		retornar=0;
	}
	return retornar;
}

int venta_setZone(Venta* this, int zone)
{
	int retornar=-1;
	if(this!=NULL && (zone>0 && zone<5))
	{
		this->zone = zone;
		retornar=0;
	}
	return retornar;
}

int venta_setZoneTxt(Venta* this, char* zone)
{
	int retornar=-1;
	if(this!=NULL && zone!=NULL && isValidInt(zone))
	{
		this->zone = atoi(zone);
		retornar=0;
	}
	return retornar;
}

int venta_setState(Venta* this, int state)
{
	int retornar=-1;
	if(this!=NULL && (state==0 || state==1))
	{
		this->state = state;
		retornar=0;
	}
	return retornar;
}

int venta_setStateTxt(Venta* this, char* state)
{
	int retornar=-1;
	if(this!=NULL && state!=NULL && isValidInt(state))
	{
		this->state = atoi(state);
		retornar=0;
	}
	return retornar;
}

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
