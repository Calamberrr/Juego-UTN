#include <iostream>
#include "visual.h"
#include <cstdlib>
#include "rlutil.h"
#include "juego.h"
#include "highscore.h"
#include "eventos.h"
#include "logros.h"
using namespace std;

// Muestra una advertencia parpadeante al entrar en modo Nightmare.
void mostrarAlertaNightmare() {
    rlutil::hidecursor();

    for (int parpadeo = 0; parpadeo < 6; parpadeo++) {
        rlutil::cls();

        if (parpadeo % 2 == 0) {
            rlutil::setColor(rlutil::LIGHTRED);
        } else {
            rlutil::setColor(rlutil::YELLOW);
        }

        imprimirCentrado("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!", 7);
        imprimirCentrado("!!!       MODO NIGHTMARE ACTIVADO     !!!", 9);
        imprimirCentrado("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!", 11);

        rlutil::setColor(rlutil::WHITE);
        imprimirCentrado("QUEDA UN SOLO SUPERVIVIENTE.", 14);
        imprimirCentrado("La supervivencia sera mucho mas dificil.", 16);
        rlutil::msleep(300);
    }

    rlutil::cls();
    rlutil::setColor(rlutil::LIGHTRED);
    imprimirCentrado("============================================", 7);
    imprimirCentrado("          MODO NIGHTMARE ACTIVADO           ", 9);
    imprimirCentrado("============================================", 11);

    rlutil::setColor(rlutil::WHITE);
    imprimirCentrado("Quedaste completamente solo.", 14);
    imprimirCentrado("Los peligros seran mayores y los recursos escasos.", 16);

    rlutil::setColor(rlutil::YELLOW);
    imprimirCentrado("Presione una tecla para continuar...", 20);
    rlutil::anykey();
    rlutil::setColor(rlutil::WHITE);
}

// Detecta el ingreso al modo Nightmare sin repetir la alerta cada dia.
void actualizarEstadoNightmare(int supervivientes, bool &nightmareActivo) {
    if (supervivientes == 1 && !nightmareActivo) {
        mostrarAlertaNightmare();
        nightmareActivo = true;
    }
    else if (supervivientes != 1) {
        nightmareActivo = false;
    }
}

// Pantalla principal de gestion del refugio.
void mostrarPanelRefugio(int diasSobrevividos, int comida, int agua,
                         int supervivientes, int defensas) {
    rlutil::cls();
    rlutil::hidecursor();

    int ancho = rlutil::tcols();

    if (ancho < 75) {
        rlutil::setColor(rlutil::LIGHTRED);
        imprimirCentrado("AMPLIA LA VENTANA DE LA CONSOLA", 5);
        rlutil::setColor(rlutil::WHITE);
        imprimirCentrado("Se necesitan al menos 75 columnas para el refugio.", 7);
        rlutil::anykey();
        return;
    }

    rlutil::setColor(rlutil::DARKGREY);
    rlutil::locate(4, 2);
    cout << "SURVIVAL NETWORK // TERMINAL 07-B";
    rlutil::locate(ancho - 22, 2);
    cout << "DIA " << diasSobrevividos << " // EN LINEA";

    rlutil::setColor(rlutil::LIGHTRED);
    imprimirCentrado("==============================================================", 4);

    rlutil::setColor(rlutil::YELLOW);
    imprimirCentrado("CENTRO DE OPERACIONES // REFUGIO", 6);

    rlutil::setColor(rlutil::LIGHTGREEN);
    imprimirCentrado("SUPERVIVIENTES: " + to_string(supervivientes) +
                     "     DEFENSAS: " + to_string(defensas), 8);

    rlutil::setColor(rlutil::LIGHTCYAN);
    imprimirCentrado("COMIDA: " + to_string(comida) + " kg     AGUA: " +
                     to_string(agua) + " litros", 9);

    int nivelAmenaza = ((diasSobrevividos - 1) / 5) + 1;
    rlutil::setColor(rlutil::LIGHTRED);
    imprimirCentrado("NIVEL DE AMENAZA: " + to_string(nivelAmenaza), 10);

    rlutil::setColor(rlutil::LIGHTRED);
    imprimirCentrado("--------------------------------------------------------------", 11);

    rlutil::setColor(rlutil::WHITE);
    imprimirCentrado("SELECCIONA LA PROXIMA OPERACION", 12);

    rlutil::setColor(rlutil::DARKGREY);
    imprimirCentrado("CADA DECISION PUEDE CAMBIAR TU SUPERVIVENCIA.", 27);

    rlutil::setColor(rlutil::YELLOW);
    imprimirCentrado("FLECHAS: MOVER     ENTER: CONFIRMAR", 29);

    rlutil::setColor(rlutil::DARKGREY);
    imprimirCentrado("SURVIVAL NETWORK // NADIE SOBREVIVE SOLO", 31);
    rlutil::setColor(rlutil::WHITE);

}

