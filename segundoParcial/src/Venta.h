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

int venta_getClientId(Venta* this, int* pResult);
int venta_setClientId(Venta* this, int clientId);
int venta_setClientIdTxt(Venta* this, char* clientId);

int venta_getSellId(Venta* this, int* pResult);
int venta_setSellId(Venta* this, int posterId);
int venta_setSellIdTxt(Venta* this, char* posterId);

int venta_getPosterQty(Venta* this, int* pResult);
int venta_setPosterQty(Venta* this, int posterQty);
int venta_setPosterQtyTxt(Venta* this, char* posterQty);

int venta_getFileName(Venta* this, char* pResult);
int venta_setFileName(Venta* this, char* posterName);

int venta_getZone(Venta* this, int* pResult);
int venta_setZone(Venta* this, int zone);
int venta_setZoneTxt(Venta* this, char* zone);

int venta_getState(Venta* this, int* pResult);
int venta_setState(Venta* this, int state);
int venta_setStateTxt(Venta* this, char* state);

int venta_print(void* this);
int venta_isSold(void* this);
int venta_isNotSold(void* this);
int venta_sameId(void* this, void* id);

#endif /* VENTA_H_ */
