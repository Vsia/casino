//Vallesia Pierre Louis
//COP3223 



#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include<string.h>
#include "casino.h"

//Global variables
#define SLOTS 1
#define SCRATCH 2
#define BLACKJACK 3

//Constants for Black Jack
#define FACES 13
#define SUITS 4
#define CLUBS 0
#define DIAMONDS 1
#define HEARTS 2
#define SPADES 3
#define BUST 21

//Constants for game Scratch Off
#define ONE 1
#define TWO 2
#define FIVE 5
#define BONUS 20
//Function declaration
//Function prototypes
void welcomeScreen();
int displayMenu();
void clearScreen();

//Scratch off prototypes
int playSlots();
int playScratchOffs();
int playBlackJack();
char randomSymbol();


//Black jack function prototypes
void initializeUsed(char used [SUITS][FACES]);
void printDeck(char deck [SUITS][FACES]);
void initializeDeck(char deck [SUITS][FACES]);
int deal(char deck[SUITS][FACES], char used[SUITS][FACES]);
int results(int playerScore, int dealerScore);

//Scratch offs function prototypes
struct OneDollar createScratchOffOne(struct OneDollar oneSo);
void displayScratchOffOne(struct OneDollar oneSo);

struct TwoDollar createScratchOffTwo(struct TwoDollar twoSo);
void displayScratchOffTwo(struct TwoDollar two);

struct FiveDollar createScratchOffFive(struct FiveDollar five );
void displayScratchOffFive(struct FiveDollar five );

//Casino 5 scratch  off prototypes

int cashOneDollar(struct OneDollar one);
int cashTwoDollar(struct TwoDollar two);
int cashFiveDollar(struct FiveDollar five);
char getBonus();

//Struct for Scratch Offs
typedef struct OneDollar
{
    int winNumbers;
    int numbers[5];
    float prizes[5];
    char bonus[2];
} oneSo; // variable for strut
typedef struct TwoDollar
{
    int winNumbers[2];
    int numbers[10];
    float prizes[10];
    char bonus[2];
} twoSo; //struct variable
typedef struct FiveDollar
{
    int winNumbers[4];
    int numbers[12];
    float prizes[12];
    char bonus[4];
} fiveSo; // struct variable

