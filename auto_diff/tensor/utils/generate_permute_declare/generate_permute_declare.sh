#!/bin/bash
# Input: 
#   Nothing
# Output:
#   Declare of the copy assignment operations.
#   Copy the generated lines into expr3|expr4.hpp to declare
#   the prototype operations.

python permute3_generate_prototype.py
python permute4_generate_prototype.py

