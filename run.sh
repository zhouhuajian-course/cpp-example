#!/bin/bash

buildPath=./build

if [[ ! -d ${buildPath} ]]; then
  mkdir ${buildPath}
fi

cd ${buildPath}

cmake ..

make

echo -e "\n=================================\n"

./bin/app