//Main function
int main ()
{
    //local variable play
    int play =1;
    //Seed the random function
    srand(time(0));
    //Declare variable cash as data type integer with value 1000
    int cash = 1000;
    // Variable to store the selected game
    int game;
    // call function welcomeScreen
    welcomeScreen();
    //while loop whule variable play is true
    while (play==1)
    {
        // call function clearScreen
        clearScreen();
        //Call selectedGame
        game = displayMenu();
        //CAll function clearScreen after displayMenu;
        clearScreen();

        //Write a switch statement and pass variable cash as an argument for each
        switch(game)
        {
        case SLOTS:
            cash= playSlots(cash);
            break;
        case SCRATCH:
            cash = playScratchOffs(cash);
            break;
        case BLACKJACK:
            cash= playBlackJack(cash);
            break;
        case EXIT:
            game=0;
            return 0;
            break;
        }
        printf("Your cash balance is %d\n",cash);
        printf(" Would you like to play another game? (1 =Yes, 0= No)\n");
        scanf("%d", &play);
    }
    return 0;
}
//Welcome screen
void welcomeScreen()
{
    printf("\t\t##########################################################\n");
    printf("\t\t##########################################################\n");
    printf("\t\t############                                  ############\n");
    printf("\t\t############          Knights Casino          ############\n");
    printf("\t\t############                                  ############\n");
    printf("\t\t##########################################################\n");
    printf("\t\t##########################################################\n");
}
//Clear screen function
void clearScreen()
{
    printf("\n\t\t\t\t <Hit Enter to continue>\n\n");
    //Declare a variable of data type char e
    char e;
    //Getting info from user
    scanf("%c",&e);
    //Windows clear screen;
    system("cls");
    //Unix clear screen
    //system("clear");
}
//Casino menu
int displayMenu()
{
    //Declare variable to store user selection
    int game;
    //Do while loop
    do
    {
        printf("Select a game to play by entering the number next to the game\n");
        printf("%d Slots\n", SLOTS);
        printf("%d Scratch Offs\n", SCRATCH);
        printf("%d Black Jack\n", BLACKJACK);
        printf("%d Quit\n ",EXIT);
        scanf("%d", &game);

        // While condition validate the user's input is less than SLOTS or greater than BLACKJACK.
    }
    while((game < SLOTS) || (game > EXIT));
    return game;
}
int playSlots(int cash)
{
    const int BET = 5; //constant for bet amount
    const int MATCH_TWO = 5; // constant for payout
    const int MATCH_THREE = 50; // constant for payout
    int play = 1; //Integer for loop control
    char symOne, symTwo,symThree; // 3 character variables for symbols;
    //welcome
    printf("Let's play the slot machine!\n");
    printf("\n");
    // Rules of the game
    printf("Your cash balance is $%d. The bet is $%d.\n", cash,BET);
    printf("Match two symbols to win $5.\n");
    printf("Match all three symbols to win $50.\n");
    printf("\n");
    //If statement to determine of the player's cash balance is enough
    if( cash <5 )
    {
        play =0;
    }
    while(play==1)
    {
        cash -= BET;
        printf("Spinning...\n");
        //Set the characters to the randomSymbol function
        symOne = randomSymbol();
        symTwo = randomSymbol();
        symThree = randomSymbol();
        printf("\n%c %c %c\n",symOne,symTwo,symThree);
        //If else statement to provide the player's results
        if((symOne == symTwo )&& (symTwo ==symThree))
        {
            cash += MATCH_THREE;
            printf("Three symbols matched\n");
            printf("You've won $50!\n");
        }
        else if((symOne== symTwo) || (symOne ==symThree)|| ( symTwo == symThree) )
        {
            cash += MATCH_TWO;
            printf("Two symbols matched!\n");
            printf("You've won $5!\n");
        }
        else
        {
            printf("No symbols matched\n");
            printf("You've won $0 dollars!");
            cash += 0;
        }
        //The player's cash balance
        printf("Your cash balance is $%d \n", cash);
        //Evaluate player's cash
        if(cash >= 5)
        {
            printf("\nWould you like to spin again (Yes =1, No =0)? ");
            scanf("%d",&play);
        }
        else
        {
            break;
        }
    }
    printf("Thank you for playing slots at Knights Casino. Your cash out is $%d\n", cash);
    return cash;
}
//Random symbol function for spinning screen
char randomSymbol()
{
    const int SYMBOLS = 6;
    const char symbols[6]= {'$', '%', '&','#','@','!'};
    char symbol;
    int num =0 ;//Integer variable to store random value
    num= rand() %6 ;

    switch(num)
    {
    case 0:
        symbol = symbols[0];
        break;
    case 1:
        symbol = symbols[1];
        break;
    case 2:
        symbol = symbols[2];
        break;
    case 3:
        symbol = symbols[3];
        break;
    case 4:
        symbol = symbols[3];
        break;
    case 5:
        symbol = symbols [4];
        break;
    }
    return symbol;
}
//Scratch offs game
int playScratchOffs(int cash)
{
    //local variable
    int play=1;
    struct OneDollar oneSo;
    struct TwoDollar twoSo;
    struct FiveDollar fiveSo;
    int type; //Variable to store type of scratch off game
    int count;//Variable to store the number of scratch offs
    int c; //loop control
    //Rules of the game
    printf("Let's play scratch off tickets!\n");
    printf("Players can select from One Dollar, Two Dollar, and Five Dollar tickets\n");
    printf("Prizes are based on the ticket selected\n");
    //Prompt the user for the type of scratch off
    //while loop based on play being true
    while (play ==1)
    {
        printf("Which type of scratch off would you like\n");
        printf("(%d= One Dollar, %d= Two Dollar, %d=Five Dollar)?\n", ONE,TWO,FIVE);
        scanf("%d",&type);
        printf("How many scratch offs would you like?\n");
        scanf("%d",&count);
        printf("Getting you scratch offs...\n");

        //for loop for the number of scratch offs
        for(c=0; c<count; c++)
        {
            switch(type)
            {
            case ONE:
                if(cash >= ONE)
                {
                    cash -= ONE;
                    oneSo = createScratchOffOne(oneSo);
                    displayScratchOffOne(oneSo);
                    cash += cashOneDollar(oneSo);
                    break;
                }
                else
                {
                    printf("You don't have enough cash to play.\n");
                    c= count;
                    break;
                }
            case TWO:
                if(cash >= TWO)
                {
                    cash -= TWO;
                    twoSo = createScratchOffTwo(twoSo);
                    displayScratchOffTwo(twoSo);
                    cash += cashTwoDollar( twoSo);
                    break;
                }
                else
                {
                    printf("You don't have enough cash to play.\n");
                    c= count;
                    break;
                }
            case FIVE:
                if(cash >= FIVE)
                {
                    cash += FIVE;
                    fiveSo = createScratchOffFive(fiveSo);
                    displayScratchOffFive(fiveSo);
                    cash += cashFiveDollar(fiveSo);
                    break;
                }
                else
                {
                    printf("You don't have enough cash to play.\n");
                    c= count;
                    break;
                }
            }
        }
    }
    return cash;
}
// Function for the scratch off one

