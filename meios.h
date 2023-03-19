#pragma once
#include <stdio.h>

typedef struct meio_eletrico {
	char tipo[50];
	int id[50];
	float carga_bateria;
	float custo_hora;
	char geocodigo[50];
	int reservado;
	struct meio_eletrico* prox;
} MeioEletrico;

MeioEletrico* inserirMeioEletrico(MeioEletrico* inicio, char tip[], int i[], float carga_bateri, float custo_hor, char geocodig[], int reservado);
void listarMeioEletrico(MeioEletrico* inicio);
int existeMeioEletrico(MeioEletrico* inicio, char* tipo);
MeioEletrico* removerMeioEletrico(MeioEletrico* inicio, char idMeioEletrico);
int guardarMeiosEletricos(MeioEletrico* inicio);
MeioEletrico* lerMeioEletrico();
void editarMeioEletrico(MeioEletrico* inicio, char* id);
void alterarEstadoMeio(MeioEletrico* inicio, char* idMeioEletrico, int reserva);
void listarMeiosPorCargaBateria(MeioEletrico* inicio);
void listarMeiosPorGeocodigo(MeioEletrico* inicio, char* geocodigo);
MeioEletrico* criarMeioEletrico(MeioEletrico* inicio, char* tipo, float carga_bateria, float custo_hora, char* geocodigo, int reservado);
