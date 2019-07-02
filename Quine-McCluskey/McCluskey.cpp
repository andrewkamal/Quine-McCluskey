#include "McCluskey.h"
McCluskey::McCluskey()                                   //constructor
{
	a1 = (char*)calloc(size, sizeof(char));              //intialize a1 to a dynamic array of characters
	counter = 0;
	counter2 = 0;
}

McCluskey::~McCluskey()                                  //destructor                 
{
}

void McCluskey::getFromFile(string s)                    //retrieve data from file
{
	ifstream infile(s);
	if (!infile.is_open())                               // if file does not open
		cout << "error" << endl;
	infile >> size;                                      //number of variables up to 16
	cout << "The number of bits are:" << size << endl;                   
	sizePow = pow(2, size);                              //get the 2 to the power of the size
	while (!infile.eof())         
	{
		getline(infile, s, ',');                         //get the string till the comma
		if (s != "")                                     //an added condition to get all the minterms with and without the comma
		{
			counter++;
			z = stoi(s);                                 //change from string to int
			if (z < sizePow && z >= 0)                   //if the minterms and dontcares are within the range works
			{
				dectoBin(a1, z, size);                   //change from decimal to binary and save it to the dynamic char array a1
				c1.push_back(a1);                        //push a1 into vector c1
				cout << a1 << " ";                     
			}
			else                                         //else exit the code
			{
				cout << "Invalid Input" << endl;
				exit(0);
			}
		}
	}
	cout << endl;
	infile.close();                                      //close the file
}

void McCluskey::check_Min_Dont()                        //for all the minterms and dont cares reach the final simplified binary values
{
	for (int i = 0; i < size; i++)                      //pass each one till the last
		c1 = checkGroup(c1);                            //check them one by one with the rest of the values and return the updated vector
	for (int j = 0; j < c1.size(); j++)                 //print all the simplified values 
		cout << c1[j] << endl;
	for (int j = 0; j < c1.size(); j++)                 //go throught the final updated vector
		getValues(c1[j]);                               //
	cout << "The final number of binary terms are: " << c1.size() << endl;
}

void McCluskey::read_Min_D(string s)                   //reads the minterms and dont cares for validation
{
	ifstream infile(s);                                //open the file again
	int counter3 = 0;
	getline(infile, s);                                //ignore the first line 
	getline(infile, s);                                //get the line of the minterms
	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] == ',')							   //check the number of commas      
			counter2++;                                //counter them all
	}
	getMin(s, counter2 + 1);                           //pass the string and the counter + 1 in case their is a fogetted comma at the end
	for(int i = 0; i < minterms.size(); i++)
		for (int j = i + 1; j < minterms.size(); j++)
			if (minterms[i] == minterms[j])             //check for duplicates in the minterms
			{
				cout << "duplicates found" << endl;
				exit(0);
			}
	if (!infile.eof())
	{
		getline(infile, s);                                //get the line of the dont cares
		for (int i = 0; i < s.length(); i++)
		{
			if (s[i] == ',')
				counter3++;                                //counter the dont cares
		}
		if (counter3 + 1 > counter2)                       //if the dont cares are greater than the minterms
		{
			cout << "The number of don't cares are greater";
			exit(0);
		}
	}
	cout << endl;
	infile.close();                                     //close the file
}

void McCluskey::getMin(string s, int counter2)           //get the minterms and add them to vector minterms and check for validations
{
	int i = 0;
	string temp;
	if (s[s.length() - 1] == ',')                        //if the last value equal to a comma then user didn't forget to add it so decrease the count
	{
		counter2--;
		s[s.length() - 1] = NULL;                        //make the last value null instead of a comma
	}
	for (int x = 0; x < counter2; x++)
	{
		while (s[i] != ',' && s[i] != '\0')			   
		{
			temp += s[i];								 //add to string temp till a the commal
			i++;
		}
		i++;
		z = stoi(temp);                                  //change the string to integer
		minterms.push_back(z);                           //add all the minterms to the vector minterms
		temp.clear();                                    //clear the string temp to take a new one
	}
}

vector<string> McCluskey::checkGroup(vector<string>c1)

{
	updated.clear();                                        //empty the updated vector
	for (int i = 0; i < c1.size(); i++)					    //make all the boolean array false
		visited1[i] = false;
	for (int i = 0; i < c1.size(); i++) {
		for (int j = i + 1; j < c1.size(); j++) {
			if (compare(c1[i], c1[j], updated)) {			//pass the vector updated with the two strings that will be compared
				visited1[i] = true;							//since they had differences make the array positon of the compared strings true
				visited1[j] = true;

			}
			duplicate(updated);                             //check for any duplicates and remove them all
		}
	}

	for (int i = 0; i < c1.size(); i++)                     
		if (visited1[i] != true)                            //if any term was not paired at all 
			updated.push_back(c1[i]);                       //add it as it is to the updated vector
	return updated;                                         //return vector updated 
}

bool McCluskey::compare(string c3, string c2, vector<string>&s)   //compares two strings together and returns their pairs if found

{
	int c = 0, pos = 0;
	for (int i = 0; i < size; i++)                                //checks for the difference of the two strings 
	{
		if (c3[i] != c2[i])                                       //if difference is found                 
		{
			c++;                                                 
			pos = i; 
		}
	}
	if (c == 1)                                                   //work only if the difference is 1
	{
		c3[pos] = '_';                                            //make this position a dash in any string
		s.push_back(c3);                                          //push the updated value to the vector s
		return true;
	}
	return false;                                                 //if none or greater differnec is found return false
}

