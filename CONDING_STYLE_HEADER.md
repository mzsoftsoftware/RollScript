# RollScript C++ Header Style Guide

## Status

This document defines the mandatory style for new and modified C++ header files in the RollScript project.

It applies to:

* Application
* Common
* Core
* Plugins

This document supplements the general rules defined in `CODING_STYLE.md`.

---

# 1. General Principles

1. **Headers are interfaces.** A header describes what a class provides. Implementation details should remain in the `.cpp` file whenever possible.
2. Simple setters and getters are an exception and may be implemented directly in the header where appropriate.
3. **Use as few includes as possible.** If a type is only used as a pointer or reference, prefer a forward declaration.
4. A consistent and recognizable structure is mandatory.
5. Public plugin APIs should be treated particularly conservatively.

---

# 2. Header Structure

The basic structure of a header is:

1. `#pragma once`
2. Qt includes
3. Empty line
4. Project includes
5. Empty line
6. Forward declarations
7. Two empty lines
8. Class declaration

## 2.1 Includes

* Includes within each group are sorted alphabetically where this does not reduce readability.
* Exactly one empty line separates include groups.
* Only required includes are allowed.
* Forward declarations are preferred whenever the complete type definition is not required.
* Two empty lines precede the class declaration.
* The file ends with one empty line.

---

# 3. Class Structure

The following order is mandatory within a class:

```cpp id="q6n4yx"
class Example : public QObject
{
    Q_OBJECT

public:
    // Types and constants

    // Constructor / Destructor

    // Getters

    // Setters

    // Operations

    // State

public slots:
    // Public slots

protected slots:
    // Protected slots

private slots:
    // Private slots

signals:
    // Signals

protected:
    // Protected API

    // Protected members

private:
    // Private helper methods

    // Private members
};
```

Unused sections are omitted completely.

Semantic grouping has priority over alphabetical ordering.

Within a semantic group, elements are sorted alphabetically where this improves readability.

Each group should be identified by a comment.

---

# 4. Getters and Setters

Within the public API, getters precede setters.

Simple getters and setters may be implemented directly in the header.

Non-trivial implementations belong in the `.cpp` file.

---

# 5. Slots

## 5.1 Custom Slots

Custom slots use the naming scheme:

`slot_<Sender>_<Signal>`

## 5.2 Qt Designer Auto-Connect

Qt Designer auto-connect slots retain the standard Qt naming convention.

---

# 6. Signals

Signals describe events or state changes.

They use a past-tense or state-oriented form and must not use imperative names.

---

# 7. Data Members

Data members are grouped by responsibility, not by type.

A vertical alignment of related data members is preferred.

---

# 8. Qt-Specific Header Rules

Qt-specific constructs retain their required Qt syntax.

For plugins:

1. `Q_PLUGIN_METADATA` is placed directly after `Q_OBJECT`.
2. `Q_INTERFACES` follows `Q_PLUGIN_METADATA`.

---

# 9. Plugin Headers

Plugin headers follow the same structure as all other RollScript headers.

Plugin implementation details should remain inside the plugin whenever possible.

Public Core plugin interfaces must not require Application GUI types.

The plugin ID must remain stable and documented.
