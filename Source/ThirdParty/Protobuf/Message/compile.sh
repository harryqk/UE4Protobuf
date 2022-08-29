#!/bin/bash
echo "start"
SRC_DIR="/Volumes/Mac/Develop/UEProjects/UE4Protobuf1/Source/ThirdParty/Protobuf/Message"
DST_DIR="/Volumes/Mac/Develop/UEProjects/UE4Protobuf1/Source/ThirdParty/Protobuf/Message"
protoc -I=$SRC_DIR --cpp_out=$DST_DIR $SRC_DIR/addressbook.proto
echo "finish"