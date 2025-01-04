#include <iostream>
#include <fstream>
#include <ctime>
#include <conio.h>

using namespace std;

const int max_data_size = 24; // matrix(maze) size

// Declaration of the maze in matrix form
char maze[max_data_size][max_data_size];

// Structure for storing player score
struct Score {
    int player_number; // declaration of player_number as an integer
    int points; // declaration of the accumulated points(score) as an integer
};

Score Score_table[3]; // Table to store the scores of the 3 players

// Function to initialize the scoreboard
void initialiserScores() {
    for (int i = 0; i < 3; ++i) {
        Score_table[i].player_number = i + 1; // Player number
        Score_table[i].points = 0; // Initializing the score to 0 for each player
    }
}

// Function to display player scores
void display_Scores(int nb) {
    cout << "Player(s) Score : " << endl;//display the phrase "player score:" on the screen
    for (int i = 0; i < nb; ++i) {//in this for function we will determine which player is playing and display his score
            if (i==0)
            cout << "Player P " << " : " << Score_table[i].points << " points" << endl;
            else
             if (i==1)
            cout << "Player Q " << " : " << Score_table[i].points << " points" << endl;
            else
             if (i==2)
            cout << "Player R " << " : " << Score_table[i].points << " points" << endl;
    }
}


// Function to load a maze from a text file into a 2D array
void show_maze(const char* file_name, char maze[max_data_size][max_data_size]) {
    string line;//declaring line as a string
    ifstream file(file_name);//ifstream(input file stream) will read the file maze
    if (file) {//if file is found

        string line;

        int i = 0;
        while (getline(file, line) && i < max_data_size) { // Read the contents of the file If the file has more than max_data_size rows, stop at the max_data_size'th row.

            for (int j=0;j<max_data_size;j++){
                maze[i][j]=line[j];
            }
            i++;
        }
        file.close();
    }
    else {// if file is not found , display an error message to the user
        cout << "Error! maze not found" << endl;
    }
}

//function to ask the user on the player number and choose a maze depending on the difficulty level chosen
void menu(char maze[max_data_size][max_data_size],int& num_play){
    srand(time(0));//Initialize random number generator
    int level,diff;//declaring level and diff as an integer
    cout<<"*************************************************************Title: TRY TO ESCAPE*******************************************************"<<endl;
        cout<<"Welcome to my game!"<<endl;//display a message to the user to explain the game
         cout<<"-Immerse yourself in a captivating 2D maze .The key to your escape lies in navigating your way out by uncovering paths marked with 'O'."<<endl;
         cout<<"-Consuming a bonus marked with the letter'B' grants you an extra movement "<<endl;
         cout<<"-Additionally, every bonus consumed contributes to your score, with 25 points awarded for each bonus successfully eaten. "<<endl;
         cout<<"-If you successfully escape the maze, 50 points will be added to your score, 10 points are awarded for every correct move."<<endl;
         cout<<"***************************************************************************************************************************************"<<endl;
    do{

        cout<<"Please specify number of players (1, 2, or 3): ";// ask the user about the player number
        cin>>num_play;
    }while(!(num_play>=1 && num_play<=3));//keep asking the player number until the user puts a number between 1 and 3
    do{
        cout<<"Select the game Difficulty: 1 for easy , 2 for average ,3 for hard :";//ask the user about the difficulty of the game
        cin>>diff;
    }while(!(diff>=1 && diff<=3));//keep asking the difficulty until the user puts a number between 1 and 3
    if (diff==1){
        level=rand()%2+1;//if diff=1 we choose either maze 1 or 2
    }
    else if (diff==2){
        level=rand()%2+3;//if diff=2 we choose maze 3 or 4
    }
    else {
        level=rand()%2+5;//if diff=3 we chose maze 5 or 6
    }
    show_maze(("maze"+to_string(level)+".txt").c_str(), maze);//converting the random number generated to a string and add the word maze in front and .txt in the end so it matches the file name
}

//function to display the maze
void display_maze(char maze[max_data_size][max_data_size]) {
    for (int i = 0; i < max_data_size; ++i) {// starting a for function to display the x-axis as i
        for (int j = 0; j < max_data_size; ++j) {//starting a for function to display y-axis as j
            cout << maze[i][j] ;//we display each line and collumn
        }
        cout <<endl;//we return to line so the next message doesn't show next to the maze
    }
}

//display the word winner by importing it from a file
void displayWinner()
{ string line;

    ifstream file("winner.txt");//import the file winner
    if (file) {//check if the file exists
        string line;
        while (getline(file, line) ) { // Read the contents of the file If the file has more than max_data_size rows, stop at the max_data_size'th row.
            cout<<line<<endl;
        }
        file.close();
    }else {
        cout << "Error! winner file not found " << endl;//if the file winne is not file we display an error message to the user
    }
}

