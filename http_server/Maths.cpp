#include <vector>
#include <time.h>
#include "Maths.h"

using namespace std;

long long Maths::inverseModulo(long long e, long long fi)
{
	//odwrotnoœæ mod fi liczby e
	long long u = 1, w = e, x = 0, z = fi, temp;
	while (w != 0)
	{
		if (w < z)
		{
			temp = u;
			u = x;
			x = temp;
			temp = w;
			w = z;
			z = temp;
		}

		temp = w / z;
		u -= temp * x;
		w -= temp * z;
	}

	if (z != 1)
		return 0;

	if (x < 0)
		x += fi;

	return x;
}

long long Maths::NWD(long long  a, long long b)
{
	if (b != 0)
		return NWD(b, a % b);

	return a;
}

vector<long long> Maths::generateFirstPrimes(long long counter)
{
	if (counter < 3)
		throw exception("Counter should be 3 or higher!");

	vector<long long> firstPrimes;
	firstPrimes.push_back(2);
	bool help = true;

	for (long long i = 3; i <= counter; i += 2)
	{
		for (long long j = 2; j * j <= i; j++)
		{
			if (i % j == 0)
				help = false;
		}

		if (help)
			firstPrimes.push_back(i);
		help = true;
	}

	return firstPrimes;
}

long long Maths::randomNumber(int maxValue) {
	//srand(time(0));
	//int a = ((double)std::rand() / RAND_MAX) * maxValue;
	long long a = static_cast<long long>(rand()) % 32767 + 32769;	//16bitowa    < 2^(n-1) + 1; 2^n - 1> 
	if (a % 2 == 0)
		a--;
	return a;
}

bool Maths::checkingDivisionByFirstPrimes(long long n, vector<long long>& firstPrimes)
{
	bool help = false;
	for (int i = 0; i < firstPrimes.size() && n >= firstPrimes[i]; i++)
	{
		if (n % firstPrimes[i] == 0)
		{
			help = true;
			break;
		}
	}

	return help;
}

bool Maths::MillerRabinTest(long long n)
{
	long long s = 0, d = n - 1, a, x, j;
	while (d % 2 == 0)
	{
		s += 1;
		d = d / 2;
	}
	for (int i = 0; i < 20; i++)
	{
		a = rand() % (n - 2) + 2;	//<2; n-2>
		x = power(a, d, n);

		if (x == 1 || x == n - 1)
			continue;

		j = 1;
		while (j < s && x != n - 1)
		{
			x = (x * x) % n;
			if (x == 1)
				return false;
			j += 1;
		}

		if (x != n - 1)
			return false;
	}

	return true;
}

long long Maths::power(long long a, long long b, long long n)
{
	long long result = 1;
	for (int i = 0; i < b; i++)
	{
		result = result * a;
		result = result % n;
	}

	return result;
}
