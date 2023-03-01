#!/usr/bin/env bash
# ----------------------------------------------------------------
# Script for building and running the tests
# ----------------------------------------------------------------

THIRD_PARTY_I=-I./third_party
TEST_FOLDER="test"
BUILD_FOLDER=build
TESTS=(
    test.c
)

mkdir -p ${BUILD_FOLDER}

# compiling
for FILE in "${TESTS[@]}"; do
    cc ./${TEST_FOLDER}/"${FILE}" -o ./${BUILD_FOLDER}/"${FILE}".a ${THIRD_PARTY_I}
done

# running
for FILE in "${TESTS[@]}"; do
    ./${BUILD_FOLDER}/"${FILE}".a
done

echo "tests done"
