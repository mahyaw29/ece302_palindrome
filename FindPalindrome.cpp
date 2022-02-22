#include <string>
#include <vector>
#include <iostream>
#include <locale> 
#include <bits/stdc++.h> 
#include "FindPalindrome.hpp"

using namespace std;

//------------------- HELPER FUNCTIONS -----------------------------------------

// non-class helper functions go here, should be declared as "static" so that
// their scope is limited

// helper function to convert string to lower case
static void convertToLowerCase(string & value)
{
	locale loc;

	for (int i=0; i<value.size(); i++) {
		value[i] = tolower(value[i],loc);
	}

}

//helper function to ensure uniqueness and accepted characters
static bool isValid(string & str) 
{
	bool good = true;
	convertToLowerCase(str);
	int length = str.length();

	for (int i=0; i<length; i++) {
		if(str[i] < 'a' || str[i] > 'z')
			good = false;
	}

	return good;
}

//------------------- PRIVATE CLASS METHODS ------------------------------------

// private recursive function. Must use this signature!
void FindPalindrome::recursiveFindPalindromes(vector<string>
        candidateStringVector, vector<string> currentStringVector)
{
	int length = currentStringVector.size();

	for (int i = 0; i<length; i++) 
	{
		//declaring local varibles to be able to modify the constant paramters
		vector<string> currentVect = currentStringVector; 
		vector<string> candidateVect = candidateStringVector;

		string candidate = "";

		candidateVect.push_back(currentVect[0]);

		currentVect.erase(currentVect.begin());

		currentVect.shrink_to_fit();

		//converting candidate vector to one long string
		for(int k = 0; k<candidateVect.size(); k++) {
			candidate += candidateVect[k];
		}

		cout << currentVect.size() << endl;//not sure why but when I take this cout statement out it seg faults

		if(currentVect.size() == 0)
		{
			//checks if palindrome
			if(isPalindrome(candidate))
			{
				//adds palindrome to vector that stores the all palindromes
				allPalindromes.push_back(candidateVect);
				counter++;
				cout << "The palindrome is: " << candidate << endl;
			}
		}

		//calls cutTest 2 before running function again - to cut down on number of iterations
		if(cutTest2(candidateVect, currentVect))
			recursiveFindPalindromes(candidateVect, currentVect);
	}

}

// private function to determine if a string is a palindrome (given, you
// may change this if you want)
bool FindPalindrome::isPalindrome(string currentString) const
{
	locale loc;
	// make sure that the string is lower case...
	convertToLowerCase(currentString);
	//make sure string is valid
	bool valid = isValid(currentString);

	if(valid == false)
		return false;
	else {
		// see if the characters are symmetric...
		int stringLength = currentString.size();
		for (int i=0; i<stringLength/2; i++) {
			if (currentString[i] != currentString[stringLength - i - 1]) {
				return false;
			}
		}
		return true;
	}
}

//------------------- PUBLIC CLASS METHODS -------------------------------------

FindPalindrome::FindPalindrome()
{
	//setting counter to 0
	counter = 0;
}

FindPalindrome::~FindPalindrome()
{
	//clearing both private member vectors
	strVect.clear();
	strVect.shrink_to_fit();

	allPalindromes.clear();
	allPalindromes.shrink_to_fit();
}

int FindPalindrome::number() const
{
	return counter;
}

void FindPalindrome::clear()
{
	//clearing all palindromes
	allPalindromes.clear();
	allPalindromes.shrink_to_fit();
}

bool FindPalindrome::cutTest1(const vector<string> & stringVector)
{
	//array to store number of times each letter appears in stringVector
	int frequency[26] {0};
	//condition checker
	int odd = 0;
	string concat = "";

	//concatenating vector into one string
	for(int i = 0; i<stringVector.size(); i++)
	{
		concat += stringVector[i];
	}

	//counting the frequency of the letters in the string
	for(int k = 0; k<concat.length(); k++)
	{	
		frequency[concat[k] - 'a'] += 1;
	}

	//odd increments if there is an odd number of appearances of one letter
	for(int j = 0; j<26; j++)
	{
		if(frequency[j] % 2 == 1){
			odd++;
		}
	}	

	//if there is more than 1 odd number of letters, test fails
	if(odd>1){
		return false;
	}
	else
		return true;


}

bool FindPalindrome::cutTest2(const vector<string> & stringVector1,
                              const vector<string> & stringVector2)
{
	string candidate = "";
	string current = "";
	bool valid = true;
	int candFreq[26]{0};
	int currFreq[26]{0};

	//concatenating vectors into strings
	for(int i = 0; i<stringVector1.size(); i++)
		candidate += stringVector1[i];
	for(int j = 0; j<stringVector2.size(); j++)
		current += stringVector2[j];

	//counting number of appearances of each letter (like in cutTest1)
	for(int k = 0; k<current.length(); k++)
		currFreq[current[k] - 'a'] += 1;
	for(int l = 0; l<candidate.length(); l++)
		candFreq[current[l] - 'a'] += 1;

	//checking which string is longer
	if(current.length() < candidate.length()){
		//if there more appearances of a letter in the smaller one, test fails
		for(int m = 0; m<26; m++) {
			if(currFreq[m]>candFreq[m])
				valid = false;
		}
	//checks for when candidate is longer than current
	} else {

		for(int n = 0; n<26; n++) {
			if(candFreq[n]>currFreq[n])
				valid = false;
		}

	}

	return valid;
}

bool FindPalindrome::add(const string & value)
{
	string word = "";
	char a;

	//checking for uniqueness
	for (int j=0; j<strVect.size(); j++) {
		if(strVect[j] == value)
			return false;
	}

	//checks character by character
	for (int i = 1; i<=value.length(); i++) {
		//a is set to current character
		a = value[i-1];

		if((a == ' ') || (i == value.length())) {
			if(i==value.length())
				word+=a;
			convertToLowerCase(word);
			if(isValid(word))
			{
				strVect.push_back(word);
			} else {
				return false;
			}
			word = "";
		} else
			word += a;
	}

	//calls callTest1 before calling recursiveFindPalindrome
	if(cutTest1(strVect) == false) {
		cout << "NOT A PALINDROME -- failed cut test 1" << endl;
		return false;
	}

	//calling recursiveFindPalindrome with empty candidate vector
	vector<string> candidate;
	recursiveFindPalindromes(candidate, strVect);
	return true;
}

bool FindPalindrome::add(const vector<string> & stringVector)
{	
	string word = "";

	//checking for uniqueness
	for (int j=0; j<strVect.size(); j++) 
	{
		for(int k = 0; k<stringVector.size(); k++)
		{
			if(strVect[j] == stringVector[k])
				return false;
		}
	}

	//checks validity element by element
	for (int i=0; i<stringVector.size();i++) {
		word = stringVector[i];
		convertToLowerCase(word);
		if(isValid(word)) {
			strVect.push_back(word);
		} else {
			return false;
		}
		word = "";
	}

	//calls cutTest1 to avoid unneccesarily calling recursiveFindPalindrome
	if(cutTest1(strVect) == false) {
		cout << "NOT A PALINDROME -- failed cut test 1" << endl;
		return false;
	}

	//calls recursiveFindPalindrome with empty candidate vector
	vector<string> candidate;
	recursiveFindPalindromes(candidate, strVect);
	return true;
}


//returns vector of all the palindrom vectors
vector< vector<string> > FindPalindrome::toVector() const
{
	return allPalindromes;
}

