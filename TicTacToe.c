#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <time.h>

//global variables
char board[3][3];
const char PLAYER = 'X';
const char COMPUTER = 'O';

void resetBoard();
void printBoard();
int checkFreeSpaces();
void playerMove();
void computerMove();
char checkWinner();
void printWinner(char);

int main()
{
    char winner = ' ';
    char response;

    do
    {
        winner = ' ';
        response = ' ';
        resetBoard();
        while(winner == ' ' && checkFreeSpaces() != 0)     //run until there is no winner and there is free spaces
        {
            printBoard();

            playerMove();               //player move
            winner = checkWinner();     //check if there is a winner
            if(winner != ' ' || checkFreeSpaces() == 0)
            {
                break;
            }

            computerMove();             //computer move
            winner = checkWinner();     //check if there is a winner
            if(winner != ' ' || checkFreeSpaces() == 0)
            {
                break;
            }
        } 

        //print the board and the winner when the game is end
        printBoard();
        printWinner(winner);

        printf("Would you like to play again? (Y/N): ", &response);
        scanf("%c");
        scanf("%c", &response);
        response = toupper(response);           //used to convert lowercase alphabet to uppercase, count lower case also
    } while (response == 'Y');

    printf("Thanks for playing!");

    return 0;
}

//reset board
void resetBoard()
{
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j< 3; j++)
        {
            board[i][j] = ' ';
        }
    }
}

void printBoard()
{
    int j = 0;
    for(int i = 0; i < 3; i++)
    {
        printf(" %c | %c | %c\n", board[i][j], board[i][j+1], board[i][j+2]);
        printf("---|---|---\n");
        j = 0;
    }   
}

//check how much return spaces lefts, if return zero so say game over
int checkFreeSpaces()
{
    int freeSpaces = 9;

    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if(board[i][j] != ' ')
            {
                freeSpaces--;
            }
        }
    }
    return freeSpaces;
}

void playerMove()
{
    int x, y;

    //while enter valid move
    do
    {
        printf("Enter row (1-3): ");
        scanf("%d", &x);
        x--;
        printf("Enter column (1-3): ");
        scanf("%d", &y);
        y--;

        //check if non empty move
        if(board[x][y] != ' ')
        {
            printf("Invalid move!\n");
        }
        else
        {
            board[x][y] = PLAYER;
            break;
        }
    } while (board[x][y] != ' ');
   
}

void computerMove()
{
    srand(time(0));
    int x, y;

    if(checkFreeSpaces() > 0)
    {
        do
        {
            x = rand() % 3;
            y = rand() % 3;
        } while (board[x][y] != ' ');

        board[x][y] = COMPUTER;
    }
    else
    {
        printWinner(' ');
    }
}

char checkWinner()
{
    //check rows
    for(int i = 0; i < 3; i++)
    {
        if(board[i][0] == board[i][1] && board[i][1] == board[i][2])
        {
            return board[i][0];
        }
    }
    //check rows
    for(int i = 0; i < 3; i++)
    {
        if(board[0][i] == board[1][i] && board[1][i] == board[2][i])
        {
            return board[0][i];
        }
    }
    //check diagonals
    if(board[0][0] == board[1][1] && board[1][1] == board[2][2])
    {
            return board[0][0];
    }
    if(board[0][2] == board[1][1] && board[1][1] == board[2][0])
    {
            return board[0][2];
    }

    return ' ';         //there is no winner
}

void printWinner(char winner)
{
    if(winner == PLAYER)
    {
        printf("YOU WIN!\n");
    }
    else if(winner == COMPUTER)
    {
        printf("COMPUTER WIN!\n");
    }
    else
    {
        printf("NO ONE WIN!\n");
    }
}
