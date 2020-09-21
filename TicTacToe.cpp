#include <iostream> 
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <ctime>
using namespace std; 

/**
 * Class Board
 *
 * @author Kevin Song, 
 * @author Elizabeth Ostadali
 */
class Board {
	public:
		Board();
		// Gamemode testers
		void twoPlayer();
		void singlePlayer(int);
		// Checks for 3 in a row
		void checkBoard(int);
		// Checking state of game
		void checkForWin();
		void checkForCatsGame();
		// Displays the board
		void displayBoard();
		// Handle gameover
		void handleWin(int);
		void handleCatsGame();
		int whoseMove;

		//Board
		int grid[9]; //0 is empty, 1 is X, 2 is O
		int startSquare;
		int endSquare;
		int direction;
		// Game run time variables
		int player1Symbol;
		int player2Symbol;
	private:
		// Stats
		int numWins1; // number of wins for player 1
		int numWins2; // number of wins for player 2
		int numCatsGames; // number of cats games
		// States of game
		bool gameOver;
		bool player1Win;
		bool player2Win;
		bool catsGame;
};

/**
 * Constructor Board::Board()
 * Instantiates a Board object.
 */
Board::Board() {
	for (int i = 0; i < 9; i++) {
		grid[i] = 0;
	}
	player1Symbol = 1;
	player2Symbol = 2;
	whoseMove = 1;
	numWins1 = 0;
	numWins2 = 0;
	numCatsGames = 0;
	gameOver = false;
	player1Win = false;
	player2Win = false;
	catsGame = false;
	startSquare = 0;
	endSquare = 0;
	direction = 0;
};


/**
 * Class Easy
 * Defines the AI on easy mode.
 */
class Easy {
	public:
		Easy();
		int pickSquare(Board *);
	private:
		bool aiFirst;
		int boardValues[9];
};

/**
 * Constructor Easy::Easy()
 * Instantiates an Easy object.
 */
Easy::Easy() {
	aiFirst = false;
	for (int i = 0; i < 9; i++) {
		boardValues[i] = 0;
	}
}

/**
 * Class Medium
 * Defines the AI on medium mode.
 */
class Medium {
	public:
		Medium();
		int pickSquare(Board *);
	private:
		bool aiFirst;
		int boardValues[9];
};

/**
 * Constructor Medium::Medium()
 * Instantiates a Medium object.
 */
Medium::Medium() {
	aiFirst = false;
	for (int i = 0; i < 9; i++) {
		boardValues[i] = 0;
	}
}

/**
 * Class Hard
 * Defines the AI on hard mode.
 */
class Hard {
	public: 
		Hard();
		int pickSquare(Board *);
		void specialAI(Board *);
	private:
		bool aiFirst;
		int boardValues[9];
};

/**
 * Constructor Hard::Hard()
 * Instantiates a Hard object.
 */
Hard::Hard() {
	aiFirst = false;
	for (int i = 0; i < 9; i++) {
		boardValues[i] = 0;
	}
}

/**
 * function Board::displayBoard()
 * Displays the board.
 * @requires
 * 	(@code) whoseMove has been updated
 * @requires
 * 	(@code) grid has been initialized
 * @ensures
 * 	the output TicTacToe board represents (@code) grid, with 0 being empty, 1 being X, and 2 being O
 */
void Board::displayBoard() {
	/**
	 * | | | |
	 * | | | |
	 * | | | |
	 */

	cout << "\n";
	if (whoseMove == 1) {
		cout << "Player 1 Move:" << "\n";
	} else {
		cout << "Player 2 Move:" << "\n";
	}

	for (int i = 0; i < 9; i++) {
		cout << "|";
		if (grid[i] == 0) {
			cout << i;
		} else if (grid[i] == 1) {
			cout << "X";
		} else if (grid[i] == 2){
			cout << "O";
		}
		
		if ((i + 1) % 3 == 0) {
			cout << "|\n";
		}
	}
	cout << "\n";
}

