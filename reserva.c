#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <string.h>
#include "reserva.h"
#include "meios.h"

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
//Reserva* lerReserva()
//{
//	FILE* fp;
//
//	char idReserv[20]; // Id reserva
//	char nifClient[20]; // Nif do cliente
//	char idMeioEletric[50]; // ID do meio el�trico
//
//	Reserva* aux = NULL;
//
//	fp = fopen("./reserva.txt", "r");
//	if (fp == NULL)
//	{
//		printf("Erro ao abrir o ficheiro de reserva\n");
//		return NULL;
//	}
//
//	char line[350];
//	while (fgets(line, 350, fp) != NULL)
//	{
//		sscanf(line, "%[^;];%[^;];%[^;]\n", idReserv, nifClient, idMeioEletric);
//		aux = inserirReserva(aux, idReserv, nifClient, idMeioEletric);
//	}
//
//	fclose(fp);
//	return aux;
//}

//int ultimoIdReserva = 0;

//void readLastReservaIdFromFile() {
//	FILE* fp = fopen("./reservas.txt", "r");
//	if (fp == NULL) {
//		printf("Error opening file.\n");
//		exit(1);
//	}
//
//	char line[100];
//	while (fgets(line, 100, fp) != NULL) {
//		char* idReserva = strtok(line, ",");
//		ultimoIdReserva = atoi(idReserva);
//	}
//
//	fclose(fp);
//}
//
//void writeLastReservaIdToFile() {
//	FILE* fp = fopen("./reservas.txt", "w");
//	if (fp == NULL) {
//		printf("Error opening file.\n");
//		exit(1);
//	}
//
//	fprintf(fp, "%d\n", ultimoIdReserva);
//
//	fclose(fp);
//}

//Reserva* inserirReserva(Reserva* inicio, char idReserv[], char nifClient[], char idMeioEletric[]) {
//	// Aloca espaço para uma nova reserva
//	Reserva* novaReserva = malloc(sizeof(Reserva));
//
//	// Verifica se a alocação foi bem-sucedida
//	if (novaReserva != NULL) {
//		// Lê o último id de reserva a partir do arquivo
//		readLastReservaIdFromFile();
//
//		// Incrementa o último id de reserva
//		ultimoIdReserva++;
//
//		// Atribui o novo valor de idReserva à nova reserva
//		sprintf(novaReserva->idReserva, "%d", ultimoIdReserva);
//
//		// Copia os valores para a nova reserva
//		strcpy(novaReserva->nifCliente, nifCliente);
//		strcpy(novaReserva->idMeioEletrico, idMeioEletrico);
//
//		// Insere a nova reserva no início da lista
//		novaReserva->prox = inicio;
//
//		// Salva o último id de reserva no arquivo
//		writeLastReservaIdToFile();
//
//		// Retorna o novo início da lista
//		return novaReserva;
//	}
//	else {
//		// Se a alocação falhar, retorna o início da lista original
//		return inicio;
//	}
//}

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