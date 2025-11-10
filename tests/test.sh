#!/bin/bash
# To make script runnable: chmod +x ./test.sh
set -e
set -u

TEST_DIR="$(dirname "$0")"
THIS_SCRIPT="$(basename "$0")"

for testfile in "$TEST_DIR"/test*.sh; do
    [ -f "$testfile" ] || continue

    [ "$(basename "$testfile")" = "$THIS_SCRIPT" ] && continue

    chmod +x "$testfile"
    echo "================ Running: $testfile ================"
    "$testfile"
done

echo "================ All tests finished ================="
