//Program Name: Prog 1 
//Programmer Name: Alexis Tucker 
//Description: creates three trees (splay, bst, and avl) and sends a report to each file of a summary of the 
//operations done based on the tests given
//Date Created: 2/23/2020
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "avl.h"
#include "bst.h"
#include "splay.h"

using namespace std;

const int MAX_ROW = 50;
const int MAX_COL = 5;
const int row = 3;
const int col = 3;

/*
Desc: checks the validity of the user's input to loop through the program again
Pre-condition : none, will be checked automatically
Post-condition : returns a char value
*/
char sentinelCheck();

/*
Desc: reads the input file to the output files, prints the array to file and prints to screen
Pre-condition : bst, avl, splay objects, ifstream, four ofstreams, one array, one string
Post-condition : none
*/
void readFile(bst& b, avl& a, splay& s, ofstream& bin, ofstream& av, ofstream& spl, ofstream& summary, ifstream& f, int sum[], string testN);

/*
Desc: fills arrays with summary report info to be printed to screen and window
Pre-condition : 4 ofstreams, 2d string array, 2 integer arrays, an integer, a string
Post-condition : none
*/
void addToSumArray(ofstream& bin, ofstream& av, ofstream& spl, ofstream& report, string summary[MAX_ROW][MAX_COL], int sum[], int total[], int t, string str);

int main()
{
	int testNumber = 0;
	//bst b;
	//avl a;
	//splay s;
	ifstream userInputOne;
	ifstream userInputTwo;
	ofstream userOutputBin;
	ofstream userOutputAVL;
	ofstream userOutputSplay;
	ofstream summary;
	string summaryArr[MAX_ROW][MAX_COL] = { {"Test", "Title", "BST", "AVL", "Splay"} };
	int totalArr[row] = { 0 };
	int tempSum[row] = { 0 };
	bool emptyFile = false;
	char sentinel = 'y';

	while (sentinel == 'y' || sentinel == 'Y')
	{
		cin.ignore();

		string testNameOne = " ";
		string testNameTwo = " ";

		cout << "Enter a name for the test: ";
		getline(cin, testNameOne);

		cout << "Enter a name for the next test: ";
		getline(cin, testNameTwo);

		string fileName = " ";
		string fileTwo = " ";

		cout << "Enter a name for the first input file: ";
		cin >> fileName;

		cout << "Enter a name for the second input file: ";
		cin >> fileTwo;

		userInputOne.open(fileName, ios::in);
		userInputTwo.open(fileTwo, ios::in);
		if (!userInputOne.is_open() || !userInputTwo.is_open())
		{
			cout << "ERROR. File cannot be found." << endl;
		}
		else if (userInputOne.peek() == EOF || userInputTwo.peek() == EOF)
		{
			cout << "ERROR. One of the files is empty." << endl;
			emptyFile = true;
		}
		if ((userInputOne.is_open() && userInputTwo.is_open()) && emptyFile == false)
		{
			bst b;
			avl a;
			splay s;
			string outFileName = " ";
			cout << "Enter a BST output file name: ";
			cin >> outFileName;
			userOutputBin.open(outFileName, ios::out);

			cout << "Enter an AVL output file name: ";
			cin >> outFileName;
			userOutputAVL.open(outFileName, ios::app);

			cout << "Enter a Splay output file name: ";
			cin >> outFileName;
			userOutputSplay.open(outFileName, ios::app);

			string sumName = " ";
			cout << "Enter a summary report file name: ";
			cin >> sumName;

			summary.open(sumName, ios::app);

			userOutputBin << "Test " << testNumber << ": " << testNameOne << endl;
			userOutputAVL << "Test " << testNumber << ": " << testNameOne << endl;
			readFile(b, a, s, userOutputBin, userOutputAVL, userOutputSplay, summary, userInputOne, tempSum, testNameOne);
			testNumber++;
			addToSumArray(userOutputBin, userOutputAVL, userOutputSplay, summary, summaryArr, tempSum, totalArr, testNumber, testNameOne);

			testNumber++;
			userOutputBin << "Test " << testNumber << ": " << testNameTwo << endl;
			userOutputAVL << "Test " << testNumber << ": " << testNameTwo << endl;
			readFile(b, a, s, userOutputBin, userOutputAVL, userOutputSplay, summary, userInputTwo, tempSum, testNameTwo);
			addToSumArray(userOutputBin, userOutputAVL, userOutputSplay, summary, summaryArr, tempSum, totalArr, testNumber, testNameTwo);

		}

		sentinel = sentinelCheck();

		userInputOne.close();
		userInputTwo.close();
		userOutputBin.close();
		userOutputAVL.close();
		userOutputSplay.close();
		summary.close();

		cin.ignore();
	}

	return 0;
}

