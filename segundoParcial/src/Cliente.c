#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Cliente.h"

static int isValidString(char* string);
static int isValidInt(char* string);
static int isValidCuit(char* string);

/** \brief Uso de malloc para obtener una nueva direccion de memoria
 * 	\return la nueva direccion de memoria
 */
Cliente* cliente_new()
{
	return (Cliente*)malloc(sizeof(Cliente));
}

/** \brief Dar de alta un cliente recibiendo los parametros
 * \param int id: Recibo el id del cliente
 * \param char* name: Recibo el nombre del cliente
 * \param char* name: Recibo el apellido del cliente
 * \param char* cuit: Recibo el cuit del cliente
 * \return la direccion de memoria del cliente con todos sus datos cargados o NULL en caso de que algo haya salido mal
 */
Cliente* cliente_newWithParameters(int id, char* name, char* lastName, char* cuit)
{
	Cliente* this = cliente_new();
	if(this!=NULL)
	{
		if( !cliente_setId(this, id) && !cliente_setName(this, name) && !cliente_setLastName(this, lastName) && !cliente_setCuit(this, cuit) )
		{
			return this;
		}
		else
		{
			cliente_delete(this);
		}
	}
	return NULL;
}

/** \brief Dar de alta un cliente recibiendo los parametros en forma de texto
 * \param char* id: Recibo el id del cliente en forma de texto
 * \param char* name: Recibo el nombre del cliente
 * \param char* name: Recibo el apellido del cliente
 * \param char* cuit: Recibo el cuit del cliente
 * \return la direccion de memoria del cliente con todos sus datos cargados o NULL en caso de que algo haya salido mal
 */
Cliente* cliente_newWithParametersTxt(char* id, char* name, char* lastName, char* cuit)
{
	Cliente* this = cliente_new();
	if(this!=NULL)
	{
		if( !cliente_setIdTxt(this, id) && !cliente_setName(this, name) && !cliente_setLastName(this, lastName) && !cliente_setCuit(this, cuit))
		{
			return this;
		}
		else
		{
			cliente_delete(this);
		}
	}
	return NULL;
}

/** \brief Borra la direccion de memoria reservada de un cliente
 *  \param Cliente* this: Puntero del cliente
 *
 */
void cliente_delete(Cliente* this)
{
	free(this);
}

/** \brief Obtengo el id del cliente
 * \param void* this: Puntero void
 * \param int* pResult: Pasaje por referencia del id del cliente
 * \return (0) Si todo esta OK o (-1) Si algo salio mal
 */

int cliente_getId(void* this, int* pResult)
{
	int retornar=-1;
	Cliente* bufferClient;
	if(this!=NULL)
	{
		bufferClient = (Cliente*) this;
		*pResult = bufferClient->id;
		retornar=0;
	}
	return retornar;
}

/** \brief Obtengo el nombre del cliente
 * \param void* this: Puntero void
 * \param char* pResult: Pasaje por referencia del nombre del cliente
 * \return (0) Si todo esta OK o (-1) Si algo salio mal
 */
int cliente_getName(void* this, char* pResult)
{
	int retornar=-1;
	Cliente* bufferClient;
	if(this!=NULL)
	{
		retornar=0;
		bufferClient = (Cliente*) this;
		strncpy(pResult, bufferClient->name, NAME_SIZE);
	}
	return retornar;
}

/** \brief Obtengo el apellido del cliente
 * \param void* this: Puntero void
 * \param char* pResult: Pasaje por referencia del apellido del cliente
 * \return (0) Si todo esta OK o (-1) Si algo salio mal
 */
int cliente_getLastName(void* this, char* pResult)
{
	int retornar=-1;
	Cliente* bufferClient;
	if(this!=NULL)
	{
		retornar=0;
		bufferClient = (Cliente*) this;
		strncpy(pResult, bufferClient->lastName, NAME_SIZE);
	}
	return retornar;
}

/** \brief Obtengo el cuit del cliente
 * \param void* this: Puntero void
 * \param char* pResult: Pasaje por referencia del cuit del cliente
 * \return (0) Si todo esta OK o (-1) Si algo salio mal
 */
int cliente_getCuit(void* this, char* pResult)
{
	int retornar=-1;
	Cliente* bufferClient;
	if(this!=NULL)
	{
		retornar=0;
		bufferClient = (Cliente*) this;
		strncpy(pResult, bufferClient->cuit, CUIT_SIZE);
	}
	return retornar;
}

/** \brief Asigno el id del cliente
 * \param void* this: Puntero void
 * \param int id: Recibo el id a asignar
 * \return (0) Si todo esta OK o (-1) Si algo salio mal
 */
