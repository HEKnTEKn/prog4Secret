//	Author: Victor Fong & Aswin Manoj
//	Assignment : #4, Secret
//	TA : Nianzu Ma, Tues 4PM
//	Mar 7, 2017


//include libraries, define global variables,set namespace to reduce cout/in redundancy
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;


#define MAX_WORDS_IN_KEY 20
#define MAX_WORD_SIZE 25
#define MAX_CHARACTERS_IN_CIPHER 17424


int getLength(char *thingToCheck)	//ACCEPTS CHARACTER ARRAY !ONLY!
{
	int count = 0;
	for (int i = 0; thingToCheck[i] != '\0'; i++)
	{
		count++;
	}
	return count;
}


void displayInformationAndInstructions(void)   //function will display programmer information of the program.
{
	cout << "Welcome to the decoding program, where hidden messages are found inside of a text file. \n"
		 << "\n"

		 << "Author: Victor Fong & Aswin Manoj \n"
		 << "Assignment : #4, Secret \n"
		 << "TA : Nianzu Ma, Tues 4PM \n"
		 << "March 18, 2017 \n"
		 << "\n";

	return;
}


void displayTable(char *cipherText, int characterCount) // Shows a "table" containing the cipherText
{
	for (int i = 0; i < characterCount; i++)
	{
		cout << cipherText[i];
	}
	cout << "\n\n\n";

	return;
}


int analyzeKey(FILE* txtFile, char *keyArray, int *keyArrayIndex) //takes in file and gets the number of strings, as well as what they are. returns number of characters in file (including added '\0')
{
	int i = 0;
	int j = 1;
	int wordCount = 1;
	keyArrayIndex[0] = 0;

	char tempChar = 0;
	
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
	}

	cout << "Read in " << wordCount << " keyWords, which are:\n\n";
	for (int i = 0; i < wordCount; i++)
	{
		arrayPointer = &keyArray[keyArrayIndex[i]];
		cout << arrayPointer << "\n";
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


char promptForChoiceAndScanForSelection()  // Asks user to type in an option and the selection gets scanned
{
	char selection = ' ';
	cout<< "Choose from the following options:\n"
		<< "	1. Display a particular sized table\n"
		<< "	2. Find all matching key word keyArrays\n"
		<< "	X. Exit the program\n"
		<< "Enter your choice -> "; cin >> selection;

	return selection;
}


void transferArray(char *arrayFrom, char *arrayTo) // Helps you shift/transfer the placement of the characters in the cipherText in accordance with the row size given in the input
{
	
	for (int i = 0; i < strlen(arrayFrom); i++)
	{
		arrayTo[i] = arrayFrom[i];
	}

	return;
}


void wrapForN(char *cipherText, int characterCount, int n) // helps you wrap the text in accordance with the row size as mentioned in one of the options
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


void  findMatchHorz(char *wrappedText, char* keyArray, int *keyArrayIndex, int wordCount, int characterCount) // this function checks for matching key arrays using wrappedText
{
	int lettersFound = 0;
	int wordFound = 0;
	int index = 0;
	int offset = 0;
	int wordLength = 0;

	while (wordFound == 0 && index < wordCount)	//for each WORD WHILE a word has not been found HORIZONTALLY
		{
			wordLength = getLength(keyArray + keyArrayIndex[index]);
			for (int positionOfWrappedArray = 0; positionOfWrappedArray < characterCount; positionOfWrappedArray++)	//for each CHARACTER in CIPHERTEXT
			{
				if (wrappedText[positionOfWrappedArray] == keyArray[keyArrayIndex[index] + offset])	//if POSITION at WRAPPEDTEXT == [INDEX]th letter of KEYARRAY + THE NUMBER OF CHARS IN ORDER FOUND
				{
					cout << wrappedText[positionOfWrappedArray];
					offset++;
				}
				else
				{
					
				}
			}
			index++;
		}

	return;
}


void reactToSelection(char *cipherText, char *storedCipherText, char *keyArray, int *keyArrayIndex, int wordCount, char input, int characterCount, int *errCode) // responds to selection from promptForChoice function and gives output based on what user types in
{
	int wrapInput = 0;
	int wrapInputCheck = -1;

	if (input == 'X' || input == 'x')		// x to exit program
	{
		cout << "\n----------------------.       .     .   Exiting Program. Thank You For Your Time   .     .       .----------------------\n\n";
		exit(1);
	}
	else if (input == '1')		//1 to display a certain row
	{
		do
		{
			cout << "\nEnter the row size: "; cin >> wrapInput; cout << "\n\n";

			if (wrapInput >= 13 && wrapInput <= 132)
			{
			transferArray(cipherText, storedCipherText);
			wrapForN(cipherText, characterCount, wrapInput);
			displayTable(cipherText, characterCount);
			transferArray(storedCipherText, cipherText);
			*errCode = 1;
			wrapInputCheck++;
			}
			else
			{
				cout << "\n!!! ERROR: INPUT MUST BE 13-132, PLEASE TRY AGAIN !!!\n\n\n";
			}
		} while (wrapInputCheck != 0);
		
		
	}
	else if (input == '2')		//if all other if/else if statements fail input must be 2 and will therefore decode cipher for all rows 13 -> 132
	{
		//for (int i = 13; i < 132; i++)
		//{
			transferArray(cipherText, storedCipherText);
			wrapForN(cipherText, characterCount, 13);
			findMatchHorz(cipherText, keyArray, keyArrayIndex, wordCount, characterCount);
			transferArray(storedCipherText, cipherText);
		//}
	}
	else		//only remaining option is 2. if not 2 input error has occurred.
	{
		cout << "\nERROR: Input invalid, please try again! ";
		*errCode = 1;
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
	int keyArrayIndex[MAX_WORDS_IN_KEY] = { NULL };
	
	char cipherText[MAX_CHARACTERS_IN_CIPHER] = { NULL };
	char storedCipherText[MAX_CHARACTERS_IN_CIPHER] = { NULL };
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

	keyWordCount = analyzeKey(keyTXT, keyArray, keyArrayIndex);
	cipherCharacterCount = analyzeCipher(cipherTXT, cipherText);

	fclose(cipherTXT);
	fclose(keyTXT);

	do
	{
		errCode = -1;
		input = promptForChoiceAndScanForSelection();
		reactToSelection(cipherText, storedCipherText, keyArray, keyArrayIndex, keyWordCount, input, cipherCharacterCount, &errCode);
	} while (errCode == 1);

	return 0;
}