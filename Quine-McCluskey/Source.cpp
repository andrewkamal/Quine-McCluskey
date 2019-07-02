#include <stdio.h>
#include <string>
#include <iostream>
#include <algorithm>
#include <math.h>
#include "McCluskey.h"
using namespace std;

int main()
{
	string s = "file.txt";  //the file that will be passed to the functions
	McCluskey mc;
	mc.getFromFile(s);      //get all the content from the specified file
	mc.read_Min_D(s);       //reads all the minterms from the file
	mc.check_Min_Dont();    //Checks all the minterms and the dont cares with each other
	mc.prntarr();           //Print all the values in the array
	mc.getPrmEss();         //get the prime implicants and the essentials and put them in vector Ess and Prime
	mc.prntPriEss();        //print all the essentials and prime implicants in 3 differnet ways
	system("pause");
	return 0;

}