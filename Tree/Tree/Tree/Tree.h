#pragma once
typedef struct node {
	int data;
	struct node* left;
	struct node* right;
}Node,* Tree;

bool Add(Tree &T,int num);
Node* Delete(Tree &T,int num);
Node* Seek(Tree T, int num);
Node* FindMin(Tree T);
Node* FindMax(Tree T);
bool Destroy(Tree T);
void Preorder(Tree T);
void LevelOrder(Tree T);



//队列定义
//保留一个空位置存放队头指针,此时最大存放数目是MAXSIZE-1
#define MAXSIZE 33
typedef struct queue {
	Tree data[MAXSIZE];
	int front = 0, rear = 0;
}Queue;

bool IsEmpty(Queue q);		//通过判断rear和front是否相等来判断空

bool IsFull(Queue q);		//通过判断队尾指针循环递增1时等于队首来判读满

bool Push(Queue* q, Tree num);//保留一个空位置存放队头指针,此时最大存放数目是MAXSIZE-1

bool Pop(Queue* q, Tree* x);