#include <iostream>
#include "InvestmentData.h"

using namespace std;

/* Default constructor */
InvestmentData::InvestmentData() {
    initial_investment = 0;
    monthly_deposit = 0;
    annual_interest = 0;
    number_of_years = 0;
    currency = '$';
}

/* Mutators */
void InvestmentData::SetInitialInvestment(double investment) {
    initial_investment = investment;
}

void InvestmentData::SetMonthlyDeposit(double deposit) {
    monthly_deposit = deposit;
}

void InvestmentData::SetAnnualInterest(double interest) {
    annual_interest = interest;
}

void InvestmentData::SetYears(int years) {
    number_of_years = years;
}

void InvestmentData::SetCurrency(char curr) {
    currency = curr;
}

/* Accessors — now const-correct */
double InvestmentData::GetIntialInvestment() const {
    return initial_investment;
}

double InvestmentData::GetMonthlyDeposit() const {
    return monthly_deposit;
}

double InvestmentData::GetAnnualInterest() const {
    return annual_interest;
}

int InvestmentData::GetYears() const {
    return number_of_years;
}

char InvestmentData::GetCurrency() const {
    return currency;
}
