# Embedded Components

A collection of reusable embedded software components for microcontroller-based projects.

## 📦 Overview

This repository contains common modules frequently used in embedded development, such as:

* LED control
* Button handling
* Ring buffer

All components are designed to be:

* Portable across platforms (STM32, ESP32, etc.)
* Lightweight and efficient
* Easy to integrate into existing projects

## 📂 Project Structure

```text
.
├── Define.h             # Common definitions and data types
├── led/                 # LED module
│   ├── led.c
│   └── led.h
├── ring_buffer/         # Ring buffer module
│   ├── ring_buffer.c
│   ├── ring_buffer.h
│   └── README.md        # Module-specific documentation
├── test/                # Unit test (Ceedling)
│   ├── test/            # Test cases
│   │   ├── test_led.c
│   │   └── support/     # Test helpers / mocks
├── Makefile             # Build / format utilities
└── README.md            # Project overview
├── project.yml      # Ceedling configuration
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

gcovr is required to generate HTML code coverage reports.

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

Run all tests with coverage enabled:

```bash
ceedling gcov:all
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