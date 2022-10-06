#define MAXN 300

#include<stdio.h>
#include<string.h>

int N;                     // [N]umber of vertex
int W[MAXN + 1][MAXN + 1]; // [W]eight array
int D[MAXN + 1][MAXN + 1]; // [D]istance array
int P[MAXN + 1][MAXN + 1]; // [P]ath array
int cnt[MAXN + 1][MAXN + 1];
int p_cnt;

int minimum(int , int);
void floyd();
void path (int, int);
void path_cnt (int q, int r);

int main(int argc, char *argv[]) {

    scanf("%d", &N); // input N
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            scanf("%d", &W[i][j]); // input W[i][j] : i -> j weight
        }
    }

    // TODO : Floyd's Alogirhtm

    if(strcmp(argv[1], "array") == 0) {

        for(int i = 0; i < N; i++) {
            for(int j = 0; j < N; j++) {
                if (!(i==j)){
                    if (W[i][j] == 0){
                        W[i][j] = 0x7FFF;
                    }
                }
            }
        }

        floyd();

		printf("%d\n", N);

        for(int i = 0; i < N; i++) {
            for(int j = 0; j < N; j++) {
                printf("%d ", D[i][j]);
            }
            printf("\n");
        }


        for(int i = 0; i < N; i++) {
            for(int j = 0; j < N; j++) {
                printf("%d ", P[i][j]);
            }
            printf("\n");
        }
    }

    else if(strcmp(argv[1], "path") == 0) {
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < N; j++) {
                if (!(i==j)){
                    if (W[i][j] == 0){
                        W[i][j] = 0x7FFF;
                    }
                }
            }
        }

        floyd();

        for (int i=0; i<N; i++){
            for (int j=0; j<N; j++){
                p_cnt = 0;
                path_cnt (i, j);
                cnt[i][j] = p_cnt;
            }
        }

        for (int i=0; i<N; i++){
            for (int j=0; j<N; j++){
                if ((i==j)||(D[i][j]==0x7FFF)){
                    printf("0\n");
                }
                else{
                    printf("%d %d ", cnt[i][j]+2, i+1);
                    path (i, j);
                    printf("%d\n", j+1);
                }
            }
        }        

    }

    return 0;
}

// int minimum (int a, int b){
// 	if (a > b) {return b;}
// 	else {return a;}
// }

void floyd (){
    int i, j, k;

    for (i=0; i<N; i++){
        for (int j=0; j<N; j++){
            P[i][j] = 0;
        }
    }

	for (i=0; i<N; i++){
		for (j=0; j<N; j++){
			D[i][j] = W[i][j];
		}
	}

	for (k=0; k<N; k++){
		for (i = 0; i<N; i++){
			for (j=0; j<N; j++){
                if (D[i][k] + D[k][j] < D[i][j]){
                    P[i][j] = k+1;
                    D[i][j] = D[i][k] + D[k][j];
                }
            }
        }
    }

}

void path (int q, int r){

    if (!(P[q][r]==0)){
        path (q, P[q][r]-1);
        printf("%d ", P[q][r]);
        path (P[q][r]-1, r);
    }

}

void path_cnt (int q, int r){

    if (P[q][r] != 0){
        p_cnt++;
        path_cnt (q, P[q][r]-1);
        
        path_cnt (P[q][r]-1, r);
    }

}