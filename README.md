# 🧠 MiniDB – SQL-like Database Engine in C++

A lightweight SQL-like database engine built from scratch in C++.
This project demonstrates core database internals including parsing, execution, and persistent storage.

---

## 🚀 Features

* CREATE TABLE support
* INSERT INTO queries
* SELECT queries with WHERE filtering
* UPDATE queries
* DELETE queries
* File-based persistence (data stored on disk)
* In-memory execution (fast query performance)
* Modular architecture (Parser, Executor, Storage)

---

## 🏗️ Architecture

```
User Input (SQL)
        ↓
Parser (SQL → Command Struct)
        ↓
Executor (Decision Logic)
        ↓
Storage Engine
   ↙           ↘
Memory (Fast)   Disk (Persistent)
```

---

## 🧩 Component Breakdown

### 🔹 Parser

* Converts SQL-like input into structured commands
* Handles keywords: CREATE, INSERT, SELECT, UPDATE, DELETE
* Cleans tokens (removes `; , ( )`)

---

### 🔹 Executor

* Interprets parsed commands
* Routes to appropriate storage operations

---

### 🔹 Storage Engine

* Maintains in-memory database using:

  ```cpp
  std::map<std::string, std::vector<std::vector<std::string>>>
  ```
* Handles file persistence (`data/*.table`)
* Loads data at startup

---

## 📂 Project Structure

```
mini-db-engine-cpp/
 ├── src/
 │   ├── main.cpp
 │   ├── parser.cpp
 │   ├── executor.cpp
 │   ├── storage.cpp
 ├── include/
 │   ├── command.h
 │   ├── parser.h
 │   ├── executor.h
 │   ├── storage.h
 ├── data/
 ├── Makefile
 └── README.md
```

---

## ⚙️ Build & Run

### 🔧 Compile

```
make
```

### ▶️ Run

```
./db
```

---

## 🧪 Example Queries

### Create Table

```sql
CREATE TABLE users;
```

---

### Insert Data

```sql
INSERT INTO users VALUES (1, Adarsh);
INSERT INTO users VALUES (2, Rahul);
```

---

### Select Data

```sql
SELECT * FROM users;
```

---

### Select with WHERE

```sql
SELECT * FROM users WHERE id = 1;
```

---

### Update Data

```sql
UPDATE users SET name = Mohit WHERE id = 1;
```

---

### Delete Data

```sql
DELETE FROM users WHERE id = 2;
```

---

## 📁 Storage Format

Each table is stored as a file:

```
data/users.table
```

Example:

```
1 Adarsh
2 Rahul
```

---

## ⚡ Key Design Decisions

* **In-memory execution** for fast queries
* **File persistence** for durability
* **Modular architecture** for scalability
* **Simple parser** instead of full SQL grammar

---

## ⚠️ Limitations

* No schema validation (columns are assumed)
* Fixed column mapping (id, name)
* Limited SQL support (simplified syntax)
* No indexing or query optimization

---

## 🚀 Future Improvements

* Dynamic schema support
* Indexing (B-Tree / Hash Index)
* Query optimization
* Transaction support (ACID properties)
* Full SQL parser

---

## 🧠 Learning Outcomes

* Built a query parser from scratch
* Designed execution engine
* Implemented file-based storage
* Learned database internals
* Practiced modular system design in C++

---

## 📌 Author

**Adarsh Kumar**

---

## ⭐ Why This Project Matters

This project demonstrates understanding of:

* Database internals
* System design
* Data storage mechanisms
* Query processing

It goes beyond typical CRUD apps and showcases low-level engineering skills.

---
