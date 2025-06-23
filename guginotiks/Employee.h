#pragma once
#include "Project.h"
#include "Interfaces.h"
#include <string>
#include <vector>
using namespace std;

// Форматирует число для красивого вывода (убирает лишние нули)
string formatNumber(double number);

// Базовый класс для всех сотрудников
class Employee {
protected:
    int id;             // Уникальный идентификатор сотрудника
    string name;        // ФИО сотрудника
    double worktime;    // Отработанное время (в часах)
    double payment;     // Рассчитанная зарплата
    string position;    // Должность (cleaner, driver и т.д.)
    string project;     // Название проекта, над которым работает

public:
    // Конструктор инициализирует основные данные сотрудника
    Employee(int id, const string& name,
        const string& position, const string& project);

    virtual ~Employee() = default;  // Виртуальный деструктор

    // Основной метод для расчета зарплаты (должен быть реализован в производных классах)
    virtual void calc(const vector<Project>& projects,
        const vector<Employee*>& staff) = 0;

    // Установка отработанного времени
    void setWorkTime(double hours);

    // Смена проекта сотрудника
    void setProject(const string& newProject);

    // Геттеры для доступа к данным
    int getId() const;
    const string& getName() const;
    const string& getPosition() const;
    const string& getProject() const;
    double getPayment() const;

    // Получение базового оклада (для почасовых сотрудников)
    virtual double getSalary() const = 0;

    // Вывод информации о сотруднике в табличном формате
    virtual void printInfo() const;
};