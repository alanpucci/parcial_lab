#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"


static Node* getNode(LinkedList* this, int nodeIndex);
static int addNode(LinkedList* this, int nodeIndex,void* pElement);

/** \brief Crea un nuevo LinkedList en memoria de manera dinamica
 *
 *  \param void
 *  \return LinkedList* Retorna (NULL) en el caso de no conseguir espacio en memoria
 *                      o el puntero al espacio reservado
 */
LinkedList* ll_newLinkedList(void)
{
    LinkedList* this= NULL;
    this = (LinkedList*) malloc(sizeof(LinkedList));
    if(this!=NULL)
    {
		this->size = 0;
		this->pFirstNode = NULL;
    }
    return this;
}

/** \brief Retorna la cantidad de elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna (-1) si el puntero es NULL o la cantidad de elementos de la lista
 *
 */
int ll_len(LinkedList* this)
{
    int returnAux = -1;
    if(this!=NULL)
    {
    	returnAux = this->size;
    }
    return returnAux;
}


/** \brief  Obtiene un nodo de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pNode) Si funciono correctamente
 *
 */
static Node* getNode(LinkedList* this, int nodeIndex)
{
	int i;
	int len = ll_len(this);
	Node* auxNode=NULL;
	if(this!=NULL && nodeIndex>-1 && len>nodeIndex)
	{
		auxNode = this->pFirstNode;
		for(i=0;i<nodeIndex;i++)
		{
			auxNode = auxNode->pNextNode;
		}
	}
	return auxNode;
}

/** \brief  Permite realizar el test de la funcion getNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pElement) Si funciono correctamente
 *
 */
Node* test_getNode(LinkedList* this, int nodeIndex)
{
    return getNode(this, nodeIndex);
}


/** \brief Agrega y enlaza un nuevo nodo a la lista
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */

static int addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    int returnAux = -1;
    int len = ll_len(this);
    Node* pNewNode=NULL;
    Node* pPrevNode=NULL;
    if(this!=NULL && nodeIndex>-1 && len>=nodeIndex)
    {
    	pNewNode = (Node*) malloc(sizeof(Node));
    	if(pNewNode!=NULL)
    	{
    		pNewNode->pElement = pElement;
    		if(nodeIndex==0)
    		{
				pNewNode->pNextNode = this->pFirstNode;
				this->pFirstNode = pNewNode;
    		}
    		else
    		{
    			pPrevNode = getNode(this, nodeIndex-1);
    			pNewNode->pNextNode=pPrevNode->pNextNode;
				pPrevNode->pNextNode = pNewNode;
    		}
    		this->size++;
    		returnAux=0;
    	}
    }
    return returnAux;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
  * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int test_addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    return addNode(this,nodeIndex,pElement);
}


