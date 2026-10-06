#include <stddef.h>
#include "graphhwn.h"
#include "mloccpy.h"
/*
 DEMO EXAMPLE:
 
   -pri- = 1 = = 2 = = 3 = = 4 = = 5 = .......
           -
  new-data >           d1
           -           d2
          d1           d3
          d2           d4
          d3
           ^
          delete_from_here
 */

// Initialize the queue array so that each priority level starts as an empty linked list.
int initQ(obj* list){
	for(int i=0;i<L_SIZE;i++){
		list[i].key=NULL; // No data is stored in the head forever
		list[i].next=NULL; // Empty when Initialize
	}
	return 0;
}

// Insert a new element into the queue at the given priority level.
int insertQ(obj* list, void* data, int priority, int data_size){
	obj* temp=mloc(sizeof(obj));  // Allocate memory
	if(temp==(void*)0) return 1;  // If allocation fails, return 1
	temp->next=list[priority].next;  // Link the new node for this priority.
	temp->key=mloc(data_size);  // Allocate memory to store data for this node

	mcpy(temp->key, data, data_size);  // Copy data into new allocated memory
	list[priority].next=temp;
    
	return 0;
}


// Remove and return one element from the queue; choose the lowest index priority that is not empty.
void* deleteQ(obj* list){
	int find=-1;  // Index of the first nonempty priority bucket; -1 means not yet found.
	for(int i=0;i<L_SIZE;i++){
		if(list[i].next!=NULL){  // Check if this priority level has at least one node.
			find=i;  // Record the index of the first lowest priority
			break;  // Stop searching
		}
	}
	if(find==-1) return NULL;  // If all buckets are empty, return NULL
	obj* c=&list[find];  // Head node
	while(c->next!=NULL && c->next->next!=NULL){ // Go to the last node
		c=c->next;
	}
	void* temp=c->next->key;  // Save the data pointer from the last node
	c->next=NULL; // Remove the last node from the linked list by cutting off its link.
	return temp;
	
}




















