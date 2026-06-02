# Titan Language - Current Status

## Vision

Titan is a statically typed systems programming language focused on:

* Explicit fixed-width primitive types
* Strong compile-time type safety
* Optional types
* Checked conversions
* Predictable performance
* C/C++ level performance
* Simpler syntax than C++
* Safety inspired by Rust

Example:

```titan
struct Player
{
    Health: f32 = 100.0;
    Target: Player?;
}
```

---

# Compiler Pipeline

```txt
Source Code
    ↓
Lexer
    ↓
Tokens
    ↓
Parser
    ↓
AST
    ↓
Type Checker
    ↓
IR
    ↓
Code Generation
```

Current progress:

```txt
Source Code
    ↓
Lexer         ✓
    ↓
Parser        ✓
    ↓
AST           ✓ (Structs)
    ↓
Type Checker  ✗
    ↓
IR            ✗
    ↓
CodeGen       ✗
```

---

# Implemented Features

## Lexer

### Literals

* IntegerLiteral
* FloatLiteral
* StringLiteral
* CharacterLiteral

### Keywords

* struct
* fn
* return
* true
* false

### Delimiters

* {
* }
* (
* )
* :
* ;
* ,
* .

### Operators

* =
* ?
* ->

### Comments

* // Line Comment
* /* Block Comment */

### Other

* Identifier
* Unknown
* EndOfFile

---

# Parser

Current parser supports:

## Struct Declarations

Example:

```titan
struct Player
{
    Health: f32 = 100.0;
}
```

AST Output:

```txt
Struct
└── Player
    └── Field
        ├── Health
        ├── f32
        └── 100.0
```

### Supported Field Components

* Name
* Type
* Default Value

---

# Automated Tests

## Lexer Tests

✓ Empty Source

✓ Whitespace

✓ Struct Keyword

✓ Identifier

✓ Integer Literal

✓ Float Literal

✓ Field Declaration

✓ Optional Type

✓ Function Arrow

✓ Basic Struct

✓ String Literal

✓ Character Literal

✓ Line Comment

✓ Block Comment

---

## Parser Tests

✓ Basic Struct

---

# Current AST

## FASTStructNode

```cpp
struct FASTStructNode
{
    std::string Name;
    std::vector<FASTFieldNode> Fields;
};
```

## FASTFieldNode

```cpp
struct FASTFieldNode
{
    std::string Name;
    std::string TypeName;
    std::string DefaultValue;
};
```

---

# Next Milestones

## Immediate

### Parser

* Multiple fields per struct
* Optional field types
* Better parser diagnostics

### AST

* Type nodes
* Literal nodes
* Expression nodes

---

## Short Term

### Functions

```titan
fn Damage(Target: Player?, Amount: f32) -> bool
{
    return true;
}
```

Parser support for:

* Function declarations
* Parameters
* Return types
* Function bodies

---

## Mid Term

### Semantic Analysis

* Type validation
* Symbol tables
* Scope resolution
* Optional type rules
* Cast validation

---

## Long Term

### Intermediate Representation

Titan IR

```txt
Titan Source
    ↓
AST
    ↓
Titan IR
```

### Code Generation

Potential targets:

* LLVM
* Native x64
* Native ARM64

---

# Current Status

Current phase:

```txt
Frontend Development
```

Current milestone:

```txt
Struct Parsing
```

Current test status:

```txt
15 Passed
0 Failed
```

Next objective:

```txt
Parse multiple struct fields and begin
function declaration parsing.
```