int cliente_setId(void* this, int id)
{
	int retorno=-1;
	Cliente* bufferClient;
	if(this!=NULL && id>-1)
	{
		bufferClient = (Cliente*) this;
		bufferClient->id = id;
		retorno=0;
	}
	return retorno;
}

/** \brief Asigno el id del cliente en forma de texto
 * \param void* this: Puntero void
 * \param int id: Recibo el id a asignar en forma de texto
 * \return (0) Si todo esta OK o (-1) Si algo salio mal
 */
int cliente_setIdTxt(void* this, char* id)
{
	int retorno=-1;
	Cliente* bufferClient;
	if(this!=NULL && isValidInt(id)==1)
	{
		bufferClient = (Cliente*) this;
		bufferClient->id = atoi(id);
		retorno=0;
	}
	return retorno;
}

/** \brief Asigno el nombre del cliente
 * \param void* this: Puntero void
 * \param char* name Recibo el nombre a asignar
 * \return (0) Si todo esta OK o (-1) Si algo salio mal
 */
int cliente_setName(void* this, char* name)
{
	int retorno=-1;
	Cliente* bufferClient;
	if(this!=NULL && isValidString(name)==1)
	{
		bufferClient = (Cliente*) this;
		strncpy(bufferClient->name, name, NAME_SIZE);
		retorno=0;
	}
	return retorno;
}

/** \brief Asigno el apellido del cliente
 * \param void* this: Puntero void
 * \param char* lastName Recibo el apellido a asignar
 * \return (0) Si todo esta OK o (-1) Si algo salio mal
 */
int cliente_setLastName(void* this, char* lastName)
{
	int retorno=-1;
	Cliente* bufferClient;
	if(this!=NULL && isValidString(lastName)==1)
	{
		bufferClient = (Cliente*) this;
		strncpy(bufferClient->lastName, lastName, NAME_SIZE);
		retorno=0;
	}
	return retorno;
}

/** \brief Asigno el cuit del cliente
 * \param void* this: Puntero void
 * \param char* cuit Recibo el cuit a asignar
 * \return (0) Si todo esta OK o (-1) Si algo salio mal
 */
int cliente_setCuit(void* this, char* cuit)
{
	int retorno=-1;
	Cliente* bufferClient;
	if(this!=NULL && isValidCuit(cuit)==1)
	{
		bufferClient = (Cliente*) this;
		strncpy(bufferClient->cuit, cuit, CUIT_SIZE);
		retorno=0;
	}
	return retorno;
}

/**
 * \brief Funcion para validar si el array de caracteres que recibe es una cadena de texto y no otra cosa
 * \param char* string: Es el string que vamos a validar
 * \return (-1) si algo salio mal (0) si todo esta OK
 */

static int isValidString(char* string)
{
	int retorno=1;
	if(string!=NULL && strlen(string)>0)
	{
		for(int i=0;i<strlen(string);i++)
		{
			if((string[i]<'a' || string[i]>'z') && (string[i]<'A' || string[i]>'Z') && string[i]!=32 && string[i]!='-')
			{
				retorno=0;
				break;
			}
		}
	}
	return retorno;
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
 * \brief Funcion para validar si la cadena de caracteres que recibimos corresponde a un cuit
 * \char* string: Es la cadena de caracteres que vamos a validar
 * \return (-1) si algo salio mal (0) si todo esta OK
 */
static int isValidCuit(char* string)
{
	int retorno;
	int dashCounter=0;
	if(string != NULL && strlen(string) > 0 && string[2] == '-' && string[11] == '-' && string[12] != '\0')
	{
		retorno = 1;
		for(int i = 0;string[i] != '\0'; i++)
		{
			if(string[i] == '-')
			{
				dashCounter++;
			}
			if(dashCounter>2 || ((string[i] < '0' || string[i] > '9') && string[i] != '-'))
			{
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}

/**
 * \brief Funcion para imprimir todos los datos de un cliente
 * \void* this: Puntero a void que luego convertiremos en un tipo de dato Cliente
 * \return (-1) si algo salio mal (0) si todo esta OK
 */
int cliente_print(void* this)
{
	int retornar=-1;
	Cliente* bufferClient;
	int bufferId;
	char bufferName[NAME_SIZE];
	char bufferLastName[NAME_SIZE];
	char bufferCuit[CUIT_SIZE];
	if(this!=NULL)
	{
		retornar=0;
		bufferClient = (Cliente*) this;
		if( !cliente_getId(bufferClient, &bufferId) && !cliente_getName(bufferClient, bufferName) &&
			!cliente_getLastName(bufferClient, bufferLastName) && !cliente_getCuit(bufferClient, bufferCuit))
		{
			printf("\nID: %d - Nombre: %s - Apellido: %s - Cuit: %s", bufferId, bufferName, bufferLastName, bufferCuit);
		}
	}
	return retornar;
}
