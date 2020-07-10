# external_sorting_cpp
This repo deals with the technique of external sorting which is employed when the data to be sorted is larger than the memory of the machine being used.

External sorting is required when the data being sorted do not fit into the main memory of a computing device (usually RAM) and instead they must reside in the slower external memory (usually a hard drive). 
External sorting typically uses a hybrid sort-merge strategy. In the sorting phase, chunks of data small enough to fit in main memory are read, sorted, and written out to a temporary file. In the merge phase, the sorted sub-files are combined into a single larger file.

One example of external sorting is the external merge sort algorithm, which sorts chunks that each fit in RAM, then merges the sorted chunks together. We first divide the file into runs such that the size of a run is small enough to fit into main memory. Then sort each run in main memory using merge sort sorting algorithm. Finally merge the resulting runs together into successively bigger runs, until the file is sorted.

The implementaion here uses these following steps:
1. Split the large input files into "k" smaller files that can be loaded into the memory (Creating Runs).
2. Sort these files using in-memory algorithms (we used merge sort).
3. Use a k-size min heap to which will have 1 elememts each from the split files.
4. Extract the min element from the heap and write in the final output.