// Devuelve true solamente cuando se realizo un intercambio.
bool intercambiarRecursos(int &comida, int &agua) {
    string opcionesComercio[3] = {
        "ENTREGAR 3 KG DE COMIDA / RECIBIR 2 L DE AGUA",
        "ENTREGAR 3 L DE AGUA / RECIBIR 2 KG DE COMIDA",
        "VOLVER AL REFUGIO"
    };

    rlutil::cls();
    rlutil::setColor(rlutil::CYAN);
    imprimirCentrado("COMERCIO ENTRE SUPERVIVIENTES", 5);
    rlutil::setColor(rlutil::WHITE);
    imprimirCentrado("Tus reservas actuales:", 8);
    imprimirCentrado("Comida: " + to_string(comida) + " kg | Agua: " +
                     to_string(agua) + " litros", 10);
    rlutil::setColor(rlutil::YELLOW);
    imprimirCentrado("Un intercambio exitoso consume el dia.", 18);

    int opcion = menuFlechas(opcionesComercio, 3, 12, 2);

    if (opcion == 2 || opcion < 0) {
        return false;
    }

    rlutil::cls();

    if (opcion == 0) {
        if (comida < 3) {
            rlutil::setColor(rlutil::LIGHTRED);
            imprimirCentrado("NO TENES COMIDA SUFICIENTE PARA INTERCAMBIAR.", 10);
            rlutil::setColor(rlutil::WHITE);
            imprimirCentrado("Necesitas 3 kg de comida.", 12);
            rlutil::anykey();
            return false;
        }

        comida -= 3;
        agua += 2;
        rlutil::setColor(rlutil::LIGHTGREEN);
        imprimirCentrado("INTERCAMBIO REALIZADO", 9);
        imprimirCentrado("Entregaste 3 kg de comida y recibiste 2 L de agua.", 11);
    }
    else {
        if (agua < 3) {
            rlutil::setColor(rlutil::LIGHTRED);
            imprimirCentrado("NO TENES AGUA SUFICIENTE PARA INTERCAMBIAR.", 10);
            rlutil::setColor(rlutil::WHITE);
            imprimirCentrado("Necesitas 3 litros de agua.", 12);
            rlutil::anykey();
            return false;
        }

        agua -= 3;
        comida += 2;
        rlutil::setColor(rlutil::LIGHTGREEN);
        imprimirCentrado("INTERCAMBIO REALIZADO", 9);
        imprimirCentrado("Entregaste 3 L de agua y recibiste 2 kg de comida.", 11);
    }

    rlutil::setColor(rlutil::YELLOW);
    imprimirCentrado("La operacion consume el dia. Presione una tecla...", 15);
    rlutil::anykey();
    return true;
}

