#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

struct Employee {
  int emp_id;
  string name;
  double salary;
  Employee *next;

  Employee(int id, string n, double s) {
    emp_id = id;
    name = n;
    salary = s;
    next = nullptr;
  }
};

class Payroll {
private:
  Employee *head;

public:
  Payroll() {
    head = nullptr;
    loadFromCSV();
  }

  ~Payroll() {
    Employee *current = head;
    while (current != nullptr) {
      Employee *temp = current;
      current = current->next;
      delete temp;
    }
  }

  bool isDuplicate(int id) {
    Employee *temp = head;
    while (temp != nullptr) {
      if (temp->emp_id == id) {
        return true;
      }
      temp = temp->next;
    }
    return false;
  }

  void loadFromCSV(const string &filename = "payroll.csv") {
    ifstream file(filename);
    if (!file.is_open()) {
      return; // File does not exist yet; start with empty system
    }

    string line;
    int loadedCount = 0;
    while (getline(file, line)) {
      if (line.empty())
        continue;
      stringstream ss(line);
      string idStr, name, salaryStr;

      if (getline(ss, idStr, ',') && getline(ss, name, ',') &&
          getline(ss, salaryStr, ',')) {
        try {
          int id = stoi(idStr);
          double salary = stod(salaryStr);

          if (!isDuplicate(id)) {
            Employee *newNode = new Employee(id, name, salary);
            if (head == nullptr) {
              head = newNode;
            } else {
              Employee *current = head;
              while (current->next != nullptr) {
                current = current->next;
              }
              current->next = newNode;
            }
            loadedCount++;
          }
        } catch (...) {
          // Skip headers or corrupted lines
          continue;
        }
      }
    }
    file.close();
    if (loadedCount > 0) {
      cout << "Loaded " << loadedCount << " employee record(s) from "
           << filename << "." << endl;
    }
  }

  void addEmployee() {
    int id;
    string n;
    double s;
    cout << "\n--- Add New Employee ---" << endl;
    cout << "Enter Employee ID: ";
    if (!(cin >> id)) {
      cout << "Error: Invalid input for Employee ID." << endl;
      cin.clear();
      cin.ignore(10000, '\n');
      return;
    }

    if (isDuplicate(id)) {
      cout << "Error: Employee ID " << id
           << " already exists! Cannot add duplicate employee ID." << endl;
      return;
    }

    cout << "Enter Employee Name: ";
    cin >> n;

    cout << "Enter Base Salary: ";
    if (!(cin >> s)) {
      cout << "Error: Invalid input for Base Salary." << endl;
      cin.clear();
      cin.ignore(10000, '\n');
      return;
    }

    Employee *newNode = new Employee(id, n, s);

    if (head == nullptr) {
      head = newNode;
      cout << "Success: " << n << " added as the first employee!" << endl;
      return;
    }
    Employee *current = head;
    while (current->next != nullptr) {
      current = current->next;
    }
    current->next = newNode;
    cout << "Success: " << n << " added to the system!" << endl;
  }

  void displayEmployee() {
    if (head == nullptr) {
      cout << "\nNo employees found in system." << endl;
      return;
    }
    Employee *temp = head;
    cout << "\n--- Employee List ---" << endl;
    while (temp != nullptr) {
      cout << "Employee ID : " << temp->emp_id << endl;
      cout << "Name        : " << temp->name << endl;
      cout << "Salary      : " << temp->salary << endl;
      cout << "-----------------------------" << endl;

      temp = temp->next;
    }
  }

  void deleteEmployee() {
    if (head == nullptr) {
      cout << "\nNo employees found in system to delete." << endl;
      return;
    }
    int id;
    cout << "\n--- Delete Employee ---" << endl;
    cout << "Enter Employee ID to delete: ";
    if (!(cin >> id)) {
      cout << "Error: Invalid ID input." << endl;
      cin.clear();
      cin.ignore(10000, '\n');
      return;
    }

    if (head->emp_id == id) {
      Employee *toDelete = head;
      head = head->next;
      cout << "Success: Employee ID " << id << " (" << toDelete->name
           << ") deleted." << endl;
      delete toDelete;
      return;
    }

    Employee *current = head;
    while (current->next != nullptr && current->next->emp_id != id) {
      current = current->next;
    }

    if (current->next == nullptr) {
      cout << "Error: Employee ID " << id << " not found." << endl;
    } else {
      Employee *toDelete = current->next;
      current->next = current->next->next;
      cout << "Success: Employee ID " << id << " (" << toDelete->name
           << ") deleted." << endl;
      delete toDelete;
    }
  }

