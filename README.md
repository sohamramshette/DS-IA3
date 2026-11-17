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
1. **Mid-Square Hashing Method:** A non-trivial hash function that squares the key, formats the result into a 4-digit zero-padded string, and extracts the middle digits modulo table size.
2. **Separate Chaining Collision Resolution:** Handling collisions by maintaining singly linked lists (chains) at each table bucket, preserving FIFO insertion order.
3. **Domain Real-World Application:** A real-world inventory management scenario tracking **Mango Varieties** using integer variety codes.

---

## 3. Personalization Parameters

| Parameter | Assigned Value |
| :--- | :--- |
| **Seed** | 69 |
| **Domain Scenario** | Mango Varieties Inventory |
| **Dataset Size** | 20 records |
| **Hashing Method** | Mid-Square Method |
| **Collision Resolution** | Separate Chaining (Singly Linked List) |
| **Proposed Table Size ($M$)** | 11 (Configurable constant) |

---

## 4. Personalized Dataset

The dataset contains 20 unique numeric keys generated using the linear congruential progression:
$$\text{key}[i] = (69 + 13 \times i) \pmod{100} \quad \text{for } i \in [0, 19]$$

### Generated Keys:
```
Index:  0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19
Key:   69  82  95   8  21  34  47  60  73  86  99  12  25  38  51  64  77  90   3  16
```

---

## 5. Directory Structure

```text
DS_IA3_HashTable/
│
├── src/
│   └── main.cpp               # C++ source code containing hash table implementation
│
├── tests/
│   └── test_hash_table.cpp    # Automated unit tests and invariant verification suite
│
├── docs/
│   ├── debugging_log.md       # Detailed technical log per commit, observations & fixes
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

### Compilation and Execution: Main Program
```bash
# Navigate to the project root
cd DS_IA3_HashTable

# Compile using g++ with strict warnings
g++ -std=c++11 -Wall -Wextra -pedantic src/main.cpp -o bin/hashtable.exe

# Execute
.\bin\hashtable.exe
```

### Compilation and Execution: Automated Test Suite
```bash
# Compile unit test suite
g++ -std=c++11 -Wall -Wextra -pedantic tests/test_hash_table.cpp -o bin/test_hash_table.exe

# Execute unit test suite
.\bin\test_hash_table.exe
```

---

## 7. Expected Final Hash Table & Statistics

### Expected Bucket Distribution:
```text
Index 0: 21 -> 38 -> 3
Index 1: NULL
Index 2: 95
Index 3: 99 -> 12 -> 16
Index 4: 34 -> 77
Index 5: 60 -> 51
Index 6: 82 -> 8 -> 86
Index 7: 25
Index 8: NULL
Index 9: 47 -> 64
Index 10: 69 -> 73 -> 90
```

### Summary Metrics:
- **Total Inserted Keys:** 20 / 20 (All keys accounted for)
- **Total Collisions:** 11
- **Empty Buckets:** 2 (Index 1 and Index 8)
- **Occupied Buckets:** 9
- **Load Factor ($\alpha$):** $\frac{N}{M} = \frac{20}{11} \approx 1.82$

---

## 8. Status & Phases
- **Phase 1: Project Setup & Environment Preparation** (Completed)
- **Phase 2: Core Data Structure & Hashing Implementation** (Completed)
- **Phase 3: Verification, Tracing & Unit Testing** (Completed)
- **Phase 4: Git Version Control & Commit Milestones** (Completed - 6 Commits)
- **Phase 5: Documentation Audit and Finalization** (Completed)
