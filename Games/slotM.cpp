#include <iostream>
#include <cstring>     //library to handle string type text
#include <cstdlib>     //To use rand()
#include <ctime>       // To use time() as a random seed
using namespace std;

// Function to display the game instructions
void showSlot()
{

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
    cout << endl;
    //It is indicated that you must enter "M" to return to the menu or "P" to play
}

// Function to display the slot game difficulty menu
void showSlotmenu()
{

    cout << endl;
    cout << "* - * - * - * - * - * - * - * - *. . . . . . . . . . . . . . " << endl;
    cout << "|                                                          . " << endl;
    cout << "*                      -SLOT MACHINE-                      . " << endl;
    cout << "|                                                          . " << endl;
    cout << "*                  Choose the difficulty:                  . " << endl;
    cout << "|                                                          . " << endl;
    cout << ".   (E) EASY:      3 lines (Bet: $100, Win: $300)          | " << endl;
    cout << ".   (M) MEDIUM:    4 lines (Bet: $200, Win: $800)          * " << endl;
    cout << ".   (H) HARD:      5 lines (Bet: $100, Win: $1500)         | " << endl;
    cout << ".                                                          * " << endl;
    cout << ".     BACK (B)                                             | " << endl;
    cout << ". . . . . . . . . . . . . .* - * - * - * - * - * - * - * - * " << endl;
    cout << endl;
//It indicates that you must enter "B" to return to the previous menu
//"E" for easy mode, "M" for medium mode, "H" for hard mode

}

//GENERAL FUNCTIONS (For all games)

//function to change the text color
void setColor(int colorCode) {
    cout << "\033[" << colorCode << "m"; 
}
//function to return to white color
void resetColor() {
    cout << "\033[0m";
}

void losePhrases (){
    //function to display a random motivational phrase when the player loses
    string lSentence_0 = "The next move could change everything…"; //phrase 1
    string lSentence_1 = "The reels don't move by themselves! Dare!";//phrase 2
    string lSentence_2 = "The reels are heating up… don’t give up!"; //phrase 3
    string LSentence_3 = "Almost there! The next turn could be the winner."; //phrase 4
    int randomLphase = rand()%4; //variable to choose a random number from 0 to 3
    //conditions for each number
    switch(randomLphase){
        case 0:                  //if it is 0, sentence 1 will be displayed
        cout<<endl;
        cout<<lSentence_0<<endl;
        break;

        case 1:                  //if it is 1, sentence 2 will be displayed
        cout<<endl;
        cout<<lSentence_1<<endl;
        break;

        case 2:                  //if it is 2, sentence 3 will be displayed
        cout<<endl;
        cout<<lSentence_2<<endl;
        break;

        case 3:                  //if it is 3, sentence 4 will be displayed
        cout<<endl;
        cout<<LSentence_3<<endl;
        break;

        default:                 //If there is any error, another sentence will be displayed
        cout<<endl;
        cout<<"Luck turns around… and yours is about to return."<<endl;
        break;
    }
}
   

//                                           EASY MODE
void emptySlotsE(){
    //Show empty slots to the player
    cout<<endl;
    cout<<"* - * - * - * - * - *. . . . . . . "<<endl;
    cout<<"|                                ."<<endl;
    cout<<"*          Try your luck!        ."<<endl;
    cout<<"|                                ."<<endl;
    cout<<"*    -----------------------     ."<<endl;
    cout<<".   |       |       |       |    |"<< endl;
    cout<<".   |   -   |   -   |   -   |    *" <<endl;
    cout<<".   |       |       |       |    |"<< endl;
    cout<<".    -----------------------     *"<<endl;
    cout<<".   | Pull the lever (!)|        |"<<endl;
    cout<<". . . . . . .* - * - * - * - * - *"<<endl;
    cout<<endl;
    //the player is instructed to press "!" to generate the random symbols
}