/**
 * function Board::twoPlayer()
 * Tester for running a two player game.
 * @precondition
 * 	(@code) gameOver == false
 * @postcondition
 *	(@code) gameOver == true
 * @requires
 * 	(@code) grid has been initialized
 * @requires
 * 	(@code) player1Symbol has been initialized
 * @requires
 * 	(@code) player2Symbol has been initialized
 * @ensures
 * 	a two player game is run through
 */
void Board::twoPlayer() {
	displayBoard();

	int player = 0;
	while (!gameOver) {
		int move = 0;
		cin >> move;
		if (player % 2 == 0) {
			grid[move] = player1Symbol;
			whoseMove = 2;
		} else {
			grid[move] = player2Symbol;
			whoseMove = 1;
		}
		displayBoard();
		checkForWin();
		if (!player1Win && !player2Win) {
			checkForCatsGame();
		}
		player++;
	}
}

/**
 * function Board::singlePlayer()
 * Tester for running a single player game.
 * @parameter
 * 	difficulty (int) is 1-3
 * @precondition
 * 	(@code) gameOver == false
 * @postcondition
 *	(@code) gameOver == true
 * @requires
 * 	(@code) grid has been initialized
 * @requires
 * 	(@code) player1Symbol has been initialized
 * @requires
 * 	(@code) player2Symbol has been initialized
 * @ensures
 * 	a single player game is run through
 */
void Board::singlePlayer(int difficulty) {
	Easy easy;
	Medium medium;
	Hard hard;

	displayBoard();
	int player;
	
	if (whoseMove == 1) {
		player = 0;
	} else {
		player = 1;
	}

	while (!gameOver) {
		if (player % 2 == 0) {
			// Player's move
			int move = 0;
			cin >> move;
			grid[move] = player1Symbol;
			whoseMove = 2;
		} else {
			// AI's move
			int n;
			switch (difficulty) {
				case 1: {
					n = easy.pickSquare(this);
					break;
				}
				case 2: {
					n = medium.pickSquare(this);
					break;
				}
				case 3: {
					n = hard.pickSquare(this);
					break;
				}
			}
			grid[n] = player2Symbol;
			whoseMove = 1;
		}
		displayBoard();
		checkForWin();
		if (!player1Win && !player2Win) {
			checkForCatsGame();
		}
		player++;
	}
}

/**
 * function Board::checkBoard()
 * Sets up cases for the rows.
 * @parameter
 * 	c (int) is a case 0-7
 * @requires
 * 	(@code) c is an integer from 0 to 7
 * @updates
 * 	startSquare
 * @updates
 * 	endSquare
 * @updates
 * 	direction
 */
void Board::checkBoard(int c) {
	switch (c) {
		case 0: {
			startSquare = 0;
			endSquare = 2;
			direction = 1;
			break;
		}
		case 1: {
			startSquare = 3;
			endSquare = 5;
			direction = 1;
			break;
		}
		case 2: {
			startSquare = 6;
			endSquare = 8;
			direction = 1;
			break;
		}
		case 3: {
			startSquare = 0;
			endSquare = 6;
			direction = 3;
			break;
		}
		case 4: {
			startSquare = 1;
			endSquare = 7;
			direction = 3;
			break;
		}
		case 5: {
			startSquare = 2;
			endSquare = 8;
			direction = 3;
			break;
		}
		case 6: {
			startSquare = 0;
			endSquare = 8;
			direction = 4;
			break;
		}
		case 7: {
			startSquare = 2;
			endSquare = 6;
			direction = 2;
			break;
		}
	}
}

/**
 * function Board::checkForWin()
 * Checks to see if there is a three in a row of X or O.
 * @requires
 * 	(@code) grid has been initialized and/or filled
 * @ensures
 * 	if either player has one, the win is handled
 */
