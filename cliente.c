#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <string.h>
#include "cliente.h"

// Função que guarda a lista de clientes em um arquivo de texto
int guardarClientes(Cliente* inicio)
{
	// Declara e inicializa o ponteiro de arquivo fp com a abertura do arquivo "clientes.txt" para escrita
	FILE* fp;
	fp = fopen("./clientes.txt", "w");

	// Verifica se o arquivo foi aberto corretamente
	if (fp != NULL)
	{
		// Declara um ponteiro auxiliar que aponta para o início da lista de clientes
		Cliente* aux = inicio;

		// Percorre a lista de clientes e grava as informações de cada cliente no arquivo de texto
		while (aux != NULL)
		{
			fprintf(fp, "%s;%s;%s;%s;%s;%f\n", aux->nif, aux->nome, aux->username, aux->password, aux->morada, aux->saldo);
			aux = aux->prox;
		}

		// Fecha o arquivo e libera a memória do ponteiro auxiliar
		fclose(fp);
		free(aux);

		// Retorna 1 para indicar que a operação foi bem-sucedida
		return(1);
	}
	else
	{
		// Retorna 0 para indicar que a operação falhou
		return(0);
	}
}

// Função que lê a lista de clientes a partir de um arquivo de texto
Cliente* lerCliente()
{
	// Declara um ponteiro de arquivo fp e os arrays de caracteres para armazenar as informações de cada cliente
	FILE* fp;
	char n[20]; // NIF
	char nom[100]; // Nome
	char userNam[100]; // Username
	char pass[30]; // Password
	char mor[200]; // Morada
	float sal; // Saldo

	// Declara um ponteiro auxiliar para apontar para o início da lista de clientes
	Cliente* aux = NULL;

	// Abre o arquivo "clientes.txt" para leitura
	fp = fopen("./clientes.txt", "r");

	// Verifica se o arquivo foi aberto corretamente
	if (fp == NULL)
	{
		// Se houve um erro na abertura do arquivo, imprime uma mensagem de erro e retorna NULL
		printf("Erro ao abrir o ficheiro de clientes\n");
		return NULL;
	}

	// Lê cada linha do arquivo de texto e armazena as informações em um novo cliente, que é inserido na lista ligada
	char line[350];
	while (fgets(line, 350, fp) != NULL)
	{
		sscanf(line, "%[^;];%[^;];%[^;];%[^;];%[^;];%f\n", n, nom, userNam, pass, mor, &sal);
		aux = inserirCliente(aux, n, nom, userNam, pass, mor, sal);
	}

	// Fecha o arquivo e retorna o ponteiro para o início da lista de clientes
	fclose(fp);
	return aux;
}

// Inserção de um novo registo
Cliente* inserirCliente(Cliente* inicio, char n[], char nom[], char userNam[], char pass[], char mor[], float sal)
{
	// Verifica se o cliente já existe
	if (!existeCliente(inicio, n))
	{
		// Aloca espaço para um novo cliente
		Cliente* novo = malloc(sizeof(Cliente));

		// Verifica se a alocação foi bem-sucedida
		if (novo != NULL)
		{
			// Copia os valores para o novo cliente
			strcpy(novo->nif, n);
			strcpy(novo->nome, nom);
			strcpy(novo->username, userNam);
			strcpy(novo->password, pass);
			strcpy(novo->morada, mor);
			novo->saldo = sal;

			// Insere o novo cliente no início da lista
			novo->prox = inicio;

			// Retorna o novo início da lista
			return novo;
		}
		else
		{
			// Se a alocação falhar, retorna o início da lista original
			return inicio;
		}
	}
}

// listar na consola o conteúdo da lista ligada
void listarCliente(Cliente* inicio)
{
	// Percorre a lista até o final
	while (inicio != NULL)
	{
		// Imprime os valores do cliente
		printf("%s %s %s %s %s %f\n", inicio->nif, inicio->nome, inicio->username, inicio->password, inicio->morada, inicio->saldo);

		// Avança para o próximo cliente
		inicio = inicio->prox;
	}
}

// verificar se o cliente com o NIF fornecido já existe na lista ligada
int existeCliente(Cliente* inicio, char* nif)
{
	Cliente* aux = inicio;
	while (aux != NULL)
	{
		if (strcmp(aux->nif, nif) == 0) // verifica se os NIFs são iguais
		{
			return(1); // retorna 1 caso o cliente já exista na lista
		}
		aux = aux->prox; // avança para o próximo elemento da lista
	}
	free(aux); // libera a memória alocada para o último elemento da lista (que é NULL)
	return(0); // retorna 0 caso o cliente não exista na lista
}

