#ifndef MULTIJUGADOR_H 
#define MULTIJUGADOR_H 

#include <iostream> // Incluyo para poder usar cin y cout
#include <cstdlib>  // Incluyo para funciones como rand y srand
#include <ctime>    // Incluyo para usar time y generar números aleatorios con srand
#include <algorithm> // Incluyo para usar funciones como swap y copy
#include <cctype>  // para isalpha
#include "utils.h" // Aquí incluyo el limpiarConsola

using namespace std; // Uso el espacio de nombres estándar para no escribir std:: en todo

const int MAX_CARTAS = 16; // Defino el número total de cartas que usaré en el juego de memoria
const int MAX_NUMEROS = 8; // Defino el número de elementos para el puzzle de números

// Defino una estructura para representar a cada jugador en los minijuegos
struct JugadorMinijuego {
    string nombre; // Aquí guardo el nombre del jugador
    int puntuacion = 0; // Inicializo su puntuación en 0
};

// Declaro las funciones que usaré más abajo en el mismo archivo
void menuMinijuegos(JugadorMinijuego& j1, JugadorMinijuego& j2);
void juegoMemoria(JugadorMinijuego& j1, JugadorMinijuego& j2);
void juegoEstrategia(JugadorMinijuego& j1, JugadorMinijuego& j2);
void puzzleNumeros(JugadorMinijuego& j1, JugadorMinijuego& j2);
void mostrarGanador(JugadorMinijuego& j1, JugadorMinijuego& j2);
void mezclarArreglo(int arreglo[], int tamano);
bool estaOrdenado(int arreglo[], int tamano);

// Implemento una función para mezclar los valores de un arreglo aleatoriamente
void mezclarArreglo(int arreglo[], int tamano) {
    for (int i = tamano - 1; i > 0; i--) {
        int j = rand() % (i + 1); // Elijo un índice aleatorio entre 0 y i
        swap(arreglo[i], arreglo[j]); // Intercambio los valores de las posiciones i y j
    }
}

// Implemento una función para verificar si un arreglo está ordenado de menor a mayor
bool estaOrdenado(int arreglo[], int tamano) {
    for (int i = 0; i < tamano - 1; i++) {
        if (arreglo[i] > arreglo[i + 1]) {
            return false; // Si encuentro un elemento mayor que el siguiente, el arreglo no está ordenado
        }
    }
    return true; // Si todo está bien, devuelvo true
}

// Aquí defino el menú de minijuegos donde los jugadores pueden elegir qué jugar
void menuMinijuegos(JugadorMinijuego& j1, JugadorMinijuego& j2) {
    int opcion;
    do {
        if (cin.fail()) {
        // Si la entrada no es un número, limpio el error y descarto la entrada inválida
        cin.clear(); // Limpia el estado de error
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora la línea entera
        opcion = 0; // Para que entre al default y muestre mensaje
    }
        limpiarConsola();
        // Muestro las opciones disponibles
        cout << "\n=== MENU DE MINIJUEGOS ===";
        cout << "\n1. Juego de Memoria";
        cout << "\n2. Juego de Estrategia";
        cout << "\n3. Puzzle de Números";
        cout << "\n4. Ver puntuaciones";
        cout << "\n5. Salir";
        cout << "\nSelecciona un juego: ";
        
        cin >> opcion; // Leo la opción que selecciona el jugador
        
        switch(opcion) {
            case 1:
                limpiarConsola();
                juegoMemoria(j1, j2); // Llamo al juego de memoria
                break;
            case 2:
                limpiarConsola();
                juegoEstrategia(j1, j2); // Llamo al juego de estrategia
                break;
            case 3: 
                limpiarConsola();
                puzzleNumeros(j1, j2); // Llamo al puzzle de números
                break;
            case 4:
                limpiarConsola();
                mostrarGanador(j1, j2); // Muestro quién va ganando
                cout << "\nPresiona ENTER para continuar...";
                cin.ignore();
                cin.get();  // Espera que el usuario presione ENTER
                break;
            case 5:
                cout << "Volviendo al menu principal...\n"; // Mensaje de despedida
                break;
            default:
                cout << "Opcion invalida. Intenta nuevamente.\n"; // Si no elige una opción válida
        }
    } while(opcion != 5); // Repetir mientras no elijan salir
}

