/*-------------------------------------------------
| File: Wordle.cpp
| Author: Taylor Carlson
| Purpose: The purpose of this code is to create a game called "Wordle". The program uses a file to randomly choose words from a .txt file
| to be the correct answer for the user's game. The program then prompts the user to enter a five letter word where it then checks the letters
| of the user's input to the correct answer. If the letter is in the word, but not in correct spot, then the letter will appear yellow. If the
| letter is in the correct spot, then it will appear green. The user gets six tries to guess the word and win the game. If not, then the user loses. 
|
|-------------------------------------------------*/

// imports needed for the program
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
using namespace std;

int main() {
    // Creates variables needed throughout the program
    string guess;
    int tries = 6;
    vector<string> wordleWords;
    // Checks for text file
    ifstream input("WordleWords.txt");
    string word;

    // Loops through the text file and inputs it into the wordleWords vector. 
    while (getline(input, word)) {
        wordleWords.push_back(word);
    }

    // Random number generator based on the time to change word every time a user plays
    srand(static_cast<unsigned int>(time(0)));
    // Assigns random word to correctAnswer
    string correctAnswer = wordleWords[rand() % wordleWords.size()];
    cout << "Let's play Wordle!!\n";

    // Loops until user runs out of tries
    for (int i = 0; i < tries; i++) {
        cout << "You have " << tries - i << " tries left" << endl;
        cout << "Enter 5-letter word to guess (enter 'Q' to quit): ";
        // Gets user guess
        getline(cin, guess);

        // Quits the program if user enters Q
        if (guess == "Q" || guess == "q") {
            break;
        }
        // If the user does not enter a 5 letter word, the program prompts user to try again
        if (guess.length() != 5) {
            cout << "Enter a 5-letter word" << endl;
            i--; 
            continue;
        }

        // Variables to store checked letters and which letters should change colors
        vector<bool> filtered(5, false); 
        vector<string> coloredLetters(5, "white");

        // Loop to see if any letters are in correct spots as the correct answer and sets the letter to green
        for (int j = 0; j < 5; j++) {
            if (guess[j] == correctAnswer[j]) {
                coloredLetters[j] = "green";
                filtered[j] = true;
            }
        }

        // Loops to check for the ones that aren't green to see if they are in the word but not in correct spot. 
        for (int j = 0; j < 5; j++) {
            if (coloredLetters[j] != "green") {
                for (int k = 0; k < 5; k++) {
                    if (!filtered[k] && guess[j] == correctAnswer[k]) {
                        // Stores letter as yellow
                        coloredLetters[j] = "yellow";
                        filtered[k] = true;
                        break;
                    }
                }
            }
        }

        // Prints out letters as assigned colors
        for (int j = 0; j < 5; j++) {
            if (coloredLetters[j] == "green") {
                cout << "\033[32m" << guess[j] << "\033[0m";
            } 
            else if (coloredLetters[j] == "yellow") {
                cout << "\033[33m" << guess[j] << "\033[0m";
            } 
            else {
                cout << guess[j]; 
            }
        }

        cout << endl;

        // If the user has all green letters, then they win
        if (guess == correctAnswer) {
            cout << "You win!" << endl;
            break;
        }  
        // If the user does not have all green letters and out of tries, then they lose
        else if (i == tries - 1) {
            cout << "You lost! The correct word was: " << correctAnswer << endl;
        }
    }


    return 0;
}
