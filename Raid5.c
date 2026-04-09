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



// could hardcode [0,0],[1,1],[2,2]


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void createRaid5 (char *data, int num_stripes, int disk_num){
    char diskarray[disk_num][num_stripes][4][17];   
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


    // for (int j = 0; j < 3; j++) {        
    //     for (int i = 0; i < 5; i++) {   
    //         for (int k = 0; k < 4; k++) { 
    //             printf("disk %d, strip %d, block %d: %s\n", i, j, k, diskarray[i][j][k]);
    //         }
    //     }
    // }
    return;
}

void calculateParity ( char * ){
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
    char *data = malloc(769 * sizeof(char));
    scanf("%768c", data);
    createRaid5(data, 3, 5);
    int stripe_count = 0;
    int strip_count = 0;
    int block_count = 0;
    int ii = 0;
    
    printf("Creating RAID 5 reliable storage system\n");
    printf("**********************************************************************************************************\n");
    printf("[disk0]            [disk1]            [disk2]            [disk3]            [disk4]\n");
    
    for (block_count; block_count < 3; block_count++)
    {
        for (stripe_count; stripe_count < 4; stripe_count++)
        {
            if (stripe_count == 0)
            {
                printf("strip (0, %d)       strip(1, %d)        strip(2, %d)        strip(3, %d)        strip(4, %d)\n", block_count, block_count, block_count, block_count, block_count);
                printf("----------------------------------------------------------------------------------------------------------\n");
            }
            int strips = 0;
            for (strip_count; strip_count < 5; strip_count++)
            {
                if (strip_count == block_count)
                {
                    printf("parity(%d,%d,%d)      ", stripe_count, strip_count, block_count);
                    strips--;
                }
                else 
                {                    
                    for (int i = 0; i < 16; i++)
                    {
                        if (data[ii] == 10) data[ii] = 32;
                        printf("%c", data[ii+(strips*48)]);
                        ii++;
                    }
                    printf("      ");
                }
                strips++;
            }
            printf("\n");
            strip_count = 0;
        }
        strip_count = 0;
        stripe_count = 0;
        if (block_count != 2) printf("----------------------------------------------------------------------------------------------------------\n");
        else printf("**********************************************************************************************************\n");
    }

    
    return;
}

void simulateFailure (int){
    return;
}

void restoreData (void){
    return;
}

int main(int argc, char *argv[]){// need only 3 stripes, so 16 blocks(12 data, 4 parity)
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
    printRaid5Disks();

//fail code
    simulateFailure(failed_disk);
    restoreData();
    return 0;
}
