# 📇 Contact Management System (Linked List in C)

## 📌 Overview

This project is a **Contact Management System** implemented in **C using a Singly Linked List**.
It allows users to store, manage, and manipulate contact details such as names and phone numbers dynamically.

The system uses **file handling (`contacts.txt`)** to maintain data across program executions.

---

## ⚙️ Features

* ➕ Add Contact
* ❌ Delete Contact
* ✏️ Update Contact
* 🔍 Search Contacts (Exact / Partial / Phone)
* 📋 View All Contacts
* 🔃 Sort Contacts (A–Z / Z–A)
* 📊 Display Statistics
* 🚫 Prevent Duplicate Entries

---

## 🧠 Data Structure Used

* **Singly Linked List**

  * Dynamic memory allocation using `malloc()`
  * Efficient insertion and deletion
  * Flexible data storage

---

## 💾 File Handling

* Data stored in: `contacts.txt`
* File is:

  * Loaded at program start
  * Updated after every operation

---

## 🛠 Technologies Used

* C Programming
* Linked List
* File Handling
* GCC Compiler

---

## ▶️ How to Run

### Compile

```bash
gcc contact.c -o contact
```

### Run

```bash
./contact
```

---

## 📂 Project Structure

```
ACTIVITY/
│
├── src/
│   ├── contact.c
│   └── contacts.txt
│
├── documents/
│   ├── 24006052_Aaron_24006054_Ann_Report.docx
│   └── 24006052_Aaron_24006054_Ann_PPT.pptx
│
└── README.md
```

---

## 📊 Sample Data

```
Joe mama,9517534862
Leoooo,985632147
Heavens,741852963
```

---

## ⚠️ Limitations

* Command-line based (no GUI)
* Linear search complexity → O(n)
* Not suitable for very large datasets

---

## 🚀 Future Improvements

* Add GUI interface
* Use database (MySQL/SQLite)
* Improve search performance

---

## 👨‍💻 Authors

* Aaron Geevarghese Mathews
* Ann Leo

---

## 📌 Conclusion

This project demonstrates the practical implementation of **linked lists and file handling** in solving a real-world problem.
