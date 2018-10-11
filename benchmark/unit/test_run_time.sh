#!/usr/bin/env bash
SCRIPT_DIR=$(dirname "$(readlink -f "$0")")
echo '------------------------------------------'
echo 'ltensor'
cd $SCRIPT_DIR/ltensor
make 
./a.out
echo ' '
echo ' '

echo '------------------------------------------'
echo 'libxsmm'
cd $SCRIPT_DIR/libxsmm
make 
./a.out
echo ' '
echo ' '

echo '------------------------------------------'
echo 'smalltensor'
cd $SCRIPT_DIR/smalltensor
make 
./a.out
echo ' '
echo ' '

