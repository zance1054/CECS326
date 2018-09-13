// Alexander Fielding
// CECS 326
// Assn 1

#include <iostream>
#include <cstdlib>
#include <array>
#include <exception>

using namespace std;

//functions
int 	initialIntArray(int intAr[20], int finalLocation, int currentLocation, int value);
char* 	singleInitializeCharPointerMem(char *charAr, int arLength);
char**	initializeCharPointerMem(char *charAr[20], int intAr[20]);
bool	printFirstTen(char *charAr, int length);
void	deleteAll(char **charAr);
int		validate(const string PROMPT, int lowerValue, int upperValue);
