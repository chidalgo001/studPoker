
// studPoker.c

/**********************************************************************************	*/
/* Author: Christian Hidalgo.                                                       */

/* Description: program will hold the functions that will allow stud poker 
   to be played. This file is an augmentation to the cards.c file. ( cards.c contains
   functions related to the creation of cards and decks ) */
   
/* Stud Poker is a 5-card game of poker in where players compete to get the highets
   poker hand among other players.
   Hands are, from low to high: High card, one pair, two pairs, three of a kind
   full house, four of a kind, straight, flush, and straight flush. Players with 
   the same poker hand will be concidered winners (unless the function 'break tie'
   has been activated the code when determining the winner  */

/* Input: None required         */

/* Output: None            */

/* Compilation: gets compiled in the makefile  $ make (or $ make all)              */
/* Execute with ./poker.out 'anything' ' number'
   that gets created with the makefile                    */

/* I certify that this work is my own and none of it is work of any other person	*/
/* or entity (with exception of the temperature conversion formulas               	*/


/**********************************************************************************	*/
/* Program Defines */

# include <stdio.h>
# include "cards.h"         //for functions related to 'struct cards'/'struct deck'
# include "studPoker.h"     //for functions prototypes and defines related to studPoker


/**********************************************************************************	*/
/* Function Declarations */


/***********************************************************************************/
/* breakTie() accepts one array of Card, and int array, and 2 int values. The Card
   array is the array of the cards of all players. the int array is the list of 
   the players that are tied, maxRank is the winning poker hand and int winners
   is the number of winners. This function will get the player's cards from the 
   array of cards, and determines the highest card value from the winning poker
   for that hand and compares them to the rest. The funtion will return the index 
   of the player that won.  */
/***********************************************************************************/


int breakTie( Card playerHands[ ] , int playerList[] , int maxRank , int winners){
    
    int currentPlayer , count , position , currentWinner;
    int max;
    int playerCount = 0;
    int prevMax = 0;
    Card temp[ NUMBER_OF_CARDS ];
    
    
    
    for(playerCount = 0 ; playerCount < winners; playerCount++){
        
        currentPlayer = playerList[ playerCount ];
        position = ( currentPlayer * NUMBER_OF_CARDS ) - NUMBER_OF_CARDS;
        //'position' will hold the position of the initial card from each player in the array
        
        
        for( count = 0; count < NUMBER_OF_CARDS; count++){
            
            temp[count] = playerHands[position];
            position++;
            
        }//copies contents into temp for the current player
        
        if(maxRank == -1){
            
            max = highCard(temp);
            
        }else{
            
            max = evaluateHand( temp , NUMBER_OF_CARDS , maxRank);
            
        }
        
        if ( max > prevMax){
            
            currentWinner = currentPlayer;
            prevMax = max;
        
        }
        
    }//end of outer for loop
    
    return currentWinner;
    
}//end breakTie()


/***********************************************************************************/
/* highCard() accepts an array of type Card and returns the .value from the card in
   in the last position. ( array has to be a sorted array ) */
/***********************************************************************************/


int highCard( Card temp[] ){
    
    return temp[NUMBER_OF_CARDS - 1].value;
    
}//end of highCard()


/***********************************************************************************/
/* pairs() accepts an array of tyoe Card, and 2 int values as parameters. the 
   function will look for pairs in the array of Card  and will return the number of
   distinct pairs found, this will be used to determine if the hand has a 'One Pair'
   or a 'Two Pairs'. int 'totalCards' is for the amount of cards in the hand and 
   int selector is used when we want the funtion to return the highest pair 
   instead. ( array has to be a sorted array ) */
/***********************************************************************************/


