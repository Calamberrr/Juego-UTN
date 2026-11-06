#ifndef HIGHSCORE_H_INCLUDED
#define HIGHSCORE_H_INCLUDED

#include <string>

void inicializarHighscore();
void registrarPuntaje(std::string nombreJugador, int diasSobrevividos, int puntajeTotal);
void highscore();

#endif // HIGHSCORE_H_INCLUDED
