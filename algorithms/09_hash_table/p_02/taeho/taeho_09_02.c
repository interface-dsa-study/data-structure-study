#include <stdio.h>
#include <stdlib.h>
int m;
int hash(int key) {
    return key%m;
}
void insert_item(int *bucket,int key) {
    int index=hash(key);
    int i=0;
    for (;i<m&&bucket[index];i++) {
        index++;
        if (index==m)index=0;
    }
    if (i==m)printf("-1");
    else {
        for (int j=0;j<i;j++)printf("C");
        bucket[index]=key;
        printf("%d",index);
    }
}
void search(int *bucket,int key) {
    int index=hash(key);
    int i=0;
    for (;i<m&&bucket[index]!=key;i++) {
        index++;
        if (index==m)index=0;
    }
    if (i==m)printf("-1");
    else {
        for (int j=0;j<i;j++)printf("C");
        printf("%d %d",index,key);
    }
}
int main() {
    setbuf(stdout,NULL);
    int n;
    scanf("%d %d",&m,&n);
    int *bucket=calloc(m,sizeof(*bucket));
    int time=n;
    while (1) {
        char input;
        int key;
        scanf(" %c",&input);
        switch (input) {
            case 'i':
                scanf("%d",&key);
                if (time)insert_item(bucket,key);
                time--;
                break;
            case 's':
                scanf("%d",&key);
                search(bucket,key);
                break;
        }
        if (input=='e')break;
        printf("\n");
    }
    free(bucket);
    return 0;
}