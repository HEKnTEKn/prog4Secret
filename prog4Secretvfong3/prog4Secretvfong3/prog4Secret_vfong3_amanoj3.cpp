//	Author: Victor Fong & Aswin Manoj
//	Assignment : #4, Secret
//	TA : Nianzu Ma, Tues 4PM
//	Mar 7, 2017


//include libraries, define global variables,set namespace to reduce cout/in redundancy
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <iostream>
using namespace std;
#define MAX_WORD_SIZE 30

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



//TODO: find out how to make character arrays correct number of elements for text file
void analyzeKey(FILE* txtFile, char *keyArray) //takes in file and gets the number of strings, as well as what they are
{
	int i = 0;
	int j = 0;
	int wordCount = 1;
	int keyIndex[2];

	char tempChar = 0;


	while (fscanf(txtFile, "%c", &tempChar) != EOF)
	{
		keyArray[i] = tempChar;

		if (keyArray[i] == ' ')
		{
			keyIndex[j] = i;
			j++;
			wordCount++;
		}
		i++;
	}

	cout << "Read in " << wordCount << " keyWords, which are: ";
	i = 0;

	while (keyArray[i] != ' ')
	{
		cout << keyArray[i];
		i++;
	}
	cout << ' ';

	
/*	for (int i = 0; i < (wordCount - 1);i++)
	{
		while (keyArray[keyIndex[j]] != ' ')
		{
			cout << keyArray[keyIndex[j] + 1];

			j++;
		}
	}
	*/
	return;
}


void analyzeCipher(FILE* txtFile, char *cipherArray) //takes in file and gets the number of strings, as well as what they are
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
	
	return;
}

int main()
{
// initialize important variables
	FILE* cipherTXT = NULL;
	FILE* keyTXT = NULL;
	
	int i = 0;
	int j = 0;
	int numCharInKey = 0;
	int numCharInCipher = 0;
	int numColumns = 0;

	char keyArray[150];
	char cipherArray[500];
	char tempChar = ' ';

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
	
	/*while (fscanf(cipherTXT, "%c", &tempChar) != EOF)		//get number of characters in cipher
	{ numCharInCipher++; }*/

	numColumns = 13;

	analyzeKey(keyTXT, keyArray);
	analyzeCipher(cipherTXT, cipherArray);
	
	
	
	
	
	return 0;
}