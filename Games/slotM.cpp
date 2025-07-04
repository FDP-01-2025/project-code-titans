#include <iostream>
#include <cstring>     //library to handle string type text
#include <cstdlib>     //To use rand()
#include <ctime>       // To use time() as a random seed
using namespace std;

//GENERAL FUNCTIONS (For all games)

//function to change the text color
void setColor(int colorCode) {
    cout << "\033[" << colorCode << "m"; 
}
//function to return to white color
void resetColor() {
    cout << "\033[0m";
}

// Function to display the game instructions
void showSlot()
{

    cout << endl;
    cout << "* - * - * - * - * - * - * - * - *. . . . . . . . . . . . . . " << endl;
    cout << "|                                                          . " << endl;
    cout << "*                  ";
    setColor (36); //cian
    cout << " -PLAY SLOT MACHINE-";
    resetColor ();
    cout << "                    . " << endl;
    cout << "|                                                          . " << endl;
    cout << "*    A slot machine is a game where a series of random     . " << endl;
    cout << "|    symbols are displayed on each spin. If all the        . " << endl;
    cout << ".    symbols on a line match, you win.                     | " << endl;
    cout << ".                                                          * " << endl;
    cout << ".                                                          | " << endl;
    cout << ".    ";
    setColor (31); //red
    cout << "MENU (M)                 ";
    setColor (32); //green
    cout << "                PLAY (P)";
    resetColor ();
    cout << "     * " << endl;
    cout << ".                                                          | " << endl;
    cout << ". . . . . . . . . . . . . .* - * - * - * - * - * - * - * - * " << endl;
    cout << endl;
    //It is indicated that you must enter "M" to return to the menu or "P" to play
}

