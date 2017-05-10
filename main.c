// main.c

/**********************************************************************************	*/
/* Author: Christian Hidalgo. PID: 2103434                                          */

/* Description: program, when executed is to read values from the command-line
   and validate if the last numbers entered will be between the values of 1-7.
   Anything entered in in the first input, a 5 will be used instead  */
   
/* Once it has passed, a new ordered deck will be created. once done it will display
   the ordered deck, later it will shuffle it and display it. Then the program will 
   deal a number of cards (5) to a number of
   players (determined from the second input number). It will then display each
   player's hand. Organize them individually and and later display them. The program 
   will also determine and display what best poker rank each player has in their hand.
   Finally, the program will determine the winner(s) of the game by checking which player
   has the highets poker rank 
 
   **NOTE**
   for the extra credit, the breakTie function can be used. Follow instructions under 
   determinewinner function to use it  */

/* Command-line Input: a number between 1 and 7 for the second number
   i.e ( ./a.out number number )      */

/* Output: An ordered deck, a shuffled deck and the hand dealt to players,           */

/* Compilation: make (or 'make all' )                                        */
/* Execute with ./poker.out 'anything' 'number'   i.e. ( ./poker.out 2 3 )         */

/* I certify that this work is my own and none of it is work of any other person	*/
/* or entity (with exception of the temperature conversion formulas               	*/


/**********************************************************************************	*/
/* Program Defines */

# include <stdio.h>
# include <stdlib.h>        //for the use of atoi()
# include "cards.h"         //for functions related to 'struct cards'/'struct deck'
# include "studPoker.h"     /*to use in conjunction with cards.c, this will allow
                            the use of the functions related to stud poker game */

# define EXPECTED_ARGS 3    //Number of expected arguments from command-line
# define FAILED -1          //Return value if any validation fails and termination


/**********************************************************************************	*/
/* Function prototypes	*/


int validateInput(char * , char * , int[ ] );
int validateArguments( int );



/************************************************************************************/
/* Main will receive 2 values from the command-line input and will validate them.
   If they are both a number from 1-13 and the product of both numbers is between
   1 and 52, then the program will resume its execution. Similarly, if the amount
   of arguments from the command-line equals 3. i.e (./a.out, number, number) will
   also resume the execution. If one, or both conditions fail to pass validation
   the program will terminate.

   Once it has passed, main will create a new deck. Determine the number of players
   and the number of cards per player from the valid input. Then shuffle the deck
   and number of times, to finally deal the cards to the players.                   */
/************************************************************************************/

int main ( int args , char *argsv[ ] ){

    
    int result = 0;//this will be used to determine if program terminates
    
    result = validateArguments( args );
    
    if (result == FAILED ){
        
        return 0;
    
    }//this will terminate the program if validation fails
    
    char *handsPointer , *cardsPerHandPointer;
    
    cardsPerHandPointer = argsv[1];
    handsPointer = argsv[2];
    
    int storedInput[2] = { 0 , 0 };
    
    result = validateInput( handsPointer , cardsPerHandPointer , storedInput);
    
    if (result == FAILED ){
        
        return 0;
        
    }//this will terminate the program if validation fails
    
    
    int hands = storedInput[0];
    int cardsPerHand = storedInput[1];
    
    int totalCards = ( hands * cardsPerHand );//total cards to be dealt among players
    
    
    struct deck newDeck;
    struct deck *deckPointer = &newDeck;
    
    
    struct cards playersList[ totalCards ]; //playersList[total of cards dealt among players]
    struct cards *playerPointer = playersList;
    
    enum rank playerRanks[ hands ];
    
    createDeck( deckPointer );
    //displayDeck( deckPointer );
    
    shuffleDeck( deckPointer );
    //displayDeck( deckPointer );
    
    dealCards( playerPointer , deckPointer , hands , cardsPerHand);
    //displayPlayerHands( playersList , hands , cardsPerHand);
    
    
    organizeHand( playersList , totalCards , cardsPerHand);
    displayPlayerHands( playersList , hands , cardsPerHand);
    
    determinePokerHand( playersList , cardsPerHand , totalCards , playerRanks);
    displayPokerRanks( playerRanks , hands);
    
    determineWinner( playerRanks , hands , playersList);
    
    /*
    Card array[10];
    array[4] = createCard( 5, 1 );
    array[1] = createCard( 3 , 1 );
    array[2] = createCard( 1 , 2 );
    array[3] = createCard( 3, 1 );
    array[0] = createCard( 5, 1 );
    
    array[5] = createCard( 5 , 2 );
    array[6] = createCard( 7 , 3 );
    array[7] = createCard( 7 , 2 );
    array[8] = createCard( 4 , 2 );
    array[9] = createCard( 4 , 2 );
    
    
    organizeHand( array , 10 , 5);
    displayPlayerHands( array , 2 , 5);
    
    printf("this is pairs %d \n", pairs( array, 5, 0));
    
    determinePokerHand( array , 5 , 10 , playerRanks );
    
    displayPokerRanks( playerRanks , 2);
    
    determineWinner( playerRanks , 2 , playersList);
    */
    
    
return 0;

}//end of main()


