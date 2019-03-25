#!/bin/bash

currentDir=$PWD
for projectDir in "Components/Client" \
                  "Components/Server" \

do
	if [[ ! -d ${currentDir}/${projectDir}/build ]]; then
	    mkdir ${currentDir}/${projectDir}/build
	    cd ${currentDir}/${projectDir}/build && cmake ..
            cd ${currentDir}/${projectDir}/build && make
#            cd ${currentDir}/${projectDir}/build && make install
        else
	    cd ${currentDir}/${projectDir}/build && cmake ..
            cd ${currentDir}/${projectDir}/build && make
        fi
done
