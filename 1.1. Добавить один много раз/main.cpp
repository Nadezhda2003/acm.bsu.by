#include <iostream>
#include <vector>
#include <cmath>
#pragma GCC target("avx")
#pragma GCC optimize("O3")
using namespace std;

using namespace std;

long long computeGCD(long long x, long long y) {
    return y ? computeGCD(y, x % y) : x;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    long long length, increment;
    cin >> increment;

    vector<long long> originalBits(increment);
    vector<long long> newBits(increment, 0);

    for (int i = 0; i < increment; i++)
        cin >> originalBits[i];

    cin >> length;

    long long initialNumber = 0, finalNumber, tempValue = 0, powerOfTwo = 1;

    for (long long i = increment - 1; i >= 0; i--) {
        initialNumber += originalBits[i] * powerOfTwo;
        tempValue++;
        powerOfTwo <<= 1;
    }

    finalNumber = initialNumber + length;
    long long tempFinal = finalNumber, bitIndex = increment - 1, differingBits = 0, bitSum = 0, sumBefore = 0, sumAfter = 0, intermediateValue;

    while (tempFinal != 0) {
        newBits[bitIndex] = tempFinal % 2;
        tempFinal >>= 1;
        bitIndex--;
    }

    for (long long i = 0; i < increment; i++) {
        if (originalBits[i] != newBits[i]) {
            differingBits = increment - i;
            break;
        }
    }

    powerOfTwo = 1;
    while (true) {
        intermediateValue = initialNumber / powerOfTwo;
        if (intermediateValue == 0)
            break;
        sumBefore += intermediateValue;
        powerOfTwo <<= 1;
    }

    powerOfTwo = 1;
    while (true) {
        intermediateValue = finalNumber / powerOfTwo;
        if (intermediateValue == 0)
            break;
        sumAfter += intermediateValue;
        powerOfTwo <<= 1;
    }

    bitSum = sumAfter - sumBefore;
    cout << differingBits << endl;

    tempValue = computeGCD(bitSum, length);
    cout << bitSum / tempValue << "/" << length / tempValue;
}