struct OneDollar createScratchOffOne(struct OneDollar oneSo)
{
    int usedSyms[]= {0,0,0,0,0,0};
    int used=0;
    //Constants
    const int SYMS =2; //bonus symbols
    const int NUMS=5; //number of player numbers and prizes
    const int BASE =20;
    //Constant character array
    const char SYMBOLS[6] = {'$','%','&','#','@','!'};
    int sym; //for random symbol
    int n; //loop control
    //Random winning number
    oneSo.winNumbers= (rand()% BASE)+1;

    //Player's number random generation
    for(n=0; n<NUMS; n++)
    {
        oneSo.numbers[n]= (rand()%BASE)+1;
    }
    //for loop that will loop 5 times
    for(n=0; n<NUMS; n++)
    {
        oneSo.prizes[n]= (float)(((rand() % BASE)+1 )*5);
    }

    //for loop for two bonus symbols
    for(n=0; n<SYMS; n++)
    {
        sym = rand() %(sizeof(SYMBOLS) / sizeof(SYMBOLS[0]));
        used =0;
        while(!used)
        {


            switch(sym)
            {
            case 0:
                oneSo.bonus[n]=SYMBOLS[0];
                //used =0;
                break;
            case 1:
                oneSo.bonus[n]=SYMBOLS[1];
                break;
            case 2:
                oneSo.bonus[n]=SYMBOLS[2];
                break;
            case 3:
                oneSo.bonus[n]=SYMBOLS[3];
                break;
            case 4:
                oneSo.bonus[n]=SYMBOLS[4];
                break;
            case 5:
                oneSo.bonus[n]=SYMBOLS[5];
                break;
            }

            if(usedSyms[sym] ==0)
            {

                usedSyms[n]=1; // to indicate used
                used =1;
                break;
            }
        }

    }
    return oneSo;
}
//Display scratch off one
void displayScratchOffOne( struct OneDollar oneSo)
{
    int n;
    const int NUMS=5;
    const int SYMS =2;
    printf("+------------------------------------------+\n");
    printf("| WINNING NUMBER        %2d%17s|\n",oneSo.winNumbers," ");
    printf("| %41s|\n", " ");
    printf("| YOUR NUMBERS %28s|\n|"," ");
    for(n=0; n<NUMS; n++)
    {
        printf("%8d",oneSo.numbers[n]);
    }
    printf("  |\n");
    printf("|%42s|\n"," ");
    printf("| PRIZES%35s|\n"," ");
    printf("|%42s|\n|"," ");

    for (n=0; n<NUMS; n++)
    {
        printf("%8.2f", oneSo.prizes[n]);
    }
    printf("  |\n|%42s|\n"," ");
    printf("| SYMBOLS%34s|\n"," ");
    printf("| %41s|\n|","  ");
    for(n=0; n<SYMS; n++)
    {
        printf("%8c",oneSo.bonus[n]);
    }
    printf("                          |\n");
    printf("|                                          |\n");
    printf("+------------------------------------------+\n"," ");
}
struct TwoDollar createScratchOffTwo(struct TwoDollar twoSo)
{


    const int SYMS=2;
    const int NUMS=10;
    const int BASE =30;
    const char SYMBOLS[6] = {'$','%','&','#','@','!'};
    int sym; //for random symbol
    int n; //loop control

    //keeping tract of used symbols
    int usedSyms[]= {0,0,0,0,0,0};
    int usedNums[]= {0,0,0,0,0,0};
    int num;
    int used =0;

