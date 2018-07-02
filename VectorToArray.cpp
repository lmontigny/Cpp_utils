// Convert a vector to an array using C++11 copy

#include <iostream>
#include <algorithm>
#include <vector>

int main()
{
    std::vector<int> input({ 1, 2, 3, 4, 5 });

    int arr[input.size()];
    std::copy(input.begin(), input.end(), arr);

    for (int i: arr) {
        std::cout << i << ' ';
    }

    return 0;
}
