#include <stdio.h>
#include <string.h>

void computeLPS(char *pat, int m, int *lps) {
    int len = 0, i = 1;
    lps[0] = 0;
    while (i < m) {
        if (pat[i] == pat[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0)
                len = lps[len - 1];
            else {
                lps[i] = 0;
                i++;
            }
        }
    }
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
    int lps[m], i = 0, j = 0;

    computeLPS(pat, m, lps);

    int found = 0;
    while (i < n) {
        if (pat[j] == text[i]) {
            i++;
            j++;
        }
        if (j == m) {
            printf("Pattern found at index %d\n", i - j);
            found = 1;
            j = lps[j - 1];
        } else if (i < n && pat[j] != text[i]) {
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }
    if (!found)
        printf("Pattern not found\n");

    return 0;
}
