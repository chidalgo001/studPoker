
// cards.h

/**********************************************************************************	*/
/* Author: Christian Hidalgo.                                                       */

/* Description: This is the user defined header file that will be included in a file
   when the use of any 'struct cards' or 'struct deck' are going to be used, it 
   includes program defines, function prototypes and the struct declaraions         */

/* Input: none required                                                             */
/* Output: Not aplicable                                                            */

/* compilation: gcc cardFunctions.h */


/* I certify that this work is my own and none of it is work of any other person	*/
/* or entity (with exception of the temperature conversion formulas               	*/



/**********************************************************************************	*/
/* Program Defines */

# define DECK_SIZE 52       //Size of an American deck of playing cards
# define OPTIMAL_SHUFFLE 7  /*Amount of times for a deck to be completely shuffeled.
                              This ammount could be modified as needed */
# define TOTAL_PLAYERS 7   //Max number of players allowed
# define CARDS_PER_HAND 5  //number of cards per player
# define TOTAL_FACES 13     //total number of faces in a deck
# define TOTAL_SUITS 4      //total number of suits in a deck

enum deckStatus { ORDERED , SHUFFLED };

enum faceValue { BLANK = 1 , TWO = 2, THREE = 3 , FOUR = 4 , FIVE = 5 , SIX = 6 ,
    SEVEN = 7 , EIGHT = 8 , NINE = 9 , TEN = 10 , JACK = 11 , QUEEN = 12 ,
    KING = 13 , ACE = 14 };


typedef struct cards{
    
    char face;
    char suit;
    enum faceValue value;
    
}Card;


struct deck{
    
    struct cards deck[ DECK_SIZE ];
    enum deckStatus status;
    
};

/**********************************************************************************	*/
/* Function prototypes	*/

char getCardSuit( int );
char getCardFace( int );

enum faceValue getFaceValue( int faceIndex );

struct cards createCard( int, int);

void aceToLow(struct cards[] , int);
void createDeck( struct deck *pointer );
void dealCards( struct cards [] , struct deck * , int , int);
void displayDeck( struct deck *pointer );
void displayPlayerHands( struct cards [] , int , int );
void organizeHand( struct cards [] , int , int);
void printCard( struct cards );
void selectionSort( struct cards [] , int);
void shuffleDeck( struct deck *pointer );







/**********************************************************************************	*/
