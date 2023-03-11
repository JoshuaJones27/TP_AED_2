#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <string.h>
#include "reserva.h"

int guardarReserva(Reserva* inicio)
{
	FILE* fp;
	fp = fopen("./reservas.txt", "w");

	if (fp != NULL)
	{
		Reserva* aux = inicio;
		while (aux != NULL)
		{
			fprintf(fp, "%s;%s;%s\n", aux->idReserva, aux->nifCliente, aux->idMeioEletrico);
			aux = aux->prox;
		}
		fclose(fp);
		free(aux);
		return(1);
	}
	else
	{
		return(0);
	}
}
Reserva* lerReserva()
{
	FILE* fp;

	char idReserv[20]; // Id reserva
	char nifClient[20]; // Nif do cliente
	char idMeioEletric[50]; // ID do meio el�trico

	Reserva* aux = NULL;

	fp = fopen("./reserva.txt", "r");
	if (fp == NULL)
	{
		printf("Erro ao abrir o ficheiro de reserva\n");
		return NULL;
	}

	char line[350];
	while (fgets(line, 350, fp) != NULL)
	{
		sscanf(line, "%[^;];%[^;];%[^;]\n", idReserv, nifClient, idMeioEletric);
		aux = inserirCliente(aux, idReserv, nifClient, idMeioEletric);
	}

	fclose(fp);
	return aux;
}
// Inser��o de um novo registo
Reserva* inserirReserva(Reserva* inicio, char idReserv[], char nifClient[], char idMeioEletric[])
{
	if (!existeidReserva(inicio, idReserv))
	{
		Reserva* novo = malloc(sizeof(idReserv));
		if (novo != NULL)
		{
			strcpy(novo->idReserva, idReserv);
			strcpy(novo->nifCliente, nifClient);
			strcpy(novo->idMeioEletrico, idMeioEletric);
			novo->prox = inicio;
			return novo;
		}
		else
		{
			return inicio;
		}
	}
}
// listar na consola o conte�do da lista ligada
void listarReserva(Reserva* inicio)
{
	while (inicio != NULL)
	{
		printf("%s %s %s\n", inicio->idReserva, inicio->nifCliente, inicio->idMeioEletrico);
		inicio = inicio->prox;
	}
}
int existeidReserva(Reserva* inicio, char* idReserva)
{
	Reserva* aux = inicio;
	while (aux != NULL)
	{
		if (strcmp(aux->idReserva, idReserva) == 0)
		{
			return(1);
		}
		aux = aux->prox;
	}
	free(aux);
	return(0);
}

// remover um cliente a partir do seu Id de reserva
Reserva* removerReserva(Reserva* inicio, char* idReserv)
{
	Reserva* anterior = NULL, * atual = inicio, * aux;

	if (atual == NULL)
	{
		return NULL;
	}
	else if (strcmp(atual->idReserva, idReserv) == 0)
	{
		aux = atual->prox;
		free(atual);
		return(aux);
	}
	else
	{
		while ((atual != NULL) && (strcmp(atual->idReserva, idReserv) != 0))
		{
			anterior = atual;
			atual = atual->prox;
		}
		if (atual == NULL)
		{
			return inicio;
		}
		else
		{
			anterior->prox = atual->prox;
			free(atual);
			return inicio;
		}
	}
}

void editarReserva(Reserva* inicio, char* idReserva)
{
	Reserva* atual = inicio;

	while (atual != NULL)
	{
		if (strcmp(atual->idReserva, idReserva) == 0)
		{
			printf("Editar reserva: %s\n", atual->nifCliente);
			printf("Digite o novo NIF do cliente: ");
			fgets(atual->nifCliente, 20, stdin);
			strtok(atual->nifCliente, "\n");

			printf("Digite o novo ID do meio eletrico: ");
			fgets(atual->idMeioEletrico, 50, stdin);
			strtok(atual->idMeioEletrico, "\n");

			printf("Reserva editada com sucesso.\n");
			return;
		}
		atual = atual->prox;
	}

	printf("Reserva nao encontrado.\n");
}