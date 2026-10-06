#include <stddef.h>
#include "mloccpy.h"
#include "graphhwlogn.h"
//#include "mloccpy.h"
//#include "minheap.h"  // Implementation of the min-heap used to store priorities.

/*
 DEMO EXAMPLE:
 
   -pri- = 1 = = 2 = = 3 = = 4 = = 5 = .......
           -                   ^
  new-data >           d1      |
           -           d2      |
          d1           d3      |
          d2           d4      |
          d3                   |
           ^                   |
          delete_from_here     |
                               |
                               |
  min_heap:                    ^
    1 <- 3 <- ...... => give value
                         (direct)
 */

int pri_exists[L_SIZE]={0};
int initQ(obj* list){
	list[0].hp=mloc(sizeof(minhp));  // Allocate a min-heap object in list[0] to manage which priorities are currently present.
	minhp_init(list[0].hp, 1000);  // Initialize the heap
	for(int i=0;i<L_SIZE;i++){
		list[i].key=NULL;  // No data is stored in the head forever
		list[i].next=NULL;  // Empty when Initialize
		list[i].prev=NULL;  // Empty when Initialize
	}
	return 0;
}

int insertQ(obj* list, void* data, int priority, int data_size, int compare(void*, void*)){
	int first=0;  // Flag = also mark it as the last node.
	if(!pri_exists[priority]){  // If this is the first element for this priority
		int* pri=mloc(sizeof(int)); // Allocate space to store the priority index.
		*pri=priority;  // Save
        
        // Push the priority into the min-heap so it can be chosen as the smallest active priority later.
		minhp_push(list[0].hp, pri, compare);
		pri_exists[priority]=1;  // Mark this priority as active.
		first=1;  // Flag
	}
	
    // Allocate a new node for the data.
	obj* temp=mloc(sizeof(obj));
	if(temp==(void*)0) return 1;  // allocation fails
	temp->next=list[priority].next;  // Insert the new node
	temp->prev=&list[priority];  // Previous pointer points to the header for this priority.
	temp->key=mloc(data_size);  // Allocate memory for the actual user data.

	mcpy(temp->key, data, data_size);
    if(list[priority].next!=NULL) {
        list[priority].next->prev=temp;  // Old first node now points back to the new node.
    }
	list[priority].next=temp; // Make the new node the first node for this priority.
	if(first) list[priority].prev=temp; // If this is the first node for this priority, also mark it as the last node.
	return 0;
}

void* deleteQ(obj* list, int compare(void*, void*)){
	int find=-1;  // Will store the index of the smallest active priority
	void* t=minhp_top(list[0].hp);  // Look at the smallest priority currently stored in the min-heap.
	if(t!=NULL){
		find=*(int*)t;
	}

	if(find==-1) return NULL;
    //======================================
    // Get the last node in the list for this priority
	obj* c=list[find].prev;

	void* temp=c->key;  // Memory
	list[find].prev=c->prev;  // Updata the last node
	c->prev->next=NULL;  // Disconnect the removed node from the linked list.
	
    
    // If there are no more nodes for this priority, remove the priority from the heap.
	if(list[find].next==NULL){

		minhp_pop(list[0].hp,compare);  // Remove
		pri_exists[find]=0;  //Mark as no longer active

	}
	return temp;
	
}




