char randomSymbolE (){
    //Function to generate random symbols
    char symbol [3]= {'@','$','7'}; //array with 3 symbols
    int randomP = rand()%3; //variable to choose a number from 0 to 2
    return symbol[randomP]; //the function will return the symbol at position x (randomP)
}

void symbolColorE(char slots[3]){
    //Function to assign a different color to each symbol
    for(int i=0;i<3;i++){ //read the array of symbols
        switch(slots[i]){ //read array position
            case '$': //assign to '$' blue color
            setColor(34);
            cout<< slots[i];
            resetColor(); 
            cout<<"   | "<< "  ";
            break;
            case '7': //assign yellow color to '7'
            setColor(33);
            cout<< slots[i];
            resetColor(); 
            cout<<"   | "<< "  ";
            break;
            case '@': //assign magenta color to '@'
            setColor(35);
            cout<< slots[i];
            resetColor(); 
            cout<<"   | "<< "  ";
            break;
            default:
            setColor(36); //in case of any error, cyan color will be assigned
            cout<< slots[i];
            resetColor(); 
            cout<<"   | "<< "  ";
            break;
        }
    }
}

void finalSlotsE (char slots[3]) {
   //Show final slots to the player
    cout<<"* - * - * - * - * - *. . . . . . . "<<endl;
    cout<<"|                                ."<<endl;
    cout<<"*            RESULTS!            ."<<endl;
    cout<<"|                                ."<<endl;
    cout<<"*    -----------------------     ."<<endl;
    cout<<".   |       |       |       |    *"<< endl;
    //Random symbols will be displayed on this line
    cout<<".   |   ";
    symbolColorE(slots); //Call the function to display the generated symbols with their respective colors
    cout<<" |" <<endl;
    cout<<".   |       |       |       |    *"<< endl;
    cout<<".    -----------------------     |"<<endl;
    cout<<". . . . . . .* - * - * - * - * - *"<<endl;
    cout<<endl;

}

bool jackpotE(char slots[3]){
    //function to validate if the 3 symbols are equal
    return(slots[0]==slots[1] && slots[1]==slots[2]);
    //if all three are equal = true
}


