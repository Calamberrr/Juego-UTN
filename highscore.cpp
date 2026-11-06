#include <iostream>
#include "visual.h"
#include <cstdlib>
#include <windows.h>
#include "rlutil.h"
#include "juego.h"
#include "highscore.h"
using namespace std;

const int MAX_SCORES = 5;
static string nombres[MAX_SCORES] = {"---", "---", "---", "---", "---"};
static int dias[MAX_SCORES] = {0, 0, 0, 0, 0};
static int puntajes[MAX_SCORES] = {0, 0, 0, 0, 0};

void inicializarHighscore() {
    for (int i = 0; i < MAX_SCORES; i++) {
        nombres[i] = "VACIO";
        dias[i] = 0;
        puntajes[i] = 0;
    }
}

void registrarPuntaje(string nombreJugador, int diasSobrevividos, int puntajeTotal) {
    // Buscamos si entra en el ranking (orden descendente por puntaje)
    for (int i = 0; i < MAX_SCORES; i++) {
        if (puntajeTotal > puntajes[i]) {
            // Desplazamos los demas hacia abajo
            for (int j = MAX_SCORES - 1; j > i; j--) {
                puntajes[j] = puntajes[j - 1];
                dias[j] = dias[j - 1];
                nombres[j] = nombres[j - 1];
            }
            // Insertamos el nuevo
            puntajes[i] = puntajeTotal;
            dias[i] = diasSobrevividos;
            nombres[i] = nombreJugador;
            break;
        }
    }
}

void highscore() {
    rlutil::cls();
    int ancho = rlutil::tcols();

    rlutil::setColor(rlutil::LIGHTMAGENTA);
    imprimirCentrado("==================================================", 4);
    imprimirCentrado("       H I G H S C O R E   -   A R C A D E        ", 5);
    imprimirCentrado("==================================================", 6);

    rlutil::setColor(rlutil::YELLOW);
    rlutil::locate(ancho / 2 - 22, 9);
    cout << "PUESTO\tJUGADOR\t\tDIAS\tPTOS";

    rlutil::setColor(rlutil::DARKGREY);
    rlutil::locate(ancho / 2 - 22, 10);
    cout << "--------------------------------------------";

    rlutil::setColor(rlutil::WHITE);
    for (int i = 0; i < MAX_SCORES; i++) {
        rlutil::locate(ancho / 2 - 22, 12 + i);
        cout << "  #" << (i + 1) << "\t" << nombres[i] << "\t\t" << dias[i] << "\t" << puntajes[i];
    }

    rlutil::setColor(rlutil::YELLOW);
    imprimirCentrado("Presione una tecla para volver al menu...", 20);
    rlutil::anykey();
}
