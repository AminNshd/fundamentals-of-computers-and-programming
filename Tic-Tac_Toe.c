#include <stdio.h>
short guessNextMove(char[3][3]); //finds the best move for the AI
void placeTheMove(char[3][3],short move,char player); //places the move on the board
void availableMoves(char[3][3],short[9]); //returns all the possible moves that can be taken
char isItLegal(char[3][3],short move); //can the move be placed? is it a legal move?
void futureState(char[3][3],char turn); //imagines all the possible states of the board after a turn
char result(char[3][3]); //who won? U:User, C:Computer, D:Draw, N:Not ended yet
void initialize(char[3][3]); //initialize the game
void play(char[3][3]);// The core of the program which plays the game;
void copyArr(char[3][3],char[3][3]); //Copies the board into an array for furtuher analysis without modifying the board
void printBoard(char[3][3]); //Prints the board
char invertTurn(char);
short preventThree(char[3][3],short move);
int outcome = 0;
int depth = 0;
short mode;
short totalTurns = 0;
char turn; //whose turn is it?
int main()
{
    printf("Welcome to the game. Please Enter a mode:\n1- Normal Tic Tac Toe\n2- 3x tic tac toe\n");
    scanf("%hu",&mode);
    printf("Who plays first? 1: Computer 2:User\n");
    short first;
    scanf("%hu",&first);
    if (first == 1)
    turn = 'C';
    else
    turn = 'U';
    char board[3][3];
    initialize(board);
    play(board);
    return 0;
}

void initialize(char board[3][3])
{
    for (short row = 0; row < 3; row++)
    {
        for (short column = 0; column < 3; column++)
        {
            board[row][column] = 'N';
        }
        
    }
    
    
}

void play(char board[3][3])
{
    char status = result(board);
    while ((status == 'N' && mode == 1) || (status == 'N' && mode == 2 && totalTurns < 6)) //while the game is not finished
    {
        if (turn == 'U')
        {
            short move;
            char legality;
            do
            {
                printf("Please enter a legal move.\n"); //XXXX
                scanf("%hu",&move);
            } while ((legality = isItLegal(board,move)) != 'Y'); //while the move is not legal, ask for another move
            placeTheMove(board,move,'U');
            turn = 'C';
        }
        else
        {
            short move = guessNextMove(board);
            placeTheMove(board,move,'C'); //XXX
            printf("%hu\n",move);
            turn = 'U';
        }
        if (mode == 2)
        totalTurns++;
        status = result(board);
        printBoard(board);
    }
   
    printf("The result of the game is: ");
    switch (status)
    {
    case 'C':
    printf("Computer won!");
    break;
    case 'U':
    printf("User won!");
        break;
    case 'N':
    case 'D':
    printf("Draw");
    break;
    }
    
}

short guessNextMove(char board[3][3])
{
    if (board[0][2] == board[2][0] && board[2][0] == 'U' && board[1][1] == 'C' &&
        board[0][0] == board[0][1] && board[0][1] == board[1][0] && board[1][0] == board[1][2]
        && board[1][2] == board[2][1] && board[2][1] == board[2][2] && board[2][2] == 'N')
        return 21;
    short bestMove;
    char cBoard[3][3];
    copyArr(board,cBoard);
    short allMoves[9];
    availableMoves(cBoard,allMoves);
    int bestOutcome = -10000000;
    int bestDepth = 100000000;
    char prevent = 'N';
    for (short i = 0; i < 9 && allMoves[i] != -1; i++)
    {
        outcome = 0;
        depth = 0;
        placeTheMove(cBoard,allMoves[i],'C');
        futureState(cBoard,'U');
        if (depth == 1 && outcome > 0)
        return allMoves[i];
        else if (preventThree(cBoard,allMoves[i])==1)
        {
            bestMove = allMoves[i];
            prevent = 'Y';
        }
        else if (depth <= bestDepth && outcome >= bestOutcome && prevent == 'N')
        {
            bestOutcome = outcome;
            bestMove = allMoves[i];
            bestDepth = depth;
        }
        placeTheMove(cBoard,allMoves[i],'N');
    }
    return bestMove;
    
}

