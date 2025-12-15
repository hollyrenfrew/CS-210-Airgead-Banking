\# Airgead Banking Investment Calculator



\## Overview



The Airgead Banking Investment Calculator is a C++ application that models compound interest growth over time based on user-defined inputs such as initial investment, monthly deposits, interest rate, and number of years. The project was originally created as a console application for \*\*CS-210: Programming Languages\*\* and later enhanced for \*\*CS-499\*\* to demonstrate advanced algorithmic design, data structure usage, and professional software practices.



\## Original Version



The original version:

\- Used annual-only compound interest

\- Printed results directly to the console

\- Did not store calculated data in structured containers

\- Had limited validation and documentation



The original implementation is preserved in the \*\*`original-release` branch\*\*.



\## CS‑499 Enhancements



For the capstone, this project was significantly expanded:



\### Algorithm Improvements

\- Replaced annual-only compounding with \*\*monthly compound interest\*\*

\- Used nested iteration with yearly aggregation

\- Improved numerical accuracy and realism



\### Data Structures

\- Introduced `std::vector<YearRecord>` to store yearly results

\- Used `vector::reserve()` for performance optimization

\- Added:

&nbsp; - `std::stack<double>` (LIFO)

&nbsp; - `std::queue<double>` (FIFO)

\- Implemented:

&nbsp; - `std::sort()` (O(n log n))

&nbsp; - `std::binary\_search()` (O(log n))



\### Software Design

\- Refactored logic for modularity and readability

\- Separated computation from presentation

\- Added documentation for complex algorithms



\## Skills Demonstrated



\- Algorithmic refinement and complexity analysis

\- Proper data structure selection and optimization

\- STL sorting and searching techniques

\- Defensive programming

\- Modular C++ design



\## Course Outcome Alignment



\- \*\*Outcome 3:\*\* Algorithm design and evaluation

\- \*\*Outcome 4:\*\* Use of well-founded computing techniques

\- \*\*Outcome 2:\*\* Professional communication via structured output



\## Repository Notes



\- `main` branch: enhanced version

\- `original-release` branch: original CS‑210 submission



\## Reflection



Enhancing this project reinforced my understanding of algorithm efficiency, data organization, and the trade-offs involved in real-world financial modeling. Transforming a simple console program into a structured and extensible system reflects my growth in algorithmic thinking and software professionalism.



