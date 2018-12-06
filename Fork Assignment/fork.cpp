/*
    Alexander Fielding
    CECS 326 Ratana Ngo
    T/TH 9:30
    Fork Assignment
    User selects a word to search for in the text document and an additional word to replace the initally
    chosen word. Program outputs the number of times the word was replaced.
*/


#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

int searchText(ifstream & file, string input);

int main() {

	string target = "";
  string replacement = "";
  string prompt = " Enter a string to search and replace, or enter !wq to quit."
	ifstream filename ("sample.txt");
	int result = 1;
	long childPID;

	cout << prompt << endl;

	while (result > 0) {
		cout << "\n[" << getpid() << "]: Please enter string to search:" << endl;
		cin >> target;

		if (target != "!wq") {
			childPID = fork();//spawn child

			if (childPID == 0) {
				//child executes
				result = search(filename, target);
				cout << "\n[" << getpid()
				<< "]: " << target << "\' occurs " << result << " times." << endl;

				// injected bug must be stopped in another terminal
				while (result == 0) {
					cout << ".";
				}

				break;

			} else {

				wait(0);

			}
		} else {
			result = 0;
			break;
		}
	}

	cout << "[" << getpid() << "]: Ending." << endl;
	//Close file when done
	filename.close();

	return 0;
}

int search(ifstream & file, string input) {
	size_t pos;
	string currentLine;
	int numOccurrences = 0;

	if (file.is_open()) {
		file.clear();
		file.seekg(0, file.beg);

		while (getline(file, currentLine)) {
			pos = currentLine.find(input, 0);

			while (pos != currentLine.size() && pos != string::npos) {
				numOccurrences++;
				pos = currentLine.find(input, pos + 1);
			}
		}
	}

	return numOccurrences;
}