void addToSumArray(ofstream& bin, ofstream& av, ofstream& spl, ofstream& report, string summary[MAX_ROW][MAX_COL], int sum[], int total[], int t, string str)
{
	int j = t + 1;
	int i = 0;
	for (int x = t; x < j; x++)
	{
		for (int y = 0; y < MAX_COL; y++)
		{
			if (x > 0 && y == 0)
			{
				summary[x][y] = to_string(x);
			}
			if (y == 1 && x > 0)
			{
				summary[x][y] = str;
			}
			if (x > 0 && y > 1)
			{
				summary[x][y] = to_string(sum[i]);
				i++;
			}

		}

	}

	total[0] = total[0] + sum[0];
	total[1] = total[1] + sum[1];
	total[2] = total[2] + sum[2];

	bin << endl;
	av << endl;
	spl << endl;
	report << endl;
	cout << endl;

	bin << setw(10) << "Summary" << endl;
	av << setw(10) << "Summary" << endl;
	spl << setw(10) << "Summary" << endl;
	report << setw(10) << "Summary" << endl;
	cout << setw(10) << "Summary" << endl;

	for (int x = 0; x < MAX_ROW; x++)
	{

		for (int y = 0; y < MAX_COL; y++)
		{
			bin << setw(7) << summary[x][y] << setw(7) << "   ";
			av << setw(7) << summary[x][y] << setw(7) << "   ";
			spl << setw(7) << summary[x][y] << setw(7) << "   ";
			report << setw(7) << summary[x][y] << setw(7) << "   ";
			cout << setw(7) << summary[x][y] << setw(7) << "   ";
		}
		if (x > t)
		{
			break;
		}
		bin << endl;
		av << endl;
		spl << endl;
		report << endl;
		cout << endl;
	}

	bin << endl << setw(29) << "-------------------------------------------------------------------" << endl;
	av << endl << setw(29) << "-------------------------------------------------------------------" << endl;
	spl << endl << setw(29) << "-------------------------------------------------------------------" << endl;
	report << endl << setw(29) << "-------------------------------------------------------------------" << endl;
	cout << endl << setw(29) << "-------------------------------------------------------------------" << endl;
	cout << setw(29) << "Total " << setw(12) << total[0] << setw(14) << total[1] << setw(14) << total[2] << endl;
	bin << setw(29) << "Total " << setw(12) << total[0] << setw(14) << total[1] << setw(14) << total[2] << endl;
	av << setw(29) << "Total " << setw(12) << total[0] << setw(14) << total[1] << setw(14) << total[2] << endl;
	spl << setw(29) << "Total " << setw(12) << total[0] << setw(14) << total[1] << setw(14) << total[2] << endl;
	report << setw(29) << "Total " << setw(12) << total[0] << setw(14) << total[1] << setw(14) << total[2] << endl;
}


