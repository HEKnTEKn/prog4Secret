//	Author: Victor Fong & Aswin Manoj
//	Assignment : #4, Secret
//	TA : Nianzu Ma, Tues 4PM
//	Mar 7, 2017


//include libraries, define global variables,set namespace to reduce cout/in redundancy
#include <cstdio>
#include <cstring>
#include <string>
#include <cstdlib>
#include <iostream>
using namespace std;

#define MAX_WORDS_IN_KEY 20
#define MAX_WORD_SIZE 25
#define MAX_CHARACTERS_IN_CIPHER 17424

void displayInformationAndInstructions(void)   //function will display programmer information of the program.
{
	cout << "Welcome to the decoding program, where hidden messages are found inside of a text file. \n";
	cout << "\n";

	cout << "Author: Victor Fong & Aswin Manoj \n";
	cout << "Assignment : #4, Secret \n";
	cout << "TA : Nianzu Ma, Tues 4PM \n";
	cout << "Feb 19, 2017 \n";
	cout << "\n";

	return;
}



int analyzeKey(FILE* txtFile, char *keyArray) //takes in file and gets the number of strings, as well as what they are. returns number of characters in file (including added '\0')
{
	int i = 0;
	int j = 1;
	int wordCount = 1;
	int keyCharacterCount = 0;
	int keyArrayIndex[MAX_WORDS_IN_KEY] = { NULL };
	keyArrayIndex[0] = 0;
	int length = 0;
	
	char tempChar = 0;
	char words[MAX_WORDS_IN_KEY][MAX_WORD_SIZE] = { NULL };
	char* arrayPointer;
	
	while (fscanf(txtFile, "%c", &tempChar) != EOF)
	{
		keyArray[i] = tempChar;

		if (keyArray[i] == ' ')
		{
			keyArray[i] = '\0';
			wordCount++;
			keyArrayIndex[j] = (i + 1);		//stores the position of the next word in keyArray into this index
			j++;
		}
		i++;
		keyCharacterCount++;
	}
	
	cout << "Read in " << wordCount << " keyWords, which are:\n\n";
	j = 0;
	for (int i = 0; i < wordCount; i++)
	{
		arrayPointer = &keyArray[keyArrayIndex[j]];
		length = strnlen(arrayPointer, MAX_WORD_SIZE);
		cout << arrayPointer  << "\n";
		j++;
	}
	

	return keyCharacterCount;
}


int analyzeCipher(FILE* txtFile, char *cipherArray) //takes in file and gets the number of strings, as well as what they are. Returns number of characters in taken string
{
	int i = 0;
	int characterCount = 0;

	char tempChar = 0;

	while (fscanf(txtFile, "%c", &tempChar) != EOF)
	{
		cipherArray[i] = tempChar;
		characterCount++;
		i++;
	}

	cout << "\n\nRead in " << characterCount << " cipherText characters \n\n";

	return characterCount;
}


char promptForChoiceAndScanForSelection() {
	char selection = ' ';

	cout << "Choose from the following options:\n"
		 << "	1. Display a particular sized table\n"
		 << "	2. Find all matching key word keyArrays\n"
		 << "	X. Exit the program\n"
		 <<	"Enter your choice -> "; cin >> selection;

	return selection;
}


//checks input for an x or X that will later quit program
void checkForX(char input) {	//function that takes character variable and checks for for 'x' or 'X'. if true then the function will exit the prgram.

	if (input == 'X' || input == 'x')
	{
		cout << "----------------------.       .     .   Exiting Program. Thank You For Your Time   .     .       .----------------------\n\n";
		exit(1);
	}
	return;
}


void printWords(char* cipherArray, int cipherCharacterCount) {

// printf("%d", len);
    for (int i = 0; i < cipherCharacterCount; i++)
	{
        if (cipherArray[i] == ' ')
		{
            cout << "\n";
        }
		else
		{
            cout << cipherArray[i];
        }
    }
}


int main()
{
// initialize important variables
	FILE* cipherTXT = NULL;
	FILE* keyTXT = NULL;

	int i = 0;
	int j = 0;
	int keyCharacterCount = 0;
	int cipherCharacterCount = 0;
	int numColumns = 0;

	char keyArray[MAX_WORDS_IN_KEY * MAX_WORD_SIZE] = { NULL };
	char cipherArray[MAX_CHARACTERS_IN_CIPHER] = { NULL };
	char tempChar = ' ';
	char input = ' ';

	displayInformationAndInstructions();
	
//set files to corresponding txt file
	keyTXT = fopen("key.txt", "r");
	if (keyTXT == NULL)
	{
		cout << "Could not open key.\n";
		return -1;	//-1 indicates error
	}

	/*while (fscanf(keyTXT, "%c", &tempChar) != EOF)	//get number of characters in key
	{ numCharInKey++; }*/

	cipherTXT = fopen("cipher.txt", "r");
	if (cipherTXT == NULL)
	{
		cout << "Could not open cipher.\n";
		return -1;	//-1 indicates error
	}

	numColumns = 13;

	keyCharacterCount = analyzeKey(keyTXT, keyArray);
	cipherCharacterCount = analyzeCipher(cipherTXT, cipherArray);

	input = promptForChoiceAndScanForSelection();

	checkForX(input);

	return 0;
}