void Board::checkForWin() {
	int winCase = 0;
	int xInRow = 0;
	int oInRow = 0;
	while (winCase < 8) {
		xInRow = 0;
		oInRow = 0;
		checkBoard(winCase);
		for (int i = startSquare; i < endSquare + 1; i+=direction) {
			if (grid[i] == 1) {
				xInRow++;
			} else if (grid[i] == 2) {
				oInRow++;
			}
		}
		if (xInRow == 3) {
			handleWin(1);
			break;
		} else if (oInRow == 3) {
			handleWin(2);
			break;
		}
		winCase++;
	}
}

/**
 * function Board::checkForCatsGame()
 * Checks the board to see if it is a cats game.
 * @requires
 * 	(@code) grid has been initialized and/or filled
 * @ensures
 * 	if there is a cats game, the cats game is handled
 */
void Board::checkForCatsGame() {
	int count = 0;
	for (int i = 0; i < 9; i++) {
		if (grid[i] == 0) {
			count++;
		}
	}
	if (count == 0) {
		handleCatsGame();
	}
}

/**
 * function Board::handleWin()
 * Handles the scenario in which one of the player wins.
 * @parameter
 * 	n (int)
 * @requires
 * 	n is an integer that is either 1 or 2
 * @updates
 * 	(@code) player1Win
 * @updates
 * 	(@code) player2Win
 * @ensures
 * 	either player1 wins or player2 wins
 */
void Board::handleWin(int n) {
	gameOver = true;
	if (n == player1Symbol) {
		cout << "Player 1 Wins." << "\n";
		player1Win = true;
		numWins1++;
	} else if (n == player2Symbol) {
		cout << "Player 2 Wins." << "\n";
		player2Win = true;
		numWins2++;
	}
}

/**
 * function Board::handleCatsGame()
 * Handles the scenario in which there is a cats game.
 * @updates
 * 	(@code) gameOver
 * @updates
 * 	(@code) catsGame
 */
void Board::handleCatsGame() {
	cout << "Cats Game!" << "\n";
	numCatsGames++;
	gameOver = true;
	catsGame = true;
}

/**
 * function Easy::pickSquare()
 * The easy AI chooses its best square.
 * @parameter
 * 	board (pointer to a Board object)
 * @requires
 * 	!catsGame
 * @requires
 * 	!player1Win
 * @requires
 * 	!player2Win
 * @requires
 * 	!gameOver
 * @requires Board is not empty
 */
int Easy::pickSquare(Board * board) {
	/** 
	 * Assign values to squares
	 */
	int choice = -1;
	// 0, 2, 6, 8
	for (int i = 0; i < 9; i+=2) {
		if (i != 4) {
			boardValues[i] = 2;
		} else {
			boardValues[i] = 4;
		}
	}
	boardValues[4] = 3;
	// 1, 3, 5, 7
	for (int i = 1; i < 8; i+=2) {
		boardValues[i] = 1;
	}
	// Filled squares are 0
	for (int i = 0; i < 9; i++) {
		if (board->grid[i] != 0) {
			boardValues[i] = 0;
		}
	}

	/**
	 * Finds the square with max and chooses it,
	 * or if there are multiple maxes, randomly chooses from them
	 */
	int max = 0;
	for (int i = 0; i < 9; i++) {
		if (boardValues[i] > max) {
			max = boardValues[i];
		}
	}
	int numCandidates = 0;
	for (int i = 0; i < 9; i++) {
		if (boardValues[i] == max) {
			numCandidates++;
		}
	}
	if (numCandidates > 0) {
		int candidates[numCandidates];
		int counter = 0;
		for (int i = 0; i < 9; i++) {
			if (boardValues[i] == max) {
				candidates[counter] = i;
				counter++;
			}
		}
		srand(time(NULL));
		int r = (rand() % numCandidates);
		choice = candidates[r];
	}
	return choice;
}

