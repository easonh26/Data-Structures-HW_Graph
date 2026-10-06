#include "graphhw1.h"
#include "bitset.h"
//#include "graphhw_lib.a"
#include <stdio.h>

int main(){
	obj list[L_SIZE];
	initQ(list);
	int a[9]={1,2,3,4,5,6,7,8,9};
	insertQ(list, &a[0],2,sizeof(int));
	insertQ(list, &a[3],0,sizeof(int));
	insertQ(list, &a[4],0,sizeof(int));
	insertQ(list, &a[2],0,sizeof(int));
	printf("%d",*(int*)deleteQ(list));
	printf("%d",*(int*)deleteQ(list));
	printf("%d",*(int*)deleteQ(list));
		
	printf("%d\n",*(int*)deleteQ(list));
	
	insertQ(list, &a[1],0,sizeof(int));
	printf("%d",*(int*)deleteQ(list));
	insertQ(list, &a[8],2,sizeof(int));
	printf("%d",*(int*)deleteQ(list));
	
	return 0;
}
