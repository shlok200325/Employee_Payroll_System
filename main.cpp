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
        Employee *head=nullptr;
    public:
        Payroll()
        {
            head = nullptr;
        }
};
void addEmployee()
{

}

void displayEmployee()
{

}

void deleteEmployee()
{

}

void updateEmployee()
{

}
void generatePayroll()
{

}
void saveToCSV(string payroll)
{
    ofstream file("payroll.csv");

    while(!file.is_open())
    {
        cout << "Error opening file. Please try again." << endl;
        return;
    }
    file << "Employee_ID , Name , Salary" << endl;

    Employee *temp=head;
    while(temp!=nullptr)
    {
        file << temp->emp_id << " , " << temp->name << " , " << temp->salary << endl;
        temp = temp->next;
    }
    file.close();
    cout << "Payroll data saved to " << payroll << " sucessfully." << endl;
}
int main()
{
    addEmployee();
    displayEmployee();
    deleteEmployee();
    updateEmployee();
    generatePayroll();
    saveToCSV("payroll.csv");

    return 0;
}