/*
    Alexander Fielding
    CECS 326 Ratana Ngo
    T/TH 9:30
    Fork Assignment
    User selects a word to search for in the text document and an additional word to replace the initally
    chosen word. Program outputs the number of times the word was replaced.
*/

#include <unistd.h>
#include <iostream>
#include <cstdlib>
#include <sys/types.h>
#include <sys/wait.h>
#include <string>
using namespace std;

int main() {

	int count;
	long childPID;
	bool continue = true;
	string target;
	string replacement;
	string text = """A SCANDAL IN BOHEMIA Arthur Conan Doyle of contents Chapter 1 Chapter 2 Chapter 3 CHAPTER I To Sherlock Holmes she is always the woman. I have seldom heard him
       mention her under any other name. In his eyes she eclipses and
       predominates the whole of her sex. It was not that he felt any
       emotion akin to love for Irene Adler. All emotions, and that one
       particularly, were abhorrent to his cold, precise but admirably
       balanced mind. He was, I take it, the most perfect reasoning and
       observing machine that the world has seen, but as a lover he would
       have placed himself in a false position. He never spoke of the softer
       passions, save with a gibe and a sneer. They were admirable things
       for the observer--excellent for drawing the veil from men's motives
       and actions. But for the trained reasoner to admit such intrusions
       into his own delicate and finely adjusted temperament was to
       introduce a distracting factor which might throw a doubt upon all his
       mental results. Grit in a sensitive instrument, or a crack in one of
       his own high-power lenses, would not be more disturbing than a strong
       emotion in a nature such as his. And yet there was but one woman to
       him, and that woman was the late Irene Adler, of dubious and
       questionable memory."""

	while (continue)
	{
		sleep(1);
		cout << "Enter a target string that will be replaced within the text document or :wq to exit the program" << endl;
		cin >> target;
		if(target == "!wq")
		{
			exit(0);
		}

cout << "Enter a replacement string that will replaced the target string in the text document or :wq to exit the program" << endl;
		cin >> replacement;
		if(replacement != "!wq")
		{
			childPID = fork();
			if (childPID == 0)
			{
				int pos = 0;
				int count = 0;
				bool initial = true;

				while ((pos = text.find(target, pos)) != std::string::npos || initial == true)
				{
					initial = false;
					//injected bug
					if (pos == -1)
					{
						cout << "." << endl;
						sleep(.1);
						initial = true;
					}
					else
					{
						text.replace(pos, target.length(), replacement);
						pos += replacement.length();
						count++;
					}
				}
				cout << "Number of strings replaced: " << (count) << endl;
				cout << "Result: /n" << text << endl;
				exit(0);
			}
			else if (childPID < 0)
			{
				cout << "Error creating child process, returning to initial prompt" << endl;
			}

		}
		else if(replacement == "!wq")
		{
			exit(0);
		}
	}
}
