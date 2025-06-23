#pragma once
#include <vector>
#include <string>
using namespace std;

class Employee;

// Создания и сохранения персонала
class StaffFactory {
public:
    // Создает персонал из файла
    static vector<Employee*> makeStaff(const string& filename);

    // Сохраняет данные о персонале в файл
    static void saveStaff(const string& filename,
        const vector<Employee*>& staff);
};