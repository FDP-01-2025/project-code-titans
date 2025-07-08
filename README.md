# Proyecto de Code Titans C++ - casino virtual

# Nombre del juego
Casino Virtual: Consola Edición

# Temática y ambientación
Temática: El juego se centra en la experiencia de un casino, ofreciendo una variedad de juegos de azar clásicos. La temática busca replicar la emoción y la atmósfera de un casino real, pero desde la comodidad de una consola de texto.

Ambientación:
Visual: La ambientación es puramente textual y ASCII. Se utilizan caracteres especiales y códigos ANSI para simular gráficos, colores y animaciones en la consola. Esto incluye representaciones ASCII de cartas, dados, ruletas y barras de progreso.

Sonora: No hay elementos sonoros, la inmersión se logra a través de la descripción textual y las animaciones visuales en la consola.

Narrativa: El juego no tiene una narrativa profunda. El jugador asume el rol de un cliente del casino que busca probar su suerte en diferentes juegos, gestionar su dinero y ver sus estadísticas. Hay mensajes de bienvenida dinámicos según la hora del día y frases motivacionales o de ánimo durante el juego.

Interfaz: La interfaz es limpia y basada en menús de texto, con opciones numeradas para la navegación. Se utilizan colores para resaltar información importante (ganancias, pérdidas, advertencias) y para embellecer la presentación de los juegos.

# Mecánica principal
estión de Dinero: El núcleo del juego gira en torno a la gestión del saldo del jugador. Los jugadores pueden depositar y retirar dinero, y sus apuestas en los diferentes juegos afectan directamente su balance. Si el saldo llega a cero, no pueden seguir jugando.

Juegos de Azar: El juego ofrece una selección de juegos de casino populares, cada uno con sus propias reglas y mecánicas específicas:

Ruleta: Apuestas a números exactos, colores (rojo/negro) o par/impar. Incluye una animación ASCII de la ruleta girando.

Blackjack: El objetivo es sumar 21 o acercarse lo más posible sin pasarse, compitiendo contra la casa. Permite pedir cartas, doblar la apuesta y, en algunos casos, dividir.

Máquina Tragamonedas (Slot Machine): Gira carretes con símbolos y gana si los símbolos coinciden en una línea. Ofrece diferentes niveles de dificultad (fácil, medio, difícil) que varían el número de líneas y las ganancias/apuestas.

Craps (Dados): Un juego de dados con reglas específicas para la primera tirada (Come Out Roll) y las tiradas posteriores para establecer un "punto". También incluye animación de dados.

Hi-Lo: Un juego de cartas simple donde el jugador adivina si la siguiente carta será más alta o más baja que la actual, con la posibilidad de duplicar la apuesta en cada acierto.

Registro y Autenticación de Usuario: Los jugadores deben registrarse o iniciar sesión para acceder al casino. El sistema gestiona nombres de usuario, contraseñas, códigos de recuperación y datos personales (fecha de nacimiento, género, DUI). Incluye un sistema de bloqueo de cuenta por intentos fallidos de inicio de sesión.

Estadísticas y Historial: El juego registra el desempeño del jugador (partidas jugadas, ganadas, perdidas, empatadas) y su historial de transacciones y partidas, que puede ser consultado en cualquier momento. Las estadísticas se muestran tanto en formato de texto como en gráficos ASCII.

Multijugador Local (Mini-Juegos): Ofrece un modo multijugador local con mini-juegos competitivos que no involucran dinero del casino, sino un sistema de puntuación interno para determinar un ganador entre dos jugadores.

# Idea general de la jugabilidad
La jugabilidad de "Casino Virtual: Consola Edición" se centra en una experiencia de usuario interactiva y basada en texto.

Inicio: Al iniciar el programa, el jugador es recibido con una pantalla de carga animada y un saludo dinámico según la hora del día.

Menú Principal (Modo de Juego): El jugador elige entre jugar en modo individual (gestionando su cuenta de casino) o en modo multijugador local (mini-juegos).

Gestión de Cuenta (Modo Individual):
Login/Registro: Si elige el modo individual, el jugador debe iniciar sesión o registrarse. El registro implica proporcionar datos personales y crear una contraseña, con validaciones de edad, formato de DUI y unicidad de usuario. El sistema de login incluye medidas de seguridad como el bloqueo temporal de cuenta por intentos fallidos.

Menú del Casino: Una vez autenticado, el jugador accede al menú principal del casino, donde puede:
Depositar o retirar dinero de su cuenta.
Seleccionar cualquiera de los juegos de casino disponibles (Ruleta, Blackjack, Slot Machine, Craps, Hi-Lo).

Consultar su historial de transacciones y partidas.
Ver sus estadísticas de juego (ganadas, perdidas, empatadas) en formato de texto o gráfico.
Salir del casino.

Desarrollo de los Juegos:
Cada juego tiene su propia interfaz de texto y sus reglas se explican al jugador.
Las interacciones son a través de entradas de texto (apuestas, decisiones de juego como "pedir carta" o "plantarse").
Se utilizan animaciones ASCII y cambios de color para simular la acción del juego (dados rodando, ruleta girando, cartas mostrándose).
El resultado de cada partida afecta el saldo del jugador y se registra en su historial y estadísticas.
El juego valida las apuestas para asegurar que el jugador tenga suficiente dinero y que la apuesta esté dentro de los límites establecidos.

