#include <iostream>
#include <string>
using namespace std;

// Global Access Variables
string input;

// (Step 3) Counts the number of characters in the input that arent whitespace
int GetNumOfNonWSCharacters(string str)
{
   int charCount = 0;
   for(int i = 0; i < str.length(); i++)
   {
      if(str.at(i) != ' ' && str.at(i) != '\n') {charCount++;}
   }
   
   return charCount;
}

// (Step 4) Counts the number of words in the input
int GetNumOfWords(string str)
{
   int charCount = 0;
   for(int i = 1; i < str.length(); i++)
   {
      if((str.at(i) == ' ' && str.at(i-1) != ' ')) {charCount++;}
   }
   
   return ++charCount;
}

// (Part 5) Print an number of instances of a specificed string
int FindText(string target, string str)
{
   int counter = 0;
   int countFrom = 0;
   
   for(int i = 0; i < str.length() - target.length(); i++)
   {
      if(str.substr(i, target.length()) == target) counter++;
   }
   
   return counter;
}

// (Part 6) Replaces all '!' with '.'
string ReplaceExclamation(string &str)
{
   for(int i = 0; i < str.length(); i++)
   {
      if(str.at(i) == '!') str.at(i) = '.';
   }
   
   return str;
}

// (Step 7)
string ShortenSpace(string &str)
{
   for(int i = 0; i < str.length() - 1; i++)
   {
      if(str.at(i) == ' ' && str.at(i+1) == ' ') 
      {
         str.replace(i, 2, " ");
         i--;
      }
   }
   
   return str;
}

// Print Menu from Step 2
char PrintMenu()
{  
   char userInput;

   // Print Menu
   cout << "MENU" << endl;
   cout << "c - Number of non-whitespace characters" << endl;
   cout << "w - Number of words" << endl;
   cout << "f - Find text" << endl;
   cout << "r - Replace all !'s" << endl;
   cout << "s - Shorten spaces" << endl;
   cout << "q - Quit" << endl;
   cout << endl;
   cout << "Choose an option:" << endl;
   
   cin >> userInput;
   
   if(userInput == 'c') cout << "Number of non-whitespace characters: " << GetNumOfNonWSCharacters(input) << endl << endl;
   if(userInput == 'w') cout << "Number of words: " << GetNumOfWords(input) << endl << endl;
   if(userInput == 'f')
   {
      string target;
      cout << "Enter a word or phrase to be found:" << endl;
      getline(cin, target);
      getline(cin, target);
      cout << "\"" << target << "\" instances: " << FindText(target, input) << endl << endl;
   }
   if(userInput == 'r') cout << "Edited text: " << ReplaceExclamation(input) << endl << endl;
   if(userInput == 's') cout << "Edited text: " << ShortenSpace(input) << endl << endl;

   return userInput;
}

int main() {
   char menuChoice;

   // Step 1
   cout << "Enter a sample text:" << endl;
   getline(cin, input);
   cout << endl << "You entered: " << input << endl << endl;
   
   // Loop for Step 2 that retries 
   do {
      menuChoice = PrintMenu();
      
   } while(menuChoice != 'q');

   return 0;
}