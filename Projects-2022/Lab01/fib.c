// Fibonacci Series using Recursion 
#define N 10

#include <stdio.h> 

int fib(int N) { 
	if(N <= 1) { 
		return N;
	}
	return fib(N-1) + fib(N-2); 
}

int main() { 
	printf("%d", fib(N)); 
	getchar(); 
	return 0;
}
