#include <stdio.h>
#include <stdlib.h>
int m;
int q;
int hash(int key) {
    return key%m;
}
int second_hash(int key) {
    return q-(key%q);
}
int double_hash(int key,int collision_time) {
    return (hash(key)+collision_time*second_hash(key));
}
void insert_item(int *bucket,int key) {
    int index=hash(key);
    int i=0;
    for (;i<m&&bucket[index];i++) {
        index=double_hash(key,i);
        if (index<0||m<=index)index=(m+index)%m;
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
        index=double_hash(key,i);
        if (index<0||m<=index)index=(m+index)%m;
    }
    if (i==m)printf("-1");
    else {
        printf("%d %d",index,key);
    }
}
void print(int *bucket) {
    for (int *pointer=bucket;pointer<bucket+m;pointer++)printf(" %d",*pointer);
}
int main() {
    setbuf(stdout,NULL);
    int n;
    scanf("%d %d %d",&m,&n,&q);
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
            case 'p':
                print(bucket);
                break;
        }
        if (input=='e') {
            print(bucket);
            break;
        }
        printf("\n");
    }
    free(bucket);
    return 0;
}