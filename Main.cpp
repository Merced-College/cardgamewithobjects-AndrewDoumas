/* 
Kirsten Richards
Skylee Blaine
Andrew Doumas

1/28/25
Making a Card Game with OOD
*/

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

//your job is to fix this object
class Card { // Keeps a card object
public:

  Card() : suit(""), rank(""), value(0) {}

  Card(string SUITS,string RANKS,int VALUES){
    setSuit(SUITS);
    setRank(RANKS);
    set_value(VALUES);
  }

  //put the constructors and getters and setters here:

  //getter for suit
  string getSuit(){
    return suit;
  }

  //getter for rank
  string getRank(){
    return rank;
  }

  // getter for value
  int get_value() {
    return value;
  }

 

  //print card
  void print_card(){
    cout << rank << " of " << suit << endl;
  }

private:
  //put data variables here, look below to see what data variables you should have
  string suit;
  string rank;
  int value;

   //setter for suit
  void setSuit(string SUIT) {
    suit = SUIT;
  }

  //setter for rank
  void setRank(string RANK) {
    rank = RANK;
  }

  //setter for value
  void set_value(int VALUES) {
    value = VALUES;
  }
};

//define your getters and setters here

//the rest of the code is working code - if you define your object above
const string SUITS[] = {"Hearts", "Diamonds", "Clubs", "Spades"};
const string RANKS[] = {"2", "3",  "4",    "5",     "6",    "7",  "8",
                        "9", "10", "Jack", "Queen", "King", "Ace"};
const int VALUES[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11};

// int DECK[52];
Card deck[52];
int currentCardIndex = 0;
/*
defines the arrays and variables related to a deck of playing cards through the
suits, ranks, the current card index, and the deck itself.
*/

//win,loss,tie counters
int wins = 0;
int losses = 0;
int ties = 0;


// function that creates deck
void initializeDeck() {
  int deckIndex = 0;
  for (int suitIndex = 0; suitIndex < 4; suitIndex++) {
    for (int rankIndex = 0; rankIndex < 13; rankIndex++) {
      // Card(string suit, string rank, int value);
      deck[deckIndex++] =
          Card(SUITS[suitIndex], RANKS[rankIndex], VALUES[rankIndex]);
    }
  }
}

//function to print deck for debugging purposes
void printDeck() {
  for (int i = 0; i < 52; i++)
  
    deck[i].print_card();
}

// function to randomize deck
void shuffleDeck() {
  srand((time(0)));
  for (int i = 0; i < 52; i++) {
    int index = rand() % 52;
    Card temp = deck[i]; // these next three lines are a swap function
    deck[i] = deck[index];
    deck[index] = temp;
  }
}

//function to deal a card
Card dealCard() { 
  //reshuffles deck if the end of the deck has been reached
  if(currentCardIndex >= 52){
    shuffleDeck();
    currentCardIndex = 0;
  }
  return deck[currentCardIndex++]; 
}

//function to deal the player 2 cards at the start
int dealInitialPlayerCards() {
  Card card1 = dealCard();
  Card card2 = dealCard();
  cout << "Your cards: "<<endl;
  card1.print_card();
  card2.print_card();
  //cout << "Your cards: " << RANKS[card1 % 13] << " of " << SUITS[card1 / 13]
     //<< " and " << RANKS[card2 % 13] << " of " << SUITS[card2 / 13] << endl;
  return card1.get_value() + card2.get_value();
  //return cardValue(card1) + cardValue(card2);
}

//function to deal the dealer 1 card at the start
int dealInitialDealerCards() {
    Card card1 = dealCard();
    cout << "\nDealer's card: " << card1.getRank() << " of " << card1.getSuit()  << endl;
    return card1.get_value();
}

// function for player turn logic
int playerTurn(int playerTotal) {
  while (true) {
    cout << "Your total is " << playerTotal << ". Do you want to hit or stand?"
         << endl;
    string action;
    getline(cin, action);
    if (action == "hit") {
      Card newCard = dealCard();
      //playerTotal += cardValue(newCard);
      playerTotal += newCard.get_value();
      cout << "You drew a ";
      newCard.print_card();
      //cout << "You drew a " << RANKS[newCard % 13] << " of "
           //<< SUITS[newCard / 13] << endl;
      if (playerTotal > 21) {
        break;
      }
    } else if (action == "stand") {
      break;
    } else {
      cout << "Invalid action. Please type 'hit' or 'stand'." << endl;
    }
  }
  return playerTotal;
}

//function for logic behind dealer turn
int dealerTurn(int dealerTotal) {
  Card newCard;
    while (dealerTotal < 17) { // dealer draws if total is less than 17
      newCard = dealCard();
      cout<<"The dealer drew a "<< newCard.getRank() << " of " << newCard.getSuit()<<endl;
      dealerTotal += newCard.get_value();
      cout << "Dealer's total is " << dealerTotal << endl;
    }
    cout<<endl;
    return dealerTotal;
}

//function to determine who wins
void determineWinner(int playerTotal, int dealerTotal) {
    if (dealerTotal > 21 || playerTotal > dealerTotal) {

        if(dealerTotal > 21){
          cout<<"Dealer busted"<< endl;
        }

        cout << "You win!" << endl;
        //add_win();
        //add_chips();
    } else if (dealerTotal == playerTotal) {
        cout << "It's a tie!" << endl;
        //add_tie();
    } else {
        cout << "Dealer wins!" << endl;
        //add_losses();
        //remove_chips();
    }
}


int main() {
  initializeDeck();
  //printDeck();
  shuffleDeck();
  //printDeck();
  int playerTotal;
  int dealerTotal;

  bool continue_playing = true;
  bool play_another = true;
  bool player_bust = false;
  string play_again;


  while(true == continue_playing){

    player_bust = false;

    playerTotal = dealInitialPlayerCards();
    dealerTotal = dealInitialDealerCards();

    cout << "\nThe player total is " << playerTotal << endl;
    cout<<"The dealer total is "<< dealerTotal <<"\n" << endl;
    //int dealerTotal = dealInitialDealerCards();

    playerTotal = playerTurn(playerTotal);
    if (playerTotal > 21) {
      cout << "You busted! Dealer wins." << endl;
      player_bust = true;
    }

    
      // dealer turn/determine winner if the player does not bust
      if(player_bust != true){
        dealerTotal = dealerTurn(dealerTotal);

        determineWinner(playerTotal, dealerTotal);
      }

    // determine if the player wishes to play another game
    play_another = true;
    while(play_another == true){
      cout<<'\n'<< "Would you like to play again?"<<'\n'<<"Please enter either yes or no"<<endl;

      // gets player choice and converts string to lowercase
      play_again = "";
      cin>> play_again;
      std::transform(play_again.begin(), play_again.end(), play_again.begin(), ::tolower); 


      //determines player input
      if(play_again == "yes" || play_again == "no"){
        cout<< play_again<<endl;
        play_another = false;
        if(play_again == "no"){
          play_another = false;
          continue_playing = false;
        }
      }
      else{
        cout<<"Something went wrong..."<<endl;


      }
    }
  }
}
