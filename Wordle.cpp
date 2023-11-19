#include <fstream>
#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WColor.h>
#include <Wt/WCssDecorationStyle.h>
#include <Wt/WText.h>
#include <iostream>
#include <cctype>
#include "Wordle.h"


std::string answerWord="";
int attempts=0;
Wt::WPushButton *button=NULL;
Wt::WText *displayText=NULL;
std::string displayButton ="";
Wt::WColor green = Wt::WColor(255,0,0,255);
Wt::WCssDecorationStyle decor = Wt::WCssDecorationStyle();

/*
 * Wordle constructor initializes the web application.
 * The env argument provides session and initial request info.
 */

Wordle::Wordle(const Wt::WEnvironment& env)
  : WApplication(env)
{

  useStyleSheet("resources/style.css");
   
  setTitle("Wordle");                           // application title
  root()->decorationStyle().setBackgroundColor(Wt::WColor(220, 220, 220)); // RGB(220,220,220) is a shade of grey.
  root()->setStyleClass("largeText");

  // Set up empty guesses_ displays
  guesses_ = root()->addWidget(std::make_unique<Wt::WText>());
  root()->addWidget(std::make_unique<Wt::WBreak>());
  guessesTwo_ = root()->addWidget(std::make_unique<Wt::WText>());
  root()->addWidget(std::make_unique<Wt::WBreak>());
  guessesThree_ = root()->addWidget(std::make_unique<Wt::WText>());
  root()->addWidget(std::make_unique<Wt::WBreak>());
  guessesFour_ = root()->addWidget(std::make_unique<Wt::WText>());
  root()->addWidget(std::make_unique<Wt::WBreak>());
  guessesFive_ = root()->addWidget(std::make_unique<Wt::WText>());
  root()->addWidget(std::make_unique<Wt::WBreak>());
  guessesSix_ = root()->addWidget(std::make_unique<Wt::WText>());
  root()->addWidget(std::make_unique<Wt::WBreak>());


  displayText = root()->addWidget(std::make_unique<Wt::WText>("Enter guesses, 5 letters maximum: "));
  displayButton = "Submit";                                   // creates a button for checking
   
  guess_ = root()->addWidget(std::make_unique<Wt::WLineEdit>());
  guess_->setFocus();
  guess_->setMaxLength(5);                            
   
  button = root()->addWidget(std::make_unique<Wt::WPushButton>(displayButton));  
 
  button->setMargin(5, Wt::Side::Left);                  


  Wordle::getGuessWord();


  // Connect signals with slots
  button->clicked().connect(this, &Wordle::check);
  guess_->enterPressed().connect(std::bind(&Wordle::check, this));
  button->clicked().connect([=]() {
      std::cerr <<  guess_->text() << std::endl;
  });
}

// Fetch a random word for the game
void Wordle::getGuessWord(){
  int lineToRead = rand()%350; // Using 350, since there are 350 available words


  // Open words file
  std::ifstream wordsFile("resources/words.txt");
  if ( wordsFile.is_open() ) { // checks if file is already open
    for (int i = 1; i < lineToRead; i++) {
       getline(wordsFile, answerWord);
    }
  } else {
    std::cerr << "File not read";
  }
  wordsFile.close();
}

// Validate and process the user's guesses_
void Wordle::check()
{
  std::string input="";
  std::string tmp="";

  std::string input2 = guess_->text().toUTF8();

    // Check for input length
    if (input2.length() < 5) {
        displayText->setText("Please enter a word with 5 letters.");
        return; // Return early so the rest of the function does not execute
    }

  attempts = attempts+1;


  if ( displayButton=="Restart"){
    Wordle::restart();
  }

  // Submit if user still has guesses, otherwise button says Restart
  if ( (attempts<6)){
      displayText->setText("Enter guesses, 5 letters maximum: ");
      displayButton = "Submit";
      button ->setText(displayButton);  
  } else {
    displayText->setText("You are out of guesses. The correct word was: " + answerWord + ". Play Again?");
    displayButton = "Restart";  
    button ->setText(displayButton);  
  }
 
    // Convert input to uppercase before displaying
    input = (guess_->text()).toUTF8();
    for(auto& c : input) {
      c = std::toupper((unsigned char)c);
    }

   //Print per try
   if (attempts==1){
     guesses_->setTextFormat(Wt::TextFormat::XHTML);
     guesses_->setText(colour(input));
   } else if (attempts==2){
     guessesTwo_->setTextFormat(Wt::TextFormat::XHTML);
     guessesTwo_->setText(colour(input));      
   } else if (attempts==3){
      guessesThree_->setTextFormat(Wt::TextFormat::XHTML);
      guessesThree_->setText(colour(input));
   } else if(attempts==4){
      guessesFour_->setTextFormat(Wt::TextFormat::XHTML);
      guessesFour_->setText(colour(input));
   } else if (attempts==5){
      guessesFive_->setTextFormat(Wt::TextFormat::XHTML);
      guessesFive_->setText(colour(input));
   } else if (attempts==6){
      guessesSix_->setTextFormat(Wt::TextFormat::XHTML);
      guessesSix_->setText(colour(input));
   }


}

 // Change text color based on comparison results
 std::string Wordle::colour(std::string para){
  std::string colourStr ="";
  int wordCheck = 0;
  int countCheck = -1;
  std::string strHold ="";
  int num[5]={0,0,0,0,0};


 
  // Compare characters
  for (int count=0; count<para.length(); count++){
      for (int innercount=0; innercount<5; innercount++){
          if((tolower(para[innercount]) == tolower(answerWord[count])) && (count == innercount) && num[innercount] != 2){
              num[innercount] = 2;
              wordCheck += 1;
          } else if((tolower(para[innercount]) == tolower(answerWord[count])) && (count != innercount) && num[innercount] != 2){
              num[innercount] = 1;
          }
      }
  }


    for (int count=0;count<para.length();count++){
      if (num[count] == 0) {
        strHold = para[count];
        colourStr += strHold;
        continue;
      } else if (num[count] == 1) {
            strHold = para[count];
            colourStr +=  "<font color='red'><b>" +  strHold + "</b></font>"; //Red and Bold
            continue; 
        } else {
            strHold = para[count];
            colourStr +=  "<font color='green'><b>" + strHold + "</b></font>"; //Green and Bold
            continue;
      }
    }


   if (wordCheck==5){
    displayText->setText("You guessed correctly. Play Again?");
    displayButton = "Restart";
    button ->setText(displayButton);
   }


   return colourStr;
}


void Wordle::restart(){
    // Reset texts and variables
    attempts=0;
    guesses_->setText("");
    guessesTwo_->setText("");
    guessesThree_->setText("");
    guessesFour_->setText(" ");
    guessesFive_->setText("");
    guessesSix_->setText("");
    getGuessWord();
}



