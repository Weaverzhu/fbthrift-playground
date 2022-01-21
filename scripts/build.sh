#!/bin/bash
set -eux
CWD=$(dirname $0)/..
cd $CWD

if [ $1 == deps ] 
then
    echo building deps...
    source ./scripts/build-deps.sh
fi

cd build
cmake .. -GNinja
ninja