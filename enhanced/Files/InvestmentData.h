#pragma once
#ifndef INVESTMENT_DATA_HEADER
#define INVESTMENT_DATA_HEADER

class InvestmentData {
public:
    InvestmentData();

    void SetInitialInvestment(double investment);
    void SetMonthlyDeposit(double deposit);
    void SetAnnualInterest(double interest);
    void SetYears(int years);
    void SetCurrency(char curr);

    double GetIntialInvestment() const;
    double GetMonthlyDeposit() const;
    double GetAnnualInterest() const;
    int GetYears() const;
    char GetCurrency() const;

private:
    double initial_investment;
    double monthly_deposit;
    double annual_interest;
    int number_of_years;
    char currency;
};

#endif
