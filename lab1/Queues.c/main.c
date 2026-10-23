#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int customerNumber;
    struct Node* next;
} Node;

typedef struct Queue {
    Node* front;
    Node* rear;
} Queue;

void initQueue(Queue* q) {
    q->front = NULL;
    q->rear = NULL;
}

int isEmpty(Queue q) {
    return q.front == NULL;
}

void enqueue(Queue* q, int number) {
    Node* newNode = malloc(sizeof(Node));

    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    newNode->customerNumber = number;
    newNode->next = NULL;

    if (isEmpty(*q)) {
        q->front = newNode;
        q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }

    printf("Customer %d arrived and got a token.\n", number);
}

int dequeue(Queue* q) {
    if (isEmpty(*q)) {
        printf("Queue is empty.\n");
        return -1;
    }

    Node* temp = q->front;
    int number = temp->customerNumber;

    q->front = q->front->next;

    if (q->front == NULL) {
        q->rear = NULL;
    }

    free(temp);
    return number;
}

int peek(Queue q) {
    if (isEmpty(q)) {
        printf("Queue is empty.\n");
        return -1;
    }

    return q.front->customerNumber;
}

void displayQueue(Queue q) {
    Node* current = q.front;

    if (current == NULL) {
        printf("Queue is empty.\n");
        return;
    }

    printf("Customers in queue: ");

    while (current != NULL) {
        printf("%d ", current->customerNumber);
        current = current->next;
    }

    printf("\n");
}

void freeQueue(Queue* q) {
    while (!isEmpty(*q)) {
        dequeue(q);
    }
}

int main() {
    Queue q;
    initQueue(&q);

    int choice, number, customer;

    do {
        printf("\n--- Bank Queue Menu ---\n");
        printf("1. Add customer (Enqueue)\n");
        printf("2. Serve customer (Dequeue)\n");
        printf("3. Show next customer (Peek)\n");
        printf("4. Display queue\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            freeQueue(&q);
            return 1;
        }

        switch (choice) {
            case 1:
                printf("Enter customer number: ");
                if (scanf("%d", &number) != 1) {
                    printf("Invalid input.\n");
                    freeQueue(&q);
                    return 1;
                }
                enqueue(&q, number);
                break;

            case 2:
                customer = dequeue(&q);
                if (customer != -1) {
                    printf("Customer %d is being served.\n", customer);
                }
                break;

            case 3:
                customer = peek(q);
                if (customer != -1) {
                    printf("Next customer: %d\n", customer);
                }
                break;

            case 4:
                displayQueue(q);
                break;

            case 5:
                printf("Exiting program.\n");
                break;

            default:
                printf("Invalid choice.\n");
        }

    } while (choice != 5);

    freeQueue(&q);
    return 0;
}
