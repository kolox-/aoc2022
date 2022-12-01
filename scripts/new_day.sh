#!/bin/bash
set -x
set -e
# create structure for a new day
SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
DAY_NUM=$1
DAY="day0${DAY_NUM}"
NEW_FOLDER="../${DAY}"

pushd $SCRIPT_DIR
mkdir ${NEW_FOLDER}
cp template.cpp ${NEW_FOLDER}/${DAY}.cpp
cp ../day01/CMakeLists.txt ${NEW_FOLDER}
echo "add_subdirectory(${DAY})" >> ../CMakeLists.txt
./get.sh ${DAY_NUM} > ${NEW_FOLDER}/long.txt
popd