//Main game easy
void easyMode(){

    char symbols[3]; //arrangement to save the generated random symbols
    int playerLose; //Validate if the player won or lost
    string anotherRound; //save player response

    while (true){ // while infinite for the player to decide to continue playing
        srand(time(0)); //randomness
        
         for(int i=4;i>0;i--){ //for loop that repeats each shot 4 times

            while(true){ //while infinite to show the player the remaining shots

                string nextSpin; //variable for the player to start each game
                cout<<endl;
                cout<<"You have "<< i <<" remaining chances!"<<endl; //the player is shown the remaining opportunities
                cout<<"(P) to continue..."<<endl;//the player is instructed to press "P" to continue.
                getline(cin,nextSpin);  //the entered character is entered and read
                if(nextSpin=="P"|| nextSpin=="p"){
                    break; //If "P" or "p" is entered, the while loop ends and the game continues.
                }else{
                    cout<<endl;
                    setColor(31); //red
                    cout<<"Please enter a valid option (P), try again."<<endl; //if not, an error message is sent 
                    resetColor();
                          //the loop repeats until the user enters "P"
                }

            }
        
            while(true){

                string pull;
                emptySlotsE(); //The function Show empty slots to the player is called
                getline(cin,pull); //the player must enter "!" and the entered character is read
                if(pull=="!"){
                    //If "!" is entered the game continues.
                    for(int i=0;i<3;i++){            //loop through the empty array
                        symbols[i]= randomSymbolE(); //save each random symbol obtained
                    }
                    finalSlotsE(symbols); //The function Show final slots to the player is called
                
                    if(jackpotE(symbols)){ //calls the function to check if all symbols are equal
                        //If true, the player wins
                        setColor(32); //green 
                        cout<<"            * JACKPOT!! *   "<<endl;
                        resetColor();
                        cout<<endl;
                        cout<<" Congratulations!! you have earned: $300"<<endl; //muestra dinero obtenido por el jugador
                        cout<<endl;
                        i=0; //i takes the value 0 to end the initial for loop
                        playerLose=0; //variable takes the value of 0 to verify that the player has won
                        break; //the game ends when i=0
                    }else{
                        //If it is false the player loss
                        setColor(36); //color cian
                        cout<<"            KEEP TRYING "<<endl;
                        resetColor();
                        losePhrases();
                        playerLose=1;//variable takes the value of 0 to verify that the player has lost
                        break; //the player will continue with his remaining rolls
                    }
                
                }else{
                    cout<<endl;
                    setColor(31); //red
                    cout<<"Please enter a valid option (!), try again."<<endl;
                    resetColor();
                    //if no error message is sent
                    //the loop repeats until the user enters "!"
                }
            }
        }

        if(playerLose==1){ //if variable is equal to 1 the player lost
            cout<<endl;
            cout<<"   You'll be lucky next time."<<endl; //motivational message
            cout<<"-$100"<<endl; //amount the player lost
            cout<<endl;
        }

        while(true){ //infinite while to validate that a valid character was entered
            cout<<"\nDo you want to play another round?"<<endl;
            cout<<"     YES (Y).        NO(N)"<<endl;
            getline(cin,anotherRound); //player enters his choice and his answer is read

            if(anotherRound=="Y"||anotherRound=="y"){
                cout<<endl;
                setColor(32); //green color
                cout<<"GOOD LUCK!!"<<endl; //if "Y" or "y" (yes) is entered the loop ends
                resetColor();
                anotherRound="";
                break;
            }else if(anotherRound=="N"||anotherRound=="n"){
                cout<<endl;
                cout<<"Return to menu..."<<endl; //if "N" or "n" is entered (no) the loop ends
                break;
            }else{
                cout<<endl;
                setColor(31); //red
                cout<<"Please enter a valid option (Y) or (N), try again."<<endl; 
                resetColor();
                //if no error message is sent and the loop repeats
            }

        }

        if(anotherRound=="N"||anotherRound=="n"){ //validate if the player chose yes or no
            break; //if the user entered "N" or "n" (no) the function ends
        }

    }

}
//                                            MEDIUM MODE

void emptySlotsM(){
    //Show empty slots to the player
    cout<<endl;
    cout<<"* - * - * - * - * - . . . . . . . . . . ."<<endl;
    cout<<"|                                       ."<<endl;
    cout<<"*             Try your luck!            ."<<endl;
    cout<<"|                                       ."<<endl;
    cout<<"*    -------------------------------    ."<<endl;
    cout<<".   |       |       |       |       |   ."<< endl;
    cout<<".   |   -   |   -   |   -   |   -   |   *" <<endl;
    cout<<".   |       |       |       |       |   |"<< endl;
    cout<<"*    -------------------------------    *"<<endl;
    cout<<".    | Pull the lever (!)|              |"<<endl;
    cout<<". . . . . . . . . . . . * - * - * - * - *"<<endl;
    cout<<endl;
    //the player is instructed to press "!" to generate the random symbols
}

char randomSymbolM (){
    //Function to generate random symbols
    char symbol [3]= {'$','7','0'}; //array with 3 symbols
    int randomP = rand()%3; //variable to choose a number from 0 to 2
    return symbol[randomP]; //the function will return a random symbol
}

