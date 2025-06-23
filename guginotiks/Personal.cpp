#include "Personal.h"
using namespace std;

// Иницилизатор по часовой ЗП
Personal::Personal(int id, const string& name,
    const string& position, const string& project, double salary)
    : Employee(id, name, position, project), salary(salary) {
}

// Базовая зарплата = ставка * часы
double Personal::calcBase() {
    return salary * worktime;
}

// Возврат почасовой ставки
double Personal::getSalary() const {
    return salary;
}

//  Вызов конструктора Уборщика
Cleaner::Cleaner(int id, const string& name,
    const string& position, const string& project, double salary)
    : Personal(id, name, position, project, salary) {
}

// Уборщики не получают бонусов..... к сожилению... такова грустность их образования(((((
double Cleaner::calcBonus() {
    return 0;
}

// Зарплата уборщика = базовая часть
void Cleaner::calc(const vector<Project>& projects,
    const vector<Employee*>& staff) {
    payment = calcBase() + calcBonus();
}

// Конструктор Водителя инициализирует ночные часы нулем
Driver::Driver(int id, const string& name,
    const string& position, const string& project, double salary)
    : Personal(id, name, position, project, salary), nightHours(0) {
}

// Установка кол-ва ночных смен
void Driver::setNightHours(double hours) {
    nightHours = hours;
}

// Бонус водителя: 50% доплата за ночные часы (Ему повезло больше тк есть права) )
double Driver::calcBonus() {
    return (salary * 0.5) * nightHours;
}

// Зарплата водителя = база + бонус за ночные часы(если они есть)
void Driver::calc(const vector<Project>& projects,
    const vector<Employee*>& staff) {
    payment = calcBase() + calcBonus();
}