    for(n=0; n<SYMS; n++)
    {
        used =0;
        while(used ==0)
        {
            num=(rand ()%BASE) +1;
            if(usedNums[num] ==0)
            {
                usedNums[num] =1;
                twoSo.winNumbers[n] = num;
                used =1;
                break;
            }
        }
    }
    //For loop to loop 10 times
    for(n=0; n<NUMS; n++)
    {
        twoSo.numbers[n]=(rand()% BASE)+1;
    }
    //loop that generates random prizes
    for(n=0; n<NUMS; n++)
    {
        twoSo.prizes[n]=(float) (((rand() % BASE)+1 )*5);
    }
    //Loop that loop 2 times
    for(n=0; n<SYMS; n++)
    {
        while(used !=0)
        {
            sym = rand() %(sizeof(SYMBOLS) / sizeof(SYMBOLS[0]));
            //switch statement to access the characters inside the SYMBOLS array
            if(usedSyms[sym]==1)
            {
                used= 1;
                break;
            }
            switch(sym)
            {
            case 0:
                twoSo.bonus[n]=SYMBOLS[0];
                usedSyms[sym] =1;
                break;
            case 1:
                twoSo.bonus[n]=SYMBOLS[1];
                usedSyms[sym]=1;
                break;
            case 2:
                twoSo.bonus[n]=SYMBOLS[2];
                usedSyms[sym]=1;
                break;
            case 3:
                twoSo.bonus[n]=SYMBOLS[3];
                usedSyms[sym]=1;
                break;
            case 4:
                twoSo.bonus[n]=SYMBOLS[4];
                usedSyms[sym]=1;
                break;
            case 5:
                twoSo.bonus[n]=SYMBOLS[5];
                usedSyms[sym]=1;
                break;
            }
        }
    }
    return twoSo;
}
void displayScratchOffTwo(struct TwoDollar twoSo)
{
    //constants
    const int SYMS =2;
    const int NUMS = 10;
    const int BREAK = 4;
    int n;

    printf("+---------------------------------------------+\n");
    printf("| WINNING NUMBER         %2s"," ");
    for(n=0; n<SYMS; n++)
    {
        printf("%6d",twoSo.winNumbers[n]);
    }
    printf("%7s|\n|%45s|\n"," "," ");
    printf("| YOUR NUMBERS %31s|\n|"," ");
    for(n=0; n<NUMS; n++)
    {
        printf("%8d",twoSo.numbers[n]);
        if(n==BREAK)
        {
            printf("     |\n");
            printf("|");
        }
    }
    printf("     |\n|%45s|\n"," ");
    printf("| PRIZES%38s|\n"," ");
    printf("|%45s|\n|"," ");

    for (n=0; n<NUMS; n++)
    {
        printf("%8.2f", twoSo.prizes[n]);
        if(n==BREAK)
        {
            printf("     |\n");
            printf("|");
        }
    }
    printf("     |\n|%45s|\n"," ");
    printf("| SYMBOLS%37s|\n"," ");
    printf("| %44s|\n|"," ");
    for(n=0; n<SYMS; n++)
    {
        printf("%8c",twoSo.bonus[n]);
    }
    printf("                             |\n");
    printf("+---------------------------------------------+\n");
}
struct FiveDollar createScratchOffFive(struct FiveDollar fiveSo)
{
    const int SYMS=4;
    const int  NUMS = 12;
    const int BASE =50;
    const char SYMBOLS[] = {'$', '%', '&', '#', '@', '!', '^', '*'};
    int sym; //for random symbol
    int n; //loop control

    //for used symbols and numbers
    int usedSyms[]= {0,0,0,0,0,0,0,0};
    int usedNums[]= {0,0,0,0,0,0,0,0};
    int num;
    int used=0;

