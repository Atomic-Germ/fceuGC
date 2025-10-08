# Quick Start - Unit Testing

## Run Tests Immediately

```bash
cd tests
make run
```

Expected output:
```
Running 73 tests...
...
Test Results:
  Passed: 73
  Failed: 0
  Total:  73
```

## Add a New Test

1. Create `tests/unit/test_myfeature.cpp`:

```cpp
#include "../framework/simple_test.h"
#include "../mocks/mock_libogc.h"

TEST(my_first_test) {
    ASSERT_EQ(2 + 2, 4);
    return true;
}

TEST(my_string_test) {
    ASSERT_STREQ("hello", "hello");
    return true;
}
```

2. Build and run:
```bash
cd tests
make clean && make run
```

That's it! The test is automatically discovered and run.

## Common Assertions

```cpp
ASSERT_TRUE(condition)           // Verify true
ASSERT_FALSE(condition)          // Verify false
ASSERT_EQ(expected, actual)      // Verify equal
ASSERT_NE(expected, actual)      // Verify not equal
ASSERT_NULL(ptr)                 // Verify null
ASSERT_NOT_NULL(ptr)             // Verify not null
ASSERT_STREQ(expected, actual)   // Verify strings equal
ASSERT_STRNE(expected, actual)   // Verify strings not equal
```

## File Structure

```
tests/
├── framework/simple_test.h      # Test framework (don't modify)
├── mocks/mock_libogc.*          # Hardware mocks (extend as needed)
├── unit/test_*.cpp              # Your tests go here
└── Makefile                     # Build system (don't modify)
```

## More Information

- Full guide: `UNIT_TESTING_README.md`
- Implementation: `UNIT_TESTING_IMPLEMENTATION_GUIDE.md`
- Examples: Look at `tests/unit/test_fileop.cpp`

## CI Integration

Tests run automatically on every push/PR. Check the Actions tab on GitHub.
