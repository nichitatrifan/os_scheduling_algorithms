#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

struct Process
{
	int ID;
	int priority;
	int remainingTime;

	int arrivalTime;
	int burstTime;
	int completionTime;
	int turnAroundTime; // completionTime - arrivalTime
	int waitingTime;	// turnAroundTime - burstTime
	int responseTime;	// first time process got to the CPU - arrivalTime

	int cpuArrival;
};
typedef struct Process Process;

struct Node
{
	Process* process;
	struct Node* next;
};
typedef struct Node Node;

struct Queue
{
	int count;
	Node* head;
	Node* tail;
};
typedef struct Queue Queue;

int rand_num(int upper, int lower);
void print_processes(Process* arr, int numProcess);
void use_FCFS(Process* arr, int numProcess);
void use_SJF(Process* arr, int numProcess);
void use_SRTF(Process* arr, int numProcess);
void use_RR(Process* arr, int numProcess);
void use_Priority(Process* arr, int numProcess);

int main()
{
	// Set the seed 
	srand(time(0));

	int upper = 30;
	int lower = 1;
	int n = 0;
	int testAns = 0;
	int stop = 0;
	bool testData = false;


	printf("Enter the number of processes: ");
	scanf_s("%d", &n);

	while (true)
	{
		printf("Use sample or random data?\n0 - sample\n1 - random\n: ");
		scanf_s("%d", &testAns);

		Process* arr = (Process*)malloc(n * sizeof(Process));
		
		// Initialize Processes
		
		if (testAns == 0)
		{
			for (size_t i = 0; i < n; i++)
			{
				arr[i].ID = i;
				arr[i].priority = i;
				arr[i].arrivalTime = i;
				arr[i].burstTime = i + 5;
				arr[i].remainingTime = arr[i].burstTime;
				arr[i].completionTime = 0;
				arr[i].turnAroundTime = 0;
				arr[i].waitingTime = 0;
				arr[i].responseTime = 0;
				arr[i].cpuArrival = -1;
			}
		}
		else
		{
			for (size_t i = 0; i < n; i++)
			{
				arr[i].ID = i;
				arr[i].priority = rand_num(lower, upper);
				arr[i].arrivalTime = rand_num(0, upper);
				arr[i].burstTime = rand_num(lower, upper);
				arr[i].remainingTime = arr[i].burstTime;
				arr[i].completionTime = 0;
				arr[i].turnAroundTime = 0;
				arr[i].waitingTime = 0;
				arr[i].responseTime = 0;
				arr[i].cpuArrival = -1;
			}
		}

		printf("INPUT DATA:\n");

		for (size_t i = 0; i < n; i++)
		{
			printf("ID: %d \n", arr[i].ID);
			printf("Priority: %d \n", arr[i].priority);
			printf("ArrivalTime: %d \n", arr[i].arrivalTime);
			printf("BurstTime: %d \n", arr[i].burstTime);
			printf("CompletionTime: %d \n", arr[i].completionTime);
			printf("TurnAroundTime: %d \n", arr[i].turnAroundTime);
			printf("WaitingTime: %d \n", arr[i].waitingTime);
			printf("ResponseTime: %d\n", arr[i].responseTime);
			printf("CPU arrival: %d\n\n", arr[i].cpuArrival);
		}

		size_t choice = 0;

		printf("0 - FCFS\n1 - SJF\n2 - SRTF\n3 - RR\n4 - Priority\n");

		printf("Enter the choice: ");
		scanf_s("%d", &choice);
		printf("\n");

		printf("\n------GRANTT CHART------\n\n");

		switch (choice)
		{
		case 0:
			use_FCFS(arr, n);
			printf("\n");
			break;
		case 1:
			use_SJF(arr, n);
			printf("\n");
			break;

		case 2:
			use_SRTF(arr, n);
			printf("\n");
			break;

		case 3:
			use_RR(arr, n);
			printf("\n");
			break;

		case 4:
			use_Priority(arr, n);
			printf("\n");
			break;

		default:
			use_FCFS(arr, n);
			printf("\n");
			break;
		}

		print_processes(arr, n);

		printf("Want to test more?\n0 - No\n:");
		scanf_s("%d", &stop);
		if (stop == 0)
		{
			break;
		}
	}
	return 0;
}

