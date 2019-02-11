Generate .cc and .h files in windows:
TODO: download Protobuf 3.4.1 for Windows and test:
>protoc-3.2.0rc2-win32\bin\protoc.exe --proto_path=. --cpp_out=. caffe.proto

Generate .cc and .h files in Linux:
>protoc --proto_path=. --cpp_out=. caffe.proto

upgrade_proto.cpp
~$ $CAFFE_ROOT/build/tools/upgrade_net_proto_text deploy_old.prototx deploy.prototxt
~$ $CAFFE_ROOT/build/tools/upgrade_net_proto_binary deploy_old.caffemodel deploy_old.caffemodel
