#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

void encipher(char message[], char key[]);

void decipher(char encrypted[], char key[]);

void lower(char str[]);

int checkString(char str[]);

int main() {
    //used to take the return from the checkString function
    int checked = 0;
    //used to count how many failed entries the user has
    int fail = 0;
    //character array to store the message
    char message[100];
    //character array to store the key
    char key[100];
    //loop to check and ask user for message entries
    do {
        //prompts user for the message
        printf("Enter your message:\n");
        //takes the message as input
        scanf("%s", message);
        //calls the checked function to determine if the character array is all letters
        checked = checkString(message);
        //if the check returns 0 it will prompt the user their entry was incorrect
        if (checked == 0) {
            printf("Invalid entry. No numbers or special characters.\n");
            //increments the fail counter
            fail++;
            //if the user has failed more than once the program will terminate
            if (fail == 2) {
                printf("Exiting program.\n");
                exit(0);
            }
        } else
            //if all goes correct it will break the loop and move on
            break;
    } while (1);
    //reset fail counter to 0 for the key entry
    fail = 0;
    //loop to check and ask user for the key entries
    do {
        //prompts user for the key
        printf("Enter your key:\n");
        //takes the key as input
        scanf("%s", key);
        //calls the checked function to determine if the character array is all letters
        checked = checkString(key);
        //if the check returns 0 it will prompt the user their entry was incorrect
        if (checked == 0) {
            printf("Invalid entry. No numbers or special characters\n");
            //increments the fail counter
            fail++;
            //if the user has failed more than once the program will terminate
            if (fail == 2) {
                printf("Exiting program.\n");
                exit(0);
            }
        } else
            //will break from the loop if all entries are correct
            break;
    } while (1);
    //finally calls the encipher method to display the output
    encipher(message, key);
    return 0;
}


/*
 * This function is used to encipher the message.
 * It takes two character arrays: one being the message to encipher and the other is the key.
 * This function will first check the length of the key. If the key is shorter than the
 * message, the function will add characters from the start of the key to the end.
 * After ensuring the key is the right length the program will iterate through the arrays.
 * It will add the newly enciphered letters to the newly created enciphered Message.
 * If the letters go beyond the lowercase alphabet the program will check and ensure the characters are correct.
 * Finally it will print out the message, key, enciphered message and then use the decipher function.
 */
void encipher(char message[], char key[]) {
    //integer to get the length of the message
    int messageLength = strlen(message);
    //integer to get the length of the key
    int keyLength = strlen(key);
    //creates a new character array to store the encrypted message
    unsigned char encryptedMessage[messageLength];
    //creates a new character array to store the adjusted key
    unsigned char encryptionKey[messageLength];

    //checks the length of the key to the length of the message
    if (keyLength < messageLength) {
        //if the key is shorter it will iterate through the message length and add the newly needed characters
        int difference = messageLength - keyLength;
        for (int i = 0; i < keyLength; i++) {
            encryptionKey[i] = key[i];
        }
        //adds the new characters
        for (int j = 0; j < difference; j++) {
            encryptionKey[keyLength] = encryptionKey[j];
            keyLength++;
        }
    } else {
        //if the key is shorter it will just populate the new array
        for (int m = 0; m < messageLength; m++) {
            for (int i = 0; i < keyLength; i++) {
                encryptionKey[i] = key[i];
            }
        }
    }
    //adds the null terminator to the key
    encryptionKey[messageLength] = '\0';

    //this is the formula to encrypt the message
    for (int k = 0; k < messageLength; k++) {
        //it will take each letter from the message and add the shift from the encryption key
        encryptedMessage[k] = (message[k] + ((encryptionKey[k]) - 97));
        //if the letter goes beyond the scope of letters it will subtract to the correct letter
        if (encryptedMessage[k] > 122) {
            encryptedMessage[k] -= 26;
        }
    }
    //adds the null terminator to the newly encrypted message
    encryptedMessage[messageLength] = '\0';
    //prints the encipher
    printf("-----Encipher-----\nMessage: %s\nKey:     %s\nEnc:     %s\n", message, key, encryptedMessage);
    //calls decipher function
    decipher((char *) encryptedMessage, key);
}

/*
 * This function is used to decipher the message.
 * It takes two character arrays: one being the message to decipher and the other is the key.
 * This function will first check the length of the key. If the key is shorter than the
 * message, the function will add characters from the start of the key to the end.
 * After ensuring the key is the right length the program will iterate through the arrays.
 * It will add the newly encrypted letters to the newly created message.
 * If the letters go beyond the lowercase alphabet the program will check and ensure the characters are correct.
 * Finally it will print out the encipher, message and the key.
 */
void decipher(char encrypted[], char key[]) {
    //integer to get the length of the message
    int encryptedLength = strlen(encrypted);
    //integer to get the length of the key
    int keyLength = strlen(key);
    //character array to store the deciphered message
    unsigned char message[encryptedLength];
    //character array to store the adjusted key
    unsigned char encryptionKey[encryptedLength];

    //checks the length of the key to the length of the message
    if (keyLength < encryptedLength) {
        //if the key is shorter than the message it will iterate through and append the letters to the end of the key
        int difference = encryptedLength - keyLength;
        //adds original characters to new character array
        for (int i = 0; i < keyLength; i++) {
            encryptionKey[i] = key[i];
        }
        //adds new characters to the new character array
        for (int j = 0; j < difference; j++) {
            encryptionKey[keyLength] = encryptionKey[j];
            keyLength++;
        }
    } else {
        //if the key is shorter or same length it will just fill the new array
        for (int m = 0; m < keyLength; m++) {
            for (int i = 0; i < keyLength; i++) {
                encryptionKey[i] = key[i];
            }
        }
    }
    //adds null terminator to new key
    encryptionKey[encryptedLength] = '\0';
    //deciphers the method by subtracting the shift from the enciphered message
    for (int k = 0; k < encryptedLength; k++) {
        message[k] = (encrypted[k] - ((encryptionKey[k] - 97)));
        //if the shift falls out of the range it will add in order to get the correct character
        if (message[k] < 97) {
            message[k] += 26;
        }
    }
    //adds null terminator to the message
    message[encryptedLength] = '\0';
    //prints the decipher
    printf("-----Decipher-----\nEnc:     %s\nKey:     %s\nMessage: %s\n", encrypted, key, message);
}

/*
 *This function is used to make the character arrays all lower case.
 * It will iterate through the character array and change each character using the toLower function
 */
void lower(char *str) {
    for (int i = 0; i < strlen(str); i++) {
        str[i] = tolower(str[i]);
    }
}

/*
 * This function is used to check the character array for characters that lie outside of the range of useable characters.
 * It will call the lower function to make it all lowercase, then it will iterate through the array and check if
 * each characters ascii is in between 'a' and 'z'.
 * If the character lies outside the range it will return 0.
 * If the character array is all letters it will return 1.
 */
int checkString(char str[]) {
    int result = 1;
    int length = strlen(str);
    lower(str);
    for (int i = 0; i < length; i++) {
        if (str[i] > 96 && str[i] < 123) {
            continue;
        } else
            return 0;
    }
    return result;
}

