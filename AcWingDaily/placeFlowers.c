#include <stdbool.h>

bool canPlaceFlowers(int *arr, int n, int m)
{
    int i = 0;
    int count = 0;
    if (n == 1)
    {
        return m == 0 || (m == 1 && arr[0] == 0);
    }
    while (i < n)
    {
        if (count >= m)
        {
            return true;
        }
        if (i == 0)
        {
            if (arr[i] == 0 && arr[i + 1] == 0)
            {
                arr[i] = 1;
                count++;
            }
        }
        else if (i == n - 1)
        {
            if (arr[i] == 0 && arr[i - 1] == 0)
            {
                arr[i] = 1;
                count++;
            }
        }
        else if (arr[i] == 0 && arr[i - 1] == 0 && arr[i + 1] == 0)
        {
            arr[i] = 1;
            count++;
        }
        i++;
    }
    if (count >= m)
    {
        return true;
    }
    return false;
}
