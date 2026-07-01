#include <stdio.h>
void hanoi(char,char,char,int);
int main() {
    int plate_count;
    scanf("%d",&plate_count);
    hanoi('A','B','C',plate_count);
}
void hanoi(char from,char aux,char to,int plate_count) {
    if (plate_count==1) {
        printf("from %c to %c\n",from,to);
        return;
    }
    hanoi(from,to,aux,plate_count-1);
    printf("from %c to %c\n",from,to);
    hanoi(aux,from,to,plate_count-1);

}