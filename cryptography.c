#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_LEN 1000

typedef struct {
    int frequency;
    int time;
} Signal;

Signal letterMap[26];

void initMap() {
    for (int i = 0; i < 26; i++) {
        letterMap[i].frequency = 100 + i * 10; // A=100Hz, B=110Hz...
        letterMap[i].time = 50 + i * 5;        // A=50ms, B=55ms...
    }
}

void encryptText(const char *text, Signal *encrypted, int *length) {
    *length = 0;
    for (int i = 0; text[i] != '\0'; i++) {
        char ch = toupper(text[i]);
        if (ch >= 'A' && ch <= 'Z') {
            encrypted[*length] = letterMap[ch - 'A'];
            (*length)++;
        }
    }
}

void decryptSignal(Signal *encrypted, int length, char *output) {
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < 26; j++) {
            if (encrypted[i].frequency == letterMap[j].frequency &&
                encrypted[i].time == letterMap[j].time) {
                output[i] = 'A' + j;
                break;
            }
        }
    }
    output[length] = '\0';
}

void displayEncrypted(Signal *encrypted, int length) {
    printf("\nEncrypted Output (Frequency Hz, Time ms):\n");
    for (int i = 0; i < length; i++) {
        printf("(%dHz, %dms) ", encrypted[i].frequency, encrypted[i].time);
    }
    printf("\n");
}

void readMessageFromFile(const char *filename, char *text) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        printf("❌ File not found: %s\n", filename);
        return;
    }
    fgets(text, MAX_LEN, f);
    fclose(f);
    text[strcspn(text, "\n")] = '\0'; // remove newline
}

void saveEncryptedToFile(Signal *encrypted, int length, const char *filename) {
    FILE *f = fopen(filename, "w");
    for (int i = 0; i < length; i++) {
        fprintf(f, "%d %d\n", encrypted[i].frequency, encrypted[i].time);
    }
    fclose(f);
}

int loadEncryptedFromFile(Signal *encrypted, const char *filename) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        printf("❌ File not found: %s\n", filename);
        return 0;
    }
    int count = 0;
    while (fscanf(f, "%d %d", &encrypted[count].frequency, &encrypted[count].time) == 2) {
        count++;
    }
    fclose(f);
    return count;
}

void saveDecryptedToFile(char *text, const char *filename) {
    FILE *f = fopen(filename, "w");
    fprintf(f, "%s", text);
    fclose(f);
}

void manualDecryption() {
    int n;
    printf("Enter number of frequency-time pairs: ");
    scanf("%d", &n);
    Signal encrypted[MAX_LEN];
    printf("Enter frequency and time pairs (e.g. 170 85):\n");
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &encrypted[i].frequency, &encrypted[i].time);
    }
    char output[MAX_LEN];
    decryptSignal(encrypted, n, output);
    printf("Decrypted Message: %s\n", output);
}

void menu() {
    int choice;
    char inputText[MAX_LEN];
    char decryptedText[MAX_LEN];
    Signal encrypted[MAX_LEN];
    int len = 0;

    while (1) {
        printf("\n--- Cryptography using Frequency and Time ---\n");
        printf("1. Encrypt message (manual input)\n");
        printf("2. Encrypt message from file (message.txt)\n");
        printf("3. Decrypt from encrypted.txt\n");
        printf("4. Manual frequency-time input decryption\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // consume newline

        switch (choice) {
            case 1:
                printf("Enter message to encrypt (A-Z only): ");
                fgets(inputText, MAX_LEN, stdin);
                inputText[strcspn(inputText, "\n")] = '\0';
                encryptText(inputText, encrypted, &len);
                displayEncrypted(encrypted, len);
                saveEncryptedToFile(encrypted, len, "encrypted.txt");
                break;

            case 2:
                readMessageFromFile("message.txt", inputText);
                printf("Message Read: %s\n", inputText);
                encryptText(inputText, encrypted, &len);
                displayEncrypted(encrypted, len);
                saveEncryptedToFile(encrypted, len, "encrypted.txt");
                break;

            case 3:
                len = loadEncryptedFromFile(encrypted, "encrypted.txt");
                decryptSignal(encrypted, len, decryptedText);
                printf("Decrypted Message: %s\n", decryptedText);
                saveDecryptedToFile(decryptedText, "decrypted.txt");
                break;

            case 4:
                manualDecryption();
                break;

            case 5:
                printf("🔒 Exiting...\n");
                return;

            default:
                printf("❌ Invalid choice. Try again.\n");
        }
    }
}

int main() {
    initMap();
    menu();
    return 0;
}
