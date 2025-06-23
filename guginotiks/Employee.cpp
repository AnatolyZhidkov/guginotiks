#include "Employee.h"
#include <sstream>
using namespace std;

// �������������� �����: ������� ������ ���� ����� �������
string formatNumber(double number) {
    string numStr = to_string(number);  // ����������� ����� � ������

    // ������� ��� ���������� �����
    size_t dotPos = numStr.find('.');
    if (dotPos == string::npos) {
        return numStr;  // ���� ����� �� �������, ���������� ��� ����
    }

    // ���������� 0 ����� �����
    size_t lastNonZero = numStr.find_last_not_of('0');

    if (lastNonZero != string::npos && lastNonZero > dotPos) {
        if (lastNonZero == dotPos) {
            // ���� ����� ����� ������ 0 - ������� ��� ������� �����
            numStr = numStr.substr(0, dotPos);
        }
        else {
            // ������� ������ ���� ����� ���������� ��������� �������
            numStr = numStr.substr(0, lastNonZero + 1);
        }
    }

    // ������� �����, ���� ��� �������� � �����
    if (!numStr.empty() && numStr.back() == '.') {
        numStr.pop_back();
    }

    return numStr;
}

// ����������� �������������� �������� ���� ����������
Employee::Employee(int id, const string& name,
    const string& position, const string& project)
    : id(id), name(name), position(position), project(project),
    worktime(0), payment(0) {
}

// ��������� ���-�� ������������ �����
void Employee::setWorkTime(double hours) {
    worktime = hours;
}

// ���������� ���������� �� ����� ������
void Employee::setProject(const string& newProject) {
    project = newProject;
}

// ������� ��� ������� � ��������� �����
int Employee::getId() const { return id; }
const string& Employee::getName() const { return name; }
const string& Employee::getPosition() const { return position; }
const string& Employee::getProject() const { return project; }
double Employee::getPayment() const { return payment; }

// ����� ���������� � ����������
void Employee::printInfo() const {
    // ��������������� ����� � �������������� ���������:
    // %-4d  - ID (������������ �� ������ ����, 4 �������)
    // %-20s - ��� (20 ��������)
    // %-20s - ��������� (20 ��������)
    // %-8s  - ���� (8 ��������)
    // %-12s - �������� (12 ��������)
    printf("%-4d %-20s %-20s %-8s %-12s\n",
        id,
        name.c_str(),
        position.c_str(),
        formatNumber(worktime).c_str(),
        formatNumber(payment).c_str());
}