void symbolColorM(char slots[4]){
    //Function to assign a different color to each symbol
    for(int i=0;i<4;i++){ //read the array of symbols
        switch(slots[i]){ //read array position
            case '$': //assign to '$' blue color
            setColor(34);
            cout<< slots[i];
            resetColor(); 
            cout<<"   | "<< "  ";
            break;
            case '7': //assign yellow color to '7'
            setColor(33);
            cout<< slots[i];
            resetColor(); 
            cout<<"   | "<< "  ";
            break;
            case '@': //assign magenta color to '0'
            setColor(35);
            cout<< slots[i];
            resetColor(); 
            cout<<"   | "<< "  ";
            break;
            default:
            setColor(36); //in case of any error, cyan color will be assigned
            cout<< slots[i];
            resetColor(); 
            cout<<"   | "<< "  ";
            break;
        }
    }
}

void finalSlotsM (char slots[4]) {
    //Show final slots to the player
    cout<<endl;
    cout<<"* - * - * - * - * - . . . . . . . . . . ."<<endl;
    cout<<"|                                       ."<<endl;
    cout<<"*                RESULTS!               ."<<endl;
    cout<<"|                                       ."<<endl;
    cout<<"*    -------------------------------    ."<<endl;
    cout<<".   |       |       |       |       |   ."<< endl;
    //Random symbols will be displayed on this line
    cout<<".   |   ";
    symbolColorM(slots); //Call the function to display the generated symbols with their respective colors
    cout<<"*" <<endl;
    cout<<".   |       |       |       |       |   |"<< endl;
    cout<<"*    -------------------------------    *"<<endl;
    cout<<".    | Pull the lever (!)|              |"<<endl;
    cout<<". . . . . . . . . . . . * - * - * - * - *"<<endl;
    cout<<endl;
}

//function to validate if the 3 symbols are equal
bool jackpotM(char slots[4]){
    return(slots[0]==slots[1] && slots[1]==slots[2] && slots[2]==slots[3]);
    //if all three are equal = true
}

//Main game medium
void mediumMode(){

    char symbols[4]; //empty arrangement to save random symbols
    
    int playerLose; //Validate if the player won or lost
    string anotherRound; //save player response
    while (true){ // while infinite for the player to decide to continue playing
        srand(time(0)); //randomness
        
         for(int i=8;i>0;i--){ //for loop that repeats each shot 8 times

            while(true){ //while infinite to show the player the remaining shots

                string nextSpin; //variable for the player to start each game
                cout<<endl;
                cout<<"You have "<< i <<" remaining chances!"<<endl; //the player is shown the remaining opportunities
                cout<<"(P) to continue..."<<endl; //the player is instructed to press "P" to continue.
                getline(cin,nextSpin);  //the entered character is entered and read
                if(nextSpin=="P"|| nextSpin=="p"){
                    break; //If "P" or "p" is entered, the while loop ends and the game continues.
                }else{
                    cout<<endl;
                    setColor(31); //red
                    cout<<"Please enter a valid option (P), try again."<<endl; //si no se envia mensaje de error 
                    resetColor();
                    //the loop repeats until the user enters "P" 
                }
            }
        
            while(true){

                string pull;
                emptySlotsM(); //The function Show empty slots to the player is called
                getline(cin,pull); //the player must enter "!" and the entered character is read
    
                if(pull=="!"){
                    //If "!" is entered the game continues.
                    for(int i=0;i<4;i++){            //locate the array
                        symbols[i]= randomSymbolE(); //save each random symbol obtained
                    }
                    finalSlotsE(symbols); //The function Show final slots to the player is called
                
                    if(jackpotE(symbols)){ //calls the function to check if all symbols are equal
                        //If true, the player wins
                        setColor(32); //green color
                        cout<<"            * JACKPOT!! *   "<<endl;
                        resetColor();
                        cout<<endl;
                        cout<<" Congratulations!! you have earned: $800"<<endl; //shows money earned by the player
                        cout<<endl;
                        i=0; //i takes the value 0 to end the initial for loop
                        playerLose=0; //variable takes the value of 0 to verify that the player has won
                        break; //the game ends when i=0
                    }else{
                        //If false the player lost
                        setColor(36); //color cian
                        cout<<"            KEEP TRYING "<<endl;
                        resetColor();
                        losePhrases();
                        playerLose=1; //variable takes the value of 0 to verify that the player has lost
                        break; //the player will continue with his remaining rolls
                    }
                
                }else{
                    cout<<endl;
                    setColor(31); //color rojo
                    cout<<"Please enter a valid option (!), try again."<<endl;
                    resetColor();
                    //si no se envia mensaje de error 
                    //el bucle se repite hasta que el usuario ingrese "!" 
                }
            }     
        }

        if(playerLose==1){
            cout<<endl;
            cout<<"   You'll be lucky next time."<<endl;
            cout<<"-$200"<<endl;
            cout<<endl;
        }

        while(true){ //while infinito para validar que se ingreso un caracter valido
            cout<<"\nDo you want to play another round?"<<endl;
            cout<<"     YES (Y).        NO(N)"<<endl;
            getline(cin,anotherRound); //jugador ingresa su opccion y se lee su respuesta

            if(anotherRound=="Y"||anotherRound=="y"){
                cout<<endl;
                setColor(32); //color verde
                cout<<"GOOD LUCK!!"<<endl; //si se ingresa "Y" o "y" (yes) el bucle termina
                resetColor();
                anotherRound="";
                break;
            }else if(anotherRound=="N"||anotherRound=="n"){
                cout<<endl;
                cout<<"Return to menu..."<<endl; //si se ingresa "N" o "n" (no) el bucle termina
                break;
            }else{
                cout<<endl;
                setColor(31); //color rojo
                cout<<"Please enter a valid option (Y) or (N), try again."<<endl; 
                resetColor();
                //si no se envia mensaje de error y el bucle se repite
            }
        }

        if(anotherRound=="N"||anotherRound=="n"){ //validar si el juegador eligio si o no
            break; //si el usuario ingreso "N" o "n" (no) la funcion termina
        }
    }
}

