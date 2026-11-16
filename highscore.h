#ifndef HIGHSCORE_H_INCLUDED
#define HIGHSCORE_H_INCLUDED

#include <string>
using namespace std;

void inicializarHighscore(string nombres[], int dias[], int puntajes[], int tam);
void registrarPuntaje(string nombres[], int dias[], int puntajes[], int tam, string nombreJugador, int diasSobrevividos, int puntajeTotal);
void mostrarHighscore(string nombres[], int dias[], int puntajes[], int tam);

#endif // HIGHSCORE_H_INCLUDED
