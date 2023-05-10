#include<stdio.h>
#include<stdlib.h>

int main(){
    
    int *p_num_list, count =0, sum = 0, limit = 0, i;

    printf("사용할 최대 개수를 입력하세요 : ");
    scanf("%d", &limit);

    p_num_list = (int*)malloc(sizeof(int));
    p_num_list = realloc(p_num_list, sizeof(int) * 100);


    while (1){
        printf("숫자 입력하시오 : ");
        scanf("%d", (p_num_list + count));
        if (*(p_num_list + count) == 9999) break;
        count++;
    }

    for (i = 0 ; i <count;i++){
        if ( i > 0 ) printf("+");
        printf("%d", *(p_num_list + i));
        sum = sum + *(p_num_list+i);

    }
    printf(" = %d\n", sum);
    printf(" = %d\n", sum);
    free(p_num_list);


    return 0;
}