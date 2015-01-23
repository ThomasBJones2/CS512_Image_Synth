
using namespace std;

void merge(object* input, int dim, int p, int r)
{
    int mid = (p + r) / 2;
    int i1 = 0;
    int i2 = p;
    int i3 = mid + 1;

    // Temp array
    object temp[r-p+1];

    // Merge in sorted form the 2 arrays
    while ( i2 <= mid && i3 <= r )
        if ( input[i2].center[dim] < input[i3].center[dim] )
            temp[i1++] = input[i2++];
        else
            temp[i1++] = input[i3++];

    // Merge the remaining elements in left array
    while ( i2 <= mid )
        temp[i1++] = input[i2++];

    // Merge the remaining elements in right array
    while ( i3 <= r )
        temp[i1++] = input[i3++];

    // Move from temp array to master array
    for ( int i = p; i <= r; i++ )
        input[i] = temp[i-p];
}

void merge_sort(object* input, int dim, int p, int r)
{
    if ( p < r )
    {
        int mid = (p + r)/2;
        merge_sort(input, dim, p, mid);
        merge_sort(input, dim, mid + 1, r);
        merge(input, dim, p, r);
    }
}