Modo Multijugador Local:
Dos jugadores ingresan sus nombres.
Acceden a un menú de mini-juegos (Juego de Memoria, Juego de Estrategia, Rompecabezas de Números).
Cada mini-juego tiene sus propias reglas y un sistema de puntuación.
Al final de cada mini-juego, se muestra la puntuación actual de ambos jugadores.
Al salir del modo multijugador, se muestra el resultado final y el ganador general.
Persistencia de Datos: El saldo, el historial y las estadísticas del jugador se guardan en archivos de texto, lo que permite que la informac

#  Proyecto de Code Titans C++ - Casino Virtual

El proyecto "Casino Virtual: Consola Edición" es una implementación robusta de un casino en C++ utilizando la consola como interfaz principal.

Modularidad: El código está altamente modularizado, con cada juego y funcionalidad principal (gestión de usuarios, datos, utilidades) encapsulada en sus propios archivos de cabecera (.h) y, presumiblemente, archivos de implementación (.cpp) asociados. Esto facilita la lectura, el mantenimiento y la escalabilidad del proyecto.

Uso de Estructuras y Clases: Se utilizan estructuras como Player para encapsular los datos y métodos relacionados con el jugador (saldo, estadísticas, historial, depósitos, retiros). También se observa el uso de MiniGamePlayer para el modo multijugador.

Manejo de Archivos: El proyecto hace un uso extensivo de fstream para la persistencia de datos. Se guardan y cargan balances, historiales de juego, estadísticas y datos de usuario en archivos de texto (.txt). Esto incluye la creación de archivos específicos por jugador (ej. balance_nombre.txt, history_nombre.txt).

Validación de Entradas: Se implementan validaciones rigurosas para las entradas del usuario (apuestas, opciones de menú, datos de registro como fechas de nacimiento y DUI), utilizando cin.fail(), cin.ignore(), numeric_limits y funciones personalizadas (toLower, trim, normalize, isNameValid, isOfLegalAge, validDUI).

Interfaz de Usuario en Consola: Se aprovechan las capacidades de la consola para crear una experiencia visual atractiva dentro de sus limitaciones. Esto incluye:
Colores ANSI: Uso de códigos de escape ANSI para cambiar el color del texto y el fondo, mejorando la legibilidad y el atractivo visual.

Gráficos ASCII: Representaciones detalladas de elementos del juego (cartas, dados, ruleta, barras de estadísticas) utilizando caracteres ASCII.

Animaciones: Implementación de animaciones simples pero efectivas (ruleta girando, dados rodando, barras de carga) mediante la limpieza de la consola y pausas (waitMs).
Funcionalidades Avanzadas:
Sistema de Bloqueo de Cuenta: Implementación de un sistema de seguridad para bloquear cuentas temporalmente después de múltiples intentos de inicio de sesión fallidos, registrando los intentos y el tiempo del último intento.

Recuperación de Contraseña: Un sistema para recuperar contraseñas utilizando un código de recuperación generado automáticamente durante el registro.

Gestión de Estadísticas: Seguimiento detallado de las estadísticas de juego del jugador y su visualización en diferentes formatos.

Generación de Números Aleatorios: Uso de rand() y srand(time(nullptr)) para asegurar la aleatoriedad en los juegos de azar.

Portabilidad: El uso de directivas #ifdef _WIN32 permite adaptar funciones específicas del sistema operativo (como Sleep o system("cls")) para que el código sea compatible tanto con Windows como con sistemas Unix-like (Linux/macOS).


# Aplicación de los temas vistos (uno por uno con ejemplos)


## **1. Variables y Tipos de Datos**

### **Descripción:**
Se utilizan diversos tipos de datos para almacenar información esencial del juego, como el dinero del jugador, los valores de las cartas, las opciones de menú, etc.

### **Ejemplo:**
En la estructura `Player`, se definen variables para el nombre (`std::string`), el dinero (`int`) y las estadísticas de juego (`int`).
```cpp
// En MultipleFiles/player.h
struct Player
{
    std::string name;       // Player's name (string)
    int money = 0;          // Current money (integer)
    int gamesPlayed = 0;    // Games played (integer)
    // ...
};

// En MultipleFiles/blackjackGame.h
inline int generateCard()
{
    return rand() % 13 + 1; // Returns an integer card value
}
```

---

## **2. Estructuras Condicionales (if, else, switch)**
### **Descripción:**
Las estructuras condicionales son cruciales para la lógica del juego, permitiendo tomar decisiones basadas en el estado del juego, las entradas del usuario o los resultados aleatorios.

