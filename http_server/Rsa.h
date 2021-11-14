#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <vector>
#include "Maths.h"

using namespace std;

class Rsa {


	long long p, q, n, e, fi, d = 0;
	vector<long long> msgEncode;
	string msgDecode = "";
	bool checkP = false, checkQ = false;
	vector<long long> firstPrimes;


public:
	Rsa();

	vector<long long> encrypt(istream& input, ostream& output);	

	string decrypt(istream& input, ostream& output);

	long long getP();
	long long getQ();
	long long getN();
	long long getE();
	long long getFi();
	long long getD();
	vector<long long> getMesgEncode();
	string getMsgDecode();

	~Rsa();

};