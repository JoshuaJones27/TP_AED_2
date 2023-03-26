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
	//Insere os dados dos ficheiros txt dentro das structs
	Cliente* inicio = NULL;
	inicio = lerCliente();
	Gestor* inicioGestor = NULL;
	inicioGestor = lerGestor();
	MeioEletrico* inicioMeioEletrico = NULL;
	inicioMeioEletrico = lerMeioEletrico();
	int opcao;
	char nomeUtilizador[100], palavraPasse[30], email[100];
	char* nif = NULL; // Initialize the nif variable to NULL
	char* id = NULL;
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
		while (id == NULL) // Add a loop to continue until the client successfully logs in or chooses to exit
		{
			printf("Insira os seus dados:\n");
			printf("Email Gestor: ");
			scanf("%s", email);
			printf("Password: ");
			scanf("%s", palavraPasse);
			id = loginGestor(inicioGestor, email, palavraPasse);
			if (id != NULL)
			{
				printf("Login efetuado com sucesso!\n");
				system("pause");
				system("cls");
				menuGestor(inicioGestor, id);
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

int menuGestor(Gestor* inicioGestor, char* id)
{
	printf("Menu Gestor\n");

	int op;
	do
	{
		printf("1 - Criar Cliente\n");
		printf("2 - Criar Meio Eletrico\n");
		printf("3 - Editar Cliente (NAO FUNCIONA DIREITO)\n");
		printf("4 - Editar Meio Eletrico (NAO FUNCIONA DIREITO)\n");
		printf("5 - Eliminar Cliente\n");
		printf("6 - Eliminar Meio Eletrico(NAO FUNCIONA DIREITO)\n");
		printf("7 - Listar Clientes\n");
		printf("8 - Listar Meios Eletricos\n");
		printf("0 - Logout\n");
		printf("Opcao:");
		scanf("%d", &op);
		system("cls");

		switch (op)
		{
		case 1:
		{
			printf("========== Criar Cliente ==========\n");
			Cliente* inicio = NULL;
			char nif[20], nome[100], username[100], password[30], morada[200];
			float saldo;

			printf("NIF: ");
			scanf("%s", nif);
			printf("Nome: ");
			scanf("%s", nome);
			printf("Nome de utilizador: ");
			scanf("%s", username);
			printf("Senha: ");
			scanf("%s", password);
			printf("Morada: ");
			scanf("%s", morada);
			printf("Saldo: ");
			scanf("%f", &saldo);

			inicio = inserirCliente(inicio, nif, nome, username, password, morada, saldo);

			if (guardarClientesGestor(inicio))
			{
				printf("Cliente guardado com sucesso.\n");
				system("pause");
				system("cls");
			}
			else
			{
				printf("Erro ao criar o cliente.\n");
				system("pause");
				system("cls");
			}
			break;
		}
		case 2:
		{
			printf("========== Criar Meio Eletrico ==========\n");

			MeioEletrico* inicio = NULL;
			char tipo[50];
			float carga_bateria = 100;
			float custo_hora;
			char geocodigo[50];
			int reservado = 0;

			printf("Tipo: ");
			scanf("%s", tipo);

			printf("Custo por Hora: ");
			scanf("%f", &custo_hora);

			printf("Geocódigo: ");
			scanf("%s", geocodigo);

			inicio = criarMeioEletrico(inicio, tipo, carga_bateria, custo_hora, geocodigo, reservado);

			if (guardarMeiosEletricosGestor(inicio)) {
				printf("Meio eletrico criado e guardado com sucesso.\n");
				system("pause");
				system("cls");
			}
			else {
				printf("Erro ao guardar meio eletrico.\n");
				system("pause");
				system("cls");
			}
			break;
		}
		case 3:
		{
			printf("========== Editar Cliente ==========\n");

			char nifCliente[20];

			Cliente* inicio = lerCliente();

			printf("Insira o NIF do cliente a editar: ");

			scanf("%s", nifCliente);

			if (existeCliente(inicio, nifCliente) == 1)
			{
				printf("Cliente encontrado!\n");
				editarCliente(inicio, nifCliente);
				system("pause");
				system("cls");
			}
			else
			{
				printf("Cliente nao encontrado!\n");
				system("pause");
				system("cls");
			}
			break;
		}
		case 4:
		{
			printf("========== Editar Meio Eletrico ==========\n");
		}

		case 5:
		{
			printf("========== Remover Cliente ==========\n");

			char nifCliente[20];

			Cliente* inicio = lerCliente();

			printf("Insira o NIF do cliente a remover: ");

			scanf("%s", nifCliente);

			Cliente* novoInicio = removerCliente(inicio, nifCliente);

			if (novoInicio != NULL) // Se houve mudança na lista
			{
				printf("Cliente encontrado!\n");
				guardarClientesAoEliminar(novoInicio);
				printf("Cliente removido com sucesso.\n");
				system("pause");
				system("cls");
			}
			else
			{
				printf("Cliente nao encontrado!\n");
				system("pause");
				system("cls");
			}

			break;
		}

		case 6:
		{
			printf("========== Remover Meio Eletrico ==========\n");

			char idMeioEletrico[50];

			MeioEletrico* inicio = lerMeioEletrico();

			printf("Insira o ID do meio eletrico a remover: ");

			scanf("%s", idMeioEletrico);

			MeioEletrico* novoInicio = removerMeioEletrico(inicio, idMeioEletrico);

			if (novoInicio != NULL) // Se houve mudança na lista
			{
				printf("Meio eletrico encontrado!\n");
				guardarMeiosEletricos(novoInicio);
				printf("Meio eletrico removido com sucesso.\n");
				system("pause");
				system("cls");
			}
			else
			{
				printf("Meio eletrico nao encontrado!\n");
				system("pause");
				system("cls");
			}

			break;
		}

		case 7:
		{
			printf("========== Listar Clientes ==========\n");
			Cliente* inicio = lerCliente();
			listarCliente(inicio);
			system("pause");
			system("cls");
			break;
		}
		case 8:
		{
			printf("========== Listar Meio Eletrico ==========\n");
			MeioEletrico* inicio = lerMeioEletrico();
			listarMeioEletrico(inicio);
			system("pause");
			system("cls");
			break;
		}
		default:
			break;
		}
	} while (op != 0);
}

int main()
{
	menuLogin();
	return(0);
}