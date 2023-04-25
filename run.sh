#!/bin/bash

##########################################
# 构建项目并运行
# 
# author zhouhuajian
##########################################

buildPath=./build

if [[ ! -d ${buildPath} ]]; then
  mkdir ${buildPath}
fi

cd ${buildPath}

cmake ..

make

echo -e "\n=================================\n"

./bin/app