#!/usr/bin/env bash
# ----------------------------------------------------------------
# Script for building and running the tests
# ----------------------------------------------------------------
set -e

THIRD_PARTY_I=-I../third_party
TEST_FOLDER="test"
BUILD_FOLDER=build
TESTS=(
    main.c
)

WARNINGS="-Wall -Wextra -pedantic"
CFLAGS=
DEBUG=false

if [[ "${DEBUG}" == true ]]; then
    CFLAGS+=-ggdb
fi

if [ -z "${CC}" ]; then
    CC="cc"
fi

cd ${TEST_FOLDER}
mkdir -p ${BUILD_FOLDER}

# compiling
for FILE in "${TESTS[@]}"; do
    ${CC} ${CFLAGS} ${WARNINGS} "${FILE}" -o ./${BUILD_FOLDER}/"${FILE}".a ${THIRD_PARTY_I}
done

# running
for FILE in "${TESTS[@]}"; do
    ./${BUILD_FOLDER}/"${FILE}".a
done
