#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "cliente.h"
#include "gestor.h"
#include "meios.h"

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

void menuCliente();

//int menuLogin()
//{
//	Cliente* inicio = NULL;
//	inicio = lerCliente();
//	int opcao;
//	char nomeUtilizador[100], palavraPasse[30];
//	system("cls");
//	printf("Menu Login\n");
//	printf("Pressione 1 para Cliente\n");
//	printf("Pressione 2 para Gestor\n");
//	printf("Opcao:");
//	scanf("%d", &opcao);
//	switch (opcao)
//	{
//	case 1:
//		printf("Insira os seus dados:\n");
//		printf("Nome utilizador: ");
//		scanf("%s", nomeUtilizador);
//		printf("Password: ");
//		scanf("%s", palavraPasse);
//		if (loginCliente(inicio, nomeUtilizador, palavraPasse))
//		{
//			printf("Login efetuado com sucesso!\n");
//			system("pause");
//			menuCliente(inicio->nif);
//		}
//		else
//		{
//			printf("Dados incorretos!\n");
//			system("pause");
//		}
//		break;
//
//		/*case 2:
//			printf("Insira os seus dados:\n");
//			if ()
//			{
//			}
//			else
//			{
//				printf("Dados incorretos!\n");
//				system("pause");
//			}
//			break;*/
//	default:
//		break;
//	}
//}

void menuLogin()
{
	Cliente* inicio = NULL;
	inicio = lerCliente();
	int opcao;
	char nomeUtilizador[100], palavraPasse[30];
	char* nif; // Declare a variable to hold the nif value
	system("cls");
	printf("Menu Login\n");
	printf("Pressione 1 para Cliente\n");
	printf("Pressione 2 para Gestor\n");
	printf("Opcao:");
	scanf("%d", &opcao);
	switch (opcao)
	{
	case 1:
		printf("Insira os seus dados:\n");
		printf("Nome utilizador: ");
		scanf("%s", nomeUtilizador);
		printf("Password: ");
		scanf("%s", palavraPasse);
		nif = loginCliente(inicio, nomeUtilizador, palavraPasse); // Assign the returned nif to the variable
		if (nif != NULL)
		{
			printf("Login efetuado com sucesso!\n");
			system("pause");
			menuCliente(inicio, nif); // Pass the nif to the menuCliente function
		}
		else
		{
			printf("Dados incorretos!\n");
			system("pause");
		}
		break;
	default:
		break;
	}
}

void menuCliente(Cliente* inicio, char* nif)
{
	printf("Menu Cliente\n");
	printf("%s\n", nif);
	int op;
	do
	{
		printf("1 - Consultar Saldo\n");
		printf("2 - Carregar Saldo\n");
		printf("0 - Logout\n");
		printf("Opcao:");
		scanf("%d", &op);
		switch (op)
		{
		case 1:
		{
			float saldo = consultarSaldo(inicio, nif);
			if (saldo >= 0)
			{
				printf("Saldo: %.2f\n", saldo);
			}
			else
			{
				printf("NIF nao encontrado\n");
			}
			system("pause");
			break;
		}
		case 2:
		{
			float valor;
			printf("Insira o valor a carregar: ");
			scanf("%f", &valor);
			if (carregarSaldo(inicio, nif, valor) != -1)
			{
				printf("Carregamento efetuado com sucesso!\n");
			}
			else
			{
				printf("Nao foi possivel carregar o saldo!\n");
			}
			system("pause");
			break;
		}
		}
	} while (op != 0);
}

int menuGestor()
{
}

int main()
{
	menuLogin();
	return(0);
}