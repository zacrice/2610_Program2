/*
Zac Rice & Michael Hummer
Assignemnt 2
CSCE 2610.001
*/

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string.h>
#include <stdlib.h>
#include <bitset>
#include <iomanip>
using namespace std;

int main()
{
    string str1, str2;
    unsigned long long num1, num2, s1, s2, ex1, ex2, frac1, frac2, sign, exponent, fraction, sig1, sig2;
    cout<<"Enter a single precision floating point (in hex): ";
    cin>>str1;
    cout<<"Enter another single precision floating point (in hex): ";
    cin>>str2;

    istringstream iss1(str1);
    iss1 >> hex >> num1;
	
    istringstream iss2(str2);
    iss2 >> hex >> num2;
	
    s1 = num1 >> 31;
    s2 = num2 >> 31;


    ex1 = num1 & 0x000000007F800000;
    ex1 = ex1 >> 23;
    ex2 = num2 & 0x000000007F800000;
    ex2 = ex2 >> 23;
   

    frac1 = num1 & 0x00000000007fffff;
    frac2 = num2 & 0x00000000007fffff;
	
	//add leading 1 to fraction to create significand e.g. 1.001.....	
	sig1 = frac1 | 0x0000000000800000;
	sig2 = frac2 | 0x0000000000800000;

    exponent = (ex1 + ex2) - 127;
    //display the output
    string ns = bitset<64>(exponent).to_string();//------display output in binary------
    char Bexponent[64];
    int zCount;
    strcpy(Bexponent, ns.c_str());
    for (int i = 0; i<64; i++)
    {
		if (Bexponent[i] == '1')
		{
			zCount = i;
			break;
		}
	}
	cout << "Step 1 - Add the expoenents" << endl << "Result (in binary): ";
	for (int i = zCount; i < 64; i++)
	{
		cout << Bexponent[i];
	}
	cout << endl << endl;					
    //----------end exponent display---------
	//multiply significands
    fraction = sig1 * sig2;
	//convert fraction to binary string to count leading zeroes
	string s = bitset<64>(fraction).to_string(); //this is all zeroes on the cse machine
	char bits[64];
	strcpy(bits, s.c_str());
	int zeroes;
	for (int i = 0; i < 64; i++)
	{
		if (bits[i] == '1')
		{
			zeroes = i+1; 
			break;
		}
	}
	//////weird dynamic right shifting
	fraction = fraction >> (41-zeroes);
	string s22 = bitset<64>(fraction).to_string();
	char mmmbits[64];
	strcpy(mmmbits, s22.c_str());
	for (int i = 0; i<64; i++)
	{
		if(mmmbits[i] == '1')
		{
			zeroes = i+1;
			break;
		}
	}
	//// 
	//print step 2
	cout << "Step 2 - Multiply significands" << endl << "Result (in binary): ";
	for (int i = zeroes-1; i<64; i++)
	{
		cout << mmmbits[i];
	}
	cout << endl << endl;
	//end print step2
	//shift left by amount of zeroes to remove first bit
	fraction = fraction << zeroes;
	
	// shift right by 64 - 23 bits to store at correct range
	fraction = fraction >> (64-23);
	//print step 3
	string fs = bitset<64>(fraction).to_string();
	char fracbits[64];
	strcpy(fracbits, fs.c_str());
	cout << "Step 3 - Normalize the significand: " << endl << "Result of fraction (in binary): ";
	for (int i = 64-23; i < 64; i++)
	{
		cout << fracbits[i];
	}
	cout << endl;
	exponent++; //hard coding exponent change
	string bs = bitset<64>(exponent).to_string();
	char expBits[64];
	strcpy(expBits, bs.c_str());
	cout << "Result of exponent (in binary): ";
	for (int i = 64-8; i<64; i++)
	{
		cout << expBits[i];
	}
	cout << endl << endl;
	exponent = exponent << 23; //shift exponent to correct range

	//determine sign
	sign = s1 xor s2;
	cout << "Step 4 - Determine the sign" << endl;
	cout << "Result (in binary): " << sign << endl << endl;
	sign = sign << 31;
	unsigned long long result = sign | exponent | fraction;
	cout << "Product (in hex): " << hex << result <<endl << endl;
	

    return 0;
}
