#pragma once
#include <vector>
#include <string>

struct Project;

class WorkBaseTime {
public:
    virtual ~WorkBaseTime() = default;
    virtual double calcBase() = 0;
    virtual double calcBonus() = 0;
};

class ProjectBudget {
public:
    virtual ~ProjectBudget() = default;
    virtual double calcBudgetPart(double projectBudget, int totalWorkers) = 0;
    virtual double calcProAdditions() = 0;
};

class Heading {
public:
    virtual ~Heading() = default;
    virtual double calcHeadingAdditions(int subordinateCount) = 0;
};