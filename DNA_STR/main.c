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
void load_csv_dna(char *file, dna *data);
int STR_count_file(char STR[], char *file_path );
int STR_count_string(char STR[], char *dna_sequence );
dna find_match(dna *data, dna test_dna);
void add_dna(dna *data, dna item);
void free_dna(dna *data);
bool comp_two_str(dna dna1, dna dna2);
void find_match_option(dna *data);
void find_match_name(dna *data);
void add_dna_option(dna *data);
void display_database(dna *data);
void database_menu(dna *data);
void save_database(dna *data, char *file);



// The main function
int main(int argc, char *argv[])
{
    int state = 0; // 0 for no database, 1 for database
    // check the command line inputs for any database
    if (argc == 2)
    {
        // choose the state of the program
        state = 1;
    }
    else
    {
        // choose the state of the program
        state = 0;
    }

    // switch between the states
    switch(state)
    {
        // case 0: no database
        case 0:
        // case 1: database
        case 1: 
        {
            // create a new dna structure
            dna *data = NULL;
            load_csv_dna(argv[1], data);
            database_menu(data);
            // save and free
            save_database(data, argv[1]);
            free_dna(data);
            return 0;
        }
    }
}

// database menu
void database_menu(dna *data)
{
    for(;;)
    {
        // print the menu
        printf("1. Add a new DNA sequence to the database\n");
        printf("2. Search for a DNA sequence in the database from a DNA\n");
        printf("3. Display the info of a given name\n");
        printf("4. Display the database\n");
        printf("5. Save and Exit\n");
        printf("Enter your choice: ");
        // get the choice
        int choice;
        scanf("%d", &choice);
        // switch between the choices
        switch(choice)
        {
            case 1: // add new sequence
            {
                add_dna_option(data);
                break;
            }
            case 2: // search for a sequence
            {
                find_match_option(data);
                break;
            }
            case 3: // display the info of a given name
            {
                find_match_name(data);
                break;
            }
            case 4: // display the database
            {
                display_database(data);
                break;
            }
            case 5: // save and exit
            {
                return;
            }
        }
    }

}


void load_csv_dna(char *file, dna *data)
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

void find_match_option(dna *data)
{
    // get the DNA sequence
    printf("Enter the DNA sequence if it's small or filename: ");
    char sequence[500];
    scanf("%s", sequence);
    // create a new dna structure
    dna test_dna;
    // get the STR counts
    // if the sequence is a file
    if (strstr(sequence, ".txt") != NULL)
    {
        for (int i = 0; i < STRs_number; i++)
        {
            test_dna.STR[i] = STR_count_file(STRs[i], sequence);
        }
    }
    // if the sequence is a string
    else
    {
        for (int i = 0; i < STRs_number; i++)
        {
            test_dna.STR[i] = STR_count_string(STRs[i], sequence);
        }
    }
    // find the match
    dna match = find_match(data, test_dna);
    // print the result
    if (match.name != NULL)
    {
        printf("The DNA sequence belongs to %s\n", match.name);
    }
    else
    {
        printf("The DNA sequence doesn't belong to anyone\n");
    }
}

dna find_match(dna *data, dna test_dna)
{
    // iterate through the linked list
    // compare the STR counnts in for each node
    // if there was any match return the node where the match happen 
    //(can be reduced to return the name only since the dna data is already given)
    // if nothing was found return NULL




}

void find_match_name(dna *data)
{
    // get the name of the person
    printf("Enter the name of the person: ");
    char name[20];
    scanf("%s", name);
    // search for the name
    dna *current = data;
    while (current != NULL)
    {
        if (strcmp(current->name, name) == 0)
        {
            // print the info
            printf("Name: %s\n", current->name);
            printf("STR counts: ");
            for (int i = 0; i < STRs_number; i++)
            {
                printf("%d ", current->STR[i]);
            }
            printf("\n");
            break;
        }
        current = current->next;
    }
    
}

void add_dna_option(dna *data)
{
    // get the name of the person
    printf("Enter the name of the person: ");
    char name[20];
    scanf("%s", name);
    // get the DNA sequence
    printf("Enter the DNA sequence if it's small or filename: ");
    char sequence[500];
    scanf("%s", sequence);
    // create a new dna structure
    dna new_dna;
    // copy the name
    strcpy(new_dna.name, name);
    // get the STR counts
    // if the sequence is a file
    if (strstr(sequence, ".txt") != NULL)
    {
        for (int i = 0; i < STRs_number; i++)
        {
            new_dna.STR[i] = STR_count_file(STRs[i], sequence);
        }
    }
    // if the sequence is a string
    else
    {
        for (int i = 0; i < STRs_number; i++)
        {
            new_dna.STR[i] = STR_count_string(STRs[i], sequence);
        }
    }
    // add the new dna to the database
    add_dna(data, new_dna);
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

void display_database(dna *data)
{
    // iterate through the linked list and print the info of each node
    // print the number of nodes in the database

}

void save_database(dna *data)
{
    // save the current structure into a csv file with the same name of the given file if any
    // free the allocated memory used for the linked list

}