/** \brief  Agrega un elemento a la lista
 * \param pList LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento a ser agregado
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_add(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    int len=ll_len(this);
    if(this!=NULL && len>-1)
    {
    	addNode(this, len, pElement);
    	returnAux=0;
    }
    return returnAux;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a obtener
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_get(LinkedList* this, int index)
{
    void* returnAux = NULL;
    int len = ll_len(this);
	Node* auxNode=NULL;
    if(this!=NULL && index>-1 && len>index)
    {
    	auxNode = getNode(this, index);
    	if(auxNode!=NULL)
    	{
    		returnAux = auxNode->pElement;
    	}
    }
    return returnAux;
}


/** \brief Modifica un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a modificar
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_set(LinkedList* this, int index,void* pElement)
{
    int returnAux = -1;
    Node* auxNode=NULL;
    if(this!=NULL && index>-1 && index<ll_len(this))
    {
    	auxNode = getNode(this, index);
    	if(auxNode!=NULL)
    	{
			returnAux=0;
    		auxNode->pElement = pElement;
    	}
    }
    return returnAux;
}


/** \brief Elimina un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a eliminar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_remove(LinkedList* this,int index)
{
    int returnAux = -1;
    Node* pAuxNode=NULL;
    Node* pPrevNode=NULL;
    if(this!=NULL && index>-1 && index<ll_len(this))
    {
    	pAuxNode = getNode(this,index);
    	if(pAuxNode!=NULL && index==0)
		{
			this->pFirstNode=pAuxNode->pNextNode;
		}
    	else
    	{
			pPrevNode = getNode(this, index-1);
			if(pPrevNode!=NULL)
			{
				pPrevNode->pNextNode = pAuxNode->pNextNode;
			}
    	}
		returnAux = 0;
		this->size--;
		free(pAuxNode);
    }
    return returnAux;
}


/** \brief Elimina todos los elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_clear(LinkedList* this)
{
    int returnAux = -1;
    if(this!=NULL)
    {
    	while(ll_len(this))
    	{
    		ll_remove(this, 0);
    	}
		returnAux=0;
    	this->pFirstNode=NULL;
    }
    return returnAux;
}


/** \brief Elimina todos los elementos de la lista y la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_deleteLinkedList(LinkedList* this)
{
    int returnAux = -1;
    if(this!=NULL)
    {
    	ll_clear(this);
    	free(this);
    	returnAux=0;
    }
    return returnAux;
}

/** \brief Busca el indice de la primer ocurrencia del elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        (indice del elemento) Si funciono correctamente
 *
 */
int ll_indexOf(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    void* pAuxElement;
    if(this!=NULL)
    {
    	for(int i=0;i<ll_len(this);i++)
    	{
    		pAuxElement = ll_get(this, i);
    		if(pAuxElement == pElement)
    		{
    			returnAux=i;
    		}
    	}
    }
    return returnAux;
}

/** \brief Indica si la lista esta o no vacia
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si la lista NO esta vacia
                        ( 1) Si la lista esta vacia
 *
 */
int ll_isEmpty(LinkedList* this)
{
    int returnAux = -1;
    if(this!=NULL)
    {
    	returnAux=1;
    	if(this->pFirstNode!=NULL && this->size>0)
    	{
    		returnAux=0;
    	}
    }
    return returnAux;
}

/** \brief Inserta un nuevo elemento en la lista en la posicion indicada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo elemento
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_push(LinkedList* this, int index, void* pElement)
{
    int returnAux = -1;
    if(this!=NULL && index>-1 && index<=ll_len(this))
    {
    	if(!addNode(this, index, pElement))
    	{
    		returnAux=0;
    	}
    }
    return returnAux;
}


/** \brief Elimina el elemento de la posicion indicada y retorna su puntero
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento eliminar
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_pop(LinkedList* this,int index)
{
    void* returnAux = NULL;
    void* pAuxElement=NULL;
    if(this!=NULL && index>-1 && index<ll_len(this))
    {
    	pAuxElement = ll_get(this, index);
    	if(pAuxElement!=NULL)
    	{
			this->size--;
    		ll_remove(this, index);
    		returnAux = pAuxElement;
    	}
    }
    return returnAux;
}


/** \brief  Determina si la lista contiene o no el elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero del elemento a verificar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 1) Si contiene el elemento
                        ( 0) si No contiene el elemento
*/
int ll_contains(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    if(this!=NULL)
    {
    	returnAux=0;
    	if(ll_indexOf(this, pElement)>-1)
    	{
    		returnAux=1;
    	}
    }
    return returnAux;
}

