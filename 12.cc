#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include <math.h>
using namespace std;

/*
The sequence of triangle numbers is generated by adding the natural numbers.
So the 7th triangle number would be 1+2+3+4+5+6+7=28. The first ten terms would be:
1,3,6,10,15,21,28,36,45,55..

Let us list the factors of the first seven triangle numbers:
1: 1
3: 1,3
6: 1,2,3,6
10: 1,2,5,10
15: 1,3,5,15
21: 1,3,7,21
28: 1,2,4,7,14,28

We can see that 28 is the first triangle number to have over five divisors.

What is the value of the first triangle number to have over N divisors?

Input
First line T, the number of testcases. Each testcase consists of N in one line.

Output
For each testcase, print the required answer in one line.

Constraints
1 <= T <= 10
1 <= N <= 10^3

Sample input
4
1
2
3
4
Sample output
3
6
6
28
*/

long getTriangleNumber(int n) {
  long triangleNumber = (n * (n+1))/2;
  return triangleNumber;
}

vector<long> sieveOfEratosthenes() {
  int maxInt = 1000001;
  bool primes[maxInt];
  vector<long> foundPrimes;

  // Sieve the boolean array
  for (int i = 0 ; i < maxInt ; i++) {
    primes[i] = true;
  }

  for (int i = 2; i <= maxInt; i++) {
    if (primes[i] == true) {
      for (int j = i+i; j <= maxInt; j+=i) {
        primes[j] = false;
      }
    }
  }

  // Now take what we found and put it
  // in an array. Probably can be more efficient
  // but for the sake of this exercise, is fast
  // enough.
  for(int i = 2; i <= maxInt; i++ ) {
    if (primes[i] == true) {
      foundPrimes.push_back(i);
    }
  }

  return foundPrimes;
}

long getNumberOfDivisors(int n, vector<long> listOfPrimes) {
  map<long, int> divisorToPowers;
  int primeIndex = 0;
  // Based on the specifications of the problem, the number is always divisible by 1
  long numberOfDivisors = 1;

  // Prime factorize first
  while (n > 1) {
    long prime = listOfPrimes[primeIndex];
    if ( n % prime == 0) {
      n = n / prime;
      divisorToPowers[prime]++;
    } else {
      primeIndex++;
    }
  }

  // using 2^x*3^y ... n^z - take each of the powers and do (x+1)*(y+1)*...(z+1)
  for (map<long,int>::iterator it = divisorToPowers.begin(); it != divisorToPowers.end(); it++ ) {
    long power = it->second;
    numberOfDivisors *= (power+1);
  }

  return numberOfDivisors;
}

vector<long> getTriangleNumbersToDivisors(vector<long> listOfPrimes) {
  long numberOfDivisors = 0;
  long maxNumberOfDivisors = 1000;
  vector<long> listOfDivisors;
  listOfDivisors.push_back(1);
  for (int i = 1; numberOfDivisors <= maxNumberOfDivisors; i++) {
    long triangleNumber = getTriangleNumber(i);
    numberOfDivisors = getNumberOfDivisors(triangleNumber, listOfPrimes);
    listOfDivisors.push_back(numberOfDivisors);
  }

  return listOfDivisors;
}


int main() {
  int testCases;
  int testValue;
  vector<long> listOfPrimes = sieveOfEratosthenes();
  vector<long> triangleNumberToDivisor = getTriangleNumbersToDivisors(listOfPrimes);
  cin >> testCases;
  for (int testCase = 0; testCase < testCases ; testCase++ ) {
    cin >> testValue;
    for (int i = 1 ; i < triangleNumberToDivisor.size(); i++) {
      if (triangleNumberToDivisor[i] > testValue) {
        cout << getTriangleNumber(i) << endl;
        break;
      }
    }
  }
}