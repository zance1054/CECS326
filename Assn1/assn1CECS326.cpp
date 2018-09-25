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
	const string mainMenu = 	"Select a number from the list below\n"
                            "1: Access a Pointer\n"
            								"2: List Deallocated Memory(index)\n"
								            "3: Deallocate All Memory\n"
								            "4: Exit\n";

	const string accessMenu =   "Select a number from the list below\n"
                            "1: Print First Ten Characters in the Chosen Array\n"
							              "2: Delete All Characters in the Chosen Array\n"
							               "3: Return to the Main Menu\n";
	Data data;
	int mainInput;
	int subInput;


	initialIntArray(data.intArray, 20, 0, 2700);

	data.charArray = new char * [20];
	for(int i = 0; i < 20; i++)
	{
		*(data.charArray + i) = singleInitializeCharPointerMem(*(data.charArray + i), data.intArray[i]);
	}

	do
	{
		mainInput = validate(mainMenu, 1, 4);

		switch(mainInput)
		{
		case 1:
			do
			{
				int arrayNumber = validate("Choose an array to access (1-20)? ", 1, 20) - 1;

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
					cout << "There is no data in the specified array\n";
					*(data.charArray + arrayNumber) = singleInitializeCharPointerMem(*(data.charArray + arrayNumber), data.intArray[arrayNumber]);
				}
				subInput = validate(accessMenu, 1, 3);
				cout << subInput << endl;

				switch(subInput)
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
			}while(subInput != 3);
			break;
		case 2:
			cout<< "Arrays where charachters were deleted: "<< endl;

			for(int i = 0; i < 20; i++)
			{
				if(*(data.charArray + i) == NULL)
				{
					cout<< "Array:";
					cout<< i << endl;
				}
			}

			break;
		case 3:
			cout << "Deleting all characters\n";

			deleteAll(data.charArray);
			break;
		case 4:
			cout << "Exiting Program.\n";
			break;
		default:
			cout << "outer default\n";
			break;
		}
	} while(mainInput != 4);

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
		cout << "First ten characters: \n";
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

int initialIntArray(int arr[20], int Last, int curr, int value)
{
	if(curr == Last)
	{
		return value * 2;
	}
	else
	{
		arr[curr] = value;
		value*=2;
		curr++;
		return initialIntArray(arr, Last, curr, value);
	}
}