    //loop that generate winning number
    for(n=0; n<SYMS; n++)
    {

        used=0;
        while(used ==0)
        {
            num=(rand()% BASE)+1;
            if(usedNums[num]==0)
            {
                usedNums[num]=1;
                fiveSo.winNumbers[n]= num;
                used=1;
                break;
            }

        }
    }
    //For loop that generate player's number
    for(n=0; n<NUMS; n++)
    {
        fiveSo.numbers[n]=(rand()% BASE)+1;
    }
    //loop that generates random prizes
    for(n=0; n<NUMS; n++)
    {
        fiveSo.prizes[n]=(float) (((rand() % BASE)+1 )*5);
    }
    //Loop that loop 4 times
    for(n=0; n<SYMS; n++)
    {
        used =0;
        while(!used)
        {
            sym = rand() %(sizeof(SYMBOLS) / sizeof(SYMBOLS[0]));
            if(usedSyms[sym]==1)
            {
                usedSyms[sym]=1;
                used=1;
                break;
            }

            switch(sym)
            {
            case 0:
                fiveSo.bonus[n] = SYMBOLS[0];
                break;
            case 1:
                fiveSo.bonus[n] = SYMBOLS[1];
                break;
            case 2:
                fiveSo.bonus[n] = SYMBOLS[2];
                break;
            case 3:
                fiveSo.bonus[n] = SYMBOLS[3];
                break;
            case 4:
                fiveSo.bonus[n] = SYMBOLS[4];
                break;
            case 5:
                fiveSo.bonus[n] = SYMBOLS[5];
                break;
            case 6:
                fiveSo.bonus[n] = SYMBOLS[6];
                break;
            case 7:
                fiveSo.bonus[n] = SYMBOLS[7];
                break;

            }
        }
    }
    return fiveSo;
}
void displayScratchOffFive(struct FiveDollar fiveSo)
{
    const int SYMS=4;
    const int  NUMS = 12;
    const int BREAK =4;
    int n;
    printf("+----------------------------------------------------------------------------+\n");
    printf("| WINNING NUMBER                  %12s"," ");
    for(n=0; n<SYMS; n++)
    {
        printf("%6d",fiveSo.winNumbers[n]);
    }
    printf("%7s|\n|%76s|\n"," "," ");
    printf("| YOUR NUMBERS %62s|\n|"," ");
    for(n=0; n<NUMS; n++)
    {
        printf("%8d",fiveSo.numbers[n]);
        if ( (n + 1) % 5 != 0 )
        {
            printf ("\t");
        }
        else
        {
            printf("     |\n"); // right border
            printf("|");// left border
        }

    }
    printf("%45s|\n"," "); // right border after last number
    printf("|%76s|\n"," ");
    printf("| PRIZES%69s|\n"," ");
    printf("|%76s|\n|"," ");

    for (n=0; n<NUMS; n++)
    {
        printf("%8.2f", fiveSo.prizes[n]);
        if ( (n + 1) % 5 != 0 )
        {
            printf ("\t");
        }
        else
        {
            printf("     |\n");
            printf("|");
        }
    }
    printf("%45s|\n"," "); // right border after last number
    printf("|%76s|\n"," ");
    printf("| SYMBOLS%68s|\n"," ");
    printf("|  %74s|\n|"," ");
    for(n=0; n<SYMS; n++)
    {
        printf("%8c",fiveSo.bonus[n]);
    }
    printf("                                            |\n");
    printf("+----------------------------------------------------------------------------+\n");
}
//part 2 of scratch off
int cashOneDollar(struct OneDollar one)
{
    //constants
    const int SYMS = 2;
    const int NUMS = 5;
    //variables
    float cash=0;
    int n;
    char bonus = getBonus(ONE);
    printf("Bonus symbol is %c\n",bonus);

    for(n=0; n<NUMS; n++)
    {
        if(one.numbers[n]== one.winNumbers)
        {
            cash += one.prizes[n];
        }
    }
    for(n=0; n<SYMS; n++)
    {
        if(one.bonus[n] == bonus)
        {
            cash += BONUS;
        }
    }
    printf("Your One Dollar Scratch off won you $%.2f\n",cash);
    return (int)cash;
}
int cashTwoDollar(struct TwoDollar two)
{
    //constants
    const int WINS =2;
    const int SYMS =2;
    const int NUMS =10;
    float cash=0;
    int n,w;

    char bonus = getBonus(TWO);
    printf("Bonus symbol is %c\n",bonus);

    for(w = 0; w < WINS; w++)
    {
        for(n = 0; n < NUMS; n++)
        {
            if(two.numbers[n] == two.winNumbers[w])
            {
                cash += two.prizes[n];
            }
        }
    }

    for(n = 0; n < SYMS; n++)
    {
        if(two.bonus[n] == bonus)
        {
            cash += BONUS;
        }
    }

    printf("Your Two Dollar Scratch Off won you $%.2f\n\n", cash);

    return (int)cash;
}
int cashFiveDollar(struct FiveDollar five)
{
    //constants
    const int WINS =4;
    const int SYMS =4;
    const int NUMS =12;
    float cash=0;
    int n,w;
    char bonus = getBonus(FIVE);
    printf("Bonus symbol is %c\n",bonus);

    for(w = 0; w < WINS; w++)
    {
        for(n = 0; n < NUMS; n++)
        {
            if(five.numbers[n] == five.winNumbers[w])
            {
                cash += five.prizes[n];
            }
        }
    }

    for(n = 0; n < SYMS; n++)
    {
        if(five.bonus[n] == bonus)
        {
            cash += BONUS;
        }
    }

    printf("Your Five Dollar Scratch Off won you $%.2f\n\n", cash);

    return (int)cash;
}
char getBonus(int type)
{
    //constants
    const int ONE_TWO=6;
    const int FIVE_RAND =8;
    const char SYMBOLS[] = {'$', '%', '&', '#', '@', '!', '^', '*'};
    //VARIABLES
    char bonus;
    int sym;
    if(type == ONE || type == TWO)
    {
        sym=rand() % ONE_TWO;
        switch(sym)
        {
        case 0:
            bonus = SYMBOLS[0];
            break;
        case 1:
            bonus = SYMBOLS[1];
            break;
        case 2:
            bonus = SYMBOLS[2];
            break;
        case 3:
            bonus = SYMBOLS[3];
            break;
        case 4:
            bonus = SYMBOLS[4];
            break;
        case 5:
            bonus = SYMBOLS[5];
            break;
        }
    }
    else if( type == FIVE)
    {
        sym= rand() % FIVE_RAND;
        switch(sym)
        {
        case 0:
            bonus = SYMBOLS[0];
            break;
        case 1:
            bonus = SYMBOLS[1];
            break;
        case 2:
            bonus = SYMBOLS[2];
            break;
        case 3:
            bonus = SYMBOLS[3];
            break;
        case 4:
            bonus = SYMBOLS[4];
            break;
        case 5:
            bonus = SYMBOLS[5];
            break;
        case 6:
            bonus = SYMBOLS[6];
            break;
        case 7:
            bonus = SYMBOLS[7];
            break;
        case 8:
            bonus = SYMBOLS[8];
            break;
        }
    }
    return bonus;
}
//Blackjack game
int playBlackJack(int cash)
{
    // bet amount
    const int BET = 10;

    // Black Jack constants
    const int MIN_HIT = 16;
    const int HIT = 1;
    const int STAND = 0;

    // loop control variables
    int play = 1;   // continue playing
    int choice = 0; // player wants to HIT or STAND
    int bust = 0;   // flag for player busting and play again

    // keep track of score of cards
    int player = 0;
    int dealer = 0;

    // the deck of cards
    char deck[SUITS][FACES];

    // which cards have been dealt
    char dealt[SUITS][FACES];

    printf("Let's play Black Jack!\n\n");
    printf("Your cash balance is $%d\nThe bet is $%d\n", cash, BET);
    printf("Dealer must HIT if their score is 16 or less\n");
    printf("Dealer must STAND if their score is 17 or higher\n");
    printf("If the player wins the hand, they receive $20\n");
    printf("If the dealer wins the hand, the $10 bet is lost\n");
    printf("If it is a PUSH, the player keeps their $%d bet\n", BET);

    clearScreen();

    if(cash < BET)
    {
        printf("Player does not have enough money to play!\n");
        return cash;
    }

    initializeUsed(dealt);

    printf("Shuffling the cards...\n");
    initializeDeck(deck);

    printf("Here's the deck...\n");
    printDeck(deck);

    clearScreen();

    printf("\nDealing...\n");

    while(play)
    {
        printf("\nPlayer's cash $%d\n\n", cash);

        if(cash < BET)
        {
            printf("Player does not have enough money to play!\n");
            play = 0;
            continue;
        }

        // place the player's bet
        cash -= BET;

        // for each hand, reset the scores to 0 and the bust flag
        player = 0;
        dealer = 0;
        bust = 0;

        // deal two cards to player and dealer
        player += deal(deck, dealt);
        player += deal(deck, dealt);

        printf("\nPlayer's score %d\n", player);

        dealer += deal(deck, dealt);
        dealer += deal(deck, dealt);

        // determine if the player wants to HIT or STAND first
        printf("\nPlayer, another card? (0 = STAND, 1 = HIT)\n");
        scanf("%d", &choice);

        // continue looping until the player busts or stands
        while(choice == HIT && player < BUST)
        {
            player += deal(deck, dealt);

            printf("\nPlayer's score %d\n", player);

            // if the player busts 21, dealer automatically wins the hand
            if(player > BUST)
            {
                // set the bust flag
                bust = 1;
                printf("\nPlayer BUSTED! Dealer wins the hand!\n");
                // break out of the inner loop
                break;
            }
            else
            {
                printf("\nPlayer, another card? (0 = STAND, 1 = HIT)\n");
                scanf("%d", &choice);
            }
        } // end while loop for player to HIT or STAND


        // if the player busted and the player wants another hand, skip the remaining code
        if(bust)
        {
            printf("\nPlayer, play another hand? (0 = No, 1 = Yes)\n");
            scanf("%d", &play);

            // clear the screen after each hand
            clearScreen();
            continue;
        }
        else
        {
            // determine if the dealer has to HIT or STAND
            if(dealer <= MIN_HIT)
            {
                choice = HIT;
            }
            else
            {
                choice = STAND;
            }

            // keep dealing until the dealer is required to HIT, STAND or busts
            while(choice == HIT)
            {
                dealer += deal(deck, dealt);

                if(dealer <= MIN_HIT)
                {
                    choice = HIT;
                }
                else
                {
                    choice = STAND;
                }
            }
        }

        printf("\nDealers's score %d\n", dealer);

        cash += results(player, dealer);

        printf("\nPlayer, play another hand? (0 = No, 1 = Yes)\n");
        scanf("%d", &play);

        // clear the screen after each hand
        clearScreen();
    }

    printf("Thank you for playing Black Jack at Knights Casino! Your cash out is $%d\n\n", cash);

    return cash;
}


