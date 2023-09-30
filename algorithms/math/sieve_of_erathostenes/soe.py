import math

def findPrimes(n):
    isPrimes = [True]*(n+1)
    for p in range(2, math.isqrt(n)):
        if isPrimes[p]:
            for j in range(p*p, n+1, p):
                isPrimes[j] = False
    primes = [i for i in range(2, n+1) if isPrimes[i]]
    return primes

if __name__ == '__main__':
    print(findPrimes(100))