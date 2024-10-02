/*
 * author: Noa Figenblat
 * title: Project 3
 * due: 3/22/22
 */ 
// do not include other libraries
#include <stdio.h>
#include <stdlib.h>

// ***************************************
// *** struct definitions ****************
// *** do not change these ***************
// ***************************************
typedef struct NODE {int data; struct NODE* next;} NODE; // nodes of the linked list
typedef struct LINKED_LIST {struct NODE *head;} LINKED_LIST; // struct to act as the head of the list


// ***************************************
// *** provided functions  ****************
// ***************************************

// this function returns a LINKED_LIST struct to
// act as the head of the linked list.
// do not change this function
LINKED_LIST Create_List(void) {LINKED_LIST list = {NULL}; return list;}

// call this function to verify malloc worked when you create new nodes
void Verify_Malloc(NODE *node) {if (node == NULL) {printf("Malloc Failed\n"); exit(1);} return;}

// do not change this function
// this function prints out all of the nodes in the linked list
void Print_List(FILE *out, LINKED_LIST list) {
    if (list.head == NULL) {printf("\n"); return;} //empty list
    NODE *current = list.head;
    while (current->next != NULL) {
        fprintf(out, "%d -> ",current->data);
        current = current->next;
    }
    fprintf(out, "%d\n",current->data);
    return;
}

// ******************************************************
// *** Complete the following functions  ****************
// ******************************************************

// this function returns the number 
// of elements in the linked list
int Size(LINKED_LIST list){

	// int var to count the number of elements 
	int count = 0;

	//struct type NODE which is the current node of the linked list (initially the head node)
	struct NODE *current = list.head;

	// while loop counting how many elements are in the linked list 
	while (current != NULL){
		count ++; 	// incrementing count
		current = current -> next;	// moving current to the next node
	}

	return count;	//returning the number of elements in the linked list

}

// this function adds an element to
// the front of the list
void Push_Front(LINKED_LIST *list, int data){

	// creating a new struct NODE for the new node to be pushed to the front 
	struct NODE *newNode = (NODE *)malloc(sizeof(struct NODE));

	// setting the new node's data to int data 
	newNode -> data = data;

	// setting the new node's next node to the original head of the linked list
	newNode -> next = list -> head;

	// setting list's head to the new node
	list -> head = newNode;

}

// this function adds an element 
// to the end of the linked list 
void Push_Back(LINKED_LIST *list, int data) {

	// creating a new struct NODE for the current node of the linked list 
	struct NODE *current = (NODE *)malloc(sizeof(struct NODE));

	if (list -> head != NULL){
		// setting the current node to the head node of the list 
		current = list -> head;

		// while loop until current's next is null
		while (current -> next != NULL){
			current = current -> next;	// incrementing current node to the next node
		}	

		// new struct NODE for the new node to be pushed to the back of the linked list 
		struct NODE *newNode = (NODE *)malloc(sizeof(struct NODE));
	
		newNode -> data = data;	// new node's data set to data
		newNode -> next = NULL; // new node's next node set to NULL
		current -> next = newNode; // the last node in the list has its next node set to the new node
	}
	else{
		current -> data = data;
		current -> next = NULL;
		list -> head = current;
	}
}


// if the list is not empty
// the value of the first element of the list is returned by reference in the parameter data
// the first element of the list is deleted
// returns 0 if the list is empty otherwise returns 1
// remember to free the deleted node
int Pop_Front(LINKED_LIST *list, int *data) {
	
	// creating new struct NODE for the next node 
	struct NODE *nextNode = (NODE *)malloc(sizeof(struct NODE));
	
	// if the list is empty return 0
	if (list -> head == NULL){
		return 0;
	}
	// else delete the first element of the list 
	else{
		// storing the address of data from head in *data for use in main method to ensure proper 
		// element popped from the linked list 
		*data = list -> head -> data;
		nextNode = list -> head -> next;
		free (list -> head); 	// freeing the deleted node
		list -> head = nextNode; // setting new head to the nextNode
		return 1; // return 1 if the list is not empty 
	}

}


