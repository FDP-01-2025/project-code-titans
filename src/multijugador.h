#ifndef MULTIJUGADOR_H 
#define MULTIJUGADOR_H 

#include <iostream> // Incluyo para poder usar cin y cout
#include <cstdlib>  // Incluyo para funciones como rand y srand
#include <ctime>    // Incluyo para usar time y generar números aleatorios con srand
#include <algorithm> // Incluyo para usar funciones como swap y copy
#include <cctype>  // para isalpha

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
                juegoMemoria(j1, j2); // Llamo al juego de memoria
                break;
            case 2:
                juegoEstrategia(j1, j2); // Llamo al juego de estrategia
                break;
            case 3:
                puzzleNumeros(j1, j2); // Llamo al puzzle de números
                break;
            case 4:
                mostrarGanador(j1, j2); // Muestro quién va ganando
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
void juegoMemoria(JugadorMinijuego& j1, JugadorMinijuego& j2) {
    // Inicio el juego de memoria con dos jugadores pasados por referencia
    cout << "\n=== JUEGO DE MEMORIA ===";
    cout << "\nEncuentra todas las parejas para ganar puntos!\n";
    
    // Creo un arreglo con pares de números del 1 al 8
    int cartas[MAX_CARTAS] = {1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8};
    // Creo un arreglo booleano para saber qué cartas están reveladas, inicio todas en false
    bool reveladas[MAX_CARTAS] = {false};
    // Mezclo las cartas para que estén en orden aleatorio
    mezclarArreglo(cartas, MAX_CARTAS);

    // Inicializo el contador de parejas encontradas en 0
    int parejasEncontradas = 0;
    // Inicio el turno en 0 para jugador 1
    int turno = 0;

    // El juego continúa hasta que se encuentren las 8 parejas
    while(parejasEncontradas < 8) {
        // Defino la referencia al jugador actual según el turno
        JugadorMinijuego& jugadorActual = (turno == 0) ? j1 : j2;
        cout << "\nTurno de " << jugadorActual.nombre << endl;

        // Muestro el tablero con las cartas reveladas o con asteriscos
        cout << "Tablero:\n";
        for(int i = 0; i < MAX_CARTAS; i++) {
            if(reveladas[i])
                cout << cartas[i] << " "; // Muestro número si la carta está revelada
            else
                cout << "* "; // Sino muestro asterisco

            // Hago salto de línea cada 4 cartas para formato visual
            if((i+1) % 4 == 0) cout << endl;
        }

        // Pido al usuario que seleccione dos cartas
        int pos1, pos2;
        cout << "Selecciona dos cartas (0-15): ";
        cin >> pos1 >> pos2;

        // Si la entrada es inválida, limpio error y pierdes el turno
        if (cin.fail()) {
            cin.clear(); // Limpio estado de error
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignoro basura del buffer
            cout << "Entrada inválida. Pierdes tu turno.\n";
            turno = 1 - turno; // Cambio turno al otro jugador
            continue; // Sigo con la siguiente iteración
        }

        // Verifico que las posiciones estén dentro del rango, no sean iguales, ni estén ya reveladas
        if(pos1 < 0 || pos1 >= MAX_CARTAS || pos2 < 0 || pos2 >= MAX_CARTAS || pos1 == pos2 || reveladas[pos1] || reveladas[pos2]) {
            cout << "Seleccion invalida (posiciones fuera de rango, iguales o ya reveladas). Pierdes tu turno.\n";
            turno = 1 - turno; // Cambio turno porque fallo en la selección
            continue;
        }

        // Revelo las cartas seleccionadas en el tablero
        reveladas[pos1] = true;
        reveladas[pos2] = true;

        // Muestro qué cartas fueron seleccionadas
        cout << "Seleccionaste: " << cartas[pos1] << " y " << cartas[pos2] << endl;

        // Compruebo si las dos cartas forman pareja
        if(cartas[pos1] == cartas[pos2]) {
            cout << "¡Encontraste una pareja! +10 puntos\n";
            jugadorActual.puntuacion += 10; // Sumo puntos al jugador actual
            parejasEncontradas++; // Aumento el contador de parejas encontradas
        } else {
            cout << "No es una pareja. Turno del siguiente jugador.\n";
            // Si no fue pareja, oculto nuevamente las cartas
            reveladas[pos1] = false;
            reveladas[pos2] = false;
            turno = 1 - turno; // Cambio el turno al siguiente jugador
        }
    }

    // Cuando se encuentren todas las parejas, termino el juego
    cout << "\n¡Juego terminado!\n";
    mostrarGanador(j1, j2); // Muestro quién ganó según la puntuación
}

// Aquí defino el juego de estrategia donde los jugadores no deben pasarse de 21
void juegoEstrategia(JugadorMinijuego& j1, JugadorMinijuego& j2) {
    // Inicio el juego de estrategia con dos jugadores pasados por referencia
    cout << "\n=== JUEGO DE ESTRATEGIA ===";
    cout << "\nEl ultimo en sumar menos de 21 gana!\n";

    int total = 0;  // Inicializo el total acumulado en 0
    int turno = 0;  // Inicio el turno en 0 (jugador 1)

    // Mientras el total acumulado sea menor a 21, el juego sigue
    while(total < 21) {
        // Determino quién es el jugador actual según el turno
        JugadorMinijuego& jugadorActual = (turno == 0) ? j1 : j2;
        int suma;  // Variable para guardar la suma que el jugador introducirá

        // Muestro el total acumulado hasta ahora
        cout << "\nTotal acumulado: " << total << endl;
        // Le pido al jugador que ingrese una suma entre 1 y 5
        cout << jugadorActual.nombre << ", suma entre 1 y 5: ";
        cin >> suma;

        // Si la entrada no es válida o está fuera del rango, muestro error y pido otra vez
        if (cin.fail() || suma < 1 || suma > 5) {
            cin.clear(); // Limpio el estado de error de cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignoro el resto de la línea
            cout << "Suma invalida. Debe ser entre 1 y 5.\n";
            continue; // Vuelvo a pedir el número sin cambiar turno
        }

        total += suma; // Sumo la cantidad al total acumulado
        turno = 1 - turno; // Cambio el turno al otro jugador
    }

    // Cuando el total es 21 o más, el jugador que no acaba de sumar es el ganador
    JugadorMinijuego& ganador = (turno == 0) ? j1 : j2;
    cout << "\n¡" << ganador.nombre << " gana 15 puntos por estrategia!\n";
    ganador.puntuacion += 15; // Le sumo 15 puntos al ganador

    mostrarGanador(j1, j2); // Muestro la puntuación actual de ambos jugadores
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

// Función para mostrar quién va ganando
void mostrarGanador(JugadorMinijuego& j1, JugadorMinijuego& j2) {
    cout << "\n=== PUNTUACIONES ===";
    cout << "\n" << j1.nombre << ": " << j1.puntuacion << " puntos";
    cout << "\n" << j2.nombre << ": " << j2.puntuacion << " puntos\n";

    if(j1.puntuacion > j2.puntuacion) {
        cout << "\n¡" << j1.nombre << " va ganando!\n";
    } else if(j2.puntuacion > j1.puntuacion) {
        cout << "\n¡" << j2.nombre << " va ganando!\n";
    } else {
        cout << "\n¡Estan empatados!\n";
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