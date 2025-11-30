#include <stdio.h>
#include <string.h>

#define d 37 //256
#define q 31 //101

int main() {
    char text[200], pattern[50];
    int n, m;
    printf("Enter text: ");
    scanf("%[^\n]", text);
    getchar();
    printf("Enter pattern: ");
    scanf("%[^\n]", pattern);

    n = strlen(text);
    m = strlen(pattern);

    int i, j;
    int p = 0, t = 0, h = 1;

    for (i = 0; i < m - 1; i++)
        h = (h * d) % q;

    for (i = 0; i < m; i++) {
        p = (d * p + pattern[i]) % q;
        t = (d * t + text[i]) % q;
    }

    int found = 0;

    for (i = 0; i <= n - m; i++) {
        if (p == t) {
            int match = 1;
            for (j = 0; j < m; j++) {
                if (text[i + j] != pattern[j]) {
                    match = 0;
                    break;
                }
            }
            if (match) {
                printf("Pattern found at index %d\n", i);
                found = 1;
            }
        }
        if (i < n - m) {
            t = (d * (t - text[i] * h) + text[i + 1 + (m - 1)]) % q;
            if (t < 0)
                t += q;
        }
    }

    if (!found)
        printf("Pattern not found\n");

    return 0;
}