// Aquí defino el juego de memoria donde deben emparejar cartas iguales
// Aquí defino el juego de memoria, pero ahora con menú para ver reglas antes de comenzar
void juegoMemoria(JugadorMinijuego& j1, JugadorMinijuego& j2) {
    int opcion; // Variable para guardar la opción del menú

    // Menú previo para explicar el juego si el jugador lo desea
    do {
        cout << "\n=== JUEGO DE MEMORIA ===";
        cout << "\n1. Ver reglas del juego";
        cout << "\n2. Empezar el juego";
        cout << "\nSelecciona una opción: ";
        cin >> opcion;

        // Validación de entrada inválida
        if (cin.fail() || (opcion != 1 && opcion != 2)) {
            cin.clear(); // Limpio error de entrada
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignoro basura
            cout << "Opción inválida. Intenta de nuevo.\n";
        } else if (opcion == 1) {
            limpiarConsola();
            // Si elige 1, le muestro las reglas
            cout << "\n=== REGLAS DEL JUEGO DE MEMORIA ===\n";
            cout << "1. Hay 16 cartas (8 parejas) ocultas.\n";
            cout << "2. Seleccionas dos cartas por turno (0-15).\n";
            cout << "3. Si son iguales, ganas 10 puntos.\n";
            cout << "4. Si fallás, pierdes el turno.\n";
            cout << "5. Gana el que tenga más puntos al final.\n";
            cout << "----------------------------------------\n";
        }
    } while (opcion != 2); // Repito hasta que elija empezar

    // Empieza la lógica real del juego
    int cartas[MAX_CARTAS] = {1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8}; // Las cartas
    bool reveladas[MAX_CARTAS] = {false}; // Todas ocultas al inicio
    mezclarArreglo(cartas, MAX_CARTAS); // Mezclo aleatoriamente
    int parejasEncontradas = 0; // Contador de parejas
    int turno = 0; // Comienzo con el jugador 1

    // Mientras no se encuentren las 8 parejas
    while(parejasEncontradas < 8) {
        JugadorMinijuego& jugadorActual = (turno == 0) ? j1 : j2; // Decido quién juega
        cout << "\nTurno de " << jugadorActual.nombre << endl;

        // Muestro el tablero
        cout << "Tablero:\n";
        for(int i = 0; i < MAX_CARTAS; i++) {
            if(reveladas[i])
                cout << cartas[i] << " ";
            else
                cout << "* ";
            if((i+1) % 4 == 0) cout << endl;
        }

        // Le pido al jugador dos posiciones
        int pos1, pos2;
        cout << "Selecciona dos cartas (0-15): ";
        cin >> pos1 >> pos2;

        // Verifico si la entrada fue válida o si eligió la misma carta
        if (cin.fail() || pos1 < 0 || pos1 >= MAX_CARTAS || pos2 < 0 || pos2 >= MAX_CARTAS || pos1 == pos2 || reveladas[pos1] || reveladas[pos2]) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Selección inválida. Pierdes tu turno.\n";
            turno = 1 - turno;
            continue;
        }

        // Revelo las cartas elegidas
        reveladas[pos1] = true;
        reveladas[pos2] = true;

        // Muestro lo que eligió
        cout << "Seleccionaste: " << cartas[pos1] << " y " << cartas[pos2] << endl;

        // Si acierta
        if(cartas[pos1] == cartas[pos2]) {
            cout << "¡Pareja encontrada! +10 puntos\n";
            jugadorActual.puntuacion += 10;
            parejasEncontradas++;
        } else {
            cout << "No es pareja. Se ocultan de nuevo.\n";
            reveladas[pos1] = false;
            reveladas[pos2] = false;
            turno = 1 - turno;
        }
    }

    // Cuando termina el juego
    cout << "\n¡Juego terminado!\n";
    mostrarGanador(j1, j2); // Muestro quién ganó
}


// Aquí defino el juego de estrategia donde los jugadores no deben pasarse de 21
void juegoEstrategia(JugadorMinijuego& j1, JugadorMinijuego& j2) {
    int opcion; // Variable para el menú

    // Submenú para mostrar reglas si lo desea el jugador
    do {
        cout << "\n=== JUEGO DE ESTRATEGIA ===";
        cout << "\n1. Ver reglas del juego";
        cout << "\n2. Empezar el juego";
        cout << "\nSelecciona una opción: ";
        cin >> opcion;

        // Valido la opción elegida
        if (cin.fail() || (opcion != 1 && opcion != 2)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Opción inválida. Intenta nuevamente.\n";
        } else if (opcion == 1) {
            // Si elige ver reglas
            cout << "\n=== REGLAS DEL JUEGO DE ESTRATEGIA ===\n";
            cout << "1. Comenzamos desde 0.\n";
            cout << "2. Cada jugador suma un número entre 1 y 5 en su turno.\n";
            cout << "3. El que haga que el total llegue a 21 pierde.\n";
            cout << "4. El otro jugador gana 15 puntos.\n";
            cout << "---------------------------------------\n";
        }
    } while (opcion != 2); // Repite hasta que elija jugar

    // Lógica principal del juego
    int total = 0; // Comienzo desde cero
    int turno = 0; // Empieza el jugador 1

    while(total < 21) {
        JugadorMinijuego& jugadorActual = (turno == 0) ? j1 : j2;
        int suma;

        cout << "\nTotal actual: " << total;
        cout << "\n" << jugadorActual.nombre << ", suma un número entre 1 y 5: ";
        cin >> suma;

        // Verifico si la suma es válida
        if (cin.fail() || suma < 1 || suma > 5) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Suma inválida. Debe ser entre 1 y 5.\n";
            continue;
        }

        total += suma; // Le sumo al total
        turno = 1 - turno; // Cambio de turno
    }

    // Como el que sumó el 21 pierde, el otro gana
    JugadorMinijuego& ganador = (turno == 0) ? j1 : j2;
    cout << "\n¡" << ganador.nombre << " gana 15 puntos por estrategia!\n";
    ganador.puntuacion += 15;

    mostrarGanador(j1, j2); // Muestro quién va ganando
}