/**********************************************************************************	*/
/* validateInput() will recieve 2 char pointers and one int array. the pointers 
   will be pointing to the input values gathered from the comman-line by first
   converting the string into int and test if the number is a value between 1-7.
   If validation is passed it will store both values into the array from the 
   parameter for later use.
   if validations fails, an error message will print out and it will 
   return a -1 to indicate termination.                                           */
/**********************************************************************************	*/

int validateInput( char *hands , char *cardsPerHand , int input[]){
    
    int numberOfPlayers = atoi( hands );
    
    //int numberOfCards = atoi( cardsPerHand );
    //int totalCards = ( numberOfPlayers * numberOfCards );
    
    
    if( /* totalCards <= DECK_SIZE && */ numberOfPlayers <= TOTAL_PLAYERS
            && numberOfPlayers > 0 ) {
        
        input[0] = numberOfPlayers;
        input[1] = CARDS_PER_HAND;
        
    }//numbers allowed are 1-7 and products of 52, no negative numbers either
    
    else{
        
        printf("\n\n****************-- NUMBER ERROR --***************\n");
        printf("Unfortunately, your input was invalid. \n\n");
        printf("Please, re-run the program and enter %d numbers. \n\n", (EXPECTED_ARGS - 1) );
        printf("The first entry is for the number of cards per player, \n");
        printf("where the number of cards is %d\n" , CARDS_PER_HAND);
        printf("And the second entry is for the number of players \n");
        printf("where the maximun number of players is %d\n", TOTAL_PLAYERS);
        printf("when entered as command-line input. \n\n");
        printf("\nThank you!\n");
        printf("*************************************************\n\n\n");
        
        return -1;
    }
    
    return 0;
    
}//end of validateInput()


/**********************************************************************************	*/
/* validateArguments() will receive one int as a parameter, this is will be the
   number of arguments counted from the command-line. This function will only
   display an error message and terminate the program if the validation fails,
   otherwise it does nothing.                                                       */
/**********************************************************************************	*/

int validateArguments( int numberOfArgs){
    
    if( numberOfArgs != EXPECTED_ARGS){
        
        printf("\n\n**************-- ARGUMENT ERROR --***************\n");
        printf("Unfortunately, your input was invalid. \n\n");
        printf("Please, re-run the program and enter %d numbers. \n\n", (EXPECTED_ARGS - 1) );
        printf("The first entry is for the number of cards per player, \n");
        printf("where the maximun number of cards is %d\n" , CARDS_PER_HAND);
        printf("And the second entry is for the number of players \n");
        printf("where the maximun number of players is %d\n", TOTAL_PLAYERS);
        printf("when entered as command-line input. \n\n");
        printf("Also, please make sure that the product of the two\n");
        printf("numbers is %d or less but higher than 0\n", DECK_SIZE );
        printf("\nThank you!\n");
        printf("*************************************************\n\n");
        
        return -1;
    }
    
    return 0;
}