void McCluskey::getPrmEss()                                       //Finds all the Prime Implicants and the essentials
{
	string t, tm;
	int nm;
	bool flag;
	for (int i = 0; i < nums.size(); i++)
	{	
		t = nums[i];                                              //gets the first numbers from vector nums ex: 0,1,8,9,
		for (int j = 0; j < t.length(); j++)
		{
			tm.clear();                                           //clears string tm
			while (t[j] != ',')
			{
				tm += t[j];                                       //adds the number to tm till the comma
				j++;
			}
			nm = stoi(tm);                                        //changes from string to int and gives it to nm
			if (arr[nm] == 1)                                     //if this number is equal to 1 then it is an Essentail
			{
				flag = true;                                      //if condition is true then flag is true
				break;
			}
			else
				flag = false;                                     //else flag is false
 			
		}
		if (flag == true)
			Ess.push_back(i);                                     //if it is an essential then add the i into vector Ess
		else
			Prime.push_back(i);                                   //if it is a prime implicant then add the i into vector Pri
	}
}


void McCluskey::prntarr()						    //Print all the values in the array
{
	cout << "The numbers of the array are: ";     
	for (int i = 0; i < sizePow; i++)               //iterate from 0 to sizePow and print the integer value
		cout << arr[i] << " ";
	cout << endl;
}

void McCluskey::prntPriEss()                        //print all the essentials and prime implicants in 3 differnet ways
{
	cout << "\nThe Essentials are: " << endl;       //The essentials
	int l;
	for (int i = 0; i < Ess.size(); i++)
	{
		l = Ess[i];                                 //l is the first essential number in the vector
		cout << c1[l] << "   " << nums[l] << "   "; //print it in dashes and in minterms ex: _00_ and 0,1,8,9,
		for (int j = 0; j < size; j++)
		{
			if (c1[l][j] == '0')                    //if the char is 0 print its value in alphabet with a '`'
				cout << char(j + 65) << '`';
			else if (c1[l][j] == '1')               //if the char is 1 print its vlaue in alphabet       
				cout << char(j + 65);
			else
				continue;                           //do nothing
		}
		cout << endl;
	}
	cout << "\nThe Prime Implicants are: " << endl; //The Prime Implicants
	for (int i = 0; i < Prime.size(); i++)
	{
		l = Prime[i];
		cout << c1[l] << "   " << nums[l] << "   "; //print it in dashes and in minterms ex: _00_ and 0,1,8,9,
		for (int j = 0; j < size; j++)
		{
			if (c1[l][j] == '0')				    //if the char is 0 print its value in alphabet with a '`'
				cout << char(j + 65) << '`';   
			else if (c1[l][j] == '1')			    //if the char is 1 print its vlaue in alphabet   
				cout << char(j + 65);
			else
				continue;                           //do nothing
		}
		cout << endl;
	}
	cout << endl;
}

void McCluskey::duplicate(vector<string>& updated)            //if any duplicates are found in the vector remove them all
{
	for (int i = 0; i < updated.size(); i++)
	{
		for (int j = i + 1; j < updated.size(); j++)
			if (updated[i].compare(updated[j]) == 0)          //if two binary strings are the same
				updated.erase(updated.begin() + j);           //erase the extra duplicate from the updated vector
			else
				continue;                                     //if none is found do nothing
	}
}

void McCluskey::dectoBin(char s[], int num, int size)         //change from decimal to binary while getting the number, its size, and the array that will be saved in
{
	memset(s, '0', size);								      // set all the characters to 0
	s[size] = '\0';											  // set the last character to NULL to terminate the string
	int count = size - 1;								      // counter for the array

	while (num != 0)									      // from dec to binary
	{
		if (num % 2 != 0)                                     //change and update s                  
			s[count] = '1';
		count--;
		num /= 2;
	}
}

int McCluskey::bintoDec(int a[], int counter)                 //change from binary to decimal
{
	int c = 0, temp, l = 0;
	while (counter > 0)
	{
		if (a[counter - 1] == 1)
		{
			temp = pow(2, c);
			l += temp;
		}
		c++;
		counter--;
	}
	return l;													//return the decimal value
}

void McCluskey::getValues(string s)                             //get the decimal values from the binary string
{
	int counter3 = 0, k, counter4 = 0, t;
	string temp;
	Dec.clear();                                                //clear the Dec vector    
	for (int i = 0; i < s.size(); i++)
		if (s[i] == '_')                                        //check the number of dashes
			counter3++;                                         //count them
	k = pow(2, counter3);                                       //k = the number of values that could be used when the dashes are filled
	a2 = (char*)calloc(size, sizeof(char));                     //a pointer to a dynamic array
	int *PossibleCombination = new int[size];
	for (int i = 0; i < k; i++)
	{
		dectoBin(a2, i, counter3);                              //change i from decimal to bin
		Dec.push_back(a2);	                                // push all the i's into the vector Dec
	}
	for (int i = 0; i < k; i++)
	{
		for (int j = 0; j < s.size(); j++)
			if (s[j] == '_')                                   //one a _ is found
			{
				PossibleCombination[j] = Dec[i][counter4] - 48;   //change it with the number in the Dec using counter4 as its position
				counter4++;
			}
			else
				PossibleCombination[j] = s[j] - 48;            //if it is not a dash add it to array z the same as it is
		t = bintoDec(PossibleCombination, size);           //change the final number from binary to decimal
		arr[t]++;                                          //increment this value in the arr
		temp += to_string(t) + ",";                        //convert it to string and add a comma 
		counter4 = 0;
	}
	cout << temp << endl;                                      //print it ex: 0,1,8,9
	nums.push_back(temp);                                      //push it in nums                           
}