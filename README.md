🛠️ Appliance Repair Service Simulator

📌 General Description
This project is an Object-Oriented C++ application that simulates the daily operations of an appliance repair shop in discrete time (cycles). 
It manages employees, appliance models, and repair requests, providing a fully data-driven simulation configured exclusively via text files. 

The architecture is heavily modular, emphasizing Modern C++ paradigms, robust memory management, and clean object-oriented design.

🚀 Core Features
* **Discrete-Time Simulation Engine:** Simulates the repair process tick-by-tick, advancing global time, reducing active repair durations, and dynamically
assigning pending requests to available technicians based on capacity and specialization.
* **Hierarchical Management:** Handles different types of employees (Receptionists, Technicians, Supervisors) and appliances (Washing Machines, TVs, Fridges) using class inheritance.
* **Data-Driven Configuration:** The entire simulation (employees, specializations, repairable models, requests, and total cycles) is loaded from
structured text files, allowing multiple test scenarios without recompilation.

🧠 Technical Highlights (Modern C++ & OOP)
* **Memory Management:** Extensive use of `std::unique_ptr` for all dynamic object collections to ensure memory safety, prevent leaks, and eliminate
the need for explicit destructors. Objects are transferred using `std::move`.
* **Dynamic Polymorphism:** Utilizes virtual methods for generic displaying and salary calculations across different derived classes.
* **Type Safety:** Implements `dynamic_cast` to safely identify concrete employee types (e.g., dispatching tasks specifically to Technicians).
* **Robust Exception Handling:** Input parsing and business logic validations (CNP, timestamps, complexity constraints) throw `std::invalid_argument` exceptions, which are gracefully caught and reported.
* **STL Integration:** Uses `std::vector` as the primary dynamic collection and leverages `<algorithm>` and `<iomanip>` (`std::setw`, `std::setfill`) for data processing and formatted time display.

▶️ How to Run
1. Compile the project using a modern C++ compiler (C++14 or newer recommended):
   ```bash
   g++ -std=c++14 main.cpp citiri.cpp angajati/*.cpp electrocasnice/*.cpp -o service_sim
