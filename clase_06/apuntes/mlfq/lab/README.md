# Implementing MLFQ Scheduling

**Objective**: In this lab, our goal is to implement the MLFQ scheduling algorithm with at least 3 queues, each having a different time quantum. Processes should be moved between queues based on their behavior and estimation of CPU duration.

The **Multi-Level Feedback Queue (MLFQ)** scheduling algorithm is a complex CPU scheduling algorithm designed to optimize turnaround time, response time, and CPU utilization. It utilizes multiple queues with different priority levels, adjusting the priority of processes based on their behavior and requirements.

## How MLFQ Works:

1. **Multiple Queues**: MLFQ involves multiple queues with different priority levels. A higher-priority queue has a shorter time quantum, and a lower-priority queue has a longer time quantum.
2. **Adjusting Priorities**: Processes start in the highest-priority queue. If a process uses up its time quantum without completing, it is moved to a lower-priority queue. If a process yields the CPU before its time quantum is up, it stays in the same queue.
3. **Boosting**: To prevent starvation, there is a mechanism to periodically boost the priority of processes in lower-priority queues.

## Rules of MLFQ

1. If **Priority(A) > Priority(B)**, A runs (B doesn’t).
2. If **Priority(A) = Priority(B)**, A & B run in round robin fashion using the time quantum of the given queue.
3. When a job enters the system, it is placed at the **highest priority** (the topmost queue).
4. Once a job uses up its time allotment at a given level (regardless of how many times it has been given CPU time), **its priority is reduced** (i.e., it moves down one queue).
5. After some time period, $S$, move all the jobs in the system to the topmost queue.

## Implementing MLFQ Scheduling in C

### Step 1: Include Necessary Libraries

Before we start implementing the MLFQ algorithm, we need to set up our programming environment with any necessary libraries.

```c
#include <stdio.h>
#include <stdlib.h>
```

### Step 2: Define the Process and Queue Structures

We need to define two structures: `Process` and `Queue`.
* **`Process`**: Represents a process with attributes like `id`, `duration`, `remaining_time`, `waiting_time`, and `turnaround_time`.
* **`Queue`**: Represents a queue that holds processes. It has attributes like `processes` (an array of pointers to `Process`), `front`, `rear`, and `time_quantum`.

```c
typedef struct {
    int id;
    int duration;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
} Process;

typedef struct {
    Process *processes[100];
    int front, rear;
    int time_quantum;
} Queue;
```

### Step 3: Initialize the Queue

We need a function to initialize our queue. This function sets the front and rear pointers to -1 (indicating an empty queue) and sets the time quantum for the queue.


```c
void initializeQueue(Queue *q, int time_quantum) {
    q->front = q->rear = -1;
    q->time_quantum = time_quantum;
}
```

### Step 4: Implement Queue Operations

We also need functions to add (`enqueue`) and remove (`dequeue`) processes from the queue.
* **`enqueue`**: Adds a process to the rear of the queue.
* **`dequeue`**: Removes a process from the front of the queue and returns it.

```c
void enqueue(Queue *q, Process *p) {
    if(q->rear == 99) {
        printf("Queue is full!\n");
        return;
    }
    q->processes[++q->rear] = p;
    if(q->front == -1) {
        q->front = 0;
    }
    printf("Process %d enqueued in queue with time quantum %d\n", p->id, q->time_quantum);
}

Process* dequeue(Queue *q) {
    if(q->front == -1) {
        return NULL;
    }
    Process *p = q->processes[q->front];
    if(q->front == q->rear) {
        q->front = q->rear = -1;
    } else {
        q->front++;
    }
    printf("Process %d dequeued from queue with time quantum %d\n", p->id, q->time_quantum);
    return p;
}
```

### Step 5: Implement the MLFQ Scheduling Logic

This is the core of the MLFQ scheduling algorithm. It dequeues processes from the highest priority queue and gives them CPU time according to their queue’s time quantum. If a process doesn’t finish within its time quantum, it is moved to a lower priority queue.

**In this implementation**:
* We start by trying to dequeue a process from the high priority queue.
* If a process is found, we check if it can finish within the high priority queue’s time quantum.
  * If it can finish, we update the total time, waiting time, turnaround time, and set the remaining time to 0.
  * If it can’t finish, we reduce its remaining time by the high priority queue’s time quantum, update the total time, and enqueue it to the medium priority queue.
* If no process is found in the high priority queue, we move on to the medium priority queue and repeat the same logic, moving processes to the low priority queue if they can’t finish.
* If no process is found in the medium priority queue, we move on to the low priority queue.
  * In the low priority queue, if a process can’t finish within the time quantum, it is given another round in the low priority queue.
