#include <stdio.h>
#include <stdlib.h>
#define max(a, b) ((a) > (b) ? (a) : (b))
int main()
{

    int N, V, M;
    scanf("%d %d %d", &N, &V, &M);

    int *v = (int *)malloc(N * sizeof(int));
    int *w = (int *)malloc(N * sizeof(int));
    int *m = (int *)malloc(N * sizeof(int));
    int **dp = malloc((V + 1) * sizeof(int *));

    for (int i = 0; i < V + 1; i++)
    {
        dp[i] = (int *)malloc((M + 1) * sizeof(int));
        for (int j = 0; j < M + 1; j++)
        {
            dp[i][j] = 0;
        }
    }

    for (int i = 0; i < N; i++)
    {
        scanf("%d %d %d", &v[i], &m[i], &w[i]);
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = V; j >= v[i]; j--)
        {
            for (int z = M; z >= m[i]; z--)
            {
                dp[j][z] = max(dp[j][z], dp[j - v[i]][z - m[i]] + w[i]);
            }
        }
    }

    printf("%d\n", dp[V][M]);

    free(v);
    free(m);
    free(w);

    for (int i = 0; i < V + 1; i++)
    {
        free(dp[i]);
    }
    free(dp);
    return 0;
}