### **Ejemplo:**
En Blackjack, se verifica si el jugador se ha pasado de 21.
```cpp
// En MultipleFiles/blackjackGame.h
bool playHandFunction(Player &player, int values[], std::string suits[], int &numCards, int currentBet)
{
    int score = calculateScore(values, numCards);
    if (score > 21) // Condición para determinar si el jugador se "pasa"
    {
        std::cout << "\n\033[31mYou exceeded 21. You lost this hand.\033[0m\n";
        // ...
        return true;
    }
    // ...
    return false;
}
```
En el juego Hi-Lo, se usa `switch` para manejar las opciones del menú principal.
```cpp
// En MultipleFiles/hilo.h
inline void playHilo(Player &player)
{
    int option;
    // ...
    switch (option) // Evalúa la opción elegida por el usuario
    {
    case 1:
        // ... (mostrar explicación)
        break;
    case 2:
        // ... (iniciar juego)
        break;
    // ...
    }
}
```

---

## **3. Ciclos (for, while, do while)**
### **Descripción:**
Los ciclos son fundamentales para repetir acciones, como animaciones, turnos de juego, validación de entradas o iterar sobre colecciones de datos.

### **Ejemplo:**
En la Ruleta, un ciclo `for` anima el giro de la rueda.
```cpp
// En MultipleFiles/rouletteGame.h
for (int step = 0; step <= totalSteps; step++) // Ciclo para la animación de la ruleta
{
    clearConsole();
    printCanvas(highlighted);
    highlighted = (highlighted + 1) % NUMBERS;
    waitMs(70); // Pausa para el efecto visual
}
```
Un ciclo `while` se usa para validar que el usuario ingrese una apuesta válida.
```cpp
// En MultipleFiles/blackjackGame.h
int bet;
// ...
while (true) // Ciclo para validar la entrada de la apuesta
{
    std::cin >> bet;
    if (std::cin.fail() || bet < 10 || bet > 500 || bet > player.money)
    {
        // ... (manejo de error y reintento)
        continue;
    }
    break; // Sale del ciclo si la apuesta es válida
}
```
El menú principal del casino usa un `do-while` para seguir mostrando opciones hasta que el usuario decida salir.
```cpp
// En MultipleFiles/mainMenu.h
inline void start(const std::string &username)
{
    // ...
    int option;
    bool playing = true;
    do // El menú se repite hasta que 'playing' sea falso
    {
        showMenu();
        std::cin >> option;
        // ... (manejo de opciones)
        if (option == 10) { // Opción para salir
            playing = false;
        }
    } while (playing);
}
```

---

## **4. Funciones**
### **Descripción:**
El código está altamente modularizado en funciones, lo que permite organizar la lógica, reutilizar código y mejorar la legibilidad.

### **Ejemplo:**
La función `playBlackjack` encapsula toda la lógica de una partida de Blackjack.
```cpp
// En MultipleFiles/blackjackGame.h
inline void playBlackjack(Player &player)
{
    // ... (lógica completa del juego)
}
```
Funciones auxiliares como `clearConsole` o `toLower` son ejemplos de reutilización.
```cpp
// En MultipleFiles/utils.h
inline void clearConsole() { /* ... */ } // Limpia la pantalla
inline std::string toLower(const std::string &s) { /* ... */ } // Convierte a minúsculas
```

---

## **5. Estructuras de Datos**
### **Descripción:**
Además de los tipos de datos primitivos, se utilizan estructuras definidas por el usuario para organizar datos complejos y relacionados.

### **Ejemplo:**
La estructura `Player` (ya mencionada en "Variables y Tipos de Datos") es el ejemplo principal. Otro es `Position` para las coordenadas.
```cpp
// En MultipleFiles/gameConstants.h
struct Position
{
    int x, y; // Coordenadas X e Y
};

extern Position positions[NUMBERS]; // Array global de posiciones para la ruleta
```
La estructura `Record` se usa para almacenar descripciones de eventos en el historial del jugador.
```cpp
// En MultipleFiles/gameConstants.h
struct Record
{
    std::string description; // Text that describes the action or event
};
```

---

## **6. Manejo de Archivos**
### **Descripción:**
La persistencia de datos es fundamental para que el estado del juego (saldo, estadísticas, usuarios) se mantenga entre sesiones. Se utilizan `std::ifstream` para leer y `std::ofstream` para escribir.

### **Ejemplo:**
La función `saveBalance` guarda el saldo de un jugador en un archivo de texto.
```cpp
// En MultipleFiles/playerData.h
inline void saveBalance(const std::string &player, int money)
{
    std::ofstream file("./documents/balance_" + player + ".txt"); // Abre el archivo para escritura
    if (file.is_open())
    {
        file << money << "\n"; // Escribe el saldo
    }
}
```
La función `loadBalance` lee el saldo de un jugador desde su archivo.
```cpp
// En MultipleFiles/playerData.h
inline int loadBalance(const std::string &player)
{
    std::ifstream file("./documents/balance_" + player + ".txt"); // Abre el archivo para lectura
    if (!file.is_open())
        return 0; // Si no existe, retorna 0
    int savedMoney;
    file >> savedMoney; // Lee el saldo
    return savedMoney;
}
```
La función `deleteHistory` muestra un manejo más avanzado, leyendo de un archivo, escribiendo en uno temporal y luego reemplazando el original.
```cpp
// En MultipleFiles/player.h
inline void deleteHistory()
{
    std::ifstream inFile("./documents/games.txt");
    std::ofstream outFile("./documents/temp.txt");
    // ... (lógica para copiar líneas que no pertenecen al jugador)
    inFile.close();
    outFile.close();
    remove("./documents/games.txt"); // Elimina el archivo original
    rename("./documents/temp.txt", "./documents/games.txt"); // Renombra el temporal
}
```

