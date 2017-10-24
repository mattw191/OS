/// counts number of primes from standard input
/// compile with:
/// $ gcc countPrimes.c –O2 -o count –lm
/// by Pavol Federl, for CPSC457 Spring 2017, University of Calgary
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <pthread.h>

void*handler(void*num);
int isPrime(int64_t n);
//pthread_t threads;

pthread_mutex_t count_mutex;

volatile int64_t count = 0;
volatile int64_t numbersfound = 0;

/// primality test, if n is prime, return 1, else return 0
int isPrime(int64_t n)
{
printf("num %ld\n", n);
if( n <= 1) return 0; // small numbers are not primes
if( n <= 3) return 1; // 2 and 3 are prime
if( n % 2 == 0 || n % 3 == 0) return 0; // multiples of 2 and
int64_t i = 5;
int64_t max = sqrt(n);
while( i <= max) {
if (n % i == 0 || n % (i+2) == 0) return 0;
i += 6;
}
return 1;
}


int main( int argc, char ** argv)
{
/// parse command line arguments
int nThreads;
if( argc != 1 && argc != 2) {
printf("Uasge: countPrimes [nThreads]\n");
exit(-1);
}
if( argc == 2) nThreads = atoi( argv[1]);
/// handle invalid arguments
if( nThreads < 1 || nThreads > 256) {
printf("Bad arguments. 1 <= nThreads <= 256!\n");
}

pthread_mutex_init(&count_mutex, NULL);
pthread_t threads[nThreads];


printf("Counting primes using %d thread%s.\n",
nThreads, nThreads == 1 ? "" : "s");

long indexer;
  for(indexer =1;indexer<=nThreads;indexer++){
	  if( 0 != pthread_create(&threads[(indexer-1)],NULL,handler,(void*)indexer)){
      printf("Oops, pthread_create failed.\n");
      exit(-1);
    }}

   //join all the threads
  for(indexer=1;indexer<=nThreads;indexer++){
    pthread_join(threads[(indexer-1)],NULL);}
    
pthread_mutex_destroy(&count_mutex);
//printf("found %ld numbers\n", numbersfound);
/// report results*/
printf("Found %ld primes.\n", count);
return 0;
}


void*handler(void*num){
while( 1) {
	int64_t num;
	pthread_mutex_lock(&count_mutex);	
	if( 1 != scanf("%ld", & num)) {
	pthread_mutex_unlock(&count_mutex); 
	break;}
	pthread_mutex_unlock(&count_mutex); 

	if( isPrime(num)) count ++;
}
}



