#include <iostream>
#include <math.h>
#include <fstream>
#include "Main.h"
using namespace std;

void Encode(char  data[5], int b, std::ofstream &primefile);
void Decode();

int main(void)
{
	int maxNum;												//initialize variables
	bool *BinString;
	ofstream primefile;
	int c = 0;
	int i = 0;
	primefile.open("primes.dat");							//open encode file
		
	char data[5];

															//get max number
	cout << "Enter largest number to check:";
	cin >> maxNum;

															//malloc binary string
	BinString = (bool*)malloc(maxNum);

															//initialize the binary string
	BinString[0] = 0;
	BinString[1] = 0;
	for (int a = 2; a <= maxNum; a++)
	{
		BinString[a] = 1;
		
	}

															//loop and remove logic
	for (unsigned int b = 2; b < maxNum; b++)
	{
		if (!(b % 1000000)) cout << b << " = " << b / 1000000 << "x 10^6 " << '\n';
		if (BinString[b] == 1)
		{
			c++;
			
			Encode(data, b, primefile);
		}
		for (int d = 2; d <= maxNum / b; d++)
		{
			BinString[b*d] = 0;
		}
	}
	if (!(maxNum % 1000000)) cout << maxNum << " = " << maxNum / 1000000 << "x 10^6 " << '\n';		//report position
	cout << '\n';
	primefile << (char)26 << (char)26 << (char)26;
	primefile.close();
	Decode();
	return 0;
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////
void Encode(char  data[4], int b, std::ofstream &primefile)
{
	if (b < 256) data[0] = 1;
	else if (b < 65536) data[0] = 2;
	else if (b < 16777216) data[0] = 3;
	else data[0] = 4;
	data[1] = static_cast<unsigned char>(b & 0xFF);
	data[2] = static_cast<unsigned char>((b >> 8) & 0xFF);
	data[3] = static_cast<unsigned char>((b >> 16) & 0xFF);
	data[4] = static_cast<char>((b >> 24) & 0xFF);
	primefile.write(data, data[0]+1);
}

void Decode()
{
	cout << "Reading encoded file..\n\n\n";
	ifstream infile;
	infile.open("primes.dat");
	int i = 0;
	int decoded=0;
	char c = 0;
	unsigned char data[5];
	data[0] = 1;
	data[1] = 0;
	data[2] = 0;
	data[3] = 0;
	data[4] = 0;
	while (1)
	{
		infile.read(&c, 1);
		
		if (data[0] > 5)
		{
			decoded = data[1] + data[2] * 256 + data[3] * 65536 + data[4] * 16777216;
			cout << '\n';
			return;
		}
		if (data[0] == i-1)
		{
			decoded = (int)data[1] + (int)data[2] * 256 + (int)data[3] * 65536 + (int)data[4] * 16777216;
			data[0] = c;
			data[1] = 0;
			data[2] = 0;
			data[3] = 0;
			data[4] = 0;
			cout << decoded << ",\t";
		
			i = 1;
		}
		else {
			data[i] = c;
			i++;
			
		}

	}
	
	cout << decoded;
	infile.close();
	cout << '\n';
	return ;
}
