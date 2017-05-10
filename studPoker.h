
// studPoker.h

/**********************************************************************************	*/
/* Author: Christian Hidalgo.          */

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

# define NUMBER_OF_CARDS 5          //Number of cards is in this game of Stud Poker
# define PASS 1                     //Used to determine if a rank test passes
# define FAIL 0                     //Used to determine if a rank test fails
# define NUMBER_OF_COMPARISONS 4    //The cumber of comparisons made in 5 cards

enum rank { HIGH , PAIR , TWO_PAIRS , THREE_KIND , STRAIGHT , FLUSH , F_HOUSE ,
    FOUR_KIND , S_FLUSH };


/**********************************************************************************	*/
/* Function prototypes	*/

int breakTie( Card[ ] , int[ ] , int , int );
int highCard( Card[ ] );
int pairs( Card[ ] , int , int );
int threeKind( Card[ ] , int );
int fullHouse( Card[ ] , int);
int fourKind( Card[ ] , int);
int straight( Card[ ] , int);
int flush( Card[ ] , int );
int straightFlush( Card[ ] , int );
int returnMaxRank( enum rank[ ] , int );

enum rank evaluateHand( Card[ ] , int , int);

void determinePokerHand( Card[ ] , int , int , enum rank[ ] );
void determineWinner( enum rank[ ] , int , Card[ ] );
void displayOneWinner( int , int );
void displayPokerRanks( enum rank[ ] , int );
void displayWinner( int[ ] , int , int );
void enumRank_To_String( int );
/**********************************************************************************	*/