* The loop continues until all queues are empty.

```c
void mlfq_scheduling(Queue *high_priority_q, Queue *medium_priority_q, Queue *low_priority_q, int n) {
    int total_time = 0;
    while(1) {
        Process *p = dequeue(high_priority_q);
        if(p != NULL) {
            printf("Process %d is running in high priority queue\n", p->id);
            if(p->remaining_time <= high_priority_q->time_quantum) {
                total_time += p->remaining_time;
                p->remaining_time = 0;
                p->waiting_time = total_time - p->duration;
                p->turnaround_time = total_time;
                printf("Process %d finished execution\n", p->id);
            } else {
                p->remaining_time -= high_priority_q->time_quantum;
                total_time += high_priority_q->time_quantum;
                enqueue(medium_priority_q, p);
            }
        } else {
            p = dequeue(medium_priority_q);
            if(p != NULL) {
                printf("Process %d is running in medium priority queue\n", p->id);
                if(p->remaining_time <= medium_priority_q->time_quantum) {
                    total_time += p->remaining_time;
                    p->remaining_time = 0;
                    p->waiting_time = total_time - p->duration;
                    p->turnaround_time = total_time;
                    printf("Process %d finished execution\n", p->id);
                } else {
                    p->remaining_time -= medium_priority_q->time_quantum;
                    total_time += medium_priority_q->time_quantum;
                    enqueue(low_priority_q, p);
                }
            } else {
                p = dequeue(low_priority_q);
                if(p != NULL) {
                    printf("Process %d is running in low priority queue\n", p->id);
                    if(p->remaining_time <= low_priority_q->time_quantum) {
                        total_time += p->remaining_time;
                        p->remaining_time = 0;
                        p->waiting_time = total_time - p->duration;
                        p->turnaround_time = total_time;
                        printf("Process %d finished execution\n", p->id);
                    } else {
                        p->remaining_time -= low_priority_q->time_quantum;
                        total_time += low_priority_q->time_quantum;
                        enqueue(low_priority_q, p);
                    }
                } else {
                    break;
                }
            }
        }
    }
}
```

This implementation provides a detailed view of how processes move between different priority queues in the MLFQ scheduling algorithm, and how their waiting time and turnaround time are calculated.

### Step 6: Implement the main() Function

The `main()` function serves as the entry point of the program, where the execution begins. In the context of the MLFQ scheduling algorithm, the `main()` function is responsible for initializing the queues, taking user input for the processes, invoking the scheduling function, and displaying the results. Let’s break down each part of the `main()` function.

**Step 6.1: Initialize the Queues**

Here, we initialize three queues for high, medium, and low priority levels, each with their respective time quantum. The time quantum determines how much CPU time a process in that queue receives before it is either moved to a lower priority queue or finishes execution.

**Step 6.2: Take User Input for Number of Processes**

We ask the user to input the number of processes that will be scheduled.

**Step 6.3: Allocate Memory for Processes and Take Their Input**

We allocate memory to store the process information and take user input for the duration of each process. All processes are initially enqueued to the high priority queue.

**Step 6.4: Invoke the MLFQ Scheduling Function**

We call the `mlfq_scheduling()` function to perform the scheduling based on the MLFQ algorithm.

**Step 6.5: Display the Results**

After the scheduling is complete, we display the results, showing the process ID, duration, waiting time, and turnaround time for each process.

**Step 6.6: Free the Allocated Memory**

Finally, we free the memory allocated for storing the process information.


```c
int main() {
    // Step 6.1: Initialize the Queues
    Queue high_priority_q, medium_priority_q, low_priority_q;
    initializeQueue(&high_priority_q, 2);  // High priority queue with time quantum of 2
    initializeQueue(&medium_priority_q, 4); // Medium priority queue with time quantum of 4
    initializeQueue(&low_priority_q, 8);    // Low priority queue with time quantum of 8

    // Step 6.2: Take User Input for Number of Processes
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Step 6.3: Allocate Memory for Processes and Take Their Input
    Process *processes = (Process *)malloc(n * sizeof(Process));
    for(int i = 0; i < n; i++) {
        printf("Enter duration for process %d: ", i+1);
        scanf("%d", &processes[i].duration);
        processes[i].id = i+1;
        processes[i].remaining_time = processes[i].duration;
        processes[i].waiting_time = 0;
        processes[i].turnaround_time = 0;
        enqueue(&high_priority_q, &processes[i]);  // Enqueue all processes to high priority queue initially
    }

    // Step 6.4: Invoke the MLFQ Scheduling Function
    mlfq_scheduling(&high_priority_q, &medium_priority_q, &low_priority_q, n);

    // Step 6.5: Display the Results
    printf("Process\tDuration\tWaiting Time\tTurnaround Time\n");
    for(int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\n", processes[i].id, processes[i].duration, processes[i].waiting_time, processes[i].turnaround_time);
    }

    // Step 6.6: Free the Allocated Memory
    free(processes);
    return 0;
}
```

