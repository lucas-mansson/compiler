#!/usr/bin/env bash

set -uo pipefail

TEST_DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)
PROJECT_DIR=$(cd -- "$TEST_DIR/.." && pwd)
SUITES=(scanner)

passed=0
failed=0

printf 'Compiler test \n'

for suite in "${SUITES[@]}"; do
    if "$TEST_DIR/test.sh" "$suite" "$PROJECT_DIR/build/test/$suite"; then
        ((passed += 1))
    else
        ((failed += 1))
    fi
done

printf '\nSuite summary: %d passed, %d failed, %d total\n' \
    "$passed" "$failed" "${#SUITES[@]}"

((failed == 0))
