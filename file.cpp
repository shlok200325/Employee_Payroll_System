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
    public:

    private:

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
void saveTOCVS(string payroll)
{
    ofstream file("payroll.csva");

    while(!file.is_open())
    {
        cout << "Error opening file. Please try again." << endl;
        return;
    }
    file << "Employee_ID , Name , Salary" << endl;

    while(temp!=nullptr)
    {
        file << temp->emp_id << " , " << temp->name << " , " << temp->salary << endl;
        temp = temp->next;
    }
    file.close();
    cout << "Payroll data saved to " << payroll.csv << " sucessfully." << endl;
}
int main()
{
    addEmployee();
    deleteEmployee();
    updateEmployee();
    generatePayroll();
    saveTOCVS("payroll.csv");

    return 0;
}