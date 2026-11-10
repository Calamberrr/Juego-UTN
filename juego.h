#ifndef JUEGO_H_INCLUDED
#define JUEGO_H_INCLUDED

void iniciarPartida(bool logros[]);
bool gestionarRefugio(int &comida, int &agua, int &supervivientes,
                      int &defensas, bool logros[], int diasSobrevividos);

#endif // JUEGO_H_INCLUDED
