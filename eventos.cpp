#include <iostream>
#include "visual.h"
#include <cstdlib>
#include <windows.h>
#include "rlutil.h"
#include "juego.h"
#include "highscore.h"
#include "eventos.h"

using namespace std;


void ejecutarEventos(int &comida, int &agua, int &supervivientes,
                     int defensas, int diasSobrevividos) {

    int ancho = rlutil::tcols();

    // Nightmare se activa automaticamente cuando queda uno.
    bool nightmare = (supervivientes == 1);
    int nivelDificultad = (diasSobrevividos - 1) / 5;

    // En grupo aparecen los eventos generales y los nuevos eventos de decision.
    // En solitario tambien pueden aparecer los cuatro eventos exclusivos Nightmare.
    int eventosNormales[9] = {0, 1, 2, 7, 8, 9, 10, 11, 12};
    int tipo_evento;

    if (nightmare) {
        tipo_evento = rand() % 13;
    }
    else {
        tipo_evento = eventosNormales[rand() % 9];
    }

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
            probabilidadganar = 45 - (hordaZ * 2) - 20 +
                                (defensas * 2) - (nivelDificultad * 4);
        }
        else {
            probabilidadganar = 80 - (hordaZ * 2) +
                                (defensas * 3) - (nivelDificultad * 3);
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

    // =====================================================
    // EVENTO 7: SUPERVIVIENTE HERIDO
    // =====================================================
    else if (tipo_evento == 7) {

        rlutil::cls();
        rlutil::setColor(rlutil::YELLOW);
        imprimirCentrado("=== UN HERIDO EN LA ENTRADA ===", 5);
        rlutil::setColor(rlutil::WHITE);
        imprimirCentrado("Un desconocido pide refugio. Tiene una herida grave.", 8);
        imprimirCentrado("Ayudarlo requiere 3 de comida y 3 de agua.", 10);

        string opciones[2] = {
            "Ayudarlo y dejarlo entrar",
            "No arriesgar los suministros"
        };
        int opcion = menuFlechas(opciones, 2, 13, 2);

        rlutil::cls();
        if (opcion == 0 && comida >= 3 && agua >= 3) {
            comida -= 3;
            agua -= 3;
            supervivientes++;
            rlutil::setColor(rlutil::LIGHTGREEN);
            imprimirCentrado("EL DESCONOCIDO SE UNE AL REFUGIO", 8);
            imprimirCentrado("Gastaste 3 de comida y 3 litros de agua.", 11);
            imprimirCentrado("Supervivientes: +1", 13);
        }
        else if (opcion == 0) {
            rlutil::setColor(rlutil::LIGHTRED);
            imprimirCentrado("NO TENES SUMINISTROS SUFICIENTES", 8);
            imprimirCentrado("No pudiste ayudarlo y se marcho.", 11);
        }
        else {
            rlutil::setColor(rlutil::YELLOW);
            imprimirCentrado("El desconocido se aleja del refugio.", 9);
            imprimirCentrado("Decidiste guardar tus provisiones.", 11);
        }

        rlutil::setColor(rlutil::YELLOW);
        imprimirCentrado("Presione una tecla para continuar...", 19);
        rlutil::anykey();
    }

    // =====================================================
    // EVENTO 8: CAJA MILITAR
    // =====================================================
    else if (tipo_evento == 8) {

        rlutil::cls();
        rlutil::setColor(rlutil::LIGHTCYAN);
        imprimirCentrado("=== CAJA MILITAR ABANDONADA ===", 6);
        rlutil::setColor(rlutil::WHITE);
        imprimirCentrado("Encontraste una caja cerrada junto a un vehiculo.", 9);
        imprimirCentrado("Podria contener suministros... o una trampa.", 11);

        string opciones[2] = {"Abrir la caja", "Dejarla y regresar"};
        int opcion = menuFlechas(opciones, 2, 14, 2);

        rlutil::cls();
        if (opcion == 0) {
            int tirada = rand() % 100 + 1;
            if (tirada <= 70) {
                int comidaGanada = rand() % 6 + 3;
                int aguaGanada = rand() % 6 + 3;
                comida += comidaGanada;
                agua += aguaGanada;
                rlutil::setColor(rlutil::LIGHTGREEN);
                imprimirCentrado("¡LA CAJA TENIA SUMINISTROS!", 8);
                imprimirCentrado("Comida: +" + to_string(comidaGanada), 11);
                imprimirCentrado("Agua: +" + to_string(aguaGanada), 13);
            }
            else {
                int comidaPerdida = (comida > 0) ? (rand() % 3 + 1) : 0;
                int aguaPerdida = (agua > 0) ? (rand() % 3 + 1) : 0;
                comida -= comidaPerdida;
                agua -= aguaPerdida;
                if (comida < 0) comida = 0;
                if (agua < 0) agua = 0;
                rlutil::setColor(rlutil::LIGHTRED);
                imprimirCentrado("¡ERA UNA TRAMPA!", 8);
                imprimirCentrado("Perdiste parte de tus provisiones.", 11);
                imprimirCentrado("Comida: -" + to_string(comidaPerdida) +
                                 " | Agua: -" + to_string(aguaPerdida), 13);
            }
        }
        else {
            rlutil::setColor(rlutil::YELLOW);
            imprimirCentrado("Decidiste no correr el riesgo.", 10);
        }

        rlutil::setColor(rlutil::YELLOW);
        imprimirCentrado("Presione una tecla para continuar...", 19);
        rlutil::anykey();
    }

    // =====================================================
    // EVENTO 9: COMERCIANTE AMBULANTE
    // =====================================================
    else if (tipo_evento == 9) {

        rlutil::cls();
        rlutil::setColor(rlutil::LIGHTCYAN);
        imprimirCentrado("=== COMERCIANTE AMBULANTE ===", 6);
        rlutil::setColor(rlutil::WHITE);
        imprimirCentrado("Un viajero ofrece intercambiar sus provisiones.", 9);

        string opciones[3] = {
            "Cambiar 5 de comida por 4 de agua",
            "Cambiar 5 de agua por 4 de comida",
            "No realizar ningun intercambio"
        };
        int opcion = menuFlechas(opciones, 3, 12, 2);

        rlutil::cls();
        if (opcion == 0 && comida >= 5) {
            comida -= 5;
            agua += 4;
            rlutil::setColor(rlutil::LIGHTGREEN);
            imprimirCentrado("INTERCAMBIO REALIZADO", 9);
            imprimirCentrado("Comida: -5 | Agua: +4", 12);
        }
        else if (opcion == 1 && agua >= 5) {
            agua -= 5;
            comida += 4;
            rlutil::setColor(rlutil::LIGHTGREEN);
            imprimirCentrado("INTERCAMBIO REALIZADO", 9);
            imprimirCentrado("Agua: -5 | Comida: +4", 12);
        }
        else if (opcion == 2) {
            rlutil::setColor(rlutil::YELLOW);
            imprimirCentrado("El comerciante se marcha sin hacer tratos.", 10);
        }
        else {
            rlutil::setColor(rlutil::LIGHTRED);
            imprimirCentrado("NO TENES SUFICIENTES PROVISIONES", 9);
            imprimirCentrado("El intercambio no pudo realizarse.", 12);
        }

        rlutil::setColor(rlutil::YELLOW);
        imprimirCentrado("Presione una tecla para continuar...", 19);
        rlutil::anykey();
    }

    // =====================================================
    // EVENTO 10: DESCONOCIDO EN LA PUERTA
    // =====================================================
    else if (tipo_evento == 10) {

        rlutil::cls();
        rlutil::setColor(rlutil::YELLOW);
        imprimirCentrado("=== ALGUIEN GOLPEA LA PUERTA ===", 6);
        rlutil::setColor(rlutil::WHITE);
        imprimirCentrado("Una persona asegura estar sola y pide entrar.", 9);
        imprimirCentrado("No sabes si dice la verdad.", 11);

        string opciones[2] = {"Abrir la puerta", "Mantener el refugio cerrado"};
        int opcion = menuFlechas(opciones, 2, 14, 2);

        rlutil::cls();
        if (opcion == 0) {
            int tirada = rand() % 100 + 1;
            if (tirada <= 65) {
                supervivientes++;
                rlutil::setColor(rlutil::LIGHTGREEN);
                imprimirCentrado("EL DESCONOCIDO ERA UN SUPERVIVIENTE", 8);
                imprimirCentrado("Se une al grupo. Supervivientes: +1", 11);
            }
            else {
                int comidaRobada = (comida >= 4) ? 4 : comida;
                int aguaRobada = (agua >= 4) ? 4 : agua;
                comida -= comidaRobada;
                agua -= aguaRobada;
                rlutil::setColor(rlutil::LIGHTRED);
                imprimirCentrado("¡ERA UN LADRON!", 8);
                imprimirCentrado("Escapo llevandose parte de tus provisiones.", 11);
                imprimirCentrado("Comida: -" + to_string(comidaRobada) +
                                 " | Agua: -" + to_string(aguaRobada), 13);
            }
        }
        else {
            rlutil::setColor(rlutil::YELLOW);
            imprimirCentrado("No abriste la puerta. La persona se marcho.", 10);
        }

        rlutil::setColor(rlutil::YELLOW);
        imprimirCentrado("Presione una tecla para continuar...", 19);
        rlutil::anykey();
    }

    // =====================================================
    // EVENTO 11: ALARMA EN UN EDIFICIO
    // =====================================================
    else if (tipo_evento == 11) {

        rlutil::cls();
        rlutil::setColor(rlutil::LIGHTCYAN);
        imprimirCentrado("=== UNA ALARMA SIGUE SONANDO ===", 6);
        rlutil::setColor(rlutil::WHITE);
        imprimirCentrado("Una alarma atrae zombies desde varias calles.", 9);
        imprimirCentrado("Tal vez haya suministros en el edificio.", 11);

        string opciones[2] = {"Entrar a buscar suministros", "Alejarse de la zona"};
        int opcion = menuFlechas(opciones, 2, 14, 2);

        rlutil::cls();
        if (opcion == 0) {
            int tirada = rand() % 100 + 1;
            if (tirada <= 60) {
                int comidaGanada = rand() % 5 + 2;
                int aguaGanada = rand() % 4 + 2;
                comida += comidaGanada;
                agua += aguaGanada;
                rlutil::setColor(rlutil::LIGHTGREEN);
                imprimirCentrado("SAQUEO EXITOSO", 8);
                imprimirCentrado("Comida: +" + to_string(comidaGanada), 11);
                imprimirCentrado("Agua: +" + to_string(aguaGanada), 13);
            }
            else {
                int perdida = (supervivientes > 1) ? 1 : 0;
                supervivientes -= perdida;
                comida = (comida >= 2) ? comida - 2 : 0;
                agua = (agua >= 2) ? agua - 2 : 0;
                rlutil::setColor(rlutil::LIGHTRED);
                imprimirCentrado("¡LOS ZOMBIES TE CERRARON EL PASO!", 8);
                if (perdida == 1) {
                    imprimirCentrado("Un superviviente no logro regresar.", 11);
                }
                else {
                    imprimirCentrado("Perdiste provisiones durante la huida.", 11);
                }
                imprimirCentrado("Comida y agua: -2", 13);
            }
        }
        else {
            rlutil::setColor(rlutil::YELLOW);
            imprimirCentrado("Te alejaste antes de atraer a la horda.", 10);
        }

        rlutil::setColor(rlutil::YELLOW);
        imprimirCentrado("Presione una tecla para continuar...", 19);
        rlutil::anykey();
    }

    // =====================================================
    // EVENTO 12: DISCUSION ENTRE SUPERVIVIENTES
    // =====================================================
    else if (tipo_evento == 12) {

        rlutil::cls();
        rlutil::setColor(rlutil::YELLOW);
        imprimirCentrado("=== TENSION EN EL REFUGIO ===", 6);
        rlutil::setColor(rlutil::WHITE);
        imprimirCentrado("Dos supervivientes discuten por el reparto de provisiones.", 9);
        imprimirCentrado("Tenes que intervenir o dejar que lo resuelvan.", 11);

        string opciones[2] = {
            "Mediar y compartir provisiones (-2 comida, -2 agua)",
            "No intervenir"
        };
        int opcion = menuFlechas(opciones, 2, 14, 2);

        rlutil::cls();
        if (opcion == 0 && comida >= 2 && agua >= 2) {
            comida -= 2;
            agua -= 2;
            rlutil::setColor(rlutil::LIGHTGREEN);
            imprimirCentrado("EL CONFLICTO FUE RESUELTO", 9);
            imprimirCentrado("El grupo recupero la calma.", 12);
        }
        else if (opcion == 0) {
            rlutil::setColor(rlutil::LIGHTRED);
            imprimirCentrado("NO ALCANZARON LOS SUMINISTROS", 8);
            if (supervivientes > 1) {
                supervivientes--;
                imprimirCentrado("Un superviviente decidio abandonar el refugio.", 11);
            }
            else {
                imprimirCentrado("La tension aumento dentro del refugio.", 11);
            }
        }
        else {
            int tirada = rand() % 100 + 1;
            if (tirada <= 40 && supervivientes > 1) {
                supervivientes--;
                rlutil::setColor(rlutil::LIGHTRED);
                imprimirCentrado("EL CONFLICTO TERMINO MAL", 9);
                imprimirCentrado("Un superviviente abandono el refugio.", 12);
            }
            else {
                rlutil::setColor(rlutil::LIGHTGREEN);
                imprimirCentrado("El grupo logro resolver sus diferencias.", 10);
            }
        }

        rlutil::setColor(rlutil::YELLOW);
        imprimirCentrado("Presione una tecla para continuar...", 19);
        rlutil::anykey();
    }

}

