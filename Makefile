# ================= format =================
.PHONY: format-project
format:
	find . \( -name "*.c" -o -name "*.h" \) -print0 | \
	xargs -0 clang-format -i -style=file

# ================= test =================
.PHONY: test-all test

# Run all tests
test-all:
	cd test && ceedling test:all

# Run specific test (usage: make test TEST=test_led)
test:
	cd test && ceedling test:$(TEST)