//                                           HARD MODE

void emptySlotsH(){
    //Mostrar slots vacios al jugador
    cout<<endl;
    cout<<"* - * - * - * - * - * - * . . . . . . . . . . . ."<<endl;
    cout<<"|                                               ."<<endl;
    cout<<"*                 Try your luck!                ."<<endl;
    cout<<"|                                               ."<<endl;
    cout<<"*    ---------------------------------------    ."<<endl;
    cout<<".   |       |       |       |       |       |   ."<< endl;
    cout<<".   |   -   |   -   |   -   |   -   |   -   |   *" <<endl;
    cout<<".   |       |       |       |       |       |   |"<< endl;
    cout<<".    ---------------------------------------    *"<<endl;
    cout<<".    | Pull the lever (!)|                      |"<<endl;
    cout<<". . . . . . . . . . . . * - * - * - * - * - * - *"<<endl;
    cout<<endl;
    //se le indica al jugador que debe de presionar "!" para generar los simbolos aleatorios
}

char randomSymbolH (){
    //Funcion para generar simbolos aleatorios
    char symbol [3]= {'$','7','@'}; //arreglo con 4 simbolos
    int randomP = rand()%3; //variable para elegir un numero entre 0 y 2
    return symbol[randomP]; //la funcion retornara un simbolo random
}

void symbolColorH(char slots[5]){
    for(int i=0;i<5;i++){ //leer el arreglo de simbolos
        switch(slots[i]){ //leer posisicion del arreglo
            case '$': //asignar a '$' color azul
            setColor(34);
            cout<< slots[i];
            resetColor(); 
            cout<<"   | "<< "  ";
            break;
            case '7': //asignar a '7' color amarillo
            setColor(33);
            cout<< slots[i];
            resetColor(); 
            cout<<"   | "<< "  ";
            break;
            case '@': //asignar a '0' color magenta
            setColor(35);
            cout<< slots[i];
            resetColor(); 
            cout<<"   | "<< "  ";
            break;
            default:
            setColor(36); //ante cualquier error se asignara color cian
            cout<< slots[i];
            resetColor(); 
            cout<<"   | "<< "  ";
            break;

        }
    }
}

