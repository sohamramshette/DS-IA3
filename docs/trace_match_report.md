# Trace Match Report: Mid-Square Hashing & Separate Chaining

## Project & Student Information
- **Student Name:** Soham Balaji Ramshette
- **PRN:** 202501100069
- **Subject:** Data Structures (Course Code: 2310212 T)
- **College:** MIT Academy of Engineering, Alandi
- **Personalized Seed:** 69
- **Domain Scenario:** Mango Varieties Inventory
- **Table Size ($M$):** 11 (Configurable constant)
- **Dataset Size ($N$):** 20 keys

---

## 1. Dataset Generation Trace
The 20 keys are generated using the linear progression formula:
$$\text{key}[i] = (69 + 13 \times i) \pmod{100} \quad \text{for } i \in [0, 19]$$

| Step $i$ | Formula Calculation | Key Value | Mango Variety Associated |
| :---: | :--- | :---: | :--- |
| 0 | $(69 + 0) \pmod{100} = 69 \pmod{100}$ | **69** | Alphonso |
| 1 | $(69 + 13) \pmod{100} = 82 \pmod{100}$ | **82** | Kesar |
| 2 | $(69 + 26) \pmod{100} = 95 \pmod{100}$ | **95** | Dasheri |
| 3 | $(69 + 39) \pmod{100} = 108 \pmod{100}$ | **8** | Langra |
| 4 | $(69 + 52) \pmod{100} = 121 \pmod{100}$ | **21** | Chaunsa |
| 5 | $(69 + 65) \pmod{100} = 134 \pmod{100}$ | **34** | Totapuri |
| 6 | $(69 + 78) \pmod{100} = 147 \pmod{100}$ | **47** | Himsagar |
| 7 | $(69 + 91) \pmod{100} = 160 \pmod{100}$ | **60** | Banganapalli |
| 8 | $(69 + 104) \pmod{100} = 173 \pmod{100}$ | **73** | Badami |
| 9 | $(69 + 117) \pmod{100} = 186 \pmod{100}$ | **86** | Amrapali |
| 10 | $(69 + 130) \pmod{100} = 199 \pmod{100}$ | **99** | Mallika |
| 11 | $(69 + 143) \pmod{100} = 212 \pmod{100}$ | **12** | Neelam |
| 12 | $(69 + 156) \pmod{100} = 225 \pmod{100}$ | **25** | Raspuri |
| 13 | $(69 + 169) \pmod{100} = 238 \pmod{100}$ | **38** | Rajapuri |
| 14 | $(69 + 182) \pmod{100} = 251 \pmod{100}$ | **51** | Pairi |
| 15 | $(69 + 195) \pmod{100} = 264 \pmod{100}$ | **64** | Suvarnarekha |
| 16 | $(69 + 208) \pmod{100} = 277 \pmod{100}$ | **77** | Gulabkhas |
| 17 | $(69 + 221) \pmod{100} = 290 \pmod{100}$ | **90** | Fazli |
| 18 | $(69 + 234) \pmod{100} = 303 \pmod{100}$ | **3** | Vanraj |
| 19 | $(69 + 247) \pmod{100} = 316 \pmod{100}$ | **16** | Safeda |

---

## 2. Mid-Square Hashing Mathematical Trace

### Hash Function Definition:
1. $\text{square} = \text{key}^2$
2. Format as a 4-digit zero-padded string (`std::setw(4)`).
3. Extract characters at indices 1 and 2: $\text{midDigits} = \text{substr}(1, 2)$.
4. $\text{hashIndex} = \text{midDigits} \pmod{11}$.