### Task

Use the buttons below to compile and run your simple FCFS Scheduler.

**Compile**

```
gcc mlfq_lab.c -o mlfq_lab
```

```
./mlfq_lab
```

### Activity

Try out different numbers of processes and durations. Examine the how the waiting and turnaround times are affected.

### Solution

A solution to this problem can be found below:

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    int duration;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
} Process;

typedef struct {
    Process *processes[100];
    int front, rear;
    int time_quantum;
} Queue;

void initializeQueue(Queue *q, int time_quantum) {
    q->front = q->rear = -1;
    q->time_quantum = time_quantum;
}

void enqueue(Queue *q, Process *p) {
    if(q->rear == 99) {
        printf("Queue is full!\n");
        return;
    }
    q->processes[++q->rear] = p;
    if(q->front == -1) {
        q->front = 0;
    }
    printf("Process %d enqueued in queue with time quantum %d\n", p->id, q->time_quantum);
}

Process* dequeue(Queue *q) {
    if(q->front == -1) {
        return NULL;
    }
    Process *p = q->processes[q->front];
    if(q->front == q->rear) {
        q->front = q->rear = -1;
    } else {
        q->front++;
    }
    printf("Process %d dequeued from queue with time quantum %d\n", p->id, q->time_quantum);
    return p;
}

void mlfq_scheduling(Queue *high_priority_q, Queue *medium_priority_q, Queue *low_priority_q, int n) {
    int total_time = 0;
    while(1) {
        Process *p = dequeue(high_priority_q);
        if(p != NULL) {
            printf("Process %d is running in high priority queue\n", p->id);
            if(p->remaining_time <= high_priority_q->time_quantum) {
                total_time += p->remaining_time;
                p->remaining_time = 0;
                p->waiting_time = total_time - p->duration;
                p->turnaround_time = total_time;
                printf("Process %d finished execution\n", p->id);
            } else {
                p->remaining_time -= high_priority_q->time_quantum;
                total_time += high_priority_q->time_quantum;
                enqueue(medium_priority_q, p);
            }
        } else {
            p = dequeue(medium_priority_q);
            if(p != NULL) {
                printf("Process %d is running in medium priority queue\n", p->id);
                if(p->remaining_time <= medium_priority_q->time_quantum) {
                    total_time += p->remaining_time;
                    p->remaining_time = 0;
                    p->waiting_time = total_time - p->duration;
                    p->turnaround_time = total_time;
                    printf("Process %d finished execution\n", p->id);
                } else {
                    p->remaining_time -= medium_priority_q->time_quantum;
                    total_time += medium_priority_q->time_quantum;
                    enqueue(low_priority_q, p);
                }
            } else {
                p = dequeue(low_priority_q);
                if(p != NULL) {
                    printf("Process %d is running in low priority queue\n", p->id);
                    if(p->remaining_time <= low_priority_q->time_quantum) {
                        total_time += p->remaining_time;
                        p->remaining_time = 0;
                        p->waiting_time = total_time - p->duration;
                        p->turnaround_time = total_time;
                        printf("Process %d finished execution\n", p->id);
                    } else {
                        p->remaining_time -= low_priority_q->time_quantum;
                        total_time += low_priority_q->time_quantum;
                        enqueue(low_priority_q, p);
                    }
                } else {
                    break;
                }
            }
        }
    }
}

int main() {
    Queue high_priority_q, medium_priority_q, low_priority_q;
    initializeQueue(&high_priority_q, 2);
    initializeQueue(&medium_priority_q, 4);
    initializeQueue(&low_priority_q, 8);

    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process *processes = (Process *)malloc(n * sizeof(Process));

    for(int i = 0; i < n; i++) {
        printf("Enter duration for process %d: ", i+1);
        scanf("%d", &processes[i].duration);
        processes[i].id = i+1;
        processes[i].remaining_time = processes[i].duration;
        processes[i].waiting_time = 0;
        processes[i].turnaround_time = 0;
        enqueue(&high_priority_q, &processes[i]);
    }

    mlfq_scheduling(&high_priority_q, &medium_priority_q, &low_priority_q, n);

    printf("Process\tDuration\tWaiting Time\tTurnaround Time\n");
    for(int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\n", processes[i].id, processes[i].duration, processes[i].waiting_time, processes[i].turnaround_time);
    }

    free(processes);
    return 0;
}
```