#include<stdio.h>
#include<stdlib.h>

int main(){
    int a, b, attempt;
    int mid;
    char answer;
    scanf("%d %d %d", &a, &b, &attempt);
    
    while (attempt > 0){
        mid = (a + b)/2;
        scanf(" %c", &answer);
        //printf("%c\n", answer);
        if (answer == 'Y'){
            a = mid + 1;
        }
        else if (answer == 'N'){
            b = mid;
        }
        attempt -= 1;
    }
    mid = (a + b)/2;
    printf("%d", mid);
    return 0;
}