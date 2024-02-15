#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <stdbool.h>
#include <time.h>  //  random number generator

#define ENTER 13
#define WIDTH 80
#define HEIGHT 25

  //  Global variable decleration
int X1_cord = 30, Y1_cord = 2;
int Head_X, Head_Y;
int Tail_X[200], Tail_Y[200];
int Tail_length = 0;
int Fruit_X, Fruit_Y;
int Score, Life, speed=0;
bool Game_over;

enum Direction 
{
    STOP, LEFT, RIGHT, UP, DOWN
} dir;

   // Function prototype
void Register(void);
void accountcreated(void);
void Login(void);
void instructions(void);
void load(void);
void setup();
void gotoxy();
void border();
void direction();
void bendLogic();
void delay(unsigned int milliseconds);




// Simple delay using for loop
void delay(unsigned int milliseconds) {
    for (unsigned int i = 0; i < milliseconds * 10000; i++) {
        // Do nothing
    }
}



// Declaring gotoxy function
// cursor position at a specific location on the screen
void Gotoxy(int x, int y)
{
    COORD c;
    c.X = x;
    c.Y = y;
 
    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE), c);
}

typedef struct setup
{
    char name[50];
    char email[30];
    char password1[20];
    char password2[20];
    int number;
} reg;

void Register()
{
    struct setup set;
    FILE *reg_file;
    int i = 0, n;
    char ch1, ch2;

    reg_file = fopen("login_register.txt", "ab");

    if (reg_file == NULL)
    {
        printf("\n\n\t\t\tError in opening file");
        exit(1);
    }
    else
    {
        printf("\n\n\t\t\t WELCOME TO REGISTER ZONE");
        printf("\n\t\t\t ~~~~~~~~~~~~~~~~~~~~~~~~\n");
        fflush(stdin);
        printf("\n\t\t\tEnter your full name:\t\t");
        gets(set.name);
        printf("\n\t\t\tEnter your email:\t\t");
        gets(set.email);
        printf("\n\t\t\tEnter your phone number:\t");
        scanf("%d", &set.number);
        fflush(stdin); // To hold buffer
        printf("\n\t\t\tCreate a password:\t\t");

        // Read password character by character until ENTER is pressed or space is encountered
        while (1)
        {
            ch1 = getch();
            if (ch1 == 13 || ch1 == ' ')
            {
                set.password1[i] = '\0';
                break;
            }
            else if (ch1 == '\b')
            {
                if (i > 0)
                {
                    i--;
                    printf("\b \b");
                }
            }
            else
            {
                set.password1[i++] = ch1;
                printf("* \b");
            }
        }
        i = 0;
        printf("\n\n\t\t\tConfirm your password:\t\t");
        while (1)
        {
            ch2 = getch();
            if (ch2 == 13 || ch2 == ' ')
            {
                set.password2[i] = '\0';
                break;
            }
            else if (ch2 == '\b')
            {
                if (i > 0)
                {
                    i--;
                    printf("\b \b");
                }
            }
            else
            {
                set.password2[i++] = ch2;
                printf("* \b");
            }
        }
        if (strcmp(set.password1, set.password2) != 0)
        {
            system("cls");
            fflush(stdin);
            printf("\n\n\t\t\tINVALID PASSWORD");
            Register();
        }

        fwrite(&set, sizeof(set), 1, reg_file);
    }

    fclose(reg_file); // Close the file when done
    Gotoxy(WIDTH/2 , HEIGHT/2);
    printf("Press 'Enter' key to confirm registration");
    accountcreated(); // Calling another function after successfull register
    
   
}

// Successful account creation
void accountcreated(void)
{
    int i,n;
    system("cls");
    Gotoxy(WIDTH/2 , HEIGHT/2);
    printf("PLEASE WAIT,YOUR REQUEST IS PROCESSING");
    for (i = 0; i < 4; i++)
     {
        delay(100000);
        printf(".");
    }
    system("cls");
    Gotoxy(WIDTH/2 , (HEIGHT/2 +2));
    printf("REGISTERED  SUCCESSFULLY....");
    Gotoxy(WIDTH/2 , (HEIGHT/2 +4));
    printf(">>Press 1 for login");
    Gotoxy(WIDTH/2 , (HEIGHT/2 +5));
    printf(">>Press 2 for exit");
    Gotoxy(WIDTH/2 , (HEIGHT/2 +6));
    printf(">> ");
    scanf("%d", &n);

    switch (n)
    {
    case 1:
        system("cls");
        Login();
        break;
    case 2:
        system("cls");
        Gotoxy(WIDTH/2 , HEIGHT/2);
        printf("PLEASE WAIT,YOUR REQUEST IS PROCESSING");
        for (i = 0; i < 4; i++)
        {
        delay(100000);
        printf(".");
       }

       Gotoxy(WIDTH/2 , (HEIGHT/2 +2));
       printf("THANK YOU FOR REGISTERING....!!!");
       getch();
    //    fflush(stdin);
       exit(0);
       Gotoxy(10, 10);
        break;
    }

 
}


