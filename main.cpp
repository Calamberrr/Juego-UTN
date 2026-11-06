#include <iostream>
#include "visual.h"
#include <cstdlib>
#include <windows.h>
#include "rlutil.h"
#include "juego.h"
#include "highscore.h"
#include "logros.h"
using namespace std;

void maximizarConsola() {
    keybd_event(VK_MENU, 0x38, 0, 0);                        // Alt abajo
    keybd_event(VK_RETURN, 0x1c, 0, 0);                      // Enter abajo
    keybd_event(VK_RETURN, 0x1c, KEYEVENTF_KEYUP, 0);        // Enter arriba
    keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0);          // Alt arriba
}


int main() {

    srand(time(NULL));

    maximizarConsola();
    rlutil::msleep(150);

    rlutil::hidecursor();
    animarInicioJuego();
    inicializarHighscore();
    bool logros[4];
    inicializarLogros(logros);
string opcionesMenu[5] = {"NUEVA PARTIDA", "HIGHSCORE", "AYUDA / GUIA","VER LOGROS", "SALIR"};
    int opcion;
    do {
        mostrarMenuPrincipalVisual();
        opcion = menuFlechas(opcionesMenu, 5,14,2,true);

        switch (opcion) {
            case 0: {
                animarConstruccionBase();
                iniciarPartida(logros);
                break;
            }
            case 1:
                rlutil::cls();
                highscore();
                rlutil::anykey();
                break;

            case 2:
                rlutil::cls();
                mostrarManualAyuda();
                break;
            case 3:
                rlutil::cls();
                mostrarLogros(logros);
                break;
            case 4:
                rlutil::setColor(rlutil::LIGHTGREEN);
                cout << "\nSaliendo del refugio... ¡Hasta pronto!" << endl;
                rlutil::msleep(500);
                break;
            default:
                rlutil::setColor(rlutil::LIGHTRED);
                cout << "\nOpcion incorrecta." << endl;
                rlutil::msleep(500);
                break;
        }

    } while (opcion != 4);

    rlutil::showcursor();
    return 0;
}
