#include <iostream>
#include <string>
#include "rlutil.h"
#include "visual.h"

using namespace std;

void animarInicioJuego() {
    rlutil::cls();
    rlutil::hidecursor();

    int ancho = rlutil::tcols();
    int centroX = ancho / 2;

    // Encabezado
    rlutil::setColor(rlutil::LIGHTRED);
    imprimirCentrado("==============================================", 5);
    imprimirCentrado("       ZOMBIE SURVIVENCIA - SISTEMA V1.0      ", 6);
    imprimirCentrado("==============================================", 7);

    // Mensaje inicial
    rlutil::setColor(rlutil::GREY);
    imprimirCentrado("INICIANDO PROTOCOLO DE EMERGENCIA...", 10);

    // Mensajes de carga
    string mensajes[] = {
        "Buscando conexion con la red...",
        "ERROR: RED GLOBAL NO DISPONIBLE",
        "Analizando zonas de peligro...",
        "Detectando supervivientes...",
        "Preparando refugio..."
    };

    for (int i = 0; i < 5; i++) {
        rlutil::locate(centroX - 19, 12);
        rlutil::setColor(i == 1 ? rlutil::LIGHTRED : rlutil::LIGHTGREEN);
        cout << "> " << mensajes[i] << "                    ";
        rlutil::msleep(550);
    }

    // Barra de carga
    rlutil::setColor(rlutil::WHITE);
    imprimirCentrado("CARGANDO SISTEMA DE SUPERVIVENCIA", 15);

    int largoBarra = 30;
    int inicioX = (ancho - largoBarra - 2) / 2;

    for (int i = 0; i <= largoBarra; i++) {
        rlutil::locate(inicioX, 17);

        rlutil::setColor(rlutil::WHITE);
        cout << "[";

        for (int j = 0; j < largoBarra; j++) {
            if (j < i) {
                rlutil::setColor(rlutil::LIGHTGREEN);
                cout << "#";
            } else {
                rlutil::setColor(rlutil::DARKGREY);
                cout << "-";
            }
        }

        rlutil::setColor(rlutil::WHITE);
        cout << "]";

        rlutil::locate(centroX - 4, 19);
        rlutil::setColor(rlutil::YELLOW);
        cout << (i * 100 / largoBarra) << "%   ";

        rlutil::msleep(55);
    }

    // Finalización
    rlutil::setColor(rlutil::LIGHTGREEN);
    imprimirCentrado("SISTEMA OPERATIVO", 22);

    rlutil::setColor(rlutil::LIGHTRED);
    imprimirCentrado("ADVERTENCIA: NADIE VENDRA A RESCATARTE.", 24);

    rlutil::msleep(1200);

    rlutil::showcursor();
    rlutil::setColor(rlutil::WHITE);
}
void animarConstruccionBase() {
    rlutil::cls();
    rlutil::hidecursor();

    rlutil::setColor(rlutil::LIGHTGREEN);
    imprimirCentrado("=== CONSTRUYENDO REFUGIO DE SUPERVIVENCIA ===", 4);

    int ancho = rlutil::tcols();
    int centroX = ancho / 2 - 10; // Base para alinear los dibujos ASCII al centro

    // Paso 1: Terreno
    rlutil::setColor(rlutil::DARKGREY);
    rlutil::locate(centroX, 6);  cout << "[....................] 0% - Preparando el terreno...        ";
    rlutil::locate(centroX + 5, 12); cout << "        _.-._          ";
    rlutil::locate(centroX + 5, 13); cout << "       (     )         ";
    rlutil::locate(centroX + 5, 14); cout << "        `---'          ";
    rlutil::msleep(600);

    // Paso 2: Cimientos
    rlutil::setColor(rlutil::YELLOW);
    rlutil::locate(centroX, 6);  cout << "[######..............] 30% - Levantando cimientos y muros ";
    rlutil::locate(centroX + 5, 11); cout << "      +-------+        ";
    rlutil::locate(centroX + 5, 12); cout << "      |       |        ";
    rlutil::locate(centroX + 5, 13); cout << "      |       |        ";
    rlutil::locate(centroX + 5, 14); cout << "      +-------+        ";
    rlutil::msleep(600);

    // Paso 3: Techo y Barricadas
    rlutil::setColor(rlutil::LIGHTRED);
    rlutil::locate(centroX, 6);  cout << "[############........] 60% - Agregando techo y barricadas   ";
    rlutil::locate(centroX + 5, 10); cout << "       /-----\\         ";
    rlutil::locate(centroX + 5, 11); cout << "      /_______\\        ";
    rlutil::locate(centroX + 5, 12); cout << "      | [X] X |        ";
    rlutil::locate(centroX + 5, 13); cout << "      |       |        ";
    rlutil::locate(centroX + 5, 14); cout << "      +-------+        ";
    rlutil::msleep(600);

    // Paso 4: Operativo
    rlutil::setColor(rlutil::LIGHTGREEN);
    rlutil::locate(centroX, 6);  cout << "[####################] 100% - Refugio operativo!          ";
    rlutil::locate(centroX + 5, 10); cout << "       /-----\\  +---+ ";
    rlutil::locate(centroX + 5, 11); cout << "      /_______\\ |[x]| ";
    rlutil::locate(centroX + 5, 12); cout << "      | [X] X | +---+ ";
    rlutil::locate(centroX + 5, 13); cout << "      |  ---  | |[x]| ";
    rlutil::locate(centroX + 5, 14); cout << "      +-------+-+---+ ";

    rlutil::setColor(rlutil::YELLOW);
    imprimirCentrado("Presione cualquier tecla para entrar al refugio...", 18);
    rlutil::anykey();
    rlutil::showcursor();
}

