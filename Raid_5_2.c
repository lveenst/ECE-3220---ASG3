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
int failed_flag = 0;
int failed_d;
char diskarray[5][3][4][17]; // contains all the data parsed in stripes, strips, and disks  

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
This function returns void and takes a char array of all the data we read in from the input file,
an integer of the number of stripes, and an integer of the number of disks
The purpose of this function is simply to create/simulate a Raid5 disk storage system and initialize
the global variable diskarray with all the data we read in.
*/
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

/*
This function takes the long  string with our input data and returns void
The purpose of this function is to calculate the parity within the disks so that we can recover data
if one of the disks failed. The parity is simply calculated from XORing each strip in the same stripe together
*/
void calculateParity(char *data)
{
    createRaid5(data, 3, 5);
    for (int stripe = 0; stripe < 3; stripe++)
    {
        for (int block = 0; block < 4; block++)
        {
            for (int k = 0; k < 16; k++)
            {
                char parity = 0;
                for (int disk = 0; disk < 5; disk++)
                {
                    if (disk != stripe)
                    {
                        parity ^= diskarray[disk][stripe][block][k]; // XOR parity within each stripe
                    }
                }
                diskarray[stripe][stripe][block][k] = parity;
            }
            diskarray[stripe][stripe][block][16] = '\0';
        }
    }
}

/*
This function takes an 8 bit unsigned char 'data_block' and prints it's value in binary
*/
void print_bits(unsigned char data_block)
{
    for (int i = 7; i >= 0; i--)
    {
        printf("%d", (data_block >> i) & 1);
    }
}
 
/*
This function has no arguments and no return value, it simply prints the Raid5 disk parsing
in a formatted a readable way. It also prints the parity values that we calculated earlier.
*/
void printRaid5Disks(void){
    int stripe_count = 0;
    int disk_count = 0;
    int block_count = 0;
    
    printf("Creating RAID 5 reliable storage system\n");
    printf("****************************************************************************************************************\n");
    printf("[disk0]                 [disk1]                [disk2]                [disk3]                [disk4]\n");
    
    for (stripe_count = 0; stripe_count < 3; stripe_count++)
    {
        printf("strip (0, %d)            strip(1, %d)            strip(2, %d)            strip(3, %d)            strip(4, %d)\n", stripe_count, stripe_count, stripe_count, stripe_count, stripe_count);
        printf("----------------------------------------------------------------------------------------------------------------\n");
        
        for (block_count = 0; block_count < 4; block_count++)
        {
            for (disk_count = 0; disk_count < 5; disk_count++)
            {
                if (disk_count == stripe_count)
                {
                    if (failed_flag == 1 && failed_d == disk_count) {
                        printf("-%s-                ", diskarray[disk_count][stripe_count][block_count]);
                    } else {
                        printf("parity(%d,%d,%d)           ", block_count, disk_count, stripe_count);
                    }
                }
                else 
                {   
                    if (failed_flag == 1 && failed_d == disk_count) {
                        printf("-%s-               ", diskarray[disk_count][stripe_count][block_count]);
                    } else {
                        printf("%-23s", diskarray[disk_count][stripe_count][block_count]);
                    }                 
                }
            }
            printf("\n");
        }

        if (stripe_count != 2) printf("----------------------------------------------------------------------------------------------------------------\n");
        else printf("****************************************************************************************************************\n");
    }
    for (stripe_count = 0; stripe_count < 3; stripe_count++){
        for (block_count = 0; block_count < 4; block_count++){
            for (disk_count = 0; disk_count < 5; disk_count++){
                if (disk_count == stripe_count){
                    printf("parity(%d, %d, %d): ", block_count, disk_count, stripe_count);
                    if (strcmp(diskarray[disk_count][stripe_count][block_count], "failed") == 0) {
                        printf("%s", diskarray[disk_count][stripe_count][block_count]);
                    } else {
                        // printing each 16 bit chunk one character at time
                        for(int k = 0; k < 16; k++) {
                            print_bits((unsigned char)diskarray[disk_count][stripe_count][block_count][k]);
                        }
                    }
                    printf("\n");

                }
            }
        }
    }

    return;
}

/*
This function takes an integer input 'failed_disk' which was given by the user of the program in the command line
which indicates the disk # that we want to simulate a failure with
The simulation is simply setting a block in the array to be the string 'failed' and then printing the disk that failed.
*/
void simulateFailure (int failed_disk){
    int stripe_count = 0;
    int disk_count = 0;
    int block_count = 0;
    for (stripe_count = 0; stripe_count < 3; stripe_count++) {
        for (disk_count = 0; disk_count < 5; disk_count++) {
            for (block_count = 0; block_count < 4; block_count++) {
                if (disk_count == failed_disk){
                    strcpy(diskarray[disk_count][stripe_count][block_count], "failed");
                }
            }
        }
    }
    printf("\nDisk %d failed.\n", failed_disk);
    return;
}

/*
This function has no return value and no arguments, it's purpose is to recover the failed data by reversing the 
parity by doing the same XOR calculation, with the disks that didn't fail in order to recover the data.
*/
void restoreData(void){
    printf("\n\nRebuilding the data...\n\n\n");
    for (int stripe = 0; stripe < 3; stripe++){
        for (int block = 0; block < 4; block++){
            for (int k = 0; k < 16; k++){
                char recovered = 0;
                for (int disk = 0; disk < 5; disk++){
                    if (disk != failed_d){
                        recovered ^= diskarray[disk][stripe][block][k];
                    }
                }
                diskarray[failed_d][stripe][block][k] = recovered;
            }
            diskarray[failed_d][stripe][block][16] = '\0';
        }
    }
    failed_flag = 0;
    return;
}

/*
Main function, calls all of our helper functions and simulates a Raid5 storage system
*/
int main(void){
    int failed_disk;

    // start to read input and save to array
    char *data;
    data = malloc(769 * sizeof(char));
    scanf("%768c", data); // getting the input file's data for us to store
    calculateParity(data); // finding the parity and simulating the Raid5 system
    printRaid5Disks(); // displaying how it is stored

    FILE *terminal = fopen("/dev/tty", "r"); // openning a terminal file to read from ("r" argument indicates read)
    printf("Enter disk # to simulate failure: "); // printing to the same terminal to ask for user input
    fflush(stdout); // flushing the standard output data stream
    fscanf(terminal, "%d", &failed_disk); // reading user input for which disk they want to simulate failure
    fclose(terminal); // closing terminal file we read from
    if (failed_disk > 4 || failed_disk < 0) // if invalid disk #, error
    {
        printf("ERROR! Enter an integer between 0-4, quitting the program..\n");
        exit(1);
    }

    // simulating the failed disk and restoring its data
    simulateFailure(failed_disk);
    failed_d = failed_disk;
    failed_flag = 1;
    printRaid5Disks();
    restoreData();
    printRaid5Disks();

    free(data); // freeing allocated memory to ensure no leaks

    return 0;

}
