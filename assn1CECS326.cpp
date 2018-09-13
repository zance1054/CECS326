// Alexander Fielding
// CECS 326
// Assn 1

#include "ass1CECS326.hpp"
using namespace std;

struct Data
{
	char** 	charArray;
	int  	intArray[20];
};

int main()
{
	const string MAIN_MENU = 	"Select a number from the list below\n"
                            "1: Access a Pointer\n"
            								"2: List Deallocated Memory(index)\n"
								            "3: Deallocate All Memory\n"
								            "4: Exit\n";

	const string SUB_MENU =   "Select a number from the list below\n"
                            "1: Print First Ten Characters in the Chosen Array\n"
							              "2: Delete All Characters in the Chosen Array\n"
							               "3: Return to the Main Menu\n";
	Data data;
	int mainMenuInput;
	int subMenuInput;


	initialIntArray(data.intArray, 20, 0, 200);

	data.charArray = new char * [20];
	for(int i = 0; i < 20; i++)
	{
		*(data.charArray + i) = singleInitializeCharPointerMem(*(data.charArray + i), data.intArray[i]);
	}

	do
	{
		mainMenuInput = validate(MAIN_MENU, 1, 4);

		switch(mainMenuInput)
		{
		case 1:
			do
			{
				int arrayNumber = validate("Which array would you like to access(1-20)? ", 1, 20) - 1;

				if(*data.charArray == NULL)
				{
					cout << "All data was erased, reinitializing all data...\n";

					data.charArray = new char * [20];
					for(int i = 0; i < 20; i++)
					{
						*(data.charArray + i) = singleInitializeCharPointerMem(*(data.charArray + i), data.intArray[i]);
					}
				}
				else if(*(data.charArray + arrayNumber) == NULL)
				{
					cout << "There is no data in the specified array, re-initializing...\n";
					*(data.charArray + arrayNumber) = singleInitializeCharPointerMem(*(data.charArray + arrayNumber), data.intArray[arrayNumber]);
				}
				subMenuInput = validate(SUB_MENU, 1, 3);
				cout << subMenuInput << endl;

				switch(subMenuInput)
				{
				case 1:
					printFirstTen(*(data.charArray + arrayNumber), 10);
					break;
				case 2:
					cout << "Deleting all characters in array #" << (arrayNumber + 1) << endl;
					delete[] *(data.charArray + arrayNumber);
					*(data.charArray + arrayNumber) = NULL;
					break;
				case 3:
					cout << "returning to main menu\n";
				default:
					break;
				}
			}while(subMenuInput != 3);
			break;
		case 2:
			break;
		case 3:
			cout << "Deleting all characters from memory\n";

			deleteAll(data.charArray);
			break;
		case 4:
			cout << "Exiting Program.";
			break;
		default:
			cout << "outer default\n";
			break;
		}
	} while(mainMenuInput != 4);

	return 0;
}

int	validate(const string PROMPT, int lowerValue, int upperValue)
{
	int input = -1;
	do
	{
		cout << PROMPT;

		if(!(cin >> input))
		{
			cout << "Invalid input!\n";
			cin.clear();
			cin.ignore();
		}
		else
		{
			cout << input << endl;
			if(input > upperValue || input < lowerValue)
			{
				cout << "Invalid input, please input a value between " << lowerValue << " and " << upperValue << endl;
				cin.clear();
				cin.ignore();
			}
			else
			{
				break;
			}
		}
	} while(true);
	return input;
}

void deleteAll(char **charAr)
{
	for(int i = 0; i < 20; i++)
	{
		cout << i << endl;
		delete[] *(charAr + i);
		*(charAr + i) = NULL;
	}
	delete[] charAr;
	*charAr = NULL;
}

bool printFirstTen(char *charAr, int length)
{
	if(charAr == NULL)
	{
		cout << "charAr null\n";
		return false;
	}
	else
	{
		cout << "Printing first ten characters: ";
		for(int i = 0;i < 10;i++)
		{
			cout << *(charAr + i);
		}
		cout << endl;
		return true;
	}
}

char** initializeCharPointerMem(char **charAr, int intAr[20])
{
	char ** charPtr = new char * [20];
	for(int i = 0; i < 20; i++)
	{
		*(charPtr + i) = singleInitializeCharPointerMem(*(charPtr + i), intAr[i]);
	}
	return charPtr;
}

char* singleInitializeCharPointerMem(char *charPtr, int arLength)
{
	charPtr = new char [arLength];

	for(int i = 0;i < arLength;i++)
	{
		*(charPtr + i) = char(65 + rand()%26);
	}

	cout << arLength << endl;
	return charPtr;
}

int initialIntArray(int intAr[20], int finalLocation, int currentLocation, int value)
{
	if(currentLocation == finalLocation) //exit case
	{
		return value * 2;
	}
	else
	{
		intAr[currentLocation] = value;
		value*=2;
		currentLocation++;
		return initialIntArray(intAr, finalLocation, currentLocation, value);
	}
}
