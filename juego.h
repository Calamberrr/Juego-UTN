#ifndef JUEGO_H_INCLUDED
#define JUEGO_H_INCLUDED
#include <string>
using namespace std;
void iniciarPartida(bool* juegoActivo, string nombres[], int dias[], int puntajes[], int tam);
bool gestionarRefugio(int &comida, int &agua, int &supervivientes,
                      int &defensas, bool logros[], int diasSobrevividos);

#endif // JUEGO_H_INCLUDED
