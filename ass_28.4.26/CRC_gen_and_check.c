// Q1. Write a menu-driven C program to perform both CRC generation and checking.

#include <stdio.h>
#include <string.h>

// Function to perform XOR operation
void xorOperation(char *dividend, char *divisor, int start) {
    for (int i = 0; i < strlen(divisor); i++) {
        dividend[start + i] = (dividend[start + i] == divisor[i]) ? '0' : '1';
    }
}

// Function to perform CRC calculation
void computeCRC(char *data, char *divisor, char *remainder) {
    int dataLen = strlen(data);
    int divisorLen = strlen(divisor);

    char temp[100];
    strcpy(temp, data);

    for (int i = 0; i <= dataLen - divisorLen; i++) {
        if (temp[i] == '1') {
            xorOperation(temp, divisor, i);
        }
    }

    // Copy remainder
    for (int i = 0; i < divisorLen - 1; i++) {
        remainder[i] = temp[dataLen - divisorLen + 1 + i];
    }
    remainder[divisorLen - 1] = '\0';
}


// Function for CRC Generation (Sender)
void crcGenerate() {
    char data[100], divisor[100];
    char appendedData[100], remainder[100];

    printf("\nEnter Data (binary): ");
    scanf("%s", data);

    printf("Enter Divisor (binary): ");
    scanf("%s", divisor);

    int dataLen = strlen(data);
    int divisorLen = strlen(divisor);

    // Append zeros
    strcpy(appendedData, data);
    for (int i = 0; i < divisorLen - 1; i++) {
        appendedData[dataLen + i] = '0';
    }
    appendedData[dataLen + divisorLen - 1] = '\0';

    // Compute remainder
    computeCRC(appendedData, divisor, remainder);

    // Form transmitted data
    char transmitted[100];
    strcpy(transmitted, data);
    strcat(transmitted, remainder);

    printf("\nCRC Remainder: %s", remainder);
    printf("\nTransmitted Data: %s\n", transmitted);
}

// Function for CRC Checking (Receiver)
void crcCheck() {
    char received[100], divisor[100];
    char remainder[100];

    printf("\nEnter Received Data (binary): ");
    scanf("%s", received);

    printf("Enter Divisor (binary): ");
    scanf("%s", divisor);

    computeCRC(received, divisor, remainder);

    // Check if remainder is zero
    int error = 0;
    for (int i = 0; i < strlen(remainder); i++) {
        if (remainder[i] != '0') {
            error = 1;
            break;
        }
    }

    if (error)
        printf("\nError detected in received data!\n");
    else
        printf("\nNo error detected. Data is correct.\n");
}

int main() {
    int choice;

    do {
        printf("\n===== CRC Menu =====\n");
        printf("1. CRC Generation (Sender)\n");
        printf("2. CRC Checking (Receiver)\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                crcGenerate();
                break;
            case 2:
                crcCheck();
                break;
            case 3:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice! Try again.\n");
        }

    } while (choice != 3);

    return 0;
}

/*
Output 1: 

===== CRC Menu =====
1. CRC Generation (Sender)
2. CRC Checking (Receiver)
3. Exit
Enter your choice: 1

Enter Data (binary): 1101
Enter Divisor (binary): 1011

CRC Remainder: 001
Transmitted Data: 1101001

===== CRC Menu =====
1. CRC Generation (Sender)
2. CRC Checking (Receiver)
3. Exit
Enter your choice: 2

Enter Received Data (binary): 1101001
Enter Divisor (binary): 1011

No error detected. Data is correct.

Output 2:

===== CRC Menu =====
1. CRC Generation (Sender)
2. CRC Checking (Receiver)
3. Exit
Enter your choice: 2

Enter Received Data (binary): 1101011
Enter Divisor (binary): 1011

Error detected in received data!

*/
