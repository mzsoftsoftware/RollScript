# RollScript C++ Source Style Guide

## Status

This document defines the mandatory style for new and modified C++ source files in the RollScript project.

It applies to:

* Application
* Common
* Core
* Plugins

This document supplements the general rules defined in `CODING_STYLE.md`.

---

# 1. Source Structure

The basic structure of a source file is:

1. Corresponding header
2. Qt includes
3. Project includes
4. Implementation

The corresponding header is always included first.

Includes are separated into groups by one empty line.

Includes within each group are sorted alphabetically where this does not reduce readability.

Only required includes are allowed.

---

# 2. Method Order

The implementation order of methods must follow the order defined in the corresponding header.

The following order therefore applies:

1. Constructor / Destructor
2. Getters
3. Setters
4. Operations
5. State-related methods
6. Public slots
7. Protected slots
8. Private slots
9. Protected methods
10. Private helper methods

Methods that are not present in the header are placed according to their logical category.

Semantic grouping has priority over alphabetical ordering.

Within a semantic group, methods are sorted alphabetically where this improves readability.

The source file should remain structurally synchronized with its corresponding header.

---

# 3. Constructors and Destructors

Constructors and destructors are implemented before all other methods.

If a class has multiple constructors, their order follows the order in the header.

---

# 4. Getters and Setters

Getters are implemented before setters.

The implementation order follows the corresponding declarations in the header.

Simple getters and setters may be implemented directly in the header where appropriate.

---

# 5. Slots

Custom slots are implemented according to their position in the header.

Qt Designer auto-connect slots retain their required Qt naming convention.

---

# 6. Signals

Signals normally do not require an implementation in the source file.

Signal emissions are placed at the point where the corresponding event or state change occurs.

---

# 7. Private Methods

Private helper methods are implemented after the public and protected functionality to which they belong.

Private methods should remain grouped by their logical responsibility.

---

# 8. Indentation and Whitespace

Indentation uses **4 spaces**.

Tabs must not be used for indentation.

Blank lines should be used where they improve readability and visually separate logical sections of code.

Blank lines between methods may be omitted when adjacent methods are closely related and keeping them together improves readability.

---

# 9. Local Implementation Structure

Within a method, code should be organized in a clear logical order.

Where appropriate, the following order should be preferred:

1. Input validation
2. Preparation
3. Main operation
4. State changes
5. Signal emission
6. Return

This order may be adapted when the logic of the method requires a different structure.

---

# 10. Braces

Opening and closing braces are always placed on their own lines.

This applies to:

* Classes
* Functions and methods
* `if` / `else`
* `for`
* `while`
* `switch`
* `case` blocks where braces are used
* Other compound statements

Braces must not be placed on the same line as the associated statement, declaration, or condition.

---

# 11. Control Structures

Control structures should use a consistent and readable structure.

Braces are always used for multi-line control structures.

Nested logic should be avoided where an early return or another clearer structure improves readability.

---

# 12. Switch Statements

`switch` statements should be used when they provide clearer intent than a chain of conditional statements.

Each relevant case should be handled explicitly.

A `default` case should be used where appropriate.

---

# 13. Lambdas

Lambdas are **not permitted** in the RollScript project.

Functionality that would otherwise be implemented using a lambda must be implemented using a named function, method, or another appropriate mechanism.

---

# 14. Comments

Comments should explain why an implementation is necessary when this is not apparent from the code.

Implementation comments should not merely repeat the source code.

---

# 15. Logging

Logging should use the appropriate Qt logging mechanism and the logging categories defined by the project.

Logging should provide meaningful information and should not unnecessarily duplicate information already available from the surrounding context.

---

# 16. Source and Header Consistency

The source file and its corresponding header must remain structurally consistent.

When methods are added, removed, renamed, or reordered in the header, the source file must be updated accordingly.

The implementation order should make it possible to locate a method in the source by following the same order used in the header.
