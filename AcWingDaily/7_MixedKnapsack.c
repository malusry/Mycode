#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max(a, b) ((a) > (b) ? (a) : (b))
int main()
{
    int N, V;
    scanf("%d %d", &N, &V);

    int *v = (int *)malloc(N * sizeof(int));
    int *w = (int *)malloc(N * sizeof(int));
    int *s = (int *)malloc(N * sizeof(int));
    int *dp = (int *)malloc((V + 1) * sizeof(int));

    for (int i = 0; i <= V; i++)
    {
        dp[i] = 0;
    }
    for (int i = 0; i < N; i++)
    {
        scanf("%d %d %d", &v[i], &w[i], &s[i]);
        if (s[i] == -1)
        {
            // 01背包
            for (int j = V; j >= v[i]; j--)
            {
                dp[j] = max(dp[j], dp[j - v[i]] + w[i]);
            }
        }
        else if (s[i] == 0)
        {
            // 完全背包
            for (int j = v[i]; j <= V; j++)
            {
                dp[j] = max(dp[j], dp[j - v[i]] + w[i]);
            }
        }
        else
        {
            // 多重背包，s[i]就是数量
            int cnt = s[i];
            for (int k = 1; k <= cnt; k *= 2)
            {
                int pack_v = k * v[i];
                int pack_w = k * w[i];
                for (int j = V; j >= pack_v; j--)
                {
                    dp[j] = max(dp[j], dp[j - pack_v] + pack_w);
                }
                cnt -= k;
            }

            if (cnt > 0)
            {
                int pack_v = cnt * v[i];
                int pack_w = cnt * w[i];
                for (int j = V; j >= pack_v; j--)
                {
                    dp[j] = max(dp[j], dp[j - pack_v] + pack_w);
                }
            }
        }
    }

    printf("%d\n", dp[V]);

    free(v);
    free(w);
    free(s);
    free(dp);

    return 0;
}