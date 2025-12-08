#!/bin/bash

# Define colors for output
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No Color

EXEC="cmake-build-debug/DS_wet1_winter_2026.exe"

if [ ! -f "$EXEC" ]; then
   echo "File $EXEC not found!"
   exit 1
fi

for test in tests/*.in; do
    # Define expected output file name
    expected_output="${test%.in}.out"
    my_output="${test%.in}.res"

    # Run the test
    ./"$EXEC" < "$test" > "$my_output"

    # Compare output
    if diff --brief --ignore-all-space "$my_output" "$expected_output" > /dev/null; then
        echo -e "Test $test: ${GREEN}PASS${NC}"
    else
        echo -e "Test $test: ${RED}FAIL${NC}"
        echo "Differences:"
        diff --ignore-all-space "$my_output" "$expected_output"
        # Optional: exit on first failure
        # exit 1
    fi
done

echo "All tests completed."
exit 0