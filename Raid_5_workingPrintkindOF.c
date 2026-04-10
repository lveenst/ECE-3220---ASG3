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

char diskarray[5][3][4][17];   

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void createRaid5 (char *data, int num_stripes, int disk_num){
    int total_blocks = 0;
    int disk = 0;
    int stripe = 0;
    int block = 0;
    int count = 0;
    char c;
    int i = 0;
    
    memset(diskarray, 0, sizeof(diskarray)); 
    while (total_blocks < 48) {
        if (disk == stripe){
            block = 0;
            disk++;
        }else {
            while(count < 16){
                c = data[i];
                if (c == 10){
                    c = ' ';
                }
                diskarray[disk][stripe][block][count] = c;
                count++;
                i++;
                
            }
            diskarray[disk][stripe][block][16] = '\0';
            block++;
            if (block == 4){
                block = 0;
                disk++;
            }
            if (disk == disk_num){
                disk = 0;
                stripe++;
            }
            total_blocks++;
            if (count == 16){
                count = 0;
            }
        }
        
    }

    return;
}

void calculateParity (char * ){
    // char result[17];
    // char a[17];
    // char b[17];
    // char c[17];
    // char d[17];
    // for (int i = 0; i < 16; i++) {
    //     result[i] = a[i] ^ b[i] ^ c[i] ^ d[i];
    // }
    // result[16] = '\0';
    // return;
}
    
void printRaid5Disks(void){
    int stripe_count = 0;
    int disk_count = 0;
    int block_count = 0;
    
    printf("Creating RAID 5 reliable storage system\n");
    printf("**********************************************************************************************************\n");
    printf("[disk0]            [disk1]            [disk2]            [disk3]            [disk4]\n");
    
    for (stripe_count = 0; stripe_count < 3; stripe_count++)
    {
        printf("strip (0, %d)       strip(1, %d)        strip(2, %d)        strip(3, %d)        strip(4, %d)\n", stripe_count, stripe_count, stripe_count, stripe_count, stripe_count);
        printf("----------------------------------------------------------------------------------------------------------\n");
        
        for (block_count = 0; block_count < 4; block_count++)
        {
            for (disk_count = 0; disk_count < 5; disk_count++)
            {
                if (disk_count == stripe_count)
                {
                    printf("parity(%d,%d,%d)      ", stripe_count, disk_count, block_count);
                }
                else 
                {                    
                    printf("%s      ", diskarray[disk_count][stripe_count][block_count]);
                }
            }
            printf("\n");
        }

        if (stripe_count != 2) printf("----------------------------------------------------------------------------------------------------------\n");
        else printf("**********************************************************************************************************\n");
    }

    return;
}

void simulateFailure (int failed_disk){
    // bunch of for loops to go though the 3d array and if the disk number = failed disk, replace it with FAILED DISK
    //might want to complete calculateparity funcion first
    return;
}

void restoreData (void){
    //should be similar to calculate paritiy just need to find a way to take in the 4 good disk in
    
    return;
}

int main(int argc, char *argv[]){
    // input validation
    if (argc != 2) {
        printf("Invalid number of arguments, run ./Raid5 with a disk number (0-4).\n");
        return 1;
    }

    int failed_disk = atoi(argv[1]);

    if (failed_disk < 0 || failed_disk > 4) {
        printf("Invalid disk number.Disk number should be between 0-4.\n");
        return 1;
    }
    // start to read input and save to array
    char *data;
    data = malloc(769 * sizeof(char));
    scanf("%768c", data);
    createRaid5(data, 3, 5);
    printRaid5Disks();

//fail code
    simulateFailure(failed_disk);
    restoreData();
    return 0;

    free(data);
}
