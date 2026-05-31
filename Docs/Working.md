# Titan Working Doc

## Primitive Types

Titan uses explicit fixed-width primitive types. Implicit sizing such as `int`, `long`, `short`, or `float` is not supported.

### Signed Integers

| Canonical | Aliases          | Size   | Range                                                   |
| --------- | ---------------- | ------ | ------------------------------------------------------- |
| `i8`      | `Int8`, `int8`   | 8-bit  | -128 to 127                                             |
| `i16`     | `Int16`, `int16` | 16-bit | -32,768 to 32,767                                       |
| `i32`     | `Int32`, `int32` | 32-bit | -2,147,483,648 to 2,147,483,647                         |
| `i64`     | `Int64`, `int64` | 64-bit | -9,223,372,036,854,775,808 to 9,223,372,036,854,775,807 |

### Unsigned Integers

| Canonical | Aliases            | Size   | Range                           |
| --------- | ------------------ | ------ | ------------------------------- |
| `u8`      | `UInt8`, `uint8`   | 8-bit  | 0 to 255                        |
| `u16`     | `UInt16`, `uint16` | 16-bit | 0 to 65,535                     |
| `u32`     | `UInt32`, `uint32` | 32-bit | 0 to 4,294,967,295              |
| `u64`     | `UInt64`, `uint64` | 64-bit | 0 to 18,446,744,073,709,551,615 |

### Floating Point

| Canonical | Aliases              | Size   | Standard |
| --------- | -------------------- | ------ | -------- |
| `f32`     | `Float32`, `float32` | 32-bit | IEEE-754 |
| `f64`     | `Float64`, `float64` | 64-bit | IEEE-754 |

### Boolean

| Canonical | Aliases           | Size   |
| --------- | ----------------- | ------ |
| `bool`    | `Bool`, `Boolean` | 1 byte |

Valid values:

```titan
true
false
```

### Character

| Canonical | Aliases |
| --------- | ------- |
| `char`    | `Char`  |

Represents a single Unicode code point.

Example:

```titan
Letter: char = 'A';
```

### String

| Canonical | Aliases  |
| --------- | -------- |
| `String`  | `string` |

Represents a UTF-8 encoded string.

Example:

```titan
Name: String = "Titan";
```

### Optional Types

Any primitive or user-defined type may be marked as optional using the `?` operator.

Examples:

```titan
Health: i32?;
Name: String?;
Player: Player?;
```

Equivalent to:

```titan
optional<i32>
optional<String>
optional<Player>
```

### Type Rules

The following types are intentionally forbidden:

```titan
int
uint
short
long
float
double
```

Titan requires all primitive types to declare their exact width.

Invalid:

```titan
Health: int = 100;
```

Valid:

```titan
Health: i32 = 100;
```

## Architecture-Sized Integers

Architecture-sized integers automatically match the native pointer size of the target platform.

These types should be used for:

* Array indexing
* Container sizes
* Memory offsets
* Pointer arithmetic
* Low-level systems programming

### Signed Architecture Integer

| Canonical | Aliases              | Size               |
| --------- | -------------------- | ------------------ |
| `isize`   | `IntSize`, `intsize` | Platform Dependent |

Size by platform:

| Platform | Size   |
| -------- | ------ |
| 32-bit   | 32-bit |
| 64-bit   | 64-bit |

Example:

```titan
Index: isize = 0;
Offset: isize = 128;
```

### Unsigned Architecture Integer

| Canonical | Aliases                | Size               |
| --------- | ---------------------- | ------------------ |
| `usize`   | `UIntSize`, `uintsize` | Platform Dependent |

Size by platform:

| Platform | Size   |
| -------- | ------ |
| 32-bit   | 32-bit |
| 64-bit   | 64-bit |

Example:

```titan
Count: usize = 100;
Length: usize = Array.Length();
```

### Usage Guidelines

Use fixed-width integers when data size must remain identical across all platforms:

```titan
PlayerId: u64;
Health: i32;
Damage: f32;
```

Use architecture-sized integers when working with memory or container sizes:

```titan
Index: usize;
BufferOffset: usize;
ElementCount: usize;
```

### Type Safety

Implicit conversion between architecture-sized and fixed-width integers is prohibited.

Invalid:

```titan
Count: usize = 100;
PlayerCount: u32 = Count;
```

Compiler Error:

```txt
Cannot implicitly convert 'usize' to 'u32'.
```

Valid:

```titan
PlayerCount: u32? = CheckedCast<u32>(Count);
```

or

```titan
PlayerCount: u32 = Cast<u32>(Count);
```

### Design Philosophy

Titan distinguishes between:

```titan
u32
```

which means:

> This value must always be exactly 32 bits.

and

```titan
usize
```

which means:

> This value represents a size, index, or memory-related quantity and should match the platform architecture.
