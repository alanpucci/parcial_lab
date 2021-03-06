/*
 * utn.h
 *
 *  Created on: Sep 17, 2020
 *      Author: alane
 */

#ifndef UTN_H_
#define UTN_H_

int utn_getString(char mensaje[], char mensajeError[], char pResultado[], int attemps, int limit);
int utn_getInt(char msg[], char msgError[], int *pResult, int attemps, int min, int max);
int utn_getMenu(int *pResult, int attemps, int min, int max);
int utn_getFloat(char msg[], char msgError[], float *pResult, int attemps, int min, int max);
int utn_getCuit(char msg[], char msgError[], char pResult[], int attemps, int limit);
int utn_getStringAlphanumeric(char msg[], char msgError[], char *pResult, int attemps, int len);

#endif /* UTN_H_ */
