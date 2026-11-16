#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include "visual.h"
#include "rlutil.h"
#include "juego.h"
#include "highscore.h"
#include "logros.h"

using namespace std;

void maximizarConsola() {
    keybd_event(VK_MENU, 0x38, 0, 0);
    keybd_event(VK_RETURN, 0x1c, 0, 0);
    keybd_event(VK_RETURN, 0x1c, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0);
}

const int MAX_SCORES = 5;

int main() {
    srand((unsigned int)time(NULL));

    maximizarConsola();
    rlutil::msleep(150);
    rlutil::hidecursor();
    animarInicioJuego();

    string nombres[MAX_SCORES];
    int dias[MAX_SCORES];
    int puntajes[MAX_SCORES];
    inicializarHighscore(nombres, dias, puntajes, MAX_SCORES);

    bool logros[8];
    inicializarLogros(logros);

    bool salir = false;
    while (!salir) {
        mostrarMenuPrincipalVisual();

        string opcionesMenu[5] = {
            "NUEVA PARTIDA",
            "HIGHSCORE",
            "AYUDA / GUIA",
            "VER LOGROS",
            "SALIR"
        };

        int opcion = menuFlechas(opcionesMenu, 5, 18, 2, true);
        switch (opcion) {
            case 0:
                iniciarPartida(logros, nombres, dias, puntajes, MAX_SCORES);
                break;
            case 1:
                mostrarHighscore(nombres, dias, puntajes, MAX_SCORES);
                break;
            case 2:
                mostrarManualAyuda();
                break;
            case 3:
                mostrarLogros(logros);
                break;
            case 4:
                salir = true;
                break;
        }
    }

    rlutil::setColor(rlutil::LIGHTGREEN);
    cout << "\nSaliendo del refugio... Hasta pronto!" << endl;
    rlutil::msleep(500);
    rlutil::showcursor();
    return 0;
}
