#include "Employee.h"
using namespace std;

Employee::Employee(int id, const string& name,
    const string& position, const string& project)
    : id(id), name(name), position(position), project(project),
    worktime(0), payment(0) {
}

void Employee::setWorkTime(double hours) {
    worktime = hours;
}

void Employee::setProject(const string& newProject) {
    project = newProject;
}

int Employee::getId() const {
    return id;
}

const string& Employee::getName() const {
    return name;
}

const string& Employee::getPosition() const {
    return position;
}

const string& Employee::getProject() const {
    return project;
}

double Employee::getPayment() const {
    return payment;
}

void Employee::printInfo() const {
    cout << left << setw(5) << id
        << setw(20) << name
        << setw(20) << position
        << setw(10) << worktime
        << setw(15) << fixed << setprecision(2) << payment << endl;
}