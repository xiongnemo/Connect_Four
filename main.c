#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char board[6][8]={
"        ",
"        ",
"        ",
"        ",
"        ",
"        "};

int winningFlag=0;//Who wins?
int drawFlag=0;//Draw?
int currentOption=0;

const int searchDirection[8][2] = { {-1,-1}, {-1, 0}, {0, -1}, {1, -1}, {-1, 1}, {0, 1}, {1, 0}, {1, 1} };

void printBoard(void);
void judge(void);
void judgeCondition(int player, int x,int y);
//void judgeSearch(int player, int depth, int x,int y);
void computerMove(void);
void humanMove(void);
void turn(int player, int column);
int isInBound(int x, int y);

int main(void)
{
    int i;
    int j;
    srand(time(0));
    int gameTurnCount=0;//How many turns?
    int continueFlag=1;//Whether the game should continue
    printf("Hi, I'm Marshmallow. Wanna play chess with me?\n");
    printf("You know the rules, right?\n");
    printf("I play O, while you play X. I go first.\n");
    printf("\nNow, let the game begin!\n");
    printf("This is the initial status of the board:\n");
    printBoard();
    while (1)
    {
        computerMove();
        judge();
        printBoard();
        if (winningFlag!=0)
            break;
        humanMove();
        judge();
        printBoard();
        if (winningFlag!=0)
            break;
        gameTurnCount++;
        if (gameTurnCount==24)
        {
            drawFlag=1;
            break;
        }
    }
    if (drawFlag==1)
        printf("It's a tie!\n");
    if (drawFlag==0)
    {
        if (winningFlag==1)
            printf("I win!\n");
        if (winningFlag==2)
            printf("Okay, you win.\n");
    }
    return 0;
}

void printBoard(void)
{
    int i;
    int j;
    char visualBoard[8][18]=
   {" 1 2 3 4 5 6 7 8 ",
    "| | | | | | | | |",
    "| | | | | | | | |",
    "| | | | | | | | |",
    "| | | | | | | | |",
    "| | | | | | | | |",
    "| | | | | | | | |",
    "-----------------"
    };//Init

    for (i=0; i<6; i++)//Perform cast from board to visualBoard
        for (j=0; j<8; j++)
            visualBoard[i+1][2*j+1]=board[i][j];
    for (i=0; i<=7; i++)
    {
        for (j=0;j<18;j++)
            printf("%c",visualBoard[i][j]);
        printf("\n");
    }
}


void judge(void)
{
    int i;
    int j;
    //currentOption=100;
    for (i=0;i<6;i++)
    {
        for (j=0;j<8;j++)
        {
            if (board[i][j]==' ')
            {
                continue;
            }
            if (board[i][j]=='O')
            {
                judgeCondition(1,i,j);
            }
            if (board[i][j]=='X')
            {
                judgeCondition(2,i,j);
            }
            if (winningFlag!=0)
                return;
        }
    }
}

void judgeCondition(int player, int x, int y)
{
    int i;
    for (i=0;i<8;i++)
    {
        if (isInBound(x+3*searchDirection[i][0],y+3*searchDirection[i][1]))
        {
            if (player==1)
            {
                if (board[x+1*searchDirection[i][0]][y+1*searchDirection[i][1]]=='O'&&
                    board[x+2*searchDirection[i][0]][y+2*searchDirection[i][1]]=='O'&&
                    board[x+3*searchDirection[i][0]][y+3*searchDirection[i][1]]=='O')
                    {
                        winningFlag=player;
                        return;
                    }
            }
            if (player==2)
            {
                if (board[x+1*searchDirection[i][0]][y+1*searchDirection[i][1]]=='X'&&
                    board[x+2*searchDirection[i][0]][y+2*searchDirection[i][1]]=='X'&&
                    board[x+3*searchDirection[i][0]][y+3*searchDirection[i][1]]=='X')
                    {
                        winningFlag=player;
                        return;
                    }
            }
        }
    }
}

/*
void judgeSearch(int player, int depth, int x, int y)
{
    int i;
    //int j;
    int searchPlaceX;
    int searchPlaceY;
    if (depth==4)
    {
        winningFlag=player;
        return;
    }
    for (i=0;i<8;i++)
    {
        if (depth>=2)
            if (i==7-currentOption)
                continue;
        searchPlaceX=x+searchDirection[i][0];
        searchPlaceY=y+searchDirection[i][1];
        if (isInBound(searchPlaceX,searchPlaceY)&&board[searchPlaceX][searchPlaceY]!=' ')
        {
            if (player==1)
            {
                if (board[searchPlaceX][searchPlaceY]=='O')
                    if (depth==1)
                        currentOption=i;
                    judgeSearch(1,depth+1,searchPlaceX,searchPlaceY);
            }
            if (player==2)
            {
                if (board[searchPlaceX][searchPlaceY]=='X')
                    if (depth==1)
                        currentOption=i;
                    judgeSearch(2,depth+1,searchPlaceX,searchPlaceY);
            }
        }
    }
    return;
}
*/
void computerMove(void)
{
    int option;
    option=rand()%8;
    printf("It\'s my turn, and I would like to put the chess in column %d...\n",option);
    turn(1,option);
}

void humanMove(void)
{
    int option;
    printf("It's your turn. Make your move! Select column from 1 to 8.\n");
    scanf("%d",&option);
    while (option<1||option>8)
    {
        printf("You selected an invalid column. Please try again.\n");
        scanf("%d",&option);
    }
    turn(2,option);
}

void turn(int player,int column)
{
    int i;
    for (i=7;i>0;i--)
    {
        if (board[i][column]==' ')
        {
            if (player==1)
            {
                 board[i][column]='O';
                 break;
            }
            if (player==2)
            {
                board[i][column]='X';
                break;
            }
        }
    }
}

int isInBound(int x, int y)
{
    return x >= 0 && x <= 6 && y >= 0 && y < 8;
}