  void updateEmployee() {
    if (head == nullptr) {
      cout << "\nNo employees found in system to update." << endl;
      return;
    }
    int id;
    cout << "\n--- Update Employee Details ---" << endl;
    cout << "Enter Employee ID to update: ";
    if (!(cin >> id)) {
      cout << "Error: Invalid ID input." << endl;
      cin.clear();
      cin.ignore(10000, '\n');
      return;
    }

    Employee *current = head;
    while (current != nullptr && current->emp_id != id) {
      current = current->next;
    }

    if (current == nullptr) {
      cout << "Error: Employee ID " << id << " not found." << endl;
      return;
    }

    string newName;
    double newSalary;
    cout << "Current Name: " << current->name << endl;
    cout << "Enter New Name: ";
    cin >> newName;

    cout << "Current Base Salary: " << current->salary << endl;
    cout << "Enter New Base Salary: ";
    if (!(cin >> newSalary)) {
      cout << "Error: Invalid salary input." << endl;
      cin.clear();
      cin.ignore(10000, '\n');
      return;
    }

    current->name = newName;
    current->salary = newSalary;
    cout << "Success: Employee ID " << id << " updated successfully!" << endl;
  }

  void generatePayroll() {
    if (head == nullptr) {
      cout << "\nNo employees found in system." << endl;
      return;
    }
    Employee *current = head;
    double TaxRate = 0.15;
    double totalPayout = 0.0;

    cout << "\n--- Payroll Report ---" << endl;

    while (current != nullptr) {
      double deduction = current->salary * TaxRate;
      double netSalary = current->salary - deduction;
      totalPayout += netSalary;

      cout << "Employee ID : " << current->emp_id
           << " | Name: " << current->name << endl;
      cout << "Gross Salary: " << current->salary << endl;
      cout << "Tax Deduction: " << deduction << endl;
      cout << "Net Salary  : " << netSalary << endl;
      cout << "-----------------------------" << endl;

      current = current->next;
    }
    cout << "Total Company Payout: " << totalPayout << endl;
    cout << "=====================================" << endl;
  }

  void saveToCSV(const string &filename = "payroll.csv") {
    ofstream file(filename);
    if (file.is_open()) {
      Employee *current = head;
      while (current != nullptr) {
        file << current->emp_id << "," << current->name << ","
             << current->salary << endl;
        current = current->next;
      }
      file.close();
      cout << "Payroll data saved to " << filename << " successfully!" << endl;
    } else {
      cout << "Error: Unable to open file " << filename << " for writing."
           << endl;
    }
  }
};

int main() {
  Payroll payroll;
  int choice;

  do {
    cout << "\n===================================" << endl;
    cout << "     EMPLOYEE PAYROLL SYSTEM       " << endl;
    cout << "===================================" << endl;
    cout << "1. Add New Employee" << endl;
    cout << "2. Display All Employees" << endl;
    cout << "3. Update Employee Details" << endl;
    cout << "4. Delete Employee" << endl;
    cout << "5. Generate Payroll Report" << endl;
    cout << "6. Save to CSV" << endl;
    cout << "7. Save & Exit" << endl;
    cout << "Enter your choice (1-7): ";

    if (!(cin >> choice)) {
      cout << "Invalid choice! Please enter a number." << endl;
      cin.clear();
      cin.ignore(10000, '\n');
      continue;
    }

    switch (choice) {
    case 1:
      payroll.addEmployee();
      break;
    case 2:
      payroll.displayEmployee();
      break;
    case 3:
      payroll.updateEmployee();
      break;
    case 4:
      payroll.deleteEmployee();
      break;
    case 5:
      payroll.generatePayroll();
      break;
    case 6:
      payroll.saveToCSV();
      break;
    case 7:
      payroll.saveToCSV();
      cout << "Exiting system. Goodbye!" << endl;
      break;
    default:
      cout << "Invalid option. Please choose between 1 and 7." << endl;
    }
  } while (choice != 7);

  return 0;
}
