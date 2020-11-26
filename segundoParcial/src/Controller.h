#ifndef CONTROLLER_H_
#define CONTROLLER_H_
#include "LinkedList.h"

int controller_loadClientFromText(char* path, LinkedList* clientList);
int controller_loadSaleFromText(char* path, LinkedList* sellList);
int controller_addClient(LinkedList* clientList);
int controller_saveClientAsText(char* path, LinkedList* clientList);
int controller_saveSalesAsText(char* path, LinkedList* sellList);
int controller_addSale(LinkedList* clientList, LinkedList* sellList);
int controller_modifySale(LinkedList* clientList, LinkedList* sellList);
int controller_chargePoster(LinkedList* clientList, LinkedList* sellList);
int controller_saveClientsWithUnchargedPosters(LinkedList* clientList, LinkedList* sellList);
int controller_saveClientsWithChargedPosters(LinkedList* clientList, LinkedList* sellList);
int controller_print(LinkedList* list, int (*pFunc)(void*));
int controller_findByIdGen(LinkedList* list, int (*pFunc)(void*,int*), int id, int* index);

#endif /* CONTROLLER_H_ */