// if the list is not empty
// the value of the last element of the list is returned by reference in the parameter data
// the last element of the list is deleted
// returns 0 if the list is empty otherwise returns 1
// remember to free the deleted node
int Pop_Back(LINKED_LIST *list, int *data) {

	// if the list is empty return 0
	if( list -> head == NULL){
		return 0;
	}

	// else if there is only one element in the list (returns 1)
	else if (list -> head -> next == NULL){
		*data = list -> head -> data;
		free (list -> head);
		list -> head = NULL;
		return 1;
	}
	
	// else delete the last element of the linked list and return 1
	else{

		// struct NODE current which is the current node in the linked list 
		struct NODE *current = (NODE *)malloc(sizeof(struct NODE));
		current = list -> head;
		// iterating through the linked list till we reach the second to last node
		while(current -> next -> next != NULL){
			current = current -> next;
		}	

	// once the second to last node is reached, delete the last element of the linked list 
	
		// store the address of data in *data which is used to check for the whether the correct 
		// element was popped 
		*data = current -> next -> data;
		free(current -> next); // free the last element of the linked list 
		current -> next = NULL; // set the last element of the linked list to NULL
	
		return 1;
	}
}

// this function returns the number 
// of times that the value of the parameter 
// data appears in the list
int Count_If(LINKED_LIST list, int data) {
    
	// int var count which counts how many times the value of the parameter appears in the linked list 
	int count = 0;

	// struct NODE current which contains the current node of the linked list 
	struct NODE *current = list.head; // initially initialized to the head node of the linked list 

	// while the current node is not null
	while (current != NULL){
		if(current -> data == data){ 	// if current's data matches the value of the parameter
			count ++;		// increment the count
		}
		current = current -> next;	// increment current to the next node
	}

	return count;	// return the count of the num of times the value appears in the list 
}

// delete the first node containing the data value
// return 1 if something was deleted otherwise 0
// remember to free the deleted node
int Delete(LINKED_LIST *list, int data) {

	// if the value does not appear in the list 
	if (Count_If(*list, data) == 0){
		return 0; 	// return 0 nothing deleted 
	}

	// else delete the first node containing the data value
	else{
		// struct NODE for the current node 
		struct NODE *current = (NODE *)malloc(sizeof(struct NODE));
		// set current to the head node of the list 
		current = list -> head;
		// struct NODE to hold the next node in the list 
		struct NODE *nextNode = (NODE *)malloc(sizeof(struct NODE));

		// while loop to find the index of the first appearence of the value 
		while (current != NULL){
			// if the current node contains the value break the loop
			if(current -> data == data){
				break;
			}
			// otherwise increment current to the next node 
			else{
				current = current -> next;
			}
		}

		// setting next and data for nextNode 
		nextNode -> next = current -> next -> next;
		nextNode -> data = current -> next -> data;

		// free current 
		free(current);

		// set current's data and next to the data and next of nextNode
		current -> data = nextNode -> data;
		current -> next = nextNode -> next;
	}

	return 1;	//return 1 as an element was deleted 
}

// return 1 if the list is empty otherwise returns 0
int Is_Empty(LINKED_LIST list) {
    
	// if the size of the list is 0 (meaning it is empty) return 1 
	if (Size(list) == 0){
		return 1;
	}
	// otherwise list is not empty and return 0
	else{
		return 0;
	}
}

// delete all elements of the list
// remember to free the nodes
void Clear(LINKED_LIST *list) {
    
	// creating struct NODE for current and nextNode
	struct NODE *current = (NODE *)malloc(sizeof(struct NODE));
	struct NODE *nextNode = (NODE *)malloc(sizeof(struct NODE));
	current = list -> head;		// initiallizing current to the head of the linked list 

	// while current is not NULL
	// iterates through the loop popping all of the nodes untill the list is cleared
	while (current != NULL){
		int removedData = current -> data; 	// removedData holds the data in current which is passed to Pop_Front
		nextNode = current -> next; 		// nextNode set to the next node in the list 
		Pop_Front(list, &removedData);		// delete the first element of the list
		current = nextNode;			// current is set to the next node in the list 
	}
}


