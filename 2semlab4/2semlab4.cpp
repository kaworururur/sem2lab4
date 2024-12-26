#include <iostream>
#include <fstream>
#include <string>
#include <deque>
#include <list>
#include <algorithm>

class Student {
public:
    std::string name;
    std::string group;
    int studentID;
    int grades[4];

    // Конструктор по умолчанию
    Student() {}

    // Конструктор с параметрами
    Student(std::string n, std::string g, int id, int g1, int g2, int g3, int g4) : name(n), group(g), studentID(id) {
        grades[0] = g1;
        grades[1] = g2;
        grades[2] = g3;
        grades[3] = g4;
    }

    // Перегруженная операция вставки в поток <<
    friend std::ostream& operator<<(std::ostream& os, const Student& student) {
        os << "Name: " << student.name << ", Group: " << student.group << ", ID: " << student.studentID << ", Grades: ";
        for (int i = 0; i < 4; i++) {
            os << student.grades[i] << " ";
        }
        return os;
    }
};

bool compareStudents(const Student& s1, const Student& s2) {
    int sum1 = 0, sum2 = 0;
    for (int i = 0; i < 4; i++) {
        sum1 += s1.grades[i];
        sum2 += s2.grades[i];
    }
    return (sum1 > sum2);
}

int main() {
    std::ifstream inputFile("input.txt");
    if (!inputFile) {
        std::cerr << "Error opening input.txt" << std::endl;
        return 1;
    }

    std::deque<Student> studentsDeque;
    std::list<Student> studentsList;

    std::string name, group;
    int id, g1, g2, g3, g4;

    while (inputFile >> name >> group >> id >> g1 >> g2 >> g3 >> g4) {
        Student student(name, group, id, g1, g2, g3, g4);
        studentsDeque.push_back(student);
    }

    studentsList.assign(studentsDeque.begin(), studentsDeque.end());

    // Сортировка исходного контейнера deque
    std::sort(studentsDeque.begin(), studentsDeque.end(), compareStudents);

    // Вывод в файл output.txt
    std::ofstream outputFile("output.txt");
    for (const auto& student : studentsDeque) {
        outputFile << student << std::endl;
    }
    outputFile << std::endl;

    // Сортировка контейнера list
    studentsList.sort(compareStudents);

    for (const auto& student : studentsList) {
        outputFile << student << std::endl;
    }
    outputFile << std::endl;

    // Вывод контейнера, скопированного из deque в list
    for (const auto& student : studentsList) {
        outputFile << student << std::endl;
    }

    inputFile.close();
    outputFile.close();

    return 0;
}