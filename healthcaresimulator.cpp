#include <iostream>
#include <queue>
#include <string>
#include <ctime>

using namespace std;

class Customer {
private:
    int queueNumber;
    string name;
    time_t arrivalTime;
public:
    Customer(int num, string n) : 
        queueNumber(num), 
        name(n), 
        arrivalTime(time(nullptr)) {}
    
    int getNumber() const { return queueNumber; }
    string getName() const { return name; }
    time_t getArrivalTime() const { return arrivalTime; }
};

class HealthcareCenterQueue {
private:
    queue<Customer> customers;
    int nextNumber = 1;

public:
    void addCustomer() {
        string name;
        cout << "Enter customer name: ";
        getline(cin, name);
        customers.push(Customer(nextNumber++, name));
        cout << "Added customer number: " << (nextNumber-1) << endl;
    }

    void callNext() {
        if(customers.empty()) {
            cout << "No customers waiting." << endl;
            return;
        }

        Customer next = customers.front();
        customers.pop();
        
        time_t now = time(nullptr);
        double waitTime = difftime(now, next.getArrivalTime());
        
        cout << "Calling customer: " << next.getName() << endl;
        cout << "Queue number: " << next.getNumber() << endl;
        cout << "Wait time: " << waitTime << " seconds" << endl;
    }
};

void healthCareSimulator() {
    HealthcareCenterQueue queue;
    string choice;

    while(true) {
        cout << "\n1. Add customer" << endl;
        cout << "2. Call next" << endl;
        cout << "3. Exit" << endl;
        cout << "Choice: ";
        
        getline(cin, choice);
        
        if(choice == "1") {
            queue.addCustomer();
        }
        else if(choice == "2") {
            queue.callNext();
        }
        else if(choice == "3") {
            break;
        }
    }
}