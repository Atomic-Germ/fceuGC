#ifndef SIMPLE_TEST_H
#define SIMPLE_TEST_H

#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <functional>

// Test registry and runner
class TestRunner {
private:
    struct TestCase {
        std::string name;
        std::function<bool()> func;
    };
    
    std::vector<TestCase> tests;
    int passedTests = 0;
    int failedTests = 0;
    
    TestRunner() {}
    
public:
    static TestRunner& instance() {
        static TestRunner runner;
        return runner;
    }
    
    void registerTest(const std::string& name, std::function<bool()> func) {
        tests.push_back({name, func});
    }
    
    int runTests() {
        std::cout << "\nRunning " << tests.size() << " tests...\n" << std::endl;
        
        for (const auto& test : tests) {
            std::cout << "Running test: " << test.name << "... ";
            std::cout.flush();
            
            try {
                bool result = test.func();
                if (result) {
                    std::cout << "PASSED" << std::endl;
                    passedTests++;
                } else {
                    std::cout << "FAILED" << std::endl;
                    failedTests++;
                }
            } catch (const std::exception& e) {
                std::cout << "EXCEPTION: " << e.what() << std::endl;
                failedTests++;
            } catch (...) {
                std::cout << "UNKNOWN EXCEPTION" << std::endl;
                failedTests++;
            }
        }
        
        std::cout << "\nTest Results:" << std::endl;
        std::cout << "  Passed: " << passedTests << std::endl;
        std::cout << "  Failed: " << failedTests << std::endl;
        std::cout << "  Total:  " << tests.size() << std::endl;
        std::cout << std::endl;
        
        return (failedTests == 0) ? 0 : 1;
    }
};

// Test registrar helper
class TestRegistrar {
public:
    TestRegistrar(const std::string& name, std::function<bool()> func) {
        TestRunner::instance().registerTest(name, func);
    }
};

// Assertion macros
#define ASSERT_TRUE(condition) \
    do { \
        if (!(condition)) { \
            std::cerr << "\n  Assertion failed: " << #condition << std::endl; \
            std::cerr << "  File: " << __FILE__ << ":" << __LINE__ << std::endl; \
            return false; \
        } \
    } while (0)

#define ASSERT_FALSE(condition) \
    do { \
        if (condition) { \
            std::cerr << "\n  Assertion failed: !(" << #condition << ")" << std::endl; \
            std::cerr << "  File: " << __FILE__ << ":" << __LINE__ << std::endl; \
            return false; \
        } \
    } while (0)

#define ASSERT_EQ(expected, actual) \
    do { \
        if ((expected) != (actual)) { \
            std::cerr << "\n  Assertion failed: " << #expected << " == " << #actual << std::endl; \
            std::cerr << "  Expected: " << (expected) << std::endl; \
            std::cerr << "  Actual:   " << (actual) << std::endl; \
            std::cerr << "  File: " << __FILE__ << ":" << __LINE__ << std::endl; \
            return false; \
        } \
    } while (0)

#define ASSERT_NE(expected, actual) \
    do { \
        if ((expected) == (actual)) { \
            std::cerr << "\n  Assertion failed: " << #expected << " != " << #actual << std::endl; \
            std::cerr << "  Expected not equal to: " << (expected) << std::endl; \
            std::cerr << "  File: " << __FILE__ << ":" << __LINE__ << std::endl; \
            return false; \
        } \
    } while (0)

#define ASSERT_NULL(ptr) \
    do { \
        if ((ptr) != nullptr) { \
            std::cerr << "\n  Assertion failed: " << #ptr << " is not null" << std::endl; \
            std::cerr << "  File: " << __FILE__ << ":" << __LINE__ << std::endl; \
            return false; \
        } \
    } while (0)

#define ASSERT_NOT_NULL(ptr) \
    do { \
        if ((ptr) == nullptr) { \
            std::cerr << "\n  Assertion failed: " << #ptr << " is null" << std::endl; \
            std::cerr << "  File: " << __FILE__ << ":" << __LINE__ << std::endl; \
            return false; \
        } \
    } while (0)

#define ASSERT_STREQ(expected, actual) \
    do { \
        if (strcmp((expected), (actual)) != 0) { \
            std::cerr << "\n  Assertion failed: strings not equal" << std::endl; \
            std::cerr << "  Expected: \"" << (expected) << "\"" << std::endl; \
            std::cerr << "  Actual:   \"" << (actual) << "\"" << std::endl; \
            std::cerr << "  File: " << __FILE__ << ":" << __LINE__ << std::endl; \
            return false; \
        } \
    } while (0)

#define ASSERT_STRNE(expected, actual) \
    do { \
        if (strcmp((expected), (actual)) == 0) { \
            std::cerr << "\n  Assertion failed: strings are equal" << std::endl; \
            std::cerr << "  Both strings: \"" << (expected) << "\"" << std::endl; \
            std::cerr << "  File: " << __FILE__ << ":" << __LINE__ << std::endl; \
            return false; \
        } \
    } while (0)

// Test definition macro
#define TEST(test_name) \
    bool test_##test_name(); \
    static TestRegistrar registrar_##test_name(#test_name, test_##test_name); \
    bool test_##test_name()

#endif // SIMPLE_TEST_H
