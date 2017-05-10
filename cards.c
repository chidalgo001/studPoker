
// cards.c

/**********************************************************************************	*/
/* Author: Christian Hidalgo. PID: 2103434                                          */

/* Description: program will hold all of the functions used in cards.c relating to 
   'struct cards' and 'struct deck'.                                                */

/* Input: none required                                                             */

/* Output: not aplicable                                                            */

/* Compilation: make (or make all) using the make file                              */
/* Execute with ./poker.out 'anything' 'number'   i.e. ( ./poker.out 2 3 )          */

/* I certify that this work is my own and none of it is work of any other person	*/
/* or entity (with exception of the temperature conversion formulas               	*/



/**********************************************************************************	*/
/* Program Defines */

# include <stdio.h>
# include <stdlib.h>        //for rand(), srand()
# include <time.h>          //to supplement the srand() function
# include "cards.h"         //for functions related to 'struct cards'/'struct deck'

# define DISPLAY 4          //Number of cards to display per line in display

/**********************************************************************************	*/
/* Function Declarations */


/***********************************************************************************/
/* getCardFace() gets one int as a parameter. This int is the current index
 passed from createCard in order to determine the face of the card. It will
 the index passed on into its appropiate face value of the card as a char.
 
 If an index is not a number between 1-13, it will return a '0' and print an
 error message.                                                                  */
/***********************************************************************************/


char getCardFace( int faceIndex ){
    
    char faces[ ] = {'0','A','2','3','4','5','6','7','8','9','T','J','Q','K'};
    
    if (faceIndex > TOTAL_FACES || faceIndex < 1 ) {
        
        printf("\nThe index for the face of the card was not within range. \n");
        printf("Please update parameter\n\n");
        
        return '0';
    }
    
    return faces[ faceIndex ];
    
}// end of getCardFace(int)


/***********************************************************************************/
/* getCardSuit() gets one int as a parameter. This int is the current index
 passed from createCard in order to determine the suit of the card. It will
 the index passed on into its appropiate suit value of the card as a char.
 
 If an index is not a number between 1-4, it will return a '0' and print an
 error message.                                                                  */
/***********************************************************************************/


char getCardSuit( int suitIndex){
    
    char suit[] = {'0','C','D','H','S'};
    
    if(suitIndex > TOTAL_SUITS || suitIndex < 0){
        
        printf("\nThe index for the suit of the card was not within range. \n");
        printf("Please update parameter\n\n");
        
        return '0';
        
    }
    
    
    return suit[ suitIndex ];
    
}//end of getCardSuit(int)

/***********************************************************************************/


/***********************************************************************************/


enum faceValue getFaceValue( int faceIndex ){
    
    enum faceValue faceList[ ] = { BLANK , BLANK, TWO , THREE , FOUR , FIVE ,
        SIX , SEVEN , EIGHT , NINE , TEN , JACK , QUEEN , KING , ACE };
    
    if( faceIndex == 1 ){
        
        return ACE;
        
    }
    
    
    return faceList[ faceIndex ];
    
}// end of getFaceValue()


/***********************************************************************************/
/* createCard() will recieve 2 ints as parameters. These two ints are the indexes
 being passed oon by createDeck() to determine the next card. It creates a new
 'struct cards' with those indexes by using getCargdFace() and getCardSuit()
 correspondingly                                                                 */
/***********************************************************************************/

struct cards createCard( int faceIndex , int suitIndex){
    
    struct cards tempCard;
    
    tempCard.face = getCardFace(faceIndex);
    tempCard.suit = getCardSuit(suitIndex);
    tempCard.value = getFaceValue(faceIndex);
    
    return tempCard;
    
}//end of createCard(int,int)

/***********************************************************************************/
/* aceToLow() gets an array of type Card and an int where the int value is the 
   number of cards in the array. The function will check if the first card.face in
   the array is equal to '2' and if the rest of the array is sequential from 2.
   If it is, it will get the Ace ('A') from the last
   place and store it in a temp variable. It will then shift every value one spot 
   up in the array and later place the Ace back in the array at position 0 */
/***********************************************************************************/


void aceToLow( Card players[] , int totalCards){
    
    int count = 0;
    int buffer;
    
    Card temp;
    
    if( players[0].face == '2' ){
        
        for( buffer = 0 ; buffer < (totalCards - 2) ; buffer ++){
            
            if( (players[ buffer ].value + 1) == players[ buffer + 1].value ){
                
                count++;
                
            }
            
        }
        
        
        if(count == (totalCards - 2) ){
            
            temp = players[ totalCards - 1];
            
            for( count = (totalCards - 2); count >= 0; count--){
                
                players [ count + 1] = players [count];
                
            }
            
            players[0] = temp;
        }
    }
    
}//end of aceToLow()