// Aquí defino el puzzle de números donde tienen que ordenar del 1 al 8
void puzzleNumeros(JugadorMinijuego& j1, JugadorMinijuego& j2) {
    // Inicio la función para el puzzle de números con dos jugadores

    int opcion; // Guardo la opción que el jugador elija en el menú inicial

    // Muestro un pequeño menú para que el jugador vea reglas o empiece a jugar
    do {
        cout << "\n=== PUZZLE DE NUMEROS ===";
        cout << "\n1. Ver reglas del juego";
        cout << "\n2. Empezar el juego";
        cout << "\nSelecciona una opción: ";
        cin >> opcion; // Leo la opción que ingresa el jugador

        // Si la entrada es inválida o la opción no es ni 1 ni 2, aviso y vuelvo a pedir
        if (cin.fail() || (opcion != 1 && opcion != 2)) {
            cin.clear(); // Limpio el estado de error de cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignoro la entrada basura
            cout << "Opción inválida. Intenta de nuevo.\n"; // Mensaje de error
        } 
        // Si elige ver reglas, las muestro
        else if (opcion == 1) {
            cout << "\n=== REGLAS DEL PUZZLE DE NUMEROS ===\n";
            cout << "1. Se te mostrará una secuencia desordenada de números del 1 al 8.\n";
            cout << "2. Debes ordenarlos intercambiando dos posiciones por turno.\n";
            cout << "3. Las posiciones van de 0 a 7.\n";
            cout << "4. Gana el jugador con menos intentos.\n";
            cout << "5. Si hay empate, ambos ganan puntos.\n";
            cout << "6. Si pones una posición inválida, el intento no cuenta.\n";
            cout << "---------------------------------------\n";
        }
    } while (opcion != 2); // Sigo mostrando el menú hasta que el jugador elija comenzar

    // Ahora comienzo el juego en sí
    int numeros[MAX_NUMEROS] = {1,2,3,4,5,6,7,8}; // Creo el arreglo ordenado base
    mezclarArreglo(numeros, MAX_NUMEROS); // Mezclo los números para hacer el puzzle

    int intentosJ1 = 0, intentosJ2 = 0; // Inicializo los contadores de intentos

    // Turno del jugador 1
    cout << "\nTurno de " << j1.nombre << endl;
    int copiaJ1[MAX_NUMEROS]; // Creo una copia para que el jugador 1 juegue sin modificar el original
    copy(numeros, numeros + MAX_NUMEROS, copiaJ1); // Copio la secuencia mezclada

    // Mientras el arreglo no esté ordenado...
    while(!estaOrdenado(copiaJ1, MAX_NUMEROS)) {
        cout << "Secuencia actual: ";
        for(int i = 0; i < MAX_NUMEROS; i++) cout << copiaJ1[i] << " "; // Muestro la secuencia actual
        cout << endl;

        int pos1, pos2; // Variables para guardar las posiciones a intercambiar
        cout << "Ingresa dos posiciones para intercambiar (0-7): ";
        cin >> pos1 >> pos2; // Leo las posiciones

        // Valido que las posiciones sean válidas y que la entrada sea correcta
        if (cin.fail() || pos1 < 0 || pos1 >= MAX_NUMEROS || pos2 < 0 || pos2 >= MAX_NUMEROS) {
            cin.clear(); // Limpio error en la entrada
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignoro basura en el buffer
            cout << "Posiciones inválidas. Intenta nuevamente.\n"; // Mensaje de error
            continue; // No cuento intento y pido de nuevo
        }

        swap(copiaJ1[pos1], copiaJ1[pos2]); // Intercambio las posiciones
        intentosJ1++; // Aumento el contador de intentos para el jugador 1
    }

    // Turno del jugador 2
    cout << "\nTurno de " << j2.nombre << endl;
    int copiaJ2[MAX_NUMEROS]; // Creo la copia para el jugador 2
    copy(numeros, numeros + MAX_NUMEROS, copiaJ2); // Copio la secuencia mezclada para él

    // Mismo proceso para jugador 2
    while(!estaOrdenado(copiaJ2, MAX_NUMEROS)) {
        cout << "Secuencia actual: ";
        for(int i = 0; i < MAX_NUMEROS; i++) cout << copiaJ2[i] << " ";
        cout << endl;

        int pos1, pos2;
        cout << "Ingresa dos posiciones para intercambiar (0-7): ";
        cin >> pos1 >> pos2;

        if (cin.fail() || pos1 < 0 || pos1 >= MAX_NUMEROS || pos2 < 0 || pos2 >= MAX_NUMEROS) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Posiciones inválidas. Intenta nuevamente.\n";
            continue;
        }

        swap(copiaJ2[pos1], copiaJ2[pos2]);
        intentosJ2++;
    }

    // Comparo los intentos para definir el ganador o si hay empate
    if(intentosJ1 < intentosJ2) {
        cout << "\n¡" << j1.nombre << " gana con " << intentosJ1 << " intentos! +20 puntos\n";
        j1.puntuacion += 20; // Asigno puntos al ganador
    } else if(intentosJ2 < intentosJ1) {
        cout << "\n¡" << j2.nombre << " gana con " << intentosJ2 << " intentos! +20 puntos\n";
        j2.puntuacion += 20;
    } else {
        cout << "\n¡Empate! Ambos ganan 10 puntos\n";
        j1.puntuacion += 10;
        j2.puntuacion += 10;
    }

    mostrarGanador(j1, j2); // Muestro la tabla final de puntajes
}