// Function to display the slot game difficulty menu
void showSlotmenu(){

    cout << endl;
    cout << "* - * - * - * - * - * - * - * -*. . . . . . . . . . . . . . " << endl;
    cout << "|                                                          . " << endl;
    cout << "*                     ";
    setColor (36); //cian
    cout << " -SLOT MACHINE-                    ";
    resetColor ();
    cout << "  . " << endl;
    cout << "|                                                          . " << endl;
    cout << "*                  Choose the difficulty:                  . " << endl;
    cout << "|                                                          . " << endl;
    cout << ".   ";
    setColor(32); //green
    cout << "(E) EASY:";
    resetColor();
    cout <<"      3 lines (Bet: $100, Win: $300)          | " << endl;
    cout << ".   ";
    setColor(33); //yellow
    cout << "(M) MEDIUM:";
    resetColor();
    cout << "    4 lines (Bet: $200, Win: $800)          * " << endl;
    cout << ".   ";
    setColor(35); //magenta
    cout << "(H) HARD:";
    resetColor();
    cout << "      5 lines (Bet: $300, Win: $1500)         | " << endl;
    cout << ".                                                          * " << endl;
    cout << ".     ";
    setColor(31); //red
    cout << "BACK (B)";
    resetColor();
    cout << "                                             | " << endl;
    cout << ". . . . . . . . . . . . . .* - * - * - * - * - * - * - * - * " << endl;
    cout << endl;
//It indicates that you must enter "B" to return to the previous menu
//"E" for easy mode, "M" for medium mode, "H" for hard mode

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
    cout<<"*          ";
    setColor (36); //cian
    cout<< "Try your luck!";
    resetColor ();
    cout<<"        ."<<endl;
    cout<<"|                                ."<<endl;
    cout<<"*    -----------------------     ."<<endl;
    cout<<".   |       |       |       |    |"<< endl;
    cout<<".   |   -   |   -   |   -   |    *" <<endl;
    cout<<".   |       |       |       |    |"<< endl;
    cout<<".    -----------------------     *"<<endl;
    cout<<".   | ";
    setColor (32); //green
    cout<<"Pull the lever (!)";
    resetColor ();
    cout<<"|        |"<<endl;
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
    cout<<"*            ";
    setColor(36); //cian
    cout<<"RESULTS!";
    resetColor();
    cout<<"            ."<<endl;
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
                        setColor(36); //cyan color
                        cout<<"            KEEP TRYING "<<endl;
                        resetColor();
                        losePhrases();
                        playerLose=1; //variable takes the value of 0 to verify that the player has lost
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
            setColor(36); //cian
            cout<<"\nDo you want to play another round?"<<endl;
            setColor(32); //green
            cout<<"     YES (Y).";
            setColor(31); //red
            cout<<"        NO(N)"<<endl;
            resetColor();
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
    cout<<"*             ";
    setColor (36); //cian
    cout<< "Try your luck!";
    resetColor ();
    cout<<"            ."<<endl;
    cout<<"|                                       ."<<endl;
    cout<<"*    -------------------------------    ."<<endl;
    cout<<".   |       |       |       |       |   ."<< endl;
    cout<<".   |   -   |   -   |   -   |   -   |   *" <<endl;
    cout<<".   |       |       |       |       |   |"<< endl;
    cout<<"*    -------------------------------    *"<<endl;
    cout<<".    | ";
    setColor (32); //green
    cout<<"Pull the lever (!)";
    resetColor ();
    cout<<"|              |"<<endl;
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
    cout<<"*                ";
    setColor(36); //cian
    cout<<"RESULTS!";
    resetColor();
    cout<<"               ."<<endl;
    cout<<"|                                       ."<<endl;
    cout<<"*    -------------------------------    ."<<endl;
    cout<<".   |       |       |       |       |   ."<< endl;
    //Random symbols will be displayed on this line
    cout<<".   |   ";
    symbolColorM(slots); //Call the function to display the generated symbols with their respective colors
    cout<<"*" <<endl;
    cout<<".   |       |       |       |       |   |"<< endl;
    cout<<"*    -------------------------------    *"<<endl;
    cout<<".                                       |"<<endl;
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
                        symbols[i]= randomSymbolM(); //save each random symbol obtained
                    }
                    finalSlotsM(symbols); //The function Show final slots to the player is called
                
                    if(jackpotM(symbols)){ //calls the function to check if all symbols are equal
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
            cout<<"-$200"<<endl; //amount the player lost
            cout<<endl;
        }

        while(true){ //infinite while to validate that a valid character was entered
            setColor(36); //cian
            cout<<"\nDo you want to play another round?"<<endl;
            setColor(32); //green
            cout<<"     YES (Y).";
            setColor(31); //red
            cout<<"        NO(N)"<<endl;
            resetColor();
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

//                                           HARD MODE

void emptySlotsH(){
    //Show empty slots to the player
    cout<<endl;
    cout<<"* - * - * - * - * - * - * . . . . . . . . . . . ."<<endl;
    cout<<"|                                               ."<<endl;
    cout<<"*                 ";
    setColor (36); //cian
    cout<< "Try your luck!";
    resetColor ();
    cout<<"                ."<<endl;
    cout<<"|                                               ."<<endl;
    cout<<"*    ---------------------------------------    ."<<endl;
    cout<<".   |       |       |       |       |       |   ."<< endl;
    cout<<".   |   -   |   -   |   -   |   -   |   -   |   *" <<endl;
    cout<<".   |       |       |       |       |       |   |"<< endl;
    cout<<".    ---------------------------------------    *"<<endl;
    cout<<".    | ";
    setColor (32); //green
    cout<<"Pull the lever (!)";
    resetColor ();
    cout<<"|                      |"<<endl;
    cout<<". . . . . . . . . . . . * - * - * - * - * - * - *"<<endl;
    cout<<endl;
    //the player is instructed to press "!" to generate the random symbols
}

char randomSymbolH (){
    //Function to generate random symbols
    char symbol [3]= {'$','7','@'}; //array with 3 symbols
    int randomP = rand()%3; //variable to choose a number from 0 to 2
    return symbol[randomP]; //the function will return a random symbol
}

void symbolColorH(char slots[5]){
    for(int i=0;i<5;i++){ //read the array of symbols
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

void finalSlotsH (char slots[5]){
   //Function to show final slots to the player
    
    cout<<endl;
    cout<<"* - * - * - * - * - * - * . . . . . . . . . . . ."<<endl;
    cout<<"|                                               ."<<endl;
    cout<<"*                    ";
    setColor(36); //cian
    cout<<"RESULTS!";
    resetColor();
    cout<<"                   ."<<endl;
    cout<<"|                                               ."<<endl;
    cout<<"*    ---------------------------------------    ."<<endl;
    cout<<".   |       |       |       |       |       |   ."<< endl;
    //Random symbols will be displayed on this line
    cout<<".   |   ";
    symbolColorH(slots);
    cout<<"." <<endl;
    cout<<".   |       |       |       |       |       |   |"<< endl;
    cout<<".    ---------------------------------------    *"<<endl;
    cout<<".                                               |"<<endl;
    cout<<". . . . . . . . . . . . * - * - * - * - * - * - *"<<endl;
    cout<<endl;

}

bool jackpotH(char slots[5]){
    //function to validate if the 3 symbols are equal
    return(slots[0]==slots[1] && slots[1]==slots[2] && slots[2]==slots[3]&& slots[3]==slots[4]);
    //if all three are equal = true
}

//Main game hard
void hardMode(){

    char symbols[3]; //arrangement to save random symbols
    
    int playerLose; //Validate if the player won or lost
    string anotherRound; //save player response

    while (true){ //while infinite for the player to decide to continue playing

        srand(time(0)); //randomness
        
         for(int i=15;i>0;i--){ //for loop that repeats each shot 15 times

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
                emptySlotsH(); //The function Show empty slots to the player is called
                getline(cin,pull); //the player must enter "!" and the entered character is read
    
                if(pull=="!"){
                    //If "!" is entered the game continues.
                    for(int i=0;i<5;i++){            //locate the array
                        symbols[i]= randomSymbolH(); //save each random symbol obtained
                    }
                    finalSlotsH(symbols); //The function Show final slots to the player is called
            
                    if(jackpotH(symbols)){ //calls the function to check if all symbols are equal
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
            cout<<"-$300"<<endl; //amount the player lost
            cout<<endl;
        }

        while(true){ //infinite while to validate that a valid character was entered
            setColor(36); //cian
            cout<<"\nDo you want to play another round?"<<endl;
            setColor(32); //green
            cout<<"     YES (Y).";
            setColor(31); //red
            cout<<"        NO(N)"<<endl;
            resetColor();
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

//main game
int main(){

    while (true){ //while infinite for first menu

        showSlot(); //call the showSlot function (game instructions)
        string option;
        getline(cin, option); //User enters option

        //verification of entered option
        if (option == "M" || option == "m"){
            cout<<"Returning to the main menu..."<<endl;
            break; // if you enter "M" or "m" then the loop is broken and the program ends (return to the initial menu)
        }
        else if (option == "P" || option == "p"){
            // if you enter "P" or "p" then the user will move to the difficulties menu
            while (true){

                showSlotmenu(); //call function to display difficulties menu
                string option;
                getline(cin, option); //user enters their option

                if (option == "B" || option == "b"){
                    break; //Return to the previous menu
                } else if (option == "E"||option=="e"){
                    easyMode(); //call easyMode function (easy mode game)
                } else if (option == "M"||option=="m"){
                    mediumMode(); //call function mediumMode (medium mode game)
                } else if (option == "H"||option=="h"){
                    hardMode(); //call hardMode function (game hard mode)
                } else {
                    // an error message is displayed and an option is requested again
                    setColor(31); //red
                    cout << "Please enter a valid option (E),(M),(D) or (B), try again." << endl;
                    resetColor();
                }
            }

        } else {
            // an error message is displayed and an option is requested again
            setColor(31); //red
            cout << "Please enter a valid option (M) or (P), try again." << endl;
            resetColor(); 
        }
    }

    return 0;

}
