#include<iostream>
#include<string>
#include<fstream>

using namespace std;

struct Employee
{
    int emp_id;
    string name;
    double salary;
    Employee*next;

    Employee(int id,string n,double s)
    {
        emp_id = id;
        name = n;
        salary = s;
        next = nullptr;
    }
};
class Payroll
{
    private:
        Employee *head;
    public:
        Payroll()
        {
            head = nullptr;
        }
        void addEmployee()
        {
            int id;
            string n;
            double s;
            cout << "\n--- Add New Employee ---" << endl;
            cout << "Enter Employee ID: ";
            cin >> id;

            cout << "Enter Employee Name: ";
            cin >> n;

            cout << "Enter Base Salary: ";
            cin >> s;

            Employee* newNode = new Employee(id, n, s);

            if (head == nullptr)
            {
                head = newNode;
                cout << "Success: " << n << " added as the first employee!" << endl;
                return;
            }
           Employee* current = head;
           while (current->next != nullptr)
           {
            current = current->next;
           }
        current->next = newNode;
        cout << "Success: " << n << " added to the system!" << endl;
        }
        void displayEmployee()
        {
            if(head==nullptr)
            {
                cout << "No employees found in system." << endl;
                endl;
                return;
            } 
            Employee *temp = head;

            while (temp != nullptr)
            {
                cout<<"Emmployee ID :"<<temp->emp_id
                << endl;
                cout<<"name  :"<<temp->name<<
                endl;
                cout<<"Salary :"<<temp->salary<<
                endl;
                cout<<"-----------------------------"<<endl;

                temp = temp->next;

            }
        

        }
        void deleteEmployee()
        {

        }
        void updateEmployee()
        {

        }
        void generatePayroll()
        {
            if(head==nullptr)
            {
                cout << "No employees found in system." << endl;
                return;
            }
            EmployeeNode *current = head;
            double TaxRate = 0.15;
            double totalPayout = 0.0;

            cout << "\n---Payroll Report---" << endl;

            while(current!=nullptr)
            {
                double deduction = current->salary * TaxRate;
                double netSalary = current->salary - deduction;
                totalPayout += netSalary;

                cout << "Employee ID: " << current->emp_id << "|" << "Name: " << current->name << endl;
                cout << "Gross Salary: " << current->salary << endl;
                cout << "Tax Deduction: " << deduction << endl;
                cout << "Net Salary: " << netSalary << endl;
            }
            cout << "Total Company Payout: " << totalPayout << endl;
            cout << " == == == == == == == == == == == == == == == == = "<<endl;
        }
        void saveToCSV()
        {
            ofstream file("payroll.csv");
            if (file.is_open())
            {
                EmployeeNode *current = head;
                while (current != nullptr)
                {
                    file << current->emp_id << "," << current->name << "," << current->netSalary << endl;
                    current = current->next;
                }
                file.close();
            }
            cout << "Payroll data saved to payroll.csv successfully!" << endl;
        }
};
int main()
{
    Payroll payroll;
    payroll.addEmployee();
    payroll.displayEmployee();
    payroll.deleteEmployee();
    payroll.updateEmployee();
    payroll.generatePayroll();
    payroll.saveToCSV();

    return 0;
}