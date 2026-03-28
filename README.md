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
│   ├── project.yml      # Ceedling configuration
│   ├── test/            # Test cases
│   │   ├── test_led.c
│   │   └── support/     # Test helpers / mocks
├── Makefile             # Build / format utilities
└── README.md            # Project overview
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

---

### 2. Run Tests

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

---

### Notes

* Tests are written using Unity and CMock.
* Test results and build artifacts are generated in `test/build/`.
* Make sure new modules have corresponding `test_<module>.c` files.