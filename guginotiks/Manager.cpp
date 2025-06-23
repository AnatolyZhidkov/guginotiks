#include "Manager.h"
#include "Project.h"
using namespace std;

// ����������� ��������� �������
ProjectManager::ProjectManager(int id, const string& name,
    const string& position, const string& project)
    : Employee(id, name, position, project) {
}

// ���� �� �������: 30% ������� / ���������� ����������
double ProjectManager::calcBudgetPart(double projectBudget, int totalWorkers) {
    if (totalWorkers == 0) return 0;
    return (projectBudget * 0.3) / totalWorkers;
}

// ��� ������� �� �������������
double ProjectManager::calcProAdditions() {
    return 0;
}

// ������� �� �����������: 1000 �� �������
double ProjectManager::calcHeadingAdditions(int subordinateCount) {
    return 1000 * subordinateCount;
}

// ��������� �� ����� ������������� ������
double ProjectManager::getSalary() const {
    return 0;
}

// ������ �������� ���������:
// ���� �� ������� + ������� �� �����������
void ProjectManager::calc(const vector<Project>& projects,
    const vector<Employee*>& staff) {
    double budgetPart = 0;
    double headingAdditions = 0;

    if (!project.empty()) {
        // ����� ������� �� �����
        vector<Project>::const_iterator it;
        for (it = projects.begin(); it != projects.end(); ++it) {
            if (it->name == project) {
                break;
            }
        }

        if (it != projects.end()) {
            int workerCount = 0;      // ���-�� ���������� �� �������
            int subordinateCount = 0; // ���-�� �����������

            for (auto emp : staff) {
                if (emp->getProject() == project) {
                    // ������� ��������� �� �������
                    if (emp->getPosition() == "programmer" ||
                        emp->getPosition() == "tester" ||
                        emp->getPosition() == "team_leader") {
                        workerCount++;
                    }

                    // ������� ����������� (��� ����� ���������)
                    if (emp->getId() != id) {
                        subordinateCount++;
                    }
                }
            }

            // ������ ������������ ��������
            budgetPart = calcBudgetPart(it->budget, workerCount);
            headingAdditions = calcHeadingAdditions(subordinateCount);
        }
    }

    payment = budgetPart + headingAdditions;
}

// ����������� �������� ��������� (�� �������� � �������)
SeniorManager::SeniorManager(int id, const string& name,
    const string& position)
    : Employee(id, name, position, "") {
}

// ���� �� �������: 15% �� ������� �������
double SeniorManager::calcBudgetPart(double projectBudget, int totalWorkers) {
    return projectBudget * 0.15;
}

// �������������� ������� �� �������������
double SeniorManager::calcProAdditions() {
    return 0;
}

// ������� �� �����������: 5000 �� ������� ���������
double SeniorManager::calcHeadingAdditions(int subordinateCount) {
    return 5000 * subordinateCount;
}

// ������� �������� �� ����� ������������� ������
double SeniorManager::getSalary() const {
    return 0;
}

// ������ �������� �������� ���������:
// ����� �� ���� �������� (15% �� �������) + ������� �� �����������
void SeniorManager::calc(const vector<Project>& projects,
    const vector<Employee*>& staff) {
    double budgetTotal = 0;
    int subordinateCount = 0;

    // ��������� ���� �� ���� ��������
    for (const auto& p : projects) {
        budgetTotal += calcBudgetPart(p.budget, 0);
    }

    // ������������ ����������� (���������� � �������� ������)
    for (auto emp : staff) {
        if (emp->getPosition() == "project_manager" ||
            emp->getPosition() == "team_leader") {
            subordinateCount++;
        }
    }

    payment = budgetTotal + calcHeadingAdditions(subordinateCount);
}

// ����������� ������ �������
TeamLeader::TeamLeader(int id, const string& name,
    const string& position, const string& project, double salary)
    : Programmer(id, name, position, project, salary) {
}

// ������� �� �����������: 500 �� ������� ������������
double TeamLeader::calcHeadingAdditions(int subordinateCount) {
    return 500 * subordinateCount;
}

// ������ �������� ������ �������:
// �������� ������������ + ������� �� �����������
void TeamLeader::calc(const vector<Project>& projects,
    const vector<Employee*>& staff) {
    // ������� ������������ �������� ��� ��� ������������
    Programmer::calc(projects, staff);

    int subordinateCount = 0;
    // ������������ ����������� ������������� (����� ������ ������)
    for (auto emp : staff) {
        if (emp->getProject() == project &&
            emp->getPosition() == "programmer" &&
            emp->getId() != id) {
            subordinateCount++;
        }
    }

    // ��������� ������� �� �����������
    payment += calcHeadingAdditions(subordinateCount);
}