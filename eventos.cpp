#include <iostream>
#include "visual.h"
#include <cstdlib>
#include <windows.h>
#include "rlutil.h"
#include "juego.h"
#include "highscore.h"
#include "eventos.h"

using namespace std;


void ejecutarEventos(int &comida, int &agua, int &supervivientes, int defensas) {

    int ancho = rlutil::tcols();

    // Nightmare se activa automaticamente cuando queda uno.
    bool nightmare = (supervivientes == 1);

    // Grupo normal: 3 eventos.
    // Solitario: 7 eventos, incluyendo 4 eventos exclusivos.
    int tipo_evento = nightmare ? rand() % 7 : rand() % 3;

    // =====================================================
    // EVENTO 0: SUPERVIVIENTES ENCUENTRAN EL REFUGIO
    // =====================================================

    if (tipo_evento == 0) {

        int nuevos_supervivientes = rand() % 4;
        int extra_comida = rand() % 16;
        int extra_agua = rand() % 16;

        supervivientes += nuevos_supervivientes;
        comida += extra_comida;
        agua += extra_agua;

        rlutil::cls();
        rlutil::setColor(rlutil::YELLOW);

        imprimirCentrado("=== ALERTA EN EL PERIMETRO ===", 5);
        imprimirCentrado("Siluetas acercandose al refugio...", 7);

        for (int x = ancho - 15; x >= ancho / 2 - 5; x -= 5) {
            rlutil::locate(x, 10);
            cout << " o/   o\\   o ";
            rlutil::msleep(50);
        }

        rlutil::cls();
        rlutil::setColor(rlutil::LIGHTGREEN);

        imprimirCentrado("=== NUEVOS SUPERVIVIENTES ===", 5);

        rlutil::setColor(rlutil::WHITE);

        imprimirCentrado("Un grupo encontro tu refugio.", 8);
        imprimirCentrado("Supervivientes: +" + to_string(nuevos_supervivientes), 10);
        imprimirCentrado("Agua: +" + to_string(extra_agua), 12);
        imprimirCentrado("Comida: +" + to_string(extra_comida), 14);

        dibujarSiluetaSupervivientes(ancho / 2 - 11, 16);

        rlutil::setColor(rlutil::YELLOW);
        imprimirCentrado("Presione una tecla para continuar...", 21);
        rlutil::anykey();
    }

    // =====================================================
    // EVENTO 1: HORDA ZOMBIE
    // =====================================================

    else if (tipo_evento == 1) {

        int hordaZ = rand() % 31;

        int probabilidadganar;

        if (nightmare) {
            probabilidadganar = 45 - (hordaZ * 2) - 20 + (defensas * 2);
        }
        else {
            probabilidadganar = 80 - (hordaZ * 2) + (defensas * 3);
        }

        if (probabilidadganar > 90) probabilidadganar = 90;
        if (probabilidadganar < 5) probabilidadganar = 5;

        rlutil::cls();

        if (hordaZ == 0) {

            rlutil::setColor(rlutil::LIGHTGREEN);

            imprimirCentrado("=== ZONA DESPEJADA ===", 8);
            imprimirCentrado("No encontraste zombies.", 10);

        }
        else {

            rlutil::setColor(rlutil::LIGHTRED);

            if (nightmare) {
                imprimirCentrado("¡HORDA EN MODO NIGHTMARE!", 4);
            }
            else {
                imprimirCentrado("=== ENCUENTRO HOSTIL ===", 4);
            }

            rlutil::setColor(rlutil::WHITE);

            imprimirCentrado("Cantidad de zombies: " + to_string(hordaZ), 6);

            string opcionesHorda[2] = {
                "Enfrentar (Probabilidad: " + to_string(probabilidadganar) + "%)",
                "Huir de la horda"
            };

            rlutil::setColor(rlutil::DARKGREY);
            imprimirCentrado("Flechas: mover | ENTER: elegir", 16);

            int opcion = menuFlechas(opcionesHorda, 2, 8, 1, 2, hordaZ);

            if (opcion == 0) {

                rlutil::cls();

                int tirada = rand() % 100 + 1;

                if (tirada <= probabilidadganar) {

                    rlutil::setColor(rlutil::LIGHTGREEN);

                    imprimirCentrado("¡VICTORIA!", 8);
                    imprimirCentrado("Lograste eliminar a la horda.", 10);

                }
                else {

                    rlutil::setColor(rlutil::LIGHTRED);

                    imprimirCentrado("¡LA HORDA SUPERO TUS DEFENSAS!", 6);

                    if (supervivientes == 1) {

                        supervivientes = 0;

                        imprimirCentrado("Tu refugio fue invadido.", 10);
                        imprimirCentrado("No sobreviviste al ataque.", 12);

                    }
                    else {

                        int sup_perdidos = rand() % 2 + 1;

                        if (sup_perdidos > supervivientes) {
                            sup_perdidos = supervivientes;
                        }

                        int com_perdida = rand() % 6 + 2;
                        int agua_perdida = rand() % 6 + 2;

                        supervivientes -= sup_perdidos;

                        comida -= com_perdida;
                        agua -= agua_perdida;

                        if (comida < 0) comida = 0;
                        if (agua < 0) agua = 0;

                        imprimirCentrado("Supervivientes perdidos: -" + to_string(sup_perdidos), 10);
                        imprimirCentrado("Comida perdida: -" + to_string(com_perdida), 12);
                        imprimirCentrado("Agua perdida: -" + to_string(agua_perdida), 14);
                    }
                }
            }
            else if (opcion == 1) {

                rlutil::cls();
                rlutil::setColor(rlutil::LIGHTGREEN);

                imprimirCentrado("RETIRADA TACTICA", 8);
                imprimirCentrado("Lograste escapar de la horda.", 10);
            }

        }

        rlutil::setColor(rlutil::YELLOW);
        imprimirCentrado("Presione una tecla para continuar...", 20);
        rlutil::anykey();
    }

    // =====================================================
    // EVENTO 2: FILTRACIONES Y PLAGAS
    // =====================================================

    else if (tipo_evento == 2) {

        int comida_perdida = rand() % 5 + 1;
        int agua_perdida = rand() % 5 + 1;

        comida -= comida_perdida;
        agua -= agua_perdida;

        if (comida < 0) comida = 0;
        if (agua < 0) agua = 0;

        rlutil::cls();
        rlutil::setColor(rlutil::LIGHTRED);

        imprimirCentrado("=== PROBLEMA CRITICO EN EL REFUGIO ===", 5);
        imprimirCentrado("¡Filtraciones y plagas dañaron los suministros!", 7);

        dibujarSiluetaRefugioDanado(ancho / 2 - 10, 10);

        rlutil::setColor(rlutil::WHITE);

        imprimirCentrado("Comida perdida: -" + to_string(comida_perdida), 16);
        imprimirCentrado("Agua perdida: -" + to_string(agua_perdida), 18);

        rlutil::setColor(rlutil::YELLOW);
        imprimirCentrado("Presione una tecla para continuar...", 21);
        rlutil::anykey();
    }

    // =====================================================
    // EVENTO 3: EMBOSCADA (SOLO NIGHTMARE)
    // =====================================================

    else if (tipo_evento == 3) {

        rlutil::cls();
        rlutil::setColor(rlutil::LIGHTRED);

        imprimirCentrado("=== ¡EMBOSCADA! ===", 5);
        imprimirCentrado("Alguien te ataca mientras buscas provisiones.", 8);

        int tirada = rand() % 100 + 1;

        // 35% de posibilidades de sobrevivir sin consecuencias.
        if (tirada <= 35) {

            rlutil::setColor(rlutil::LIGHTGREEN);
            imprimirCentrado("Lograste escapar del atacante.", 12);

        }
        else if (tirada <= 75) {

            comida -= 4;
            agua -= 3;

            if (comida < 0) comida = 0;
            if (agua < 0) agua = 0;

            rlutil::setColor(rlutil::LIGHTRED);

            imprimirCentrado("Te robaron parte de tus suministros.", 12);
            imprimirCentrado("Comida: -4 | Agua: -3", 14);

        }
        else {

            supervivientes = 0;

            rlutil::setColor(rlutil::RED);

            imprimirCentrado("Recibiste una herida mortal.", 12);
            imprimirCentrado("No lograste regresar al refugio.", 14);
        }

        rlutil::setColor(rlutil::YELLOW);
        imprimirCentrado("Presione una tecla para continuar...", 20);
        rlutil::anykey();
    }

    // =====================================================
    // EVENTO 4: SAQUEADORES (SOLO NIGHTMARE)
    // =====================================================

    else if (tipo_evento == 4) {

        int perdidaComida = rand() % 7 + 4;
        int perdidaAgua = rand() % 6 + 3;

        comida -= perdidaComida;
        agua -= perdidaAgua;

        if (comida < 0) comida = 0;
        if (agua < 0) agua = 0;

        rlutil::cls();
        rlutil::setColor(rlutil::LIGHTRED);

        imprimirCentrado("=== SAQUEADORES EN EL REFUGIO ===", 6);
        imprimirCentrado("Alguien logro entrar durante la noche.", 9);

        rlutil::setColor(rlutil::WHITE);

        imprimirCentrado("Comida robada: -" + to_string(perdidaComida), 12);
        imprimirCentrado("Agua robada: -" + to_string(perdidaAgua), 14);

        rlutil::setColor(rlutil::YELLOW);
        imprimirCentrado("Presione una tecla para continuar...", 19);
        rlutil::anykey();
    }

    // =====================================================
    // EVENTO 5: INFECCION (SOLO NIGHTMARE)
    // =====================================================

    else if (tipo_evento == 5) {

        rlutil::cls();
        rlutil::setColor(rlutil::LIGHTRED);

        imprimirCentrado("=== INFECCION ===", 6);
        imprimirCentrado("Descubris una herida infectada.", 9);

        int tirada = rand() % 100 + 1;

        if (tirada <= 25) {

            supervivientes = 0;

            rlutil::setColor(rlutil::RED);

            imprimirCentrado("La infeccion se extendio demasiado.", 12);
            imprimirCentrado("Has muerto.", 14);

        }
        else {

            comida -= 5;
            agua -= 5;

            if (comida < 0) comida = 0;
            if (agua < 0) agua = 0;

            rlutil::setColor(rlutil::WHITE);

            imprimirCentrado("Lograste sobrevivir, pero necesitas recuperarte.", 12);
            imprimirCentrado("Comida: -5 | Agua: -5", 14);
        }

        rlutil::setColor(rlutil::YELLOW);
        imprimirCentrado("Presione una tecla para continuar...", 20);
        rlutil::anykey();
    }

    // =====================================================
    // EVENTO 6: HORDA MASIVA (SOLO NIGHTMARE)
    // =====================================================

    else if (tipo_evento == 6) {

        rlutil::cls();
        rlutil::setColor(rlutil::RED);

        imprimirCentrado("=== ¡ALERTA DE HORDA MASIVA! ===", 5);
        imprimirCentrado("Decenas de zombies rodean el refugio.", 8);

        int defensaTotal = defensas * 4;
        int tirada = rand() % 100 + 1;

        int posibilidad = 20 + defensaTotal;

        if (posibilidad > 80) posibilidad = 80;

        if (tirada <= posibilidad) {

            rlutil::setColor(rlutil::LIGHTGREEN);

            imprimirCentrado("¡Sobreviviste al ataque!", 12);
            imprimirCentrado("Tus defensas resistieron la invasion.", 14);

        }
        else {

            supervivientes = 0;

            rlutil::setColor(rlutil::RED);

            imprimirCentrado("Las barricadas fueron destruidas.", 12);
            imprimirCentrado("La horda invadio el refugio.", 14);
        }

        rlutil::setColor(rlutil::YELLOW);
        imprimirCentrado("Presione una tecla para continuar...", 20);
        rlutil::anykey();
    }
}

