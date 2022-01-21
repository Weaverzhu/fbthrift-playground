#!/bin/bash
set -eux
cd $(dirname $0)/..
CWD=`pwd`
git submodule update --init --recursive

git_tag=v2022.01.03.00

cd $CWD/external/folly
git fetch --all --tags
git checkout $git_tag

cd $CWD/external/fizz
git fetch --all --tags
git checkout $git_tag

cd $CWD/external/wangle
git fetch --all --tags
git checkout $git_tag

cd $CWD/external/fbthrift
git fetch --all --tags
git checkout $git_tag