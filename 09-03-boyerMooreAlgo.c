#include <stdio.h>
#include <string.h>

#define NO_OF_CHARS 256

void badCharHeuristic(char *pat, int m, int badchar[]) {
    int i;
    for (i = 0; i < NO_OF_CHARS; i++)
        badchar[i] = -1;
    for (i = 0; i < m; i++)
        badchar[(unsigned char)pat[i]] = i;
}

int main() {
    char text[200], pat[50];
    printf("Enter text: ");
    scanf("%[^\n]", text);
    getchar();
    printf("Enter pattern: ");
    scanf("%[^\n]", pat);

    int n = strlen(text);
    int m = strlen(pat);
    int badchar[NO_OF_CHARS];
    int s = 0;

    badCharHeuristic(pat, m, badchar);

    int found = 0;

    while (s <= n - m) {
        int j = m - 1;
        while (j >= 0 && pat[j] == text[s + j])
            j--;
        if (j < 0) {
            printf("Pattern found at index %d\n", s);
            found = 1;
            s += (s + m < n) ? m - badchar[(unsigned char)text[s + m]] : 1;
        } else {
            int shift = j - badchar[(unsigned char)text[s + j]];
            s += (shift > 1) ? shift : 1;
        }
    }

    if (!found)
        printf("Pattern not found\n");

    return 0;
}
