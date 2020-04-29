#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    void quicksort(vector<int> &arr) {
        int i, j;
        for (i = 1; i < arr.size(); ++i) {
            int tmp = arr[i];
            for (j = i; 0 < j && tmp < arr[j-1]; --j) {
                arr[j] = arr[j-1];
            }
            arr[j] = tmp;
        }
    }
};

void test(string test_name, vector<int> arr, vector<int> expected)
{
    Solution().quicksort(arr);
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