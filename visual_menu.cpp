#include <iostream>
#include <string>
#include "rlutil.h"
#include "visual.h"

using namespace std;

void mostrarMenuPrincipalVisual() {
    rlutil::cls();
    rlutil::hidecursor();
dibujarCiudadApocaliptica();
    int ancho = rlutil::tcols();
    int centroX = ancho / 2;

    // Limitar el diseño a consolas con espacio suficiente
    if (ancho < 75) {
        rlutil::setColor(rlutil::LIGHTRED);
        imprimirCentrado("AMPLIA LA VENTANA DE LA CONSOLA", 5);
        rlutil::setColor(rlutil::WHITE);
        return;
    }

    // ==========================================
    // ENCABEZADO SUPERIOR
    // ==========================================

    rlutil::setColor(rlutil::DARKGREY);
    rlutil::locate(4, 2);
    cout << "SURVIVAL NETWORK // TERMINAL 07-B";

    rlutil::locate(ancho - 29, 2);
    cout << "VERSION 1.0 // OFFLINE";

    rlutil::setColor(rlutil::LIGHTRED);
    imprimirCentrado(
        "==============================================================", 4
    );

    // ==========================================
    // TITULO
    // ==========================================

    rlutil::setColor(rlutil::RED);
    imprimirCentrado("Z O M B I E", 6);

    rlutil::setColor(rlutil::LIGHTRED);
    imprimirCentrado("S U R V I V A L", 7);

    rlutil::setColor(rlutil::GREY);
    imprimirCentrado("EL MUNDO HA CAIDO. SOBREVIVI.", 8);

    rlutil::setColor(rlutil::LIGHTRED);
    imprimirCentrado(
        "==============================================================", 9
    );

    // ==========================================
    // ESTADO DEL APOCALIPSIS
    // ==========================================

    int xIzq = centroX - 29;
    int xDer = centroX + 5;

    rlutil::setColor(rlutil::DARKGREY);
    rlutil::locate(xIzq, 11);
    cout << "SECTOR";

    rlutil::locate(xDer, 11);
    cout << "ESTADO DEL MUNDO";

    rlutil::setColor(rlutil::LIGHTGREEN);
    rlutil::locate(xIzq, 12);
    cout << "07-B / REFUGIO";

    rlutil::setColor(rlutil::LIGHTRED);
    rlutil::locate(xDer, 12);
    cout << "CRITICO // NIVEL 5";

    rlutil::setColor(rlutil::DARKGREY);
    rlutil::locate(xIzq, 13);
    cout << "-----------------------------";

    rlutil::locate(xDer, 13);
    cout << "-----------------------------";

    // ==========================================
    // MARCO DEL MENU
    // ==========================================

    int marcoIzq = centroX - 24;
    int marcoDer = centroX + 24;

    rlutil::setColor(rlutil::DARKGREY);

    for (int y = 14; y <= 25; y++) {
        rlutil::locate(marcoIzq, y);
        cout << "|";

        rlutil::locate(marcoDer, y);
        cout << "|";
    }

    rlutil::locate(marcoIzq, 14);
    cout << "+-----------------------------------------------+";

    rlutil::locate(marcoIzq, 25);
    cout << "+-----------------------------------------------+";


    rlutil::setColor(rlutil::YELLOW);
    imprimirCentrado(
        "FLECHAS: MOVER     ENTER: SELECCIONAR", 29
    );

    rlutil::setColor(rlutil::DARKGREY);
    imprimirCentrado(
        "NO HAY RESCATE. NO HAY SEGUNDO INTENTO.", 31
    );

    rlutil::setColor(rlutil::WHITE);
}

