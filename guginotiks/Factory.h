#pragma once
#include <vector>
#include <string>
using namespace std;

class Employee;

// �������� � ���������� ���������
class StaffFactory {
public:
    // ������� �������� �� �����
    static vector<Employee*> makeStaff(const string& filename);

    // ��������� ������ � ��������� � ����
    static void saveStaff(const string& filename,
        const vector<Employee*>& staff);
};