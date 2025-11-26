#pragma once
#ifndef USER_INTERFACE_HEADER
#define USER_INTERFACE_HEADER

#include "InvestmentData.h"

class UserInterface {
public:
    static InvestmentData UserInput(InvestmentData inputInvestment);
    static void inputError(std::string input);
    static bool ContinueQuestion();
};

#endif