void Login()
{
    reg set; // Added the 'reg' structure variable
    FILE *login;
    char email_id[30], paswd[20], ps;
    int i = 0;
    int check_email = 1, check_paswd = 1; // Initialize with a non-zero value to enter the loop

    printf("\n\n\t\t\tWELCOME TO LOGIN ZONE");
    printf("\n\n\t\t\t~~~~~~~~~~~~~~~~~~~~~");
    printf("\n\n\t\t\tENTER YOUR E-MAIL:\t");
    scanf("%s", email_id);
    printf("\n\n\t\t\tENTER YOUR PASSWORD:\t");

    while (1)
    {
        ps = getch();
        if (ps == 13 || ps == ' ')
        {
            ps = '\0';
            break;
        }
        else if (ps == '\b')
        {
            if (i > 0)
            {
                i--;
                printf("\b \b");
            }
        }
        else
        {
            paswd[i++] = ps;
            printf("* \b");
        }
    }
    paswd[i] = '\0'; // Null-terminate the password string
    printf("\n\n\tYou entered: %s\n", paswd);

    login = fopen("login_register.txt", "rb");
    if (login == NULL)
    {
        printf("\n\n\t\t\tFile not found");
    }
    else
    {
        while (fread(&set, sizeof(set), 1, login))
        {
            check_email = strcmp(set.email, email_id);
            check_paswd = strcmp(set.password1, paswd);

            if (check_email == 0 && check_paswd == 0)
            {
                system("cls");
                Gotoxy(WIDTH/2,HEIGHT/2);
                 printf("PLEASE WAIT,YOUR DATA IS PROCESSING");

                //  delay(20000000); // Calling another function
                 
                    for (i = 0; i < 4; i++)
                  {
                      delay(100000);
                      printf(".");
                  }

                Gotoxy(WIDTH/2 , (HEIGHT/2 +2));
                printf("LOGIN SUCCESSFULLY...!!");
                Gotoxy(WIDTH/2 , (HEIGHT/2 +4));
                printf("Press any key to continue ");
                getch();
                system("cls");
                instructions();
               
                break;
            }
        }

        if (check_email != 0 || check_paswd != 0)
        {
            system("cls");
            printf("\n\n\t\t\tInvalid email or password.\n");
            printf("\n\n\t\t\t> Press 'y' to re-login or any other key to register: ");
            if (getch() == 'y' || getch() == 'Y')
            {
                system("cls");
                Login();
            }
            else
            {
                system("cls");
                Register();
            }
        }

        fclose(login); // Close the file when done
        getch();
    }
}

void instructions()
{

     printf("\n\n\t\t\tWELCOME TO HUNGRY-SNAKE\n");
     printf("\n\tGame instructions:");
     printf("\n\n\t-> Use arrow key to move the snake (LEFT,RIGHT,UP,DOWN)");
     printf("\n\t-> You will be provided foods at the several coordinate of the screen which you have to eat.\n\t   Everytime you eat the length of snake will be increased by 1 tail and thus the score.");
     printf("\n\t-> Here you are provided with three lives. Your life will decrease as you hit the wall or snake's body.\n\t-> YOu can exit the game in its middle by pressing any key mainly ESC key.");
     printf("\n\n\t\t\tPress any key to play game....");
                 
        if(getch()==27)
             exit(0);

     system("cls");

    load();

}


void load()
{
    int row,col;
     system("color 02");
    Gotoxy(40,15);
    printf(" loading...");
    Gotoxy(35,16);
    for( row=1; row<=20 ; row++)
    {
        for(col=0 ; col<=100000000 ; col++); // To dispaly the character slowly
        printf("%c",177);
    }

   
    // getch();
}

int main()
{
    system("color 20");
    printf("\n\n\t\t\t WELCOME TO WORMS-ZONE");
    printf("\n\t\t\t ~~~~~~~~~~~~~~~~~~~~~");
    printf("\n\n\t\tDeveloped by TEAM CRUSADERS");
    printf("\n\t\t\t-> ARUN ARYAL");
    printf("\n\t\t\t-> INTAF MALIK");
    printf("\n\t\t\t-> ARYAN THAPA");
    printf("\n\t\t\t-> AARYA DAHAL");
    printf("\n\n\t\t Press 'ENTER' key to continue...!!");
    getchar(); // Use getchar() to wait for the Enter key
    system("cls");

    printf("\n\n\t\t\t1.REGISTER\t\t2.LOGIN");
    printf("\n\n\t\t\tEnter your choice:  ");
    int n;
    scanf("%d", &n);

    switch (n)
    {
    case 1:
        system("cls");
        Register();
        break; // Don't forget to break after each case
    case 2:
        system("cls");
        Login();
        break;
    default:
        printf("\nInvalid choice\n");
    }
     
    system("color 20");
    srand(time(NULL));
    setup();
    
    while (!Game_over) {
        system("cls");
        border();
        direction();
        bendLogic();
        Sleep(150+speed);
    }

    system("cls");
    fflush(stdin);
    // gotoxy(X1_cord + (WIDTH / 2), Y1_cord + (HEIGHT / 2));
    gotoxy(WIDTH/2 , HEIGHT/2);
    printf("GAME OVER!!!");
    gotoxy(WIDTH/2 , HEIGHT/2+2);
    printf("Your Score : %d",Score);
    getch();

    return 0;
}


