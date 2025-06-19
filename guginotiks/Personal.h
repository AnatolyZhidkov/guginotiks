#pragma once
#include "Employee.h"
#include "Interfaces.h"
using namespace std;

class Personal : public Employee, public WorkBaseTime {
protected:
    double salary;

public:
    Personal(int id, const string& name,
        const string& position, const string& project, double salary);

    double calcBase() override;
    double getSalary() const override;
};

class Cleaner : public Personal {
public:
    Cleaner(int id, const string& name,
        const string& position, const string& project, double salary);

    double calcBonus() override;
    void calc(const vector<Project>& projects,
        const vector<Employee*>& staff) override;
};

class Driver : public Personal {
private:
    double nightHours;

public:
    Driver(int id, const string& name,
        const string& position, const string& project, double salary);

    void setNightHours(double hours);
    double calcBonus() override;
    void calc(const vector<Project>& projects,
        const vector<Employee*>& staff) override;
};