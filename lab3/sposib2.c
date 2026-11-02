#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int id;
    int burst_time;
} Process;

typedef struct Node {
    Process data;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    Node* tail;
} Queue;

void init_queue(Queue* q) {
    q->head = NULL;
    q->tail = NULL;
}

bool is_empty(Queue* q) {
    return q->head == NULL;
}

bool is_full(Queue* q) {
    return false;
}

void enqueue(Queue* q, Process p) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("[Error]: Failed to allocate memory for process %d\n", p.id);
        return;
    }
    new_node->data = p;
    new_node->next = NULL;

    if (is_empty(q)) {
        q->head = new_node;
        q->tail = new_node;
    } else {
        q->tail->next = new_node;
        q->tail = new_node;
    }
}

Process dequeue(Queue* q) {
    if (is_empty(q)) {
        printf("[Error]: Attempt to dequeue from an empty queue!\n");
        Process empty = { -1, 0 };
        return empty;
    }
    
    Node* temp = q->head;
    Process p = temp->data;
    
    q->head = q->head->next;
    if (q->head == NULL) {
        q->tail = NULL; 
    }
    
    free(temp); 
    return p;
}

Process peek_front(Queue* q) {
    if (is_empty(q)) {
        Process empty = { -1, 0 };
        return empty;
    }
    return q->head->data;
}

int main() {
    system("chcp 1251 > nul");

    Queue q;
    init_queue(&q);

    int n, quantum;
    printf("=== Round Robin Simulation (Linked List Queue) ===\n\n");
    printf("Enter the number of processes: ");
    if (scanf("%d", &n) != 1 || n <= 0) return 1;

    printf("Enter the time quantum: ");
    if (scanf("%d", &quantum) != 1 || quantum <= 0) return 1;

    for (int i = 0; i < n; i++) {
        Process p;
        p.id = i + 1;
        printf("Enter burst time for Process %d: ", p.id);
        if (scanf("%d", &p.burst_time) != 1 ||
    p.burst_time <= 0) {
    printf("Error: Invalid burst time!\n");
    return 1;
}
        enqueue(&q, p);
    }

    printf("\nOrder of process completion: ");
    
    while (!is_empty(&q)) {
        Process current = dequeue(&q);

        if (current.burst_time <= quantum) {
            printf("P%d ", current.id);
        } else {
            current.burst_time -= quantum;
            enqueue(&q, current);
        }
    }
    printf("\n\nSimulation completed successfully.\n");

    printf("\n--- Demonstration of dequeue on an empty queue ---\n");
    dequeue(&q);
    printf("-----------------------------------------------------\n");

    return 0;
}
