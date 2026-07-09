# Embedded Components

A collection of reusable embedded software components for microcontroller-based projects.

## 📦 Overview

This repository contains common modules frequently used in embedded development, such as:

*  Bit manipulation utilities for CAN communication
*  Button driver and debounce logic
*  Command line parser and shell interface
*  Endianness conversion utilities
*  LED driver
*  Pattern matching utilities
*  Platform abstraction layer
*  Lightweight printf implementation
*  Ring buffer implementation

All components are designed to be:

* Portable across platforms (STM32, ESP32, Renesas etc.)
* Lightweight and efficient
* Easy to integrate into existing projects

## 📂 Project Structure

```text
.
├── .vscode/                    # VSCode configuration
├── resource/                   # Project resources
│   └── img/                    # Images and assets
│
├── source/                     # Embedded library source code
│   ├── bit_field/              # Bit manipulation utilities for CAN communication
│   ├── button/                 # Button driver and debounce logic
│   ├── cmd_line/               # Command line parser and shell interface
│   ├── endian/                 # Endianness conversion utilities
│   ├── led/                    # LED driver
│   ├── match/                  # Pattern matching utilities
│   ├── port/                   # Platform abstraction layer
│   ├── printf/                 # Lightweight printf implementation
│   └── ring_buffer/            # Ring buffer implementation
│
└── test/                       # Ceedling unit test environment
    ├── build/                  # Test build artifacts (auto-generated)
    ├── support/                # Test helpers and shared utilities
    └── test/                   # Unit test source files
```

## 🧪 How to Run Unit Tests

### 1. Install Ceedling

Ceedling requires Ruby and build tools:

```bash
sudo apt update
sudo apt install ruby-full build-essential -y
sudo gem install ceedling
```

Verify installation:

```bash
ceedling version
```

### 2. Install Gcovr (Coverage Report)

gcovr is required to generate HTML for code coverage reports.

Install gcovr:

```bash
sudo apt install gcovr
```

Verify the installation:

```bash
gcovr --version
```

### 3. Run Tests

Navigate to the test directory:

```bash
cd test
```

Run all tests:

```bash
ceedling test:all
```

Run a specific module test (e.g., LED):

```bash
ceedling test:test_led
```

### 4. Generate Code Coverage Report

Navigate to the test directory:

```bash
cd test
```

Run all tests with coverage enabled:
```bash
ceedling clobber gcov:all
```

After the tests complete, the HTML coverage report will be generated at:

```bash
build/artifacts/gcov/gcovr/GcovCoverageResults.html
```

Open the report in your browser to view line, branch, and function coverage.
![Coverage repoert template](<resource/img/gcc_code_coverage_report_template.png>)
---

### Notes

* Tests are written using Unity and CMock.
* Test results and build artifacts are generated in `test/build/`.
* Make sure new modules have corresponding `test_<module>.c` files.