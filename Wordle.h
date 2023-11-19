#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>

class Wordle : public Wt::WApplication
{
public:
  Wordle(const Wt::WEnvironment& env);

private:
  Wt::WText    *guesses_=NULL; 
  Wt::WText    *guessesTwo_=NULL;
  Wt::WText    *guessesThree_=NULL;
  Wt::WText    *guessesFour_=NULL;
  Wt::WText    *guessesFive_=NULL;
  Wt::WText    *guessesSix_=NULL;
  Wt::WText    *match=NULL;
  Wt::WLineEdit *guess_=NULL;
  Wt::WString wordToCompare="";

  void check();

  void getGuessWord();

  void restart();

   std::string colour(std::string para);
  
};