| Step | Key | $\text{Key}^2$ | 4-Digit Padded | Mid Digits | Hash Index Calculation | Event Type | Chain at Bucket |
| :---: | :---: | :---: | :---: | :---: | :---: | :---: | :--- |
| 1 | **69** | 4761 | `4761` | 76 | $76 \pmod{11} = \mathbf{10}$ | `[NEW CHAIN]` | `69` |
| 2 | **82** | 6724 | `6724` | 72 | $72 \pmod{11} = \mathbf{6}$ | `[NEW CHAIN]` | `82` |
| 3 | **95** | 9025 | `9025` | 02 | $2 \pmod{11} = \mathbf{2}$ | `[NEW CHAIN]` | `95` |
| 4 | **8** | 64 | `0064` | 06 | $6 \pmod{11} = \mathbf{6}$ | `[COLLISION]` | `82 -> 8` |
| 5 | **21** | 441 | `0441` | 44 | $44 \pmod{11} = \mathbf{0}$ | `[NEW CHAIN]` | `21` |
| 6 | **34** | 1156 | `1156` | 15 | $15 \pmod{11} = \mathbf{4}$ | `[NEW CHAIN]` | `34` |
| 7 | **47** | 2209 | `2209` | 20 | $20 \pmod{11} = \mathbf{9}$ | `[NEW CHAIN]` | `47` |
| 8 | **60** | 3600 | `3600` | 60 | $60 \pmod{11} = \mathbf{5}$ | `[NEW CHAIN]` | `60` |
| 9 | **73** | 5329 | `5329` | 32 | $32 \pmod{11} = \mathbf{10}$ | `[COLLISION]` | `69 -> 73` |
| 10 | **86** | 7396 | `7396` | 39 | $39 \pmod{11} = \mathbf{6}$ | `[COLLISION]` | `82 -> 8 -> 86` |
| 11 | **99** | 9801 | `9801` | 80 | $80 \pmod{11} = \mathbf{3}$ | `[NEW CHAIN]` | `99` |
| 12 | **12** | 144 | `0144` | 14 | $14 \pmod{11} = \mathbf{3}$ | `[COLLISION]` | `99 -> 12` |
| 13 | **25** | 625 | `0625` | 62 | $62 \pmod{11} = \mathbf{7}$ | `[NEW CHAIN]` | `25` |
| 14 | **38** | 1444 | `1444` | 44 | $44 \pmod{11} = \mathbf{0}$ | `[COLLISION]` | `21 -> 38` |
| 15 | **51** | 2601 | `2601` | 60 | $60 \pmod{11} = \mathbf{5}$ | `[COLLISION]` | `60 -> 51` |
| 16 | **64** | 4096 | `4096` | 09 | $9 \pmod{11} = \mathbf{9}$ | `[COLLISION]` | `47 -> 64` |
| 17 | **77** | 5929 | `5929` | 92 | $92 \pmod{11} = \mathbf{4}$ | `[COLLISION]` | `34 -> 77` |
| 18 | **90** | 8100 | `8100` | 10 | $10 \pmod{11} = \mathbf{10}$ | `[COLLISION]` | `69 -> 73 -> 90` |
| 19 | **3** | 9 | `0009` | 00 | $0 \pmod{11} = \mathbf{0}$ | `[COLLISION]` | `21 -> 38 -> 3` |
| 20 | **16** | 256 | `0256` | 25 | $25 \pmod{11} = \mathbf{3}$ | `[COLLISION]` | `99 -> 12 -> 16` |

---

## 3. Final Hash Table Trace Match Verification

| Index | Theoretical Bucket Chain | Program Output Chain | Match Status |
| :---: | :--- | :--- | :---: |
| **0** | `21 -> 38 -> 3` | `21 -> 38 -> 3` | **EXACT MATCH** |
| **1** | `NULL` | `NULL` | **EXACT MATCH** |
| **2** | `95` | `95` | **EXACT MATCH** |
| **3** | `99 -> 12 -> 16` | `99 -> 12 -> 16` | **EXACT MATCH** |
| **4** | `34 -> 77` | `34 -> 77` | **EXACT MATCH** |
| **5** | `60 -> 51` | `60 -> 51` | **EXACT MATCH** |
| **6** | `82 -> 8 -> 86` | `82 -> 8 -> 86` | **EXACT MATCH** |
| **7** | `25` | `25` | **EXACT MATCH** |
| **8** | `NULL` | `NULL` | **EXACT MATCH** |
| **9** | `47 -> 64` | `47 -> 64` | **EXACT MATCH** |
| **10** | `69 -> 73 -> 90` | `69 -> 73 -> 90` | **EXACT MATCH** |

---

## 4. Invariant Checks
1. **Total Inserted Keys:** $3 + 0 + 1 + 3 + 2 + 2 + 3 + 1 + 0 + 2 + 3 = 20$ keys.
2. **Total Collisions:** $20 - 9 \text{ (occupied buckets)} = 11$ collisions.
3. **Empty Buckets:** Index 1 and Index 8 are confirmed empty (`NULL`).
4. **Load Factor ($\alpha$):** $\frac{N}{M} = \frac{20}{11} \approx 1.82$.
