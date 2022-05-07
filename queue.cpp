#include "queue.h"
#include <iostream>
#include <cstring>
using namespace std;

inline man create_elem(queue& q, string name, string sex, int age, string job, int zp, bool kv) {
	man n;
	n.name = name;
	n.sex = sex;
	n.age = age;
	n.job = job;
	n.zp = zp;
	n.kv = kv;
	return n;
}

void enqueue(queue& q, string name, string sex, int age, string job, int zp, bool kv) {
	man newn = create_elem(q,name, sex, age, job, zp, kv);
	elem* newel = new elem;
	newel->n = newn;
	if (!q.tail) {    //была ли очередь (был ли хвост)
		q.head = q.tail = newel;
	}
	else {
		q.tail->next = newel;
		q.tail = newel;
	}
	q.lenght++;
}

void delete_elem(queue& q) {
	elem* rem = q.head;
	q.head = q.head->next;
	delete rem;
	q.lenght--;
}

bool dequeue(queue& q, man& n) {
	if (!q.head) return false;
	n = q.head->n;
	delete_elem(q);
	if (!q.head) q.tail = nullptr;
	return true;
}

void clear(queue& q) {
	while (q.head) {
		delete_elem(q);
	}
	q.tail = nullptr;
}