/**
 * function Medium::pickSquare()
 * @parameter
 * 	board (pointer to a Board object)
 * @requires
 * 	!catsGame
 * @requires
 * 	!player1Win
 * @requires
 * 	!player2Win
 * @requires
 * 	!gameOver
 * @updates 
 * 	(@code) boardValues
 * @requires Board is not empty
 */
int Medium::pickSquare(Board * board) {
	/** 
	 * Assign values to squares
	 */
	int choice = -1;
	// 0, 2, 6, 8
	for (int i = 0; i < 9; i+=2) {
		if (i != 4) {
			boardValues[i] = 2;
		} else {
			boardValues[i] = 4;
		}
	}
	boardValues[4] = 3;
	// 1, 3, 5, 7
	for (int i = 1; i < 8; i+=2) {
		boardValues[i] = 1;
	}
	// Filled squares are 0
	for (int i = 0; i < 9; i++) {
		if (board->grid[i] != 0) {
			boardValues[i] = 0;
		}
	}
	
	/**
	 * Tests for immediate loss/win
	 */
	int counter = 0;
	do {
		int xInRow = 0;
		int oInRow = 0;

		board->checkBoard(counter);
		for (int i = board->startSquare; i < board->endSquare + 1; i+=board->direction) {
			if (board->grid[i] == 1) {
				xInRow++;
			} else if (board->grid[i] == 2) {
				oInRow++;
			}
		}
		if (xInRow == 2) {
			int emptySquare = -1;
			for (int i = board->startSquare; i < board->endSquare + 1; i+=board->direction) {
				if (board->grid[i] == 0) {
					emptySquare = i;
				}
			}
			if (emptySquare != -1) {
				if (board->player1Symbol == 1) {
					// If it's a possible block
					if (boardValues[emptySquare] < 8) {
						boardValues[emptySquare] = 8;
					}
				} else {
					// If it's a possible win
					boardValues[emptySquare] = 9;
				}
				
			}
		} else if (oInRow == 2) {
			int emptySquare = -1;
			for (int i = board->startSquare; i < board->endSquare + 1; i+=board->direction) {
				if (board->grid[i] == 0) {
					emptySquare = i;
				}
			}
			if (emptySquare != -1) {
				if (board->player1Symbol == 2) {
					// If it's a possible block
					if (boardValues[emptySquare] < 8) {
						boardValues[emptySquare] = 8;
					}
				} else {
					// If it's a possible win
						boardValues[emptySquare] = 9;
				}
			}
		}
		counter++;
	} while (counter < 8);

	/**
	 * Finds the square with max and chooses it,
	 * or if there are multiple maxes, randomly chooses from them
	 */
	int max = 0;
	for (int i = 0; i < 9; i++) {
		if (boardValues[i] > max) {
			max = boardValues[i];
		}
	}
	int numCandidates = 0;
	for (int i = 0; i < 9; i++) {
		if (boardValues[i] == max) {
			numCandidates++;
		}
	}
	if (numCandidates > 0) {
		int candidates[numCandidates];
		int counter = 0;
		for (int i = 0; i < 9; i++) {
			if (boardValues[i] == max) {
				candidates[counter] = i;
				counter++;
			}
		}
		srand(time(NULL));
		int r = (rand() % numCandidates);
		choice = candidates[r];
	}
	return choice;
}

/**
 * function Hard::pickSquare()
 * The hard level AI picks a square that will guarantee either an eventual draw or loss for the player.
 * @parameter
 * 	board (pointer to a Board object)
 * @requires
 * 	!catsGame
 * @requires
 * 	!player1Win
 * @requires
 * 	!player2Win
 * @requires
 * 	!gameOver
 * @updates 
 * 	(@code) boardValues
 * @requires Board is not empty
 */
