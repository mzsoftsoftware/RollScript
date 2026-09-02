# RollScript C++ Coding Style

## Status

This document defines the general and mandatory coding conventions for the RollScript project.

It applies to all C++ code within:

* Application
* Common
* Core
* Plugins

Header-specific rules are defined in `CODING_STYLE_HEADER.md`.

Source-specific rules are defined in `CODING_STYLE_SOURCE.md`.

These documents together form the **RollScript C++ Coding Style**.

The coding style is mandatory for all RollScript source code.

Existing code **must be adapted** to comply with this coding style.

---

# 1. General Principles

## 1.1 Readability

Code must be easy to read and understand.

Readability and maintainability take precedence over unnecessary compactness, clever implementations, and personal coding preferences.

## 1.2 Consistency

The same concept must use the same terminology and naming throughout the project.

## 1.3 Explicitness

Code should make its intention clear.

Names should be descriptive and unambiguous.

## 1.4 Project Conventions

RollScript-specific conventions take precedence over generic C++ style recommendations when they intentionally differ.

Qt conventions are followed where appropriate, but do not automatically override explicit RollScript conventions.

---

# 2. Naming Conventions

## 2.1 Classes

Classes use **PascalCase**.

## 2.2 Interfaces

Interfaces use the `I` prefix followed by a PascalCase name.

The `I` prefix indicates an abstract interface.

## 2.3 Abstract Base Classes

Abstract base classes use a descriptive PascalCase name with `Base` as the suffix.

## 2.4 Methods and Functions

Methods and functions use **lowerCamelCase**.

Boolean queries should preferably begin with:

* `is`
* `has`
* `can`
* `supports`

## 2.5 Variables

Variables use **lowerCamelCase** with the applicable type prefix.

## 2.6 Data Members

Data members use the `m_` prefix followed by the applicable type prefix and a lowerCamelCase name.

## 2.7 Constants

Constants follow the same naming conventions as variables unless explicitly specified otherwise.

## 2.8 Acronyms and Abbreviations

Established technical abbreviations are written consistently throughout the project.

The same abbreviation must not use different capitalization variants for the same concept.

---

# 3. Parameter Lists

Parameter lists use consistent spacing in declarations, definitions, and function or method calls.

* There is no space before the opening parenthesis.
* There is no space after the opening parenthesis.
* There is no space before the closing parenthesis.
* Exactly one space follows each comma.
* Exactly one space separates a type from its parameter name.

The same rules apply to constructors, functions, methods, and function or method calls.

---

# 4. Type Prefixes

Variables, parameters and data members use a type prefix where defined.

The type prefix identifies the declared type and is followed by the variable name in lowerCamelCase.

For data members, `m_` is added before the type prefix.

The type-prefix list is maintained as part of this coding style and may be extended when additional types are introduced into the project.

## 4.1 Basic Types

| Type           | Prefix |
| -------------- | ------ |
| `bool`         | `b`    |
| `int`          | `i`    |
| `unsigned int` | `ui`   |
| `double`       | `dbl`  |

## 4.2 Qt Types

| Type         | Prefix  |
| ------------ | ------- |
| `QString`    | `qstr`  |
| `QByteArray` | `qba`   |
| `QVector`    | `qvec`  |
| `QList`      | `qlst`  |
| `QHash`      | `qhash` |
| `QMap`       | `qmap`  |
| `QSet`       | `qset`  |
| `QJson...`   | `qjson` |

The list is not exhaustive and may be extended as required.

## 4.3 Pointers

Pointers use the `ptr` prefix.

---

# 5. Plural and Singular Naming

Names must clearly distinguish between a single object and a collection of objects.

Methods should follow the same distinction where applicable.

---

# 6. Boolean Naming

Boolean variables use the `b` type prefix.

Boolean methods should preferably use descriptive predicates such as `is`, `has`, `can`, or `supports`.

---

# 7. Enums

`enum class` is preferred over unscoped `enum`.

Enum types use PascalCase.

Enum values use PascalCase.

---

# 8. Type Aliases

`using` is preferred for type aliases.

The legacy `typedef` syntax should not be used for new code.

---

# 9. Pointer and Reference Syntax

Pointers and references are attached to the type.

The project uses:

* `Type*`
* `Type&`

and not:

* `Type *`
* `Type &`

---

# 10. Const Correctness

`const` must be used consistently throughout the RollScript project.

All parameters must be declared `const` unless the parameter needs to be modified by the function or the language/API requires otherwise.

Methods that do not modify the logical state of an object should be declared `const` where appropriate.

Getters should normally be `const` when they do not modify object state.

References that must not be modified must be declared `const`.

---

# 11. Constructors and Destructors

Every RollScript class must explicitly declare a constructor and a destructor.

Polymorphic base classes and interfaces use a virtual destructor.

A defaulted destructor is permitted for simple interfaces and abstract base classes.

---

# 12. Override and Final

Every overriding virtual function must use `override`.

`virtual` must not be repeated when `override` is used.

`final` may be used when further overriding must explicitly be prevented.

---

# 13. Initialization

Members should be initialized directly at their declaration when a defined and semantically meaningful initial value exists.

Pointer members are initialized explicitly to `nullptr` unless another initial value is required.

---

# 14. Qt Conventions

Qt conventions are followed where they do not conflict with explicit RollScript conventions.

Qt-specific language constructs are used according to Qt requirements.

Qt Designer auto-connect naming conventions are retained.

---

# 15. Code Organization

RollScript code is organized according to responsibility.

The project distinguishes between:

* Application
* Common
* Core
* Plugins

Implementation details should remain in the component where they belong.

Dependencies between components should be kept as small and explicit as reasonably possible.

---

# 16. Plugin Code

Plugin code follows the same general naming conventions as the rest of RollScript.

Plugin-specific conventions must not contradict the general RollScript coding style.

Public plugin interfaces are treated as stable APIs and should therefore be changed conservatively.

Plugin-specific implementation details should remain inside the plugin whenever possible.

---

# 17. Comments

Comments should explain why code exists when the reason is not obvious from the code itself.

Comments should not merely repeat what the code already expresses.

---

# 18. Existing Code

The coding style applies to the complete RollScript codebase.

Existing code that does not comply with this coding style **must be adapted**.

Style-only modifications are explicitly permitted and expected when necessary to bring existing code into compliance.

Unrelated functional changes should not be mixed into a style-only change unless necessary.

---

# 19. Related Style Guides

The following documents define the file-type-specific rules:

* `CODING_STYLE_HEADER.md` — C++ header conventions
* `CODING_STYLE_SOURCE.md` — C++ source conventions

These documents are part of the same RollScript C++ Coding Style and must be considered together.
