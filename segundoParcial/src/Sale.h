#ifndef SALE_H_
#define SALE_H_
#define POSTER_SIZE 101

typedef struct{
	int sellId;
	int clientId;
	int posterQty;
	char posterName[POSTER_SIZE];
	int zone;
	int state;
}Sale;



Sale* sale_new();
Sale* sale_newWithParameters(int clientId, int posterId, int posterQty, char* posterName, int zone, int state);
Sale* sale_newWithParametersTxt(char* clientId, char* posterId, char* posterQty, char* posterName, char* zone, char* state);
void sale_delete(Sale* this);

int sale_getClientId(void* this, int* pResult);
int sale_setClientId(void* this, int clientId);
int sale_setClientIdTxt(void* this, char* clientId);

int sale_getSaleId(void* this, int* pResult);
int sale_setSaleId(void* this, int posterId);
int sale_setSaleIdTxt(void* this, char* posterId);

int sale_getPosterQty(void* this, int* pResult);
int sale_setPosterQty(void* this, int posterQty);
int sale_setPosterQtyTxt(void* this, char* posterQty);

int sale_getFileName(void* this, char* pResult);
int sale_setFileName(void* this, char* posterName);

int sale_getZone(void* this, int* pResult);
int sale_setZone(void* this, int zone);
int sale_setZoneTxt(void* this, char* zone);

int sale_getState(void* this, int* pResult);
int sale_setState(void* this, int state);
int sale_setStateTxt(void* this, char* state);

int sale_print(void* this);
int sale_isSold(void* this);
int sale_isNotSold(void* this);
int sale_sameId(void* this, void* id);

#endif /* SALE_H_ */
