#include <stdlib.h>

int maxProductAfterCutting(int length)
{
    int *dp = (int *)malloc((length + 1) * sizeof(int));

    for (int i = 2; i <= length; i++)
    {
        for (int j = 1; j <= i - 1; j++)
        {
            dp[i] = max(j * (i - j), j * dp[i - j]);
        }
    }
}