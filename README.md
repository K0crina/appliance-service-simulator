# Appliance Service Simulator

A discrete-time simulation of an appliance repair shop, implemented in C++14. The system manages employees, repairable appliance models and repair requests through a tick-based engine, configured entirely via text files — no recompilation needed to change scenarios.

---

## How It Works

Each simulation **cycle** (tick) represents one second of real operation:
- Active repair requests have their remaining duration decremented.
- Completed requests are finalized and the technician's earnings are updated.
- Pending requests in the queue are dispatched to the first available technician whose specializations match the appliance type and brand.

A **Receptionist** registers incoming requests. A **Technician** is assigned a request only if they hold a matching (type, brand) specialization and are currently idle. A **Supervisor** oversees the service. The simulation requires at least 3 technicians, 1 receptionist and 1 supervisor to run.

Repair cost and estimated duration are derived from the appliance's age and request complexity (1–5). Technician salary is base pay plus a percentage of their total completed repair value.

---

## Class Hierarchy

```
Angajat  (abstract)
├── Receptioner
├── Tehnician        ← holds specializations + completed repair value
└── Supervizor

Electrocasnic  (abstract)
├── MasinaSpalat     ← capacity (kg)
├── Televizor        ← diagonal + unit (cm/inch)
└── Frigider         ← has freezer compartment

Service              ← owns employees + repair requests (unique_ptr)
ServiceElectrocasnice ← registry of repairable models
CerereReparatie      ← owns the appliance, tracks status + duration
```

---

## Project Structure

```
.
├── main.cpp                        # Interactive menu + entry point
├── service.cpp / .h                # Core simulation engine
├── cerereReparatie.cpp / .h        # Repair request lifecycle
├── citiri.cpp                      # File parser — loads full test scenario
├── angajati/
│   ├── angajat.cpp / .h            # Abstract base employee
│   ├── receptioner.cpp / .h
│   ├── tehnician.cpp / .h
│   └── supervizor.cpp / .h
├── electrocasnice/
│   ├── electrocasnic.cpp / .h      # Abstract base appliance
│   ├── masinaSpalat.cpp / .h
│   ├── televizor.cpp / .h
│   ├── frigider.cpp / .h
│   └── serviceElectrocasnice.cpp / .h
└── tests/
    ├── test1.txt ... test5.txt     # Scenario files
```

---

## Build & Run

```bash
g++ -std=c++14 main.cpp citiri.cpp angajati/*.cpp electrocasnice/*.cpp cerereReparatie.cpp service.cpp -o service_sim
./service_sim
```

The interactive menu has three submenus:

| Menu | Actions |
|---|---|
| Employee Management | List all, search by CNP, delete by CNP |
| Appliance Management | List repairable models, add model manually |
| Request Processing | Load test file, view requests, run one cycle, run all cycles |

---

## Test File Format

Each test file is a plain text scenario with four sections separated by blank lines:

```
# 1. Employees  — ROLE;id;surname;name;CNP;hire_date;city
RECEPTIONER;1;Popescu;Ana;2900101052016;01.09.2020;Bucuresti
TEHNICIAN;2;Ionescu;Mihai;1800315123016;15.03.2015;Cluj

# 2. Technician specializations  — techId;ApplianceType;Brand
2;MasinaSpalat;Bosch
3;Frigider;Samsung

# 3. Repairable appliance models  — Type;Brand;Model;Year;Price;[extra]
MasinaSpalat;Bosch;Wash7;2022;2000;7          # extra = capacity (kg)
Televizor;LG;Smart55;2023;2500;55;inch         # extra = diagonal + unit
Frigider;Samsung;CoolX;2021;1800;1             # extra = 1/0 (has freezer)

# 4. Repair requests  — id;timestamp;Type;Brand;Model;Year;Price;complexity;receptionistId
1;05.01.2026 10:00:00;Frigider;Samsung;CoolX;2021;1800;2;1

# 5. Number of simulation cycles (last line)
15
```

---

## Technical Notes

- All polymorphic object collections use `std::unique_ptr` — no manual `delete`, no memory leaks.
- Objects are transferred between containers with `std::move`.
- `dynamic_cast` is used to safely downcast `Angajat*` to `Tehnician*` when dispatching repair requests.
- Input validation (CNP format, timestamps, complexity bounds) throws `std::invalid_argument`, caught and reported at the call site.
- Time display uses `<iomanip>` (`std::setw` / `std::setfill`) for `HH:MM:SS` formatting.