void animarMenu(int frame) {

    int ancho = rlutil::tcols();

    // Posicion vertical de la animacion
    int y = 34;

    if (ancho < 40) return;

    // Ancho aproximado del grupo de zombis
    int anchoGrupo = 27;

    // Distancia maxima sin salir de la pantalla
    int recorrido = ancho - anchoGrupo - 6;

    if (recorrido < 1) return;

    // Movimiento de ida y vuelta
    int ciclo = frame % (recorrido * 2);

    int desplazamiento;

    if (ciclo <= recorrido) {
        desplazamiento = ciclo;
    } else {
        desplazamiento = recorrido * 2 - ciclo;
    }

    int x = 3 + desplazamiento;

    // Limpiar completamente la zona de animacion
    for (int i = 0; i < 3; i++) {
        rlutil::locate(2, y + i);
        cout << string(ancho - 4, ' ');
    }

    // Etiqueta
    rlutil::setColor(rlutil::DARKGREY);
    imprimirCentrado(
        "MOVIMIENTO DETECTADO EN LAS AFUERAS DEL REFUGIO", 32
    );

    // Cabezas
    rlutil::setColor(rlutil::LIGHTRED);
    rlutil::locate(x, y);
    cout << "  Z       Z       Z";

    // Cuerpos
    rlutil::locate(x, y + 1);
    cout << " (o_o)   (o_o)   (o_o)";

    // Piernas animadas
    rlutil::locate(x, y + 2);

    if (frame % 2 == 0) {
        cout << " /|\\     /|\\     /|\\";
    } else {
        cout << " / \\     / \\     / \\";
    }

    rlutil::setColor(rlutil::WHITE);
}

void animarHorda(int frame, int cantidad) {
    int ancho = rlutil::tcols();
    int y = 12;                          // la horda ocupa las filas y, y + 1 e y + 2
    int muro = 3;                        // columna del refugio (a la izquierda)

    int n = cantidad;                    // cuántos zombis se dibujan (máximo 6)
    if (n > 6) n = 6;
    if (n < 1) n = 1;
    int largo = n * 8;                   // cada zombi ocupa 8 columnas

    int inicio = ancho - largo - 2;      // donde aparece la horda (derecha)
    int fin = muro + 6;                  // donde llega (pegada al muro)
    int recorrido = inicio - fin;
    if (recorrido < 4) recorrido = 4;

    int paso = frame % recorrido;        // avanza 1 columna por cuadro y vuelve a empezar
    int x = inicio - paso;

    if (paso == 0) {                     // arranca una vuelta nueva: limpia las 3 filas
        for (int f = 0; f < 3; f++) {
            rlutil::locate(muro + 5, y + f);
            cout << string(ancho - muro - 6, ' ');
        }
    }

    int distancia = x - fin;
    rlutil::setColor(distancia < 10 ? rlutil::LIGHTRED : rlutil::GREY);
    rlutil::locate(muro - 1, y - 2);
    cout << "REFUGIO";
    for (int f = -1; f < 3; f++) {
        rlutil::locate(muro, y + f);
        cout << "|##|";
    }

    string fila0 = "", fila1 = "", fila2 = "";
    for (int i = 0; i < n; i++) {
        bool alt = ((frame / 2 + i) % 2 == 0);
        fila0 += alt ? "   Z    " : "   z    ";
        fila1 += alt ? "\\(o_o)/ " : "|(o_o)| ";
        fila2 += alt ? "  / \\   " : "  | |   ";
    }

    rlutil::setColor(rlutil::GREY);
    rlutil::locate(x, y);     cout << fila0 << "  ";
    rlutil::setColor(rlutil::RED);
    rlutil::locate(x, y + 1); cout << fila1 << "  ";
    rlutil::locate(x, y + 2); cout << fila2 << "  ";
}
void animarAmbiente(int frame) {

    int ancho = rlutil::tcols();
    int derecha = ancho - 20;


    rlutil::setColor(rlutil::DARKGREY);

    int posicionHumo = frame % 3;

    rlutil::locate(12, 17);
    cout << "       ";

    rlutil::locate(12, 16 - posicionHumo);
    cout << " ~ ~ ~ ";

    rlutil::locate(derecha, 17);
    cout << "       ";

    rlutil::locate(derecha, 16 - posicionHumo);
    cout << " ~ ~ ~ ";

    if (frame % 2 == 0) {
        rlutil::setColor(rlutil::LIGHTRED);

        rlutil::locate(13, 22);
        cout << "!!";

        rlutil::locate(derecha + 4, 23);
        cout << "!!";
    } else {
        rlutil::setColor(rlutil::DARKGREY);

        rlutil::locate(13, 22);
        cout << "  ";

        rlutil::locate(derecha + 4, 23);
        cout << "  ";
    }
    string alertas[] = {
        "MOVIMIENTO DETECTADO EN EL SECTOR 07-B",
        "ADVERTENCIA: ACTIVIDAD ZOMBI CERCANA",
        "SISTEMA DE SEGURIDAD COMPROMETIDO",
        "NO ABANDONE EL REFUGIO"
    };

    rlutil::setColor(rlutil::BLACK);
rlutil::locate(1, 27);
cout << string(rlutil::tcols(), ' ');

rlutil::setColor(rlutil::LIGHTRED);
imprimirCentrado(alertas[(frame / 10) % 4], 27);

rlutil::setColor(rlutil::WHITE);
}