char* loginCliente(Cliente* inicio, char* nomeUtilizador, char* palavraPasse)
{
	Cliente* aux = inicio;
	while (aux != NULL)
	{
		if (strcmp(aux->username, nomeUtilizador) == 0 && strcmp(aux->password, palavraPasse) == 0)
		{
			// If the username and password match, return the nif
			return aux->nif;
		}
		aux = aux->prox;
	}
	// If no match is found, return NULL
	return NULL;
}

// remover um cliente a partir do seu NIF
Cliente* removerCliente(Cliente* inicio, char* n)
{
	Cliente* anterior = NULL, * atual = inicio, * aux;

	if (atual == NULL) // se a lista estiver vazia, retorna NULL
	{
		return NULL;
	}
	else if (strcmp(atual->nif, n) == 0) // se o primeiro elemento tiver o NIF a remover
	{
		aux = atual->prox; // armazena o próximo elemento
		free(atual); // libera a memória alocada para o elemento a remover
		return(aux); // retorna o próximo elemento como novo início da lista
	}
	else
	{
		while ((atual != NULL) && (strcmp(atual->nif, n) != 0)) // enquanto não encontrar o elemento a remover
		{
			anterior = atual; // armazena o elemento atual como elemento anterior
			atual = atual->prox; // avança para o próximo elemento da lista
		}
		if (atual == NULL) // se não encontrar o elemento a remover, retorna o início da lista
		{
			return inicio;
		}
		else // caso contrário, remove o elemento e retorna o início da lista
		{
			anterior->prox = atual->prox; // faz com que o elemento anterior aponte para o próximo elemento do elemento a remover
			free(atual); // libera a memória alocada para o elemento a remover
			return inicio;
		}
	}
}

// editar um cliente a partir do seu NIF
void editarCliente(Cliente* inicio, char* nif)
{
	Cliente* atual = inicio; // começa no início da lista

	while (atual != NULL) // enquanto não chegou ao final da lista
	{
		if (strcmp(atual->nif, nif) == 0) // se encontrou o cliente com o NIF dado
		{
			printf("Editar cliente: %s\n", atual->nome);
			printf("Digite o novo nome: ");
			fgets(atual->nome, 100, stdin); // lê o novo nome
			strtok(atual->nome, "\n"); // remove o caractere de nova linha adicionado pelo fgets

			printf("Editar cliente: %s\n", atual->username);
			printf("Digite o novo nome: ");
			fgets(atual->username, 100, stdin); // lê o novo nome
			strtok(atual->username, "\n"); // remove o caractere de nova linha adicionado pelo fgets

			printf("Editar cliente: %s\n", atual->password);
			printf("Digite o novo nome: ");
			fgets(atual->password, 100, stdin); // lê o novo nome
			strtok(atual->password, "\n"); // remove o caractere de nova linha adicionado pelo fgets

			printf("Digite a nova morada: ");
			fgets(atual->morada, 200, stdin); // lê a nova morada
			strtok(atual->morada, "\n"); // remove o caractere de nova linha adicionado pelo fgets

			printf("Digite o novo saldo: ");
			scanf("%f", &atual->saldo); // lê o novo saldo
			getchar(); // remove o caractere de nova linha deixado pelo scanf

			printf("Cliente editado com sucesso.\n");
			return;
		}
		atual = atual->prox; // avança para o próximo cliente na lista
	}

	printf("Cliente nao encontrado.\n"); // se chegou aqui, o cliente não foi encontrado
}

float consultarSaldo(Cliente* inicio, char* nif)
{
	Cliente* atual = inicio;
	while (atual != NULL)
	{
		if (strcmp(atual->nif, nif) == 0)
		{
			return atual->saldo;
		}
		atual = atual->prox;
	}
	return -1.0; // indicate that the nif was not found
}

float carregarSaldo(Cliente* inicio, char* nif, float valor)
{
	Cliente* atual = inicio;
	while (atual != NULL)
	{
		if (strcmp(atual->nif, nif) == 0)
		{
			atual->saldo += valor;
			return atual->saldo;
		}
		atual = atual->prox;
	}
	return -1;
}