// Function to place players initially in the maze
void player_displacement(char maze[max_data_size][max_data_size], int player_num) {
    int centerRow = max_data_size / 2;//find the center row which is 12 if max_data_size is 24
    int centerCol = max_data_size / 2;//find the center column which 12 if max_data_size is 24

    // Position each player in the center of the maze
    switch (player_num) {
        case 1: // case 1 represents if there is only one player
            maze[centerRow - 1][centerCol] = 'P'; // player 1 (P)

            break;
        case 2: // two players
            maze[centerRow - 1][centerCol] = 'P'; // player 1 (P)
            maze[centerRow + 1][centerCol] = 'Q'; // player 2 (Q)
            break;
        case 3: // Three players
            maze[centerRow - 1][centerCol] = 'P'; // player 1 (P)
            maze[centerRow + 1][centerCol] = 'Q'; // player 2 (Q)
            maze[centerRow][centerCol - 1] = 'R'; // player 3 (R)
            break;
        default:
            cout << "unsupported number of player " << endl;
            break;
    }
}

// Function to move a player according to the key pressed
// Find the position of player x:row number x and y:column number in the maze table
void player_position(char maze[max_data_size][max_data_size], char player, int& x, int& y) {
    bool found = false;//we take a bolean found as false
    for (int i = 0; i < max_data_size; ++i) {// i represnts x:row
        for (int j = 0; j < max_data_size; ++j) {// j represnts j:column
            if (maze[i][j] == player) {//keep checking each row,column until the player is found
                x = i;
                y = j;
                found = true;//if the player is found , then found= true and break from the for function to optomise to program and not run in the for loop for no reason
                break;
            }
        }
        if (found) break;//break from the for loop if found=true
    }
}

//converting characters from uppercase to lowercase
char lowerCase(char c) {
    // Check if the letter is capital
    if (c >= 'A' && c <= 'Z') {
        // Convert the letter to lowercase by adding the ascii difference between 'A' and 'a'
        c = c + ('a' - 'A');
    }
    return c;
}

// Function to move a player according to the key pressed
void player_displacement_via_keyboard(char maze[max_data_size][max_data_size], int playr,bool& winner ,Score Score_table[]) {
    int x = 0, y = 0; // Player coordinates
    char touche;
// Determine current player
    char player;
    switch (playr){
        case 1:player='P';
            break;
        case 2:player='Q';
            break;
        case 3:player='R';
            break;
    }
    player_position(maze,player,x,y);// Find the player's current position in the maze
    //Replace x and y with the player's coordinates
    int bonus;
    do{
        bonus=0;
        int posX = x; // Position X of player
        int posY = y; // Position Y of player

        switch(playr){// Keypressed
            case 1://player 1
                do{
                    cout << "Player " << playr << " controls: P role. Move up(w)  Move down(s)  Move left(a)  Move right(d) : ";//display the word player+(the player number)+ the button that he should press to move
                    touche = _getch();//key pressed
                    cout<<endl;
                    touche=lowerCase(touche);//making sure that whether the user inputs an upper or lower case we accept it and transfer it to a lower case as long as it meets the 4 available letter for movements by using the lowercase function
                }while(!(touche=='w' || touche=='s' || touche=='a' ||touche=='d' ));
                break;

            case 2://player 2
                do{
                    cout << "Player " << playr << " controls: Q role. Move up(i)  Move down(k)  Move left(j)  Move right(l) :  ";//display the word player+(the player number)+ the button that he should press to move
                    touche = _getch();
                    touche=lowerCase(touche);
                    cout<<endl;
                }while(!(touche=='i' || touche=='k' || touche=='j' ||touche=='l' ));
                break;
            case 3://player 3
                do{
                    cout << "Player " << playr << " controls: R role. Move up(g)  Move down(b)  Move left(v)  Move right(n) :  ";//display the word player+(the player number)+ the button that he should press to move
                    touche = _getch();
                    touche=lowerCase(touche);
                    cout<<endl;
                }while(!(touche=='g' || touche=='b' || touche=='v' ||touche=='n' ));
                break;
        }

        // Get the key pressed by the user
        // Move the Player according to the key pressed
        switch (touche) {
            case 'w': // the key to move up
                if (posX > 0) posX--;//positionX minus 1 because the player is moving up (the upper lines are less than the downwards lines)
                break;
            case 's': // the key to move down
                if (posX < max_data_size - 1) posX++;//positionX + 1 because the player is moving down
                break;
            case 'a': // the key to move left
                if (posY > 0) posY--;//positionY minus 1 because the player is moving left
                break;
            case 'd': // right
                if (posY < max_data_size - 1) posY++;//positionY plus 1 because the player is moving right
                break;
            case 'i': //up
                if (posX > 0) posX--;
                break;
            case 'k': //down
                if (posX < max_data_size - 1) posX++;
                break;
            case 'j': // left
                if (posY > 0) posY--;
                break;
            case 'l': // right
                if (posY < max_data_size - 1) posY++;
                break;
            case 'g': // up
                if (posX > 0) posX--;
                break;
            case 'b': // down
                if (posX < max_data_size - 1) posX++;
                break;
            case 'v': // left
                if (posY > 0) posY--;
                break;
            case 'n': // right
                if (posY < max_data_size - 1) posY++;
                break;
        }

        // Player reaches the exit
        if (maze[posX][posY]=='O'){//if the player position=O than he found his way out and won
            winner=true;
            // Update player position in maze board with new player
            maze[posX][posY] = player;
            // Update the player's old coordinates with the character representing an empty square
            maze[x][y] = ' ';}
        else
        {
            if (posX > 0 && posX < max_data_size-1 && posY > 0 && posY < max_data_size-1) {
                if (maze[posX][posY]==' '){//if there is no character to where the player wants to move
                    maze[posX][posY] = player;// Update player position in maze board with new player
                    // Update the player's old coordinates with the character representing an empty square
                    maze[x][y] = ' ';
                    Score_table[playr - 1].points += 10; //Increment score for correct movement
                }
                else if (maze[posX][posY]=='B'){//if the player finds bonus along the way
                    maze[posX][posY] = player;//Update player position in maze board with the new player position
                    maze[x][y] = ' ';// Update the player's old coordinates with the character representing an empty square
                    x=posX;
                    y=posY;
                    bonus=1;
                    Score_table[playr - 1].points += 25; // Increment score for correct movement
                    system("cls");//clear screen
                    // Show maze
                    display_maze(maze);
                    cout<<"Congratulations! You've earned a bonus! Enjoy an additional free move and a boost to your score!"<<endl;// display to the user that he got a bonus and has another movement
                }
                else{
                    maze[x][y] = player;// After moving, update the player's position in the maze board
                }
                system("cls");//clear screen
                display_maze(maze);//display the maze with the new coordinates of the players
            }
        }
    }while(bonus==1);
}

