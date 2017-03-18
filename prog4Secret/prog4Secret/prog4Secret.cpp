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
	cout << "Welcome to the decoding program, where hidden messages are found inside of a text file. \n"
		 << "\n"

		 << "Author: Victor Fong & Aswin Manoj \n"
		 << "Assignment : #4, Secret \n"
		 << "TA : Nianzu Ma, Tues 4PM \n"
		 << "Feb 19, 2017 \n"
		 << "\n";

	return;
}


void displayTable(char *cipherText, int characterCount)
{
	for (int i = 0; i < characterCount; i++)
	{
		cout << cipherText[i];
	}
	cout << "\n\n\n";

	return;
}


int analyzeKey(FILE* txtFile, char *keyArray) //takes in file and gets the number of strings, as well as what they are. returns number of characters in file (including added '\0')
{
	int i = 0;
	int j = 1;
	int characterCount = 0;
	int wordCount = 1;
	int keyArrayIndex[MAX_WORDS_IN_KEY] = { NULL };
	keyArrayIndex[0] = 0;
	int length = 0;

	char tempChar = 0;
	//char words[MAX_WORDS_IN_KEY][MAX_WORD_SIZE] = { NULL };		//TODO: FIND A WAY TO SAVE THE SINGLE WORD FROM KEY ARRAY (AT TIME OF POINTER SEEMS TO WORK) INTO THIS ARRAY. WE NEED IT TO CHECK THE TABLE

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
		characterCount++;
	}

	cout << "Read in " << wordCount << " keyWords, which are:\n\n";
	j = 0;
	for (int i = 0; i < wordCount; i++)
	{
		arrayPointer = &keyArray[keyArrayIndex[j]];
		length = strnlen(arrayPointer, MAX_WORD_SIZE);
		cout << arrayPointer << "\n";
		j++;
	}

	return wordCount;
}


int analyzeCipher(FILE* txtFile, char *cipherText) //takes in file and gets the number of strings, as well as what they are. Returns number of characters in taken string
{
	int i = 0;
	int characterCount = 0;

	char tempChar = 0;

	while (fscanf(txtFile, "%c", &tempChar) != EOF)
	{
		cipherText[i] = tempChar;
		characterCount++;
		i++;
	}

	cout << "\n\nRead in " << characterCount << " cipherText characters which are:\n\n\n";
	displayTable(cipherText, characterCount);

	return characterCount;
}


char promptForChoiceAndScanForSelection()
{
	char selection = ' ';
	cout << "Choose from the following options:\n"
		<< "	1. Display a particular sized table\n"
		<< "	2. Find all matching key word keyArrays\n"
		<< "	X. Exit the program\n"
		<< "Enter your choice -> "; cin >> selection;

	return selection;
}

//TODO: make a function that will restore cipherText to it's original state.
void wrapForN(char *cipherText, int characterCount, int n)
{
	char cipherTextBuffer[MAX_CHARACTERS_IN_CIPHER] = { NULL };
	int i = 0, j = 0;
	for (int i = 0; i < characterCount; i++)
	{
		if (i == 0 || (i % n) != 0)
		{
			cipherTextBuffer[j] = cipherText[i];
			j++;
		}
		else if ((i % n) == 0)
		{
			cipherTextBuffer[j] = '\n';
			j++;
			cipherTextBuffer[j] = cipherText[i];
			j++;
		}
	}

	i = 0;
	while (cipherTextBuffer[i] != NULL)
	{
		cipherText[i] = cipherTextBuffer[i];
		i++;
	}

	return;
}


void reactToSelection(char * cipherText, char input, int characterCount, int *errCode)
{
	int wrapInput = 0;

	if (input == 'X' || input == 'x')		//x to exit program
	{
		cout << "\n----------------------.       .     .   Exiting Program. Thank You For Your Time   .     .       .----------------------\n\n";
		exit(1);
	}
	else if (input == '1')		//1 to display a certain row
	{
		cout << "\nEnter the row size: "; cin >> wrapInput; cout << "\n\n";
		wrapForN(cipherText, characterCount, wrapInput);
		displayTable(cipherText, characterCount);
		*errCode = 1;
	}
	else if (input != '2')		//only remaining option is 2. if not 2 input error has occurred.
	{
		cout << "\nERROR: Input invalid, please try again! ";
		*errCode = 1;
	}
	else		//if all other if/else if statements fail input must be 2 and will therefore decode cipher for all rows 13 -> 132
	{
	}
	return;
}


int main()
{
// initialize important variables
	FILE* cipherTXT = NULL;
	FILE* keyTXT = NULL;

	int errCode = -1;
	int i = 0;
	int j = 0;
	int keyCharacterCount = 0;
	int keyWordCount = 0;
	int cipherCharacterCount = 0;
	int cipherWordCount = 0;

	char keyArray[MAX_WORDS_IN_KEY * MAX_WORD_SIZE] = { NULL };
	char cipherText[MAX_CHARACTERS_IN_CIPHER] = { NULL };
	char tempChar = ' ';
	char input = ' ';

	displayInformationAndInstructions();

//set files to corresponding txt file
	keyTXT = fopen("keys.txt", "r");
	//keyTXT = fopen("complxKeys.txt", "r");
	if (keyTXT == NULL)
	{
		cout << "Could not open key.\n";
		return -1;	//-1 indicates error
	}

	cipherTXT = fopen("cipher.txt", "r");
	//cipherTXT = fopen("complxCipher.txt", "r");
	if (cipherTXT == NULL)
	{
		cout << "Could not open cipher.\n";
		return -1;	//-1 indicates error
	}

	keyWordCount = analyzeKey(keyTXT, keyArray);
	cipherCharacterCount = analyzeCipher(cipherTXT, cipherText);

	fclose(cipherTXT);
	fclose(keyTXT);

	do
	{
		errCode = -1;
		input = promptForChoiceAndScanForSelection();
		reactToSelection(cipherText, input, cipherCharacterCount, &errCode);
	} while (errCode == 1);

	return 0;
}