// if an element appears in the list 
// retain the first occurance but
// remove all other nodes with the same 
// data value
void Remove_Duplicates(LINKED_LIST *list) {

	// creating struct nodes for current, nextNode, and temp nodes
	struct NODE *current = (NODE *)malloc(sizeof(struct NODE));
	struct NODE *nextNode = (NODE *)malloc(sizeof(struct NODE));
	struct NODE *temp = (NODE *)malloc(sizeof(struct NODE));

	// initializing current node to the head of the linked list
	current = list -> head;

	// while current is not NULL
	while(current != NULL){
		// initializing the next node in the list 
		nextNode = current -> next;
		// while the nextNode is not NULL
		while(nextNode != NULL){
			// if the data in the next node is the same as the data in the current node delete the duplicate
			if(nextNode -> data == current -> data){
				current -> next = nextNode -> next;	// current's next node is set to nextNode's next node
				temp = nextNode;			// temp is set to newNode
				nextNode = nextNode -> next;		// nextNode is set to the following node
				free(temp);				// free the temp node 
			}
			// otherwise move the nextNode to the following node
			else{
				nextNode = nextNode -> next;
			}
		}
		// increment current to the next node in the list 
		current = current -> next;
	}
}

// modify main to completely test your functions 
int main() {
    // create a linked list
    printf("creating linked list\n");
    LINKED_LIST list = Create_List();
   
    // add some data (hardcoded for testing)
    printf("hardcoding some data\n");
    NODE *first  = malloc(sizeof(NODE)); Verify_Malloc(first);
    NODE *second = malloc(sizeof(NODE)); Verify_Malloc(second);
    first->data  = 1;
    second->data = 2;
    list.head = first;
    first->next = second;
    second->next = NULL;

    // print the list
    printf("Testing Print_List\n");
    Print_List(stdout, list);

    // write a better test for Size
    printf("Testing Size\n");
    printf("size = %d\n",Size(list));

    // write a better test for Push_Front
    printf("Testing Push_Front\n");
    Push_Front(&list, 0);
    Print_List(stdout, list);
    
    // write a better test for Push_Back
    printf("Testing Push_Back\n");
    Push_Back(&list, 3);
    Print_List(stdout, list);

    // write a better test for Pop_Front
    printf("Testing Pop_Front\n");
    {
        int x; 
        int not_empty = Pop_Front(&list, &x);
        if (not_empty) {
            printf("Element popped was %d\n",x);
            Print_List(stdout,list);
            printf("size = %d\n",Size(list));
        }
        else 
            printf("List was empty\n");
    }

    // write a better test for Pop_Back
    printf("Testing Pop_Back\n");
    {
        int x; 
        int not_empty = Pop_Back(&list, &x);
        if (not_empty) {
            printf("Element popped was %d\n",x);
            Print_List(stdout,list);
            printf("size = %d\n",Size(list));
        }
        else 
            printf("List was empty\n");
    }

    // write a beter test for Count_If
    Push_Front(&list, 5);
    Push_Front(&list, 5);
    Print_List(stdout, list);
    printf("5 count = %d\n",Count_If(list, 5));
    
    // write a test for Delete 
    printf("Testing Delete\n");
    Print_List(stdout, list);
    Delete(&list, 1); 
    Print_List(stdout, list);

    // write a better test for Is_Empty
    printf("Testing Is_Empty\n");
    if (Is_Empty(list)) printf("List is Empty\n"); else printf("List is not empty\n");
    
    // write a better test for Clear
    Clear(&list);
    if (Is_Empty(list)) printf("List is Empty\n"); else printf("List is not empty\n");

    // write a better test for Remove_Duplicates
    Push_Back(&list, 1);
    Push_Back(&list, 1);
    Push_Back(&list, 1);
    Push_Back(&list, 2);
    Push_Back(&list, 2);
    Push_Back(&list, 3);
    Push_Back(&list, 3);
    Push_Back(&list, 3);
    Remove_Duplicates(&list);
    Print_List(stdout, list);
    return 0;
}
