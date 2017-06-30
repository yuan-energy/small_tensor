#!/bin/bash
# Input: 
#   1. filename       -> used as the include "filename";
#      The content in <filename> is not required.
#   2. permuate_number-> 2|3|4. 
# Output:
#   1. Macro file to permuate the nontype variables.

# Generate the C++ template permuate operations.
# Then include the operations in _core.hpp file.
# [python] [script] [included-filename] [permuate_num]
python permute.py expr4_subtraction_core.hpp 4
python permute.py expr3_subtraction_core.hpp 3
python permute.py expr2_subtraction_core.hpp 2
python permute.py expr4_plus_core.hpp 4
python permute.py expr3_plus_core.hpp 3
python permute.py expr2_plus_core.hpp 2
python permute.py expr4_equal_core.hpp 4
python permute.py expr3_equal_core.hpp 3

