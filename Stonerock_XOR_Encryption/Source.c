#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_KEY_LENGTH 100

void clear_buffer();

int is_only_whitespace(const char* str);

void xorEncryptDecrypt(char* data, const char* key) {
    int keyLen = strlen(key);

    for (int i = 0; data[i] != '\0'; i++) {
        data[i] ^= key[i % keyLen];
    }
}

int main() {
    char mode[10];

    printf("Enter 'encrypt' or 'decrypt': ");
    fgets(mode, sizeof(mode), stdin);
    mode[strcspn(mode, "\n")] = '\0';

    if (strcmp(mode, "encrypt") == 0) {
        char message[MAX_KEY_LENGTH];

        // Keep asking until a non-whitespace message is entered
        do {
            printf("Enter the message to encrypt: ");
            fgets(message, sizeof(message), stdin);
            message[strcspn(message, "\n")] = '\0';

            if (is_only_whitespace(message)) {
                printf("Message cannot be empty or contain only whitespace. Please try again.\n");
            }

        } while (is_only_whitespace(message));

        char key[MAX_KEY_LENGTH];

        printf("Enter the encryption key: ");
        scanf("%99s", key);
        clear_buffer();

        xorEncryptDecrypt(message, key);

        char filename[100];

        printf("Enter the output filename: ");
        scanf("%99s", filename);
        clear_buffer();

        FILE* file = fopen(filename, "w");

        if (file == NULL) {
            perror("Error opening file for writing");
            return 1;
        }

        fwrite(message, sizeof(char), strlen(message), file);
        fclose(file);

        printf("Message encrypted successfully.\n");

    }
    else if (strcmp(mode, "decrypt") == 0) {
        char filename[100];

        printf("Enter the input filename: ");
        scanf("%99s", filename);
        clear_buffer();

        FILE* file = fopen(filename, "r");

        if (file == NULL) {
            perror("Error opening file for reading");
            return 1;
        }

        fseek(file, 0, SEEK_END);
        long fileSize = ftell(file);
        fseek(file, 0, SEEK_SET);

        char* encryptedData = (char*)malloc(fileSize + 1);

        if (encryptedData == NULL) {
            perror("Error allocating memory");
            fclose(file);
            return 1;
        }

        fread(encryptedData, sizeof(char), fileSize, file);
        encryptedData[fileSize] = '\0';
        fclose(file);

        char key[MAX_KEY_LENGTH];

        printf("Enter the decryption key: ");
        scanf("%99s", key);
        clear_buffer();

        xorEncryptDecrypt(encryptedData, key);

        printf("Decrypted message: %s\n", encryptedData);

        free(encryptedData);

    }
    else {
        printf("Invalid mode. Please enter 'encrypt' or 'decrypt'.\n");
        return 1;
    }

    return 0;
}

void clear_buffer() {
    int character;

    while ((character = getchar()) != '\n' && character != EOF) {
        // Clear remaining characters from the input buffer
    }
}

int is_only_whitespace(const char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isspace((unsigned char)str[i])) {
            return 0;
        }
    }
    return 1;
}
