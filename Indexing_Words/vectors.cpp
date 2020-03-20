/*
 * Compilation:
 * Step 1: g++ -o main vectors.cpp
 * Step 2: ./main text.txt
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

// This is the vector variable that will store every info
vector<string> vCounts;
vector<string> vWords;
int iUniqueWord = 0; // Counter for unique words

// This is the utility function to print the vector
void printVector()
{
	// Printing the vector
	for (int i = 0; i < iUniqueWord; i++)
		cout << vWords.at(i) << endl;
}

// This is the utility function to check the word and return the index in the vector
int isAppearedBefore(string sItem)
{
	// Iterate through the vector to search the value in the vector
	// Return the index if found; otherwise return -1

	int iVectorSize = vWords.size();
	int index = 0;
	while(index < iVectorSize)
	{
		if(sItem.compare(vWords.at(index)) == 0)
			break; // Appeared before!

		index++;
	}

	if(index == iVectorSize || iVectorSize == 0)
		return -1; // Not appeared
	else
		return index; // Appeared on index
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
			// Store the word and the line number to the vector as adjacency list
			int iFlag = isAppearedBefore(sWord);
			if(iFlag == -1)
			{
				// First time appeared; hence, pushing into the vector
				vWords.push_back(sWord);
				vCounts.push_back(to_string(iLine+1));
				iUniqueWord += 1;
			}
			else
			{
				int iTemp = -1;
				int iCountLen = vCounts.at(iFlag).length();
				
				// Getting the final occurred line of the word	
				if(iCountLen >= 1)
					iTemp = vCounts.at(iFlag)[iCountLen-1] - '0';

				// Making sure multiple entries of line numbers do not get stored
				if(iTemp != iLine+1)
				{
					vCounts.at(iFlag) += " ";
					vCounts.at(iFlag) += to_string(iLine+1);
				}
			}
			sWord = "";
			iWord = iWord + 1;
		}
		else
			sWord = sWord + x;
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

    string fName = argv[1];	// Storing the file in the variable
    ifstream infile;
    infile.open(fName); // Openning the file passed as an argument

    if(!infile) // exit program if the file is not found
	{
        cerr << "File is not found!" << endl;
        return -1;
    }

    string line; // this variable is responsible to access each line
 
    int iLine = 0; // Counter for lines
    int iWord = 0; // Counter for words

    while(getline(infile, line)) //scan per line
	{
		line = line + " "; // a hack to solve the word problem
		iWord = iWord + parseWords(line, iLine);
		
    	iLine = iLine + 1;
    }
    infile.close();	// close the file that was accessed below

    // Merging two vectors into one which will help the sorting operation
    for (int i = 0; i < iUniqueWord; i++)
	{
		vWords.at(i) += " ";
		vWords.at(i) += vCounts.at(i);
	}
	
	// Sorting the vector
	sort(vWords.begin(), vWords.end());

    // By now everything should be processed
   	printVector();
   	
   	// Deallocating memory
   	vWords.clear();
   	vCounts.clear();
   	
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
 dog 1
 fox 1
 jumps 1
 lazy 1
 over 1
 quick 1
 the 1

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
 brown 3
 dog 11
 fox 4
 jumps 5
 lazy 8 9 10
 over 6
 quick 2
 the 1 7

*/