bool gestionarRefugio(int &comida, int &agua, int &supervivientes,
                      int &defensas, bool logros[], int diasSobrevividos) {

    bool jugandoRefugio = true;

    string opcionesRefugio[4] = {
        "EXPLORAR EL EXTERIOR - Buscar provisiones",
        "FORTIFICAR EL REFUGIO - Mejorar defensas",
        "COMERCIAR - Intercambiar comida y agua",
        "ABANDONAR Y REGISTRAR PUNTAJE"
    };

    int opcion;

    do {
        if (supervivientes == 1) {
            opcionesRefugio[0] = "EXPLORAR EN SOLITARIO - MAYOR RIESGO, X2 RECURSOS";
            opcionesRefugio[1] = "REFORZAR BARRICADAS - BONIFICACION +4 DEFENSA";
        } else {
            opcionesRefugio[0] = "EXPLORAR EL EXTERIOR - Buscar provisiones";
            opcionesRefugio[1] = "FORTIFICAR EL REFUGIO - Mejorar defensas";
        }

        mostrarPanelRefugio(diasSobrevividos, comida, agua, supervivientes, defensas);
        opcion = menuFlechas(opcionesRefugio, 4, 14, 2);

        switch (opcion) {

            case 0: {
                int comidaEncontrada;
                int aguaEncontrada;

                if (supervivientes == 1) {
                    comidaEncontrada = (rand() % 4) + 1;
                    aguaEncontrada = (rand() % 3) + 1;
                } else {
                    comidaEncontrada = (rand() % 5) + 1;
                    aguaEncontrada = (rand() % 5) + 1;
                }

                comida += comidaEncontrada;
                agua += aguaEncontrada;

                rlutil::cls();
                rlutil::setColor(rlutil::LIGHTGREEN);
                imprimirCentrado("EXPLORACION EXITOSA", 8);
                imprimirCentrado("Conseguiste +" + to_string(comidaEncontrada) +
                                 " comida y +" + to_string(aguaEncontrada) + "L de agua.", 10);
                rlutil::anykey();
                jugandoRefugio = false;
                break;
            }

            case 1: {
                int puntosDefensa = (supervivientes == 1) ? 4 : 2;
                defensas += puntosDefensa;

                rlutil::cls();
                rlutil::setColor(rlutil::LIGHTBLUE);
                imprimirCentrado("REFUERZO COMPLETADO", 8);
                imprimirCentrado("Defensas mejoradas: +" + to_string(puntosDefensa), 10);
                imprimirCentrado("Defensas acumuladas: " + to_string(defensas), 12);
                rlutil::anykey();
                jugandoRefugio = false;
                break;
            }

            case 2: {
                bool intercambioRealizado = intercambiarRecursos(comida, agua);
                if (intercambioRealizado) {
                    jugandoRefugio = false;
                }
                break;
            }

            case 3: {
                return false;
            }
        }

        verificarLogros(logros, diasSobrevividos, defensas,
                        comida, agua, supervivientes);

    } while (jugandoRefugio);

    return true;
}

