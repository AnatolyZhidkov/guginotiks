#pragma once
#include "Employee.h"
#include "Interfaces.h"
using namespace std;

// Класс для персонала с почасовой оплатой (уборщики, водители)
class Personal : public Employee, public WorkBaseTime {
protected:
    double salary;  // Почасовая ставка

public:
    Personal(int id, const string& name,
        const string& position, const string& project, double salary);

    // Рассчет базовой части ЗП (ставка * часы)
    double calcBase() override;

    // Возврат почасовую ставку
    double getSalary() const override;
};

// Уборщик 
class Cleaner : public Personal {
public:
    Cleaner(int id, const string& name,
        const string& position, const string& project, double salary);

    // Бонусы для уборщика отсутствуют (всегда 0)
    double calcBonus() override;

    // Рассчет общей ЗП 
    void calc(const vector<Project>& projects,
        const vector<Employee*>& staff) override;
};

// Водитель
class Driver : public Personal {
private:
    double nightHours;  // Количество ночных часов

public:
    Driver(int id, const string& name,
        const string& position, const string& project, double salary);

    // Устанавлка кол-ва ночных часов
    void setNightHours(double hours);

    // Рассчет бонуса за ночные часы (50% доплата)
    double calcBonus() override;

    // Рассчет общей ЗП (база + бонусы)
    void calc(const vector<Project>& projects,
        const vector<Employee*>& staff) override;
};