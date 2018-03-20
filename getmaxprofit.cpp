#include <iostream>
#include <string>
using namespace std;

//	This is a program to get the max profit if you are given the stock prices of the previous day. For instance,
// if you the stock goes 2, 7, 1, 5, 8. You would want to buy at 1 and sell at 8 for a 7 profit. 

int get_max_profit(int stocks[], int size)
    {
        int i = 0;
        while ( stocks[i] > stocks[i+1])
            ++i;
        
        int j = i+1;
        int diff = stocks[j] - stocks[i];
        int low;
        int high;
        
        while (i <= size - 1)
        {
            while (j <= size - 1)
            {
                if (stocks[j] - stocks[i] >= diff)
                    {
                    low = stocks[i];
                    high = stocks[j];
                    diff = high - low;
                    }
                ++j;    
            }
            ++i;
            j = i + 1;
        }
        return diff;
        
    }
    
int main()
{
    int stockprice[6] = {10, 7, 5, 6, 2, 10};
    
    int diff = get_max_profit(stockprice, 6);
    
    cout << diff;

    return 2;
}
        
        