void setup() {
    Game_over = false;
    Life = 3;
    Head_X = WIDTH / 2;
    Head_Y = HEIGHT / 2;
    Fruit_X = rand() % (WIDTH - X1_cord-2)+X1_cord+1;
    Fruit_Y = rand() % (HEIGHT - Y1_cord-2)+Y1_cord+1;
    Score = 0;
}


void gotoxy(int x, int y)
 {
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}


void border() {
    int i, j;
    gotoxy((X1_cord + WIDTH - 8), Y1_cord - 1);
    printf("LIFE: %d", Life);

    gotoxy(X1_cord, Y1_cord);
    for (i = 0; i < WIDTH; i++)
        printf("%c", 33); // Top border

    for (i = 0; i < HEIGHT - 2; i++) {
        gotoxy(X1_cord, Y1_cord + i + 1);

        for (j = 0; j < WIDTH; j++) {
            if (j == 0 || j == WIDTH - 2)
                printf("%c", 33); // Left and Right borders

            if (i == Head_Y && j == Head_X)
                printf("O");
            else if (i == Fruit_Y && j == Fruit_X)
                printf("%c", 248);
            else {
                bool isTailPrinted = false;
                for (int k = 0; k < Tail_length; k++) {
                    if (Tail_X[k] == j && Tail_Y[k] == i) {
                        printf("*");
                        isTailPrinted = true;
                        break;
                    }
                }
                if (!isTailPrinted)
                    printf(" ");
            }
            // else 
            //    printf(" ");
        }
    }

    gotoxy(X1_cord, Y1_cord + HEIGHT - 2);
    for (i = 0; i < WIDTH; i++)
        printf("%c", 33); // Bottom border

    gotoxy(X1_cord, Y1_cord + HEIGHT - 1);
    printf("Score: %d\n", Score);
}


void direction() {
    if (_kbhit())   // Keyboard key has been pressed
    {
        switch (_getch())  // Read a character from the keyboard input
        {
            case 75:  // Left arrow key
                dir = LEFT;
                break;
            case 77:  // Right arrow key
                dir = RIGHT;
                break;
            case 72: // Up arrow key
                dir = UP;
                break;
            case 80:  // Down arrow key
                dir = DOWN;
                break;
            case 27: // ESC key
                Game_over = true;
                break;
        }
    }
}


void bendLogic() {
    int first_tailX = Tail_X[0], first_tailY = Tail_Y[0];
    int second_tailX, second_tailY;
    Tail_X[0] = Head_X;   // Swapping the ccordinate of snake head to its 1st tail
    Tail_Y[0] = Head_Y;

    // After the formation of 2 tails excluding head the coordinate of head swap to tail which is Tail_X & Tail_Y is the 1st tail of snake 
     // and  first_tailX & first_tailY is the 2nd tail parts of snake where as second_tailX & second_tailY is the 3rd tail part of snake.

     // Tail swapping logic

    for (int i = 1; i < Tail_length; i++)
     {
        second_tailX = Tail_X[i];
        second_tailY = Tail_Y[i];
        Tail_X[i] = first_tailX;
        Tail_Y[i] = first_tailY;
        first_tailX = second_tailX;
        first_tailY = second_tailY;
    }

    switch (dir)   // Updating the head's position
    {
        case LEFT:
            Head_X--;
            break;
        case RIGHT:
            Head_X++;
            break;
        case UP:
            Head_Y--;
            break;
        case DOWN:
            Head_Y++;
            break;
    }

     // Boundary checking 
     // If the head goes beyond the boundaries, it wraps around to the opposite side of the screen

      
    if(Head_X >= WIDTH-2 || Head_X < 0 || Head_Y >= HEIGHT || Head_Y == Y1_cord-2 )
    {
        Life--;
        Head_X=WIDTH/2;
        Head_Y=HEIGHT/2;
    }

    if (Life <= 0) {
        Game_over = true;
    }

    // Self-collision detection
    for (int i = 0; i < Tail_length; i++) {
        if (Tail_X[i] == Head_X && Tail_Y[i] == Head_Y) 
        {
            Game_over = true;
        }
    }


   // Colision-detection  snake's head with fruit

    if (Head_X == Fruit_X && Head_Y == Fruit_Y)  // Matches coordinate of head and fruit 
    {
        Score += 5;
        speed += 20;
        Fruit_X = rand() % (WIDTH -X1_cord-2) + X1_cord;
        Fruit_Y = rand() % (HEIGHT -Y1_cord-2) + Y1_cord;
        Tail_length++;  // Increasing  the length of snake
    }
}