/***********************************************************************************/
/* createDeck() will receive a 'struct deck' pointer. The deck that it is being 
   pointed to will be created as an ordered deck and will be given the tag ORDERED
   to keep track of its current status. Cards will be created using createCard()
   and will be placed starting at index 0 of the 'struct deck' being pointed at.
   
   Indexes are being used for faces and suits.
   For simplicity, Faces will be using indexes [1 - 13] and Suits will be using 
   indexes [ 1 - 4 ]  (Reffer to function getCard() and getFace() for the 
   appropiate equivalent value)                                                    */
/***********************************************************************************/

void createDeck( struct deck *tempDeck){
    
    int faceIndex = 1;
    int suitIndex = 1;
    int count;
    
    for( count = 0; count < DECK_SIZE; count++){
        
        (*tempDeck).deck[ count ] = createCard( faceIndex , suitIndex);
        
        faceIndex++;
        
        if (faceIndex > TOTAL_FACES) {
            faceIndex = 1;
            suitIndex++;
        }
        
    }
    
    (*tempDeck).status = ORDERED;
    
}//end of createDeck( struct cards *pointer)


/***********************************************************************************/
/* dealCards() receives a 'struct cards' pointer, a 'struct deck' pointer and
 two int values. the deck pointer points to the deck where the cards are to be
 drawn from, and the cards pointer points to the array of cards which represents
 the players hands. It will transfer the first 'totalCards' where totalCards is
 equal to the number of players times the number of cards per player to the
 player array.                                                                   */
/***********************************************************************************/

void dealCards( struct cards players[ ] , struct deck *tempDeck, int totalPlayers ,
               int cardsPerHand){
    
    int topCard;
    int totalCards = ( totalPlayers * cardsPerHand );
    
    struct cards temp;
    
    
    for(topCard = 0; topCard < totalCards; topCard++){
        
        temp = (*(tempDeck)).deck[ topCard ];
        
        players[ topCard ] = temp;
        
        
    }
    
}// end of dealCards()


/***********************************************************************************/
/* displayDeck() receives a 'struct deck' pointer as a parameter. This funtion will
   first read the status of the deck (ORDERED or SHUFFLED) in order to determine the
   correct heading for the display. Then, it will go through the deck and print 
   the cards one by one using the printCard() function                             */
/***********************************************************************************/


void displayDeck( struct deck *tempDeck){

    
    if((*tempDeck).status == ORDERED){
    
        printf("\n\n*******************************\n");
        printf("*     -- Ordered Deck --      *\n");
        printf("*******************************\n");

    
    }
    
    if((*tempDeck).status == SHUFFLED){
        
        printf("\n\n*******************************\n");
        printf("*     -- Shuffled Deck --     *\n");
        printf("* (Deck was shuffled %d times) *", OPTIMAL_SHUFFLE );
        printf("\n*******************************\n");
        
        
    }
    
    int count;
    int position = 0;
    int buffer = 0;
    int displayCount = 0;
    struct cards tempCard;
    
    for(count = 0; count < DECK_SIZE; count++ ){
        
        displayCount++;
        
        tempCard = (*tempDeck).deck[ position ];
        
        printCard( tempCard );
        
        position = position + 13;
       
        if( displayCount == DISPLAY ){
            
            buffer ++;
            position = buffer;
         
            displayCount = 0;
            
            printf("\n");
            
        }//this will print every DISPLAY number of cards per line
        
    }
    
    printf("\n*******************************\n\n");
    printf("\n-------------------------------\n");
            
}//end of displayDeck();


/***********************************************************************************/
/* displayPlayerHands() receives one 'struct cards' pointer and 2 int values as
 as parameters. The cards pointer points to the array of cards which represents
 the players' hands. The function will print out one by one the cards from the
 list using the printCard() function. It will print until the count reaches
 the product of the 2 int values (total cards dealt). Players determined
 by calculating a multiple of the 'count' from 'cards per hand' */
/***********************************************************************************/


