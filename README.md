# WORDLE GAME

DESCRIPTION:
-----------
Wordle is a web-based word guessing game where the player gets six attempts to guess a 5-letter word. After each guess, the letters in the word will be colored to give the user hints about their accuracy:
- Green and Bold: The letter is correct and in the right position.
- Red and Bold: The letter is correct but in the wrong position.
- Normal: The letter is not in the word.

REQUIREMENTS:
------------
- Wt Web Toolkit

SETUP:
-----
1. Ensure you have the Wt Web Toolkit installed.
2. Compile and run the application.

USAGE:
-----
1. Launch the Wordle web application.
2. Enter your 5-letter word guess in the provided text box.
3. Click on the 'Submit' button or press 'Enter' to submit your guess.
4. Letters will be colored based on their accuracy.
5. You have a total of six attempts to guess the word correctly.
6. If you run out of guesses, the correct word will be displayed, and you'll be prompted to play again.

FILES:
-----
- main.cpp: Main file to compile and run the game.
- Wordle.cpp: Contains the main logic of the game.
- Wordle.h: Header file for the Wordle class.
- style.css: Stylesheet for the game's appearance.
- words.txt: A file containing possible 5-letter words for the game.\
- Makefile: Used to make the cpp files and run the program

BUGS AND LIMITATIONS:
---------------------
- Only words present in the words.txt file can be used as the word to guess.
- Guesses can be any combination of letters, does not have to make up a valid word, however all answers are valid.

CREDITS:
--------

Game was coded and designed by Joel Daniel.