void finalSlotsH (char slots[5]){
    //Funcion para Mostrar slots finales al jugador

    //funcion para asignar un color diferente a cada simbolo
    
    cout<<endl;
    cout<<"* - * - * - * - * - * - * . . . . . . . . . . . ."<<endl;
    cout<<"|                                               ."<<endl;
    cout<<"*                    RESULTS!                   ."<<endl;
    cout<<"|                                               ."<<endl;
    cout<<"*    ---------------------------------------    ."<<endl;
    cout<<".   |       |       |       |       |       |   ."<< endl;
    //En esta linea se mostraran los simbolos aleatorios
    cout<<".   |   ";
    symbolColorH(slots);
    cout<<"." <<endl;
    cout<<".   |       |       |       |       |       |   |"<< endl;
    cout<<".    ---------------------------------------    *"<<endl;
    cout<<".    | Pull the lever (!)|                      |"<<endl;
    cout<<". . . . . . . . . . . . * - * - * - * - * - * - *"<<endl;
    cout<<endl;

}

bool jackpotH(char slots[5]){
    //funcion para validar si los 3 simbolos son iguales
    return(slots[0]==slots[1] && slots[1]==slots[2] && slots[2]==slots[3]&& slots[3]==slots[4]);
    //si los tres son iguales = true
}

//Main game hard
void hardMode(){

    char symbols[3]; //arreglo para guardar los simbolos aletorios
    
    int playerLose; //Validar si el jugador gano o perdio
    string anotherRound; //guardar respuesta del jugador

    while (true){ // while infinito para que el jugador decida seguir jugando

        srand(time(0)); //aleatoriedad
        
         for(int i=15;i>0;i--){ //bucle for que repite 15 veces cada tiro

            while(true){ //while infinito para mostrar al jugador los tiros restantes 

                string nextSpin; //variable para que el jugador inicie cada juego
                cout<<endl;
                cout<<"You have "<< i <<" remaining chances!"<<endl; //se le muestran al jugador las oportunidades restantes
                cout<<"(P) to continue..."<<endl; //se le indica al jugador debe de presionar "P" para continuar.
                getline(cin,nextSpin);  //se ingresa y se lee el character ingresado
                if(nextSpin=="P"|| nextSpin=="p"){
                    break; //si se ingresa "P" o "p" el bucle while termina y se continua con el juego.
                }else{
                    cout<<endl;
                    setColor(31); //color rojo
                    cout<<"Please enter a valid option (P), try again."<<endl; //si no se envia mensaje de error 
                    resetColor();
                    //el bucle se repite hasta que el usuario ingrese "P" 
                }
            }
        
            while(true){

                string pull;
                emptySlotsH(); //Se llama a la funcion Mostrar slots vacios al jugador 
                getline(cin,pull); //el jugador debe ingresar "!" y se lee el character ingresado
    
                if(pull=="!"){
                   //si se ingresa "!" se continua con el juego.
                    for(int i=0;i<3;i++){            //recorrer el arreglo
                        symbols[i]= randomSymbolE(); //guardar cada simbolo aleatorio obtenido
                    }
                    finalSlotsE(symbols); //Se llama a la funcion Mostrar slots finales al jugador
            
                    if(jackpotE(symbols)){ //llama a la funcion comprobar si todos los simbolos son iguales
                    //Si es true el jugador gano
                    setColor(32); //color verde
                    cout<<"            * JACKPOT!! *   "<<endl;
                    resetColor();
                    cout<<endl;
                    cout<<" Congratulations!! you have earned: $1500"<<endl; //muestra dinero obtenido por el jugador
                    cout<<endl;
                    i=0; //i toma el valor de 0 para finalizar el bucle for inicial
                    playerLose=0; //variable toma el valor de 0 para verificar que el jugador ha ganado
                    break; //el juego termina al i=0

                    }else{
                    //Si es false el jugador perdio
                    setColor(36); //color cian
                    cout<<"            KEEP TRYING "<<endl;
                    resetColor();
                    losePhrases();
                    playerLose=1; //variable toma el valor de 0 para verificar que el jugador ha perdido
                    break; //el jugador continuara con sus tiradas restantes
                }
                
                }else{
                    cout<<endl;
                    setColor(31); //color rojo
                    cout<<"Please enter a valid option (!), try again."<<endl;
                    resetColor();
                    //si no se envia mensaje de error 
                    //el bucle se repite hasta que el usuario ingrese "!" 
                }
            }         
        }

        if(playerLose==1){
            cout<<endl;
            cout<<"   You'll be lucky next time."<<endl;
            cout<<"-$300"<<endl;
            cout<<endl;
        }

        while(true){ //while infinito para validar que se ingreso un caracter valido
            cout<<"\nDo you want to play another round?"<<endl;
            cout<<"     YES (Y).        NO(N)"<<endl;
            getline(cin,anotherRound); //jugador ingresa su opccion y se lee su respuesta

            if(anotherRound=="Y"||anotherRound=="y"){
                cout<<endl;
                setColor(32); //color verde
                cout<<"GOOD LUCK!!"<<endl; //si se ingresa "Y" o "y" (yes) el bucle termina
                resetColor();
                anotherRound="";
                break;
            }else if(anotherRound=="N"||anotherRound=="n"){
                cout<<endl;
                cout<<"Return to menu..."<<endl; //si se ingresa "N" o "n" (no) el bucle termina
                break;
            }else{
                cout<<endl;
                setColor(31); //color rojo
                cout<<"Please enter a valid option (Y) or (N), try again."<<endl; 
                resetColor();
                //si no se envia mensaje de error y el bucle se repite
            }
        }

        if(anotherRound=="N"||anotherRound=="n"){ //validar si el juegador eligio si o no
            break; //si el usuario ingreso "N" o "n" (no) la funcion termina
        }   
    }
}


