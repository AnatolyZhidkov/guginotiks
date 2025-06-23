#include "Employee.h"
#include <sstream>
using namespace std;

// Форматирование чисел: убирает лишние нули после запятой
string formatNumber(double number) {
    string numStr = to_string(number);  // Преобразует число в строку

    // позиция для десятичной точки
    size_t dotPos = numStr.find('.');
    if (dotPos == string::npos) {
        return numStr;  // Если точка не найдена, возвращаем как есть
    }

    // Нахождение 0 после точки
    size_t lastNonZero = numStr.find_last_not_of('0');

    if (lastNonZero != string::npos && lastNonZero > dotPos) {
        if (lastNonZero == dotPos) {
            // Если после точки только 0 - удаляет всю дробную часть
            numStr = numStr.substr(0, dotPos);
        }
        else {
            // Удаляет лишние нули после последнего значащего символа
            numStr = numStr.substr(0, lastNonZero + 1);
        }
    }

    // Удаляет точку, если она осталась в конце
    if (!numStr.empty() && numStr.back() == '.') {
        numStr.pop_back();
    }

    return numStr;
}

// Конструктор инициализирует основные поля сотрудника
Employee::Employee(int id, const string& name,
    const string& position, const string& project)
    : id(id), name(name), position(position), project(project),
    worktime(0), payment(0) {
}

// Устанавка кол-ва отработанных часов
void Employee::setWorkTime(double hours) {
    worktime = hours;
}

// Назначение сотрудника на новый проект
void Employee::setProject(const string& newProject) {
    project = newProject;
}

// Геттеры для доступа к приватным полям
int Employee::getId() const { return id; }
const string& Employee::getName() const { return name; }
const string& Employee::getPosition() const { return position; }
const string& Employee::getProject() const { return project; }
double Employee::getPayment() const { return payment; }

// Вывод информации о сотруднике
void Employee::printInfo() const {
    // Форматированный вывод с фиксированными колонками:
    // %-4d  - ID (выравнивание по левому краю, 4 символа)
    // %-20s - Имя (20 символов)
    // %-20s - Должность (20 символов)
    // %-8s  - Часы (8 символов)
    // %-12s - Зарплата (12 символов)
    printf("%-4d %-20s %-20s %-8s %-12s\n",
        id,
        name.c_str(),
        position.c_str(),
        formatNumber(worktime).c_str(),
        formatNumber(payment).c_str());
}