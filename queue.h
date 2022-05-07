#pragma once
#include <iostream>
using namespace std;

struct man {
	string name;
	string sex;
	int age;
	string job;
	int zp;
	bool kv;
};

struct elem {
	man n;
	elem* next=nullptr;
};

struct queue {
	elem* head = nullptr;
	elem* tail = nullptr;
	size_t lenght = 0;
};

void enqueue(queue& q, string name, string sex, int age, string job, int zp, bool kv);
bool dequeue(queue& q, man& n);     //проверка на то, был ли получен аргумент
void clear(queue& q);
