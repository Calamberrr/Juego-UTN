#include <iostream>
#include <string>
#include "rlutil.h"
#include "visual.h"
using namespace std;

// Dibuja una horda estática de zombis en una posición (x, y)
void dibujarSiluetaHorda(int x, int y) {
    rlutil::setColor(rlutil::DARKGREY);
    rlutil::locate(x, y);
    cout << "  Z   Z   Z   Z   Z  ";
    rlutil::locate(x, y + 1);
    rlutil::setColor(rlutil::RED);
    cout << " \\(o_o)/ \\(o_o)/ \\(o_o)/ ";
}

// Dibuja siluetas de supervivientes encontrados
void dibujarSiluetaSupervivientes(int x, int y) {
    rlutil::setColor(rlutil::LIGHTGREEN);
    rlutil::locate(x, y);
    cout << "   o/     o\\     o   ";
    rlutil::locate(x, y + 1);
    cout << "  /|\\    /|\\    /|\\  ";
}

// Dibuja un icono de peligro / refugio dañado
void dibujarSiluetaRefugioDanado(int x, int y) {
    rlutil::setColor(rlutil::LIGHTRED);
    rlutil::locate(x, y);
    cout << "      /-----\\      ";
    rlutil::locate(x, y + 1);
    cout << "     | [X]! |     ";
    rlutil::locate(x, y + 2);
    cout << "     +------+.     ";
}

void imprimirCentrado(string texto, int y) {
    int ancho = rlutil::tcols();
    int x = (ancho - (int)texto.length()) / 2;
    if (x < 1) x = 1;
    rlutil::locate(x, y);
    cout << texto;
}

void dibujarCiudadApocaliptica() {

    int ancho = rlutil::tcols();
    int centro = ancho / 2;

    // Edificios del lado izquierdo
    string edificioIzq[] = {
        "       .-------.",
        "       | [] [] |",
        "   .---|       |",
        "   | []|  []   |",
        "   |   |       |",
        "   | []| []  []|",
        "   |   |       |",
        " __|___|_______|__"
    };

    // Edificios del lado derecho
    string edificioDer[] = {
        " .-----------.",
        " | []    []  |",
        " |     .-----|",
        " | []  |     |",
        " |     | []  |",
        " | []  |     |",
        " |     | []  |",
        "_|_____|_____|__"
    };

    // Humo y siluetas
    string humo[] = {
        "       ~  ~",
        "    ~       ~",
        " ~       ~"
    };

    int xIzq = 4;
    int xDer = ancho - 24;

    // Dibujar humo izquierdo
    rlutil::setColor(rlutil::DARKGREY);

    for (int i = 0; i < 3; i++) {
        rlutil::locate(xIzq + 5, 16 + i);
        cout << humo[i];
    }

    // Dibujar edificio izquierdo
    rlutil::setColor(rlutil::DARKGREY);

    for (int i = 0; i < 8; i++) {
        rlutil::locate(xIzq, 19 + i);
        cout << edificioIzq[i];
    }

    // Dibujar humo derecho
    for (int i = 0; i < 3; i++) {
        rlutil::locate(xDer, 16 + i);
        cout << humo[i];
    }

    // Dibujar edificio derecho
    rlutil::setColor(rlutil::DARKGREY);

    for (int i = 0; i < 8; i++) {
        rlutil::locate(xDer, 19 + i);
        cout << edificioDer[i];
    }

    // Ventanas con luz de emergencia
    rlutil::setColor(rlutil::LIGHTRED);

    rlutil::locate(xIzq + 9, 22);
    cout << "!!";

    rlutil::locate(xDer + 4, 23);
    cout << "!!";

    // Restaurar color
    rlutil::setColor(rlutil::WHITE);
}



