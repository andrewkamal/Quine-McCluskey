#pragma once
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <fstream>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <math.h>
using namespace std;
class McCluskey
{
public:
	McCluskey();                                       //Constructor
	~McCluskey();                                      //Destructor
	void getFromFile(string);                          //Read all file content
	void check_Min_Dont();                             //Checks all the minterms and the dont cares with each other
	void duplicate(vector<string>&);				   //if any duplicates are found in the vector remove them all
	void read_Min_D(string);                           //reads the minterms and dont cares for validation
	void getMin(string, int);                          //get the minterms and add them to vector minterms and check for validations
	void getValues(string);                            //get the decimal values from the binary string
	vector<string> checkGroup(vector<string>);         //Finds all the Prime Implicants and the essentials
	void dectoBin(char[], int, int);				   //change from decimal to binary while getting the num, its size, and the arr to save in
	int bintoDec(int[], int);					        //change from binary to decimal
	bool compare(string, string, vector<string>&);     //compares two strings together and returns their pairs if found
	void getPrmEss();								   //get the prime implicants and the essentials and put them in vector Ess and Prime
	void prntarr();                                    //Print all the values in the array
	void prntPriEss();								   //print all the essentials and prime implicants in 3 differnet ways
private:
	int size, z, counter, counter2, sizePow;           //size and counters
	int arr[65536]={ 0 };                              //empty int array for the prime and essentials
	char *a1, *a2;                                     //two pointers to 2 dynamic arrays
	vector <string> c1, updated, Dec, nums;			   //string vector for c1, updated, Dec, and nums
	vector <int> minterms, Prime, Ess;                 //int vector for minterms, Prime, Ess
	bool visited1[131072];                             //a boolean array with 2^17 to cover the worst possible outcome from a 2^16
};

