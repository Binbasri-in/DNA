#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Global variables
char *STRs[8] = {"AGATC","TTTTTTCT","AATG","TCTAG","GATA","TATC","GAAA","TCTG"};
int STRs_number = 8;

// Structs
typedef struct _dna // tag name is _dna
{
    char name[20]; // name of the person
    int STR[8]; // STR counts
    unsigned long long int counts; // the combined counts (Try)
    struct _dna *next; // pointer to the next node
} dna; // name of the data structure

// Function prototypes
void load_csv_dna(FILE * file, dna *data);
int STR_count_file(char STR[], char *file_path );
int STR_count_string(char STR[], char *dna_sequence );
dna find_match(dna *data, dna test_dna);
void add_dna(dna *data, dna item);
void free_dna(dna *data);
bool comp_two_str(dna dna1, dna dna2);



// The main function
int main(int argc, char *argv[])
{
    // check the command line inputs for any database
    // 
}

void load_csv_dna(FILE * file, dna *data)
{
    // read the csv row by row or line by line
    // for each column in the row not including the header
    // create new dna node to store the data in it
    // add the new node to the linked list
    // print the number of rows and show successful load
    



}

int STR_count_file(char STR[], char *file_path )
{
    // open the file in read mode
    // start parsing the file till you find the first letter
    // if first was found check the other letters following it
    // if one was a match start counting
    // check the next substring if it has the same str and continue counting till there is no match
    // compare the current count with the previous one and keep the maximum only
    // repeate the process till you reach theend of file
    // return the maximum count that was found in the file




}

int STR_count_string(char STR[], char *dna_sequence )
{
    // here we could use sscanf()
    // start parsing the string till you find the first letter
    // if first was found check the other letters following it
    // if one was a match start counting
    // check the next substring if it has the same str and continue counting till there is no match
    // compare the current count with the previous one and keep the maximum only
    // repeate the process till you reach theend of string
    // return the maximum count that was found in the file




}

dna find_match(dna *data, dna test_dna)
{
    // iterate through the linked list
    // compare the STR counnts in for each node
    // if there was any match return the node where the match happen 
    //(can be reduced to return the name only since the dna data is already given)
    // if nothing was found return NULL




}

void add_dna(dna *data, dna item)
{
    // check if the given dna is already in the database
    // allocate memory to for the new item
    // add it to the structure




}

void free_dna(dna *data)
{
    // save the current structure into a csv file with the same name of the given file if any
    // free the allocated memory used for the linked list



}

bool comp_two_str(dna dna1, dna dna2)
{
    // simple comparasion between the STR counts in each dna and returns false if there was any difference



}