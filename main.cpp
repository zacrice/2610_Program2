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
    cout << "num1: " << hex << num1 << endl;
	
    istringstream iss2(str2);
    iss2 >> hex >> num2;
    cout << "num2: " << hex << num2 << endl;
	
	
    s1 = num1 >> 31;
    s2 = num2 >> 31;

    cout << "s1: " << hex << s1 << endl;
    cout << "s2: " << hex << s2 << endl;

    ex1 = num1 & 0x000000007F800000;
    ex1 = ex1 >> 23;
    ex2 = num2 & 0x000000007F800000;
    ex2 = ex2 >> 23;

    cout << "ex1: " << hex << ex1 << endl;
    cout << "ex2: " << hex << ex2 << endl;

    frac1 = num1 & 0x00000000007fffff;
    frac2 = num2 & 0x00000000007fffff;
	
	//add leading 1 to fraction to create significand e.g. 1.001.....	
	sig1 = frac1 | 0x0000000000800000;
	sig2 = frac2 | 0x0000000000800000;
	
    cout << "frac1: " << hex << frac1 << endl;
    cout << "frac2: " << hex << frac2 << endl;
	cout << "significand1: " << hex << sig1 << endl;
	cout << "significand2: " << hex << sig2 << endl;
    exponent = (ex1 + ex2) - 127;
    //display the output
    cout << "exponent: " << hex << exponent << endl;
	//multiply significands
    fraction = sig1 * sig2;
    cout << "fraction: " << hex << fraction << endl;
	//convert fraction to binary string to count leading zeroes
	string s = bitset<64>(fraction).to_string();
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
	//shift left by amount of zeroes to remove first bit
	fraction = fraction << zeroes;
	
	// shift right by 64 - 23 bits to store at correct range
	fraction = fraction >> (64-23);
	
	exponent++; //hard coding exponent change
	exponent = exponent << 23; //shift exponent to correct range
	//string ms = bitset<64>(exponent).to_string(); test print exponent
	//cout << ms << endl;
	//determine sign
	sign = s1 xor s2;
	sign = sign << 31;
	unsigned long long result = sign | exponent | fraction;
	cout << "Final Result: " << hex << result <<endl;
	

    return 0;
}
