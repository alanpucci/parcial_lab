/*
 * Cliente.h
 *
 *  Created on: Nov 21, 2020
 *      Author: alane
 */

#ifndef CLIENTE_H_
#define CLIENTE_H_
#define NAME_SIZE 51
#define CUIT_SIZE 20

typedef struct{
	int id;
	char name[NAME_SIZE];
	char lastName[NAME_SIZE];
	char cuit[CUIT_SIZE];
}Cliente;

Cliente* cliente_new();
Cliente* cliente_newWithParameters(int id, char* name, char* lastName, char* cuit);
Cliente* cliente_newWithParametersTxt(char* id, char* name, char* lastName, char* cuit);
void cliente_delete(Cliente* this);

int cliente_getId(void* this, int* pResult);
int cliente_setId(void* this, int id);
int cliente_setIdTxt(void* this, char* id);

int cliente_getName(void* this, char* pResult);
int cliente_setName(void* this, char* name);

int cliente_getLastName(void* this, char* pResult);
int cliente_setLastName(void* this, char* lastName);

int cliente_getCuit(void* this, char* pResult);
int cliente_setCuit(void* this, char* cuit);

int cliente_print(void* this);
//int cliente_compareCuit(void* this, char* cuit);

#endif /* CLIENTE_H_ */
