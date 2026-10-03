#!/usr/bin/env bash

set -uo pipefail

if [[ $# -ne 2 ]]; then
    echo "Usage: $0 <suite> <executable>" >&2
    exit 1
fi

SUITE=$1
BINARY=$2
TEST_DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)
SUITE_DIR="$TEST_DIR/$SUITE"

if [[ ! -x "$BINARY" ]]; then
    echo "Error: '$BINARY' is not executable." >&2
    exit 1
fi

if [[ ! -d "$SUITE_DIR" ]]; then
    echo "Error: Test suite '$SUITE' does not exist." >&2
    exit 1
fi

shopt -s globstar nullglob
inputs=("$SUITE_DIR"/**/*.in)

if [[ -t 1 ]]; then
    GREEN=$'\033[32m'
    RED=$'\033[31m'
    YELLOW=$'\033[33m'
    BOLD=$'\033[1m'
    RESET=$'\033[0m'
else
    GREEN=
    RED=
    YELLOW=
    BOLD=
    RESET=
fi

if [[ ${#inputs[@]} -eq 0 ]]; then
    printf '%sNo test cases found for %s.%s\n' "$YELLOW" "$SUITE" "$RESET"
    exit 1
fi

passed=0
failed=0

printf '\n%s%s: %d test case(s)%s\n\n' \
    "$BOLD" "$SUITE" "${#inputs[@]}" "$RESET"

for input in "${inputs[@]}"; do
    output="${input%.in}.out"
    answer="${input%.in}.ans"
    name=${input#"$SUITE_DIR"/}
    answer_name=${answer#"$SUITE_DIR"/}

    printf '  %-50s' "$name"

    if ! "$BINARY" "$input" > "$output"; then
        printf '%sERROR%s\n' "$RED" "$RESET"
        ((failed += 1))
        continue
    fi

    if [[ ! -f "$answer" ]]; then
        printf '%sERROR%s (missing %s)\n' "$RED" "$RESET" "$answer_name"
        ((failed += 1))
        continue
    fi

    if diff -q -- "$answer" "$output" > /dev/null; then
        printf '%sPASS%s\n' "$GREEN" "$RESET"
        ((passed += 1))
    else
        printf '%sFAIL%s\n' "$RED" "$RESET"
        diff -u --label "${name%.in}.ans" --label "${name%.in}.out" -- "$answer" "$output" || true
        printf '\n'
        ((failed += 1))
    fi
done

printf '%s%s summary:%s %s%d passed%s, %s%d failed%s, %d total\n' \
    "$BOLD" "$SUITE" "$RESET" \
    "$GREEN" "$passed" "$RESET" "$RED" "$failed" "$RESET" \
    "${#inputs[@]}"

((failed == 0))
