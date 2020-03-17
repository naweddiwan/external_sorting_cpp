// C++ program to implement external sorting using
// merge sort
#include <bits/stdc++.h>
#define ll long long
using namespace std;

struct MinHeapNode
{
    // The element to be stored
    string element;

    // index of the array from which the element is taken
    int i;
};

// Prototype of a utility function to swap two min heap nodes
void swap(MinHeapNode *x, MinHeapNode *y);

// A class for Min Heap
class MinHeap
{
    MinHeapNode *harr; // pointer to array of elements in heap
    int heap_size;     // size of min heap

public:
    // Constructor: creates a min heap of given size
    MinHeap(MinHeapNode a[], int size);

    // to heapify a subtree with root at given index
    void MinHeapify(int);

    // to get index of left child of node at index i
    int left(int i) { return (2 * i + 1); }

    // to get index of right child of node at index i
    int right(int i) { return (2 * i + 2); }

    // to get the root
    MinHeapNode getMin() 
    { 
        return harr[0]; 
    }

    // to replace root with new node x and heapify()
    // new root
    void replaceMin(MinHeapNode x)
    {
        harr[0] = x;
        MinHeapify(0);
    }
};

// Constructor: Builds a heap from a given array a[]
// of given size
MinHeap::MinHeap(MinHeapNode a[], int size)
{
    heap_size = size;
    harr = a; // store address of array
    int i = (heap_size - 1) / 2;
    while (i >= 0)
    {
        MinHeapify(i);
        i--;
    }
}

// A recursive method to heapify a subtree with root
// at given index. 
//This method assumes that the
// subtrees are already heapified
void MinHeap::MinHeapify(int i)
{
    int l = left(i);
    int r = right(i);
    int smallest = i;
    if (l < heap_size && harr[l].element < harr[i].element)
        smallest = l;
    if (r < heap_size && harr[r].element < harr[smallest].element)
        smallest = r;
    if (smallest != i)
    {
        swap(&harr[i], &harr[smallest]);
        MinHeapify(smallest);
    }
}

// A utility function to swap two elements
void swap(MinHeapNode *x, MinHeapNode *y)
{
    MinHeapNode temp = *x;
    *x = *y;
    *y = temp;
}

void merge(vector<string> &arr, ll l, ll m, ll r)
{
    ll i, j, k;
    ll n = r - l + 1;
    vector<string> temp(n);
    i = l;
    j = m + 1;
    k = 0;
    while (i <= m && j <= r)
    {
        if (arr[i] <= arr[j])
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }
    while (i <= m)
        temp[k++] = arr[i++];
    while (j <= r)
        temp[k++] = arr[j++];
    for (i = l; i <= r; i++)
        arr[i] = temp[i - l];
}
void merge_sort(vector<string> &arr, ll l, ll r)
{
    ll m;
    if (l < r)
    {
        m = l + (r - l) / 2;
        merge_sort(arr, l, m);
        merge_sort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

// Merges k sorted files. Names of files are assumed
// to be file_1, file_2, file_3, ... file_k
void mergeFiles(char *output_file, int n, int k)
{
    cout << "Merging Files......." << endl;

    ifstream *in = new ifstream[k];

    for (int i = 0; i < k; i++)
    {
        string s= "file_"+to_string(i+1);
        in[i].open(s);
    }
  
    // FINAL OUTPUT FILE
    ofstream out;
    out.open(output_file);

    // Create a min heap with k heap nodes. Every heap node
    // has first element of scratch output file
    MinHeapNode *harr = new MinHeapNode[k];
    int i;

    for (i = 0; i < k; i++)
    {
        // break if no output file is empty and
        // index i will be no. of input files
        if (!in[i])
        {
            break;
        }
        else
        {
            string s;
            getline(in[i], s);
            //cout << s << endl;
            harr[i].element = s;
        }

        harr[i].i = i; // Index of scratch output file
    }
    MinHeap hp(harr, i); // Create the heap

    int count = 0;

    // Now one by one get the minimum element from min
    // heap and replace it with next element.
    // run till all filled input files reach EOF
   
    while (count != i)
    {
        // Get the minimum element and store it in output file
        MinHeapNode root = hp.getMin();
        //fprintf(out, "%s ", root.element);

        out << root.element << endl;

        // Find the next element that will replace current
        // root of heap. The next element belongs to same
        // input file as the current min element.
        if (in[root.i])
        {
            string s;
            getline(in[root.i], s);
            root.element = s;
            
        }
        else
        {
            root.element = "ZZZZZZ";
            count++;
        }

        // Replace root with next element of input file
        hp.replaceMin(root);
    }

    // close input and output files
    for (int i = 0; i < k; i++)
        in[i].close();

    out.close();
  
    delete[] in;
}

// Using a merge-sort algorithm, create the initial runs
// and divide them evenly among the output files

void createInitialRuns(char *input_file, int run_size,
                       int num_ways)
{
    // For big input file
    cout << "Creating Initial Runs........" << endl;

    ifstream in;
    in.open(input_file);

    // output scratch files
    ofstream *out = new ofstream[num_ways];
 

    char fileName[2];
    for (int i = 0; i < num_ways; i++)
    {
        // convert i to string
        string s;
        s = "file_"+to_string(i+1);
        out[i].open(s);
    }

    // allocate a dynamic array large enough
    // to accommodate runs of size run_size
    vector<string> arr(run_size);
    bool more_input = true;
    int next_output_file = 0;

    int i;
    while (more_input)
    {
        // write run_size elements into arr from input file
        for (i = 0; i < run_size; i++)
        {
            //reading from file
            if (!in)
            {
                more_input = false;
                break;
            }

            string line;
            getline(in, line);
            if (line != "") // excluding blank lines
                arr[i] = line;

        }
        if (!more_input)
            break;
        // sort array using merge sort
        merge_sort(arr, 0, i - 1);
        // write the records to the appropriate scratch output file
        // can't assume that the loop runs to run_size
        // since the last run's length may be less than run_size
        for (int j = 0; j < i; j++)
            out[next_output_file] << arr[j] << endl;
       
        cout << "Creating Sorted Split: " << next_output_file + 1 << " file(s) out of " << num_ways << endl;
        next_output_file++;
    }

    // close input and output files
    for (int i = 0; i < num_ways; i++)
        out[i].close();

    in.close();
    delete[] out;
}

// For sorting data stored on disk
void externalSort(char *input_file, char *output_file,
                  int num_ways, int run_size)
{
    // read the input file, create the initial runs,
    // and assign the runs to the scratch output files
    createInitialRuns(input_file, run_size, num_ways);

    // Merge the runs using the K-way merging
    mergeFiles(output_file, run_size, num_ways);
}

// Driver program to test above

int main()
{
    // No. of Partitions of input file.
    // deciding the no. of splits of the input files
    
    // In this case we are splitting a 300 line of text file into 3 files
    // Each file containing 100 lines.
    int num_ways = 3;

    // The size of each partition, total bytes = 100*40 = 4000bytes in ceach partition
    // approx 40 characters in each line
    //Take care while taking the size of run_size because
    // this is the size that will be loaded as well as sorted using merge sort.
    int run_size = 100;

    char input_file[] = "input.txt";
    char output_file[] = "output.txt";
 

    externalSort(input_file, output_file, num_ways,run_size);

    return 0;
}
