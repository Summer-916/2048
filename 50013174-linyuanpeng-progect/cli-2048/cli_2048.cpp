#include "..\core-2048\core_2048.hpp"

// - CLI unique global value zone
int limit = 2048; // - Limited mode game settings, end condition is limit
int step = 1; // - "step" represents the operation of each step, '0' is to open the settings, '1' is to walk normally
int mode = 0; // - "mode" represents the game mode, 0 is limited mode, 1 is infinite mode
// - CLI UI function declare zone
void setName();
void printHighestScore();
void setGameMode();
void moveFunction(char move);
bool isValidMove(char move);

void openningUI(){
    cout<<"----------------------------------------\n";
    cout<<"Welcome to 2048, following are the key rules\n";
    cout<<"----------------------------------------\n";
    cout<<"Press w,a,s,d to control the movement of numbers\n";
    cout<<"Press j to open the control console\n";
    cout<<"----------------------------------------\n";
    cout<<"Enjoy your 2048 now!!\n";
}

void setting(){
    cout<<"----------------------------------------\n";
    cout<<"Press key c to enter your name"<<'\n';
    cout<<"Press key s to select your game mode"<<'\n';
    cout<<"Press key g to continue your game"<<'\n';
    cout<<"----------------------------------------\n";

    char ope;
    cin>>ope;

    switch(ope){
        case 'c':
            setName();
            break;
        case 's':
            setGameMode();
            break;
        case 'g':
            break;
        case 't': // - use for testing
            break;
        default:
            cout<<"Sorry, this is not a valid command\n";
            break;
    }
}

void setName(){ // - Nicessss
    cout<<"----------------------------------------\n";
    cout<<"Your great name: ";
    cin>>name;
}

void setGameMode(){
    cout<<"----------------------------------------\n";
    cout<<"Change maximum points or Endless mode"<<'\n';
    cout<<"Press key c to change maximum points"<<'\n';
    cout<<"Press key e to choose infinite mode"<<'\n';
    cout<<"----------------------------------------\n";

    char choice;
    cin>>choice;
    switch(choice){
        case 'c':
        {
            cout<<"What is your limit? Please input exponent of 2:";
            int walk;
            cin>>walk;  // - 先假设合理，以后再改.
            //if(limit<walk){
            limit = walk;
                //mode = 0;
            //}
            //else cout<<"You should try a harder mode! Input a larger number next time!\n";
            break;
        }
        case 'e':
        {   
            mode = 1;
            break; // - 尚未开发.
        }
        default:
            cout<<"Sorry, this is an invalid move. Return to the game console.\n";
    }
}

void moveFunction(char move){
    if (move == 'w')
    {
        upMove();
    }
    else if (move == 's')
    {
        downMove();
    }
    else if (move == 'a')
    {
        leftMove();
    }
    else if (move == 'd')
    {
        rightMove();
    }
}

bool isValidMove(char move) // - It is CLI mode
{
    bool keyValid = move == 'w' || move == 'a' || move == 's' || move == 'd';
    if (keyValid)
    {
        int copyScore = currentScore;
        int copyExBoard[4][4] = {};
        for(int i=0;i<4;++i){
            for(int j=0;j<4;++j){
                copyExBoard[i][j] = exponentBoard[i][j];
            }
        }
        moveFunction(move);
        // Check if merge
        if (currentScore != copyScore)
        {
            return true;
        }
        // Check if move
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (exponentBoard[i][j] != copyExBoard[i][j])
                {
                    return true;
                }
            }
        }
        return false;
    }
    return false;
}

void printBoard(){
    // - Print the console
    cout<<"----------------------------------------\n";
    cout<<"User Name : "<<name<<'\n';
    if(mode == 0) cout << "Current mode  : "<<limit<<'\n';
    else cout << "Current mode  : Infinite mode\n";
    int a = highestScore > currentScore ? highestScore : currentScore;
    highestScore = a;
    cout << "Highest score : " << highestScore<<'\n';
    cout << "Current score : " << currentScore << '\n';
    cout<<"----------------------------------------\n";
    // - Print the board
    for (int i = 0; i < 4; i++)
    {   
        
        for (int j = 0; j < 4; j++)
        {   
            cout << "|";
            if(surfaceBoard[i][j]) cout << surfaceBoard[i][j] << '\t';
            else cout<<'\t';
        }
        cout << "|";
        cout << '\n';
    }
    cout<<"----------------------------------------\n";
}

void endOrGoOn(){
    cout<<"This round of game is over\n";
    cout<<"Would you like to have a new turn? (y/n)";
    char a;
    cin>>a;
    cout<<"----------------------------------------\n";
    switch(a){
        case 'y':
            cout<<"New game is ready!\n";
            break;
        case 'n':
            cout<<"See u again~\n";
            goOn = false;
            break;
        default:
            cout<<"You don't give a clear command, so continue!\n";
            break;
    }
}

void closingUI(){
    cout<<"----------------------------------------\n";
    cout << "Gameover!\n";
    cout << "The following are the statistics of your game this round:\n";
    cout << "The highest score:            "<< highestScore<<'\n';
    cout<<"----------------------------------------\n";
    cout<<"Final word: "<<name<<", ";
    if(highestScore>10000) cout<<"you are the god of 2048!"; // - 2048 is the spirit of this game
    else cout<<"you are vegetable! Practice more!";
}

int main()
{
    while(goOn)
    {    
        char move;
        openningUI();
        randomTile();
        randomTile();
        boardUpdate();
        while (!gameIsOver())
        {

            printBoard();
            cout<<"Next move:";
            cin >> move;
            if(move=='j'){
                setting();
                step = 0;
            }
            if(step){
                if(isValidMove(move))
                {
                    moveFunction(move);
                    boardUpdate();
                    if(!mode){
                        if (successful(limit))
                        {   
                            cout << "Cangratulation! You pass the challenge!" << '\n';
                            break;
                        }
                    }
                }
                else
                {
                    cout << "Sorry, this is an invalid move. Try again." << '\n';
                    continue;
                }
                randomTile();
                boardUpdate();
            }
            step = 1;
        }
        printBoard();
        endOrGoOn(); // End of a round
    }
    closingUI(); // - True end of this program
    return 0;
}