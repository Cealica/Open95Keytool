#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void key_generator(int p1_key[], int p2_key[], int size1, int size2) {
    for (int key_1 = 0; key_1 < 1; key_1++) {
        for (int key_2 = 0; key_2 < 7; key_2++) {
            p2_key[key_2] = rand() % 9; // This generates the value of the second part of the key.
        }
        p1_key[key_1] = rand() % 999; // This generates the value of the first part of the key.
    }
}

int p1_authChecker(int arr1[], int size1, int arr2[], int size1_false) {
    for (int i = 0; i < size1; i++) {
        for (int j = 0; j < size1_false; j++) {
            if (arr1[i] == arr2[j]) {
                return 1; // Found a duplicate
            }
        }
    }
    return 0; // No duplicates found
}

int p2_authChecker(int arr2[], int size2) {
    int sum = 0;
    for (int p2 = 0; p2 < size2; p2++) {
        sum = sum + arr2[p2];
    }
    return sum % 7; // Calculate the remainder
}

int main() {
    // Seed the random generator with the current time
    srand(time(NULL));

    // This contains the array used to store the keys.
    // The p1 is the first part of the key (123-XXXXXXX).
    // The p2 is the second part of the key (XXX-1234567).
    // The sizes are used for logic in this code.
    int p1_key[2];
    int p2_key[7];
    int p1_key_false[] = {333, 444, 555, 666, 777, 888, 999};
    int size1 = sizeof(p1_key) / sizeof(p1_key[0]);
    int size1_false = sizeof(p1_key_false) / sizeof(p1_key_false[0]);
    int size2 = sizeof(p2_key) / sizeof(p2_key[0]);

    do {
        // Populate both arrays with numbers between 0 to 9.
        key_generator(p1_key, p2_key, size1, size2);

        // P1 Authentication key checker.
        if (p1_authChecker(p1_key, size1, p1_key_false, size1_false)) {
            continue;  // Regenerate the keys
        } else {
            printf("");
        }

        // P2 Authentication key checker.
        int p2_auth_1 = p2_authChecker(p2_key, size2);
        if (p2_auth_1 == 0) {
            printf("");
        } else {
            continue; // Regenerate the keys
        }

        // If either p1_key or p2_key authentication failed, regenerate the keys.
    } while (p1_authChecker(p1_key, size1, p1_key_false, size1_false) || p2_authChecker(p2_key, size2) != 0);

    // Test print output from both arrays.
    printf("p1_key: ");
    for (int gen1 = 0; gen1 < 1; gen1++) {
        printf("%03d ", p1_key[gen1]);
    }

    printf("\np2_key: ");
    for (int gen2 = 0; gen2 < 7; gen2++) {
        printf("%d ", p2_key[gen2]);
    }

    printf("\n");

    return 0;
}
