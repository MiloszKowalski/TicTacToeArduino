#include <stdio.h>
#include <stdbool.h>

    char grid[8][8];
    char currentPlayer = 'a';
    bool isOver = false;
    bool isValid;
    char used[9];
    char answers[] = {'A','B','C','D','E','F','G','H','I'};
    char answer;
    int roundNumber = 1;


//Projecting the grid
void Project()
{
    for(int i=1; i<9; i++)
    {
        for(int j=1; j<9; j++)
        {
            //If the number is divisible by 3
            if(j%3==0 || i%3==0)
                grid[i-1][j-1] = 'z';
        }
        printf("\n");
    }
}

//Displaying grid on screen
void Draw()
{
    //Clear console window
    system("cls");
    for(int i=0; i<8; i++)
    {
        for(int j=0; j<8; j++)
        {
            //Drawing grid
            if(grid[i][j]=='z')
                printf("#");
            //Drawing fields
            else
                printf("%c",grid[i][j]);
        }
        printf("\n");  
    }
    printf("\n");
    //Displaying the number of the round
    printf("Runda %i \n", roundNumber);
}

//Checking if the answer is valid and never used
void CheckUsed()
{
    bool answerValid = false;
    bool found = false;
    for(int i=0;i<9;i++)
    {
       if(answer==used[i])
           found = true;
    }
    for(int i=0;i<9;i++)
    {
        if(answer==answers[i])
            answerValid = true;
    }
    //If the field is already filled
    if(found == true)
    {
        getchar();
        printf("Pole jest zajete! Wybierz pole na ktorym chcesz postawic znak: ");
        isValid = false;
    }
    //If the answer is invalid character
    else if(answerValid == false)
    {
        getchar();
        printf("Niepoprawne pole! Wybierz pole na ktorym chcesz postawic znak: ");
        isValid = false;
    }
    else
        isValid = true;
}

//Setting the field based on the specified coordinates
void SetField(int a, int b)
{
    grid[a][b] = currentPlayer;
    grid[a][b+1] = currentPlayer;
    grid[a+1][b] = currentPlayer;
    grid[a+1][b+1] = currentPlayer;
}

//Getting user's input and changing the fields
void Logic()
{
    printf("Wybierz pole na ktorym chcesz postawic znak: ");
    scanf("%c", &answer);
    CheckUsed();
    while(!isValid)
    {
        scanf("%c", &answer);
        CheckUsed();
    }
    
    switch(answer)
    {
        case 'A':
            SetField(0,0);
            used[0] = 'A';
        break;
        case 'B':
            SetField(0,3);
            used[1] = 'B';
        break;
        case 'C':
            SetField(0,6);
            used[2] = 'C';
        break;
        case 'D':
            SetField(3,0);
            used[3] = 'D';
        break;
        case 'E':
            SetField(3,3);
            used[4] = 'E';
        break;
        case 'F':
            SetField(3,6);
            used[5] = 'F';
        break;
        case 'G':
            SetField(6,0);
            used[6] = 'G';
        break;
        case 'H':
            SetField(6,3);
            used[7] = 'H';
        break;
        case 'I':
            SetField(6,6);
            used[8] = 'I';
        break;
    }
}

//Changing current player
void ChangePlayer()
{
    if(currentPlayer == 'a')
        currentPlayer = 'b';
    else
        currentPlayer = 'a';
}

//Checking if one of the players won
void CheckWin()
{
    if(
    //Check horizontal
    (grid[0][0]=='a'&&grid[0][3]=='a'&&grid[0][6]=='a') ||
    (grid[3][0]=='a'&&grid[3][3]=='a'&&grid[3][6]=='a') ||
    (grid[6][0]=='a'&&grid[6][3]=='a'&&grid[6][6]=='a') ||
    //Check vertical
    (grid[0][0]=='a'&&grid[3][0]=='a'&&grid[6][0]=='a') ||
    (grid[0][3]=='a'&&grid[3][3]=='a'&&grid[6][3]=='a') ||
    (grid[0][6]=='a'&&grid[3][6]=='a'&&grid[6][6]=='a') ||
    //Check diagonal
    (grid[0][0]=='a'&&grid[3][3]=='a'&&grid[6][6]=='a') ||
    (grid[0][6]=='a'&&grid[3][3]=='a'&&grid[6][0]=='a')
    )
    {
        Draw();
        isOver = true;
        printf("A wygralo! \n");
    }
    else if(
    //Check horizontal
    (grid[0][0]=='b'&&grid[0][3]=='b'&&grid[0][6]=='b') ||
    (grid[3][0]=='b'&&grid[3][3]=='b'&&grid[3][6]=='b') ||
    (grid[6][0]=='b'&&grid[6][3]=='b'&&grid[6][6]=='b') ||
    //Check vertical
    (grid[0][0]=='b'&&grid[3][0]=='b'&&grid[6][0]=='b') ||
    (grid[0][3]=='b'&&grid[3][3]=='b'&&grid[6][3]=='b') ||
    (grid[0][6]=='b'&&grid[3][6]=='b'&&grid[6][6]=='b') ||
    //Check diagonal
    (grid[0][0]=='b'&&grid[3][3]=='b'&&grid[6][6]=='b') ||
    (grid[0][6]=='b'&&grid[3][3]=='b'&&grid[6][0]=='b')
    )
    {
        Draw();
        isOver = true;
        printf("B wygralo! \n");
    }
}

//If it's a draw
void CheckGameOver()
{
    roundNumber++;
    if(roundNumber >= 10 && isOver == false)
    {
        Draw();
        isOver = true;
        printf("Gra sie skonczyla! Nikt nie wygral! \n");
    }
}

int main(int argc, char **argv)
{
    Project();
    while(!isOver)
    {
        Draw();
        Logic();
        CheckWin();
        CheckGameOver();
        ChangePlayer();
        //Getting the character so the code slows down
        //otherwise it did the loop a few times without
        //getting user input
        getchar();
    }
	return 0;
}