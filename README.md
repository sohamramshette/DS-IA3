# Hash Table Using Mid-Square Hashing and Separate Chaining

## 1. Student Details
- **Student Name:** Soham Balaji Ramshette
- **PRN:** 202501100069
- **Subject:** Data Structures (Course Code: 2310212 T)
- **Class / Program:** Second Year B.Tech Computer Engineering
- **College:** MIT Academy of Engineering, Alandi (Pune)
- **Project Title:** Hash Table Using Mid-Square Hashing and Separate Chaining

---

## 2. Project Overview
This project implements a Hash Table in standard C++ designed for practical understanding and viva evaluation in Data Structures. It demonstrates:
1. **Mid-Square Hashing Method:** A popular non-trivial hash function that squares the key and extracts the middle digits to determine the bucket index.
2. **Separate Chaining Collision Resolution:** Handling collisions by maintaining linked lists (chains) at each index in the hash table.
3. **Domain Real-World Application:** A real-world inventory management scenario tracking **Mango Varieties** using integer variety codes and variety details.

---

## 3. Personalization Parameters

| Parameter | Assigned Value |
| :--- | :--- |
| **Seed** | 69 |
| **Domain Scenario** | Mango Varieties |
| **Dataset Size** | 20 records |
| **Hashing Method** | Mid-Square Method |
| **Collision Resolution** | Separate Chaining (Linked List) |
| **Proposed Table Size** | 11 (Configurable constant) |

---

## 4. Personalized Dataset

The dataset contains 20 unique numeric keys generated using the linear congruential progression:
$$\text{key}[i] = (69 + 13 \times i) \pmod{100} \quad \text{for } i \in [0, 19]$$

### Generated Keys:
```
Index:  0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19
Key:   69  82  95   8  21  34  47  60  73  86  99  12  25  38  51  64  77  90   3  16
```

### Domain Mapping (Mango Varieties):
Each key maps to a distinct mango variety record (e.g., Key `69` $\rightarrow$ Alphonso, Key `82` $\rightarrow$ Kesar, Key `95` $\rightarrow$ Dasheri, Key `8` $\rightarrow$ Langra, etc.).

---

## 5. Directory Structure

```text
DS_IA3_HashTable/
│
├── src/
│   └── main.cpp               # C++ source code containing hash table implementation
│
├── docs/
│   ├── debugging_log.md       # Log of test cases, edge cases, and bug resolutions
│   └── trace_match_report.md  # Step-by-step mathematical trace matching manual calculations
│
├── screenshots/               # Output execution screenshots for demonstration/viva
│
├── README.md                  # Comprehensive project documentation
└── .gitignore                 # Standard C++ build artifact ignore file
```

---

## 6. How to Build and Run (C++)

### Prerequisites
- GCC / G++ (MinGW on Windows) or Clang or MSVC
- C++11 standard or higher

### Compilation Command
```bash
# Navigate to the project root
cd DS_IA3_HashTable

# Compile using g++
g++ -std=c++11 -Wall -Wextra src/main.cpp -o bin/hashtable.exe
```

### Execution Command
```bash
# Run on Windows PowerShell / Command Prompt
.\bin\hashtable.exe
```

---

## 7. Status & Phases
- **Phase 1: Project Setup & Environment Preparation** (Completed)
- **Phase 2: Core Data Structure & Hashing Implementation** (Pending Confirmation)
- **Phase 3: Verification, Tracing & Documentation** (Pending)