---

## **7. Manejo de Errores**
### **Descripción:**
El juego implementa validaciones robustas para las entradas del usuario y el manejo de situaciones inesperadas (como archivos no encontrados o entradas inválidas), informando al usuario y permitiendo reintentos.

### **Ejemplo:**
Cuando el usuario ingresa una opción de menú inválida, se limpia el buffer de entrada y se muestra un mensaje de error.
```cpp
// En MultipleFiles/mainMenu.h
int option;
std::cin >> option;
if (std::cin.fail()) // Verifica si la entrada no fue un número
{
    std::cin.clear(); // Limpia el flag de error
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Descarta la entrada inválida
    std::cout << "Invalid input.\n";
    std::cout << "Press Enter to continue...";
    std::cin.get();
    // ...
}
```
Al intentar cargar estadísticas, se verifica si el archivo existe.
```cpp
// En MultipleFiles/asciiGraphics.h
inline void showStatistics(const std::string &playerName) {
    int played, won, lost, tied;
    if (!loadStatistics(playerName, played, won, lost, tied)) { // Verifica si la carga fue exitosa
        std::cout << "\033[31m[!] No statistics found for " << playerName << "\033[0m\n";
        return;
    }
    // ...
}
```

---

## **8. Interfaz por Consola**
### **Descripción:**
El proyecto se desarrolla íntegramente en la consola, utilizando caracteres ASCII y códigos de escape ANSI para crear una interfaz de usuario interactiva y visualmente atractiva.

### **Ejemplo:**
La función `showDateTime` muestra un encabezado decorativo con la fecha y hora actuales, utilizando colores ANSI.
```cpp
// En MultipleFiles/date_time.h
inline void showDateTime()
{
    // ...
    setColor(31); // Establece color rojo
    std::cout << "+======================================+\n";
    std::cout << "|                                      |\n";
    std::cout << "║    ";
    setColor(34); // Establece color azul
    std::cout << "WELCOME TO THE VIRTUAL CASINO";
    setColor(31);
    std::cout << "     ║\n";
    // ...
    resetColor(); // Restablece el color
}
```
La función `showDiceASCII` dibuja los dados usando caracteres ASCII.
```cpp
// En MultipleFiles/crapsGame.h
inline void showDiceASCII(int d1, int d2)
{
    const char *diceFaces[6][5] = {
        {"+-------+", "|       |", "|   o   |", "|       |", "+-------+"}, // Cara 1
        // ... (otras caras)
    };
    for (int i = 0; i < 5; ++i)
    {
        std::cout << diceFaces[d1 - 1][i] << "   " << diceFaces[d2 - 1][i] << "\n";
    }
}
```

## **Consideraciones Técnicas del Desarrollo**  

### **1. Arquitectura y Modularidad**
- **Estructura de Archivos:** El proyecto está organizado en múltiples archivos de cabecera (`.h`), cada uno encapsulando una funcionalidad específica (ej., `blackjackGame.h` para la lógica del Blackjack, `player.h` para la estructura del jugador, `utils.h` para funciones de utilidad).
  ```
  ├── MultipleFiles/
  │   ├── asciiGraphics.h      # Gráficos ASCII y estadísticas
  │   ├── blackjackGame.h      # Lógica del juego Blackjack
  │   ├── crapsGame.h          # Lógica del juego Craps
  │   ├── date_time.h          # Funciones de fecha y hora
  │   ├── gameConstants.h      # Constantes y estructuras globales
  │   ├── hilo.h               # Lógica del juego Hi-Lo
  │   ├── loadingScreen.h      # Pantalla de carga
  │   ├── loginAttempts.h      # Gestión de intentos de login
  │   ├── mainMenu.h           # Menú principal y navegación
  │   ├── multiplayer.h        # Modo multijugador y mini-juegos
  │   ├── player.h             # Estructura y métodos del jugador
  │   ├── playerData.h         # Funciones de persistencia de datos del jugador
  │   ├── rouletteGame.h       # Lógica del juego Ruleta
  │   ├── slotMachineGame.h    # Lógica del juego Máquina Tragamonedas
  │   ├── start.h              # Función de inicio del juego
  │   └── userManager.h        # Gestión de usuarios (registro, login, etc.)
  ```
- **Motivación:** Esta separación facilita la lectura, el mantenimiento, la depuración y la escalabilidad del código, permitiendo que diferentes partes del proyecto se desarrollen de forma independiente.

---

