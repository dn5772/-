#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
// #include <Windows.h>

int price[4], num[4], count[4] = {0};
char item0[10], item1[10], item2[10], item3[10];

void sale(int i, char item[]){
    
    if (num[i] < 1){
        printf("재고가 부족합니다.");
    }

    int money;
    printf("돈을 넣어주세요\n");
    scanf("%d", &money);

    if (money < price[i]) {
        printf("돈이 부족합니다\n");
    }
    else {
        printf("잔돈 %d원이 나왔습니다\n", money - price[i]);
        switch (i){
            case 0:
            printf("%s가 나왔습니다\n", item0);
            break;
            case 1:
            printf("%s가 나왔습니다\n", item1); 
            break;
            case 2:
            printf("%s가 나왔습니다\n", item2); 
            break;
            case 3:
            printf("%s가 나왔습니다\n", item3); 
            break;
        }
        count[i]++;
        num[i]--;
    }

}

void print(int i){
    switch (i){
        case 0:
        printf("%-10s|", item0);
        break;
        case 1:
        printf("%-11s|", item1); 
        break;
        case 2:
        printf("%-12s|", item2); 
        break;
        case 3:
        printf("%-13s|", item3); 
        break;
    }

    printf("%-16d%-16d%-16d%-12d\n", price[i], count[i], num[i], price[i]*count[i]);


}

int main()
{
	int c;
    //상품 설정
    
    for (int i=0; i<4; i++){
        printf("%d번째 상품 이름을 입력해 주세요\n", i+1);
        switch (i){
            case 0:
            scanf("%s", item0);
            break;
            case 1:
            scanf("%s", item1);
            break;
            case 2:
            scanf("%s", item2);
            break;
            case 3:
            scanf("%s", item3);
            break;
            
        }
        printf("%d번째 상품 가격을 입력해 주세요\n", i+1);
        scanf("%d", &price[i]);

        printf("%d번째 상품 수량을 입력해 주세요\n",i+1);
        scanf("%d", &num[i]);

    }
    printf("상품 설정이 완료 되었습니다.\n");

    //판매


    _Bool loop = 1;

    while (loop)
    {
        /* code */
        printf("원하는 상품의 번호를 입력해주세요 0.관리자 모드 1.%s(%d원) 2.%s(%d원) 3.%s(%d원) 4.%s(%d원) 5.종료\n", item0, price[0], item1, price[1], item2, price[2], item3, price[3]);
        scanf("%d", &c);

        switch (c) {
            
            case 1:
            sale(0, item0);
            break;

            case 2:
            sale(1, item1); 
            break;

            case 3:
            sale(2, item2); 
            break;

            case 4:
            sale(3, item3); 
            break;

            case 5:
            loop = 0;
            break;

            case 0 :
            // system("cls");
            printf("상품------판매가격----판매수량----재고수량----판매액---\n");
            for (int i=0; i<4; i++){
                print(i);
            }
            break;

            default :
            printf("오류가 발생했습니다. 다시 시도해 주세요\n");
        }
        
    
    }



    return 0;
}
