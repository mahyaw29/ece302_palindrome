#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"
#include <string>
#include <vector>
#include "FindPalindrome.hpp"

using namespace std;

// There should be at least one test per FindPalindrome method


TEST_CASE( "Test FindPalindrome add a non-allowable word", "[FindPalindrome]" )
{
	FindPalindrome b;
	REQUIRE(!b.add("kayak1"));
}

//testing adding valid string 
TEST_CASE( "Valid string addition", "[FindPalindrome]" )
{
	FindPalindrome b;
	REQUIRE(b.add("kayak"));
}


//testing adding valid vector
TEST_CASE( "Valid vector addition", "[FindPalindrome]" )
{
	FindPalindrome b;
	vector<string> str = {"Never", "odd", "or", "even"};
	REQUIRE(b.add(str));
}


//checking adding invalid vector
TEST_CASE( "Invalid vector addition", "[FindPalindrome]" )
{
	FindPalindrome b;
	vector <string> badStr = {"Never", "odd", "or2", "even"};
	REQUIRE(!b.add(badStr));
}


//adding palindrome "a man, a plan, a canal, panama" & checking number function
TEST_CASE( "Palindrome in order", "[FindPalindrome]" )
{
	FindPalindrome b;
	vector<string> sentence = {"Aman", "aplan", "acanal", "Panama"};
	REQUIRE(b.add(sentence));
	REQUIRE(b.number() != 0);
}

//testing adding a string with a space and checking toVector function
TEST_CASE( "Palindrome string", "[FindPalindrome]" )
{
	FindPalindrome b;
	REQUIRE(b.add("race car"));
}