void displayPlayerHands( struct cards players[ ] , int totalPlayers , int cardsPerHand){
    
    int count = 0;
    int playerNumber = 0;
    int cardsDealt = totalPlayers * cardsPerHand;
    
    printf("\n\n*******************************\n");
    printf("*      -- Displaying --       *\n");
    printf("*    -- Player's Hands --     *\n");
    printf("*******************************\n");
    
    
    for( count = 0; count < ( cardsDealt ); count++ ){
        
        if( ( count % cardsPerHand ) == 0){
            playerNumber++;
            printf("\n     ----* Player %d *----\n\n" , playerNumber);
        }
        
        struct cards temp;
        temp = players[ count ];
        
        printf("\t   ");
        printCard( temp );
        printf("\n");
        
    }
    
    printf("\n*******************************\n\n");
    
    //determineHand( players , cardsPerHand , cardsDealt );
    
    
}// end of displayPlayerHands()


/***********************************************************************************/
/* deal the first x cards, then organize them. store in same array, deal next x 
 cards... repeat */
/***********************************************************************************/


void organizeHand( struct cards players[ ] , int totalCards , int cardsPerHand ){

    int position;
    int arrLeft = 0;
    int arrRight = ( cardsPerHand - 1 );
    
    struct cards holder[ cardsPerHand ];
    
    if( totalCards == 1){
        //do nothing, its organized if its one card.
    }
    else{
        
        do{
            
            for( position = 0; position < cardsPerHand; position++){
                
                holder[ position ] = players[ arrLeft + position ];
                
            }//this will copy 'cardsPerHand' number of cards into 'holder' array
            
            selectionSort( holder , cardsPerHand );
            
            for( position = 0; position < cardsPerHand; position++){
                
                players[ arrLeft + position ] = holder[ position ];
                
            }//Will place the sorted section back into the original array
            
            arrRight = arrRight + cardsPerHand;
            arrLeft = arrLeft + cardsPerHand;
            
        }while( arrRight <= totalCards );
        
    }
    
}

/***********************************************************************************/
/* void printCard() will recieve a 'struct cards' as a parameter and it will print
   the card's face and suit int the form of: 'face' of 'suit'.
   the spaces have been formatted to align with the "display" functions.           */
/***********************************************************************************/


void printCard( struct cards tempCard){
    
    printf(" %c of %c " , tempCard.face , tempCard.suit);
    
}//end of printCard()


/***********************************************************************************/
/* selectoinSort() will sort the cards from low to high using the selection sort
   algorithm. One change to the algorithm is that if at the end of the sorting; it 
   checks if the ACE ('A') is in the last place on the array. If it is, it will check
   it will call the function aceToLow() for further ordering. */
/***********************************************************************************/

void selectionSort( struct cards players[] , int totalCards){

    int count , position , next;
    
    Card temp;
    
    
    for ( count = 0 ; count < ( totalCards - 1 ) ; count++ )
    {
        position = count;
    
        for ( next = count + 1 ; next < totalCards ; next++ )
        {
        
            if ( players[ position ].value > players[ next ].value )
           
                position = next;
        
        }
        
        if ( position != count )
        
        {
            temp = players[ count ];
            players[ count ] = players[ position ];
            players[ position ] = temp;
        }
    }
    
    
    
    if( players[ totalCards - 1].face == 'A' ){
    
        aceToLow(players , totalCards);
        
    }//this IF will set ace to low if the followings cards are in order starting at 2
    
}//end of selectionSort()

/***********************************************************************************/
/* shuffleDeck() will receive a 'struct deck' pointer as a parameter and will
 shuffle the 'cards' in the deck that the pointer is pointing at. It will do so
 by randomly selecting a position in the deck array and will swap it with the
 card at index 0, it will keep doing so until all of the indexes in the array
 reach (DECK_SIZE - 1). It will also shuffle it a number of times determined
 by OPTIMAL_SHUFFLE whick can be modified in cardFunction.h file.
 Once shuffled, the function will change the status of the deck to SHUFFLED.     */
/***********************************************************************************/


void shuffleDeck( struct deck *tempDeck){
    
    struct cards temp;
    
    int timesShuffled;
    
    time_t timeVariable;
    srand((unsigned) time(&timeVariable));
    
    
    for(timesShuffled = 0; timesShuffled <= OPTIMAL_SHUFFLE; timesShuffled++ ){
        
        int currentPosition;
        
        for( currentPosition = 0; currentPosition < DECK_SIZE; currentPosition++  ){
            
            
            int randomPosition = rand() % DECK_SIZE;
            
            temp = (*(tempDeck)).deck[ randomPosition ];
            
            (*(tempDeck)).deck[ randomPosition ] = (*(tempDeck)).deck[ currentPosition ];
            
            (*(tempDeck)).deck[ currentPosition] = temp;
        }
        
    }//shuffles deck OPTIMAL_SHUFFLE times (currently set at 7)
    
    (*(tempDeck)).status = SHUFFLED;
    
}//end of shuffleDeck()