int results(int playerScore,int dealerScore)
{
    //constants
    const int WIN =20;
    const int PUSH = 10;
    const int LOSE =0;
    //if else statement
    if(dealerScore >BUST)
    {
        printf("Dealer busted!\n");
        return PUSH;// returns $10 dollars
    }
    else if(playerScore == dealerScore)
    {
        printf("It was a push!\n");
        return PUSH;
    }
    else if(playerScore > dealerScore)
    {
        printf("Player wins the hand!\n");
        return WIN;
    }
    else
    {
        printf("Dealer wins the hand!\n");
        return LOSE;
    }
}
int deal(char deck[SUITS][FACES],char dealt [SUITS][FACES])
{
    //constant for the maximum number of cards
    const int MAX_OF_CARDS=52;

    //flag variable to store used cards
    int used=0;
    //score
    int score;
    //randoms
    int suit;//Variable to store the random suit
    int face;//store random faces
    //if statement
    if(cards == MAX_OF_CARDS )
    {
        cards=0;
        initializeUsed(dealt);
    }
    //while loop
    while(!used)
    {
        suit=rand()%SUITS;
        face=rand()%FACES;
        if (dealt[suit][face] == 0)
        {
            used = 1;
            dealt[suit][face] = 1;
            cards++;
        }
    }
    switch(face)
    {
    case 1:
        score = face;
        break;
    case 2:
        score = face;
        break;
    case 3:
        score = face;
        break;
    case 4:
        score = face;
        break;
    case 5:
        score = face;
        break;
    case 6:
        score = face;
        break;
    case 7:
        score = face;
        break;
    case 8:
        score =10;
        break;
    case 9:
        score =10;
        break;
    case 10:
        score =10;
        break;
    case 11:
        score =10;
        break;
    case 12:
        score=12;
        break;
    }

    return score;
}
void initializeUsed(char used [SUITS][FACES])
{
    int s; // integer looping variable for the rows
    int f; // integer looping variable for the columns
    for(s = 0; s < SUITS; s++)
    {
        for(f = 0; f < FACES; f++)
        {
            used[s][f] = 0;
        }
    }
}

void initializeDeck(char deck [SUITS][FACES])
{
    const char face[] = {'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};
    //two integer looping variables
    int s,f;
    //nested loop
    for(s = 0; s < SUITS; s++)
    {
        for(f = 0; f < FACES; f++)
        {
            deck[s][f] = face[f];
        }
    }
}

void printDeck(char deck [SUITS][FACES])
{
    int s; //suits
    int f;//faces

    for(s = 0; s < SUITS; s++)
    {
        for(f = 0; f < FACES; f++)
        {
            switch(s)
            {
            case CLUBS:
                printf("%c of Clubs\n", deck[s][f]);
                break;
            case DIAMONDS:
                printf("%c of Diamonds\n", deck[s][f]);
                break;
            case HEARTS:
                printf("%c of Hearts\n", deck[s][f]);
                break;
            case SPADES:
                printf("%c of Spades\n", deck[s][f]);
                break;
            }
        }
    }
}
