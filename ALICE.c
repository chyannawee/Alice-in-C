#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ROWSIZE 15
#define COLSIZE 20
void player1Wins (void);
void player2Wins (void);

int main(void)
{
    int stage, players, randomMoves, dice, level = 0, count = 0;
    int life1 = 5, life2 = 5;
    int row = 0, col = 0;
    int n, m, i, j, k, q, x = 0, y = 0, p = 1;
    int count1 = 0, count2 = 0, mincount;
    int min, temp;
    int numberArray[5];
    int A[ROWSIZE][COLSIZE] = { 0 };
    int ch, lines = 0;
    char response;

    srand(time(NULL));

    printf("------------------------------------------------------\n");
    printf("     Welcome to the Game, Help Alice escape!\n");
    printf("------------------------------------------------------\n");

    //check if stage entered is valid
    do {
        printf("Choose among 3 stages of difficulties:\n");
        printf("1) Beginner\n2) Intermediate\n3) Advanced\n\nStage:");
        scanf("%d", &stage);

        switch (stage)
        {
            case 1: level = 5;
                break;
            case 2: level = 10;
                break;
            case 3: level = 25;
                //A[14][18] = -3;//put trap near end
                break;
            default:
                printf("Error! Please enter a valid stage (1, 2, or 3):\n\n");
                break;
        }
    } while (stage != 1 && stage != 2 && stage != 3);//stage end when user enter a valid number

    //check if number of players entered is valid
    do {
        printf("\nHow many players?\n1) Player vs Computer\n2) Player 1 vs Player 2\n\nPlayers:");
        scanf("%d", &players);
        switch (players)
        {
            case 1:players = 1;
                break;
            case 2:players = 2;
                break;
            default:
                printf("Error! Please enter a valid number of players!\n");
                break;
        }
    } while (players != 1 && players != 2);

    system("cls");

    //to determine how many elements should be generated
    for (j = 1; j <= level; j++) //assigns elements to random arrays
    {
        n = rand() % ROWSIZE;//0-15  //1
        m = rand() % COLSIZE;//0-20  //5
        A[n][m] = -1;//life

        n = rand() % ROWSIZE;
        m = rand() % COLSIZE;
        A[n][m] = -2;//lose life

        n = rand() % ROWSIZE;
        m = rand() % COLSIZE;
        A[n][m] = -3;//Trap

        n = rand() % ROWSIZE;
        m = rand() % COLSIZE;
        A[n][m] = -4;//ladder
    }

    //do not want to generate anything in those arrays
    for (col = 0; col <= 6; col++)
    {
      	A[0][col] = 0;
    }
  

    printf("\nBelow is the game board for this game. Have fun!\n\n");
    while (getchar() != '\n');

    //game elements
    printf("Game elements:\n");
    printf("# = Gain a life\n! = Poison (Lose a life)\n");
    printf("O = Trap (Move backwards a random (1-10) amount of steps)\n");
    printf("H = Ladder (Move forward a random (1-10) amount of steps)\n\n");

    //printing the map
    do {
        A[0][0] = -5;//Start
        A[ROWSIZE - 1][COLSIZE - 1] = -6;//End

        for (i = 0; i < COLSIZE; i++)
        {
            printf("+-----");
        }
        printf("+\n");

        for (row = 0; row <= ROWSIZE - 1; row++)
        {
            for (col = 0; col <= COLSIZE - 1; col++)
            {
                if (A[row][col] == -5)//start
                {
                    printf("|  S  ");
                }
                else if (A[row][col] == -6)//end
                {
                    printf("|  E  ");
                }
                else if (A[row][col] == -1)//life
                {
                    printf("|  #  ");
                }
                else if (A[row][col] == -2)//lose life
                {
                    printf("|  !  ");
                }
                else if (A[row][col] == -3)//trap
                {
                    printf("|  O  ");
                }
                else if (A[row][col] == -4)//ladder
                {
                    printf("|  H  ");
                }
                else if (A[row][col] == -7)//player 1
                {
                    printf("| P1  ");
                }
                else if (A[row][col] == -8)//player 2
                {
                    printf("| P2  ");
                }
                else if (A[row][col] == -10)//player 1 & 2
                {
                    printf("|P1,P2");
                }
                else
                {
                    printf("|     ");
                }
            }

            printf("|\n");
            for (k = 0; k < COLSIZE; k++)
            {
                printf("+-----");
            }
            printf("+\n");
        }

        A[0][y] = 0;
        A[0][x] = 0;

        printf("Press [ENTER] to continue");
        getchar();
        system("cls");

        //player1
        printf("Player 1, press [ENTER] to throw dice: ");
        getchar();
        dice = 1 + (rand() % 6);

        printf("\nDice(Player 1) = %d\n", dice);
        y = y + dice;
        count1 = count1 + dice;

        if (A[0][y] == -1)//life
        {
            life1++;
            printf("Player 1 has landed on a life!\n");
            printf("Player 1 gets a life!\n");
        }
        if (A[0][y] == -2)//lose life
        {
            life1--;
            printf("Player 1 has landed on some poison!\n");
            printf("Player 1 lost a life!\n");
        }
        if (A[0][y] == -3 || y > 299)//trap
        {
            randomMoves = 1 + (rand() % 10);
            y = y - randomMoves;
            printf("Player 1 has landed on a trap!\n");
            printf("Player 1 took %d steps back!\n", randomMoves);
            count1 = count1 + randomMoves;
        }
        if (A[0][y] == -4)//ladder
        {
            randomMoves = 1 + (rand() % 10);
            y = y + randomMoves;
            printf("Player 1 has landed on a ladder!\n");
            printf("Player 1 took %d steps forward!\n", randomMoves);
            count1 = count1 + randomMoves;
        }

        printf("Player 1 has %d lives\n", life1);

        if (A[0][y] == -6)//reaches the end
        {
            count = -9;
            player1Wins();
        }
        if (life1 == 0)//run out of life
        {
            count = -9;
            printf("--------------\n");
            printf("Player 1 lost!\n");
            printf("--------------\n\n");
        }

        A[0][y] = -7;

        //dont execute anything below it if player 1 wins

        if (count == -9)
        {
            break;
        }

        //player2
        if (players == 2)
        {
            printf("\nPlayer 2, press [ENTER] to throw dice: ");
            getchar();
        }

        dice = 1 + (rand() % 6);
        printf("\nDice(Player 2) = %d\n", dice);
        x = x + dice;
        count2 = count2 + dice;

        if (A[0][x] == -1)//life
        {
            life2++;
            printf("Player 2 has landed on a life!\n");
            printf("Player 2 gets a life!\n");
        }
        if (A[0][x] == -2)//lose life
        {
            life2--;
            printf("Player 2 has landed on some poison!\n");
            printf("Player 2 lost a life!\n");
        }
        if (A[0][x] == -3 || x > 299)//trap
        {
            randomMoves = 1 + (rand() % 10);
            x = x - randomMoves;
            printf("Player 2 has landed on a trap!\n");
            printf("Player 2 took %d steps back!\n", randomMoves);
            count2 = count2 + randomMoves;
        }
        if (A[0][x] == -4)//ladder
        {
            randomMoves = 1 + (rand() % 10);
            x = x + randomMoves;
            printf("Player 2 has landed on a ladder!\n");
            printf("Player 2 took %d steps forward!\n", randomMoves);
            count2 = count2 + randomMoves;
        }

        printf("Player 2 has %d lives\n\n", life2);

        if (A[0][x] == -6)//reaches the end
        {
            count = -9;
            player2Wins();
        }

        if (life2 == 0)//run out of lives
        {
            count = -9;
            printf("--------------\n");
            printf("Player 2 lost!\n");
            printf("--------------\n\n");
        }

        A[0][x] = -8;

        //if both players land at end at the same time must check who took the least step
        if (x == 299 && y == 299)
        {
            if (count2 > count1)
            {
                player1Wins();
            }

            else
            {
                player2Wins();
            }
        }
        //if both players land on the same cell
        if (x == y)
        {
            A[0][y] = -10;
            A[0][x] = -10;
        }

    } while (count != -9);//until someone wins the game

    printf("Player 1 took %d steps and has %d lives left\n", count1, life1);
    printf("Player 2 took %d steps and has %d lives left\n\n", count2, life2);

    if (count1<count2)
    {
        mincount = count1;
    }
    else{
        mincount = count2;
    }

    //FIlE PROCESSING STARTS HERE
    FILE *file;

    // Open the file for writing
    file = fopen("records.txt", "a+");
    if (!file)
    {
        printf("File could not be opened\n\a\a");
        getchar();
    }
    else{
        // Save data
        fprintf(file, "%d\t\n", mincount);
    }

    fclose(file);

    //Read data
    file = fopen("records.txt", "r+");

    /*Start do while loop*/
    do
    {
        /*Get current character of the file and store in ch*/
        ch = fgetc(file);

        /*Check if ch is equal to newline character*/
        if( ch== '\n')
        /*If ch is a newline character then increment the line counter by one*/
            lines++;
    }while(ch != EOF);

    int z=1;

    if ((file = fopen("records.txt", "r"))) {
        while (fscanf(file, "%d", &numberArray[z]) != EOF) {
            ++z;
        }
    }

    for (p = 1; p <= lines; p++)
    {
        min = p;
        for (q = p+1; q <= lines; q++)
        {
            if (numberArray[q] < numberArray[min])
                min = q;
        }
        temp = numberArray[p];
        numberArray[p] = numberArray[min];
        numberArray[min] = temp;
    }

    printf ("High Scores:\n");

    for (p = 1; p <= 5; p++)
    {
        printf("%d: %d\n\n",p, numberArray[p]);
    }

    // Close the file
    fclose(file);

    do{
        printf ("Reset data? (Y or N)\n");
        response = getchar();

        switch (response)
        {
            case 'Y':case 'y':
                file = fopen("records.txt","w");
                printf("\nThank you for playing, see you next time!\n\n");
                break;
            case 'N':case 'n':
                printf("\nThank you for playing, see you next time!\n\n");
                break;
        }

    }while(response!='Y' && response!='y' && response!='N' && response!='n');


    return 0;
}

void player1Wins (void)
{
    printf("\n-----------------------\n");
    printf("Player 1 wins the game!\n");
    printf("-----------------------\n\n");
}

void player2Wins (void)
{
    printf("--------------\n");
    printf("Player 2 wins the game!\n");
    printf("--------------\n\n");
}



