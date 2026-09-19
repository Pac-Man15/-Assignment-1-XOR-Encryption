#include <stdio.h>
#include <string.h>

#define MAX_KEY_LENGTH 100

void xorEncryptDecrypt(char *data, const char *key) {
    int keyLen = strlen(key);
    for (int i = 0; data[i] != '\0'; i++) {
        data[i] ^= key[i % keyLen];
    }
}

int main() {
    char mode[10];
    printf("Enter 'encrypt' or 'decrypt': ");
    fgets(mode, 10, stdin);
    mode[strcspn(mode, "\n")] = '\0'; // Remove newline

    if (strcmp(mode, "encrypt") == 0) {
        char message[MAX_KEY_LENGTH];
        printf("Enter the message to encrypt: ");
        fgets(message, sizeof(message), stdin);
        message[strcspn(message, "\n")] = '\0'; // Remove newline

        char key[MAX_KEY_LENGTH];
        printf("Enter the encryption key: ");
        scanf("%s", key);

        xorEncryptDecrypt(message, key);

        char filename[100];
        printf("Enter the output filename: ");
        scanf("%s", filename);

        FILE *file = fopen(filename, "w");
        if (file == NULL) {
            perror("Error opening file for writing");
            return 1;
        }

        fwrite(message, sizeof(char), strlen(message), file);
        fclose(file);
    } else if (strcmp(mode, "decrypt") == 0) {
        char filename[100];
        printf("Enter the input filename: ");
        scanf("%s", filename);

        FILE *file = fopen(filename, "r");
        if (file == NULL) {
            perror("Error opening file for reading");
            return 1;
        }

        fseek(file, 0, SEEK_END);
        long fileSize = ftell(file);
        fseek(file, 0, SEEK_SET);

        char *encryptedData = (char *)malloc(fileSize + 1);
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
        scanf("%s", key);

        xorEncryptDecrypt(encryptedData, key);

        printf("Decrypted message: %s\n", encryptedData);

        free(encryptedData);
    } else {
        printf("Invalid mode. Please enter 'encrypt' or 'decrypt'.\n");
        return 1;
    }

    return 0;
}

