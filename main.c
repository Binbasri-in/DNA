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




