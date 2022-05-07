#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "queue.h"
using namespace std;

void load_data(const char* filename, queue& kredit, queue& vklad);

void show_queue(queue& q);

static vector<string> split(const string& s, char delim);

void main() {
	setlocale(LC_ALL, "ru");
	queue kredit;
	queue vklad;
	load_data("data.txt", kredit, vklad);
	cout << "Кредит:\n";
	show_queue(kredit);
	cout << "Вклад:\n";
	show_queue(vklad);
}
void load_data(const char* filename, queue& kredit, queue& vklad) {
	ifstream f(filename);
	if (f.is_open()) {
		while (!f.eof()) {
			char* file = new char[700];
			f.getline(file, 700);
			vector<string> date = split(static_cast<string>(file), ' ');
			string name = date[1];
			string sex = date[2];
			int age = stoi(date[3]);
			string job = date[4];
			int zp = atof(date[5].c_str());
			bool kv;
			if (date[6] == "кредит") enqueue(kredit, name, sex, age, job, zp, true);
			else  enqueue(vklad, name, sex, age, job, zp, false);
			/*char* man = new char[60];
			f.getline(man, 60);
			char* name = new char[50];
			bool kv;
			sscanf_s(man, "%49[^0-9] %d", name, 50, &kv);
			if (kv==) enqueue(k, name);
			else enqueue(v, name,sex, age,job, zp,false);*/
		}
		f.close();
	}
	else cout << "Файл не найден";
}

void show_queue(queue& q) {
	int i = 0;
	while (true) {
		man m;
		if (dequeue(q, m)) {
			cout << ++i << ".\t" << m.name <<m.sex << m.age<<m.job<<m.zp;
			cout << "\tцель обращения: ";
			if (m.kv) {
				cout << "кредит" << endl;
			}
			else cout << "вклад " << endl;
		}
		/*else {
			cout << "____________________________________"<<endl;
			break;
		}*/
	}
}

static vector<string> split(const string& s, char delim) {
	vector<string> elems;
	stringstream ss(s);
	string item;
	while (getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}