void print_processes(Process* arr, int numProcess)
{	

	// TABLE
	printf("\n------TABLE------\n\n");

	for (size_t i = 0; i < numProcess; i++)
	{
		printf("ID: %d \n", arr[i].ID);
		printf("Priority: %d \n", arr[i].priority);
		printf("ArrivalTime: %d \n", arr[i].arrivalTime);
		printf("BurstTime: %d \n", arr[i].burstTime);
		printf("CompletionTime: %d \n", arr[i].completionTime);

		arr[i].turnAroundTime = arr[i].completionTime - arr[i].arrivalTime;
		printf("TurnAroundTime: %d \n", arr[i].turnAroundTime);

		arr[i].waitingTime = arr[i].turnAroundTime - arr[i].burstTime;
		printf("WaitingTime: %d \n", arr[i].waitingTime);

		arr[i].responseTime = arr[i].cpuArrival - arr[i].arrivalTime;
		printf("ResponseTime: %d\n", arr[i].responseTime);

		printf("CPU Arrival Time: %d \n", arr[i].cpuArrival);

		printf("----\nremaining time: %d\n\n", arr[i].remainingTime);
	}

	int totalWT = 0;
	int totalTAT = 0;
	int totalRT = 0;
	int maxCT = 0;
	int minAT = arr[0].arrivalTime;

	// int throughput = 0;

	for (size_t i = 0; i < numProcess; i++)
	{
		totalWT += arr[i].waitingTime;
		totalTAT += arr[i].turnAroundTime;
		totalRT += arr[i].responseTime;

		if (arr[i].arrivalTime < minAT)
		{
			minAT = arr[i].arrivalTime;
		}

		if (arr[i].completionTime > maxCT)
		{
			maxCT = arr[i].completionTime;
		}


	}

	printf("Average Waiting Time: %f\n", (float)totalWT / numProcess);
	printf("Average Response Time: %f\n", (float)totalRT / numProcess);
	printf("Average Turn Around Time: %f\n", (float)totalTAT / numProcess);
	printf("Throughtput: %f\n", (float)numProcess/(maxCT - minAT));

}

int rand_num(int lower, int upper)
{
	return (rand() % (upper - lower + 1) + lower);
}

void add_node(Queue* queue, Process* process)
{
	Node* tmp = malloc(sizeof(Node));

	tmp->process = process;				// PROBLEM !
	tmp->next = NULL;

	if (queue->head == NULL)
	{
		queue->head = tmp;
		queue->tail = tmp;
	}
	else
	{
		queue->tail->next = tmp;
		queue->tail = tmp;
	}

	queue->count++;
}

Node* pop_queue(Queue* queue)
{
	Node* returnNode = queue->head;
	if (queue->head == queue->tail)
	{
		queue->head = queue->head->next;
		queue->tail = queue->tail->next;
	}
	else
	{
		queue->head = queue->head->next;
	}

	queue->count--;

	return returnNode;
}

void pop_queue_first(Process** arr, int used)
{
	for (size_t i = 0; i < used - 1; i++)
	{
		arr[i] = arr[i + 1];
	}
}

bool is_empty(Queue* queue)
{

	if (queue->head == NULL)
		return true;
	else
		return false;
}

void swap(Process* p1, Process* p2)
{
	Process tmp = { p1[0].ID, p1[0].priority, p1[0].remainingTime,
					p1[0].arrivalTime, p1[0].burstTime, p1[0].completionTime,
					p1[0].turnAroundTime, p1[0].waitingTime, p1[0].responseTime,
					p1[0].cpuArrival };

	p1[0].ID = p2[0].ID;
	p1[0].priority = p2[0].priority;
	p1[0].remainingTime = p2[0].remainingTime;
	p1[0].arrivalTime = p2[0].arrivalTime;
	p1[0].burstTime = p2[0].burstTime;
	p1[0].completionTime = p2[0].completionTime;
	p1[0].turnAroundTime = p2[0].turnAroundTime;
	p1[0].waitingTime = p2[0].waitingTime;
	p1[0].responseTime = p2[0].responseTime;
	p1[0].cpuArrival = p2[0].cpuArrival;

	p2[0].ID = tmp.ID;
	p2[0].priority = tmp.priority;
	p2[0].remainingTime = tmp.remainingTime;
	p2[0].arrivalTime = tmp.arrivalTime;
	p2[0].burstTime = tmp.burstTime;
	p2[0].completionTime = tmp.completionTime;
	p2[0].turnAroundTime = tmp.turnAroundTime;
	p2[0].waitingTime = tmp.waitingTime;
	p2[0].responseTime = tmp.responseTime;
	p2[0].cpuArrival = tmp.cpuArrival;
}

void rotate(Process** arr, int size)
{
	arr[size] = arr[0];

	for (size_t i = 0; i < size; i++)
	{
		arr[i] = arr[i + 1];
	}

}

void buble_sort_SJF(Process** arr, int size)
{
	if (size > 1)
	{
		for (size_t i = 0; i < size - 1; i++)
		{
			for (size_t j = 0; j < size - i - 1; j++)
			{
				if (arr[i][0].burstTime > arr[i + 1][0].burstTime)
				{
					swap(arr[i], arr[i + 1]);
				}
				else if (arr[i][0].burstTime == arr[i + 1][0].burstTime &&
					arr[i][0].arrivalTime > arr[i + 1][0].arrivalTime)
				{
					swap(arr[i], arr[i + 1]);
				}
			}
		}
	}
}

