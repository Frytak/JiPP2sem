#include <string>

class BankAccount {
    private:
        static int nextId;

        int id;
        std::string owner;
        double balance;

    public:
        BankAccount(std::string owner, double balance);
        void deposit(double amount);
        double withdraw(double amount);
        double getBalance() const;
        int getId() const;
        void print() const;
};
