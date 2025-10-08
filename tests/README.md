# FCE Ultra GX Unit Tests

This directory contains the unit test suite for FCE Ultra GX, following the proven testing pattern from [snes9xGC](https://github.com/Atomic-Germ/snes9xGC/tree/master/tests).

## Overview

The unit tests are designed to run **without building the full project**. They use standard compiler tools (g++) and mock hardware dependencies, making them perfect for CI environments and rapid development.

### Key Features

- ✅ **No full build required** - Tests compile independently
- ✅ **Standard tools only** - Uses g++, not DevkitPPC cross-compiler
- ✅ **Fast execution** - All tests run in seconds
- ✅ **Hardware mocked** - No GameCube/Wii hardware needed
- ✅ **CI-friendly** - Runs in standard GitHub Actions environment

## Directory Structure

```
tests/
├── framework/
│   └── simple_test.h           # Lightweight test framework
├── mocks/
│   ├── mock_libogc.h           # Mock GameCube/Wii types and functions
│   └── mock_libogc.cpp         # Mock implementations
├── unit/
│   ├── test_main.cpp           # Test entry point
│   ├── test_dummy.cpp          # Framework verification tests
│   ├── test_fileop.cpp         # File operation tests
│   ├── test_button_mapping.cpp # Controller mapping tests
│   └── [additional tests...]   # Future test files
├── Makefile                    # Test build system
└── README.md                   # This file
```

## Building and Running Tests

### Quick Start

```bash
cd tests

# Build and run all tests
make run

# Or step by step:
make tests      # Build only
./run_tests     # Run tests

# Clean build artifacts
make clean
```

### Expected Output

```
Running 77 tests...

Running test: framework_basic_test... PASSED
Running test: controller_type_gcpad_valid... PASSED
Running test: strip_device_with_sd_prefix... PASSED
...

Test Results:
  Passed: 77
  Failed: 0
  Total:  77
```

## Test Categories

### Framework Tests (`test_dummy.cpp`)
Basic tests that verify the test framework itself is working correctly.

**Coverage:**
- Basic assertions (TRUE/FALSE)
- Equality checks
- String comparisons

### File Operation Tests (`test_fileop.cpp`)
Tests for file path manipulation and validation utilities.

**Coverage:**
- Device prefix stripping (`sd:/`, `usb:/`, etc.)
- Device name extraction
- ROM extension validation
- File extension parsing
- Path manipulation

**Example tests:**
- Strip device prefix from paths
- Validate NES/FDS/NSF/UNIF extensions
- Extract file extensions
- Handle null/invalid inputs

### Button Mapping Tests (`test_button_mapping.cpp`)
Tests for controller configuration and button mapping logic.

**Coverage:**
- Controller type validation
- Controller name lookup
- Button value validation
- Button combination handling
- Button counting

**Example tests:**
- Validate controller types (GC, Wiimote, Classic, etc.)
- Check button constants
- Count pressed buttons
- Test button combinations

## Writing New Tests

### 1. Create a Test File

Create `unit/test_yourmodule.cpp`:

```cpp
#include "../framework/simple_test.h"
#include "../mocks/mock_libogc.h"
#include <cstring>

// Your test helper functions here

TEST(your_test_name) {
    // Arrange
    int value = 42;
    
    // Act
    int result = value * 2;
    
    // Assert
    ASSERT_EQ(84, result);
    return true;
}
```

### 2. Build and Run

```bash
cd tests
make clean && make run
```

The Makefile automatically discovers new test files matching `unit/test_*.cpp`.

### 3. Available Assertions

```cpp
ASSERT_TRUE(condition)           // Verify condition is true
ASSERT_FALSE(condition)          // Verify condition is false
ASSERT_EQ(expected, actual)      // Verify equality
ASSERT_NE(expected, actual)      // Verify inequality
ASSERT_NULL(ptr)                 // Verify pointer is null
ASSERT_NOT_NULL(ptr)             // Verify pointer is not null
ASSERT_STREQ(expected, actual)   // Verify string equality
ASSERT_STRNE(expected, actual)   // Verify string inequality
```

## Testing Strategy

### What to Test

✅ **Pure logic functions** - String manipulation, calculations, validation  
✅ **Data structure operations** - Parsing, formatting, conversion  
✅ **Edge cases** - Null inputs, empty strings, boundary values  
✅ **Error handling** - Invalid input validation  

### What NOT to Test

❌ **Hardware interactions** - Mock them instead  
❌ **File I/O** - Use memory buffers or mock  
❌ **Network operations** - Mock them  
❌ **Complex integration** - Save for higher-level tests  

### Test Structure

Follow the Arrange-Act-Assert pattern:

```cpp
TEST(descriptive_test_name) {
    // Arrange - Set up test data
    char buffer[256];
    const char* input = "test";
    
    // Act - Call the function being tested
    bool result = MyFunction(buffer, input);
    
    // Assert - Verify the result
    ASSERT_TRUE(result);
    ASSERT_STREQ("expected", buffer);
    
    return true;
}
```

## Mock Library

The `mocks/` directory contains mock implementations of GameCube/Wii libraries.

### Mock Types Available

- Basic types: `u8`, `u16`, `u32`, `s8`, `s16`, `s32`
- Controller buttons: `PAD_BUTTON_*`, `WPAD_BUTTON_*`
- Video modes: `GXRModeObj`, `TVNtsc480IntDf`, etc.

### Adding New Mocks

When you encounter missing types or functions:

**1. For types and constants** - Add to `mock_libogc.h`:
```cpp
typedef struct _NewType {
    u32 field1;
    u16 field2;
} NewType;
```

**2. For simple functions** - Add inline stub to `mock_libogc.h`:
```cpp
static inline void NewFunction() {}
```

**3. For complex functions** - Declare in `.h`, implement in `.cpp`:
```cpp
// In mock_libogc.h
extern NewType globalObject;

// In mock_libogc.cpp
NewType globalObject = { /* ... */ };
```

## Continuous Integration

These tests run automatically in GitHub Actions on every push and pull request.

### CI Configuration

The tests run in the `unit-tests` job in `.github/workflows/build.yml`:

```yaml
jobs:
  unit-tests:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v4
      - name: Install build dependencies
        run: sudo apt-get install -y build-essential g++
      - name: Build unit tests
        run: cd tests && make tests
      - name: Run unit tests
        run: cd tests && make run
```

### Viewing Test Results

1. Go to the GitHub Actions tab
2. Click on the latest workflow run
3. View the `unit-tests` job output
4. Download test results from artifacts (if available)

## Troubleshooting

### Compilation Errors

**Problem:** Missing type or function
```
error: 'SomeType' was not declared in this scope
```

**Solution:** Add the type to `mocks/mock_libogc.h`

### Linking Errors

**Problem:** Undefined reference
```
undefined reference to 'SomeFunction'
```

**Solution:** Add function stub to `mocks/mock_libogc.h` or implementation to `mocks/mock_libogc.cpp`

### Test Failures

**Problem:** Test fails unexpectedly

**Solution:** Run with verbose output:
```bash
cd tests
./run_tests
```

The test will show which assertion failed and on which line.

### Segmentation Faults

**Problem:** Test crashes with segfault

**Solution:** Debug with gdb:
```bash
cd tests
make tests
gdb ./run_tests
run
bt  # Show backtrace
```

## Test Statistics

Current test coverage:

- **77 tests** across 3 test files
- **100% pass rate**
- **Tests run in ~0.1 seconds**

### Test Breakdown

| Module | Tests | Coverage |
|--------|-------|----------|
| Framework | 4 | Basic assertions |
| File Operations | 40 | Path handling, extensions |
| Button Mapping | 33 | Controller types, buttons |

## Future Tests

Planned test coverage expansion:

- **Preferences** - Settings validation, default values
- **Memory Operations** - Buffer management, allocation
- **Video Mode** - Mode selection logic
- **Save State** - State validation
- **Cheat System** - Cheat code parsing

## Best Practices

1. **One test, one assertion focus** - Test one thing per test
2. **Descriptive names** - Use clear, specific test names
3. **Test edge cases** - Null, empty, boundary values
4. **Keep tests fast** - Mock expensive operations
5. **Keep tests independent** - No shared state between tests
6. **Update tests with code** - Tests are documentation

## Resources

### Reference Implementation
- **snes9xGC Tests**: https://github.com/Atomic-Germ/snes9xGC/tree/master/tests
- **snes9xGC Test README**: https://github.com/Atomic-Germ/snes9xGC/blob/master/tests/README.md

### Documentation
- **Implementation Guide**: `../UNIT_TESTING_IMPLEMENTATION_GUIDE.md`
- **Quick Reference**: `../UNIT_TESTING_QUICK_REFERENCE.md`
- **Testing Plan**: `../UNIT_TESTING_PLAN.md`

## Contributing

When adding new tests:

1. Write tests following existing patterns
2. Ensure all tests pass: `make clean && make run`
3. Update this README if adding new test categories
4. Submit PR with tests and related code changes

---

**Questions?** Check the documentation files in the root directory or refer to the snes9xGC test suite for examples.