void buble_sort_SRTF(Process** arr, int size)
{
	if (size > 1)
	{
		for (size_t i = 0; i < size - 1; i++)
		{
			for (size_t j = 0; j < size - i - 1; j++)
			{
				if (arr[i][0].remainingTime > arr[i + 1][0].remainingTime)
				{
					swap(arr[i], arr[i + 1]);
				}
				else if (arr[i][0].burstTime == arr[i + 1][0].burstTime &&
					arr[i][0].arrivalTime > arr[i + 1][0].arrivalTime)
				{
					swap(arr[i], arr[i + 1]);
				}
			}
		}
	}
}

void buble_sort_Priority(Process** arr, int size)
{
	if (size > 1)
	{
		for (size_t i = 0; i < size - 1; i++)
		{
			for (size_t j = 0; j < size - i - 1; j++)
			{
				if (arr[i][0].priority > arr[i + 1][0].priority)
				{
					swap(arr[i], arr[i + 1]);
				}
				else if (arr[i][0].priority == arr[i + 1][0].priority &&
					arr[i][0].arrivalTime > arr[i + 1][0].arrivalTime)
				{
					swap(arr[i], arr[i + 1]);
				}
			}
		}
	}
}

void use_FCFS(Process* arr, int numProcess)
{

	Queue readyQueue = { 0,NULL,NULL };
	Node* runningNode = NULL;

	int time = 0;
	int processed = 0;
	bool printed = false;

	while (processed < numProcess)
	{
		// Add arrived processes in the readyQueue
		for (size_t i = 0; i < numProcess; i++)
		{
			if (time == arr[i].arrivalTime)
			{
				// printf("\nadded P%d to the ready queue\n", arr[i].ID);
				add_node(&readyQueue, &arr[i]);
			}
		}

		if (runningNode == NULL && !is_empty(&readyQueue))
		{
			runningNode = pop_queue(&readyQueue);
			runningNode->process->cpuArrival = time;
		}

		if (runningNode != NULL)
		{
			if (runningNode->process->remainingTime == 0)
			{
				runningNode->process->completionTime = time;
				runningNode = NULL;
				processed++;

			}
			else
			{
				printf("|%d P%d|-", time, runningNode->process->ID);
				printed = true;
				runningNode->process->remainingTime--;
				// printf("running: %d, remaining: %d\n", runningNode->process->ID, runningNode->process->remainingTime);
			}

		}

		if (runningNode == NULL && !is_empty(&readyQueue))
		{
			runningNode = pop_queue(&readyQueue);
			runningNode->process->cpuArrival = time;

			if (runningNode->process->remainingTime == 0)
			{
				runningNode->process->completionTime = time;
				runningNode = NULL;
				processed++;
			}
			else
			{
				printf("|%d P%d|-", time, runningNode->process->ID);
				printed = true;
				runningNode->process->remainingTime--;
				runningNode->process->cpuArrival = time;
				// printf("running: %d, remaining: %d\n", runningNode->process->ID, runningNode->process->remainingTime);
			}

		}

		if (!printed && processed < numProcess)
		{
			printf("|%d |-", time);
		}
		else
		{
			printed = false;
		}

		time++;
	}

}

void use_SJF(Process* arr, int numProcess)
{
	Process** readyQueue = (Process**)malloc(numProcess * sizeof(Process*));
	for (size_t i = 0; i < numProcess; i++)
	{
		readyQueue[i] = (Process*)malloc(sizeof(Process));
	}

	int used = 0;
	int processed = 0;
	int time = 0;
	bool completed = true;

	while (processed < numProcess)
	{
		// ADD PROCESSES TO THE QUEUE

		for (size_t i = 0; i < numProcess; i++)
		{
			if (arr[i].arrivalTime == time)
			{
				readyQueue[used] = &arr[i];
				used++;
			}
		}

		// SORT THE QUEUE
		if (completed && used > 0)
		{
			buble_sort_SJF(readyQueue, used);
		}

		if (used > 0 && readyQueue[0][0].remainingTime > 0)
		{
			if (readyQueue[0][0].cpuArrival < 0)
				readyQueue[0][0].cpuArrival = time;

			printf("|%d P%d|-", time, readyQueue[0][0].ID);
			readyQueue[0][0].remainingTime--;
			completed = false;
			time++;
		}
		else if (used > 0 && readyQueue[0][0].remainingTime == 0)
		{
			readyQueue[0][0].completionTime = time;
			pop_queue_first(readyQueue, used);
			completed = true;
			processed++;
			used--;
		}
		else
		{
			printf("|%d |-", time);
			time++;
		}


	}

}