void futureState(char board[3][3],char pTurn)
{
    char status = result(board);
    char cBoard[3][3];
    copyArr(board,cBoard);
    switch (status)
    {
    case 'U':
        outcome--;
        depth++;
        return;
        break;
    case 'C':
        outcome++;
        depth++;
        return;
        break;
    case 'D':
        depth++;
        return;
        break;
    }
    
    short allMoves[9];
    availableMoves(cBoard,allMoves);
    for (short i = 0; i < 9 && allMoves[i] != -1; i++)
    {
        placeTheMove(cBoard,allMoves[i],pTurn);
        futureState(cBoard,invertTurn(pTurn));
        placeTheMove(cBoard,allMoves[i],'N');
    }

}

void placeTheMove(char board[3][3],short move,char player)
{
    short row = move / 10;
    short column = move % 10;
    board[row][column] = player;
}

void availableMoves(char board[3][3],short moves[9])
{
    for (short i = 0; i < 9; i++)
        moves[i] = -1;
    
    short index = 0;
    short move;
    for (short row = 0; row < 3; row++)
    {
        for (short column = 0; column < 3; column++)
        {
            move = (row * 10) + column;
            if (isItLegal(board,move) == 'Y')
                moves[index++] = move;
            
        }
        
    }
}
char isItLegal(char board[3][3],short move)
{
    return (board[move/10][move%10] == 'N') ? 'Y' : 'N';
}
char result(char board[3][3])
{
    //checking rows
    for (short row = 0; row < 3; row++)
    {
        if (board[row][0] == board[row][1] && board[row][1] == board[row][2] && board[row][2] == 'U')
        return 'U';
        if (board[row][0] == board[row][1] && board[row][1] == board[row][2] && board[row][2] == 'C')
        return 'C';   
    }

    //checking columns
    for (short column = 0; column < 3; column++)
    {
        if (board[0][column] == board[1][column] && board[1][column] == board[2][column] && board[2][column] == 'U')
        return 'U';
        if (board[0][column] == board[1][column] && board[1][column] == board[2][column] && board[2][column] == 'C')
        return 'C';
    }

    //checking diagnols
    if ((board[0][0] == board[1][1] && board[1][1] == board[2][2]) ||
        (board[0][2] == board[1][1] && board[1][1] == board[2][0]))
    {
        if (board[1][1] == 'U')
        return 'U';
        else if (board[1][1] == 'C')
        return 'C';
    }
    
    //check if there's any available moves
    short moves[9];
    availableMoves(board,moves);
    if (moves[0] == -1)
    return 'D'; //No available moves and no winner therefore the game is a draw
    else
    return 'N'; //The game hasn't finished yet
    
}
void copyArr(char source[3][3],char dest[3][3])
{
    for (short i = 0; i < 3; i++)
        for (short j = 0; j < 3; j++)
            dest[i][j] = source[i][j];
    
}
void printBoard(char board[3][3])
{
    printf("\n");
    for (short row = 0; row < 3; row++)
    {
        for (short column = 0; column < 3; column++)
            printf("(%c)\t",board[row][column]);
        printf("\n");
    }
    
}
char invertTurn(char turn)
{
    return (turn == 'C') ? 'U' : 'C';
}

short preventThree(char board[3][3], short move)
{
    short row = move / 10;
    short col = move % 10;

    //checking the row
    if ((col == 0 && board[row][1] == 'U' && board[row][2] == 'U') ||
        (col == 1 && board[row][0] == 'U' && board[row][2] == 'U') ||
        (col == 2 && board[row][1] == 'U' && board[row][0] == 'U'))
        return 1;

    //checking the column
    if ((row  == 0 && board[1][col] == 'U' && board[2][col] == 'U') ||
        (row  == 1 && board[0][col] == 'U' && board[2][col] == 'U') ||
        (row  == 2 && board[1][col] == 'U' && board[0][col] == 'U'))
        return 1;

    //checking the diagonal (if it exists)
    if (((col == 0 && row == 0) && board[1][1] == 'U' && board[2][2] == 'U') ||
        ((col == 1 && row == 1) && board[0][0] == 'U' && board[2][2] == 'U') ||
        ((col == 2 && row == 2) && board[1][1] == 'U' && board[0][0] == 'U'))
        return 1;

    if (((col == 0 && row == 2) && board[1][1] == 'U' && board[0][2] == 'U') ||
        ((col == 1 && row == 1) && board[0][2] == 'U' && board[2][0] == 'U') ||
        ((col == 2 && row == 0) && board[1][1] == 'U' && board[2][0] == 'U'))
        return 1;

    return 0;
}
