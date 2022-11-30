#!/bin/bash

# You can find SESSION by using Chrome tools. Go to https://adventofcode.com/2018/day/3/input, right-click, inspect, tab over to network, click refresh, click input, click cookies, and grab the value for session.
SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
DAY=$1
URL="https://adventofcode.com/2018/day/${DAY}/input "
COOKIE=$(cat ${SCRIPT_DIR}/.cookie)
curl $URL --cookie "session=${COOKIE}"
