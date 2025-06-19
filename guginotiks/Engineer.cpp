#include "Engineer.h"
#include "Project.h"
#include <algorithm>
using namespace std;

Engineer::Engineer(int id, const string& name,
    const string& position, const string& project, double salary)
    : Employee(id, name, position, project), salary(salary) {
}

double Engineer::calcBase() {
    return salary * worktime;
}

double Engineer::calcBonus() {
    return 0;
}

double Engineer::getSalary() const {
    return salary;
}

double Engineer::calcBudgetPart(double projectBudget, int totalWorkers) {
    return (projectBudget * 0.3) / totalWorkers;
}



Programmer::Programmer(int id, const string& name,
    const string& position, const string& project, double salary)
    : Engineer(id, name, position, project, salary), hasEarlyCompletion(false) {
}

void Programmer::setEarlyCompletion(bool flag) {
    hasEarlyCompletion = flag;
}

double Programmer::calcProAdditions() {
    return hasEarlyCompletion ? 20000 : 0;
}

void Programmer::calc(const vector<Project>& projects,
    const vector<Employee*>& staff) {
    double base = calcBase();
    double budgetPart = 0;
    double additions = calcProAdditions();

    if (!project.empty()) {
        auto it = find_if(projects.begin(), projects.end(),
            [this](const Project& p) { return p.name == project; });

        if (it != projects.end()) {
            int count = 0;
            for (auto emp : staff) {
                if (emp->getProject() == project &&
                    (emp->getPosition() == "programmer" ||
                        emp->getPosition() == "tester" ||
                        emp->getPosition() == "team_leader")) {
                    count++;
                }
            }
            budgetPart = calcBudgetPart(it->budget, count);
        }
    }

    payment = base + budgetPart + additions;
}

Tester::Tester(int id, const string& name,
    const string& position, const string& project, double salary)
    : Engineer(id, name, position, project, salary), errorCount(0) {
}

void Tester::setErrorCount(int count) {
    errorCount = count;
}

double Tester::calcProAdditions() {
    return 500 * errorCount;
}

void Tester::calc(const vector<Project>& projects,
    const vector<Employee*>& staff) {
    double base = calcBase();
    double budgetPart = 0;
    double additions = calcProAdditions();

    if (!project.empty()) {
        auto it = find_if(projects.begin(), projects.end(),
            [this](const Project& p) { return p.name == project; });

        if (it != projects.end()) {
            int count = 0;
            for (auto emp : staff) {
                if (emp->getProject() == project &&
                    (emp->getPosition() == "programmer" ||
                        emp->getPosition() == "tester" ||
                        emp->getPosition() == "team_leader")) {
                    count++;
                }
            }
            budgetPart = calcBudgetPart(it->budget, count);
        }
    }

    payment = base + budgetPart + additions;
}