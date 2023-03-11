#include <stdio.h>

typedef struct reserva {
	char idReserva[20];
	char nifCliente[20];
	char idMeioEletrico[50];
	struct reserva* prox;
} Reserva;

int guardarReserva(Reserva* inicio);
Reserva* lerReserva();
Reserva* inserirReserva(Reserva* inicio, char idReserv[], char nifClient[], char idMeioEletric[]);
void listarReserva(Reserva* inicio);
int existeidReserva(Reserva* inicio, char* idReserva);
Reserva* removerReserva(Reserva* inicio, char* idReserv);
void editarReserva(Reserva* inicio, char* idReserva);
