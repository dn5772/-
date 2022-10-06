#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 50


int main(){
    FILE *fp = fopen("50.txt", "w");
    srand(time(NULL));

    int rand_a[N];
    int a, b, tmp;


    for (int i=0; i<N; i++){
        rand_a[i]=i+1;
    }


    for (int i=0; i<N*2; i++){
        
        a = rand()%N;
        b = rand()%N;

        tmp = rand_a[a];
        rand_a[a] = rand_a[b];
        rand_a[b] = tmp;

    }

    
    for (int i=0; i<N; i++){
        fprintf(fp, "%d ", rand_a[i]);
    }

    fclose(fp);

    return 0;
}