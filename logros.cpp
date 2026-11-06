#include<iostream>
#include "rlutil.h"
#include "visual.h"
#include "logros.h"
using namespace std;

void inicializarLogros(bool logros[]) {
    for (int i = 0; i < 4; i++) {
        logros[i] = false;
    }
}

void verificarLogros(bool logros[], int dias, int defensas, int comida, int agua, int supervivientes) {
    int ancho = rlutil::tcols();

    // Logro 0: Superviviente Nato (Sobrevivir 5 días)
    if (!logros[0] && dias >= 5) {
        logros[0] = true;
        rlutil::cls();
        rlutil::setColor(rlutil::LIGHTGREEN);
        imprimirCentrado("¡LOGRO DESBLOQUEADO!", 6);
        imprimirCentrado("🏆 Superviviente Nato: Resiste 5 dias en el refugio.", 8);
        rlutil::anykey();
    }

    // Logro 1: Maestro Constructor (Alcanzar 10 o más puntos de defensa)
    if (!logros[1] && defensas >= 10) {
        logros[1] = true;
        rlutil::cls();
        rlutil::setColor(rlutil::LIGHTGREEN);
        imprimirCentrado("¡LOGRO DESBLOQUEADO!", 6);
        imprimirCentrado("🏆 Fortaleza Inexpugnable: Acumula 10 puntos de defensa.", 8);
        rlutil::anykey();
    }

    // Logro 2: Despensa Llena (Tener más de 30 de comida o agua)
    if (!logros[2] && (comida >= 30 || agua >= 30)) {
        logros[2] = true;
        rlutil::cls();
        rlutil::setColor(rlutil::LIGHTGREEN);
        imprimirCentrado("¡LOGRO DESBLOQUEADO!", 6);
        imprimirCentrado("🏆 Aprovisionado: Consigue mas de 30 unidades de un recurso.", 8);
        rlutil::anykey();
    }

    // Logro 3: Manada Fuerte (Mantener 4 o más supervivientes)
    if (!logros[3] && supervivientes >= 4) {
        logros[3] = true;
        rlutil::cls();
        rlutil::setColor(rlutil::LIGHTGREEN);
        imprimirCentrado("¡LOGRO DESBLOQUEADO!", 6);
        imprimirCentrado("🏆 Comunidad: Logra reunir 4 o mas supervivientes.", 8);
        rlutil::anykey();
    }
}

void mostrarLogros(bool logros[]) {
    rlutil::cls();
    int ancho = rlutil::tcols();

    rlutil::setColor(rlutil::CYAN);
    imprimirCentrado("==================================================", 3);
    imprimirCentrado("              REGISTRO DE LOGROS                  ", 4);
    imprimirCentrado("==================================================", 5);

    string nombresLogros[4] = {
        "1. Superviviente Nato (Resistir 5 dias)",
        "2. Fortaleza Inexpugnable (10 pts de defensa)",
        "3. Aprovisionado (Mas de 30 de comida/agua)",
        "4. Comunidad (Reunir 4 o mas supervivientes)"
    };

    int y = 8;
    for (int i = 0; i < 4; i++) {
        rlutil::locate((ancho - 45) / 2, y);
        if (logros[i]) {
            rlutil::setColor(rlutil::LIGHTGREEN);
            cout << "[COMPLETADO] " << nombresLogros[i];
        } else {
            rlutil::setColor(rlutil::DARKGREY);
            cout << "[BLOQUEADO]  " << nombresLogros[i];
        }
        y += 2;
    }

    rlutil::setColor(rlutil::YELLOW);
    imprimirCentrado("Presione una tecla para volver...", 18);
    rlutil::anykey();
}