int pairs( Card temp[ ] , int totalCards , int selector){
    
    int count;
    int pair = 0;
    enum faceValue currentValue , maxValue = 0;
    
    for( count = 1; count < totalCards; count++ ){
        
        if( temp[ count ].value == temp[ count - 1 ].value && currentValue != temp[ count ].value ){
            
            pair++;
            currentValue = temp[ count ].value;
            
            if(currentValue > maxValue){
                
                maxValue = currentValue;
                
            }
            
        }
        
    }
    
    if( (selector == 1 || selector == 2) && pair > 0){
        
        return currentValue;
        
    }//selector is used to return the value instead of the pair count.
    
    else{
        
        return pair;
        
    }
    
}//end of pairs()


/***********************************************************************************/
/* threeKind() accepts an array of type Card and an int. The function checks if a
   value is repeated 3 times in the array, if the verification fails the function
   will return a 0 otherwise it will return a tkind. int totalCards is for the 
   number of cards in a hand.( array has to be sorted ) */
/***********************************************************************************/


int threeKind( Card temp[ ] , int totalCards ){
    
    int count;
    int tkind = 0;
    
    for( count = 2; count < totalCards; count++ ){
        
        if( temp[ count ].face == temp[ count - 1 ].face
           && temp[ count - 1 ].face == temp[ count - 2 ].face ){
            
            tkind++;
            
        }
        
    }
    
    return tkind;

}//end of threeKind


/***********************************************************************************/
/* fullHouse() accepts an array of type Card and an int. The function will check
   if the array has has a 3 of a kind a 1 pair. The functions does so by passing 
   the same array into threeKind() and later passing it into pairs(). if BOTH 
   functions return PASS, the function will return a PASS (1) otherwise it returns
   a FAIL (0). int totalCards is for the number of cards in a hand. 
   ( array has to be a sorted array) */
/***********************************************************************************/


int fullHouse( Card temp[] , int cardsPerHand){
    
    int result1 = 0;
    int result2 = 0;
    int fullH = 0;
    
    result1 = threeKind( temp , cardsPerHand );
    result2 = pairs( temp , cardsPerHand , 0);
    //the '0' in pairs is to tell the function to return if it passes or fail the test
    
    if( result1 != FAIL && result2 == TWO_PAIRS){
        
        return PASS;
        
    }else{
        
        return FAIL;
    }
    
}//end of fullHouse()


/***********************************************************************************/
/* fourKind() accepts an array of type Card and an int. int totalCards is for the
   number of cards in a hand. Funtion checks if a card value is repeated 4 times
   in the array, if the count is equal to NUMBER_OF_COMPARISONS (4) then the 
   function returns PASS (1) otherwise it returns a FAIL (0).
   (array needs to be sorted first )*/
/***********************************************************************************/


int fourKind( Card arr[] ,  int totalCards ){
    
    int count;
    int pair = 0;
    enum faceValue temp = arr[ 0 ].value;
    
    for( count = 0; count < totalCards; count++ ){
        
        if( temp == arr[count].value){
            pair++;
        }
        else{
            
            temp = arr[ 1 ].value;
            
        }//temp will be assigned the second value on the array to use for comparison
        
    }
    if (pair == NUMBER_OF_COMPARISONS){
        
        return PASS;
        
    }else{
        
        return FAIL;
        
    }
}//end of fourKind()


/***********************************************************************************/
/* straight() accepts an array of type Card and an int where the int represents the
   number of cards in the hand. The function will check if the card values in the 
   array are in sequential order. If the count = NUMBER_OF_COMPARISONS (4) then the
   function returns PASS (1) otherwise it returns FAIL(0). 
   If the first card in the array is an 'A', the function will set the value of the
   Ace to '1' since it was set to low during the sorting (array needs to be sorted)*/
/***********************************************************************************/


int straight( Card temp[ ] , int cardsPerHand){
    
    int comparison = 0;
    
    int count;
    
    
    if( temp[0].face == 'A'){
        
        temp[0].value = 1;
        
    }//will only change if the hand was sorted with ace low
    
    for( count = 1 ; count < cardsPerHand; count++){
        
        if (temp[ count ].value == ( temp[ count - 1 ].value + 1 ) ){
            
            comparison++;
        }
        
    }
    if( comparison == NUMBER_OF_COMPARISONS ){
        
        return PASS;
        
    }else{
        
        return FAIL;
    }
    
}// end of straight()




