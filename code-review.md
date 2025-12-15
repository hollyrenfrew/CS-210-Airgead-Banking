Algorithms and Data Structure
=============================

Introduction
------------

For the Algorithms and Data Structures category, I chose my Airgead Banking investment calculator, which I originally created for CS-210: Programming Languages. This project is a C++ console application that helps users explore how their investments grow over time based on starting balance, monthly deposits, interest rate, and duration in years.

I picked this artifact because it focuses directly on core logic, numeric processing, and looping structures. It also shows how I separate responsibilities across multiple classes while still keeping the algorithms straightforward and efficient. There is a clear opportunity to refine the internal data handling, improve numerical accuracy, and make the underlying algorithms more reusable and testable.

Existing Code Functionality
---------------------------

The Airgead program works in a straightforward way:

1.  The user is prompted for inputs such as currency symbol, initial investment, monthly deposit, interest, and number of years.
2.  The program stores these values inside an InvestmentData object.
3.  DataCalculation takes these values and computes monthly compounding interest.
4.  Two formatted yearly reports are printed:

    - One without monthly deposits.
    - One with monthly deposits.

6.  The user is asked if they want to run another calculation.

The primary C++ files include:

1. main.cpp

    - Controls the main loop, gets user input, calls the calculation, and asks if they want to continue.

2. InvestmentData.cpp

    - Stores and retrieves all user inputs.

3. UserInterface.cpp

    - Handles all input validation and formatting for prompts.

4. DataCalculation.cpp

    - Runs the core compounding interest algorithm and prints the annual reports.

Overall, the program successfully performs the investment projections it was designed to do.

Code Review Analysis
--------------------

### Structure

The structure is functional and clear. Each responsibility is separated into logical files. However, there are places where improvements are needed. For example, some code that belongs in validation functions is mixed directly into the user interaction loop. Screenshot this section:

![get_initial_investment example](screenshots/get_initial_investment.png)

*UserInterface.cpp*

### Documentation

The code is readable but lacks comments in key computational areas.

A great example to screenshot is in DataCalculation.cpp, inside YearlyBalances. The calculation algorithm itself is not commented even though it is the core logic.

![DataCalculation.cpp example](screenshots/documentation.png)

*DataCalculation.cpp*

### Variables

Variables are generally named well, but there are two concerns:

1.  User input is stored in int amount, which restricts decimals even though currency inputs are often decimals.

![example of in variable](screenshots/variables.png)

*UserInterface.cpp*

2.  Naming consistency can improve clarity, such as standardizing capitalization in getters (GetIntialInvestment has a typo, instead of Intial, it should be Initial).

![original typo example](screenshots/naming_inconsistency.png)

*DataCalculation.cpp*


### Loops and Branches

Loop control is complete and logical, but readability could be improved by using early continues or extracting code into helper methods. There is a missing initializer in the for loop, which is a small correctness issue:

![example of loop](screenshots/loop_example.png)

*DataCalculation.cpp*


### Target Areas for Improvement

Summarizing the findings, the most important enhancement opportunities include:

1. Fixing the yearly interest calculation so that it reflects proper monthly compounding.

2. Improving input validation. For example, rejecting negative numbers or unrealistic interest rates.

3. Refactoring repeated user input loops into a single reusable helper.

4. Increasing documentation around the algorithm's steps.

5. Renaming or standardizing functions with capitalization errors.

6. Extracting formatting logic into separate functions to improve readability.

7. Improving precision by avoiding unnecessary use of integers for money.

### Planned Enhancements

Here is what I will implement to enhance the Airgead program:

#### Algorithm Fixes

Correct the yearly interest calculation by removing the manual multiplication and letting the loop accumulate values naturally.

#### Input Validation

Add validation for:

-   negative values
-   unrealistic interest
-   extremely long year ranges

#### Refactoring

Create a generalized function to handle input collection to remove repeated loops.

#### Documentation

Add comments to describe each computational step within YearlyBalances.

#### Variable Improvements

Change int amount to double where appropriate and fix naming issues like GetIntialInvestment.

#### Separation of Concerns

Move the formatting code into helper functions, making YearlyBalances easier to read and extend.

#### Practical Impact

These enhancements will make the program:

-   more accurate
-   more maintainable
-   easier to test
-   more professional
-   more aligned with real-world programming practices

They also demonstrate better my understanding of algorithmic clarity, defensive coding, and modularity.

### Skills Demonstrated

Through these enhancements, I will show:

-   Algorithmic reasoning
-   Improved software design
-   Defensive programming
-   Accurate use of looping and mathematical logic
-   Clean documentation practices
-   Modular C++ class design

### Alignment with Course Outcomes

- **Outcome 3: Design and evaluate computing solutions using algorithmic principles while managing trade-offs.**

This is the strongest match for the Airgead enhancements. By fixing the compound interest algorithm, correcting the yearly interest accumulation, improving numeric precision, and restructuring repeated logic into modular functions, I am directly evaluating how the existing algorithm works and redesigning it to be more accurate and mathematically sound. These improvements show that I can analyze algorithmic behavior, identify where the logic breaks down, and make trade-offs between performance, readability, and accuracy.

- **Outcome 4: Demonstrate an ability to use well-founded and innovative techniques, skills, and tools in computing practices.**

Refactoring the input system to reduce repetition, correcting naming inconsistencies, and improving documentation all help demonstrate my ability to use cleaner and more maintainable coding practices. Updating the program to use better variable types, reorganizing loop logic, and extracting formatting routines also show that I can apply modern programming techniques to make legacy code more robust and professional.

- **Outcome 2: Design, develop, and deliver professional-quality written communication.**

This enhancement gives me the chance to document the algorithm in a clearer way. Adding comments to the core compounding logic and describing complicated sections of code helps future developers understand how the calculations work. The process of explaining these enhancements in my ePortfolio also supports this outcome, since it requires clear written communication about technical work.

Overall, the enhancements planned for the Airgead project give me the opportunity to show a strong understanding of algorithm design, data processing, and code quality. These directly align with program outcomes related to algorithmic evaluation, professional coding practices, and clear communication.

Conclusion
----------

To wrap everything up, the Airgead Banking Application still does exactly what it was originally built to do. It takes user input, processes compound interest over time, and prints a clean yearly report that helps users visualize their long-term investment growth. For a project written early in my program, it already shows solid structure, clear separation of responsibilities, and a straightforward algorithm that is easy to follow.

Through this review, I was able to step back and look at the code the way a professional developer would. I found several places where the logic can be strengthened, especially in the compound interest calculations and the formatting of the yearly output. There are also opportunities to improve input validation, reduce repeated code, and bring more clarity to the functions through better naming and documentation.

By correcting the calculation inconsistencies, simplifying the control flow, and turning repeated logic into reusable functions, I will move the project closer to a professional standard. These enhancements not only improve the accuracy and reliability of the program, but they also show my growth in algorithmic thinking, code organization, and maintainability.

Making these changes also gives me the chance to demonstrate important skills tied to the program outcomes. Improving the algorithm aligns with core computing principles, while restructuring and documenting the code reflects my ability to communicate clearly and work with technical material in a professional way.

Overall, this enhancement will turn Airgead into a polished, well-structured artifact that represents my abilities in both problem-solving and software refinement. It is satisfying to look back at something I built early on and bring it up to the level of work I can produce now.
