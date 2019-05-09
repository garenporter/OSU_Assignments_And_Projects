Both insertsort.cpp and meregesort.cpp expect there to be a data.txt file in the same directory.
If data.txt is not there, the program will do nothing. Passing in the file as an argument will do nothing.

insertsort.cpp writes its input to a file called insert.out, while mergesort.cpp write its output to merge.out.
Each line of the output files will be sorted. Newlines in the file indicate a different sorted vector.

mergeTime.cpp sorts 50 vectors and insertTime.cpp sorts 10 vectors. For some reason, if mergeTime.cpp
sorted less than 50 vectors, the times would not make sense. I only use the first 10 times when graphing
data.

Note that insertTime.cpp takes a long time to complete, so have patience. 