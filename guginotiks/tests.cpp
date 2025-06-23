//#include <cassert>
//#include <vector>
//#include <fstream>
//#include <sstream>
//#include "Employee.h"
//#include "Personal.h"
//#include "Engineer.h"
//#include "Manager.h"
//#include "Project.h"
//#include "Factory.h"
//
//using namespace std;
//
//// ��������������� ������� ��� �������� �������� ������
//void createTestFiles() {
//    // ������� �������� ���� �����������
//    ofstream staffFile("test_staff.txt");
//    staffFile << "id;name;position;salary;project\n"
//        << "1;Test Cleaner;cleaner;100;-\n"
//        << "2;Test Driver;driver;120;-\n"
//        << "3;Test Programmer;programmer;150;ProjectA\n"
//        << "4;Test Tester;tester;140;ProjectA\n"
//        << "5;Test TeamLeader;team_leader;200;ProjectA\n"
//        << "6;Test ProjManager;project_manager;0;ProjectA\n"
//        << "7;Test SeniorManager;senior_manager;0;-\n";
//    staffFile.close();
//
//    // ������� �������� ���� ��������
//    ofstream projectsFile("test_projects.txt");
//    projectsFile << "name;budget\n"
//        << "ProjectA;1000000.00\n"
//        << "ProjectB;500000.00\n";
//    projectsFile.close();
//}
//
//void testCleaner() {
//    Cleaner cleaner(101, "John Doe", "cleaner", "-", 100);
//    cleaner.setWorkTime(160);
//    cleaner.calc({}, {});
//
//    assert(cleaner.getPayment() == 16000);
//    assert(cleaner.getSalary() == 100);
//    cout << "Cleaner tests passed\n";
//}
//
//void testDriver() {
//    Driver driver(102, "Jane Smith", "driver", "-", 120);
//    driver.setWorkTime(160);
//    driver.setNightHours(40);
//    driver.calc({}, {});
//
//    assert(driver.getPayment() == (160 * 120 + 40 * 60)); // 19200 + 2400 = 21600
//    cout << "Driver tests passed\n";
//}
//
//void testProgrammer() {
//    Programmer prog(103, "Alice Programmer", "programmer", "ProjectA", 150);
//    prog.setWorkTime(160);
//    prog.setEarlyCompletion(true);
//
//    vector<Project> projects = { {"ProjectA", 1000000} };
//    vector<Employee*> staff = { &prog };
//
//    prog.calc(projects, staff);
//
//    // ����: 150*160 = 24000
//    // ������: (1000000*0.3)/1 = 300000
//    // �����: 20000
//    assert(prog.getPayment() == 24000 + 300000 + 20000);
//    cout << "Programmer tests passed\n";
//}
//
//void testTester() {
//    Tester tester(104, "Bob Tester", "tester", "ProjectA", 140);
//    tester.setWorkTime(160);
//    tester.setErrorCount(10);
//
//    vector<Project> projects = { {"ProjectA", 1000000} };
//    vector<Employee*> staff = { &tester };
//
//    tester.calc(projects, staff);
//
//    // ����: 140*160 = 22400
//    // ������: (1000000*0.3)/1 = 300000
//    // �����: 500*10 = 5000
//    assert(tester.getPayment() == 22400 + 300000 + 5000);
//    cout << "Tester tests passed\n";
//}
//
//void testTeamLeader() {
//    // ������� �������: 1 ����� + 2 ������������
//    TeamLeader leader(105, "Lead Dev", "team_leader", "ProjectA", 200);
//    Programmer prog1(106, "Dev 1", "programmer", "ProjectA", 150);
//    Programmer prog2(107, "Dev 2", "programmer", "ProjectA", 160);
//
//    leader.setWorkTime(160);
//    prog1.setWorkTime(160);
//    prog2.setWorkTime(160);
//    leader.setEarlyCompletion(true);
//
//    vector<Project> projects = { {"ProjectA", 1000000} };
//    vector<Employee*> staff = { &leader, &prog1, &prog2 };
//
//    // ������ ��� ����
//    for (auto emp : staff) {
//        emp->calc(projects, staff);
//    }
//
//    // �������� ������:
//    // ����: 200*160 = 32000
//    // ������: (1000000*0.3)/3 = 100000 (3 �������� � �������)
//    // �����: 20000
//    // ������� �� �������: 500 * 2 ����������� = 1000
//    assert(leader.getPayment() == 32000 + 100000 + 20000 + 1000);
//    cout << "TeamLeader tests passed\n";
//}
//
//void testProjectManager() {
//    ProjectManager pm(108, "PM Alex", "project_manager", "ProjectA");
//
//    // ������� ������� ��� �������
//    Programmer prog(109, "Prog", "programmer", "ProjectA", 150);
//    Tester tester(110, "Tester", "tester", "ProjectA", 140);
//
//    vector<Project> projects = { {"ProjectA", 1000000} };
//    vector<Employee*> staff = { &pm, &prog, &tester };
//
//    // ������ �������
//    for (auto emp : staff) {
//        emp->calc(projects, staff);
//    }
//
//    // �������� PM:
//    // ������: (1000000*0.3)/2 = 150000 (2 ��������)
//    // ������� �� �����������: 1000 * 2 = 2000
//    assert(pm.getPayment() == 150000 + 2000);
//    cout << "ProjectManager tests passed\n";
//}
//
//void testSeniorManager() {
//    SeniorManager sm(111, "Senior Boss", "senior_manager");
//
//    // ������� ������� � ����������
//    vector<Project> projects = {
//        {"ProjectA", 1000000},
//        {"ProjectB", 500000}
//    };
//
//    ProjectManager pm1(112, "PM1", "project_manager", "ProjectA");
//    ProjectManager pm2(113, "PM2", "project_manager", "ProjectB");
//    TeamLeader tl(114, "TeamLead", "team_leader", "ProjectA", 200);
//
//    vector<Employee*> staff = { &sm, &pm1, &pm2, &tl };
//
//    // ������ �������
//    for (auto emp : staff) {
//        emp->calc(projects, staff);
//    }
//
//    // �������� SeniorManager:
//    // ������: 15% �� ���� �������� = (1000000+500000)*0.15 = 225000
//    // ������� �� �����������: 5000 * 3 (2 PM + 1 TL) = 15000
//    assert(sm.getPayment() == 225000 + 15000);
//    cout << "SeniorManager tests passed\n";
//}
//
//void testFactory() {
//    createTestFiles();
//
//    // ���� �������� �����������
//    vector<Employee*> staff = StaffFactory::makeStaff("test_staff.txt");
//    assert(staff.size() == 7);
//
//    // �������� �����
//    assert(dynamic_cast<Cleaner*>(staff[0]) != nullptr);
//    assert(dynamic_cast<Driver*>(staff[1]) != nullptr);
//    assert(dynamic_cast<Programmer*>(staff[2]) != nullptr);
//    assert(dynamic_cast<Tester*>(staff[3]) != nullptr);
//    assert(dynamic_cast<TeamLeader*>(staff[4]) != nullptr);
//    assert(dynamic_cast<ProjectManager*>(staff[5]) != nullptr);
//    assert(dynamic_cast<SeniorManager*>(staff[6]) != nullptr);
//
//    // �������� ������
//    assert(staff[2]->getName() == "Test Programmer");
//    assert(staff[3]->getProject() == "ProjectA");
//
//    // ���� ����������
//    StaffFactory::saveStaff("test_staff_out.txt", staff);
//    ifstream in("test_staff_out.txt");
//    string line;
//    getline(in, line); // header
//    getline(in, line);
//    //assert(line.find("Test Programmer;programmer;150;ProjectA") != string::npos);
//    
//    // �������
//    for (auto emp : staff) delete emp;
//    cout << "Factory tests passed\n";
//}
//
//void testProjectLoading() {
//    createTestFiles();
//
//    vector<Project> projects;
//    ifstream file("test_projects.txt");
//    string line;
//    getline(file, line); // header
//
//    while (getline(file, line)) {
//        istringstream iss(line);
//        string name, budgetStr;
//        if (getline(iss, name, ';') && getline(iss, budgetStr)) {
//            projects.push_back({ name, stod(budgetStr) });
//        }
//    }
//
//    assert(projects.size() == 2);
//    assert(projects[0].name == "ProjectA");
//    assert(projects[0].budget == 1000000.00);
//    assert(projects[1].name == "ProjectB");
//    assert(projects[1].budget == 500000.00);
//    cout << "Project loading tests passed\n";
//}
//
//void testEdgeCases() {
//    // ���� 1: ������ ��� �������
//    Programmer prog(201, "Prog", "programmer", "NoBudget", 150);
//    prog.setWorkTime(160);
//    vector<Project> projects = { {"NoBudget", 0} };
//    vector<Employee*> staff = { &prog };
//    prog.calc(projects, staff);
//    assert(prog.getPayment() == 150 * 160); // ������ ������� �����
//
//    // ���� 2: ������� �� 0 (��� ����������� � �������)
//    ProjectManager pm(202, "PM", "project_manager", "EmptyProject");
//    vector<Project> projects2 = { {"EmptyProject", 500000} };
//    vector<Employee*> staff2 = { &pm };
//    pm.calc(projects2, staff2);
//    assert(pm.getPayment() == 0); // ��������� ����� = 0
//
//    // ���� 3: ������������� ����� ������
//    Cleaner cleaner(203, "Cleaner", "cleaner", "-", 100);
//    cleaner.setWorkTime(-40);
//    cleaner.calc({}, {});
//    assert(cleaner.getPayment() <= 0);
//
//    cout << "Edge cases tests passed\n";
//}
//
//void runAllTests() {
//    testCleaner();
//    testDriver();
//    testProgrammer();
//    testTester();
//    testTeamLeader();
//    testProjectManager();
//    testSeniorManager();
//    testFactory();
//    testProjectLoading();
//    testEdgeCases();
//
//    cout << "\n=== ALL TESTS PASSED SUCCESSFULLY ===\n";
//}
//
////int main() {
////    runAllTests();
////    return 0;
////}