#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "cliente.h"

int menu()
{
	int op;
	system("cls");
	printf("M E N U\n");
	printf("1 Inserir Cliente\n");
	printf("2 Listar Clientes\n");
	printf("3 Remover Cliente\n");
	printf("4 Guardar Cliente\n");
	printf("5 Ler Clientes\n");
	printf("6 Editar Clientes\n");
	printf("0 Sair\n");
	printf("Opcao:\n");
	scanf("%d", &op);
	return(op);
}

int main()
{
	Cliente* inicio = NULL;
	char nif[20], nome[100], morada[200];
	float saldo;
	int op;
	do
	{
		op = menu();
		switch (op)
		{
		case 1:
			system("cls");
			printf("NIF: ");
			scanf("%s", nif);
			printf("Nome: ");
			scanf("%s", nome);
			printf("Morada: ");
			scanf("%s", morada);
			printf("Saldo: ");
			scanf("%f", &saldo);
			inicio = inserirCliente(inicio, nif, nome, morada, saldo);
			system("pause");
			break;
		case 2:
			system("cls");
			listarCliente(inicio);
			system("pause");
			break;
		case 3:
			system("cls");
			printf("NIF: ");
			scanf("%s", nif);
			inicio = removerCliente(inicio, nif);
			system("pause");
			break;
		case 4:
			system("cls");
			guardarClientes(inicio);
			system("pause");
			break;
		case 5:
			system("cls");
			inicio = lerCliente();
			system("pause");
			break;
		case 6:
			system("cls");
			printf("Insira o NIF do cliente que pretende editar:\n");
			printf("NIF: ");
			scanf("%s", nif);
			getchar();
			editarCliente(inicio, nif);
			system("pause");
			break;
		case 0:
			printf("Adeus!\n");
			break;
		default:
			printf("Opcao invalida!\n");
		}
	} while (op != 0);
	return 0;
}