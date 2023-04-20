#include <stdio.h>

int main() {
    int n;
    printf("Enter the size of the stuffed data array: ");
    scanf("%d", &n);
    
    int stuffedData[n];
    printf("Enter the stuffed data array (0 or 1 only):\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &stuffedData[i]);
    }
    
    int destuffedData[n]; // array to hold de-stuffed data
    int count = 0; // count of consecutive 1's
    
    // loop through stuffed data and de-stuff bits
    int destuffedIndex = 0; // index for destuffedData array
    for (int i = 0; i < n; i++) {
        destuffedData[destuffedIndex] = stuffedData[i]; // copy original bit to destuffedData
        destuffedIndex++;
        
        if (stuffedData[i] == 1) { // check if bit is 1
            count++; // increment count of consecutive 1's
            if (count == 5) { // if 5 consecutive 1's are found, skip the next bit
                i++; // skip next bit
                count = 0; // reset count of consecutive 1's
            }
        }
        else { // if bit is not 1, reset count of consecutive 1's
            count = 0;
        }
    }
    
    // print stuffed and de-stuffed data
    for (int i = 0; i < destuffedIndex; i++) {
        printf("%d", destuffedData[i]);
    }
    
    return 0;
}
