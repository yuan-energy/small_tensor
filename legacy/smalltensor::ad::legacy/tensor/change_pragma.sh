files=./*

# for f in $files
# do
# 	echo "Processing $f file ..."
# 	cat $f
# done

find . -type f -name "*.h*" -exec sed -e "/ifndef/,+1d" -i {} \;
find . -type f -name "*.h*" -exec sed -e "/#endif/d" -i {} \;
find . -type f -name "*.h*" -exec sed -e "1i #pragma once" -i {} \;

# files=( $(find . -name "*.h*" ) )
# # deepest_dir_array=( $(find . -type d -links 3 ) )

# # for element in $(seq 0 $((${#deepest_dir_array[@]} - 1)))
# for element in $files
# do
# 	echo "Processing $element file ..."
# 	# cat $element
# done
