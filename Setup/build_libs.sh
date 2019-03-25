#!/bin/bash

currentDir=$PWD

#
# Google Test install lib
#
gtestDir=${currentDir}/OpenLibs/googletest
if [[ ! -d ${gtestDir}/googletest/build ]]; then
        echo " - Install Google Test"
        mkdir -p ${gtestDir}/googletest/build
        cd ${gtestDir}/googletest/build && cmake ..
        cd ${gtestDir}/googletest/build && make
else
        echo " - Bypass install Google Test (file ${gtestDir}/googletest/build exist)"
fi

##
## Boost install lib
##
boostDir=${currentDir}/OpenLibs/boost/boost_1_68_0/
if [[ ! -d ${boostDir}/stage ]]; then
    cd ${boostDir}
    echo " - Install Boost lib."
    ./bootstrap.sh
    ./b2 --with-system --with-thread --with-date_time --with-regex --with-serialization --with-program_options stage
else
        echo " - Bypass install Boost (directory ${boostDir}/stage exist)"
fi

##
## msgpack lib
##
msgPackDir=${currentDir}/OpenLibs/msgpack
cd ${msgPackDir}
echo " - Install msgpack sckcpp lib."
cmake .
make

##
## sckcpp lib
##
asioDir=${currentDir}/OpenLibs/sckcpp
if [[ ! -d ${asioDir}/build ]]; then
    cd ${asioDir}
    echo " - Install asio sckcpp lib."
    mkdir build
    cd build
    cmake ..
    make
else
        echo " - Bypass install sckcpp boost asio (directory ${asioDir}/build exist)"
fi

##
## Urho3D lib
##
urhoDir=${currentDir}/OpenLibs/Urho3D
if [[ ! -d ${Dir}/build ]]; then
    cd ${urhoDir}
    echo " - Install Urho3D lib."
    mkdir build
    cd build
    cmake .. -DURHO3D_LIB_TYPE=SHARED -DURHO3D_NETWORK=0
    make
else
        echo " - Bypass install Urho3D (directory ${currentDir}/build exist)"
fi