void use_SRTF(Process* arr, int numProcess)
{
	Process** readyQueue = (Process**)malloc(numProcess * sizeof(Process*));
	for (size_t i = 0; i < numProcess; i++)
	{
		readyQueue[i] = (Process*)malloc(sizeof(Process));
	}

	int used = 0;
	int processed = 0;
	int time = 0;

	while (processed < numProcess)
	{
		// ADD PROCESSES TO THE QUEUE
		for (size_t i = 0; i < numProcess; i++)
		{
			if (arr[i].arrivalTime == time)
			{
				readyQueue[used] = &arr[i];
				used++;
			}
		}

		// SORT EVERY TIME UNIT TO ACHIEVE PREEMTIVE SCHEDULING 
		if (used > 0)
		{
			buble_sort_SRTF(readyQueue, used);
		}

		// EXECUTION LOGIC
		if (used > 0 && readyQueue[0][0].remainingTime > 0)
		{
			if (readyQueue[0][0].cpuArrival < 0)
				readyQueue[0][0].cpuArrival = time;

			printf("|%d P%d|-", time, readyQueue[0][0].ID);
			readyQueue[0][0].remainingTime--;
			time++;
		}
		else if (used > 0 && readyQueue[0][0].remainingTime == 0)
		{
			readyQueue[0][0].completionTime = time;
			pop_queue_first(readyQueue, used);
			processed++;
			used--;
		}
		else
		{	
			printf("|%d |-", time);
			time++;
		}
	}
}

void use_RR(Process* arr, int numProcess)
{
	Process** readyQueue = (Process**)malloc(numProcess * sizeof(Process*));
	// <= to have additional space for swaping
	for (size_t i = 0; i <= numProcess; i++)
	{
		readyQueue[i] = (Process*)malloc(sizeof(Process));
	}

	size_t used = 0;
	size_t count = 2;
	size_t processed = 0;
	size_t time = 0;
	
	bool completedTQ = false;
	

	while (processed < numProcess)
	{
		if (!completedTQ)
		{
			for (size_t i = 0; i < numProcess; i++)
			{
				if (arr[i].arrivalTime == time)
				{
					readyQueue[used] = &arr[i];
					used++;
				}
			}
		}

		if (completedTQ && used > 1)
		{
			rotate(readyQueue, used);
		}

		if (count > 0 && used > 0 && readyQueue[0][0].remainingTime > 0)
		{
			if (readyQueue[0][0].cpuArrival < 0)
				readyQueue[0][0].cpuArrival = time;
			printf("|%d P%d|-", time, readyQueue[0][0].ID);
			readyQueue[0][0].remainingTime--;
			completedTQ = false;
			time++;
			count--;
		}
		else if (count == 0 && used > 0 && readyQueue[0][0].remainingTime > 0)
		{

			completedTQ = true;
			count = 2;
		}
		else if (count >= 0 && used > 0 && readyQueue[0][0].remainingTime == 0)
		{
			if (readyQueue[0][0].cpuArrival < 0)
				readyQueue[0][0].cpuArrival = time;

			readyQueue[0][0].completionTime = time;

			for (size_t i = 0; i < used; i++) // -1
			{
				// change !!!!
				readyQueue[i] = readyQueue[i + 1];			// PROBLEM	
			}

			used--;
			processed++;
			completedTQ = true;
			count = 2;
		}
		else
		{	
			printf("|%d |-", time);
			time++;
			completedTQ = false;
		}

	}
}

void use_Priority(Process* arr, int numProcess)
{
	Process** readyQueue = (Process**)malloc(numProcess * sizeof(Process*));
	for (size_t i = 0; i < numProcess; i++)
	{
		readyQueue[i] = (Process*)malloc(sizeof(Process));
	}

	size_t used = 0;
	int processed = 0;
	int time = 0;

	while (processed < numProcess)
	{
		for (size_t i = 0; i < numProcess; i++)
		{
			if (arr[i].arrivalTime == time)
			{
				readyQueue[used] = &arr[i];
				used++;
			}
		}

		if (used > 1)
			buble_sort_Priority(readyQueue, used);

		if (used > 0)
		{	
			
			if (readyQueue[0][0].cpuArrival < 0)
				readyQueue[0][0].cpuArrival = time;

			if (readyQueue[0][0].remainingTime == 0)
			{
				readyQueue[0][0].completionTime = time;
				
				// DELETE THE FIRST ELEMENT
				pop_queue_first(readyQueue, used);
				used--;
				processed++;
			}
			else
			{	
				printf("|%d P%d|-", time, readyQueue[0][0].ID);
				readyQueue[0][0].remainingTime--;
				time++;
			}

		}
		else
		{	
			printf("|%d |-", time);
			time++;
		}
	}
}