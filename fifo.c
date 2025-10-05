#include <stdio.h>
int main() {
    int i, j, n, no, a[50], frame[10], count = 0, avail, k;

    printf("\nEnter the number of frames: ");
    scanf("%d", &no);

    printf("Enter the number of pages: ");
    scanf("%d", &n);

    printf("Enter the reference string: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    for (i = 0; i < no; i++) {
        frame[i] = -1; 
    }

    j = 0; 
    printf("\nReference String\tPage Frames\n");

    for (i = 0; i < n; i++) {
        printf("%d\t\t", a[i]);
        avail = 0;

        for (k = 0; k < no; k++) {
            if (frame[k] == a[i]) {
                avail = 1;
                break;
            }
        }

        if (!avail) {
            frame[j] = a[i];
            j = (j + 1) % no;
            count++;
        }

        for (k = 0; k < no; k++) {
            if (frame[k] != -1) {
                printf("%d\t", frame[k]);
            } else {
                printf("-\t");
            }
        }
        printf("\n");
    }

    printf("\nTotal Page Faults: %d\n", count);
    return 0;
}

