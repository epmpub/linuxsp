#include <stdio.h>
#include <stdlib.h>



struct List {
     int Node;
     struct List *Next;
};


void insertAtBegin(struct List** head,int value)
{
    struct List* header = (struct List*)malloc(sizeof(struct List));
    header->Node = value;
    header->Next = NULL;

    head = &header;

}

void printList(struct List* head) {
    struct List* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->Node);
        temp = temp->Next;
    }
    printf("NULL\n");
}

#include <stdio.h>
printf("Hello %d", 10);


int main() {
    struct List* head = NULL;
    insertAtBegin(&head,10);
    insertAtBegin(&head,20);
    insertAtBegin(&head,30);

    printList(head);

    
    return 0;
}
