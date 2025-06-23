#pragma once
#include "Employee.h"
#include "Interfaces.h"
#include "Engineer.h"
using namespace std;

// Менеджер проекта
class ProjectManager : public Employee, public ProjectBudget, public Heading {
public:
    ProjectManager(int id, const string& name,
        const string& position, const string& project);

    // Расчет доли от бюджета проекта
    double calcBudgetPart(double projectBudget, int totalWorkers) override;

    // Дополнительные выплаты (не используются)
    double calcProAdditions() override;

    // Доплата за подчиненных (1000 за каждого)
    double calcHeadingAdditions(int subordinateCount) override;

    // Менеджеры не имеют фиксированной ставки
    double getSalary() const override;

    // Расчет зарплаты менеджера
    void calc(const vector<Project>& projects,
        const vector<Employee*>& staff) override;
};

// Старший менеджер
class SeniorManager : public Employee, public ProjectBudget, public Heading {
public:
    SeniorManager(int id, const string& name, const string& position);

    // Расчет доли от бюджета (15% бюджета каждого проекта)
    double calcBudgetPart(double projectBudget, int totalWorkers) override;

    // Дополнительные выплаты (не используются)
    double calcProAdditions() override;

    // Доплата за подчиненных (5000 за каждого)
    double calcHeadingAdditions(int subordinateCount) override;

    // Старшие менеджеры не имеют фиксированной ставки
    double getSalary() const override;

    // Расчет зарплаты старшего менеджера
    void calc(const vector<Project>& projects,
        const vector<Employee*>& staff) override;
};

// Лидер команды
class TeamLeader : public Programmer, public Heading {
public:
    TeamLeader(int id, const string& name,
        const string& position, const string& project, double salary);

    // Доплата за подчиненных (500 за каждого программиста)
    double calcHeadingAdditions(int subordinateCount) override;

    // Расчет зарплаты с учетом доплаты за подчиненных
    void calc(const vector<Project>& projects,
        const vector<Employee*>& staff) override;
};