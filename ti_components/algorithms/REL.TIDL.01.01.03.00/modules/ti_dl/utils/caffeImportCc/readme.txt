>protoc-3.2.0rc2-win32\bin\protoc.exe --proto_path=. --cpp_out=. caffe.proto

upgrade_proto.cpp
~$ $CAFFE_ROOT/build/tools/upgrade_net_proto_text deploy_old.prototx deploy.prototxt
~$ $CAFFE_ROOT/build/tools/upgrade_net_proto_binary deploy_old.caffemodel deploy_old.caffemodel