/** \brief  Determina si todos los elementos de la lista (this2)
            estan contenidos en la lista (this)
 *
 * \param this LinkedList* Puntero a la lista
 * \param this2 LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si alguno de los punteros a las listas son NULL
                        ( 1) Si los elementos de (this2) estan contenidos en la lista (this)
                        ( 0) si los elementos de (this2) NO estan contenidos en la lista (this)
*/
int ll_containsAll(LinkedList* this,LinkedList* this2)
{
    int returnAux = -1;
    void* pAuxElement=NULL;
    if(this!=NULL && this2!=NULL)
    {
    	returnAux=1;
    	for(int i=0;i<ll_len(this2);i++)
    	{
    		pAuxElement = ll_get(this2, i);
    		if(pAuxElement!=NULL)
    		{
    			if(!ll_contains(this, pAuxElement))
    			{
    				returnAux=0;
    				break;
    			}
    		}
    	}
    }
    return returnAux;
}

/** \brief Crea y retorna una nueva lista con los elementos indicados
 *
 * \param pList LinkedList* Puntero a la lista
 * \param from int Indice desde el cual se copian los elementos en la nueva lista
 * \param to int Indice hasta el cual se copian los elementos en la nueva lista (no incluido)
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                o (si el indice from es menor a 0 o mayor al len de la lista)
                                o (si el indice to es menor o igual a from o mayor al len de la lista)
                         (puntero a la nueva lista) Si ok
*/
LinkedList* ll_subList(LinkedList* this,int from,int to)
{
    LinkedList* cloneArray = NULL;
    void* pAuxElement=NULL;
    int len = ll_len(this);
    if(this!=NULL && from>-1 && to>-1 && from<=to && from<len && to<=len)
    {
    	cloneArray = ll_newLinkedList();
    	if(cloneArray!=NULL)
    	{
			for(int i=from;i<to;i++)
			{
				pAuxElement = ll_get(this, i);
				if(pAuxElement!=NULL)
				{
					ll_add(cloneArray, pAuxElement);
				}
			}
    	}
    }
    return cloneArray;
}

/** \brief Crea y retorna una nueva lista con los elementos de la lista pasada como parametro
 *
 * \param pList LinkedList* Puntero a la lista
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                (puntero a la nueva lista) Si ok
*/
LinkedList* ll_clone(LinkedList* this)
{
    LinkedList* cloneArray = NULL;
    if(this!=NULL)
    {
    	cloneArray = ll_subList(this, 0, ll_len(this));
    }
    return cloneArray;
}


/** \brief Ordena los elementos de la lista utilizando la funcion criterio recibida como parametro
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \param order int  [1] Indica orden ascendente - [0] Indica orden descendente
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL
                                ( 0) Si ok
 */
int ll_sort(LinkedList* this, int (*pFunc)(void* ,void*), int order)
{
    int returnAux =-1;
    void* pFirstNode=NULL;
    void* pSecondNode=NULL;
    int len=ll_len(this);
    int flagSwap=0;
    if(this!=NULL && pFunc!=NULL && (order==1 || order==0))
    {
    	do
    	{
    		flagSwap=1;
			for(int i=0;i<len-1;i++)
			{
				pFirstNode=ll_get(this, i);
				pSecondNode=ll_get(this, i+1);
				if(pFirstNode!=NULL && pSecondNode!=NULL)
				{
					if( (order==1 && pFunc(pFirstNode,pSecondNode)>0) ||
						(order==0 && pFunc(pFirstNode, pSecondNode)<0))
					{
						flagSwap=0;
						ll_set(this, i, pSecondNode);
						ll_set(this, i+1, pFirstNode);
					}
				}
			}
    	}while(flagSwap==0);
    	returnAux=0;
    }
    return returnAux;
}

/** \brief Recorre toda la lista y por cada uno de los elementos de la misma llama a una funcion criterio
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL
                                ( 0) Si ok
 */
int ll_map(LinkedList* this, int (*pFunc)(void*))
{
	int returnAux=-1;
	int len = ll_len(this);
	void *pElement=NULL;
	if(this!=NULL)
	{
		for(int i=0;i<len;i++)
		{
			pElement=ll_get(this, i);
			if(pElement!=NULL && !pFunc(pElement))
			{
				returnAux=0;
			}
		}
	}
	return returnAux;
}
/** \brief Recorre toda la lista y por cada uno de los elementos de la misma llama a una funcion criterio que ademas va a comparar con otro parametro
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio, recibe puntero a void y a char
 * \param char* cuit Cuit a comparar en la funcion criterio
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL
                                ( 1) Si ok
                                ( 0) si ningun elemento cumplio con la funcion criterio
 */
