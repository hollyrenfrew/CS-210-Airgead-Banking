#pragma once
#ifndef DATA_CALCULATIONS_HEADER
#define DATA_CALCULATIONS_HEADER

#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include "InvestmentData.h"

/* Struct for enhanced algorithm */
struct YearRecord {
    int year;
    double endingBalance;
    double interestEarned;
};

class DataCalculation {
public:
    DataCalculation(InvestmentData investmentData);

    // Enhanced monthly-compound algorithm
    static std::vector<YearRecord> CalculateYearlyResults(
        const InvestmentData& data,
        bool includeMonthlyDeposits,
        std::queue<double>& transactionHistory,
        std::stack<double>& reverseHistory
    );

    // NEW: sorted results
    static void SortResultsByBalance(std::vector<YearRecord>& results);

    // NEW: binary search on year (requires sorted order)
    static bool SearchForYear(const std::vector<YearRecord>& results, int targetYear);

private:
    int yearWidth = 6;
    int balanceWidth = 24;
    int interestWidth = 30;
    int totalWidth = yearWidth + balanceWidth + interestWidth;
};

#endif
