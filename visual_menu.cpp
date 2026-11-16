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
    int alto = rlutil::trows();
    int centroX = ancho / 2;

    // Verificar espacio disponible
    if (ancho < 75 || alto < 33) {
        rlutil::setColor(rlutil::LIGHTRED);
        imprimirCentrado("AMPLIA LA VENTANA DE LA CONSOLA", 5);
        rlutil::setColor(rlutil::WHITE);
        return;
    }

    // ==========================================
    // ENCABEZADO DEL SISTEMA
    // ==========================================

    rlutil::setColor(rlutil::DARKGREY);
    rlutil::locate(4, 2);
    cout << "SURVIVAL NETWORK // TERMINAL 07-B";

    rlutil::locate(ancho - 25, 2);
    cout << "SISTEMA // OFFLINE";

    rlutil::setColor(rlutil::LIGHTRED);
    imprimirCentrado(
        "==============================================================", 4
    );

    // ==========================================
    // TITULO PRINCIPAL
    // ==========================================

    rlutil::setColor(rlutil::LIGHTRED);
    imprimirCentrado("Z O M B I E", 6);

    rlutil::setColor(rlutil::WHITE);
    imprimirCentrado("S U R V I V A L", 7);

    rlutil::setColor(rlutil::GREY);
    imprimirCentrado("LA HUMANIDAD ESTA AL BORDE DE LA EXTINCION", 8);

    rlutil::setColor(rlutil::LIGHTRED);
    imprimirCentrado(
        "==============================================================", 9
    );

    // ==========================================
    // INFORMACION DEL REFUGIO
    // ==========================================

    int xIzq = centroX - 29;
    int xDer = centroX + 5;

    rlutil::setColor(rlutil::DARKGREY);

    rlutil::locate(xIzq, 11);
    cout << "UBICACION DEL REFUGIO";

    rlutil::locate(xDer, 11);
    cout << "ESTADO DE LA CIUDAD";

    rlutil::setColor(rlutil::LIGHTGREEN);
    rlutil::locate(xIzq, 12);
    cout << "SECTOR 07-B";

    rlutil::setColor(rlutil::LIGHTRED);
    rlutil::locate(xDer, 12);
    cout << "AMENAZA CRITICA";

    rlutil::setColor(rlutil::DARKGREY);

    rlutil::locate(xIzq, 13);
    cout << "-----------------------------";

    rlutil::locate(xDer, 13);
    cout << "-----------------------------";

    // ==========================================
    // MARCO DEL MENU
    // ==========================================

    int marcoIzq = centroX - 26;
    int marcoDer = centroX + 26;

    string borde = "+" + string(50, '-') + "+";

    rlutil::setColor(rlutil::LIGHTRED);

    rlutil::locate(marcoIzq, 14);
    cout << borde;

    rlutil::locate(marcoIzq, 28);
    cout << borde;

    for (int y = 15; y < 28; y++) {
        rlutil::locate(marcoIzq, y);
        cout << "|";

        rlutil::locate(marcoDer, y);
        cout << "|";
    }

    // Encabezado interno
    rlutil::setColor(rlutil::YELLOW);
    imprimirCentrado("CENTRO DE COMANDO", 16);

    // ==========================================
    // INSTRUCCIONES
    // ==========================================

    rlutil::setColor(rlutil::YELLOW);
    imprimirCentrado(
        "[ FLECHAS ] MOVER     [ ENTER ] CONFIRMAR", 29
    );

    rlutil::setColor(rlutil::DARKGREY);
    imprimirCentrado(
        "NO HAY RESCATE. NO HAY SEGUNDO INTENTO.", 31
    );

    rlutil::setBackgroundColor(rlutil::BLACK);
    rlutil::setColor(rlutil::WHITE);
}


void dibujarOpciones(string opciones[], int cantidad, int seleccion,
                     int yInicio, int separacion) {

    for (int i = 0; i < cantidad; i++) {

        int y = yInicio + i * separacion;

        // Limpiar la linea anterior
        rlutil::setBackgroundColor(rlutil::BLACK);
        rlutil::setColor(rlutil::WHITE);

        if (i == seleccion) {

            // OPCION SELECCIONADA
            rlutil::setBackgroundColor(rlutil::YELLOW);
            rlutil::setColor(rlutil::BLACK);

            string texto = "  >> " + opciones[i] + " <<  ";

            imprimirCentrado(texto, y);

        } else {

            // OPCIONES NORMALES
            rlutil::setBackgroundColor(rlutil::BLACK);
            rlutil::setColor(rlutil::GREY);

            string texto = "     " + opciones[i] + "     ";

            imprimirCentrado(texto, y);
        }

        rlutil::setBackgroundColor(rlutil::BLACK);
        rlutil::setColor(rlutil::WHITE);
    }
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
    imprimirCentrado("COMERCIAR", 19);
    rlutil::setColor(rlutil::WHITE);
    imprimirCentrado("Intercambia comida por agua o agua por comida.", 20);
    imprimirCentrado("Un intercambio exitoso consume el dia.", 21);

    // SECCION 3
    rlutil::setColor(rlutil::YELLOW);
    imprimirCentrado("[ 03 ] AMENAZAS Y EVENTOS", 25);

    rlutil::setColor(rlutil::WHITE);
    imprimirCentrado("Cada dia puede haber eventos hostiles o encuentros.", 26);
    imprimirCentrado("La amenaza aumenta cada 5 dias sobrevividos.", 27);

    // SECCION 4
    rlutil::setColor(rlutil::YELLOW);
    imprimirCentrado("[ 04 ] SISTEMA DE PUNTUACION", 29);

    rlutil::setColor(rlutil::WHITE);
    imprimirCentrado("Dias x 100 + Comida x 10 + Agua x 10", 30);
    imprimirCentrado("+ Supervivientes x 500", 31);

    // ALERTA FINAL
    rlutil::setColor(rlutil::LIGHTRED);
    imprimirCentrado("RECUERDA: CADA DIA PUEDE SER EL ULTIMO.", 33);

    // PIE DE PAGINA
    rlutil::setColor(rlutil::LIGHTGREEN);
    imprimirCentrado("[ PRESIONE CUALQUIER TECLA PARA CONTINUAR ]", 35);

    rlutil::setColor(rlutil::WHITE);
    rlutil::anykey();

    rlutil::showcursor();
}
