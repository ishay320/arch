#!/usr/bin/env bash
# ----------------------------------------------------------------
# Script for building and running the tests
# ----------------------------------------------------------------
set -e

THIRD_PARTY_I=-I./third_party
TEST_FOLDER="test"
BUILD_FOLDER=build
TESTS=(
    test.c
)

WARNINGS="-Wall -Wextra -pedantic"
CFLAGS=
DEBUG=false

mkdir -p ${BUILD_FOLDER}

if [[ "${DEBUG}" == true ]]; then
    CFLAGS+=-ggdb
fi

# compiling
for FILE in "${TESTS[@]}"; do
    cc ${CFLAGS} ${WARNINGS} ./${TEST_FOLDER}/"${FILE}" -o ./${BUILD_FOLDER}/"${FILE}".a ${THIRD_PARTY_I}
done

# running
for FILE in "${TESTS[@]}"; do
    ./${BUILD_FOLDER}/"${FILE}".a
done
