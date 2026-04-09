/* Name: Aryan Patel and Lucas Veenstra
 * ASSIGNMENT 3
 * ECE 3220 Spring 2026
 * 
 * Purpose: Simulate RAID-5 disk storage system
 * 
 * assumptions: Input is entered in the intended way.
 * 
 * bugs: N/A
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void createRaid5 (char *, int, int){
    return;
}

void calculateParity ( char * ){
    char result[17];
    char a[17];
    char b[17];
    char c[17];
    char d[17];
    for (int i = 0; i < 16; i++) {
        result[i] = a[i] ^ b[i] ^ c[i] ^ d[i];
    }
    result[16] = '\0';
    return;
}

void printRaid5Disks(void){
    printf("Creating RAID 5 reliable storage system\n");
    printf("**********************************************************************************************************\n");
    printf("[disk0]            [disk1]            [disk2]            [disk3]            [disk4]\n");
    printf("strip (0, 0)       strip(1, 0)        strip(2, 0)        strip(3, 0)        strip(4, 0)\n");
    printf("----------------------------------------------------------------------------------------------------------\n");
    return;
}

void simulateFailure (int){
    return;
}

void restoreData (void){
    return;
}

int main(int argc, char *argv[]){// need only 3 stripes, so 16 blocks(12 data, 4 parity)
    if (argc != 2) {
        printf("Invalid number of arguments, run ./Raid5 with a disk number (0-4).\n");
        return 1;
    }

    int failed_disk = atoi(argv[1]);

    if (failed_disk < 0 || failed_disk > 4) {
        printf("Invalid disk number.Disk number should be between 0-4.\n");
        return 1;
    }

    char input[17];
    int i = 1;
    

    while (i<=48 && scanf("%16c", input) == 1){
        input[16] = '\0';
        
        printf("%d.[%s]\n", i, input);
        i++;
    }

    printRaid5Disks();

//fail code
    simulateFailure(failed_disk);
    restoreData();
    return 0;
}
