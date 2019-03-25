#!/bin/sh

currentDir=$PWD
git checkout develop
git pull origin develop
cd ${currentDir}/Components/Client
git checkout develop
git pull origin develop
cd ${currentDir}/Components/Server
git checkout develop
git pull origin develop
cd ${currentDir}/Components/Commun
git checkout develop
git pull origin develop
cd ${currentDir}/OpenLibs/googletest
git checkout master
git pull origin master
cd ${currentDir}/OpenLibs/boost
git checkout master
git pull origin master
cd ${currentDir}/OpenLibs/msgpack
git checkout master
git pull origin master
cd ${currentDir}/OpenLibs/sckcpp
git checkout master
git pull origin master
cd ${currentDir}/OpenLibs/plog
git checkout master
git pull origin master

