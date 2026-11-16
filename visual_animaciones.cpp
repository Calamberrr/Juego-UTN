#include <iostream>
#include <string>
#include "rlutil.h"
#include "visual.h"

using namespace std;

int centrarX(string texto) {
    return (rlutil::tcols() - (int)texto.length()) / 2 + 1;
}

void borrarTexto(int x, int y, int largo) {
    rlutil::locate(x, y);
    for (int i = 0; i < largo; i++) {
        cout << ' ';
    }
}

bool pausar(int ms) {
    int transcurrido = 0;
    while (transcurrido < ms) {
        if (rlutil::nb_getch() != 0) {
            return true;
        }
        rlutil::msleep(10);
        transcurrido += 10;
    }
    return false;
}

bool escribirLento(string texto, int x, int y, int color, int demora) {
    rlutil::setColor(color);
    rlutil::locate(x, y);
    for (int i = 0; i < (int)texto.length(); i++) {
        cout << texto[i] << flush;
        if (pausar(demora)) {
            return true;
        }
    }
    return false;
}

bool escribirCentrado(string texto, int y, int color, int demora) {
    return escribirLento(texto, centrarX(texto), y, color, demora);
}

bool narrarEscena(string lineas[], int cantidad, int color, int colorFinal) {
    rlutil::cls();
    int yInicial = 10;

    for (int i = 0; i < cantidad; i++) {
        int y = yInicial + i * 2;

        if (i == cantidad - 1) {
            if (pausar(400)) return true;                       // silencio dramatico
            if (escribirCentrado(lineas[i], y, colorFinal, 70)) return true;
        } else {
            if (escribirCentrado(lineas[i], y, color, 35)) return true;
            if (pausar(250)) return true;
        }
    }
    return pausar(500);
}

// Texto que parpadea cada vez mas rapido, como una senal que se muere.
bool senalPerdida() {
    rlutil::cls();
    string texto = "...SENAL PERDIDA...";
    int x = centrarX(texto);

    for (int i = 0; i < 5; i++) {
        rlutil::setColor(i % 2 == 0 ? rlutil::LIGHTRED : rlutil::DARKGREY);
        rlutil::locate(x, 12);
        cout << texto;
        if (pausar(180 - i * 30)) return true;

        borrarTexto(x, 12, (int)texto.length());
        if (pausar(100)) return true;
    }
    return false;
}

void dibujarBanner(string banner[], int filas, int yInicial, int color) {
    int x = centrarX(banner[0]);
    rlutil::setColor(color);
    for (int i = 0; i < filas; i++) {
        rlutil::locate(x, yInicial + i);
        cout << banner[i];
    }
}

bool mostrarTitulo() {
    string banner[5] = {
        " _____   ___   __  __  ____   ___  _____ ",
        "|__  /  / _ \\ |  \\/  || __ ) |_ _|| ____|",
        "  / /  | | | || |\\/| ||  _ \\  | | |  _|  ",
        " / /_  | |_| || |  | || |_) | | | | |___ ",
        "/____|  \\___/ |_|  |_||____/ |___||_____|"
    };

    rlutil::cls();

    if (escribirCentrado("M U N D O", 5, rlutil::GREY, 120)) return true;

    // El banner aparece linea por linea
    int x = centrarX(banner[0]);
    rlutil::setColor(rlutil::LIGHTRED);
    for (int i = 0; i < 5; i++) {
        rlutil::locate(x, 7 + i);
        cout << banner[i];
        if (pausar(200)) return true;
    }

    // Destello blanco
    for (int i = 0; i < 3; i++) {
        dibujarBanner(banner, 5, 7, rlutil::WHITE);
        if (pausar(80)) return true;
        dibujarBanner(banner, 5, 7, rlutil::LIGHTRED);
        if (pausar(80)) return true;
    }

    if (pausar(600)) return true;
    if (escribirCentrado("NADIE VENDRA A RESCATARTE.", 14, rlutil::GREY, 70)) return true;
    return pausar(500);
}

void esperarTecla(string texto, int y) {
    int x = centrarX(texto);
    bool visible = true;

    while (rlutil::nb_getch() == 0) {
        if (visible) {
            rlutil::setColor(rlutil::YELLOW);
            rlutil::locate(x, y);
            cout << texto;
        } else {
            borrarTexto(x, y, (int)texto.length());
        }
        visible = !visible;
        rlutil::msleep(250);
    }
}

// ---------- Animacion principal ----------


void animarInicioJuego() {
    rlutil::cls();
    rlutil::hidecursor();

    // Limpia teclas pendientes
    while (rlutil::nb_getch() != 0) { }

    string historia[4] = {
        "Todo empezo con un brote en el puerto.",
        "En 48 horas, la ciudad dejo de responder.",
        "Las calles quedaron infestadas.",
        "Los pocos sobrevivientes buscan refugio."
    };

    bool salteada = narrarEscena(
        historia, 4, rlutil::GREY, rlutil::LIGHTRED
    );

    if (!salteada) salteada = senalPerdida();

    if (!salteada) salteada = mostrarTitulo();

    if (!salteada) {
        esperarTecla("[ Presiona una tecla para comenzar ]", 18);
    }

    rlutil::cls();
    rlutil::showcursor();
    rlutil::setColor(rlutil::WHITE);
}

