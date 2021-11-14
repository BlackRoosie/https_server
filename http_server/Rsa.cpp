#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <vector>
#include "Maths.h"
#include "Rsa.h"

using namespace std;

Rsa::Rsa() {

	srand(time(0));
	firstPrimes = Maths::generateFirstPrimes(1000);
	p = Maths::randomNumber();
	q = Maths::randomNumber();
	//p = 991;
	//q = 991;

	while (!checkP)
	{
		if (Maths::checkingDivisionByFirstPrimes(p, firstPrimes) == false)
		{
			checkP = Maths::MillerRabinTest(p);
		}
		if (!checkP)
			p++;
	}

	while (!checkQ)
	{
		if (Maths::checkingDivisionByFirstPrimes(q, firstPrimes) == false)
		{
			checkQ = Maths::MillerRabinTest(q);
		}
		if (!checkQ)
			q++;
	}

	//test do china
	//p = 9817;
	//q = 9907;

	n = p * q;
	fi = (p - 1) * (q - 1);		

	//eNumber();
	e = 7;	//potrzebne do china
	while (d == 0)
	{
		d = Maths::inverseModulo(e, fi);
		//d = Maths::inverseModulo(e, 16206216);		//china
	}
}

vector<long long> Rsa::encrypt(istream& input, ostream& output)		
{
	long long single;
	const int buf_size = 10;
	char buf[buf_size];
	long long temp;

	while (!input.eof())
	{
		input.read(buf, buf_size);
		for (int i = 0; i < buf_size; i++)
		{
			if (buf[i] > 0)
			{
				single = (long long)buf[i];
				temp = Maths::power(single, e, n);
				output.write((const char*)&temp, sizeof(long long));
				msgEncode.push_back(temp);
			}

		}
	}

	return msgEncode;
}

string Rsa::decrypt(istream& input, ostream& output)
{
	long long temp;
	while (!input.eof())
	{
		input.read((char*)&temp, sizeof(long long));
		msgDecode += (char)Maths::power(temp, d, n);
	}

	output << msgDecode;
	return msgDecode;
}

long long Rsa::getP() { return p; }
long long Rsa::getQ() { return q; }
long long Rsa::getN() { return n; }
long long Rsa::getE() { return e; }
long long Rsa::getFi() { return fi; }
long long Rsa::getD() { return d; }
vector<long long> Rsa::getMesgEncode() { return msgEncode; }
string Rsa::getMsgDecode() { return msgDecode; }

Rsa::~Rsa() {}
