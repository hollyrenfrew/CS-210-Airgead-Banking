# Airgead Banking Investment Calculator

## Overview

The Airgead Banking Investment Calculator is a C++ application that calculates and displays compound interest growth over time based on user inputs, including monthly deposits, interest rate, and investment duration. Originally created for **CS-210: Programming Languages**, this project evolved into a full desktop application with both algorithmic and UI enhancements.

## Original Functionality

- Prompted user for:
  - initial investment
  - monthly deposit
  - annual interest rate
  - number of years
- Calculated yearly compound interest
- Printed two formatted reports:
  - Without monthly deposits
  - With monthly deposits

## Enhancements (CS‑499)

For my CS‑499 capstone, I expanded this project to demonstrate algorithm refinement and data structure usage:

### ✨ Key Enhancements

- **Monthly Compound Interest Algorithm**
  - Replaced annual-only calculation
  - Uses nested loops and yearly aggregation
- **Dynamic Data Structure**
  - Results stored in `std::vector<YearRecord>`
  - Used `reserve()` for performance optimization
- **Sorting and Searching**
  - Used `std::sort` and `std::binary_search` with custom comparators
- **Auxiliary Structures**
  - Introduced `queue<double>` (FIFO) and `stack<double>` (LIFO) for transaction history
- **Windows GUI**
  - Light/Dark theme toggle
  - Splash screen and custom app icon
  - Live‑updating results table

## Skills Demonstrated

- Algorithm refinement and complexity analysis
- Use of STL containers (`vector`, `stack`, `queue`)
- Sorting and search implementation
- Separation of logic and UI
- Modular software structure

## Course Outcome Alignment

- **Outcome 3:** Design and evaluate computing solutions using algorithmic principles  
- **Outcome 4:** Use well‑founded techniques in computing practices  
- **Outcome 2:** Professional presentation and user‑oriented output

## Reflections

Enhancing this project deepened my understanding of:
- Monthly vs. annual compounding
- How data structures impact performance
- Bridging core logic with a usable GUI

Challenges included balancing responsiveness in the UI with intensive algorithms and ensuring numeric stability.
