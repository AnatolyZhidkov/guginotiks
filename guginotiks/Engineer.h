#pragma once
#include "Employee.h"
#include "Interfaces.h"
using namespace std;

// Базовый класс для сотрудников (программисты, тестировщики)
class Engineer : public Employee, public WorkBaseTime, public ProjectBudget {
protected:
    double salary;  // Почасовая ставка

public:
    Engineer(int id, const string& name,
        const string& position, const string& project, double salary);

    // Рассчет базовой части ЗП (ставка * часы)
    double calcBase() override;

    // Бонусная часть (для переопределения)
    double calcBonus() override;

    // Возврат почасовуй ставки
    double getSalary() const override;

    // Рассчет доли от бюджета проекта
    double calcBudgetPart(double projectBudget, int totalWorkers) override;
};

// Программист - производный класс от Engineer
class Programmer : public Engineer {
protected:
    bool hasEarlyCompletion;  // Флаг досрочного завершения проекта

public:
    Programmer(int id, const string& name,
        const string& position, const string& project, double salary);

    // Устанавка флага досрочного завершения
    void setEarlyCompletion(bool flag);

    // Доплата за досрочное завершение (20000 если true)
    double calcProAdditions() override;

    // Рассчет ЗП программиста
    void calc(const vector<Project>& projects,
        const vector<Employee*>& staff) override;
};

// Тестировщик - производный класс от Engineer
class Tester : public Engineer {
private:
    int errorCount;  // Количество найденных ошибок

public:
    Tester(int id, const string& name,
        const string& position, const string& project, double salary);

    // Устанавливает количество найденных ошибок
    void setErrorCount(int count);

    // Доплата за найденные ошибки (500 за каждую)
    double calcProAdditions() override;

    // Рассчитывает зарплату тестировщика
    void calc(const vector<Project>& projects,
        const vector<Employee*>& staff) override;
};