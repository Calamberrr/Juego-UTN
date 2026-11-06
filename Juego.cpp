#include <iostream>
#include "visual.h"
#include <cstdlib>
#include <windows.h>
#include "rlutil.h"
#include "juego.h"
#include "highscore.h"
#include "eventos.h"
#include "logros.h"
using namespace std;

int ancho = rlutil::tcols();


void mostrarstats(int diasSobrevividos, int comida, int agua, int supervivientes) {
    rlutil::cls();

    rlutil::setColor(rlutil::CYAN);
    imprimirCentrado("==================================================", 4);
    imprimirCentrado("       ESTADISTICAS ACTUALES DEL REFUGIO          ", 5);
    imprimirCentrado("==================================================", 6);

    rlutil::setColor(rlutil::WHITE);
    imprimirCentrado("Dias sobrevividos en el paramo: " + to_string(diasSobrevividos), 9);
    imprimirCentrado("Supervivientes activos en el grupo: " + to_string(supervivientes), 11);
    imprimirCentrado("Reservas de comida disponibles: " + to_string(comida) + " kg", 13);
    imprimirCentrado("Reservas de agua disponibles: " + to_string(agua) + " litros", 15);

    rlutil::setColor(rlutil::YELLOW);
    imprimirCentrado("Presione una tecla para volver al refugio...", 19);
    rlutil::anykey();
}

bool gestionarRefugio(int &comida, int &agua, int &supervivientes,
                      int &defensas, bool logros[], int diasSobrevividos) {

    bool jugandoRefugio = true;

    string opcionesRefugio[4] = {
        "Explorar zona en busca de provisiones",
        "Fortalecer defensas y descansar",
        "Ver estadisticas actuales del refugio",
        "Abandonar refugio y registrar en Highscore"
    };

    int opcion;

    do {
        rlutil::cls();
        rlutil::setColor(rlutil::CYAN);
        imprimirCentrado("=== OPCIONES DEL REFUGIO ===", 8);

        if (supervivientes == 1) {
            opcionesRefugio[0] = "Exploracion desesperada en solitario (Mas riesgo, x2 recursos)";
            opcionesRefugio[1] = "Fortalecer barricadas a solas (+4 Defensas)";
        } else {
            opcionesRefugio[0] = "Explorar zona en busca de provisiones";
            opcionesRefugio[1] = "Fortalecer defensas y descansar";
        }

        opcion = menuFlechas(opcionesRefugio, 4, 10, 2);

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

                imprimirCentrado("¡Exploracion exitosa!", 8);
                imprimirCentrado("Conseguiste +" + to_string(comidaEncontrada) +
                                 " comida y +" + to_string(aguaEncontrada) + "L de agua.", 10);

                rlutil::anykey();

                // La exploración termina el día.
                jugandoRefugio = false;
                break;
            }

            case 1: {
                int puntosDefensa = (supervivientes == 1) ? 4 : 2;
                defensas += puntosDefensa;

                rlutil::cls();
                rlutil::setColor(rlutil::LIGHTBLUE);

                imprimirCentrado("Reforzaste los accesos del refugio.", 10);
                imprimirCentrado("Nivel actual de defensas: +" + to_string(defensas), 12);

                rlutil::anykey();

                // Fortalecer defensas también termina el día.
                jugandoRefugio = false;
                break;
            }

            case 2: {
                mostrarstats(diasSobrevividos, comida, agua, supervivientes);
                break;
            }

            case 3: {
                jugandoRefugio = false;
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

        // Evento diario
        int probabilidad = (rand() % 100) + 1;

int limiteEvento = (supervivientes == 1) ? 65 : 30;

if (probabilidad <= limiteEvento) {

    ejecutarEventos(comida, agua, supervivientes, defensas);

}
else {

    rlutil::setColor(rlutil::DARKGREY);

    imprimirCentrado("El perimetro se mantiene relativamente tranquilo hoy...", 7);

    rlutil::msleep(500);
}
        // Menu del refugio
        bool seguirJugando = gestionarRefugio(
            comida, agua, supervivientes, defensas, logros, diasSobrevividos
        );

        if (!seguirJugando) {
            jugando = false;
            break;
        }

        // Consumo diario de recursos
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
if (agua < 0) agua = 0;;

        // Crisis de suministros
        if (comida == 0 || agua == 0) {

            int huyen = 1;

            if (supervivientes > 1) {
                huyen = (rand() % (supervivientes - 1)) + 1;
            }

            supervivientes -= huyen;

            rlutil::cls();
            rlutil::setColor(rlutil::LIGHTRED);

            imprimirCentrado("¡CRISIS DE SUMINISTROS!", 8);

            imprimirCentrado("La falta de agua o comida provoco que " +
                             to_string(huyen) +
                             " supervivientes huyan del refugio.", 10);

            rlutil::anykey();
        }

        // Game Over
        if (supervivientes <= 0) {

            jugando = false;

            rlutil::cls();
            rlutil::setColor(rlutil::RED);

            imprimirCentrado("=== GAME OVER ===", 8);
            imprimirCentrado("El refugio se ha quedado sin supervivientes. Fin de la partida.", 10);

            rlutil::anykey();
        }
    }

    // Puntaje final
    int puntajeTotal = (diasSobrevividos * 100) +
                       (comida * 10) +
                       (agua * 10) +
                       (supervivientes * 500);

    registrarPuntaje(nombreJugador, diasSobrevividos, puntajeTotal);

    rlutil::cls();
    rlutil::setColor(rlutil::YELLOW);

    imprimirCentrado("=== RESUMEN DE LA PARTIDA ===", 6);
    imprimirCentrado("Superviviente: " + nombreJugador, 8);
    imprimirCentrado("Dias sobrevividos: " + to_string(diasSobrevividos), 10);
    imprimirCentrado("Puntaje Arcade Final: " + to_string(puntajeTotal), 12);

    imprimirCentrado("Presione una tecla para regresar al menu principal...", 16);

    rlutil::anykey();
}

