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
void displayScratchOffTwo(struct TwoDollar twoSo);

struct FiveDollar createScratchOffFive(struct FiveDollar fiveSo);
void displayScratchOffFive(struct FiveDollar fiveSo);

//Casino 5 scratch  off prototypes
int cashOneDollar(struct OneDollar one);
int cashTwoDollar(struct TwoDollar two);
int cashFiveDollar(struct FiveDollar five);
char getBonus();


int cards;
#define EXIT 4
