#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int pos;
    int speed;
} Car;

int compare(const void* a, const void* b) {
    return ((Car*)b)->pos - ((Car*)a)->pos;
}

int main() {
    int target, n;
    if (scanf("%d %d", &target, &n) != 2) return 0;
    
    if (n == 0) {
        printf("0\n");
        return 0;
    }

    Car* cars = (Car*)malloc(n * sizeof(Car));
    for (int i = 0; i < n; i++) {
        scanf("%d", &cars[i].pos);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &cars[i].speed);
    }

    qsort(cars, n, sizeof(Car), compare);

    int fleets = 0;
    double maxTime = 0.0;

    for (int i = 0; i < n; i++) {
        double time = (double)(target - cars[i].pos) / cars[i].speed;
        if (time > maxTime) {
            fleets++;
            maxTime = time;
        }
    }

    printf("%d\n", fleets);

    free(cars);
    return 0;
}