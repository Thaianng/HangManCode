#include "Header.h"

string getHangPicture(int badGuessCount)
{
	string picture[] = { "",
"   ------------\n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"-------        ",
"   ------------\n"
"   |          |\n"
"   |          O\n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"-------        ",
"   ------------\n"
"   |          |\n"
"   |          O\n"
"   |          |\n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"-------        ",
"   ------------\n"
"   |          |\n"
"   |          O\n"
"   |         /|\n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"-------        ",
"   ------------\n"
"   |          |\n"
"   |          O\n"
"   |         /|\\\n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"-------        ",
"   ------------\n"
"   |          |\n"
"   |          O\n"
"   |         /|\\\n"
"   |         / \n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"-------        ",
"   ------------\n"
"   |          |\n"
"   |          O\n"
"   |         /|\\\n"
"   |         / \\\n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"-------        ",

	};
	return picture[badGuessCount];
}

void clearScreen()
{
#ifdef _WIN32
	system("cls");
#elif __linux__
	system("clear");
#endif // _WIN32
}

void renderGame(int badGuessCount, string guessedWord, string badGuess)
{
	clearScreen();
	cout << "Current guess = " << guessedWord << endl;
	cout << "You have made bad " << badGuessCount << " guess(es)"
		<< (badGuess.empty() ? "" : ": ") << badGuess << endl
		<< getHangPicture(badGuessCount) << endl;

}

void printGameOverInfo(string guessedWord, string word, int badGuessCount) // Hinh gia treo luc end game 
{
	renderGame(badGuessCount, guessedWord);
	if (guessedWord != word) {
		vector<string> hanged = {
"   ------------\n"
"   |         /\n"
"   |        O\n"
"   |       /|\\\n"
"   |       / \\\n"
"   |         \n"
"   |         \n"
"   |         \n"
"   |         \n"
"-------        ",
"   ------------\n"
"   |          |\n"
"   |          O\n"
"   |         /|\\\n"
"   |         / \\\n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"-------        ",
"   ------------\n"
"   |           \\\n"
"   |            O\n"
"   |           /|\\\n"
"   |           / \\\n"
"   |             \n"
"   |             \n"
"   |             \n"
"   |             \n"
"-------        ",
"   ------------\n"
"   |          |\n"
"   |          O\n"
"   |         /|\\\n"
"   |         / \\\n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"-------        "
		};
		int n = 0;
		int k = 0;
		PlaySound(L"Wasted.wav", NULL, SND_ASYNC);
		while (k < 10) {
			clearScreen();
			cout << "Game Over!!! You are hanged" << endl
				<< "The correct word is " << word << endl;
			cout << hanged[n];
			cout << endl;
			n = (n + 1) % hanged.size();
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			k++;
		}

	}
	else {
		cout << "Congrats!!! You are free" << endl;
	}
}

void ShowHeader() //the function which shows the header on each screen
{
	clearScreen();
	cout << endl << "+-----------------------------------------------------------------------------+";
	cout << endl << "|                          Hangman Game - By NTAzz                            |";
	cout << endl << "+-----------------------------------------------------------------------------+";
	cout << endl << endl;
	return;
}

void ShowMenu() //this is the main menu of the program
{
	char choice; //to store choice
	ShowHeader();

	PlaySound(L"Sound.wav", NULL, SND_ASYNC | SND_LOOP);
	system("color 2");

	cout << "Select an Option: ";
	cout << "\n1. Start Game";
	cout << "\n2. HighScore";
	cout << "\n3. How to play";
	cout << "\n4. Exit";
	cout << endl << "\t\tMode: ";
	cin >> choice; //Input function returns input values

	if (choice == '1') Game(); //start game
	else if (choice == '2') HS(); //highscore 
	else if (choice == '3') HTP();
	else if (choice == '4') //exit program
	{
		cout << "\t\tExited succesfully!";
		_getch();
		exit(0);
	}
	else
	{
		cout << "\t\tInvalid Input! Try again.";
		_getch();
		ShowMenu();
	}
}


