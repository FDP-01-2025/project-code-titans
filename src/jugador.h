#ifndef JUGADOR_H
#define JUGADOR_H

#include <string>
#include <iostream>
#include "gameConstants.h" // Uso constantes como MAX_REGISTROS y Registro
#include "playerData.h"    // Para funciones de guardar y cargar datos del jugador
#include "utils.h"           // Aquí incluyo el limpiarConsola

using namespace std;

// Aquí defino el array de posiciones para la ruleta que usaré en el programa,
// solo lo defino una vez aquí para evitar múltiples definiciones
Posicion posiciones[NUMEROS];

// Defino la estructura Jugador con toda la información que necesito guardar sobre cada jugador
struct Jugador {
    string nombre;                // Nombre del jugador
    int dinero = 0;               // Dinero actual que tiene el jugador
    Registro historial[MAX_REGISTROS]; // Historial de movimientos y eventos
    int numRegistros = 0;         // Cuántos registros tiene el historial

    // Estadísticas del jugador para los juegos
    int partidasJugadas = 0;
    int partidasGanadas = 0;
    int partidasPerdidas = 0;
    int partidasEmpatadas = 0;

    // Actualizo las estadísticas del jugador guardándolas en el archivo
    inline void actualizarEstadisticas() {
        guardarEstadisticas(nombre, partidasJugadas, partidasGanadas, partidasPerdidas, partidasEmpatadas);
    }

    // Cargo las estadísticas del jugador desde el archivo
    inline void cargarEstadisticasJugador() {
        int j, g, p, e;
        if (cargarEstadisticas(nombre, j, g, p, e)) {
            partidasJugadas = j;
            partidasGanadas = g;
            partidasPerdidas = p;
            partidasEmpatadas = e;
        }
    }

    // Muestro las estadísticas del jugador en consola
    inline void mostrarEstadisticas() {
        cargarEstadisticasJugador(); // Primero cargo para mostrar datos actualizados
        cout << "\nEstadísticas del jugador:\n";
        cout << "Partidas jugadas: " << partidasJugadas << "\n";
        cout << "Partidas ganadas: " << partidasGanadas << "\n";
        cout << "Partidas perdidas: " << partidasPerdidas << "\n";
        cout << "Partidas empatadas: " << partidasEmpatadas << "\n";
    }

    // Agrego un nuevo registro al historial del jugador (si hay espacio)
    inline void agregarRegistro(const string& texto) {
        if (numRegistros < MAX_REGISTROS) {
            historial[numRegistros++].descripcion = texto;
        }
    }

    // Método para que el jugador deposite dinero
    inline void depositar(int cantidad) {
        if (cantidad > 0) {
            dinero += cantidad; // Aumento saldo
            cout << "Has depositado $" << cantidad << ". Saldo actual: $" << dinero << "\n";
            agregarRegistro("Depósito: $" + to_string(cantidad)); // Registro el movimiento
            registrarMovimientoDinero("Depósito", nombre, cantidad, dinero);
            guardarSaldo(nombre, dinero); // Guardo saldo actualizado
        } else {
            cout << "No puedes depositar una cantidad negativa o cero.\n";
        }
    }

    // Método para que el jugador retire dinero
    inline bool retirar(int cantidad) {
        if (cantidad > 0 && cantidad <= dinero) {
            dinero -= cantidad; // Disminuyo saldo
            cout << "Has retirado $" << cantidad << ". Saldo actual: $" << dinero << "\n";
            agregarRegistro("Retiro: $" + to_string(cantidad)); // Registro movimiento
            registrarMovimientoDinero("Retiro", nombre, cantidad, dinero);
            guardarSaldo(nombre, dinero); // Guardo saldo actualizado
            return true; // Retiro exitoso
        } else {
            cout << "Retiro inválido o saldo insuficiente.\n";
            return false; // Retiro fallido
        }
    }

    // Método para mostrar el historial completo del jugador
    inline void mostrarHistorial() {
       // Abro el archivo que contiene todos los eventos de juegos registrados
    ifstream archivo("./documentos/juegos.txt");

    // Verifico si el archivo se abrió correctamente
    if (!archivo.is_open()) {
        // Si no se pudo abrir, informo al jugador y salgo de la función
        cout << "No se pudo abrir el historial de juegos.\n";
        return;
    }

    string linea;        // Aquí voy a guardar cada línea del archivo mientras lo leo
    bool hayHistorial = false; // Creo esta bandera para saber si encontré alguna línea del jugador

    clearConsole();
    // Muestro el encabezado para que se vea bonito y ordenado
    cout << "\n===============  Historial de partidas =============== \n";

    // Leo el archivo línea por línea usando getline
    while (getline(archivo, linea)) {
        // Verifico si la línea contiene el nombre del jugador
        if (linea.find("Jugador: " + nombre) != string::npos) {
            // Si la línea es del jugador, la muestro por pantalla
            cout << linea << "\n";
            hayHistorial = true; // Cambio la bandera para indicar que encontré historial
        }
    }

    // Cierro el archivo cuando termino de leerlo
    archivo.close();

    // Si no encontré ninguna línea del jugador, lo informo
    if (!hayHistorial) {
        cout << "No hay historial registrado para este jugador.\n";
    }

    cout << "\nPresiona Enter para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();

    // Muestro el pie del historial para cerrarlo visualmente
    cout << "=================================\n";
    }
};

#endif // JUGADOR_H