### **2. Manejo de Datos y Persistencia**
- **Almacenamiento:** Los datos del juego (información de usuarios, saldos, estadísticas, historiales de juego y movimientos de dinero) se almacenan en **archivos de texto plano (`.txt`)** dentro de una carpeta `documents/`.
- **Formato de Archivos:**
    - **Usuarios:** `users.txt` almacena nombre, contraseña, código de recuperación, fecha de nacimiento, género y DUI.
    - **Balances:** `balance_nombreJugador.txt` guarda el saldo actual de cada jugador.
    - **Estadísticas:** `statistics_nombreJugador.txt` registra partidas jugadas, ganadas, perdidas y empatadas.
    - **Historial General:** `games.txt` registra todas las partidas jugadas por todos los usuarios.
    - **Historial Personal:** `history_nombreJugador.txt` guarda el historial detallado de cada jugador.
    - **Movimientos de Dinero:** `movements.txt` registra depósitos y retiros.
    - **Intentos de Login:** `login_attempts.txt` almacena los intentos fallidos para el bloqueo de cuentas.
- **Manejo de Archivos:** Se utilizan las clases `std::ifstream` (para lectura) y `std::ofstream` (para escritura), a menudo en modo de adición (`std::ios::app`) para registrar nuevos eventos sin sobrescribir. Para actualizaciones o eliminaciones (ej., borrar historial, actualizar usuarios), se emplea la técnica de escribir en un archivo temporal y luego reemplazar el original (`remove()` y `rename()`).

---

### **3. Interfaz de Consola y Experiencia de Usuario**
- **Gráficos ASCII:** Se utilizan caracteres ASCII para dibujar elementos visuales como cartas (Blackjack, Hi-Lo), dados (Craps), la ruleta, y barras de estadísticas.
- **Colores ANSI:** Se emplean códigos de escape ANSI (`\033[...m`) para aplicar colores al texto y al fondo, mejorando la legibilidad, resaltando información importante (ganancias en verde, pérdidas en rojo) y embelleciendo la interfaz.
- **Animaciones:** Se simulan animaciones (ej., ruleta girando, dados rodando, barra de carga) mediante la combinación de:
    - **Limpieza de Consola:** `clearConsole()` (adaptado para Windows `cls` y Unix `clear`).
    - **Pausas:** `waitMs()` (adaptado para Windows `Sleep()` y Unix `usleep()`).
    - **Actualización Rápida:** Redibujado constante de elementos en bucles.
- **Mensajes Dinámicos:** Saludos personalizados según la hora del día (`Good morning`, `Good afternoon`, `Good evening`) y frases motivacionales o de ánimo en juegos como la Máquina Tragamonedas.

---

### **4. Lógica de Juegos y Aleatoriedad**
- **Implementación de Reglas:** Cada juego implementa sus reglas específicas (ej., cálculo de puntuación en Blackjack con Ases flexibles, reglas de "punto" en Craps, pagos en Ruleta).
- **Generación de Aleatoriedad:** Se utiliza `rand()` para la generación de números pseudoaleatorios. La semilla se inicializa con `srand(time(nullptr))` al inicio del programa para asegurar una secuencia diferente de números aleatorios en cada ejecución.

---

### **5. Gestión de Usuarios y Seguridad Básica**
- **Registro:** Los usuarios deben proporcionar un nombre de usuario, contraseña, fecha de nacimiento (validación de mayoría de edad), género y DUI (validación de formato y unicidad). Se genera un código de recuperación aleatorio.
- **Login:** Se verifica el nombre de usuario y la contraseña.
- **Bloqueo de Cuenta:** Tras un número configurable de intentos fallidos (`MAX_ATTEMPTS = 3`), la cuenta se bloquea temporalmente por un periodo (`LOCK_TIME = 300` segundos). Los intentos se registran en `login_attempts.txt`.
- **Recuperación de Contraseña:** Permite al usuario ver su contraseña actual o establecer una nueva si proporciona el nombre de usuario y el código de recuperación correcto.
- **Eliminación de Usuario:** Permite eliminar un usuario y sus registros asociados si se proporciona el nombre de usuario y el código de recuperación.

---

### **6. Manejo de Errores y Validación de Entradas**
- **Validación de Entrada:** Se realizan validaciones exhaustivas para las entradas del usuario (ej., apuestas dentro de límites, opciones de menú válidas, formatos de fecha y DUI correctos).
- **Manejo de `std::cin`:** Se utiliza `std::cin.fail()`, `std::cin.clear()`, y `std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n')` para limpiar el buffer de entrada y manejar correctamente las entradas no numéricas o incorrectas, evitando bucles infinitos o comportamientos inesperados.
- **Mensajes al Usuario:** Se proporcionan mensajes claros y específicos sobre errores de entrada o condiciones de juego (ej., "No tienes suficiente dinero", "Entrada inválida").

---

### **7. Portabilidad (Básica)**
- **Directivas de Preprocesador:** El uso de `#ifdef _WIN32` permite que el código se adapte a diferentes sistemas operativos (Windows vs. Unix-like como Linux/macOS) para funciones específicas como limpiar la consola (`system("cls")` vs `system("clear")` o secuencias ANSI) y pausas (`Sleep()` vs `usleep()`). Esto mejora la compatibilidad del ejecutable en diferentes entornos.

### Imágenes o mockups del juego

