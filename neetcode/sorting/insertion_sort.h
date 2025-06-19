#include <vector>
#include <algorithm>
#include <iostream>

// behaves good when list is already sorted or partial sorted
void insertion_sort(std::vector<int> &array)
{
    for (int i = 1; i < array.size(); i++)
    {
        // put each element in sorted sub array [0, i)
        // probe current element in previous sub array
        int j = i;
        while (j > 0 && array[j] < array[j - 1])
        {
            std::swap(array[j], array[j - 1]);
            j--;
        }
    }
}

//bubble up each max element
void bubble_sort(std::vector<int>& array)
{
    bool is_sorted = false;
    
    //swap consecutive element until max reaches the end
    for(int i=0;i<array.size();i++)
    {
        is_sorted = true;
        for(int j = 0;j<array.size()-i-1;j++)
        {        
            if(array[j] > array[j+1])
            {
                is_sorted = false;
                std::swap(array[j], array[j+1]);
            }           
        }

        if(is_sorted)
        {
            break;
        }
    }
}

//find max and swap with last element
void selection_sort(std::vector<int>& array)
{
    //at each iteration find max and swap
    for(int i=0;i<array.size();i++)
    {
        int posMax = 0;
        for(int j=1;j<array.size()-i;j++)
        {
            if(array[posMax] < array[j])
            {
                posMax = j;
            }
        }
        std::swap(array[posMax], array[array.size()-i-1]);
    }
}

void insert_in_already_sorted(std::vector<int> &array, int el)
{
    int i = 0;
    while (i < array.size() && el > array[i])
    {
        i++;
    }

    auto it = array.begin();
    std::advance(it, i);

    // progressive copy from the back
    // it can be array.end() and just does push_back
    array.insert(it, el);
}

void insert_in_already_sorted_binary_search(std::vector<int> &array, int el)
{
    // stl binary search to get first element greater or equal
    auto it = std::lower_bound(array.begin(), array.end(), el);

    // progressive copy from the back
    // it can be array.end() and just does push_back
    array.insert(it, el);
}

bool same_arrays(const std::vector<int> &a1, const std::vector<int> &a2)
{
    return std::equal(a1.begin(), a1.end(), a2.begin());
}

void print_array(const std::vector<int> &a)
{
    std::for_each(a.begin(), a.end(), [](int a)
                  { std::cout << a << ", "; });
}

int main()
{
    std::vector<int> expected = {1, 2, 3, 4, 5, 5, 6, 7};
    std::vector<int> actual = {6, 2, 5, 1, 3, 4, 5, 7};

    insertion_sort(actual);

    std::cout << same_arrays(expected, actual) << "\n";
    print_array(actual);

    return 0;
}


//inplace merging of two sub arrays
void merge_sub_arrays(std::vector<int>& array, int start, int pivot, int end)
{
    int i = start;
    int j = pivot + 1;
    
    while(i <= pivot && j <= end)
    {
        //already in place
        if(array[i] < array[j])
        {
            i++;
        }
        //copy all elements from right to left between the sub arrays
        else
        {
            int temp = array[j];
            for(int k=j;k>i;k--)
            {
                array[k] = array[k-1];
            }
            array[i] = temp;
            
            i++;
            j++;
            pivot++;
        }
    }
}

void merge_recursive(std::vector<int>& array, int start, int end)
{
    if(start >= end)
    {
        return;
    }
    
    int pivot = (start + end) / 2;
    merge_recursive(array, start, pivot);
    merge_recursive(array, pivot + 1, end);
    
    merge_sub_arrays(array, start, pivot, end);
}

//using hoare algorithm partition last element
int partition(std::vector<int>& array, int start, int end)
{
    int i = start;
    int j = end - 1;
    while(i <= j)
    {
        if(array[i] < array[end])
        {
            i++;
        }
        else
        {
            if(array[j] > array[end])
            {
                j--;
            }
            else
            {
                std::swap(array[i], array[j]);
                i++;
                j--;
            }
        }
    }
    
    std::swap(array[i], array[end]);
    
    return i;
}

void quicksort(std::vector<int>& array, int start, int end)
{
    if(start >= end)
    {
        return;
    }
    
    int pivot = partition(array, start, end);
    quicksort(array, start, pivot - 1);
    quicksort(array, pivot + 1, end);
}