int ll_map2(LinkedList* this, int (*pFunc)(void*, char*), char* cuit)
{
	int returnAux=-1;
	int len = ll_len(this);
	void *pElement=NULL;
	if(this!=NULL)
	{
		returnAux=0;
		for(int i=0;i<len;i++)
		{
			pElement=ll_get(this, i);
			if(pElement!=NULL && pFunc(pElement, cuit))
			{
				returnAux=1;
			}
		}
	}
	return returnAux;
}

/** \brief Filtra a traves de una funcion criterio y devuelve una lista nueva
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \return lista nueva y filtrada
 */
LinkedList* ll_cloneFilter(LinkedList* this, int (*pFunc)(void*))
{
	int len = ll_len(this);
	LinkedList* auxList=NULL;
	void* pElement=NULL;
	if(this!=NULL && pFunc!=NULL)
	{
		auxList = ll_newLinkedList();
		if(auxList!=NULL)
		{
			for(int i=0; i<len;i++)
			{
				pElement = ll_get(this, i);
				if(pFunc(pElement))
				{
					ll_add(auxList, pElement);
				}
			}
		}
	}
	return auxList;
}

/** \brief Filtra a traves de una funcion criterio y remueve los elementos que no la cumplan
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \return int (-1) si la lista es NULL
 * 			   (0) si Ok
 */
int ll_filter(LinkedList* this, int (*pFunc)(void*))
{
	int returnAux=-1;
	int len = ll_len(this);
	int flagRemove=0;
	void* pElement=NULL;
	if(this!=NULL && pFunc!=NULL)
	{
		returnAux=0;
		do
		{
			flagRemove=1;
			for(int i=0; i<len;i++)
			{
				pElement = ll_get(this, i);
				if(pElement!=NULL && pFunc(pElement)==0)
				{
					ll_remove(this, i);
					flagRemove=0;
				}
			}
		}while(flagRemove==0);
	}
	return returnAux;
}

/** \brief Recorre la lista y devuelve un acumulador INT con respecto a una funcion criterio
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio, recibe dos punteros a void
 * \param int id : parametro a comparar, ID
 * \param int* pResultado : Retornamos por referencia el acumulador INT
 * \return int (-1) si la lista es NULL
 * 			   (0) si Ok
 */
int ll_reduceInt(LinkedList* this, int (*pFunc)(void*, void*), int id,int* pResultado)
{
	int returnAux=-1;
	int len = ll_len(this);
	int acc=0;
	void* pElement=NULL;
	if(this!=NULL && pFunc!=NULL && len>-1)
	{
		for(int i=0;i<len;i++)
		{
			pElement = ll_get(this, i);
			acc= acc + pFunc(pElement,(void*) id);
		}
		*pResultado = acc;
		returnAux=0;
	}
	return returnAux;
}

/** \brief Recorre la lista y devuelve un acumulador float con respecto a una funcion criterio
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio, recibe puntero a void
 * \param int* pResultado : Retornamos por referencia el acumulador float
 * \return int (-1) si la lista es NULL
 * 			   (0) si Ok
 */
int ll_reduceFloat(LinkedList* this, int (*pFunc)(void*), float* pResultado)
{
	int returnAux=-1;
	int len = ll_len(this);
	float acc=0;
	void* pElement=NULL;
	if(this!=NULL && pFunc!=NULL && len>-1)
	{
		for(int i=0;i<len;i++)
		{
			pElement = ll_get(this, i);
			acc=+ pFunc(pElement);
		}
		*pResultado = acc;
		returnAux=0;
	}
	return returnAux;
}

