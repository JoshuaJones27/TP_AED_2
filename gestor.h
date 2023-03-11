#pragma once
#include <stdio.h>

typedef struct gestor {
	int id;
	char nome[100];
	char email[100];
	char password[30];
	struct gestor* prox;
} Gestor;

Gestor* inserirGestor(Gestor* inicio, int id, char nom[], char emai[], char pass[]);
void listarGestor(Gestor* inicio);
int existeGestor(Gestor* inicio, int* id);
Gestor* removerGestor(Gestor* inicio, int* i);
int guardarGestores(Gestor* inicio);
Gestor* lerGestor();