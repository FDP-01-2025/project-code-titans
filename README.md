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


# Aplicación de los temas vistos en clases

- Variables y tipos de datos
- Estructuras condicionales (if, else, switch)
- Ciclos (for, while, do while)
- Funciones
- Estructuras de datos
- Manejo de archivos
- Manejo de errores
- Interfaz por consola


## Equipo

- **Nombre del equipo:** Code Titans 

### Integrantes del equipo

1. Fernando Alonso Moreno Flores 00000125 

2. Marcos Noe Vásquez Guardado 00114825

3. Camila Alessandra Menjívar Martínez  00095825

4. Lizbeth Sofia Menjívar Castillo  00074525

5. Carlos Eduardo Martínez Velasquez 00207024
## Instrucciones de Ejecución

1. Clona este repositorio en tu máquina local:
   ```bash
   git clone https://github.com/FDP-01-2025/project-code-titans.git

2. Para poder ejecutar el programa en tu maquina local atravez de la terminal podras ejecutarlo asi:

para la creacion del ejecutable
g++ main.cpp -o casino

para ejecutar el ejecutable
./casino.exe