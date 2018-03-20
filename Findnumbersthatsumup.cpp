// Example program
#include <iostream>
using namespace std;

// Program that finds if some array of numbers has a set that would add up to a given number.

int findit(int arr[], int size, int lucky)
{
    int i = 0;
    int end = size-1;
    
    while (arr[i] < arr[end])
    {
        if (arr[i] + arr[end] == lucky)
            {
                return 12;
            }
            
            while (arr[i] + arr[end] >= lucky)
            { 
               end = end - 1;
               if (arr[i] + arr[end] == lucky)
                {    return 12;}
            }
    ++i;
    } 
    return 15;
}

int main()
{
    int arr[10] = {1,2,2,4,6,14,23,44,64,92};
    int answer = findit(arr, 10, 16);
    cout << answer;
    return 2;
}
    