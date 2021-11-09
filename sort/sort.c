#include <stdio.h>
#include <time.h>
#include <string.h>

#define N 5//00000


int cnt_c=0, cnt_s=0;

inline void exchange (int *a, int *b);
int comp (int *a, int *b);
void insertion_ (int arr[]);
void merge_ (int arr[]);
void quick_ (int arr[]);
void heap_ (int arr[]);

int main (int argc, char* argv[]){
	int arr[N];


	for (int i=0; i<N; i++){
		scanf("%d ", &arr[i]);
	}
	
	if (!strcmp(argv[1], "insertion")){
		insertion_(arr);
	}
	else if (!strcmp(argv[1], "merge")){

	}
	else if (!strcmp(argv[1], "quick")){

	}
	else if (!strcmp(argv[1], "heap")){

	}

	for (int i=0; i<N; i++){
		printf("%d ", arr[i]);
	}

	printf("\ncnt_s = %d\ncnt_c = %d", cnt_s, cnt_c);

	return 0;
}

inline void exchange (int *a, int *b){
	int tmp = *a;
	*a = *b;
	*b = tmp;
	cnt_s++;
}

int comp (int *a, int *b){
	cnt_c++;

	if (*a > *b){
		return 1;
	}else if (*a < *b){
		return -1;
	}

	return 0;
}

void insertion_ (int arr[]){
	for (int i=1; i<N; i++){
		int key, j=0;

		key = arr[i];

		for (j=i-1; j>=0; j--){
			int comparison = comp(arr+j, &key);

			if (comparison == 1){
				arr[j+1] = arr[j];
				cnt_s++;
			}else {
				break;
			}
		}

		arr[j+1] = key;
	}
}