void dibujarOpciones(string opciones[], int cantidad, int seleccion,
                     int yInicio, int separacion) {

    for (int i = 0; i < cantidad; i++) {

        // Limpiar el fondo de la linea
        rlutil::setBackgroundColor(rlutil::BLACK);

        if (i == seleccion) {

            // OPCION SELECCIONADA
            rlutil::setColor(rlutil::BLACK);
            rlutil::setBackgroundColor(rlutil::YELLOW);

            string texto = "  >> " + opciones[i] + " <<  ";

            imprimirCentrado(
                texto,
                yInicio + i * separacion
            );

        } else {

            // OPCIONES NO SELECCIONADAS
            rlutil::setColor(rlutil::DARKGREY);

            string texto = "     " + opciones[i] + "     ";

            imprimirCentrado(
                texto,
                yInicio + i * separacion
            );
        }

        // Restaurar colores
        rlutil::setBackgroundColor(rlutil::BLACK);
        rlutil::setColor(rlutil::WHITE);
    }

    // Restaurar estado final
    rlutil::setBackgroundColor(rlutil::BLACK);
    rlutil::setColor(rlutil::WHITE);
}
int menuFlechas(string opciones[], int cantidad, int yInicio,
                int separacion, int animacion, int dato) {
    int seleccion = 0;
    int frame = 0;
    bool redibujar = true;
    // Evitar menus vacios
    if (cantidad <= 0) {
        return -1;
    }
    rlutil::hidecursor();
    while (true) {
        if (redibujar) {
            dibujarOpciones(
                opciones,
                cantidad,
                seleccion,
                yInicio,
                separacion
            );
            redibujar = false;
        }
        if (kbhit()) {
            int tecla = rlutil::getkey();
            if (tecla == rlutil::KEY_UP) {
                seleccion--;
                if (seleccion < 0) {
                    seleccion = cantidad - 1;
                }
                redibujar = true;
            } else if (tecla == rlutil::KEY_DOWN) {
                seleccion++;
                if (seleccion >= cantidad) {
                    seleccion = 0;
                }
                redibujar = true;
            } else if (tecla == rlutil::KEY_ENTER) {
                rlutil::setBackgroundColor(rlutil::BLACK);
                rlutil::setColor(rlutil::WHITE);
                rlutil::showcursor();
                return seleccion;
            }
        } else {
            if (animacion) {
                animarMenu(frame);
                animarAmbiente(frame);
                frame++;
            }
            rlutil::msleep(120);
        }
    }
}
void mostrarManualAyuda() {

    rlutil::cls();
    rlutil::hidecursor();

    int ancho = rlutil::tcols();

    // ENCABEZADO MILITAR
    rlutil::setColor(rlutil::LIGHTRED);
    imprimirCentrado("==============================================", 2);

    rlutil::setColor(rlutil::WHITE);
    imprimirCentrado("SURVIVAL NETWORK // ARCHIVO CLASIFICADO", 3);

    rlutil::setColor(rlutil::LIGHTRED);
    imprimirCentrado("PROTOCOLO DE SUPERVIVENCIA - NIVEL 07-B", 4);
    imprimirCentrado("==============================================", 5);

    // ESTADO DEL INFORME
    rlutil::setColor(rlutil::DARKGREY);
    imprimirCentrado("DOCUMENTO: SN-072 | ACCESO: AUTORIZADO", 7);

    rlutil::setColor(rlutil::LIGHTRED);
    imprimirCentrado("ADVERTENCIA: LA HUMANIDAD ESTA EN PELIGRO", 8);

    // SECCION 1
    rlutil::setColor(rlutil::YELLOW);
    imprimirCentrado("[ 01 ] OBJETIVO DE LA MISION", 10);

    rlutil::setColor(rlutil::WHITE);
    imprimirCentrado("Sobrevive administrando comida, agua y recursos.", 11);
    imprimirCentrado("Cuantos mas dias resistas, mayor sera tu puntaje.", 12);

    // SECCION 2
    rlutil::setColor(rlutil::YELLOW);
    imprimirCentrado("[ 02 ] OPERACIONES DEL REFUGIO", 14);

    rlutil::setColor(rlutil::LIGHTGREEN);
    imprimirCentrado("EXPLORAR", 15);
    rlutil::setColor(rlutil::WHITE);
    imprimirCentrado("Busca suministros aleatorios: comida y agua.", 16);

    rlutil::setColor(rlutil::LIGHTGREEN);
    imprimirCentrado("FORTALECER", 17);
    rlutil::setColor(rlutil::WHITE);
    imprimirCentrado("Mejora las defensas contra los ataques de hordas.", 18);

    rlutil::setColor(rlutil::LIGHTGREEN);
    imprimirCentrado("ESTADISTICAS", 19);
    rlutil::setColor(rlutil::WHITE);
    imprimirCentrado("Consulta el estado actual de tu grupo.", 20);

    // SECCION 3
    rlutil::setColor(rlutil::YELLOW);
    imprimirCentrado("[ 03 ] AMENAZAS Y EVENTOS", 22);

    rlutil::setColor(rlutil::WHITE);
    imprimirCentrado("Cada dia existe un 30% de probabilidad de eventos", 23);
    imprimirCentrado("hostiles o ataques de hordas.", 24);
    imprimirCentrado("Administra tus defensas o realiza una retirada.", 25);

    // SECCION 4
    rlutil::setColor(rlutil::YELLOW);
    imprimirCentrado("[ 04 ] SISTEMA DE PUNTUACION", 27);

    rlutil::setColor(rlutil::WHITE);
    imprimirCentrado("Dias x 100 + Comida x 10 + Agua x 10", 28);
    imprimirCentrado("+ Supervivientes x 500", 29);

    // ALERTA FINAL
    rlutil::setColor(rlutil::LIGHTRED);
    imprimirCentrado("==============================================", 31);
    imprimirCentrado("RECUERDA: CADA DIA PUEDE SER EL ULTIMO.", 32);

    // PIE DE PAGINA
    rlutil::setColor(rlutil::LIGHTGREEN);
    imprimirCentrado("[ PRESIONE CUALQUIER TECLA PARA CONTINUAR ]", 35);

    rlutil::setColor(rlutil::WHITE);
    rlutil::anykey();

    rlutil::showcursor();
}