int Hard::pickSquare(Board * board) {
	/** 
	 * Assign values to squares
	 */
	int choice = -1;
	// 0, 2, 6, 8
	for (int i = 0; i < 9; i+=2) {
		if (i != 4) {
			boardValues[i] = 2;
		} else {
			boardValues[i] = 4;
		}
	}
	boardValues[4] = 3;
	// 1, 3, 5, 7
	for (int i = 1; i < 8; i+=2) {
		boardValues[i] = 1;
	}
	// Filled squares are 0
	for (int i = 0; i < 9; i++) {
		if (board->grid[i] != 0) {
			boardValues[i] = 0;
		}
	}
	
	/**
	 * Tests for immediate loss/win
	 */
	int counter = 0;
	do {
		int xInRow = 0;
		int oInRow = 0;

		board->checkBoard(counter);
		for (int i = board->startSquare; i < board->endSquare + 1; i+=board->direction) {
			if (board->grid[i] == 1) {
				xInRow++;
			} else if (board->grid[i] == 2) {
				oInRow++;
			}
		}
		if (xInRow == 2) {
			int emptySquare = -1;
			for (int i = board->startSquare; i < board->endSquare + 1; i+=board->direction) {
				if (board->grid[i] == 0) {
					emptySquare = i;
				}
			}
			if (emptySquare != -1) {
				if (board->player1Symbol == 1) {
					// If it's a possible block
					if (boardValues[emptySquare] < 8) {
						boardValues[emptySquare] = 8;
					}
				} else {
					// If it's a possible win
					boardValues[emptySquare] = 9;
				}
				
			}
		} else if (oInRow == 2) {
			int emptySquare = -1;
			for (int i = board->startSquare; i < board->endSquare + 1; i+=board->direction) {
				if (board->grid[i] == 0) {
					emptySquare = i;
				}
			}
			if (emptySquare != -1) {
				if (board->player1Symbol == 2) {
					// If it's a possible block
					if (boardValues[emptySquare] < 8) {
						boardValues[emptySquare] = 8;
					}
				} else {
					// If it's a possible win
						boardValues[emptySquare] = 9;
				}
			}
		}
		counter++;
	} while (counter < 8);

	/**
	 * Test for special cases in which the human can trick the AI
	 * This starts after 3 moves have been made
	 */
	int numEmpty = 0;
	for (int i = 0; i < 9; i++) {
		if (board->grid[i] == 0) {
			numEmpty++;
		}
	}
	if (numEmpty == 6) {
		specialAI(board);
	}

	/**
	 * Finds the square with max and chooses it,
	 * or if there are multiple maxes, randomly chooses from them
	 */
	int max = 0;
	for (int i = 0; i < 9; i++) {
		if (boardValues[i] > max) {
			max = boardValues[i];
		}
	}
	int numCandidates = 0;
	for (int i = 0; i < 9; i++) {
		if (boardValues[i] == max) {
			numCandidates++;
		}
	}
	if (numCandidates > 0) {
		int candidates[numCandidates];
		int counter = 0;
		for (int i = 0; i < 9; i++) {
			if (boardValues[i] == max) {
				candidates[counter] = i;
				counter++;
			}
		}
		srand(time(NULL));
		int r = (rand() % numCandidates);
		choice = candidates[r];
	}
	return choice;
}

/**
 * function Hard::specialAI()
 * Deals with 3 cases in which a player can trick the AI into losing
 * @parameter
 * 	board (pointer to a Board object)
 * @requires Board is not empty
 * @updates 
 * 	(@code) boardValues
 */
