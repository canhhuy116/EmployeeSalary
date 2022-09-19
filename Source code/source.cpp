#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
#include<string>

using namespace std;

class employee {
protected:
	string name;
	double salary;
	int total;
public:
	employee();
	static employee* makeEmployee(int choice);
	virtual void printFinalPayment();
	virtual double getTotalSalary();
	void setName(string name);
	void setSalary(double salary);
	void setTotal(int total);
	string getName();
	double getSalary();
	int getTotal();
	virtual void setBonus(double bonus);
};

class employeesCompanyManager {
private:
	vector<employee*> employees;
public:
	employeesCompanyManager();
	void readFileListEmployees();
	void printListFinalPayment();
};

int main() {
	employeesCompanyManager companyOmega;
	// read file
	companyOmega.readFileListEmployees();
	// print total salary of employee
	companyOmega.printListFinalPayment();
	return 0;
}

class DailyEmployee: public employee {
public:
	void printFinalPayment();
};

class HourlyEmployee : public employee {
public:
	void printFinalPayment();
};

class ProductsEmployee : public employee {
public:
	void printFinalPayment();
};

class Manager :public employee {
private:
	double bonus;
public:
	Manager();
	void printFinalPayment();
	double getTotalSalary();
	void setBonus(double bonus);
};

employee::employee()
	:name(""), salary(0), total(0)
{
}

employee* employee::makeEmployee(int choice) {
	switch (choice) {
	case 1:
		return new DailyEmployee();
		break;
	case 2:
		return new HourlyEmployee();
		break;
	case 3:
		return new ProductsEmployee();
		break;
	case 4:
		return new Manager();
		break;
	default:
		return nullptr;
		break;
	}
}

void employee::printFinalPayment()
{
	return;
}

double employee::getTotalSalary()
{
	return total*salary;
}

void employee::setName(string name)
{
	this->name = name;
}

void employee::setSalary(double salary)
{
	this->salary = salary;
}

void employee::setTotal(int total)
{
	this->total = total;
}

string employee::getName()
{
	return name;
}

double employee::getSalary()
{
	return salary;
}

int employee::getTotal()
{
	return total;
}

void employee::setBonus(double bonus)
{
	return;
}

void DailyEmployee::printFinalPayment()
{
	cout << "The payment for" << name << " daily employee will be " << salary << "$ x " << total << " = " << getTotalSalary() << "$\n";
}

void HourlyEmployee::printFinalPayment()
{
	cout << "The payment for" << name << " hourly employee will be " << salary << "$ x " << total << " = " << getTotalSalary() << "$\n";
}

void ProductsEmployee::printFinalPayment()
{
	cout << "The payment for" << name << " product employee will be " << salary << "$ x " << total << " = " << getTotalSalary() << "$\n";
}

Manager::Manager()
	:bonus(0)
{}

void Manager::printFinalPayment()
{
	cout << "The payment for" << name << " manager employee will be " << salary << "$ x " << total << " + " << bonus << "$ = " << getTotalSalary() << "$\n";
}

double Manager::getTotalSalary()
{
	return salary * total + bonus;
}

void Manager::setBonus(double bonus)
{
	this->bonus = bonus;
}

employeesCompanyManager::employeesCompanyManager()
{}

void employeesCompanyManager::readFileListEmployees()
{
	FILE* stream;
	if ((stream = freopen("November2021.txt", "rt", stdin)) == nullptr)
		return;
	
	int choice = 0;

	employee* temp = new employee;
	string typeEmployee;
	string str;
	double k;
	double k1;

	while (!feof(stdin)) {
		getline(cin, typeEmployee, ':');
		if (typeEmployee == "DailyEmployee")
			choice = 1;
		else if (typeEmployee == "HourlyEmployee")
			choice = 2;
		else if (typeEmployee == "ProductEmployee")
			choice = 3;
		else if (typeEmployee == "Manager")
			choice = 4;

		employees.push_back(employee::makeEmployee(choice));

		getline(cin, str);
		temp->setName(str);
		if (choice == 4) {
			getline(cin, str, '=');
			cin >> k1;
			employees.back()->setBonus(k1);
		}
		getline(cin, str, '=');
		cin >> k1;
		temp->setSalary(k1);
		getline(cin, str, '=');
		cin >> k;
		temp->setTotal(k);
		employees.back()->setName(temp->getName());
		employees.back()->setSalary(temp->getSalary());
		employees.back()->setTotal(temp->getTotal());
		getline(cin, str);
	}
}

void employeesCompanyManager::printListFinalPayment()
{
	size_t size = employees.size();
	for (int i = 0; i < size; i++) {
		employees[i]->printFinalPayment();
	}
}