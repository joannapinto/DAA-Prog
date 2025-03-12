#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICES 100

void dfs(int n, int a[MAX_VERTICES][MAX_VERTICES], int vis[], int v) {
    vis[v] = 1; 
    for (int i = 0; i < n; i++) {
        if (a[v][i] && !vis[i]) { 
            dfs(n, a, vis, i); 
        }
    }
}

int main() {
    int n;
    printf("Enter the number of vertices:\n");
    scanf("%d", &n);
    int a[MAX_VERTICES][MAX_VERTICES];
    printf("Enter the adjacency matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &a[i][j]);
        }
    }
    int vis[MAX_VERTICES] = {0}; 
    dfs(n, a, vis, 0);
    int connected = 1;
    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            connected = 0;
            break;
        }
    }
    if (connected) {
        printf("The graph is connected\n");
    } else {
        printf("The graph is disconnected\n");
    }
    return 0;
}




