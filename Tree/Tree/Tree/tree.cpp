#include"Tree.h"
#include<iostream>
using std::cout;
using std::cin;
using std::endl;
bool Add(Tree& T,int num)
{
	if (!T)		//����
	{
		Node* node = (Node*)malloc(sizeof(Node));
		if (!node)
			return false;

		node->left = node->right = nullptr;
		node->data = num;
		T = node;

		return true;
	}

	if (num < T->data)		//���С�ڽڵ㣬����������
		 return Add(T->left, num);
	else			
		 return Add(T->right, num);		//��������


	
}
Node* Delete(Tree &T, int num)
{
	if (!T)		//�սڵ㣬��ʾû�ҵ�
		return nullptr;
	else
	{
		if (num < T->data)
			T->left = Delete(T->left, num);
		else if (num > T->data)
			T->right = Delete(T->right, num);

		if (num == T->data)
		{
			if ((T->left) && (T->right))	//����������ӽڵ�
			{
				Node* temp = FindMin(T->right);
				T->data = temp->data;
				T->right = Delete(T->right, temp->data);
			}
			else			//һ������û���ӽڵ�ʱ
			{
				Node* temp = T;

				if ((T->left) == nullptr)
					T = T->right;
				else if ((T->right) == nullptr)
					T = T->left;
				free(temp);
			}
		}
	}

	return T;
}
	
Node* Seek(Tree T, int num)
{
	if (T)
	{
		if (num == T->data)
			return T;
		else if (num > T->data)
			return Seek(T->right, num);
		else
			return Seek(T->left, num);
	}
	return nullptr;
}
Node* FindMin(Tree T)
{
	if (!T)
		return nullptr;
	else 
	{
		if ((T->left)==nullptr)
			return T;
		else
			return FindMin(T->left);
	}
}

Node* FindMax(Tree T)
{
	if (!T)
		return nullptr;
	else 
	{
		if ((T->right)==nullptr)
			return T;
		else
			return FindMax(T->right);
	}
}

bool Destroy(Tree T)
{
	if (T)
	{
		Destroy(T->left);
		Destroy(T->right);
		free(T);
		return true;
	}

	return false;
}
void Preorder(Tree T)
{
	if (T)
	{
		cout << T->data << "    ";
		Preorder(T->left);
		Preorder(T->right);
	}
}

void LevelOrder(Tree T)
{
	Queue Q;
	Node* p;

	Push(&Q, T);
	while (!IsEmpty(Q))
	{
		Pop(&Q, &p);
		cout << p->data << "    ";;

		if (p->left)
			Push(&Q, p->left);
		if (p->right)
			Push(&Q, p->right);
	}
}




//����ʵ��
bool IsEmpty(Queue q)	//ͨ���ж�rear��front�Ƿ�������жϿ�
{
	return q.rear == q.front;
}

bool IsFull(Queue q)	//ͨ���ж϶�βָ��ѭ������1ʱ���ڶ������ж���
{
	return (q.rear + 1) % MAXSIZE == q.front;
}

bool Push(Queue* q, Tree num)	//����һ����λ�ô�Ŷ�ͷָ��,��ʱ�������Ŀ��MAXSIZE-1
{
	if (!IsFull(*q))
	{
		q->rear = (q->rear + 1) % MAXSIZE;
		q->data[q->rear] = num;

		return true;
	}
	return false;
}

bool Pop(Queue* q, Tree* x)
{
	if (!IsEmpty(*q))
	{
		q->front = (q->front + 1) % MAXSIZE;
		*x = q->data[q->front];
		return true;
	}

	return false;
}