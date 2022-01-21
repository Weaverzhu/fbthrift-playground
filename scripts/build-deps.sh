#!/bin/bash
set -eu
CWD=$(dirname $0)/..
cd $CWD
CWD=`pwd`
echo $CWD

if ! command -v sudo &> /dev/null
then
    apt update && apt -y install sudo git
fi

git submodule update --init
mkdir -p build/opt/playground
INSTALL_DIR=$CWD/build/opt/playground

cmake_args="-DCMAKE_INSTALL_PREFIX=$INSTALL_DIR -DCMAKE_PREFIX_PATH=$INSTALL_DIR -DBUILD_TESTS=OFF -GNinja -DCMAKE_EXPORT_COMPILE_COMMANDS=on"

sudo apt-get -y install \
    g++ \
    cmake \
    ninja-build \
    libboost-all-dev \
    libevent-dev \
    libdouble-conversion-dev \
    libgoogle-glog-dev \
    libgflags-dev \
    libiberty-dev \
    liblz4-dev \
    liblzma-dev \
    libsnappy-dev \
    make \
    zlib1g-dev \
    binutils-dev \
    libjemalloc-dev \
    libssl-dev \
    pkg-config \
    libunwind-dev \
    liburing-dev \
    libfmt-dev \
    libsodium-dev \
    libzstd-dev

cd $CWD
build_dir=$CWD/build-folly
echo $build_dir
mkdir -p $build_dir && cd $build_dir
cmake ../external/folly $cmake_args
ninja
ninja install
cp ../external/folly/CMake/FindLibsodium.cmake ../cmake/FindSodium.cmake
cd -

build_dir=$CWD/build-fizz
mkdir -p $build_dir && cd $build_dir
cmake ../external/fizz/fizz $cmake_args
ninja
ninja install
cd -

build_dir=$CWD/build-wangle
mkdir -p $build_dir && cd $build_dir
cmake ../external/wangle/wangle $cmake_args
ninja
ninja install
cd -

build_dir=$CWD/build-fbthrift
mkdir -p $build_dir && cd $build_dir
sudo apt-get -y install bison \
    flex \
    openssl
cmake ../external/fbthrift $cmake_args
ninja
ninja install
cd -