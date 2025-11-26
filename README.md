# Airgead Banking Investment Calculator

This project is an enhanced version of the Airgead Banking Investment Calculator developed for the CS-210 course. It serves as an example of applying algorithms and data structures to solve real-world problems in financial forecasting.

## Category Two: Algorithms and Data Structures

### Artifact Selection and Origin

The selected artifact is the Airgead Banking Investment Calculator, originally developed as part of the CS-210 course curriculum. Its core functionality involves computing investment growth over a given number of years, factoring in monthly deposits and compound interest. This artifact was chosen because it provides an ideal platform for applying algorithmic principles and structured data storage.

### Enhancement Plan

To improve alignment with the algorithms and data structures category, the calculator's logic has been upgraded to use monthly compound interest calculations instead of simple annual calculations. The program now uses a dynamic data structure, specifically a vector of custom YearRecord structs, to store each year's results. This provides structured, scalable access to financial data.

### Pseudocode for Enhanced Logic

```
balance = initial_investment
monthlyRate = (annual_interest / 100) / 12
results = empty vector

for each year in total_years:
    yearlyInterest = 0

    for each month in 12:
        balance += monthly_deposit
        monthlyInterest = balance * monthlyRate
        balance += monthlyInterest
        yearlyInterest += monthlyInterest

    store (year, balance, yearlyInterest) in vector
```

## Skill Demonstration and Course Outcome Alignment

### Skills Demonstrated

This enhancement demonstrates skills in algorithm design, data structure implementation, and modular development. Specifically:

* Algorithm optimization for monthly compounding
* Use of the vector container to store structured records
* Refactoring for maintainability and clarity

### Course Outcomes Met

* Design and evaluate computing solutions that solve a given problem using algorithmic principles and computer science practices and standards appropriate to its solution, while managing the trade-offs involved in design choices.
* Demonstrate an ability to use well-founded and innovative techniques, skills, and tools in computing practices for the purpose of implementing computer solutions that deliver value and accomplish industry-specific goals.

## Build Instructions

1. Open the solution in Visual Studio.
2. Ensure that all `.cpp`, `.h`, and `resource.rc` files are included.
3. Make sure you have linked `comctl32.lib` and `dwmapi.lib` under project properties.
4. Press `Ctrl + Shift + B` to build.
5. Run the `Airgead Investment Calculator.exe` from the output directory.

## File Contents

* main.cpp: Core application logic and UI
* InvestmentData.h / .cpp: Holds user input and investment parameters
* DataCalculation.h / .cpp: Performs the enhanced compound interest calculations
* resource.h / .rc: Contains GUI assets like icons and splash screen

## Notes

* The application includes a splash screen with fade-in and fade-out effects
* A true dark mode is available, featuring dark gray backgrounds and light gray text
* The application logic has been enhanced to align with advanced data structure and algorithm requirements
