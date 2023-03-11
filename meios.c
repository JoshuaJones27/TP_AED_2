#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <string.h>
#include "meios.h"

int guardarMeiosEletricos(MeioEletrico* inicio)
{
	FILE* fp;
	fp = fopen("./meios.txt", "w");

	if (fp != NULL)
	{
		MeioEletrico* aux = inicio;
		while (aux != NULL)
		{
			fprintf(fp, "%s;%s;%f;%f;%s\n", aux->tipo, aux->id, aux->carga_bateria, aux->custo_hora, aux->geocodigo);
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

MeioEletrico* lerMeioEletrico()
{
	FILE* fp;

	char tip[50]; //tipo
	char i[50]; //id
	float carga_bateri; //carga bateria
	float custo_hor; //custo por hora
	char geocodig[50]; //geocodigo
	MeioEletrico* aux = NULL;

	fp = fopen("./meios.txt", "r");
	if (fp == NULL)
	{
		printf("Erro ao abrir o ficheiro de meios de transporte\n");
		return NULL;
	}

	char line[350];
	while (fgets(line, 350, fp) != NULL)
	{
		sscanf(line, "%[^;];%[^;];%f;%f;%[^;]\n", tip, i, &carga_bateri, &custo_hor, geocodig);
		aux = inserirMeioEletrico(aux, tip, i, carga_bateri, custo_hor, geocodig);
	}
	fclose(fp);
	return aux;
}

// Inser��o de um novo registo
MeioEletrico* inserirMeioEletrico(MeioEletrico* inicio, char tip[], char i[], float carga_bateri, float custo_hor, char geocodig[])
{
	if (!existeMeioEletrico(inicio, i))
	{
		MeioEletrico* novo = malloc(sizeof(MeioEletrico));
		if (novo != NULL)
		{
			strcpy(novo->tipo, tip);
			strcpy(novo->id, i);
			novo->carga_bateria = carga_bateri;
			novo->custo_hora = custo_hor;
			strcpy(novo->geocodigo, geocodig);
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
void listarMeioEletrico(MeioEletrico* inicio)
{
	while (inicio != NULL)
	{
		printf("%s %s %f %f %s\n", inicio->tipo, inicio->id, inicio->carga_bateria, inicio->custo_hora, inicio->geocodigo);
		inicio = inicio->prox;
	}
}

int existeMeioEletrico(MeioEletrico* inicio, char* id)
{
	MeioEletrico* aux = inicio;
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
MeioEletrico* removerMeioEletrico(MeioEletrico* inicio, char* i)
{
	MeioEletrico* anterior = NULL, * atual = inicio, * aux;

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
void editarMeioEletrico(MeioEletrico* inicio, char* id)
{
	MeioEletrico* atual = inicio;

	while (atual != NULL)
	{
		if (strcmp(atual->id, id) == 0)
		{
			printf("Editar meio de transporte: %s\n", atual->tipo);
			printf("Digite o novo tipo de transporte: ");
			fgets(atual->tipo, 50, stdin);
			strtok(atual->tipo, "\n");

			printf("Digite a nova carga de bateria: ");
			scanf("%f", &atual->carga_bateria);
			getchar();

			printf("Digite o novo custo por hora: ");
			scanf("%f", &atual->custo_hora);
			getchar();

			printf("Digite o novo geocodigo: ");
			fgets(atual->geocodigo, 50, stdin);
			strtok(atual->geocodigo, "\n");

			printf("Meio de transporte editado com sucesso.\n");
			return;
		}
		atual = atual->prox;
	}

	printf("Meio de transporte nao encontrado.\n");
}