#include <map>
#include <iostream>
#include <string>

void atm(){
    std::map<int, double> accounts;
    int currentAccount = -1;
    bool isLoggedIn = false;

    while(true){
        std::cout << "ATM Menu" << std::endl
                  << "1. Create Account" << std::endl
                  << "2. Login" << std::endl
                  << "3. Withdraw" << std::endl
                  << "4. Deposit" << std::endl
                  << "5. Check Balance" << std::endl
                  << "6. Exit" << std::endl
                  << "Choice: ";

        int choice;
        std::cin >> choice;

        switch(choice){
            case 1:{
                int accNumber;
                double balance;
                std::cout << "Enter account number: ";
                std::cin >> accNumber;
                std::cout << "Enter balance: ";
                std::cin >> balance;
                accounts[accNumber] = balance;
                std::cout << "Account created successfully!" << std::endl;
                break;
            }
            case 2:{
                int accNumber;
                std::cout << "Enter account number: ";
                std::cin >> accNumber;
                if(accounts.find(accNumber) != accounts.end()){
                    currentAccount = accNumber;
                    isLoggedIn = true;
                    std::cout << "Login successful!" << std::endl;
                }else{
                    std::cout << "Account not found!" << std::endl;
                }
                break;
            }
            case 3:{
                if(!isLoggedIn){
                    std::cout << "Please login first!" << std::endl;
                    break;
                }
                double amount;
                std::cout << "Enter amount to withdraw: ";
                std::cin >> amount;
                if(amount > accounts[currentAccount]){
                    std::cout << "Insufficient funds!" << std::endl;
                }else{
                    accounts[currentAccount] -= amount;
                    std::cout << "Withdrawal successful!" << std::endl;
                    std::cout << "Remaining balance: " << accounts[currentAccount] << std::endl;
                 }
                break;
            }
            case 4:{
                if(!isLoggedIn){
                    std::cout << "Please login first!" << std::endl;
                    break;
                }
                double amount;
                std::cout << "Enter amount to deposit: ";
                std::cin >> amount;
                accounts[currentAccount] += amount;
                std::cout << "Deposit successful!" << std::endl;
                std::cout << "Updated balance: " << accounts[currentAccount] << std::endl;
                break;
            }
            case 5:{
                if(!isLoggedIn){
                    std::cout << "Please login first!" << std::endl;
                    break;
                }
                std::cout << "Current balance: " << accounts[currentAccount] << std::endl;
                break;
            }
            case 6:
                return;
            default:
                std::cout << "Invalid choice!" << std::endl;
        }
    }
}