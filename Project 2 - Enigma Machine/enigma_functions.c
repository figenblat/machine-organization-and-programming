/* name: Noa Figenblat 
 * uw net Id: 908 198 9114
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "enigma.h"

const char *ROTOR_CONSTANTS[] = {
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ", // Identity Rotor (index 0 - and useful for testing):
        "EKMFLGDQVZNTOWYHXUSPAIBRCJ",
        "AJDKSIRUXBLHWTMCQGZNPYFVOE",
        "BDFHJLCPRTXVZNYEIWGAKMUSQO",
        "ESOVPZJAYQUIRHXLNFTGKDCMWB",
        "VZBRGITYUPSDNHLXAWMJQOFECK",
        "JPGVOUMFYQBENHZRDKASXLICTW",
        "NZJHGRCXMYSWBOUFAIVLPEKQDT",
        "FKQHTLXOCBJSPDZRAMEWNIUYGV",
};

// This method reads a character string from the keyboard and 
// stores the string in the parameter msg.
// Keyboard input will be entirely uppercase and spaces followed by 
// the enter key.  
// The string msg should contain only uppercase letters spaces and 
// terminated by the '\0' character
// Do not include the \n entered from the keyboard
void Get_Message(char msg[]){
	// width = 80 --> string can be up to 80 chars long
	// [^\n]--> reads string including spaces until \n char
	// stores the string in msg
	scanf("%80[^\n]s", msg);

   return;
}

// This function reads up to 4 characters from the keyboard
// These characters will be only digits 1 through 8. The user
// will press enter when finished entering the digits.
// The rotor string filled in by the function should only contain 
// the digits terminated by the '\0' character. Do not include
// the \n entered by the user. 
// The function returns the number of active rotors.
int Get_Which_Rotors(char which_rotors[]){
	// int var keeping track of how many active rotors there are
	int activeRotors = 0;

	// scanf of width 4; storing in which_rotors
	scanf("%4s", which_rotors);

	// forloop countng how many active rotors there are
	for(int i = 0; i < 4; i++){
		if(which_rotors[i]=='\0'){
			break;
		}
		else{
			activeRotors++;
		}
	}
	       
   return activeRotors;
} 

// This function reads an integer from the keyboard and returns it 
// This number represents the number of rotations to apply to the 
// encryption rotors.  The input will be between 0 and 25 inclusive
int Get_Rotations(){
	// int var keeping track of the number of rotations
	int numRotations;

	//scanf reading an int
	scanf("%d", &numRotations);

    return numRotations;
}


// This function copies the rotors indicated in the which_rotors string 
// into the encryption_rotors.  For example if which rotors contains the string 
// {'3', '1', '\0'} Then this function copies the third and first rotors into the 
// encryption rotors array in positions 0 and 1.  
// encryptions_rotors[0] = "BDFHJLCPRTXVZNYEIWGAKMUSQO"
// encryptions_rotors[1] = "EKMFLGDQVZNTOWYHXUSPAIBRCJ"
void Set_Up_Rotors(char encryption_rotors[4][27], char which_rotors[5]){

	// forloop going through each index of which_rotors
	for(int i = 0; i < 4; i++){
		// if the index is null (no rotor stored) break the loop
		if (which_rotors[i] == '\0'){
			break;
		}
		// if the index is 1 store ROTOR_CONSTANTS[1] at index
		// i of encryption rotors
		else if(which_rotors[i] == '1'){
			strcpy(encryption_rotors[i], ROTOR_CONSTANTS[1]);
		}
		else if(which_rotors[i] == '2'){
			strcpy(encryption_rotors[i], ROTOR_CONSTANTS[2]);
		}
		else if(which_rotors[i] == '3'){
			strcpy(encryption_rotors[i], ROTOR_CONSTANTS[3]);
		}
		else if(which_rotors[i] == '4'){
			strcpy(encryption_rotors[i], ROTOR_CONSTANTS[4]);
		}
		else if(which_rotors[i] == '5'){
			strcpy(encryption_rotors[i], ROTOR_CONSTANTS[5]);
		}
		else if(which_rotors[i] == '6'){
			strcpy(encryption_rotors[i], ROTOR_CONSTANTS[6]);
		}
		else if(which_rotors[i] == '7'){
			strcpy(encryption_rotors[i], ROTOR_CONSTANTS[7]);
		}
		else if(which_rotors[i] == '8'){
			strcpy(encryption_rotors[i], ROTOR_CONSTANTS[8]);
		}
	}

    return;
}


// This function rotates the characters in each of the active encryption rotors
// to the right by rotations.  For example if rotations is 3 encryption_rotors[0]
// contains "BDFHJLCPRTXVZNYEIWGAKMUSQO" then after rotation this row will contain
// SQOBDFHJLCPRTXVZNYEIWGAKMU.  Apply the same rotation to all for strings in 
// encryption_rotors
void Apply_Rotation(int rotations, char encryption_rotors[4][27]) { 
	
	// temp char var
	char temp;

	// forloop going through each rotor in encryption_rotors
	for(int i = 0; i < 4; i++){
		// if the index is null break the loop
		if(*encryption_rotors[i]=='\0'){
			break;
		}

		// forloop looping for each rotation
		// ie: if rotations = 3 this will loop 3 times
		for(int j = 0; j < rotations; j++){
			// temp equals the last char in the current rotor
			temp = encryption_rotors[i][25];
			// forloop right rotating by one
			for(int k = 26; k > 0; k--){
				encryption_rotors[i][k] = encryption_rotors[i][k-1];
			}
			// the first index is set to the char temp
			encryption_rotors[i][0] = temp;
			// the very last index is set to the null terminator
			encryption_rotors[i][26] = '\0';
		}
	}

    return;
}

// This function takes a string msg and applys the enigma machine to encrypt the message
// The encrypted message is stored in the string encryped_msg 
// Do not change spaces, make sure your encryped_msg is a \0 terminated string
void Encrypt(char encryption_rotors[4][27], int num_active_rotors, char msg[], char encrypted_msg[]){
	// int len holding the length of msg
	int len = strlen(msg);	
	int index = 0;
	int charIndex = 0;
	char temp;

	while(index <= len){
		// char temp is set to the char at msg[index]
		temp = msg[index];

		// if the char is a space, just add it to encrypted_msg
		if(temp == 32){
			encrypted_msg[index] = msg[index];
			index++;
		}
		// if the index and length are equal add a null terminator to 
		// encrypted_msg and break
		else if(index == len){
			encrypted_msg[index] = '\0';
			break;
		}
		else{
			// forloop going through each rotor
			for(int i = 0; i < num_active_rotors; i++){
				// pointer to the char temp in
				// ROTOR_CONSTANTS[0]
				char *ptr = strchr(ROTOR_CONSTANTS[0], temp);
				// charIndex stores the index of the 
				// temp in ROTOR_CONSTANTS
				charIndex = ptr - ROTOR_CONSTANTS[0];
				// temp is set to the char at charIndex in the
				// current rotor
				temp = encryption_rotors[i][charIndex];
			}
			// adding the encrypted char to the encrypted_msg
			encrypted_msg[index] = temp;
			index++;
		}
	}

    return;
}


// This function takes a string msg and applys the enigma machine to decrypt the message
// The encrypted message is stored in the string encryped_msg and the decrypted_message 
// is returned as a call by reference variable
// remember the encryption rotors must be used in the reverse order to decrypt a message
// Do not change spaces, make sure your decrytped_msg is a \0 terminated string
void Decrypt(char encryption_rotors[4][27], int num_active_rotors, char encrypted_msg[], char decrypted_msg[]) {
  
	// int var storing the length of encrypted_msg
	int len = strlen(encrypted_msg);
	char temp;
	int index = 0;
	int charIndex = 0;

	while(index <= len){
		// temp holds the char at encrypted_msg[index]
		temp = encrypted_msg[index];

		// if the char is a space, just add it to decrypted_msg[index]
		if(temp == 32){
			decrypted_msg[index] = encrypted_msg[index];
			index++;
		}
		// if the index and length are equal add the null terminator 
		// to decrypted_msg and break
		else if(index == len){
			decrypted_msg[index] = '\0';
			break;
		}
		else{
			// loop going through active rotors
			// starts from the last rotor 
			// (opposite of encrypt)
			// ie: if encrypt visits rotor 3 and then rotor 1
			// decrypt will visit rotor 1 and then rotor 3
			for(int i = num_active_rotors-1; i >= 0; i--){
				// pointer to temp in the current rotor
				char *ptr = strchr(encryption_rotors[i], temp);
				// charIndex is set to the index of temp
				// in the current rotor
				charIndex = ptr - encryption_rotors[i];

				// temp is then set to the char at charIndex 
				// in the identity rotor
				temp = ROTOR_CONSTANTS[0][charIndex];
			}

			// temp is added to the decrypted_msg
			decrypted_msg[index] = temp;
			index++;
		}
	}
    return;
}


