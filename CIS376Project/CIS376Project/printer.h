#pragma once
#ifndef PRINTER
#define PRINTER
#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

class printer
{
private:
	//fstream outputFile;

public:
	printer();
	void printEverywhere(ofstream& f, string line);
	void printToFileAVL();
	void printToFileBST();
	void printToFileSPLAY();
};

#endif

void printer::printEverywhere(ofstream& f, string line)
{
	cout << line;
	f << line;
}
