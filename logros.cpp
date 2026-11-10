#include <iostream>
#include "rlutil.h"
#include "visual.h"
#include "logros.h"

using namespace std;

void inicializarLogros(bool logros[]) {
    for (int i = 0; i < 8; i++) {
        logros[i] = false;
    }
}

void verificarLogros(bool logros[], int dias, int defensas,
                     int comida, int agua, int supervivientes) {
    string nombresLogros[8] = {
        "Superviviente Nato: resisti 5 dias",
        "Fortaleza Inexpugnable: alcanza 10 defensas",
        "Aprovisionado: acumula 30 de comida o agua",
        "Comunidad: reuni 4 supervivientes",
        "Veterano del Paramo: resisti 10 dias",
        "Leyenda del Paramo: resisti 20 dias",
        "Bastion: alcanza 25 puntos de defensa",
        "Reserva de Emergencia: acumula 50 de comida o agua"
    };

    bool nuevos[8] = {false, false, false, false, false, false, false, false};
    int cantidadNuevos = 0;

    if (!logros[0] && dias >= 5) nuevos[0] = true;
    if (!logros[1] && defensas >= 10) nuevos[1] = true;
    if (!logros[2] && (comida >= 30 || agua >= 30)) nuevos[2] = true;
    if (!logros[3] && supervivientes >= 4) nuevos[3] = true;
    if (!logros[4] && dias >= 10) nuevos[4] = true;
    if (!logros[5] && dias >= 20) nuevos[5] = true;
    if (!logros[6] && defensas >= 25) nuevos[6] = true;
    if (!logros[7] && (comida >= 50 || agua >= 50)) nuevos[7] = true;

    for (int i = 0; i < 8; i++) {
        if (nuevos[i]) {
            logros[i] = true;
            cantidadNuevos++;
        }
    }

    if (cantidadNuevos > 0) {
        rlutil::cls();
        rlutil::setColor(rlutil::LIGHTGREEN);
        imprimirCentrado("!!! LOGRO(S) DESBLOQUEADO(S) !!!", 5);
        rlutil::setColor(rlutil::WHITE);

        int y = 8;
        for (int i = 0; i < 8; i++) {
            if (nuevos[i]) {
                imprimirCentrado("[OK] " + nombresLogros[i], y);
                y += 2;
            }
        }

        rlutil::setColor(rlutil::YELLOW);
        imprimirCentrado("Presione una tecla para continuar...", y + 2);
        rlutil::anykey();
    }
}

void mostrarLogros(bool logros[]) {
    string nombresLogros[8] = {
        "1. Superviviente Nato (5 dias)",
        "2. Fortaleza Inexpugnable (10 defensas)",
        "3. Aprovisionado (30 de comida/agua)",
        "4. Comunidad (4 supervivientes)",
        "5. Veterano del Paramo (10 dias)",
        "6. Leyenda del Paramo (20 dias)",
        "7. Bastion (25 defensas)",
        "8. Reserva de Emergencia (50 de comida/agua)"
    };

    rlutil::cls();
    int ancho = rlutil::tcols();

    rlutil::setColor(rlutil::CYAN);
    imprimirCentrado("==================================================", 3);
    imprimirCentrado("              REGISTRO DE LOGROS                  ", 4);
    imprimirCentrado("==================================================", 5);

    for (int i = 0; i < 8; i++) {
        rlutil::locate((ancho - 55) / 2, 8 + i * 2);
        if (logros[i]) {
            rlutil::setColor(rlutil::LIGHTGREEN);
            cout << "[COMPLETADO] " << nombresLogros[i];
        } else {
            rlutil::setColor(rlutil::DARKGREY);
            cout << "[BLOQUEADO]  " << nombresLogros[i];
        }
    }

    rlutil::setColor(rlutil::YELLOW);
    imprimirCentrado("Presione una tecla para volver...", 26);
    rlutil::anykey();
}