/***********************************************************************************/
/* flush() accepts an array of type Card and an int, where the int is the number of
   cards in the hand. The function will check if all the suits of the cards are the 
   same by taking the first card.suit and comparing it to the next one. if the 
   number of times the function counted a match is the same as 
   NUMBER_OF_COMPARISONS, the function will return a PASS (1) otherwise it will 
   return a FAIL (0) */
/***********************************************************************************/


int flush( Card temp[] , int cardsPerHand ){
    
    int count;
    int suitCounter = 0;
    
    for (count = 1 ; count < cardsPerHand; count++ ){
        
        if( temp[ count ].suit == temp[ count -1 ].suit){
            suitCounter++;
        }
    }
    if(suitCounter == NUMBER_OF_COMPARISONS){
        
        return PASS;
        
    }else{
    
        return FAIL;
    }
}//end of flush()


/***********************************************************************************/
/* straightFlush() accepts an array of type Card and an int, where the int is the 
   number of cards in the hand. The functiion will check if the array has a flush and
   and a straight by calling both functions. Once BOTH functions return PASS, that
   is when straightFlush() will return a PASS, otherwise it will return FAIL 
   ( array needs to be sorted first )*/
/***********************************************************************************/


int straightFlush( Card temp[ ] , int cardsPerHand){
    
    int resutl1 , resutl2;
    int result = 0;
    
    resutl1 = flush( temp , cardsPerHand);
    resutl2 = straight( temp , cardsPerHand);
    
    if( resutl1 == PASS && resutl2 == PASS){
        
        result = PASS;
    }
    
    return result;
    
}//end of straightFlush()

/***********************************************************************************/
/* returnMaxRank() receives an 'enum rank 'array and an int. The array is for the
   collection of all the player's poker ranks and the int parameter is for the
   number of players. The function will return the index of the highest enum rank
   in the array */
/***********************************************************************************/


int returnMaxRank( enum rank list[] ,  int players){
    
    int count;
    enum rank max = 0;
    
    for( count = 1 ; count <= players ; count++){
        
        if( list[ count ] >= max){
            max = list[ count ];
        }
        
    }
    
    return max;
    
}//end of returnMaxRank()

/***********************************************************************************/
/* evaluateHand() accepts an array of type Card and 2 int values where the first 
   is for the number of cards per hand and the second one is an indicator for a
   function. The function will determine what the array of cards has as a Poker
   Rank. the return value will be the 'enum rank' value determined if the 
   appropiate test has been passed. The test have been ordered from highest to 
   lowest to determine priority. If all the tests fail, then the function will 
   return the 'enum rank' of 'HIGH' for that array ( or hand ). */
/***********************************************************************************/


enum rank evaluateHand( Card arr[ ] , int cardsPerHand , int selector){
    
    int test = 0;
    
    /***********************************************/
    
    test = straightFlush( arr , cardsPerHand );
    
    if( test == PASS ){
        
        return S_FLUSH;
        
    }// straight flush tag return
    
    /***********************************************/
    
    test = fourKind( arr , cardsPerHand  );
    
    if( test == PASS ){
        
        return FOUR_KIND;
        
    }//four of a kind tag return
    /***********************************************/
    
    test = flush(arr , cardsPerHand  );
    
    if( test == PASS ){
        
        return FLUSH;
        
    }//flush tag return
    
    /***********************************************/
    
    test = straight( arr , cardsPerHand );
    
    if( test == PASS ){
        
        return STRAIGHT;
        
    }//straight tag return
    
    /***********************************************/
    
    test = fullHouse( arr , cardsPerHand );
    
    if( test == PASS ){
        
        return F_HOUSE;
        
    }//full house tag return
    
    /***********************************************/
    