void readFile(bst& b, avl& a, splay& s, ofstream& bin, ofstream& av, ofstream& spl, ofstream& summary, ifstream& f, int sum[], string testN)
{
	int countArr[row][col] = { 0 };
	string line;
	int number = 0;
	bool check = false;
	//bst b;
	//avl a;
	//splay s;

	sum[0] = 0;
	sum[1] = 0;
	sum[2] = 0;

	while (!f.eof())
	{
		getline(f, line);

		if (!line.empty() && isdigit(line[0]))
		{
			string strNum = line.substr(0, line.size());
			stringstream sNum(strNum);
			sNum >> number;
			cout << "--------------------------------------" << endl;
			bin << "--------------------------------------" << endl;
			bin << " BST" << endl << "Insert " << number << endl;
			cout << " BST" << endl << "Insert " << number << endl;
			b.insertNode(number);
			b.printTree(bin);
			bin << "Height: " << b.findHeight() << endl;
			cout << "Height: " << b.findHeight() << endl;

			cout << "--------------------------------------" << endl;
			av << "--------------------------------------" << endl;
			cout << " AVL" << endl << "Insert " << number << endl;
			av << " AVL" << endl << "Insert " << number << endl;
			a.insertNode(number, av);
			a.printTree(av);
			cout << "Height: " << a.findHeight() << endl;
			av << "Height: " << a.findHeight() << endl;

			cout << "--------------------------------------" << endl;
			spl << "--------------------------------------" << endl;
			cout << " Splay" << endl << "Insert " << number << endl;
			spl << " Splay" << endl << "Insert " << number << endl;
			s.insertNode(number, spl);
			s.printTree(spl);
			cout << "Height: " << a.findHeight() << endl;
			spl << "Height: " << a.findHeight() << endl;
		}

		else if (line[0] == 'S') //search
		{
			string strNum = line.substr(2, line.size());
			stringstream sNum(strNum);
			sNum >> number;
			cout << "BST" << endl << "Search " << number << endl;
			b.searchNode(number, check);
			cout << "AVL" << endl << "Search " << number << endl;
			a.searchNode(number, check);

			cout << "Splay" << endl << "Search " << number << endl;
			s.searchNode(number, check, spl);
			s.printTree(spl);
			cout << "Height: " << a.findHeight() << endl;
			spl << "Height: " << a.findHeight() << endl;
		}

		else if (line[0] == 'I') //insert
		{
			string strNum = line.substr(2, line.size());
			stringstream sNum(strNum);
			sNum >> number;
			bin << "--------------------------------------" << endl;
			cout << "--------------------------------------" << endl;
			cout << " BST" << endl << "Insert " << number << endl;
			bin << " BST" << endl << "Insert " << number << endl;
			b.insertNode(number);
			b.printTree(bin);
			cout << "Height: " << b.findHeight() << endl;
			bin << "Height: " << b.findHeight() << endl;

			cout << "--------------------------------------" << endl;
			av << "--------------------------------------" << endl;
			cout << " AVL" << endl << "Insert " << number << endl;
			av << " AVL" << endl << "Insert " << number << endl;
			a.insertNode(number, av);
			a.printTree(av);
			cout << "Height: " << a.findHeight() << endl;
			av << "Height: " << a.findHeight() << endl;

			cout << "--------------------------------------" << endl;
			spl << "--------------------------------------" << endl;
			cout << " Splay" << endl << "Insert " << number << endl;
			spl << " Splay" << endl << "Insert " << number << endl;
			s.insertNode(number, spl);
			s.printTree(spl);
			cout << "Height: " << s.findHeight() << endl;
			spl << "Height: " << s.findHeight() << endl;
		}

		else if (line[0] == 'D') //delete
		{
			string strNum = line.substr(2, line.size());
			stringstream sNum(strNum);
			sNum >> number;

			cout << "--------------------------------------" << endl;
			bin << "--------------------------------------" << endl;
			cout << " BST" << endl << "Delete " << number << endl;
			bin << " BST" << endl << "Delete " << number << endl;
			b.deleteItem(number);
			b.printTree(bin);
			cout << "Height: " << b.findHeight() << endl;
			bin << "Height: " << b.findHeight() << endl;

			cout << "--------------------------------------" << endl;
			av << "--------------------------------------" << endl;
			cout << " AVL" << endl << "Delete " << number << endl;
			av << " AVL" << endl << "Delete " << number << endl;
			a.deleteItem(number, av);
			a.printTree(av);
			cout << "Height: " << a.findHeight() << endl;
			av << "Height: " << a.findHeight() << endl;

			cout << "--------------------------------------" << endl;
			spl << "--------------------------------------" << endl;
			cout << " Splay" << endl << "Delete " << number << endl;
			spl << " Splay" << endl << "Delete " << number << endl;
			s.deleteItem(number, spl);
			s.printTree(spl);
			cout << "Height: " << s.findHeight() << endl;
			spl << "Height: " << s.findHeight() << endl;
		}

		else //anything else
		{
			//cout << line[0] << " is not a command" << endl;
		}

	}

	countArr[0][0] = b.getCountSearches();
	countArr[1][0] = b.getCountInserts();
	countArr[2][0] = b.getCountDeletes();
	countArr[0][1] = a.getCountSearches();
	countArr[1][1] = a.getCountInserts();
	countArr[2][1] = a.getCountDeletes();
	countArr[0][2] = s.getCountSearches();
	countArr[1][2] = s.getCountInserts();
	countArr[2][2] = s.getCountDeletes();

	int temp[row] = { 0 };

	bin << setw(10) << testN << endl;
	av << setw(10) << testN << endl;
	spl << setw(10) << testN << endl;
	summary << setw(10) << testN << endl;
	cout << setw(10) << testN << endl;

	cout << setw(10) << "Operation Counts" << endl;
	bin << setw(10) << "Operation Counts" << endl;
	av << setw(10) << "Operation Counts" << endl;
	spl << setw(10) << "Operation Counts" << endl;
	summary << setw(10) << "Operation Counts" << endl;

	cout << setw(13) << "BST" << setw(5) << " AVL" << setw(7) << " Splay" << endl;
	bin << setw(13) << "BST" << setw(5) << " AVL" << setw(7) << " Splay" << endl;
	av << setw(13) << "BST" << setw(5) << " AVL" << setw(7) << " Splay" << endl;
	spl << setw(13) << "BST" << setw(5) << " AVL" << setw(7) << " Splay" << endl;
	summary << setw(13) << "BST" << setw(5) << " AVL" << setw(7) << " Splay" << endl;
	for (int x = 0; x < row; x++)
	{
		if (x == 0)
		{
			bin << "Searches" << setw(5);
			av << "Searches" << setw(5);
			spl << "Searches" << setw(5);
			summary << "Searches" << setw(5);
			cout << "Searches" << setw(5);
		}
		if (x == 1)
		{
			bin << "Inserts" << setw(6);
			av << "Inserts" << setw(6);
			spl << "Inserts" << setw(6);
			summary << "Inserts" << setw(6);
			cout << "Inserts" << setw(6);
		}
		if (x == 2)
		{
			bin << "Deletes" << setw(6);
			av << "Deletes" << setw(6);
			spl << "Deletes" << setw(6);
			summary << "Deletes" << setw(6);
			cout << "Deletes" << setw(6);
		}

		for (int y = 0; y < col; y++)
		{
			sum[y] = sum[y] + countArr[x][y];
			temp[y] = temp[y] + countArr[x][y];

			bin << countArr[x][y] << setw(5);
			av << countArr[x][y] << setw(5);
			spl << countArr[x][y] << setw(5);
			summary << countArr[x][y] << setw(5);
			cout << countArr[x][y] << setw(5);

		}

		bin << endl;
		av << endl;
		spl << endl;
		summary << endl;
		cout << endl;
	}

	bin << "----------------------------" << endl;
	av << "----------------------------" << endl;
	spl << "----------------------------" << endl;
	summary << "----------------------------" << endl;
	cout << "----------------------------" << endl;

	bin << "Total " << setw(7) << temp[0] << setw(5) << temp[1] << setw(5) << temp[2] << endl;
	av << "Total " << setw(7) << temp[0] << setw(5) << temp[1] << setw(5) << temp[2] << endl;
	spl << "Total " << setw(7) << temp[0] << setw(5) << temp[1] << setw(5) << temp[2] << endl;
	summary << "Total " << setw(7) << temp[0] << setw(5) << temp[1] << setw(5) << temp[2] << endl;
	cout << "Total " << setw(7) << temp[0] << setw(5) << temp[1] << setw(5) << temp[2] << endl;

}

char sentinelCheck()
{
	char userInput = ' '; //the user's input, which is checked, to decide whether to loop  
	bool inputCheck = false; //used to loop through 

	cout << "Enter y or n to continue or quit: ";
	cin >> userInput;

	do
	{
		if (userInput == 'y' || userInput == 'Y' || userInput == 'n' || userInput == 'N')
		{

			return userInput;

		}
		else
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Sorry, that wasn't a valid answer. Please enter y or n: ";
			cin >> userInput;
		}
	} while (inputCheck == false);
}