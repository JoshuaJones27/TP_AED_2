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
			fprintf(fp, "%s;%d;%f;%f;%s;%d", aux->tipo, aux->id, aux->carga_bateria, aux->custo_hora, aux->geocodigo, aux->reservado);
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

int guardarMeiosEletricosGestor(MeioEletrico* inicio)
{
	FILE* fp;
	fp = fopen("./meios.txt", "a");

	if (fp != NULL)
	{
		MeioEletrico* aux = inicio;
		while (aux != NULL)
		{
			fprintf(fp, "%s;%d;%f;%f;%s;%d", aux->tipo, aux->id, aux->carga_bateria, aux->custo_hora, aux->geocodigo, aux->reservado);
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
	char id[50]; //id
	float carga_bateri; //carga bateria
	float custo_hor; //custo por hora
	char geocodig[50]; //geocodigo
	int reservad = 0; // initialize to 0
	MeioEletrico* inicio = NULL; // Initialize to NULL
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
		sscanf(line, "%[^;];%[^;];%f;%f;%[^;];%d\n", tip, id, &carga_bateri, &custo_hor, geocodig, &reservad);
		aux = inserirMeioEletrico(aux, tip, atoi(id), carga_bateri, custo_hor, geocodig, reservad);
		if (inicio == NULL) // If this is the first node, set inicio to it
			inicio = aux;
	}
	fclose(fp);
	return inicio;
}

MeioEletrico* inserirMeioEletrico(MeioEletrico* inicio, char* tipo, int id, float carga_bateria, float custo_hora, char* geocodigo, int reservado) {
	MeioEletrico* novo = (MeioEletrico*)malloc(sizeof(MeioEletrico));
	strcpy(novo->tipo, tipo);
	sprintf(novo->id, "%d", id);
	novo->carga_bateria = carga_bateria;
	novo->custo_hora = custo_hora;
	strcpy(novo->geocodigo, geocodigo);
	novo->reservado = reservado;
	novo->prox = NULL; // initialize prox to NULL
	if (inicio == NULL) {
		return novo;
	}
	MeioEletrico* aux = inicio;
	while (aux->prox != NULL) {
		aux = aux->prox;
	}
	aux->prox = novo;
	return inicio;
}

// listar na consola o conte�do da lista ligada
void listarMeioEletrico(MeioEletrico* inicio)
{
	while (inicio != NULL)
	{
		printf("%s %s %.2f %.2f %s %d\n", inicio->tipo, inicio->id, inicio->carga_bateria, inicio->custo_hora, inicio->geocodigo, inicio->reservado);
		inicio = inicio->prox;
	}
}

int existeMeioEletrico(MeioEletrico* inicio, char* id) {
	MeioEletrico* aux = inicio;
	while (aux != NULL) {
		if (strcmp(aux->id, id) == 0) {
			return 1;
		}
		aux = aux->prox;
	}
	return 0;
}

void alterarEstadoMeio(MeioEletrico* inicio, char* idMeioEletrico, int reserva)
{
	MeioEletrico* aux = inicio;
	while (aux != NULL)
	{
		if (strcmp(aux->id, idMeioEletrico) == 0)
		{
			if (aux->reservado == 1) {
				printf("O meio eletrico com o ID %s ja esta reservado!\n", idMeioEletrico);
				return;
			}
			else {
				aux->reservado = 1;
				printf("O meio eletrico com o ID %s foi reservado com sucesso!\n", idMeioEletrico);

				// Open the file in write mode
				FILE* fp = fopen("./meios.txt", "w");
				if (fp == NULL) {
					printf("Erro ao abrir o ficheiro de meios de transporte\n");
					return;
				}

				// Traverse the linked list and write the contents of each node to the file
				MeioEletrico* temp = inicio;
				while (temp != NULL) {
					fprintf(fp, "%s;%s;%f;%f;%s;%d\n", temp->tipo, temp->id, temp->carga_bateria, temp->custo_hora, temp->geocodigo, temp->reservado);
					temp = temp->prox;
				}

				// Close the file
				fclose(fp);

				return;
			}
		}
		aux = aux->prox;
	}
	printf("Meio eletrico nao encontrado!\n");
}

void listarMeiosPorCargaBateria(MeioEletrico* inicio) {
	// First, we need to count the number of meios
	int count = 0;
	MeioEletrico* aux = inicio;
	while (aux != NULL) {
		count++;
		aux = aux->prox;
	}

	// Then, we create an array with the meios and their carga_bateria values
	float* carga_bateria_array = (float*)malloc(sizeof(float) * count);
	MeioEletrico** meio_array = (MeioEletrico**)malloc(sizeof(MeioEletrico*) * count);
	aux = inicio;
	int i = 0;
	while (aux != NULL) {
		meio_array[i] = aux;
		carga_bateria_array[i] = aux->carga_bateria;
		aux = aux->prox;
		i++;
	}

	// We can then sort the arrays by carga_bateria
	for (int i = 0; i < count - 1; i++) {
		for (int j = 0; j < count - i - 1; j++) {
			if (carga_bateria_array[j] < carga_bateria_array[j + 1]) {
				float temp_bateria = carga_bateria_array[j];
				carga_bateria_array[j] = carga_bateria_array[j + 1];
				carga_bateria_array[j + 1] = temp_bateria;

				MeioEletrico* temp_meio = meio_array[j];
				meio_array[j] = meio_array[j + 1];
				meio_array[j + 1] = temp_meio;
			}
		}
	}

	// Finally, we print the sorted array
	printf("Lista de meios eletricos por carga de bateria (de maior para menor):\n");
	for (int i = 0; i < count; i++) {
		printf("Tipo: %s | ID: %s | Carga de bateria: %.2f | Custo por hora: %.2f | Geocodigo: %s | Reservado: %d\n",
			meio_array[i]->tipo, meio_array[i]->id, meio_array[i]->carga_bateria, meio_array[i]->custo_hora, meio_array[i]->geocodigo, meio_array[i]->reservado);
	}

	// We need to free the allocated memory
	free(carga_bateria_array);
	free(meio_array);
}

void listarMeiosPorGeocodigo(MeioEletrico* inicio, char* geocodigo) {
	MeioEletrico* aux = inicio;
	int found = 0;

	printf("Lista de meios eletricos com o geocodigo %s:\n", geocodigo);
	while (aux != NULL) {
		if (strcmp(aux->geocodigo, geocodigo) == 0) {
			printf("Tipo: %s | ID: %s | Carga de bateria: %.2f | Custo por hora: %.2f | Geocodigo: %s | Reservado: %d\n",
				aux->tipo, aux->id, aux->carga_bateria, aux->custo_hora, aux->geocodigo, aux->reservado);
			found = 1;
		}
		aux = aux->prox;
	}

	if (!found) {
		printf("Nao foram encontrados meios eletricos com o geocodigo %s.\n", geocodigo);
	}
}

// remover um cliente a partir do seu ID
MeioEletrico* removerMeioEletrico(MeioEletrico* inicio, char idMeioEletrico)
{
	MeioEletrico* anterior = NULL, * atual = inicio, * aux;

	if (atual == NULL)
	{
		return NULL;
	}
	else if (atual->id == idMeioEletrico)
	{
		aux = atual->prox;
		free(atual);
		return(aux);
	}
	else
	{
		while ((atual != NULL) && (atual->id != idMeioEletrico))
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

			printf("Digite o estado de reserva: ");
			scanf("%d", &atual->reservado);
			getchar();

			printf("Meio de transporte editado com sucesso.\n");
			return;
		}
		atual = atual->prox;
	}

	printf("Meio de transporte nao encontrado.\n");
}

MeioEletrico* criarMeioEletrico(MeioEletrico* inicio, char* tipo, float carga_bateria, float custo_hora, char* geocodigo, int reservado) {
	MeioEletrico* novo = (MeioEletrico*)malloc(sizeof(MeioEletrico));
	strcpy(novo->tipo, tipo);
	novo->carga_bateria = carga_bateria;
	novo->custo_hora = custo_hora;
	strcpy(novo->geocodigo, geocodigo);
	novo->reservado = reservado;
	novo->prox = NULL; // initialize prox to NULL
	if (inicio == NULL) {
		novo->id[0] = 1; // if the list is empty, set the first element of the id array to 1
		return novo;
	}
	MeioEletrico* aux = inicio;
	while (aux->prox != NULL) {
		aux = aux->prox;
	}
	int last_id = atoi(aux->id);
	novo->id[0] = last_id + 1; // set the first element of the id array to the last id + 1
	aux->prox = novo;
	return inicio;
}