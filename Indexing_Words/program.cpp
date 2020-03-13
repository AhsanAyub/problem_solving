/*
 * The file consists of a number of lines, separated by line breaks.
 * Each line contains "words" made up of lower case alphabetical characters separated by white space.
 * You can assume that the file is small enough to fit in working memory.
 *
 * @author Md. Ahsan Ayub
 * @version 1.0 11/27/2019 
 *
 */

// Including all the librarires
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

const int iUniqueWord = 1000; // A bad way, but for the sake of implementation in short time

// This is the vector variable that will store every info
vector<string> verbose[iUniqueWord];
//vector<vector<int>> verbose;


// This is the utility function to print the vector
void printVector()
{
	/*
		The should be nested loop
		The parent loop will first be limited to the size of the word list
		The child loop will be limited to the size of the line count list
	*/
}

// This is the utility function to check the word and return the index in the vector
int isAppearBefore(string str)
{
	// Iterate through the vector to search the value in the vector
	// Return the index if found; otherwise return 0

	return 0;
}

// This is a utility function to create an adjancency list
void addLineCount(string str, int i)
{

	// check whether the word is unique or appeared before in the vector
	int iCounter = isAppearBefore(str);

	cout << str << " " << i << endl;

	if(!iCounter)
		verbose[i].push_back(str); // Insert a new word with the occured line
	
	/*
	else
		verbose will add the line count in the index returned from the function
	*/
	
	/*
		What it should do is:
		"the" -> 0, 1
		..
		..
	*/	

}


// Parse words given a line found in the file
int parseWords(string str, int iLine)
{
	int iWord = 0;
	string sWord = "";

	for (auto x : str)
	{
		if(x == ' ')
		{
			//cout << sWord << endl;

			// Store the word and the line number to the vector as adjacency list
			addLineCount(sWord, (iLine + 1));

			sWord = "";
			iWord = iWord + 1;
		}
		else
		{
			sWord = sWord + x;
		}
	}
	
	return (iWord+1);
}

// Driver program
int main (int argc, char *argv[])
{
	if (argc < 2) // Checks only the name of the file is passed as an argument
    {
        cerr << "Usuage: ./program <file_name>" << endl;
        return -1;
    }

    string fName = argv[1]; // Storing the file in the variable
    ifstream infile;
    infile.open(fName); // Openning the file passed as an argument

    if(!infile) // exit program if the file is not found
	{
        cerr << "File is not found!" << endl;
        return -1;
    }

    string line; // this variable is responsible to access each line
 
    int iLine = 0; // Counter for line
    int iWord = 0; // Counter for word
    while(getline(infile, line)) //scan per line
	{
		//cout << line << endl;
		line = line + " "; // a hack to solve the word problem
		iWord = iWord + parseWords(line, iLine);
		//cout << parseWords(line) << endl;
		
    	iLine = iLine + 1;
    }
    //cout << iWord << iLine << endl;

    infile.close(); // close the file that was accessed below
   	
   	// By now everything should be processed
   	// printVector();

   	//verbose.clear(); // Deallocating memory
    
    return 0;
}

/*
 
 Test Case 1:
 
 i/p
 the quick brown fox jumps over
 the lazy
 lazy lazy
 dog
 
 o/p
 brown 1
 dog 4
 fox 1
 jumps 1
 lazy 2 3
 over 1
 quick 1
 the 1 2

 Test Case 2:
 
 i/p
 the quick brown fox jumps over the lazy lazy lazy dog
 
 o/p
 brown 1
 dog 4
 fox 1
 jumps 1
 lazy 2 3
 over 1
 quick 1
 the 1 2

 Test Case 3:
 
 i/p
 the
 quick
 brown
 fox
 jumps
 over
 the
 lazy
 lazy
 lazy
 dog
 
 o/p
 brown 1
 dog 4
 fox 1
 jumps 1
 lazy 2 3
 over 1
 quick 1
 the 1 2

*/