// Function to manage a player's turn
void playr_tour(char maze[max_data_size][max_data_size], int playr,bool& winner) {

    winner=false;//set winner as false
    player_displacement_via_keyboard(maze, playr,winner,Score_table);//Manage player movement based on key pressed
    if (winner) {// Check if the player has reached the exit
        system("cls");//clean all screen
        cout<<endl<< endl<< endl<< endl;
        // Check if the player has reached the exit
        if (playr==1)//check if it is player 1 who won
            cout<<"  Player 'P' is the winner! Congratulations! "<< endl;
            else
             if (playr==2)//check if it is player 2 who won
            cout<<"  Player 'Q' is the winner! Congratulations! "<< endl;
            else
             if (playr==3)//check if it is player 3 who won
            cout<<"  Player 'R' is the winner! Congratulations! "<< endl;

        cout<<endl<< endl<< endl<< endl;
        displayWinner();//display the file winner
    }
}



// Main function of the program
int main() {
    char replay;//declaring replay as a charactere
    do {//Main game loop
        int num_play;
        bool gameOver = false;//setting gameOver as false
        system("cls");//clean screen
        menu(maze, num_play); // Menu for selecting the number of players and difficulty
        player_displacement(maze, num_play); // placement of players in maze
        system("cls");//clean screen
        display_maze(maze); // Viewing the maze for the first time
        while (!gameOver) {
            bool winner = false;
            for (int i = 1; i < num_play + 1; ++i) {
                playr_tour(maze, i, winner); // Managing a player's turn

                if (winner) {
                    // Updating scores and declaring the winning player
                    Score_table[i - 1].points += 50; // Added 50 points for winning the game
                    gameOver = true;// Declaration of the winning player and end of the game
                    cout << endl << endl << endl << endl;
                    display_Scores(num_play);// Display scores at the end of the game
                    do {
                        cout << "Ready for another round? (y/n) Type 'y' for yes or 'n' for no ";//asl the player for another round
                        cin >> replay;
                    } while (!(replay == 'y' || replay == 'Y' || replay == 'n' || replay == 'N'));//repeat the loop if the player does not give(y,n or Y,N)
                    break;
                }
            }
        }
    } while (replay == 'y' || replay == 'Y');//repeat the main game loop if the player answers with y or Y

    system("cls");//clean screen to prepare for the output message
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
//Output message
    cout<<"************      **          **   **************      "<< endl;
    cout<<"*          **      **        **    **                  "<<endl;
    cout<<"*           **      **      **     **                  "<<endl;
    cout<<"*            **      **    **      **                  "<<endl;
    cout<<"*            **       **  **       **                  "<< endl;
    cout<<"*            **        ****        **                  "<<endl;
    cout<<"***************         **         **************      "<<endl;
    cout<<"*            **         **         **                  "<<endl;
    cout<<"*            **         **         **                  "<< endl;
    cout<<"*            **         **         **                  "<<endl;
    cout<<"*            **         **         **                  "<<endl;
    cout<<"*           **          **         **                  "<<endl;
    cout<<"*          **           **         **                  "<< endl;
    cout<<"************            **         **************      "<<endl;
    return 0;
}
