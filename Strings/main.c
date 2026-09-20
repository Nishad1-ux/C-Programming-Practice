#include <stdio.h>

// Function to reverse the string in-place
void reverseString(char str[]) {
    int length = 0;
    
    // 1. Finding the End: Manual calculation of length
    while (str[length] != '\0') {
        length++;
    }

    // 2. The Two-Pointer Technique (using indexes)
    int start = 0;           
    int end = length - 1;    

    // 3. Variable Swapping inside a loop
    while (start < end) {
        // Temporary variable to hold one letter during the swap
        char temp = str[start];
        
        // Swap the characters
        str[start] = str[end];
        str[end] = temp;

        // Move pointers toward the center
        start++;
        end--;
    }
}

int main() {
    char myString[] = "hello";

    printf("Original: %s\n", myString);

    reverseString(myString);

    printf("Reversed: %s\n", myString);

    return 0;
}