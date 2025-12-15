#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>

using namespace std;

#include "DataCalculation.h"

/*
 * Constructor – Uses enhanced monthly compounding, sorting,
 * searching, stack/queue history, and reserve().
 */
DataCalculation::DataCalculation(InvestmentData investmentData) {

    char symbol = investmentData.GetCurrency();

    // HISTORY STRUCTURES
    queue<double> transactionHistory;   // FIFO: Jan → Feb → Mar...
    stack<double> reverseHistory;       // LIFO: last month first

    // ------------------------------------------
    // 1: Without deposits
    // ------------------------------------------
    cout << setw(totalWidth) << "Balance and Interest Without Monthly Deposits" << endl;
    cout << string(totalWidth, '=') << endl;

    vector<YearRecord> noDeposits = CalculateYearlyResults(
        investmentData,
        false,
        transactionHistory,
        reverseHistory
    );

    // Sort by ending balance
    SortResultsByBalance(noDeposits);

    for (const auto& rec : noDeposits) {
        cout << setw(yearWidth) << rec.year;

        stringstream iStream;
        iStream << fixed << setprecision(2) << rec.interestEarned;
        cout << setw(interestWidth) << symbol + iStream.str();

        stringstream bStream;
        bStream << fixed << setprecision(2) << rec.endingBalance;
        cout << setw(balanceWidth) << symbol + bStream.str();

        cout << endl;
    }

    cout << endl << endl;

    // ------------------------------------------
    // 2: With deposits
    // ------------------------------------------
    cout << setw(totalWidth) << "Balance and Interest With Monthly Deposits" << endl;
    cout << string(totalWidth, '=') << endl;

    queue<double> transactionHistory2;
    stack<double> reverseHistory2;

    vector<YearRecord> withDeposits = CalculateYearlyResults(
        investmentData,
        true,
        transactionHistory2,
        reverseHistory2
    );

    SortResultsByBalance(withDeposits);

    for (const auto& rec : withDeposits) {
        cout << setw(yearWidth) << rec.year;

        stringstream iStream;
        iStream << fixed << setprecision(2) << rec.interestEarned;
        cout << setw(interestWidth) << symbol + iStream.str();

        stringstream bStream;
        bStream << fixed << setprecision(2) << rec.endingBalance;
        cout << setw(balanceWidth) << symbol + bStream.str();

        cout << endl;
    }

    cout << endl;

    // Optional: demonstrate binary-search usage
    int searchYear = 3;
    if (SearchForYear(withDeposits, searchYear)) {
        cout << "Year " << searchYear << " was found in the results." << endl;
    }
    else {
        cout << "Year " << searchYear << " was NOT found in the results." << endl;
    }
}

/*
 * Enhanced monthly compound interest algorithm
 * Adds:
 *  - queue logging (FIFO)
 *  - stack logging (LIFO)
 *  - vector::reserve() for performance
 */
vector<YearRecord> DataCalculation::CalculateYearlyResults(
    const InvestmentData& data,
    bool includeMonthlyDeposits,
    queue<double>& transactionHistory,
    stack<double>& reverseHistory
) {
    vector<YearRecord> results;

    // Enhancement: reserve capacity (Big-O improvement)
    results.reserve(data.GetYears());

    int totalMonths = data.GetYears() * 12;
    double balance = data.GetIntialInvestment();
    double monthlyRate = (data.GetAnnualInterest() / 100.0) / 12.0;
    double monthlyDeposit = includeMonthlyDeposits ? data.GetMonthlyDeposit() : 0;

    double yearlyInterestAcc = 0;

    for (int month = 1; month <= totalMonths; month++) {

        // Record deposit in queue + stack (FIF0 and LIFO)
        balance += monthlyDeposit;
        transactionHistory.push(monthlyDeposit);
        reverseHistory.push(monthlyDeposit);

        double interest = balance * monthlyRate;
        balance += interest;
        yearlyInterestAcc += interest;

        if (month % 12 == 0) {
            int year = month / 12;

            results.push_back({
                year,
                balance,
                yearlyInterestAcc
                });

            yearlyInterestAcc = 0;
        }
    }

    return results;
}

/*
 * Enhancement: Sort by ending balance (ascending order)
 * O(n log n)
 */
void DataCalculation::SortResultsByBalance(vector<YearRecord>& results) {
    sort(results.begin(), results.end(),
        [](const YearRecord& a, const YearRecord& b) {
            return a.endingBalance < b.endingBalance;
        });
}

/*
 * Enhancement: Binary search for year value
 * Requires results be sorted by year or transformed appropriately.
 */
bool DataCalculation::SearchForYear(const vector<YearRecord>& results, int targetYear) {
    return binary_search(
        results.begin(),
        results.end(),
        targetYear,
        [](const YearRecord& rec, int value) {
            return rec.year < value;
        }
    );
}