int main()
{

  /*                       LOGO DEL JUEGO
                           __________
                     _____|          |_____
                    |     |    /\    |     |
                    |  ---|   /  \   |\    |
                  ------- |   \  /   ---------
                /   ---   \    \/   | *       |
               |  /     \  |        |    *    |
               |  \     /  |--------|       * |
                \   ---   /          ---------
                  -------


*/

  // Menus en terminal

  // MENU BLACKJACK

  cout << endl;
  cout << "* - * - * - * - * - * - * - * - *. . . . . . . . . . . . . . " << endl;
  cout << "|                                                          . " << endl;
  cout << "*                    -PLAY BLACKJACK-                      . " << endl;
  cout << "|                                                          . " << endl;
  cout << "*    Blackjack is a card game where the objective is to    . " << endl;
  cout << "|    reach 21 without going over. You win if you get       . " << endl;
  cout << ".    closer to 21 than the dealer.                         | " << endl;
  cout << ".                                                          * " << endl;
  cout << ".                                                          | " << endl;
  cout << ".    MENU (M)                                 PLAY (P)     * " << endl;
  cout << ".                                                          | " << endl;
  cout << ". . . . . . . . . . . . . .* - * - * - * - * - * - * - * - * " << endl;
  cout << " " << endl;
  cout << " " << endl;

  // MENU BLACKJACK elegir dificultad

  cout << endl;
  cout << "* - * - * - * - * - * - * - * - *. . . . . . . . . . . . . . " << endl;
  cout << "|                                                          . " << endl;
  cout << "*                       -BLACKJACK-                        . " << endl;
  cout << "|                                                          . " << endl;
  cout << "*                  Choose the difficulty:                  . " << endl;
  cout << "|                                                          . " << endl;
  cout << ".   (1) EASY:      -Play only against the dealer.-         | " << endl;
  cout << ".   (2) MEDIUM:    -The dealer draws cards up to 17,       *" << endl;
  cout << ".                  “doubling down” is allowed.-            |" << endl;
  cout << ".   (3) DIFFICULT: -You add split and side bets,           * " << endl;
  cout << ".                  The dealer plays more aggressively.-    | " << endl;
  cout << ".                                                          * " << endl;
  cout << ".     BACK (B)                                             |" << endl;
  cout << ". . . . . . . . . . . . . .* - * - * - * - * - * - * - * - *" << endl;
  cout << endl;

  // MENU ROULETTE

  cout << endl;
  cout << "* - * - * - * - * - * - * - * - *. . . . . . . . . . . . . . " << endl;
  cout << "|                                                          . " << endl;
  cout << "*                     -PLAY ROULETTE-                      .  " << endl;
  cout << "|                                                          . " << endl;
  cout << "*    Roulette is a game of chance in which the player      . " << endl;
  cout << "|    bets where a ball will land on a numbered spinning    . " << endl;
  cout << ".    wheel.                                                | " << endl;
  cout << ".                                                          * " << endl;
  cout << ".                                                          | " << endl;
  cout << ".    MENU (M)                                 PLAY (P)     * " << endl;
  cout << ".                                                          | " << endl;
  cout << ". . . . . . . . . . . . . .* - * - * - * - * - * - * - * - * " << endl;
  cout << " " << endl;
  cout << " " << endl;

  // MENU RULETA elegir dificultad

  cout << endl;
  cout << "* - * - * - * - * - * - * - * - *. . . . . . . . . . . . . . " << endl;
  cout << "|                                                          . " << endl;
  cout << "*                       -ROULETTE-                         .  " << endl;
  cout << "|                                                          . " << endl;
  cout << "*                  Choose the difficulty:                  . " << endl;
  cout << "|                                                          . " << endl;
  cout << ".   (1) EASY:      You only bet on color (red or black).   | " << endl;
  cout << ".   (2) MEDIUM:    Exact number bets (from 0 to 36).       * " << endl;
  cout << ".   (3) DIFFICULT: Bet: even/odd + color + number.         | " << endl;
  cout << ".                                                          * " << endl;
  cout << ".     BACK (B)                                             | " << endl;
  cout << ". . . . . . . . . . . . . .* - * - * - * - * - * - * - * - * " << endl;
  cout << endl;

  // MENU TRAGAMONEDAS

  cout << endl;
  cout << "* - * - * - * - * - * - * - * - *. . . . . . . . . . . . . . " << endl;
  cout << "|                                                          . " << endl;
  cout << "*                   -PLAY SLOT MACHINE-                    . " << endl;
  cout << "|                                                          . " << endl;
  cout << "*    A slot machine is a game where a series of random     . " << endl;
  cout << "|    symbols are displayed on each spin. If all the        . " << endl;
  cout << ".    symbols on a line match, you win.                     | " << endl;
  cout << ".                                                          * " << endl;
  cout << ".                                                          | " << endl;
  cout << ".    MENU (M)                                 PLAY (P)     * " << endl;
  cout << ".                                                          | " << endl;
  cout << ". . . . . . . . . . . . . .* - * - * - * - * - * - * - * - * " << endl;
  cout << " " << endl;
  cout << " " << endl;

  // MENU TRAGAMONEDAS elegir dificultad

  cout << endl;
  cout << "* - * - * - * - * - * - * - * - *. . . . . . . . . . . . . . " << endl;
  cout << "|                                                          . " << endl;
  cout << "*                      -SLOT MACHINE-                      . " << endl;
  cout << "|                                                          . " << endl;
  cout << "*                  Choose the difficulty:                  . " << endl;
  cout << "|                                                          . " << endl;
  cout << ".   (1) EASY:      A single line of symbols                | " << endl;
  cout << ".   (2) MEDIUM:    3 paylines                              * " << endl;
  cout << ".   (3) DIFFICULT: 5 paylines + special symbols            | " << endl;
  cout << ".                                                          * " << endl;
  cout << ".     BACK (B)                                             | " << endl;
  cout << ". . . . . . . . . . . . . .* - * - * - * - * - * - * - * - * " << endl;
  cout << endl;

  // MENU DADOS

  cout << endl;
  cout << "* - * - * - * - * - * - * - * - *. . . . . . . . . . . . . . " << endl;
  cout << "|                                                          . " << endl;
  cout << "*                       -PLAY CRAPS-                       . " << endl;
  cout << "|                                                          . " << endl;
  cout << "*    Craps is a game in which you bet on the outcome of    . " << endl;
  cout << "|    two rolls of dice. If you rolls a 7 or 11, you win.   . " << endl;
  cout << ".    If you roll a 2, 3, or 12, you lose.                  |  " << endl;
  cout << ".                                                          * " << endl;
  cout << ".                                                          | " << endl;
  cout << ".    MENU (M)                                 PLAY (P)     * " << endl;
  cout << ".                                                          | " << endl;
  cout << ". . . . . . . . . . . . . .* - * - * - * - * - * - * - * - * " << endl;
  cout << " " << endl;
  cout << " " << endl;

  // MENU DADOS elegir dificultad

  cout << "* - * - * - * - * - * - * - * - *. . . . . . . . . . . . . . " << endl;
  cout << "|                                                          . " << endl;
  cout << "*                         -CRAPS-                          .  " << endl;
  cout << "|                                                          . " << endl;
  cout << "*                  Choose the difficulty:                  . " << endl;
  cout << "|                                                          . " << endl;
  cout << ".   (1) EASY:    -Simple dice roll: 7 or 11 win,           | " << endl;
  cout << ".                 2, 3, 12 lose.-                          *" << endl;
  cout << ".   (2) MEDIUM:  -“point” is established must be repeated  |" << endl;
  cout << ".                 until a victory or defeat is achieved.-  * " << endl;
  cout << ".   (3) DIFFICULT: -More bets: (doubles, combinations).-   | " << endl;
  cout << ".                                                          * " << endl;
  cout << ".     BACK (B)                                             |" << endl;
  cout << ". . . . . . . . . . . . . .* - * - * - * - * - * - * - * - *" << endl;
  cout << endl;

  /*
                         EXPLICAR JUEGO MENUS

      * - * - * - * - * - * - * - * - *. . . . . . . . . . . . . .
      |                                                          .
      *                    -PLAY BLACKJACK-                      .
      |                                                          .
      *    Blackjack is a card game where the objective is to    .
      |    reach 21 without going over. You win if you get       .
      .    closer to 21 than the dealer.                         |
      .                                                          *
      .                                                          |
      .    MENU (M)                                 PLAY (P)     *
      .                                                          |
      . . . . . . . . . . . . . .* - * - * - * - * - * - * - * - *


      * - * - * - * - * - * - * - * - *. . . . . . . . . . . . . .
      |                                                          .
      *                     -PLAY ROULETTE-                      .
      |                                                          .
      *    Roulette is a game of chance in which the player      .
      |    bets where a ball will land on a numbered spinning    .
      .    wheel.                                                |
      .                                                          *
      .                                                          |
      .    MENU (M)                                 PLAY (P)     *
      .                                                          |
      . . . . . . . . . . . . . .* - * - * - * - * - * - * - * - *


      * - * - * - * - * - * - * - * - *. . . . . . . . . . . . . .
      |                                                          .
      *                   -PLAY SLOT MACHINE-                    .
      |                                                          .
      *    A slot machine is a game where a series of random     .
      |    symbols are displayed on each spin. If all the        .
      .    symbols on a line match, you win.                     |
      .                                                          *
      .                                                          |
      .    MENU (M)                                 PLAY (P)     *
      .                                                          |
      . . . . . . . . . . . . . .* - * - * - * - * - * - * - * - *

      * - * - * - * - * - * - * - * - *. . . . . . . . . . . . . .
      |                                                          .
      *                       -PLAY CRAPS-                       .
      |                                                          .
      *    Craps is a game in which you bet on the outcome of    .
      |    two rolls of dice. If you rolls a 7 or 11, you win.   .
      .    If they roll a 2, 3, or 12, they lose.                |
      .                                                          *
      .                                                          |
      .    MENU (M)                                 PLAY (P)     *
      .                                                          |
      . . . . . . . . . . . . . .* - * - * - * - * - * - * - * - *


                       ELEJIR DIFICULTAD MENUS

      * - * - * - * - * - * - * - * - *. . . . . . . . . . . . . .
      |                                                          .
      *                      -SLOT MACHINE-                      .
      |                                                          .
      *                  Choose the difficulty:                  .
      |                                                          .
      .   (1) EASY:   A single line of symbols                   |
      .   (2) MEDIUM:  3 paylines                                *
      .   (3) DIFFICULT: 5 paylines + special symbols            |
      .                                                          *
      .     BACK (B)                                             |
      . . . . . . . . . . . . . .* - * - * - * - * - * - * - * - *

      * - * - * - * - * - * - * - * - *. . . . . . . . . . . . . .
      |                                                          .
      *                      -BLACKJACK-                         .
      |                                                          .
      *                  Choose the difficulty:                  .
      |                                                          .
      .   (1) EASY:      -Play only against the dealer.-         |
      .   (2) MEDIUM:    -The dealer draws cards up to 17,       *
      .                  “doubling down” is allowed.-            |
      .   (3) DIFFICULT: -You add split and side bets,           *
      .                  The dealer plays more aggressively.-    |
      .                                                          *
      .     BACK (B)                                             |
      . . . . . . . . . . . . . .* - * - * - * - * - * - * - * - *


      * - * - * - * - * - * - * - * - *. . . . . . . . . . . . . .
      |                                                          .
      *                       -ROULETTE-                         .
      |                                                          .
      *                  Choose the difficulty:                  .
      |                                                          .
      .   (1) EASY:      You only bet on color (red or black).   |
      .   (2) MEDIUM:  Exact number bets (from 0 to 36).         *
      .   (3) DIFFICULT: Bet: even/odd + color + number.         |
      .                                                          *
      .     BACK (B)                                             |
      . . . . . . . . . . . . . .* - * - * - * - * - * - * - * - *

      * - * - * - * - * - * - * - * - *. . . . . . . . . . . . . .
      |                                                          .
      *                         -CRAPS-                          .
      |                                                          .
      *                  Choose the difficulty:                  .
      |                                                          .
      .   (1) EASY:    -Simple dice roll: 7 or 11 win,           |
      .                 2, 3, 12 lose.-                          *
      .   (2) MEDIUM:  -“point” is established must be repeated  |
      .                 until a victory or defeat is achieved.-  *
      .   (3) DIFFICULT: -More bets: (doubles, combinations).-   |
      .                                                          *
      .     BACK (B)                                             |
      . . . . . . . . . . . . . .* - * - * - * - * - * - * - * - *


  */

  return 0;
}

