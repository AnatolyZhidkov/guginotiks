#pragma once
#include "Project.h"
#include "Interfaces.h"
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
using namespace std;

class Employee {
protected:
    int id;
    string name;
    double worktime;
    double payment;
    string position;
    string project;

public:
    Employee(int id, const string& name,
        const string& position, const string& project);
    virtual ~Employee() = default;

    virtual void calc(const vector<Project>& projects,
        const vector<Employee*>& staff) = 0;

    void setWorkTime(double hours);
    void setProject(const string& newProject);

    int getId() const;
    const string& getName() const;
    const string& getPosition() const;
    const string& getProject() const;
    double getPayment() const;
    virtual double getSalary() const = 0;

    virtual void printInfo() const;
};