    test = threeKind( arr , cardsPerHand );
    
    if( test != FAIL ){
        
        return THREE_KIND;
        
    }//three of a kind tag return
    
    /***********************************************/
    
    test = pairs( arr , cardsPerHand , selector );
    
    if (selector == 1 || selector == 2){
        
        return test;
        
    }else if( test != FAIL ){
        
        if (test == PAIR){
            return PAIR;
        }
        
        if(test == TWO_PAIRS ){
            return TWO_PAIRS;
        }
        
    }//one or two pair tag return
    
    return HIGH;
    
}//end evaluateHand


/***********************************************************************************/
/* determinePokerHand() gets an array of type Card, two int values and an array of
   type enum rank. the first integer value is for the number of cards per hand, and
   the second value of for the total number of cards dealt among players. The enum 
   rank array of used to store the results of each player hand. The function grabs
   the first 'cardsPerHand' number of cards and stores them into a temp array
   and passes it into evaluateHand(). once it has determines the which poker hand
   (or poker rank), it has the function will store the result into the enum rank
   array and procede with the next 'cardsPerHand' number of cards.
   ( The array of type Card needs to be a sorted array )*/
/***********************************************************************************/


void determinePokerHand( Card players[] , int cardsPerHand , int totalCards , enum rank list[] ){
    
    
    int place;
    int hand = 1;
    
    enum rank result;
    
    Card temp[ cardsPerHand ];
    
    int arrLeft = 0;
    int arrRight = ( cardsPerHand - 1 );
    
    
    do{
        
        for( place = 0; place < cardsPerHand; place++){
            
            temp[ place ] = players[ arrLeft + place ];
            
        }//retrieves the current hand to be examined from array
        
        
        result = evaluateHand( temp , cardsPerHand , 0);
        
        
        list[ hand ] = result;
        
        arrRight = arrRight + cardsPerHand;
        arrLeft = arrLeft + cardsPerHand;
        hand++;
        
    }while( arrRight <= totalCards );
    
    
}//end of determinePokerHand()

/***********************************************************************************/
/* determineWinner() gets an enum rank array, an int value and an array of type Card
   The enum rank array will hold the poker ranks of all players involved, the int
   value is for the number of players and the Card array is for all of the player's
   cards. The function will first get the highest poker rank using the function
   returnMax(), then it will get all of the player indexes that have the same rank
   and store it in an int array (winnerList) and finally it will display the winner
   by calling the displayWinner() function 
 
   ** NOTE **
   to the breakTie() function only works if there is a tie between a high card,
   one pair or teo pairs.*/
/***********************************************************************************/


void determineWinner( enum rank list[] , int players , Card playerHands[] ){
    
    int maxRank , count;
    int winnerList[ players ];
    int winner  = 0;
    int currentWinner;
    
    maxRank = returnMaxRank( list , players );
    
    for( count = 1; count <= players ; count = count + 1){
        
        if( list [ count ] == maxRank){
            
            winnerList[ winner ] = count;
            
            winner++;
            
        }
        
    }
    
    //displayWinner( winnerList , winner , maxRank);
    
    
     // ** ACTIVATE THIS BLOCK OF CODE TO DETERMINE ONE WINNER **
     // ** AND DISABLE THE ABOVE displayWinner() FUNCTION **
     
     if( winner > 1){
     
     if(maxRank == HIGH){
     
     maxRank = -1;
     
     }//this IF will change the value to use for HIGH in order to avoid bugs
     
     currentWinner = breakTie( playerHands , winnerList , maxRank , winner);
     displayOneWinner( currentWinner ,  maxRank);
     
     }//the outer IF will be used if there is more than one winner
     
     else{
     
     currentWinner = winnerList[0];
     displayOneWinner( currentWinner ,  maxRank);
     
     }//this else will print if there is only one winner;
    
    
}//end of determineWinner()


