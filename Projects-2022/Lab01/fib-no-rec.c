#define N 25

#include <stdio.h> 

int main() { 
    
    int first = 0; 
    int second = 1; 
    int sum;
    int i = 0;
    for(i = 0; i < N; i++) { 
        if(i <= 1) { 
            sum = i; 
        } else { 
            sum = first + second;
            first = second; 
            second = sum; 
        }

        printf("%d\n", sum); 
    }

//    printf("%d", sum);

    return 0; 
}
