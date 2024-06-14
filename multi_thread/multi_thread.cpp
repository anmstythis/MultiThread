#include <iostream>
#include <thread>
#include <vector>

using namespace std;

class MergeSort
{
public:
    void Sort(vector<int>& arr)
    {
        if (arr.size() <= 1)
        {
            return;
        }

        vector<int> left(arr.begin(), arr.begin() + arr.size() / 2);
        vector<int> right(arr.begin() + arr.size() / 2, arr.end());

        thread leftThread(&MergeSort::Sort, this, std::ref(left));
        thread rightThread(&MergeSort::Sort, this, std::ref(right));

        leftThread.join();
        rightThread.join();

        Merge(arr, left, right);
    }
private:
    void Merge(vector<int>& arr, const vector<int>& left, vector<int>& right)
    {
        size_t leftIndex = 0, rightIndex = 0, mergeIndex = 0;

        while (leftIndex < left.size() && rightIndex < right.size()) {
            if (left[leftIndex] <= right[rightIndex]) {
                arr[mergeIndex++] = left[leftIndex++];
            }
            else {
                arr[mergeIndex++] = right[rightIndex++];
            }
        }

        while (leftIndex < left.size()) {
            arr[mergeIndex++] = left[leftIndex++];
        }

        while (rightIndex < right.size()) {
            arr[mergeIndex++] = right[rightIndex++];
        }
    }
};

int main()
{
    vector<int> arr(10);
    cout << "enter 10 numbers: "<<endl;
    for (int& num : arr)
    {
        cin >> num;
    }

    MergeSort sorter;

    thread sortThread([&sorter, &arr]()
        {
            sorter.Sort(arr);
        });

    sortThread.join();

    cout << "\nSorted array: ";
    for (const int& num : arr) {
        std::cout << num << " ";
    }
    cout << endl;
}
