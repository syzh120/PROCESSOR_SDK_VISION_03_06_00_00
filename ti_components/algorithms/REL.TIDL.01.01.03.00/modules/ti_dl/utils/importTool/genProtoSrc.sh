#!/bin/bash
#Generating Protobuf .cc and .h files for Caffe and Tensorflow

protoc --version

cd caffeImport
./genProtoC.sh

cd ../tfImport
mkdir -p proto_cc/tensorflow/core/framework
./genProtoC.sh
