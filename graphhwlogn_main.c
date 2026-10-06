#include "graphhwlogn.h"
#include <stdio.h>

int compareInts(void* a, void* b) {
    int ia = *(int*)a;
    int ib = *(int*)b;
    if (ia < ib) return -1;
    if (ia > ib) return 1;
    return 0;
}

int main(){
	obj list[L_SIZE];
	initQ(list);
	int a[9]={1,2,3,4,5,6,7,8,9};
	insertQ(list, &a[0],2,sizeof(int),compareInts);
	insertQ(list, &a[3],0,sizeof(int),compareInts);
	insertQ(list, &a[4],0,sizeof(int),compareInts);
	insertQ(list, &a[2],0,sizeof(int),compareInts);
	printf("%d",*(int*)deleteQ(list,compareInts));
	printf("%d",*(int*)deleteQ(list,compareInts));
	printf("%d",*(int*)deleteQ(list,compareInts));
		
	printf("%d\n",*(int*)deleteQ(list,compareInts));
	
	insertQ(list, &a[1],0,sizeof(int),compareInts);
	printf("%d",*(int*)deleteQ(list,compareInts));
	insertQ(list, &a[8],2,sizeof(int),compareInts);
	printf("%d",*(int*)deleteQ(list,compareInts));
	
	return 0;
}