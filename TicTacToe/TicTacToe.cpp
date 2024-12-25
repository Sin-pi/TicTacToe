// TicTacToe.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <cstdlib>
#include <iostream>
#include <unordered_map>
#include <bitset>
#include <string>


//probably bad practice but global so outputboard and getuserinput can use it. 
std::unordered_map<char, int> row = { {'T',0},{'M',3},{'B',6} };
std::unordered_map<char, int> col = {{'L',0},{'C',1},{'R',2} };

struct player {
    char playerName;
    std::bitset<9> taken_positions;
    player(char name, std::string positions) {
        playerName = name;
        taken_positions = std::bitset<9>(std::string(positions));
    }
};
//convient data structure to keep the piece symbol with the bitboard. 

void OutputBoard(player* Xs,player* Os)  {
    int i = 0;
    for (auto layer : row) {
        std::cout << layer.first << "\t";
        for (int x = 0; x < 3; x++) {
            std::cout <<" | ";
            if (!(Xs->taken_positions[i] || Os->taken_positions[i])){
                std::cout << ' ';
            }
            else {
                if (Xs->taken_positions[i])
                    std::cout << Xs->playerName;
                if (Os->taken_positions[i])
                    std::cout << Os->playerName;
            }
            i++;
            


        }
        std::cout << " |\n\t -------------\n";
    }
    std::cout << " \t   L   C    R\n\n";
        
}


int GetUserInput(player *current, player * waiting) {
    
    std::string input = "";
    while(1){

        std::cin >> input;
        if (input.length() > 2) {
            std::cout << "Warning// Output too long" << std::endl;
            continue;
        }//Auto removes most mistakes

         if (row.find(input[0]) != row.end() && col.find(input[1]) != col.end()) {

                int index = row[input[0]] + col[input[1]];
                
                if (waiting->taken_positions[index] || current->taken_positions[index]) {
                    std::cout << "spot taken!" << std::endl; 
                    continue;
                }
                else {
                    current->taken_positions[index] = 1;
                }
                return (row[input[0]]+col[input[1]]);
            }else {
                std::cout << "ERROR// not a choice!\n";
            
             }
    } 
        

}


bool CheckForWinners(player* current) {
    std::string WinStates[8] = { "111000000","000111000","000000111","100100100","010010010","001001001","100010001","001010100" };
    
    for (auto win : WinStates) {
        std::bitset<9> WinToBitset(win);
        std::bitset<9> temp(win);
        WinToBitset = WinToBitset & current->taken_positions;
        // performing an & operation checks if there are pieces in that area. if there isn't a piece there it won't equate to the win state. 
        if (temp == WinToBitset) {
            return true;
        }
        
        
    }
    return false;

}


int main()
{

   // sets player positions to zero
    player Xs('X', "000000000");
    player Os('O', "000000000");

    // pointers to swap whose turn it is.
    player* current;
    player* waiting;

    //main game loop. The game ends in 9 turns anyways so no need for infinite loop.
    for (int GameLoop = 0; GameLoop < 9; GameLoop++) {
        if (GameLoop % 2) {
            current = &Os;
            waiting = &Xs;
        }
        else {
            current = &Xs;
            waiting = &Os;
        }
        //^ puts x on first turn and swaps on every other turn.
        std::system("cls");

        OutputBoard(current, waiting);
        //^ takes in the bitboards and programatically outputs the current board state.
        GetUserInput(current, waiting);
        //^ takes in input and cleases it. Also won't allow for double placement.
        if (CheckForWinners(current)) {
            std::system("cls");
            OutputBoard(current, waiting);
            //more fun if you see the win
            std::cout << "The Winner is " << current->playerName;
            break;
        //^ goes through list of winning game states and if one of the current player has it they win.
        }
        std::cout << "if no winner here then draw!";
        //end of 9 turns is automatic draw.

    }
}

