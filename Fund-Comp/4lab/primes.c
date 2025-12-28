//Gabriel Marques
//primes.c for lab4
//This program is supposed to find and print all the values from 1 to 1000 using the Sieve of Eratosthenes


#include <stdio.h>
#include <math.h>

void testPrime (int isPrime[]);
void printResults(int numberSet[], int isPrime[]);

int main()
{
 
    // set of numbers from 1-1000
    int numbersSet[1000]; 
    for(int i = 0; i < 1000; i++){
        numbersSet[i]=(i+1);
    }
 

  //true or false for number's index for whether the number is prime or not

    int isPrime[1001];
    for (int i = 0; i < 1001; i++) {
    isPrime[i] = 1;
    }
    isPrime[0] = 0;
    isPrime[1] = 0;

    
    testPrime(isPrime);  
    printResults(numbersSet, isPrime);
    
  return 0;
}


void testPrime (int isPrime[]){
    for (int p = 2; p * p <= 1000; ++p) {  // p * p <= n means up to sqrt(n), or that the multiple of p needs to be within 1000
        if (isPrime[p]) {
            for (int multiple = p * p; multiple <= 1000; multiple += p) { //checks all multiples of p, from p^2 in increments of p
                isPrime[multiple] = 0;
            }
        }
    }
}

void printResults(int numbersSet[], int isPrime[]){
    int count = 0;
    for (int i = 0; i < 1001; i++){
        if (isPrime[i]){
            printf("%3d ", numbersSet[i-1]);
            count++;
            if (count % 10 == 0){
                printf("\n");
            }
        }
        
    }
    printf("\n");	
}






