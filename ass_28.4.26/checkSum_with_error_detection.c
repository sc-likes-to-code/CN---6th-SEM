#include <stdio.h>
#include <string.h>

// Function to perform 1's complement addition
int onesComplementAdd(int a, int b, int bits) {
    int sum = a + b;
    int max = (1 << bits) - 1;

    // Wrap around carry
    while (sum > max) {
        sum = (sum & max) + (sum >> bits);
    }

    return sum;
}

// Function to compute checksum
int computeChecksum(int data[], int n, int bits) {
    int sum = 0;

    for (int i = 0; i < n; i++) {
        sum = onesComplementAdd(sum, data[i], bits);
    }

    // Take 1's complement
    return (~sum) & ((1 << bits) - 1);
}

// Function to verify checksum
int verifyChecksum(int data[], int n, int checksum, int bits) {
    int sum = 0;

    for (int i = 0; i < n; i++) {
        sum = onesComplementAdd(sum, data[i], bits);
    }

    sum = onesComplementAdd(sum, checksum, bits);

    // If result is all 1s → no error
    return (sum == (1 << bits) - 1);
}

int main() {
    int n, bits;

    printf("Enter number of segments: ");
    scanf("%d", &n);

    printf("Enter number of bits per segment: ");
    scanf("%d", &bits);

    int data[100];

    printf("Enter the data segments (in decimal):\n");
    for (int i = 0; i < n; i++) {
        printf("Segment %d: ", i + 1);
        scanf("%d", &data[i]);
    }

    // Sender side
    int checksum = computeChecksum(data, n, bits);
    printf("\nComputed Checksum: %d\n", checksum);

    // Receiver side (copy data)
    int received[100];
    for (int i = 0; i < n; i++) {
        received[i] = data[i];
    }

    int choice;
    printf("\nDo you want to introduce error? (1 = Yes, 0 = No): ");
    scanf("%d", &choice);

    if (choice == 1) {
        int pos, value;
        printf("Enter segment position to alter (1 to %d): ", n);
        scanf("%d", &pos);

        printf("Enter new value for that segment: ");
        scanf("%d", &value);

        received[pos - 1] = value;
    }

    // Verification
    if (verifyChecksum(received, n, checksum, bits)) {
        printf("\nNo error detected in received data.\n");
    } else {
        printf("\nError detected in received data!\n");
    }

    return 0;
}

/*
Output 1:

Enter number of segments: 4
Enter number of bits per segment: 4

Enter the data segments (in decimal):
Segment 1: 5
Segment 2: 7
Segment 3: 3
Segment 4: 2

Computed Checksum: 2

Do you want to introduce error? (1 = Yes, 0 = No): 0

No error detected in received data.

Output 2:

Enter number of segments: 4
Enter number of bits per segment: 4

Enter the data segments (in decimal):
Segment 1: 5
Segment 2: 7
Segment 3: 3
Segment 4: 2

Computed Checksum: 2

Do you want to introduce error? (1 = Yes, 0 = No): 1
Enter segment position to alter (1 to 4): 2
Enter new value for that segment: 6

Error detected in received data!
*/
