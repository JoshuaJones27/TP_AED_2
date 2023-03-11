#include <stdio.h>

typedef struct meio_eletrico {
	char tipo[50];
	char id[50];
	float carga_bateria;
	float custo_hora;
	char geocodigo[50];
	struct meio_eletrico* prox;
} MeioEletrico;

MeioEletrico* inserirMeioEletrico(MeioEletrico* inicio, char tip[], char i[], float carga_bateri, float custo_hor, char geocodig[]);
void listarMeioEletrico(MeioEletrico* inicio);
int existeMeioEletrico(MeioEletrico* inicio, char* tipo);
MeioEletrico* removerMeioEletrico(MeioEletrico* inicio, char* i);
int guardarMeiosEletricos(MeioEletrico* inicio);
MeioEletrico* lerMeioEletrico();
void editarMeioEletrico(MeioEletrico* inicio, char* id);
