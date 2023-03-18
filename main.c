#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "cliente.h"
#include "gestor.h"
#include "meios.h"
#include "reserva.h"

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

void menuLogin()
{
	Cliente* inicio = NULL;
	inicio = lerCliente();
	int opcao;
	char nomeUtilizador[100], palavraPasse[30];
	char* nif = NULL; // Initialize the nif variable to NULL
	system("cls");
	printf("Menu Login\n");
	printf("Pressione 1 para Cliente\n");
	printf("Pressione 2 para Gestor\n");
	printf("Opcao:");
	scanf("%d", &opcao);
	switch (opcao)
	{
	case 1:
		while (nif == NULL) // Add a loop to continue until the client successfully logs in or chooses to exit
		{
			printf("Insira os seus dados:\n");
			printf("Nome utilizador: ");
			scanf("%s", nomeUtilizador);
			printf("Password: ");
			scanf("%s", palavraPasse);
			nif = loginCliente(inicio, nomeUtilizador, palavraPasse);
			if (nif != NULL)
			{
				printf("Login efetuado com sucesso!\n");
				system("pause");
				system("cls");
				menuCliente(inicio, nif);
			}
			else
			{
				printf("Dados incorretos!\n");
				printf("Pressione 1 para tentar novamente ou 2 para sair.\n");
				scanf("%d", &opcao);
				if (opcao == 2)
				{
					system("cls");
					break; // Exit the loop if the client chooses to exit
				}
				system("cls");
			}
		}
		break;
	case 2:

	default:
		break;
	}
}

void menuCliente(Cliente* inicio, char* nif)
{
	printf("Menu Cliente\n");
	//printf("%s\n", nif);
	int op;
	do
	{
		printf("1 - Consultar Saldo\n");
		printf("2 - Carregar Saldo\n");
		printf("3 - Alugar Meio\n");
		printf("4 - Listar por Percentagem Autonomia\n");
		printf("5 - Listar por Geocodigo\n");
		printf("0 - Logout\n");
		printf("Opcao:");
		scanf("%d", &op);
		system("cls");
		switch (op)
		{
		case 1:
		{
			printf("========== Consultar Saldo ==========\n");
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
			system("cls");
			break;
		}
		case 2:
		{
			printf("========== Carregar Saldo ==========\n");
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
			system("cls");
			break;
		}
		case 3:
		{
			printf("========== Alugar Meio ==========\n");
			char idMeioEletrico[50];
			int reserva;

			// Read the contents of the file and create the linked list
			MeioEletrico* inicio = lerMeioEletrico();
			if (inicio == NULL) {
				printf("Nao foi possivel ler os meios eletricos!\n");
				system("pause");
				system("cls");
				break;
			}

			printf("Insira o ID do meio eletrico: ");
			scanf("%s", idMeioEletrico);

			if (existeMeioEletrico(inicio, idMeioEletrico) == 1)
			{
				printf("Meio eletrico encontrado!\n");
				printf("Deseja reservar este meio eletrico? (1-Sim / 0-Nao): ");
				scanf("%d", &reserva);
				alterarEstadoMeio(inicio, idMeioEletrico, reserva);
			}
			else
			{
				printf("Meio eletrico nao encontrado!\n");
			}
			system("pause");
			system("cls");
			break;
		}

		case 4:
		{
			printf("========== Listar por Percentagem Autonomia ==========\n");
			MeioEletrico* inicio = lerMeioEletrico();
			listarMeiosPorCargaBateria(inicio);
			system("pause");
			system("cls");
			break;
		}
		case 5:
		{
			printf("========== Listar por Geocodigo ==========\n");
			MeioEletrico* inicio = lerMeioEletrico();
			char geocodigo[50];
			printf("Insira o geocodigo a pesquisar: ");
			scanf("%s", geocodigo);
			listarMeiosPorGeocodigo(inicio, geocodigo);
			system("pause");
			system("cls");
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