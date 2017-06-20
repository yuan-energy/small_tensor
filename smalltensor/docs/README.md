Level 1
Call libxsmm directly with memory alignment and specified tensor/matrices dimension.

Level 2
Asynchronous with promise/future. 
(No control of extra memory, no guarantee of memory prefetch, but make the batch layer possible.)

Level 3
Copy the task tuple (1 operation, 3 references) to the concurrent queue, 
which is a single-writer-multiple-reader queue. 
The readers consume the tasks batch by batch with memory prefetch.

Level 4
Enable smalltensor runnable on purely GPU memory. Input and output are also from GPU memory.
GPU is suitable for iterations.