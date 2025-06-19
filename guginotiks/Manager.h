#pragma once
#include "Employee.h"
#include "Interfaces.h"
#include "Engineer.h"  
using namespace std;

class ProjectManager : public Employee, public ProjectBudget, public Heading {
public:
    ProjectManager(int id, const string& name,
        const string& position, const string& project);

    double calcBudgetPart(double projectBudget, int totalWorkers) override;
    double calcProAdditions() override;
    double calcHeadingAdditions(int subordinateCount) override;
    double getSalary() const override;
    void calc(const vector<Project>& projects,
        const vector<Employee*>& staff) override;
};

class SeniorManager : public Employee, public ProjectBudget, public Heading {
public:
    SeniorManager(int id, const string& name, const string& position);

    double calcBudgetPart(double projectBudget, int totalWorkers) override;
    double calcProAdditions() override;
    double calcHeadingAdditions(int subordinateCount) override;
    double getSalary() const override;
    void calc(const vector<Project>& projects,
        const vector<Employee*>& staff) override;
};

class TeamLeader : public Programmer, public Heading {
public:
    TeamLeader(int id, const string& name,
        const string& position, const string& project, double salary);

    double calcHeadingAdditions(int subordinateCount) override;
    void calc(const vector<Project>& projects,
        const vector<Employee*>& staff) override;
};