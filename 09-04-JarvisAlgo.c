#include <stdio.h>
#include <stdlib.h>

typedef struct Point {
    int x, y;
} 

Point;
int orientation(Point p, Point q, Point r) {
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0) return 0; 
    return (val > 0) ? 1 : 2; 
}

void jarvisMarch(Point points[], int n) {
    if (n < 3) {
        printf("Convex hull is not possible\n");
        return;
    }

    int hull[n];
    int l = 0;

    for (int i = 1; i < n; i++) {
        if (points[i].x < points[l].x) {
            l = i;
        }
    }

    int p = l, q;
    int hullCount = 0;

    do {
        hull[hullCount++] = p;
        q = (p + 1) % n;

        for (int i = 0; i < n; i++) {
            if (orientation(points[p], points[i], points[q]) == 2) {
                q = i;
            }
        }

        p = q;
    } while (p != l);

    printf("Points in the Convex Hull are:\n");
    for (int i = 0; i < hullCount; i++) {
        printf("(%d, %d)\n", points[hull[i]].x, points[hull[i]].y);
    }
}

int main() {
    int n;
    printf("Enter the number of points: ");
    scanf("%d", &n);

    Point points[n];
    printf("Enter the coordinates of the points (x y):\n");
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &points[i].x, &points[i].y);
    }
    jarvisMarch(points, n);

    return 0;
}