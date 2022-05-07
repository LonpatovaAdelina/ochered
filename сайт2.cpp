#include <iostream>
#include <fstream>
#include <string>
#include "cgi.h"
#include "queue.h"

using namespace std;

void show_content();
void show_menu();

void load_data(const char* filename, queue& kredit, queue& vklad);

void show_queue(queue& q);

static vector<string> split(const string& s, char delim);

void main() {
    cout << "Content-type: text/html; charset=Windows-1251\n\n";
    ifstream f("_index.html");
    if (f.is_open()) {
        auto sz = 65536;
        auto buf = new char[sz];
        while (!f.eof()) {
            f.getline(buf, sz);
            if (strcmp(buf, "<!--content-->") == 0) {
                show_content();
            }
            else if (!strcmp(buf, "<!--menu-->")) {
                show_menu();
            }
            cout << buf;
        }
        delete[] buf;
        f.close();
    }
    else {
        cout << "Не удалось открыть страницу";
    }
}

void show_menu() {
    ifstream f("menu.html");
    if (f.is_open()) {
        auto sz = 1024;
        auto buf = new char[sz];
        while (!f.eof()) {
            f.getline(buf, sz);
            char* name;
            char* addrr = strtok_s(buf, " ", &name);
            cout << "<div class='menu.html'>"
                "<a href='" << addrr << "'> " <<
                name << "</a>"
                "</div>";
        }
    }
}

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
            cout << ++i << ".\t" << m.name << m.sex << m.age << m.job << m.zp;
            cout << "\tцель обращения: ";
            if (m.kv) {
                cout << "кредит" << endl;
            }
            else cout << "вклад " << endl;
        }
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

void show_content() {
    cout << "<form method='get' action='index.cgi'>";
    cout << "Введите список: <input type='text' name='task' maxlenght='80' size='80'<br>";
    cout << "<input type='submit' value='Проверить'>";
    cout << "</form>";


#ifndef _DEBUG            //проверка на дебаг
    char* data = nullptr;
    get_from_data(data);
#else
    const char* data = "task=%28%29";
#endif

    if (data && strlen(data) > 0) {
        //cout << "<div>" << data << "</div>";
        char* value = nullptr;
        get_param_value(value, "task", data); // получить значение 
        cout << "<div>" << value << "</div>";
        string t = value;
    }
    delete[] data;
}
