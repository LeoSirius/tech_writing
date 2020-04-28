#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    void bubble_sort(vector<int> &arr)
    {
        int i, j;
        for (i = arr.size() - 2; 0 <= i; --i) {
            for (int j = i; j < arr.size() - 1; ++j) {
                if (arr[j] > arr[j+1])
                    swap(arr[j], arr[j+1]);
            }
        }
    }
};

void test(string test_name, vector<int> arr, vector<int> expected)
{
    Solution().bubble_sort(arr);
    for (auto i : arr) cout << i << " ";
    cout << endl;
    if (arr == expected)
        cout << test_name << " success." << endl;
    else
        cout << test_name << " failed." << endl;
}

int main()
{
    vector<int> arr1 = {9,8,0,7,6,5,4,1,2,3};
    vector<int> expected1 = {0,1,2,3,4,5,6,7,8,9};
    test("test1", arr1, expected1);


    return 0;
}