void Hard::specialAI(Board * board) {
	/**
	 * Case 1: 2 diagonals
	 *
	 * |X| |*|   |*| |X|
	 * | |O| |   | |O| |
	 * |*| |X|   |X| |*|
  	 *
	 * If the AI chooses *, the player wins.
	 */

	// 2 cases of the diagonals occurring
	if ((board->grid[0] == board->player1Symbol && board->grid[8] == board->player1Symbol) 
	|| (board->grid[2] == board->player1Symbol && board->grid[6] == board->player1Symbol)) {
		for (int i = 1; i < 8; i+=2) {
			boardValues[i] = 7;
		}
	}

	/**
	 * Case 2: 2 sides
	 *
	 * | |X| |   |*| | |   | | |*|   | |X| |
	 * | |O|X|   | |O|X|   |X|O| |   |X|O| |
	 * |*| | |   | |X| |   | |X| |   | | |*|
	 *
	 * If the AI chooses *, the player wins.
	 */
	
	if (board->grid[1] == board->player1Symbol && board->grid[5] == board->player1Symbol) {
		boardValues[6] = 0;
	}
	if (board->grid[5] == board->player1Symbol && board->grid[7] == board->player1Symbol) {
		boardValues[0] = 0;
	}
	if (board->grid[3] == board->player1Symbol && board->grid[7] == board->player1Symbol) {
		boardValues[2] = 0;
	}
	if (board->grid[1] == board->player1Symbol && board->grid[3] == board->player1Symbol) {
		boardValues[8] = 0;
	}

	/**
	 * Case 3: 1 diagonal 1 side
	 *
	 * |+|X|+|   |*| |+|   |X| |*|   |+| |X|
	 * | |O| |   | |O|X|   | |O| |   |X|O| |
	 * |*| |X|   |X| |+|   |+|X|+|   |+| |*|
	 *
	 * If the AI chooses *, the player wins. The value of + needs to be increased to block this.
	 */

	// Counts the number of middle side squares occupied by the player
	int numSides = 0;
	for (int i = 1; i < 8; i+=2) {
		if (board->grid[i] == board->player1Symbol) {
			numSides++;
		}
	}
	// If there is one middle side square of the player's, it finds it
	// Then it increases the value of the squares next to it
	if (numSides == 1) {
		if (board->grid[1] == board->player1Symbol) {
			boardValues[0] = 7;
			boardValues[2] = 7;
		}
		if (board->grid[3] == board->player1Symbol) {
			boardValues[0] = 7;
			boardValues[6] = 7;
		}
		if (board->grid[5] == board->player1Symbol) {
			boardValues[2] = 7;
			boardValues[8] = 7;
		}
		if (board->grid[7] == board->player1Symbol) {
			boardValues[6] = 7;
			boardValues[8] = 7;
		}
	}
}

/**
 * function main()
 * Runs the program.
 */
int main() {
	bool exit = false;
	
	while (!exit) {
		cout << "\n" << "MENU" << "\n";
		cout << "[1] - Two Player" << "\n";
		cout << "[2] - Single Player" << "\n";
		cout << "[0] - Quit" << "\n";

		int ans;
		cin >> ans;

		switch (ans) {
			case 1: {
				Board board;
				board.twoPlayer();
				break;
			}
			case 2: {
				cout << "\n" << "Single Player - ";
				cout << "Move Order" << "\n";
				cout << "[1] - Player moves first" << "\n";
				cout << "[2] - AI moves first" << "\n";
				int ans2;
				Board board;
				cin >> ans2;
				switch (ans2) {
					case 1: {
						//Board board;
						board.whoseMove = 1;
						break;
					}
					case 2: {
						//Board board;
						board.whoseMove = 2;
						break;
					}
				}

				cout << "\n" << "Single Player" << "\n";
				cout << "[1] - Easy" << "\n";
				cout << "[2] - Medium" << "\n";
				cout << "[3] - Hard" << "\n";
				cout << "[4] - Statistics" << "\n";
				
				int ans3;
				int difficulty;
				cin >> ans3;
				switch (ans3) {
					case 1: {
						difficulty = 1;
						break;
					}
					case 2: {
						difficulty = 2;
						break;
					}
					case 3: {
						difficulty = 3;
						break;
					}
					case 4: {
						break;
					}
					default: {
						break;
					}
				}
				board.singlePlayer(difficulty);
				break;
			}
			case 0: {
				exit = true;
				break;
			}
			default: {
				exit = true;
				break;
			}
		}
	}
}
