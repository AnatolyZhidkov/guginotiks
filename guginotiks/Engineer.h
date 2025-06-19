#pragma once
#include "Employee.h"
#include "Interfaces.h"
using namespace std;

class Engineer : public Employee, public WorkBaseTime, public ProjectBudget {
protected:
    double salary;

public:
    Engineer(int id, const string& name,
        const string& position, const string& project, double salary);

    double calcBase() override;
    double calcBonus() override;
    double getSalary() const override;
    double calcBudgetPart(double projectBudget, int totalWorkers) override;
};

class Programmer : public Engineer {
protected:
    bool hasEarlyCompletion;

public:
    Programmer(int id, const string& name,
        const string& position, const string& project, double salary);

    void setEarlyCompletion(bool flag);
    double calcProAdditions() override;
    void calc(const vector<Project>& projects,
        const vector<Employee*>& staff) override;
};

class Tester : public Engineer {
private:
    int errorCount;

public:
    Tester(int id, const string& name,
        const string& position, const string& project, double salary);

    void setErrorCount(int count);
    double calcProAdditions() override;
    void calc(const vector<Project>& projects,
        const vector<Employee*>& staff) override;
};