#include <stdio.h>

int main() {
    int n;
    printf("Enter n: ");
    scanf("%d", &n);
    
    int P[n];
    
    for (int i = 2; i <= n; i++) {
        P[i] = i;
    }
    
    for (int p = 2; p <= n; p++) {
        if (P[p] != 0) {
            for (int j = 2 * p; j <= n; j += p) {
                P[j] = 0;
            }
        }
    }
    
    for (int i = 2; i <= n; i++) {
        if (P[i] != 0) {
            printf("%d ", P[i]);
        }
    }
    
    return 0;
}