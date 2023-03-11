#include <stdio.h>

typedef struct cliente {
	char nif[20];
	char nome[100];
	char morada[200];
	float saldo;
	struct cliente* prox;
} Cliente;

Cliente* inserirCliente(Cliente* inicio, char n[], char nom[], char mor[], float sal);
void listarCliente(Cliente* inicio);
int existeCliente(Cliente* inicio, char* nif);
Cliente* removerCliente(Cliente* inicio, char* n);
int guardarClientes(Cliente* inicio);
Cliente* lerCliente();
void editarCliente(Cliente* inicio, char* nif);