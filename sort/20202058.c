#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define N 500000

int cnt_c=0, cnt_s=0;

void swap (int *a, int *b);
int comp (int *a, int *b);
void insertion_ (int arr[]);
void merge_sort (int n, int arr[]);
void quick_ (int, int, int arr[]);
void heap_ (int arr[], int n);

int main (int argc, char* argv[]){
	int arr[N];


	for (int i=0; i<N; i++){
		scanf("%d ", &arr[i]);
	}
	
	if (!strcmp(argv[1], "insertion")){
		insertion_(arr);
	}
	else if (!strcmp(argv[1], "merge")){
		merge_sort (N, arr);
	}
	else if (!strcmp(argv[1], "quick")){
		quick_ (0, N-1, arr);

	}
	else if (!strcmp(argv[1], "heap")){
		heap_(arr, N);

	}

	for (int i=0; i<N; i++){
		printf("%d ", arr[i]);
	}

	printf("\ncnt_s = %d\ncnt_c = %d", cnt_s, cnt_c);

	return 0;
}

void swap (int *a, int *b){
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
	} else {return 0;}
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

void merge (int h, int m, int *U, int *V, int *S){
	int i = 0, j = 0, k = 0;

	while (i < h && j < m){

		if (U[i] > V[j]){
			S[k] = V[j];
			j++;
			cnt_s++;
		} else {
			S[k] = U[i];
			i++;
			cnt_s++;
		}

		k++;
		cnt_c++;
	}

	if (i == h){
		for (; j<m; j++){
			S[k] = V[j];
			k++;
			cnt_s++;
		}
	} else {
		for (; i<h; i++){
			S[k] = U[i];
			k++;
			cnt_s++;
		}
	}

}

void merge_sort (int n, int *S){

	if (n > 1){	
		const int h = n / 2;
		const int m = n - h;

		int *U, *V;
		U = malloc(sizeof(int) * h);
		V = malloc(sizeof(int) * m);

		for (int i=0; i<h; i++){
			U[i] = S[i];
			cnt_s++;
		}
		for (int i=0; i<m; i++){
			V[i] = S[h+i];
			cnt_s++;
		}

		merge_sort (h, U);
		merge_sort (m, V);
		merge(h, m, U, V, S);

		free(U);
		free(V);
	}
}

void partition (int low, int high, int *pivotpoint, int *S){
	srand(time(NULL));

 	int i, j;
	int rand_index = rand() % (high+1-low) + low; 
	int pivot = S[rand_index];

	swap (S+rand_index, S+high);

	j = low;

	for (i=low; i<high; i++){
		cnt_c++;
		if (S[i] < pivot){
			swap (S+i, S+j);			
			j++;
		}
	}
	*pivotpoint = j;

	swap (S+high, S+j);

}

void quick_ (int low, int high, int *S){
	if (high > low){
		int pivotpoint;
		partition(low, high, &pivotpoint, S);
		quick_(low, pivotpoint-1, S);
		quick_(pivotpoint+1, high, S);
	}
}

void heapify (int *S, int parent, int last){
	int left = parent * 2 + 1;
	int right = parent * 2 + 2;
	int max = parent;

	if (left < last && (comp(S+left, S+max)==1)){
		max = left;
	}
	if (right < last && (comp(S+right, S+max)==1)){
		max = right;
	}


	if (max != parent){
		swap(S+parent, S+max);
		heapify(S, max, last);
	}
}

void buildHeap (int *S, int n){
	for (int i=n/2-1; i>=0; i--){
		heapify(S, i, n);
	}

}

void heap_ (int *S, int n){

	buildHeap(S, n);

	for (int i=n-1; i>=0; i--){
		swap (S, S+i);
		heapify (S, 0, i);
	}
}