//juego principal
int main(){

    while (true){ //while infinito para primer menu

        showSlot(); //llama a la funcion showSlot (instrucciones del juego)
        string option;
        getline(cin, option); //Usuario ingresa opccion

        // verificacion de opccion ingresada
        if (option == "M" || option == "m"){

            cout<<"Returning to the main menu..."<<endl;
            break; // si ingresa "M" o "m" entonces se rompe el bucle y finaliza el programa (volver al menu inicial)
        }
        else if (option == "P" || option == "p"){
            // si ingresa "P" o "p" entonces el usuario se movera al menu de dificultades
            while (true){

                showSlotmenu(); // llama a funcion mostrar menu de dificultades
                string option;
                getline(cin, option); //usuario ingresa su opccion

                if (option == "B" || option == "b"){
                    break; //Volver al anterior menu
                } else if (option == "E"||option=="e"){
                    easyMode(); //llama a funcion easyMode (Juego modo facil)
                } else if (option == "M"||option=="m"){
                    mediumMode(); //llama a funcion mediumMode (juego modo medio)
                } else if (option == "H"||option=="h"){
                    hardMode(); //llama a funcion hardMode (juego modo dificil)
                } else {
                    // se muestra mensaje de error y se vuelve a pedir ingresar una opccion
                    setColor(31); //color rojo
                    cout << "Please enter a valid option (E),(M),(D) or (B), try again." << endl;
                    resetColor();
                }

            }
        }
        else
        {
            // se muestra mensaje de error y se vuelve a pedir ingresar una opccion
            setColor(31); //color rojo
            cout << "Please enter a valid option (M) or (P), try again." << endl;
            resetColor(); 
            
        }
    }

    return 0;
}
