//Al entrar al punto 4 preguntar si hay alguna venta sin cobrar

#include <stdio.h>
#include <stdlib.h>
#include "Linkedlist.h"
#include "Controller.h"
#include "Info.h"
#include "utn.h"
#include "menu.h"

int main(void) {
	setbuf(stdout,NULL);
	int menuOption;
	LinkedList* listaCliente = ll_newLinkedList();
	LinkedList* listaVenta = ll_newLinkedList();

	controller_loadClientFromText("clientes.txt", listaCliente);
	controller_loadSaleFromText("ventas.txt", listaVenta);
	do
	{
		if(!utn_getMenu(&menuOption, 2, 1, 8))
		{
			switch(menuOption)
			{
			case 1:
				if(!controller_addClient(listaCliente))
				{
					printf("\nCliente ingresado exitosamente\n");
					controller_saveClientAsText("clientes.txt", listaCliente);
				}
			break;
			case 2:
				if(!ll_isEmpty(listaCliente))
				{
					if(!controller_addSale(listaCliente, listaVenta))
					{
						printf("\nVenta 'a cobrar' cargada exitosamente\n");
						controller_saveSalesAsText("ventas.txt", listaVenta);
					}
				}
				else
				{
					printf("\nNo hay clientes cargados\n");
				}
			break;
			case 3:
				if(!ll_isEmpty(listaCliente) && !ll_isEmpty(listaVenta))
				{
					if(!controller_modifySale(listaCliente, listaVenta))
					{
						printf("\nVenta modificada exitosamente\n");
						controller_saveSalesAsText("ventas.txt", listaVenta);
					}
				}
				else
				{
					printf("\nNo hay cliente o ventas cargadas\n");
				}
			break;
			case 4:
				if(!ll_isEmpty(listaCliente) && !ll_isEmpty(listaVenta))
				{
					if(!controller_chargePoster(listaCliente, listaVenta))
					{
						printf("\nVenta cobrada exitosamente\n");
						controller_saveSalesAsText("ventas.txt", listaVenta);
					}
				}
				else
				{
					printf("\nNo hay cliente o ventas cargadas\n");
				}
			break;
			case 5:
				if(!ll_isEmpty(listaCliente) && !ll_isEmpty(listaVenta))
				{
					if(!controller_saveClientsWithChargedPosters(listaCliente, listaVenta))
					{
						printf("\nArchivo guardado exitosamente\n");
					}
				}
				else
				{
					printf("\nNo hay cliente o ventas cargadas\n");
				}
			break;
			case 6:
				if(!ll_isEmpty(listaCliente) && !ll_isEmpty(listaVenta))
				{
					if(!controller_saveClientsWithUnchargedPosters(listaCliente, listaVenta))
					{
						printf("\nArchivo guardado exitosamente\n");
					}
				}
				else
				{
					printf("\nNo hay cliente o ventas cargadas\n");
				}
			break;
			case 7:
				if(!ll_isEmpty(listaCliente) && !ll_isEmpty(listaVenta))
				{
					if(!controller_report(listaCliente, listaVenta))
					{
						printf("\nFin del reporte\n");
					}
				}
			break;
			}
		}
	}while(menuOption!=8);
	printf("Adios!");
	return EXIT_SUCCESS;
}
