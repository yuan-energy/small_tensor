#!/usr/bin/env bash
SCRIPT_DIR=$(dirname "$(readlink -f "$0")")
echo '------------------------------------------'
echo 'ltensor'
cd $SCRIPT_DIR/ltensor
time make 
echo ' '
echo ' '

echo '------------------------------------------'
echo 'libxsmm'
cd $SCRIPT_DIR/libxsmm
time make 
echo ' '
echo ' '

echo '------------------------------------------'
echo 'smalltensor'
cd $SCRIPT_DIR/smalltensor
time make 
echo ' '
echo ' '

