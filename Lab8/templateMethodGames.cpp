// Games, Template Method example
// Mikhail Nesterenko, Modified by Hunter Harbison
// 2/4/2014, 3/22/2022

#include <ctime>
#include <cstdlib>
#include <iostream>

using std::cout; using std::endl; using std::cin;

// template for any game where players take 
// turns to make moves
// and there is a winner
class Game{
public:
   Game():playersCount_(0), movesCount_(0), playerWon_(noWinner){}

   // template method
   void playGame(const int playersCount = 0) {
      playersCount_ = playersCount;
      movesCount_=0;

      initializeGame();

      for(int i=0; !endOfGame(); i = (i+1) % playersCount_ ){
	    makeMove(i);
	    if (i==playersCount_-1) 
	        ++movesCount_; 
      }
      printWinner();
   }

   virtual ~Game(){}

protected:
   // primitive operations
   virtual void initializeGame() = 0;
   virtual void makeMove(int player) = 0;
   virtual void printWinner() = 0;
   virtual bool endOfGame() { return playerWon_ != noWinner;} // this is a hook
                   // returns true if winner is decided
   static const int noWinner=-1;

   int playersCount_;
   int movesCount_;
   int playerWon_;
};

// Monopoly - a concrete game implementing primitive 
// operations for the template method
class Monopoly: public Game {
public:  
   // implementing concrete methods
   void initializeGame(){
      playersCount_ = rand() % numPlayers_ + 1 ; // initialize players
   }

   void makeMove(int player) {
      if (movesCount_ > minMoves_){ 
	 const int chance = minMoves_ + rand() % (maxMoves_ - minMoves_);
	 if (chance < movesCount_) playerWon_= player;
      }
   }

   void printWinner(){
      cout << "Monopoly, player "<< playerWon_<< " won in "
	   << movesCount_<< " moves." << endl;
   }

private:
   static const int numPlayers_ = 8; // max number of players
   static const int minMoves_ = 20; // nobody wins before minMoves_
   static const int maxMoves_ = 200; // somebody wins before maxMoves_
};

// Chess - another game implementing
// primitive operations
class Chess: public Game {
public:
   void initializeGame(){
      playersCount_ = numPlayers_; // initalize players
      for(int i=0; i < numPlayers_; ++i) 
	     experience_[i] = rand() % maxExperience_ + 1 ; 
   }

   void makeMove(int player){
      if (movesCount_ > minMoves_){
	 const int chance = (rand() % maxMoves_) / experience_[player];
	 if (chance < movesCount_) playerWon_= player;
      }
   }

   void printWinner(){
      cout << "Chess, player " << playerWon_ 
	   << " with experience " << experience_[playerWon_]
	   << " won in "<< movesCount_ << " moves over"
	   << " player with experience " << experience_[playerWon_== 0 ? 1:0] 
           << endl;
   }

private:
   static const int numPlayers_ = 2;
   static const int minMoves_ = 2; // nobody wins before minMoves_
   static const int maxMoves_ = 100; // somebody wins before maxMoves_
   static const int maxExperience_ = 5; // player's experience
                              // the higher, the greater probability of winning
   int experience_[numPlayers_]; 
};
class Dice: public Game{
public:
  void initializeGame(){
      srand(time(nullptr));
      playersCount_=numberPlayers_;
      movesCount_=0;
      cout << "Welcome to the Dice Game\nCPU vs You! The game that the best highscore wins.\nThe CPU begins\n\n";
      for(int i = 0; i < 5; ++i){
		  	cpuDice[i] = 0;
			  playerDice[i] = 0;
      }
   }

  void makeMove(int player) {
    if(player == 0){
			cout << "CPU's Turn\n";
			if(rand()%2 == 0){
				cout << "CPU has skipped their roll!\n";
				++skips;
    }
    else{
      skips = 0;
			cpuSum = 0;
			cout << "Cpu rolled: ";
			for(int i = 0; i < 5; ++i){
			  cpuDice[i] = rand() % 6 + 1;
			  cout << cpuDice[i] << " ";
			  cpuSum = cpuSum + cpuDice[i];
			}
		  cout << " = " << cpuSum;
      if(cpuSum>cpuHigh) cpuHigh=cpuSum;
      cout << ", CPU's highest score is " << cpuHigh << "\n";
    }
  }
  if(player != 0){
    char skip;
    cout << "Your Turn\n";
		cout << "Do you want to skip your roll? (Y/N) ";
		cin >> skip;
		if(skip == 'N' || skip == 'n'){
      skips = 0;
		  playerSum = 0;
      cout << "Player's roll: ";
		  for(int i = 0; i < 5; ++i){
		    playerDice[i] = rand() % 6 + 1;
		    cout << playerDice[i] << " ";
		    playerSum= playerSum+playerDice[i];
			}
      cout << " = " << playerSum;
      if(playerSum>playerHigh) playerHigh=playerSum;
      cout << ", your highest score is " << playerHigh << "\n";
			}
      else{
				cout << "You skipped your roll.\n";
				++skips;
			}
    cout << "\n";
    }  
  }
      
     
  void printWinner(){
      if(cpuHigh < playerHigh) cout << "You won!\n";      
		  if(cpuHigh == playerHigh) cout << "The game is a draw!\n";      
		  if(cpuHigh > playerHigh) cout << "The CPU won!\n Try again!\n";      
   }
   
   bool endOfGame(){
		if(movesCount_ == 3 || skips == 2){
			return true;
		}
		return false;
	}

private:
  int cpuDice[5];
  int playerDice[5];
  //static const int rounds;
  static const int numberPlayers_ = 2;
  int skips;
  int cpuSum;
  int playerSum;
  int playerHigh;
  int cpuHigh;
   
};

int main() {
   srand(time(nullptr));

   Game* gp = nullptr;

/*
   // play chess 10 times
   for (int i = 0; i < 10; ++i){ 
      gp = new Chess;
      gp->playGame(); 
      delete gp;
   }
      

   // play monopoly 8 times
   for (int i = 0; i < 8; ++i){
      gp = new Monopoly;
      gp->playGame(); 
      delete gp;
   } */
   gp = new Dice;
   gp ->playGame();
   delete gp;
}