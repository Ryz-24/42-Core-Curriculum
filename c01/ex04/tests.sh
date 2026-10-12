#!/bin/bash
# Tests for ex04. Run with: make && ./tests.sh
BIN=./sedIsForLosers
DIR=test_files
PASS=0
FAIL=0

rm -rf "$DIR" && mkdir -p "$DIR"

# check <name> <input> <s1> <s2> <expected output>
check() {
    printf '%s' "$2" > "$DIR/$1"
    $BIN "$DIR/$1" "$3" "$4"
    if [ "$(cat "$DIR/$1.replace")" == "$5" ]; then
        echo "[OK]   $1"; PASS=$((PASS + 1))
    else
        echo "[FAIL] $1: expected '$5', got '$(cat "$DIR/$1.replace")'"; FAIL=$((FAIL + 1))
    fi
}

# expect_error <name> <command...>: the program must report the error and exit with code 1
expect_error() {
    name=$1; shift
    "$@" 2>/dev/null
    code=$?
    if [ "$code" -eq 1 ]; then
        echo "[OK]   $name (error reported)"; PASS=$((PASS + 1))
    else
        echo "[FAIL] $name: expected exit code 1, got $code"; FAIL=$((FAIL + 1))
    fi
}

echo "--- replacements"
check basic        "hello world"        "world" "42"     "hello 42"
check multiple     "a cat, a cat, a cat" "cat"  "dog"    "a dog, a dog, a dog"
check no_match     "nothing here"       "xyz"   "abc"    "nothing here"
check delete       "remove this word"   " this" ""       "remove word"
check s2_has_s1    "aaa"                "a"     "aa"     "aaaaaa"
check overlapping  "aaaa"               "aa"    "b"      "bb"
check whole_file   "same"               "same"  "new"    "new"
check multiline    $'line one\nline two\nline three' "line" "row" $'row one\nrow two\nrow three'
check spaces       "a  b  c"            "  "    " "      "a b c"
check empty_file   ""                   "x"     "y"      ""

echo "--- errors"
expect_error no_args        $BIN
expect_error too_few_args   $BIN "$DIR/basic" "a"
expect_error too_many_args  $BIN "$DIR/basic" "a" "b" "c"
expect_error missing_file   $BIN "$DIR/does_not_exist" "a" "b"
expect_error empty_s1       $BIN "$DIR/basic" "" "b"
expect_error directory      $BIN "$DIR" "a" "b"

echo "--- $PASS passed, $FAIL failed"
[ "$FAIL" -eq 0 ]
