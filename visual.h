#ifndef VISUAL_H_INCLUDED
#define VISUAL_H_INCLUDED
#include <string>
// FUNCIONES GENERALES
void imprimirCentrado(std::string texto, int y);
// ANIMACIONES
void animarInicioJuego();
void animarConstruccionBase();
void animarMenu(int frame);
void animarAmbiente(int frame);
void animarHorda(int frame, int cantidad);
// DIBUJOS
void dibujarCiudadApocaliptica();
void dibujarSiluetaHorda(int x, int y);
void dibujarSiluetaSupervivientes(int x, int y);
void dibujarSiluetaRefugioDanado(int x, int y);
void dibujarOpciones(
    std::string opciones[],
    int cantidad,
    int seleccion,
    int yInicio,
    int separacion
);
// MENUS Y PANTALLAS
void mostrarMenuPrincipalVisual();
void mostrarManualAyuda();
int menuFlechas(
    std::string opciones[],
    int cantidad,
    int yInicio,
    int separacion,
    int animacion = 0,
    int dato = 0
);
#endif // VISUAL_H_INCLUDED