## Equipo

Equipo "Code Titans" - 

##Roles y Responsabilidades

Fernando Alonso Moreno Flores (00000125)

Rol: Líder Técnico y Arquitecto de Software / Desarrollador Backend
Responsabilidades Clave:

Liderazgo Técnico: Definir la arquitectura del software y supervisar la implementación de las mejores prácticas de desarrollo.

Desarrollo Backend: Implementar la lógica de los juegos (Blackjack, Ruleta, Craps) y desarrollar el sistema de persistencia de datos.

Integración: Asegurar que la lógica del juego se integre correctamente con la interfaz de usuario.

Mentoría: Proporcionar orientación y apoyo a los miembros del equipo, ayudando a resolver problemas técnicos.

Marcos Noe Vásquez Guardado (00114825)

Rol: Analista
Responsabilidades Clave:

Recopilar y analizar los requisitos del proyecto y las necesidades del usuario.

Diseñar y documentar las especificaciones funcionales y técnicas.

Colaborar con el equipo de desarrollo para asegurar que se cumplan los requisitos.

Realizar pruebas de aceptación y validar que el producto final cumpla con las expectativas.

Camila Alessandra Menjívar Martínez (00095825)

Rol: Especialista en Calidad y Pruebas
Responsabilidades Clave:

Diseñar y ejecutar casos de prueba para asegurar la calidad del software.

Realizar depuración y validación de entradas.

Documentar los resultados de las pruebas y sugerir mejoras.

Lizbeth Sofia Menjívar Castillo (00074525)

Rol: Desarrolladora Frontend de Consola
Responsabilidades Clave:

Diseñar la interfaz utilizando gráficos ASCII/ANSI.

Implementar animaciones y mejorar la experiencia del usuario.

Crear gráficos estadísticos para mostrar el rendimiento del jugador.

Carlos Eduardo Martínez Velasquez (00207024)

Rol: Gestor de Proyecto y Documentación
Responsabilidades Clave:

Planificar sprints y gestionar el cronograma del proyecto.

Mantener la documentación técnica actualizada.

Comunicar avances y necesidades del equipo a los stakeholders.

## Instrucciones de Ejecución

1. Clona este repositorio en tu máquina local:
   ```bash
   git clone https://github.com/FDP-01-2025/project-code-titans.git

2. Para poder ejecutar el programa en tu maquina local atravez de la terminal podras ejecutarlo asi:

para la creacion del ejecutable
g++ main.cpp -o casino

para ejecutar el ejecutable
./casino.exe