void iniciarPartida(bool logros[]) {

    int diasSobrevividos = 0;
    int comida = 15;
    int agua = 15;
    int supervivientes = 3;
    int defensas = 0;

    bool jugando = true;
    bool nightmareActivo = false;
    bool nightmareAlcanzado = false;

    string nombreJugador;
    rlutil::cls();
    imprimirCentrado("=== REGISTRO DE SUPERVIVIENTE ===", 5);
    rlutil::locate(rlutil::tcols() / 2 - 15, 8);
    cout << "Ingrese su Nombre: ";
    cin >> nombreJugador;

    while (jugando) {

        diasSobrevividos++;

            rlutil::cls();
            rlutil::setColor(rlutil::YELLOW);
            imprimirCentrado("=== DIA " + to_string(diasSobrevividos) + " EN EL REFUGIO ===", 3);
            rlutil::setColor(rlutil::WHITE);
            imprimirCentrado("Supervivientes: " + to_string(supervivientes) +
                             " | Comida: " + to_string(comida) +
                             " | Agua: " + to_string(agua) +
                             " | Defensas: " + to_string(defensas), 5);
            rlutil::msleep(800);

            int probabilidad = (rand() % 100) + 1;
            int nivelDificultad = (diasSobrevividos - 1) / 5;
            int limiteEvento;

            if (supervivientes == 1) {
                limiteEvento = 65 + (nivelDificultad * 3);
                if (limiteEvento > 85) limiteEvento = 85;
            }
            else {
                limiteEvento = 30 + (nivelDificultad * 4);
                if (limiteEvento > 60) limiteEvento = 60;
            }

            if (probabilidad <= limiteEvento) {
                ejecutarEventos(comida, agua, supervivientes, defensas, diasSobrevividos);
            }
            else {
                rlutil::setColor(rlutil::DARKGREY);
                imprimirCentrado("El perimetro se mantiene relativamente tranquilo hoy...", 7);
                rlutil::msleep(500);
            }

            actualizarEstadoNightmare(supervivientes, nightmareActivo);
            if (supervivientes == 1) nightmareAlcanzado = true;

            if (supervivientes <= 0) {
                jugando = false;
                rlutil::cls();
                rlutil::setColor(rlutil::RED);
                imprimirCentrado("=== GAME OVER ===", 8);
                imprimirCentrado("No quedan supervivientes para defender el refugio.", 10);
                rlutil::anykey();
                break;
            }

        bool seguirJugando = gestionarRefugio(
            comida, agua, supervivientes, defensas, logros, diasSobrevividos
        );

        if (!seguirJugando) {
            jugando = false;
            break;
        }

        // Consumo diario de recursos.
        int consumoComida;
        int consumoAgua;

        if (supervivientes == 1) {
            consumoComida = 2;
            consumoAgua = 2;
        }
        else {
            consumoComida = supervivientes;
            consumoAgua = supervivientes;
        }

        comida -= consumoComida;
        agua -= consumoAgua;
        if (comida < 0) comida = 0;
        if (agua < 0) agua = 0;

        // Crisis de suministros.
        if (comida == 0 || agua == 0) {
            int huyen = 1;
            if (supervivientes > 1) {
                huyen = (rand() % (supervivientes - 1)) + 1;
            }
            supervivientes -= huyen;

            rlutil::cls();
            rlutil::setColor(rlutil::LIGHTRED);
            imprimirCentrado("CRISIS DE SUMINISTROS", 8);
            imprimirCentrado("La falta de agua o comida provoco que " +
                             to_string(huyen) +
                             " supervivientes huyan del refugio.", 10);
            rlutil::anykey();
        }

        actualizarEstadoNightmare(supervivientes, nightmareActivo);
        if (supervivientes == 1) nightmareAlcanzado = true;

        if (supervivientes <= 0) {
            jugando = false;
            rlutil::cls();
            rlutil::setColor(rlutil::RED);
            imprimirCentrado("=== GAME OVER ===", 8);
            imprimirCentrado("El refugio se ha quedado sin supervivientes. Fin de la partida.", 10);
            rlutil::anykey();
        }
    }

    int puntajeTotal = (diasSobrevividos * 100) +
                       (comida * 10) +
                       (agua * 10) +
                       (supervivientes * 500);

    registrarPuntaje(nombreJugador, diasSobrevividos, puntajeTotal);

    int logrosDesbloqueados = 0;
    for (int i = 0; i < 8; i++) {
        if (logros[i]) logrosDesbloqueados++;
    }

    rlutil::cls();
    rlutil::setColor(rlutil::YELLOW);
    imprimirCentrado("=== INFORME FINAL DE SUPERVIVENCIA ===", 4);
    rlutil::setColor(rlutil::WHITE);
    imprimirCentrado("Superviviente: " + nombreJugador, 7);
    imprimirCentrado("Dias sobrevividos: " + to_string(diasSobrevividos), 9);
    imprimirCentrado("Grupo restante: " + to_string(supervivientes), 11);
    imprimirCentrado("Comida: " + to_string(comida) + " kg | Agua: " +
                     to_string(agua) + " litros", 13);
    imprimirCentrado("Defensas acumuladas: " + to_string(defensas), 15);
    imprimirCentrado(string("Modo Nightmare alcanzado: ") +
                     (nightmareAlcanzado ? "SI" : "NO"), 17);
    imprimirCentrado("Logros desbloqueados: " + to_string(logrosDesbloqueados) + "/8", 19);
    rlutil::setColor(rlutil::LIGHTGREEN);
    imprimirCentrado("PUNTAJE ARCADE FINAL: " + to_string(puntajeTotal), 22);
    rlutil::setColor(rlutil::YELLOW);
    imprimirCentrado("Presione una tecla para regresar al menu principal...", 26);
    rlutil::anykey();
}
