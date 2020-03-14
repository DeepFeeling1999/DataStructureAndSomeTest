#pragma once
#include<string>
using std::string;
typedef struct list {
	int number;
	string name;
	int sex;  //0 ÄÐ£¬ 1Å®
	string phone_number;
	string address;

	struct list* next;
}List;

bool Initialization(List*& L, int size);
bool Add(List* &L);
List* Seek(List* L);
bool Delet(List*& L,int number);
bool Output(List* L);
