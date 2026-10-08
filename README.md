# MiniDB — SQL-like Database Engine in C++

> **A small database engine built from scratch in C++ to explore parsing, query execution, in-memory storage, and file persistence.**

MiniDB is an **educational database-engine project**, not a production SQL database. It implements a deliberately small SQL-like command set and connects a parser, executor, in-memory store, and simple on-disk representation.

The goal is to understand the mechanics behind a database system by building the core path instead of hiding it behind an existing database library.

> **Status:** Working educational prototype  
> **Focus:** Database internals and C++ systems programming  
> **Scope:** Simplified SQL-like syntax with a fixed two-column data model

---

## What it implements

- `CREATE TABLE`
- `INSERT INTO`
- `SELECT`
- `SELECT ... WHERE`
- `UPDATE ... WHERE`
- `DELETE ... WHERE`
- In-memory table storage
- File-backed table data
- Loading persisted rows when the process starts
- Separate parser, executor, and storage components

The implementation intentionally keeps the SQL surface small. It is useful for learning query processing, but it is **not compatible with standard SQL**.

---

## Architecture

```text
                 User
                  │
                  ▼
           SQL-like command
                  │
                  ▼
        ┌──────────────────┐
        │      Parser      │
        │ input → Command  │
        └────────┬─────────┘
                 │
                 ▼
        ┌──────────────────┐
        │     Executor     │
        │ command routing  │
        └────────┬─────────┘
                 │
                 ▼
        ┌──────────────────┐
        │  Storage Engine  │
        │                  │
        │  in-memory db    │
        │       ↕          │
        │  .table files    │
        └──────────────────┘
```

### Parser

`src/parser.cpp` converts the input into a `Command` structure containing:

- command type
- table name
- values
- optional `WHERE` column/value
- update column/value

The parser uses token-based string processing rather than a full SQL grammar.

### Executor

`src/executor.cpp` dispatches parsed commands to the corresponding storage operation.

### Storage

`src/storage.cpp` maintains the active database as:

```cpp
std::map<
    std::string,
    std::vector<std::vector<std::string>>
>
```

Rows are kept in memory while the process runs. Table contents are also written to `data/<table>.table` files and loaded when the program starts.

---

## Current data model

The current implementation is intentionally simple:

```text
Table
 └── rows
      ├── column 0 → id
      └── column 1 → name
```

The `id` and `name` mapping is hard-coded in the current storage implementation.

There is currently **no general schema/catalog system**. `CREATE TABLE users;` creates the table storage but does not parse or persist a real column definition.

---

## Example session

Build and start MiniDB:

```bash
make
./db
```

Then enter commands such as:

```sql
CREATE TABLE users;

INSERT INTO users VALUES (1, Adarsh);
INSERT INTO users VALUES (2, Rahul);

SELECT * FROM users;

SELECT * FROM users WHERE id = 1;

UPDATE users SET name = Mohit WHERE id = 1;

DELETE FROM users WHERE id = 2;
```

Exit with:

```text
Exit
```

### Expected data

After the operations above, the persisted table is conceptually:

```text
1 Mohit
```

The exact console output is intentionally simple because this project is focused on the engine internals rather than a polished SQL client.

---

## Storage format

Tables are stored under `data/`:

```text
data/
└── users.table
```

A table file contains whitespace-separated row values, for example:

```text
1 Adarsh
2 Rahul
```

This is a deliberately minimal persistence format.

It should **not** be confused with a WAL, page format, binary storage engine, or crash-safe transactional storage system.

---

## Build

### Requirements

- Linux/macOS environment with a C++17 compiler
- GNU Make
- Standard C++17 filesystem support

The provided Makefile uses:

```text
g++
-std=c++17
-Wall
-pthread
```

### Commands

```bash
make
./db
```

Clean the binary:

```bash
make clean
```

---

## Repository structure

```text
Database-engine/
├── include/
│   ├── command.h
│   ├── executor.h
│   ├── parser.h
│   └── storage.h
├── src/
│   ├── main.cpp
│   ├── parser.cpp
│   ├── executor.cpp
│   └── storage.cpp
├── data/
├── Makefile
└── README.md
```

---

## Engineering trade-offs

MiniDB deliberately favors **clarity over completeness**.

| Decision | Current approach | Trade-off |
|---|---|---|
| Query parsing | Token-based parser | Simple, but limited syntax |
| Rows | `vector<vector<string>>` | Easy to understand, weak typing |
| Table lookup | `std::map` | Simple metadata lookup |
| Row lookup | Linear scan | Simple, but no indexes |
| Persistence | Text files | Easy to inspect, not crash-safe |
| Schema | Fixed `id/name` mapping | Small implementation surface |
| Transactions | None | No atomic multi-operation guarantees |
| Concurrency | None | Single-process, single-threaded model |

---

## Limitations

This project should be evaluated as a learning engine, not as a database replacement.

Current limitations include:

- No general SQL grammar.
- No dynamic schemas or column definitions.
- Fixed `id` / `name` column mapping.
- String-only values.
- No type system.
- No primary keys or constraints.
- No indexes.
- No query optimizer.
- No joins, aggregation, ordering, grouping, or subqueries.
- No transactions or ACID guarantees.
- No concurrency control.
- No write-ahead log or crash recovery.
- Text-file persistence is not designed for concurrent or crash-safe writes.
- No formal benchmark suite yet.
- No automated test suite is currently exposed by the repository.

These constraints are intentional scope boundaries for the current prototype.

---

## Roadmap

The next useful steps, in increasing complexity:

1. Add parser and storage tests.
2. Introduce a real table/schema catalog.
3. Add typed values and validation.
4. Add proper error handling for malformed commands and invalid rows.
5. Replace linear scans with indexes.
6. Introduce a page-oriented storage layer.
7. Add a query planner/executor abstraction.
8. Add transactions and recovery.
9. Add concurrency control.
10. Build repeatable benchmarks for scans, inserts, updates, and indexed lookups.

The goal is not to recreate PostgreSQL feature-for-feature. The goal is to use a small engine to progressively understand **how database internals are built**.

---

## Why this project matters

MiniDB demonstrates practical C++ work across:

- parsing
- command representation
- query execution
- in-memory data structures
- persistence
- modular system design
- low-level file I/O

It is a supporting systems project in the portfolio, complementing larger distributed/backend projects by showing interest in **what happens underneath application-level database APIs**.

---

## Author

**Adarsh Kumar**

C++ • Database Internals • Backend Systems • Systems Programming

---

## License

MIT — see [LICENSE](./LICENSE).
