#pragma once

#include <vector>

using namespace std;

class Maths{

public:
	static long long inverseModulo(long long e, long long fi);

	static long long NWD(long long  a, long long b);

	static vector<long long> generateFirstPrimes(long long counter);

	static long long randomNumber(int maxValue = 1000);

	static bool checkingDivisionByFirstPrimes(long long n, vector<long long>& firstPrimes);

	static bool MillerRabinTest(long long n);

	static long long power(long long a, long long b, long long n);
};

