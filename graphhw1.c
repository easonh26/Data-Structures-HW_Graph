#include "graphhw1.h"
#include <stddef.h>
#include "mloccpy.h"
#include "bitset.h"


int initQ(obj* list){


    for(int i=0;i<L_SIZE;i++){
        list[i].key  = NULL;    // No data is stored in the head forever
        list[i].next = NULL;  // Empty when Initialize
        list[i].prev = NULL;  // Empty when Initialize
    }

    // bitset
    for (int i = 0; i < WORD_COUNT; i++) {
        pri_bits[i] = 0u;
    }
    
    word_summary = 0u;

    // init pri_exists
    for (int i = 0; i < L_SIZE; i++) {
        pri_exists[i] = 0;
    }

    // check table
    build_lsb_table();

    return 0;
}

int insertQ(obj* list, void* data, int priority, int data_size){
    int first=0;

    if(!pri_exists[priority]){
        set_priority_bit(priority);
        pri_exists[priority]=1;
        first=1;
    }


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

void* deleteQ(obj* list){
    int find = find_min_priority();
    if(find<0) return NULL;
    //======================================
    // Get the last node in the list for this priority
    obj* c=list[find].prev;

    void* temp=c->key;  // Memory
    list[find].prev=c->prev;  // Updata the last node
    c->prev->next=NULL;  // Disconnect the removed node from the linked list.

    // If there are no more nodes for this priority, remove the priority from the heap.
    if(list[find].next==NULL){
        clear_priority_bit(find);
        pri_exists[find]=0;
    }
    return temp;
}
