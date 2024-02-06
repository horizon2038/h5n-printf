#!/bin/zsh

CURRENT=`dirname $0`
cd $CURRENT

BUILDDIR=../build
TARGET=$BUILDDIR/h5n_print

function test_string_normal() {
    $TARGET "helloworld!"
}

function test_string_break() {
    $TARGET "break\n"
}

function test_value_normal() {
    $TARGET 2038
}

function test_string_with_char() {
    $TARGET "value: %c" 's'
}

function test_string_with_value {
    $TARGET "value: %d" 2038
}

function test_string_with_string() {
    $TARGET "value: %s" "string"
}


test_string_normal
test_string_with_char
test_string_break
test_value_normal
test_string_with_char
test_string_with_value
test_string_with_string