// Esta función la uso para mostrar quién va ganando o si están empatados
void mostrarGanador(JugadorMinijuego& j1, JugadorMinijuego& j2) {
    // Comienzo mostrando un encabezado bonito
    cout << "\n=== PUNTUACIONES ===";

    // Muestro el nombre del jugador 1 junto con su puntuación actual
    cout << "\n" << j1.nombre << ": " << j1.puntuacion << " puntos";

    // Muestro el nombre del jugador 2 y su puntuación también
    cout << "\n" << j2.nombre << ": " << j2.puntuacion << " puntos\n";

    // Aquí comparo las puntuaciones para ver quién va ganando
    if(j1.puntuacion > j2.puntuacion) {
        // Si el jugador 1 tiene más puntos, lo anuncio como quien va ganando
        cout << "\n¡" << j1.nombre << " va ganando!\n";
    } 
    else if(j2.puntuacion > j1.puntuacion) {
        // Si el jugador 2 tiene más puntos, entonces él va ganando
        cout << "\n¡" << j2.nombre << " va ganando!\n";
    } 
    else {
        // Si ambos tienen los mismos puntos, anuncio que están empatados
        cout << "\n¡Están empatados!\n";
    }
}


// Función para validar que el nombre solo tenga letras
bool esNombreValido(const string& nombre) {
    if (nombre.empty()) return false; // No puede estar vacío
    for (char c : nombre) {
        if (!isalpha(c)) return false; // Si hay algo que no sea letra, inválido
    }
    return true;
}

// Ejemplo de uso en modoMultijugador()
void modoMultijugador() {
    string nombre1, nombre2;
    limpiarConsola();
    cout << "\n=== MODO MULTIJUGADOR (Minijuegos) ===";

    do {
        cout << "\nJugador 1, ingresa tu nombre: ";
        cin >> nombre1;
        if (!esNombreValido(nombre1)) {
            cout << "Nombre inválido. Usa solo letras sin espacios ni números.\n";
        }
    } while (!esNombreValido(nombre1));

    do {
        cout << "Jugador 2, ingresa tu nombre: ";
        cin >> nombre2;
        if (!esNombreValido(nombre2)) {
            cout << "Nombre inválido. Usa solo letras sin espacios ni números.\n";
        }
    } while (!esNombreValido(nombre2));

    JugadorMinijuego j1 = {nombre1};
    JugadorMinijuego j2 = {nombre2};

    srand(time(nullptr)); // Inicializo la semilla aleatoria
    menuMinijuegos(j1, j2); // Llamo al menú con los dos jugadores

    cout << "\n=== RESULTADO FINAL ===";
    mostrarGanador(j1, j2); // Muestro la puntuación final
}

#endif // MULTIJUGADOR_H