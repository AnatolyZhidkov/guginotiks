#include "Personal.h"
using namespace std;

Personal::Personal(int id, const string& name,
    const string& position, const string& project, double salary)
    : Employee(id, name, position, project), salary(salary) {
}

double Personal::calcBase() {
    return salary * worktime;
}

double Personal::getSalary() const {
    return salary;
}

Cleaner::Cleaner(int id, const string& name,
    const string& position, const string& project, double salary)
    : Personal(id, name, position, project, salary) {
}

double Cleaner::calcBonus() {
    return 0;
}

void Cleaner::calc(const vector<Project>& projects,
    const vector<Employee*>& staff) {
    payment = calcBase() + calcBonus();
}

Driver::Driver(int id, const string& name,
    const string& position, const string& project, double salary)
    : Personal(id, name, position, project, salary), nightHours(0) {
}

void Driver::setNightHours(double hours) {
    nightHours = hours;
}

double Driver::calcBonus() {
    return (salary * 0.5) * nightHours;
}

void Driver::calc(const vector<Project>& projects,
    const vector<Employee*>& staff) {
    payment = calcBase() + calcBonus();
}