/***********************************************************************************/
/* displayOneWinner() will get two int values, one is for the index of the player 
   that won, and the second one is for the index of the winning poker rank.
   If maxRank is -1, then maxRank will be set to '0' in order to retrieve the 
   enum rank 'HIGH CARD'. the rest of the output will be deternimed by the player
   index and the enum index. The corresponding enum rank will be printed using 
   enumRank_To_String() with the enum rank index as a parameter. */
/***********************************************************************************/


void displayOneWinner( int winner , int maxRank ){
    
    if( maxRank == -1){
        
        maxRank = 0;
        
    }//will print HIGH CARD
    
    printf("\n\n*******************************\n");
    printf("*      --  Winner!  --        *\n");
    printf("*******************************\n");
    printf("\n     ----* Player %d *----\n\n" , winner);
    
    printf("\nWinning Poker Rank: ");
    enumRank_To_String( maxRank );
    printf("\n\n ");
    
    
    
}//end displayOneWinner()

/***********************************************************************************/
/* displayPokerRanks() gets an enum rank array and a int that represents the player
   index. The functions retrieves the rank index from the enum rank array where they
   are stored and matches it with its corresponding rank output from *ranks[].
   This output is matched with the player index it corresponds to and displays them
   together. */
/***********************************************************************************/


void displayPokerRanks( enum rank list[] , int players ){
    
    int count;
    int playerCount = 1;
    
    enum rank result;
    
    /* the elements in the array below have been modified with spaces in order to acomodate
    the output display in the program */
    
    char *ranks[ ] = { "   High Card" , "   One Pair" , "   Two Pairs" , "Three of a Kind",
        "   Straight" ,  "   Flush" , "  Full House" , "Four of a Kind" , "Straight Flush"};
    
    printf("\n\n*******************************\n");
    printf("*  -- Player's Poker Hand --  *\n");
    printf("*******************************\n\n");
    
    for( count = 1; count <= players ; count++){
        
        result = list[ count ];
        
        printf("     ----* Player %d *----\n\n" , playerCount);
        
        printf("\t%s \n\n" , ranks[result] );
        
        playerCount++;
    }
    
}//end of displayPokerRanks()


/***********************************************************************************/
/* displayWinner() will get an int array and two int values, one is for the index 
   of the player that won, and the second one is for the index of the winning poker 
   rank. The array will hold the player index that has a winning poker hand 
   The output will be determined depending on how many winners they were
   the rest of the output will be deternimed by the player
   index and the enum index. The corresponding enum rank will be printed using
   enumRank_To_String() with the enum rank index as a parameter. */
/***********************************************************************************/


void displayWinner( int list[] , int winnerCount , int maxRank ){
    
    int count = 0;
    
    if ( winnerCount == 1){
        
        printf("\n\n*******************************\n");
        printf("*      --  Winner!  --        *\n");
        printf("*******************************\n");
        printf("\n         * Player %d *\n\n" , list [ count]);
    
    }
    else{
        
        printf("\n\n*******************************\n");
        printf("*      --  Winners!  --       *\n");
        printf("*******************************\n");
        
        for( count = 0 ; count < winnerCount; count++){
            
            printf("\n         * Player %d *\n" , list[ count ]);
        
        }
        
    }//end of else
    
    printf("\nWinning Poker Rank: ");
    enumRank_To_String( maxRank );
    printf("\n\n*******************************");
    printf("\n\n");

}//end of displayWinner()


/***********************************************************************************/
/* enumRank_To_String() accepts an int value where the int value represents the 
   rank index as listed in the enum ranks. Depending on the index it was given, 
   the appropiate 'string' will be printed. (indexes accepted 0-8 )*/
/***********************************************************************************/


void enumRank_To_String( int value ){
    
    char *ranks[ ] = { "High Card" , "One Pair" , "Two Pairs" , "3 of a Kind",
        "Straight" ,  "Flush" , "Full House" , "4 of a Kind" , "Straight Flush"};
    
    printf("%s" , ranks[value]);
    
}//end of enumRank_To_String()






