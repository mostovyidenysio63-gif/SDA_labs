#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 50 

typedef struct {
    int id;         
    int burst_time; 
} Process;

typedef struct {
    Process data[MAX_SIZE];
    int head;
    int tail;
    int size;
} Queue;

void init_queue(Queue* q) {
    q->head = 0;
    q->tail = 0;
    q->size = 0;
}

bool is_empty(Queue* q) {
    return q->size == 0;
}

bool is_full(Queue* q) {
    return q->size == MAX_SIZE;
}

void enqueue(Queue* q, Process p) {
    if (is_full(q)) {
        printf("[Overflow Error]: Queue is full! Cannot add process %d\n", p.id);
        return;
    }
    q->data[q->tail] = p;
    q->tail = (q->tail + 1) % MAX_SIZE; 
    q->size++;
}

Process dequeue(Queue* q) {
    if (is_empty(q)) {
        printf("[Error]: Attempt to dequeue from an empty queue!\n");
        Process empty = { -1, 0 };
        return empty;
    }
    Process p = q->data[q->head];
    q->head = (q->head + 1) % MAX_SIZE; 
    q->size--;
    return p;
}

Process peek_front(Queue* q) {
    if (is_empty(q)) {
        Process empty = { -1, 0 };
        return empty;
    }
    return q->data[q->head];
}

int main() {
    system("chcp 1251 > nul");

    Queue q;
    init_queue(&q);

    int n, quantum;
    printf("=== Round Robin Simulation (Array-based Queue) ===\n\n");
    printf("Enter the number of processes: ");
    if (scanf("%d", &n) != 1 || n <= 0) return 1;

    if (n > MAX_SIZE) {
        printf("Error: Maximum number of processes is %d\n", MAX_SIZE);
        return 1;
}

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

    printf("\n--- Demonstration of Overflow Check ---\n");
    Process fake_process = { 999, 10 };
    int saved_size = q.size;
    while (!is_full(&q)) {
        enqueue(&q, fake_process);
    }
    enqueue(&q, fake_process);
    
    while (q.size > saved_size) {
        q.tail = (q.tail - 1 + MAX_SIZE) % MAX_SIZE;
        q.size--;
    }
    printf("----------------------------------------------\n\n");

    printf("Order of process completion: ");
    
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