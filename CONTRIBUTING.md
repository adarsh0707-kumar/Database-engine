# Contributing to MiniDB

Thanks for your interest in contributing to **MiniDB** — a lightweight SQL-like database engine built from scratch in C++. This project exists mainly as a learning/demo project showing database internals (parsing, execution, and file-based storage), so contributions that improve clarity, correctness, and functionality are very welcome.

## Table of Contents

- [Code of Conduct](#code-of-conduct)
- [Getting Started](#getting-started)
- [Project Structure](#project-structure)
- [How to Contribute](#how-to-contribute)
- [Development Workflow](#development-workflow)
- [Coding Guidelines](#coding-guidelines)
- [Testing Your Changes](#testing-your-changes)
- [Commit Message Guidelines](#commit-message-guidelines)
- [Pull Request Process](#pull-request-process)
- [Reporting Bugs](#reporting-bugs)
- [Suggesting Features](#suggesting-features)
- [Security Issues](#security-issues)

## Code of Conduct

This project follows a [Code of Conduct](CODE_OF_CONDUCT.md). By participating, you're expected to uphold it. Please be respectful and constructive in all interactions.

## Getting Started

### Prerequisites

- A C++ compiler with C++11 (or later) support (`g++` or `clang++`)
- `make`
- Git

### Setup

1. Fork the repository and clone your fork:
   ```bash
   git clone https://github.com/<your-username>/Database-engine.git
   cd Database-engine
   ```
2. Build the project:
   ```bash
   make
   ```
3. Run it:
   ```bash
   ./db
   ```
4. Try a few queries at the prompt to make sure everything works:
   ```sql
   CREATE TABLE users;
   INSERT INTO users VALUES (1, Adarsh);
   SELECT * FROM users;
   ```

## Project Structure

```
Database-engine/
 ├── src/
 │   ├── main.cpp        # Entry point / REPL loop
 │   ├── parser.cpp       # SQL-like text -> Command struct
 │   ├── executor.cpp     # Executes parsed commands
 │   ├── storage.cpp      # In-memory + file-based storage engine
 ├── include/
 │   ├── command.h
 │   ├── parser.h
 │   ├── executor.h
 │   ├── storage.h
 ├── data/                # Persisted table files (*.table)
 ├── Makefile
 └── README.md
```

Understanding the data flow will help you find where to make changes:

```
User Input (SQL) → Parser → Executor → Storage Engine (Memory / Disk)
```

- **Adding a new SQL keyword or clause?** Start in `parser.cpp`/`parser.h`.
- **Changing how a command is executed?** Look at `executor.cpp`/`executor.h`.
- **Changing how data is stored or persisted?** Look at `storage.cpp`/`storage.h`.
- **Changing the command's data shape?** Look at `command.h`.

## How to Contribute

You can contribute in several ways:

- Fixing bugs
- Adding new SQL features (see [Future Improvements](README.md#-future-improvements) in the README for ideas: dynamic schema support, indexing, transactions, a fuller SQL parser, etc.)
- Improving error handling and input validation
- Writing tests
- Improving documentation (README, code comments, examples)
- Improving build tooling (Makefile, CI)

If you're not sure where to start, check open [issues](https://github.com/adarsh0707-kumar/Database-engine/issues), especially any tagged `good first issue` or `help wanted`.

## Development Workflow

1. **Open an issue first** for anything beyond a small fix (new feature, behavior change, refactor) so it can be discussed before you invest time in it.
2. **Create a branch** off `main` with a descriptive name:
   ```bash
   git checkout -b feature/add-delete-all
   git checkout -b fix/where-clause-parsing
   ```
3. **Make your changes**, following the guidelines below.
4. **Build and manually test** before opening a PR.
5. **Open a pull request** against `main`.

## Coding Guidelines

Since this is a small, from-scratch C++ codebase, consistency matters more than strict style enforcement. Please try to:

- **Match existing style** in the file you're editing (naming, brace placement, indentation).
- Use clear, descriptive names for functions and variables (e.g. `parseInsertStatement`, not `pIS`).
- Keep the **Parser → Executor → Storage** separation intact — avoid putting parsing logic in the executor, or storage logic in the parser.
- Prefer `std::string`/`std::vector` and standard library containers over raw pointers and manual memory management where possible.
- Add comments for non-obvious logic, especially around tokenizing/parsing rules.
- Keep functions focused — if a function is doing parsing, execution, and storage all at once, consider splitting it up.
- Avoid introducing new external dependencies unless discussed in an issue first — the project intentionally has a minimal footprint.

## Testing Your Changes

The project doesn't currently ship an automated test suite, so please test manually before submitting a PR:

1. Rebuild with `make` (and `make clean` first if you're unsure about stale objects).
2. Run `./db` and exercise:
   - The feature/fix you changed
   - The core query types: `CREATE TABLE`, `INSERT INTO`, `SELECT` (with and without `WHERE`), `UPDATE`, `DELETE`
   - Persistence — restart `./db` and confirm previously inserted data is still there (check the corresponding file under `data/`)
3. If you add a new SQL feature, please also add example queries for it in your PR description so reviewers can try it themselves.

If you're comfortable doing so, adding unit tests (e.g. via a lightweight framework, or simple assertion-based test scripts) for parser/executor logic is a great contribution on its own.

## Commit Message Guidelines

Keep commit messages short and descriptive, ideally in the imperative mood:

```
Add support for DELETE with WHERE on multiple conditions
Fix crash on malformed INSERT statement
Update README with UPDATE query examples
```

Avoid vague messages like `fix`, `update`, or `changes`.

## Pull Request Process

1. Ensure your branch builds cleanly with `make` and has no leftover debug output.
2. Update the `README.md` if you've added/changed a feature, query syntax, or the project structure.
3. Fill out the PR description with:
   - What the change does and why
   - How you tested it (commands/queries you ran)
   - Any limitations or follow-up work
4. Link the related issue, if any (e.g. `Closes #12`).
5. Be responsive to review feedback — small, focused PRs are easier to review and merge than large ones.
6. A maintainer will review and merge once the PR looks good.

## Reporting Bugs

When filing a bug report, please include:

- Steps to reproduce (the exact queries you ran, in order)
- What you expected to happen
- What actually happened (error message, crash, incorrect output, etc.)
- Your OS/compiler version

## Suggesting Features

Feature suggestions are welcome, especially anything from the [Future Improvements](README.md#-future-improvements) list (indexing, transactions, dynamic schema, fuller SQL grammar). When suggesting a feature, briefly describe:

- The use case / motivation
- Example syntax or usage, if it's a new SQL feature
- Any impact on existing storage format or behavior

## Security Issues

Please do **not** open a public issue for security-related concerns. Follow the process described in [SECURITY.md](SECURITY.md) instead.

---

Thanks again for contributing — every improvement, however small, helps make MiniDB a better example of how database engines work under the hood. 🧠
