#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <string.h>
#include "cliente.h"

int guardarClientes(Cliente* inicio)
{
	FILE* fp;
	fp = fopen("./clientes.txt", "w");

	if (fp != NULL)
	{
		Cliente* aux = inicio;
		while (aux != NULL)
		{
			fprintf(fp, "%s;%s;%s;%f\n", aux->nif, aux->nome, aux->morada, aux->saldo);
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

Cliente* lerCliente()
{
	FILE* fp;

	char n[20]; // NIF
	char nom[100]; // Nome
	char mor[200]; // Morada
	float sal; // Saldo
	Cliente* aux = NULL;

	fp = fopen("./clientes.txt", "r");
	if (fp == NULL)
	{
		printf("Erro ao abrir o ficheiro de clientes\n");
		return NULL;
	}

	char line[350];
	while (fgets(line, 350, fp) != NULL)
	{
		sscanf(line, "%[^;];%[^;];%[^;];%f\n", n, nom, mor, &sal);
		aux = inserirCliente(aux, n, nom, mor, sal);
	}

	fclose(fp);
	return aux;
}

// Inserção de um novo registo
Cliente* inserirCliente(Cliente* inicio, char n[], char nom[], char mor[], float sal)
{
	if (!existeCliente(inicio, n))
	{
		Cliente* novo = malloc(sizeof(Cliente));
		if (novo != NULL)
		{
			strcpy(novo->nif, n);
			strcpy(novo->nome, nom);
			strcpy(novo->morada, mor);
			novo->saldo = sal;
			novo->prox = inicio;
			return novo;
		}
		else
		{
			return inicio;
		}
	}
}

// listar na consola o conteúdo da lista ligada
void listarCliente(Cliente* inicio)
{
	while (inicio != NULL)
	{
		printf("%s %s %s %f\n", inicio->nif, inicio->nome, inicio->morada, inicio->saldo);
		inicio = inicio->prox;
	}
}

int existeCliente(Cliente* inicio, char* nif)
{
	Cliente* aux = inicio;
	while (aux != NULL)
	{
		if (strcmp(aux->nif, nif) == 0)
		{
			return(1);
		}
		aux = aux->prox;
	}
	free(aux);
	return(0);
}

// remover um cliente a partir do seu NIF
Cliente* removerCliente(Cliente* inicio, char* n)
{
	Cliente* anterior = NULL, * atual = inicio, * aux;

	if (atual == NULL)
	{
		return NULL;
	}
	else if (strcmp(atual->nif, n) == 0)
	{
		aux = atual->prox;
		free(atual);
		return(aux);
	}
	else
	{
		while ((atual != NULL) && (strcmp(atual->nif, n) != 0))
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

void editarCliente(Cliente* inicio, char* nif)
{
	Cliente* atual = inicio;

	while (atual != NULL)
	{
		if (strcmp(atual->nif, nif) == 0)
		{
			printf("Editar cliente: %s\n", atual->nome);
			printf("Digite o novo nome: ");
			fgets(atual->nome, 100, stdin);
			strtok(atual->nome, "\n"); // remove the newline character from the input

			printf("Digite a nova morada: ");
			fgets(atual->morada, 200, stdin);
			strtok(atual->morada, "\n");

			printf("Digite o novo saldo: ");
			scanf("%f", &atual->saldo);
			getchar(); // consume the newline character left in the input stream

			printf("Cliente editado com sucesso.\n");
			return;
		}
		atual = atual->prox;
	}

	printf("Cliente nao encontrado.\n");
}