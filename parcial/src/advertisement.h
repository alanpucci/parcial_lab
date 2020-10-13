#ifndef advertisement_H_
#define advertisement_H_
#include "cliente.h"

#define TRUE 1
#define FALSE 0
#define NAME_SIZE 51
#define ARRAYAD_SIZE 1000
#define ADTEXT_SIZE 65
#define SECTOR_MIN 0
#define SECTOR_MAX 999

typedef struct
{
	int id;
	int clientID;
	int sector;
	char adText[ADTEXT_SIZE];
	int isEmpty;
	int isActive;
}Advertisement;

int advertisement_init(Advertisement* list, int len);
int advertisement_add(Advertisement *list, int len, Client *fantasmaList, int fantasmaLen);
int advertisement_modify(Advertisement *list, int len);
int advertisement_pauseAd(Advertisement *list, int len, Client *clientList, int clientLen);
int advertisement_reanudeAd(Advertisement *list, int len, Client *clientList, int clientLen);;
int advertisement_searchForNoEmptyAndActive(Advertisement *list, int len);
int advertisement_searchForNoEmptyAndInactive(Advertisement *list, int len);
int advertisement_searchEmpty(Advertisement *list, int len, int *pIndex);
int advertisement_findById(Advertisement *list, int len, int id, int *pIndex);
int advertisement_findByClientId(Advertisement *list, int len, int id);
int advertisement_print(Advertisement *list, int len);
int advertisement_printClientInfoByAdId(Advertisement *list, int len, Client *clientList, int clientLen, int id);
int advertisement_remove(Advertisement *list, int len, int id);
int advertisement_adCounterEachClient(Advertisement *adList, int adLen, int id, int *pCounter);
int advertisement_activeAdCounterEachClient(Advertisement *adList, int adLen, int id, int *pCounter);
int advertisement_pausedAdsQty(Advertisement *adList, int adLen, int *pCounter);
int advertisement_sectorMaxQtyAds(Advertisement *list, int len);
int advertisement_equalSectorQty(Advertisement *list, int len, int sector, int *pCounter);

int advertisement_isArrayEmpty(Advertisement *list, int len);
#endif