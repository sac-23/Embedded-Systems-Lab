#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Linked List Node structure
struct node {
    int data;
    struct node* next;
};

// Function to create a new node with given value
struct node* xCreateNode(int val) {

    struct node* newNode = (struct node*)malloc(sizeof(struct node)); // Allocate heap memory for new node
    newNode->data = val; 
    newNode->next = NULL;
    return newNode;
    
}

// Function to insert a new node at the beginning of the linked list
void vInsertAtBeginning(struct node** head, int val) {

    struct node* newNode = xCreateNode(val); 
    newNode->next = *head; 
    *head = newNode;

}

// Function to insert a new node at the end of the linked list
void vInsertAtEnd(struct node** head, int val) {

    struct node* newNode = xCreateNode(val);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    struct node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;

}

// Function to insert a new node at a specific position in the linked list
void vInsertAtPosition(struct node** head, int val, int pos) {

    struct node* newNode = xCreateNode(val);
    if (pos == 1) {
        newNode->next = *head;
        *head = newNode;
        return;
    }
    struct node* temp = *head;
    for (int i = 1; i < pos - 1; i++) {
        if (temp == NULL) {
            free(newNode); // free the memory allocated for the new node
            printf("Position %d is out of bounds\n", pos);
            return;
        }
        temp = temp->next;
    }
    newNode->next = temp->next;
    temp->next = newNode;

}

// Function to delete a node at the beginning of the linked list
void vDeleteAtBeginning(struct node** head) {

    if (*head == NULL) {
        return;
    }
    struct node* temp = *head;
    *head = (*head)->next;
    free(temp); // free the memory allocated for the deleted node

}

// Function to delete a node at the end of the linked list
void vDeleteAtEnd(struct node** head) {

    if (*head == NULL) {
        return;
    }
    if ((*head)->next == NULL) {
        free(*head);
        *head = NULL;
        return;
    }
    struct node* curr= *head; //curr used to traverse the list
    struct node* prev = NULL; // prev used to keep track of the previous node
    while (curr->next != NULL) {
        prev = curr; // prev points to curr 
        curr = curr->next; // curr moves to next node
    }
    free(curr); // free the last node
    prev->next = NULL;

}

void vDeleteByValue(struct node** head, int val) {

    if (*head == NULL) {
        return;
    }
    if ((*head)->data == val) {
        struct node* temp = *head;
        *head = (*head)->next;
        free(temp);
        return;
    }
    struct node* curr = *head; // curr used to traverse the list
    struct node* prev = NULL; // prev used to keep track of the previous node
    while (curr != NULL ) {
        if (curr->data == val) {
            prev->next = curr->next; // bypass the node to be deleted
            free(curr); // free the memory allocated for the deleted node
            return;
        }
        prev = curr; // prev points to curr
        curr = curr->next; // curr moves to next node
    }

    printf("Value %d not found in the List \n", val);
}

void vReverseList(struct node** head) {

    struct node* curr = *head; // curr used to traverse the list
    struct node* prev = NULL; // prev used to keep track of the previous node
    struct node* next = NULL; // next used to keep track of the next node
    while (curr != NULL) {
        next = curr->next; // store next node
        curr->next = prev; // reverse the link
        prev = curr; // move prev to curr
        curr = next; // move curr to next node
    }
    *head = prev; // update head to point to the new first node
}

void vDestroyList(struct node** head) {

    struct node* temp = *head;
    while (temp != NULL) {
        struct node* next = temp->next; // store next node
        free(temp); // free the current node
        temp = next; // move to next node
    }
    *head = NULL; // set head to NULL after destroying the list

}

void vDisplayList(struct node* head) {

    struct node* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data); 
        temp = temp->next;
    }
    printf("NULL\n");

}

int main(void)
{
    struct node *head = NULL;

    vInsertAtEnd(&head, 10);
    vInsertAtEnd(&head, 20);
    vInsertAtEnd(&head, 30);

    vDisplayList(head);

    vDeleteByValue(&head, 20);

    vDisplayList(head);

    vReverseList(&head);

    vDisplayList(head);

    vDestroyList(&head);

    return 0;
}