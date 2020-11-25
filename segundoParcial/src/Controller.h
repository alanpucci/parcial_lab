#ifndef CONTROLLER_H_
#define CONTROLLER_H_
#include "LinkedList.h"

int controller_loadClientFromText(char* path, LinkedList* clientList);
int controller_loadSellFromText(char* path, LinkedList* sellList);
int controller_addClient(LinkedList* clientList);
int controller_saveClientAsText(char* path, LinkedList* clientList);
int controller_saveSellsAsText(char* path, LinkedList* sellList);
int controller_sellPoster(LinkedList* clientList, LinkedList* sellList);
int controller_modifySell(LinkedList* clientList, LinkedList* sellList);
int controller_chargePoster(LinkedList* clientList, LinkedList* sellList);
int controller_saveClientsWithUnchargedPosters(LinkedList* clientList, LinkedList* sellList);
int controller_saveClientsWithChargedPosters(LinkedList* clientList, LinkedList* sellList);
int controller_report(LinkedList* clientList, LinkedList* sellList);

int controller_print(LinkedList* clientList, int (*pFunc)(void*));

#endif /* CONTROLLER_H_ */
