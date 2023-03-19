#pragma once
#include <stdio.h>

typedef struct gestor {
	char id[50];
	char nome[100];
	char email[100];
	char password[30];
	struct gestor* prox;
} Gestor;

Gestor* inserirGestor(Gestor* inicio, char id[], char nom[], char emai[], char pass[]);
void listarGestor(Gestor* inicio);
int existeGestor(Gestor* inicio, char* id);
Gestor* removerGestor(Gestor* inicio, char* i);
int guardarGestores(Gestor* inicio);
Gestor* lerGestor();
void editarGestor(Gestor* inicio, char* id);
char* loginGestor(Gestor* inicio, char email[], char palavraPasse[]);