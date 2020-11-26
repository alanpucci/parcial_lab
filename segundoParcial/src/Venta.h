#ifndef VENTA_H_
#define VENTA_H_
#define POSTER_SIZE 101

typedef struct{
	int sellId;
	int clientId;
	int posterQty;
	char posterName[POSTER_SIZE];
	int zone;
	int state;
}Venta;



Venta* venta_new();
Venta* venta_newWithParameters(int clientId, int posterId, int posterQty, char* posterName, int zone, int state);
Venta* venta_newWithParametersTxt(char* clientId, char* posterId, char* posterQty, char* posterName, char* zone, char* state);
void venta_delete(Venta* this);

int venta_getClientId(void* this, int* pResult);
int venta_setClientId(void* this, int clientId);
int venta_setClientIdTxt(void* this, char* clientId);

int venta_getSellId(void* this, int* pResult);
int venta_setSellId(void* this, int posterId);
int venta_setSellIdTxt(void* this, char* posterId);

int venta_getPosterQty(void* this, int* pResult);
int venta_setPosterQty(void* this, int posterQty);
int venta_setPosterQtyTxt(void* this, char* posterQty);

int venta_getFileName(void* this, char* pResult);
int venta_setFileName(void* this, char* posterName);

int venta_getZone(void* this, int* pResult);
int venta_setZone(void* this, int zone);
int venta_setZoneTxt(void* this, char* zone);

int venta_getState(void* this, int* pResult);
int venta_setState(void* this, int state);
int venta_setStateTxt(void* this, char* state);

int venta_print(void* this);
int venta_isSold(void* this);
int venta_isNotSold(void* this);
int venta_sameId(void* this, void* id);

#endif /* VENTA_H_ */
