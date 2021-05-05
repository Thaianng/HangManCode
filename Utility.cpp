#include "Header.h"

char readAGuess()
{
    char guess;
    cout << "Please enter your next guess: ";
    cin >> guess;
    return guess;
}


string normalize(const string& s)
{
    string news = s;
    transform(s.begin(), s.end(), news.begin(), ::tolower);
    return news;
}

string chooseWord(const string& fileName, const int& index)
{
    vector<string> vocabulary;
    ifstream file(fileName);
    if (!file.is_open())
        return "";

    while (!file.eof()) {
        string line;
        getline(file, line);
        if (file && !line.empty())
            vocabulary.push_back(normalize(line));
    }

    int n = vocabulary.size();
    cout << "vocabulary size = " << n << endl;
    return n > 0 ? vocabulary[index] : "";
}

bool contains(string word, char guess)
{
    return (word.find(guess) != string::npos);
}

void update(string& guessedWord, const string& word, char guess)
{
    int n = guessedWord.length();
    for (int i = 0; i < n; i++) {
        if (word[i] == guess)
            guessedWord[i] = guess;
    }
}

string ChooseTopic()
{
    clearScreen();
    cout << "Select Your Topics" << endl;
    cout << "1. Animal" << endl    
         << "2. Plant" << endl
         << "3. Food and drinks\n";
    cout << "Your choice: ";
    int choice1;
    cin >> choice1;
    if (choice1 == 1)
    {
        clearScreen();
        cout << "Choose Difficulty\n";
        cout << "1.Easy" << endl   
             << "2.Hard\n";
        cout << "Your choice: ";
        int choice2;
        cin >> choice2;
        if (choice2 == 1)
            return "WordList/Animal/EASY.txt";
        else if (choice2 == 2)
            return "WordList/Animal/HARD.txt";
        else
        {
            cout << "\n Invalid Input! Try Again";
            _getch();
            ChooseTopic();
        }
    }
    else if (choice1 == 2)
    {
        clearScreen();
        cout << "Choose Difficulty\n";
        cout << "1.Easy" << endl
            << "2.Hard\n";
        cout << "Your choice: ";
        int choice2;
        cin >> choice2;
        if (choice2 == 1)
            return "WordList/Plant/EASY.txt";
        else if (choice2 == 2)
            return "WordList/Plant/HARD.txt";
        else
        {
            cout << "\n Invalid Input! Try Again";
            _getch();
            ChooseTopic();
        }
    }
    else if (choice1 == 3)
    {
        clearScreen();
        cout << "Choose Difficulty\n";
        cout << "1.Easy" << endl
            << "2.Hard\n";
        cout << "Your choice: ";
        int choice2;
        cin >> choice2;
        if (choice2 == 1)
            return "WordList/FoodAndDrink/EASY.txt";
        else if (choice2 == 2)
            return "WordList/FoodAndDrink/HARD.txt";
        else
        {
            cout << "\n Invalid Input! Try Again";
            _getch();
            ChooseTopic();
        }
    }

    else
    {
        cout << "\n Invalid Input! Try Again";
        _getch();
        ChooseTopic();
    }
}

int ChooseIndex(const string& fileName)
{
    vector<string> vocabulary;
    ifstream file(fileName);
    if (!file.is_open())
        return -1;

    while (!file.eof()) {
        string line;
        getline(file, line);
        if (file && !line.empty())
            vocabulary.push_back(normalize(line));
    }
    int n = vocabulary.size();
    return rand() % n;
}

//Main game
void Game()
{
    srand((unsigned int)(time(NULL)));
    clock_t start = clock();
    string fileName = ChooseTopic();
    string fileHint = FileHint(fileName);
    while (true) {
        int index = ChooseIndex(fileName);
        string word = chooseWord(fileName, index);
        string hint = chooseWord(fileHint, index);
        if (word.empty()) {
            cout << "No word available in " << fileName << endl;
            return;
        }
        string guessedWord = string(word.length(), '-');
        int badGuessCount = 0;
        const int MAX_BAD_GUESS = 7;
        string badGuess;
        bool UseHint = false;
        do {
            renderGame(badGuessCount, guessedWord, badGuess);
            if (UseHint)
                cout << endl << hint << endl;
            char guess = readAGuess();
            if (guess == '#')
            {
                UseHint = true;
                badGuessCount++;
            }
            else if (contains(word, guess)) {
                update(guessedWord, word, guess);
            }
            else {
                badGuessCount++;
                badGuess += guess;
            }
        } while (badGuessCount < MAX_BAD_GUESS && guessedWord != word);

        
        printGameOverInfo(guessedWord, word, badGuessCount);
        clock_t finish = clock();
        double duration = (double)(finish - start) / CLOCKS_PER_SEC;

        ofstream fileOutput;

        fileOutput.open("Score.txt", std::ios::app);
        fileOutput << duration * (7 - badGuessCount) << endl;
        fileOutput.close();

        cout << endl;
        cout << "You need: " << duration << " seconds to walkthrough!!";
        cout << endl;
        cout << "\n";
        cout << "Do you want more (Y/N) ?";
        string answer;
        cin.ignore(1);
        getline(cin, answer);
        if (answer != "Y" && answer != "y")
            break;
        PlaySound(L"Sound.wav", NULL, SND_ASYNC | SND_LOOP);
    }
    ShowMenu();
}

//Load file hints
string FileHint(const string& fileName)
{
    if (fileName == "WordList/Animal/EASY.txt")
        return "WordList/Animal/EASY_HINT.txt";
    else if (fileName == "WordList/Animal/HARD.txt")
        return "WordList/Animal/HARD_HINT.txt";
    else if (fileName == "WordList/FoodAndDrink/EASY.txt")
        return "WordList/FoodAndDrink/EASY_HINT.txt";
    else if (fileName == "WordList/FoodAndDrink/HARD.txt")
        return "WordList/FoodAndDrink/HARD_HINT.txt";
    else if (fileName == "WordList/Plant/EASY.txt")
        return "WordList/Plant/EASY_HINT.txt";
    else if (fileName == "WordList/Plant/HARD.txt")
        return "WordList/Plant/HARD_HINT.txt";
}

void HTP()
{
    clearScreen();
    cout << " 1. Enter the characters you guess." << endl;
    cout << " 2. Each time you type wrong, a part of man will appear." << endl;
    cout << " 3. You have max 6 times wrong." << endl;
    cout << endl;
    cout << " 4. TIPS: you should guess the vowels first!!" << endl;
    cout << endl;
    cout << "Return (press n/N): ";
    char x;
    cin >> x;
    if (x == 'r' or x == 'R') ShowMenu();
}