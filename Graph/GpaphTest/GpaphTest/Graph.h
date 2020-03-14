#pragma once
typedef struct node {	
	int data;				//边的邻接点编号
	int weight;				//边的权重
	struct node* next;		//指向下一节点	
}Node;
typedef struct {
	Node list[5] = { 0 };
	int amount = 5;			//节点总数
}Graph;

void GreatGraph(Graph* g, int ar[5][5]);
void DFS(Graph* g, int visit[], int d_node);
void BFS(Graph* G, int visit[], int d_node);
void DestroyGraph(Graph* g);

//环形队列声明
//保留一个空位置存放队头指针,此时最大存放数目是MAXSIZE-1
#define MAXSIZE 6
typedef struct queue {
	int data[MAXSIZE] = { 0 };
	int front = 0, rear = 0;
}Queue;

//通过判断rear和front是否相等来判断空
bool IsEmpty(Queue* q);		

//通过判断队尾指针循环递增1时等于队首来判读满
bool IsFull(Queue* q);		

//保留一个空位置存放队头指针,此时最大存放数目是MAXSIZE-1
bool Push(Queue* q, int num);

bool Del(Queue* q, int* x);