void limpiarLinea(int y, int ancho) {
    rlutil::locate(2, y);
    for (int i = 0; i < ancho - 4; i++) {
        cout << ' ';
    }
}

// numero (0, 1 o 2) sirve para que cada zombi camine y parpadee desfasado
void dibujarZombi(int x, int y, int numero, int frame, bool peligro) {
    int color = rlutil::LIGHTRED;
    if (numero % 2 == 1) {
        color = rlutil::RED;
    }

    char ojo = 'o';
    if (peligro) {
        ojo = '@';                                  // se ponen frenéticos al acercarse
    }
    if ((frame + numero * 7) % 25 == 0) {
        ojo = '-';                                  // parpadeo
    }

    rlutil::setColor(color);

    rlutil::locate(x, y);
    cout << "   Z   ";

    rlutil::locate(x, y + 1);
    cout << " (" << ojo << "_" << ojo << ") ";

    rlutil::locate(x, y + 2);
    if ((frame + numero) % 2 == 0) {
        cout << "  /|\\  ";
    } else {
        cout << "  / \\  ";
    }
}

void dibujarRefugio(int x, int y, int color) {
    rlutil::setColor(color);

    rlutil::locate(x, y);
    cout << "  .--.  ";

    rlutil::locate(x, y + 1);
    cout << " /____\\ ";

    rlutil::locate(x, y + 2);
    cout << " |[##]| ";
}

// ---------- Animacion del menu ----------

void animarMenu(int frame) {

    int ancho = rlutil::tcols();

    // Posicion vertical de la animacion
    int y = 34;

    if (ancho < 40) return;

    // Tamanos: 3 zombis de 7 columnas con 2 de separacion = 25
    int anchoGrupo = 25;
    int anchoRefugio = 8;

    // Distancia maxima sin chocar con el refugio ni salir de la pantalla
    int recorrido = ancho - anchoGrupo - anchoRefugio - 7;

    if (recorrido < 1) return;

    // Movimiento de ida y vuelta
    int ciclo = frame % (recorrido * 2);

    int desplazamiento;
    bool avanzando;

    if (ciclo <= recorrido) {
        desplazamiento = ciclo;
        avanzando = true;
    } else {
        desplazamiento = recorrido * 2 - ciclo;
        avanzando = false;
    }

    int x = 3 + desplazamiento;
    int xRefugio = ancho - anchoRefugio - 2;

    // Estado de la escena
    bool peligro = desplazamiento > recorrido * 3 / 4;   // ultimo cuarto del camino
    bool parpadeo = (frame / 4) % 2 == 0;

    // Limpiar la zona completa (etiqueta + 3 filas de zombis)
    limpiarLinea(y - 2, ancho);
    for (int i = 0; i < 3; i++) {
        limpiarLinea(y + i, ancho);
    }

    // Etiqueta segun la situacion
    if (peligro && avanzando) {
        if (parpadeo) {
            rlutil::setColor(rlutil::LIGHTRED);
            imprimirCentrado("!! ALERTA: LA HORDA SE ACERCA A LAS PUERTAS !!", y - 2);
        }
    } else if (peligro && !avanzando) {
        rlutil::setColor(rlutil::YELLOW);
        imprimirCentrado("Retroceden... por ahora.", y - 2);
    } else {
        rlutil::setColor(rlutil::DARKGREY);
        imprimirCentrado("MOVIMIENTO DETECTADO EN LAS AFUERAS DEL REFUGIO", y - 2);
    }

    // Zombis
    for (int i = 0; i < 3; i++) {
        dibujarZombi(x + i * 9, y, i, frame, peligro);
    }

    // Refugio: titila en amarillo cuando hay peligro
    int colorRefugio = rlutil::LIGHTGREEN;
    if (peligro && parpadeo) {
        colorRefugio = rlutil::YELLOW;
    }
    dibujarRefugio(xRefugio, y, colorRefugio);

    rlutil::setColor(rlutil::WHITE);
}

void animarHorda(int frame, int cantidad) {
    int ancho = rlutil::tcols();
    int y = 12;
    int muro = 3;

    int n = cantidad;
    if (n > 6) n = 6;
    if (n < 1) n = 1;
    int largo = n * 8;

    int inicio = ancho - largo - 2;
    int fin = muro + 6;
    int recorrido = inicio - fin;
    if (recorrido < 4) recorrido = 4;

    int paso = frame % recorrido;
    int x = inicio - paso;

    if (paso == 0) {
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
