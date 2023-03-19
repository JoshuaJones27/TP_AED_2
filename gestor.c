#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <string.h>
#include "gestor.h"

int guardarGestores(Gestor* inicio)
{
	FILE* fp;
	fp = fopen("./gestores.txt", "w");

	if (fp != NULL)
	{
		Gestor* aux = inicio;
		while (aux != NULL)
		{
			fprintf(fp, "%d;%s;%s;%s\n", aux->id, aux->nome, aux->email, aux->password);
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

Gestor* lerGestor()
{
	FILE* fp;

	char i[50]; //id
	char nom[100]; //Nome
	char emai[100]; //email
	char pass[100]; //password
	Gestor* aux = NULL;

	fp = fopen("./gestores.txt", "r");
	if (fp == NULL)
	{
		printf("Erro ao abrir o ficheiro de gestores\n");
		return NULL;
	}

	char line[350];
	while (fgets(line, 350, fp) != NULL)
	{
		sscanf(line, "%[^;];%[^;];%[^;];%[^;];%[^;];%f\n", i, nom, emai, pass);
		aux = inserirGestor(aux, i, nom, emai, pass);
	}

	fclose(fp);
	return aux;
}

char* loginGestor(Gestor* inicio, char* email, char* palavraPasse)
{
	Gestor* aux = inicio;
	while (aux != NULL)
	{
		if (strcmp(aux->email, email) == 0 && strcmp(aux->password, palavraPasse) == 0)
		{
			// If the username and password match, return the nif
			return aux->id;
		}
		aux = aux->prox;
	}
	// If no match is found, return NULL
	return NULL;
}

//Inser��o de um novo registo
Gestor* inserirGestor(Gestor* inicio, char i[], char nom[], char emai[], char pass[])
{
	if (!existeGestor(inicio, i))
	{
		Gestor* novo = malloc(sizeof(Gestor));
		if (novo != NULL)
		{
			strcpy(novo->id, i);
			strcpy(novo->nome, nom);
			strcpy(novo->email, emai);
			strcpy(novo->password, pass);
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
void listarGestor(Gestor* inicio)
{
	while (inicio != NULL)
	{
		printf("%d %s %s %s", inicio->id, inicio->nome, inicio->email, inicio->password);
		inicio = inicio->prox;
	}
}

int existeGestor(Gestor* inicio, int* id)
{
	Gestor* aux = inicio;
	while (aux != NULL)
	{
		if (strcmp(aux->id, id) == 0)
		{
			return(1);
		}
		aux = aux->prox;
	}
	free(aux);
	return(0);
}

// remover um cliente a partir do seu ID

Gestor* removerGestor(Gestor* inicio, int* i)
{
	Gestor* anterior = NULL, * atual = inicio, * aux;

	if (atual == NULL)
	{
		return NULL;
	}
	else if (strcmp(atual->id, i) == 0)
	{
		aux = atual->prox;
		free(atual);
		return(aux);
	}
	else
	{
		while ((atual != NULL) && (strcmp(atual->id, i) != 0))
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

void editarGestor(Gestor* inicio, char* id)
{
	Gestor* atual = inicio;

	while (atual != NULL)
	{
		if (strcmp(atual->id, id) == 0)
		{
			printf("Editar gestor: %s\n", atual->nome);
			printf("Digite o novo nome: ");
			fgets(atual->nome, 100, stdin);
			strtok(atual->nome, "\n");

			printf("Digite o seu novo email: ");
			fgets(atual->email, 100, stdin);
			strtok(atual->email, "\n");

			printf("Digite a sua nova password: ");
			fgets(atual->password, 30, stdin);
			strtok(atual->password, "\n");

			printf("Gestor editado com sucesso.\n");
			return;
		}
		atual = atual->prox;
	}

	printf("Gestor nao encontrado.\n");
}