#include "minheap.h"
#include "mloccpy.h"
#include <stddef.h>

// Initialize the heap with a given capacity; allocate space for the pointer array.
int minhp_init(minhp* m, int cap){
	m->cap=cap;
	m->data=mloc(cap*sizeof(void*));
	if(m->data==(void*)0) return -1;
	m->size=0;
	return 0;
}

// Add it at button and from down to top
int minhp_in(minhp* m, int index, int compare(void*, void*)){
	while(index>0){
		int parent=(index-1)/2;   // Compute the parent index in the binary heap.
        
        // If current node is smaller than its parent according to compare, swap them.
		if(compare(m->data[index],m->data[parent])<0){
			void* temp=m->data[parent];
			m->data[parent]=m->data[index];
			m->data[index]=temp;  // Swap them
			index=parent;
		}else{
			break;  // Satisfied, stop
		}
	}
	return 0;
}

// Insert a new element into the heap, then fix the heap
int minhp_push(minhp* m, void* data, int compare(void*, void*)){
	if(m->size>=m->cap) return -1;
	m->data[m->size]=data;  // Place new element at the end.
	minhp_in(m,m->size,compare); // Restore heap property by moving it up.
	m->size++;  // Increase
	return 0;
}

// Some one swap to top and fix the tree
int minhp_out(minhp* m, int index, int compare(void*, void*)){
	int l=(2*index)+1;  // Left child index
	int r=(2*index)+2;  // Right child index
	int small=index;  // Store which is smallest
	while(1){
		l=(2*index)+1;
		r=(2*index)+2;
		small=index;
        
        // If left child exists and is smaller, update small
		if(l<m->size && compare(m->data[l],m->data[small])<0){
			small=l;
		}
        // If right child exists and is smaller than current smallest, update small.
		if(r<m->size && compare(m->data[r],m->data[small])<0){
			small=r;
		}
		if(index==small){
			break;   // If the smallest is already current index, heap property is satisfied.
		}
		void* temp=m->data[small];  //Swap node
		m->data[small]=m->data[index];
		m->data[index]=temp;
		
		index=small; // Continue sifting down from the child position.
	}
	return 0;
}

int minhp_pop(minhp* m, int compare(void*, void*)){
	if(m->size<=0) return -1;   // If heap is empty, nothing to pop.
	m->size--;  // Last element index
	void* temp=m->data[m->size];  // Save last element.
	m->data[m->size]=m->data[0];  // Move the smallest to button
	m->data[0]=temp;
	minhp_out(m,0,compare);  // Fix the tree
	return 0;
}

void* minhp_top(minhp* m){
	if(m->size==0) return NULL;
	return m->data[0];  // Return pointer to the smallest element
}














