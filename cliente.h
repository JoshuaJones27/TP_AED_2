#include <stdio.h>

typedef struct cliente {
	char nif[20];
	char nome[100];
	char username[100];
	char password[30];
	char morada[200];
	float saldo;
	struct cliente* prox;
} Cliente;

Cliente* inserirCliente(Cliente* inicio, char n[], char nom[], char userNam[], char pass[], char mor[], float sal);
void listarCliente(Cliente* inicio);
int existeCliente(Cliente* inicio, char* nif);
char* loginCliente(Cliente* inicio, char nomeUtilizador[], char palavraPasse[]);
Cliente* removerCliente(Cliente* inicio, char* n);
int guardarClientes(Cliente* inicio);
Cliente* lerCliente();
void editarCliente(Cliente* inicio, char* nif);
float consultarSaldo(Cliente* inicio, char* nif);
float carregarSaldo(Cliente* inicio, char* nif, float valor);
Cliente* novoCliente(Cliente* inicio, char n[], char nom[], char userNam[], char pass[], char mor[], float sal);
int guardarClientesAoEliminar(Cliente* inicio);