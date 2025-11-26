#include <iostream>
#include <limits>

using namespace std;

#include "UserInterface.h"

void UserInterface::inputError(string input) {
    cerr << "Wrong input... Please enter a valid " << input << endl;
    cin.clear();
    while (cin.get() != '\n');
}

InvestmentData UserInterface::UserInput(InvestmentData inputInvestment) {
    int years = 0;
    double amount = 0;
    bool validator = false;
    char symbol = ' ';

    cout << string(42, '*') << endl;
    cout << string(15, '*') << " Data Input " << string(15, '*') << endl;

    /* Currency symbol */
    while (!validator) {
        cout << "Currency Symbol: ";
        if (cin >> symbol) {
            inputInvestment.SetCurrency(symbol);
            validator = true;
        }
        else {
            inputError("symbol");
        }
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    validator = false;

    /* Initial investment */
    while (!validator) {
        cout << "Initial Investment Amount: ";
        if (cin >> amount) {
            inputInvestment.SetInitialInvestment(amount);
            validator = true;
        }
        else {
            inputError("number");
        }
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    validator = false;

    /* Monthly deposit */
    while (!validator) {
        cout << "Monthly Deposit: ";
        if (cin >> amount) {
            inputInvestment.SetMonthlyDeposit(amount);
            validator = true;
        }
        else {
            inputError("number");
        }
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    validator = false;

    /* Annual interest */
    while (!validator) {
        cout << "Annual Interest (%): ";
        if (cin >> amount) {
            inputInvestment.SetAnnualInterest(amount);
            validator = true;
        }
        else {
            inputError("number");
        }
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    validator = false;

    /* Years */
    while (!validator) {
        cout << "Years: ";
        if (cin >> years) {
            inputInvestment.SetYears(years);
            validator = true;
        }
        else {
            inputError("number");
        }
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    return inputInvestment;
}

bool UserInterface::ContinueQuestion() {
    char answer = ' ';
    cout << endl;

    while (answer != 'y' && answer != 'Y' &&
        answer != 'n' && answer != 'N') {
        cout << "Would you like to continue? Enter y or n." << endl;
        cin >> answer;
        while (cin.get() != '\n');
    }

    return !(answer == 'n' || answer == 'N');
}
