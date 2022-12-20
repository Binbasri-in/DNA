#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Structs
typedef struct _dna // tag name is _dna
{
    char name[20]; // name of the person
    int STR[8]; // STR counts
    unsigned long long int counts; // the combined counts (Try)
    struct _dna *next; // pointer to the next node
} dna; // name of the data structure

// Global variables
char *STRs[8] = {"AGATC","TTTTTTCT","AATG","TCTAG","GATA","TATC","GAAA","TCTG"};
int STRs_number = 8;



// Function prototypes
void load_csv_dna(char *file, dna **data);
int STR_count_file(char STR[], char *file_path );
int STR_count_string(char STR[], char *dna_sequence );
dna* find_match(dna *current_dna, dna test_dna);
void add_dna(dna **data, dna *item);
void free_dna(dna *data);
bool comp_two_str(dna dna1, dna dna2);
void find_match_option(dna **data);
void find_match_name(dna **data);
void add_dna_option(dna **data);
void display_database(dna **data);
void database_menu(dna **data);
void save_database(dna **data, char *filename);
void print_dna(dna *data);



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
        state = 1;
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
            dna *head = NULL; // head of the linked list
            char *filename = "large.csv";
            load_csv_dna(filename, &head);
            database_menu(&head);
            // save and free
            save_database(&head, filename);
            free_dna(head);
            return 0;
        }
    }
}

// database menu
void database_menu(dna **data)
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


void load_csv_dna(char *file, dna **data)
{   
    int row = 0, column = 0, i = 0;
    //open the file
    FILE *fp = fopen(file, "r");
    //check if the file is opened
    if (!fp) {
        // Error in file opening
        printf("Can't open file\n");
        return;
    }
    //set a buffer for reading the file line by line until the end
    char buffer[500];
    // temporary variable for conversions
    char temp[10];

    for (;;) // you can specifie a limit by modifiying the loop
    {
        if (fscanf(fp, "%[^\n]%*c", buffer) == EOF) // read the line 
        {
            // get the account_no
            fclose(fp);
            return;// if the end of file is reached, close and return 1
        }

        // skip the first line
        if (row == 0)
        {
            row++;
            continue;
        }

        //split the line into tokens
        char *token = strtok(buffer, ",");
        column = 0;
        // create a new dna structure
        dna new_dna;
        while (token) // read the tokens column by column
        {
            // get the name
            if (column == 0)
            {
                // copy the name
                strcpy(new_dna.name, token);
                
            }
            // get the STR counts
            else
            {
                // convert the string to int
                int count = atoi(token);
                // add the count to the dna
                new_dna.STR[column - 1] = count;
            }
            // get the next token
            token = strtok(NULL, ",");
            // increment the column
            column++;
        }
        // add the new dna to the database
        add_dna(data, &new_dna);
        print_dna(*data);
        // increment the row
        row++;
    }
    // print row
    printf("row: %d\n", row);
    // close the file
    fclose(fp);
}

int STR_count_file(char STR[], char *file_path )
{
    // open the file in read mode
    FILE *file = fopen(file_path, "r");
    // check if the file is opened successfully
    if (file == NULL)
    {
        printf("Error opening the file\n");
        exit(10);
    }
    // get the length of the STR
    int STR_length = strlen(STR);
    // read the file letter by letter
    int count = 0;
    int max_count = 0;
    char current_letter = fgetc(file);

    while (current_letter != EOF)
    {
        // while the current letter is the same as the first letter of the STR
        while (current_letter == STR[0])
        {
            // check if the next letters are the same as the rest of the STR
            bool is_same = true;
            for (int i = 1; i < STR_length; i++)
            {
                // get the next letter
                current_letter = fgetc(file);
                if ( current_letter != STR[i])
                {
                    is_same = false;
                    break;
                }
            }
            // if the next letters are the same as the rest of the STR
            if (is_same)
            {
                // increase the count
                count++;
                
            }
            // if the next letters are not the same as the rest of the STR
            else
            {
                break;
            }
            // get the next letter
            current_letter = fgetc(file);
            
        }
        // if the count is bigger than the max count
        if (count > max_count)
        {
            // update the max count
            max_count = count;
        }
        // reset the count
        count = 0;
        // get the next letter
        current_letter = fgetc(file);
        
    }
    // close the file
    fclose(file);
    // return the max count
    return max_count;
}

int STR_count_string(char STR[], char *dna_sequence )
{
    // this function counts the number of an STR in a string
    // get the length of the STR
    int STR_length = strlen(STR);
    // read the string letter by letter
    int count = 0;
    int max_count = 0;
    char current_letter = dna_sequence[0];
    int index = 0;
    
    while (current_letter != '\0')
    {
        // while the current letter is the same as the first letter of the STR
        while (current_letter == STR[0])
        {
            // check if the next letters are the same as the rest of the STR
            bool is_same = true;
            for (int i = 1; i < STR_length; i++)
            {
                // get the next letter
                index += 1;
                current_letter = dna_sequence[index];
                if ( current_letter != STR[i])
                {
                    is_same = false;
                    break;
                }
            }
            // if the next letters are the same as the rest of the STR
            if (is_same)
            {
                // increase the count
                count++;
                
            }
            // if the next letters are not the same as the rest of the STR
            else
            {
                break;
            }
            // get the next letter
            index += 1;
            current_letter = dna_sequence[index];
            
        }
        // if the count is bigger than the max count
        if (count > max_count)
        {
            // update the max count
            max_count = count;
        }
        // reset the count
        count = 0;
        // get the next letter
        index += 1;
        current_letter = dna_sequence[index];
        
    }
    // return the max count
    return max_count;
}

void find_match_option(dna **data)
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
    dna *match = find_match(data, test_dna);
    // print the result
    if (match->name != NULL)
    {
        printf("The DNA sequence belongs to %s\n", match->name);
    }
    else
    {
        printf("The DNA sequence doesn't belong to anyone\n");
    }
}

dna* find_match(dna *current_dna, dna test_dna)
{
    // iterate through the linked list
    // for each node compare the STR counts
    while (current_dna != NULL)
    {
        int match = 1;
        for (int i = 0; i < STRs_number; i++)
        {
            if (current_dna->STR[i] != test_dna.STR[i])
            {
                match = 0;
                break;
            }
        }
        // if there was any match return the node where the match happen 
        if (match == 1)
        {
            return current_dna;
        }
        current_dna = current_dna->next;
    }
    // if nothing was found return NULL
    return NULL;
}

void find_match_name(dna **data)
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

void add_dna_option(dna **data)
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
    add_dna(data, &new_dna);
}

void add_dna(dna **data, dna *item)
{   
    // create a new node
    dna *new_dna = malloc(sizeof(dna));
    
    // copy the data
    strcpy(new_dna->name, item->name);
    for (int i = 0; i < STRs_number; i++)
    {
        new_dna->STR[i] = item->STR[i];
    }
    // add it to the beginning of the linked list
    // add it to the structure
    new_dna->next = *data;
    *data = new_dna;
    print_dna(*data);

}
    

void free_dna(dna **data)
{
    // free the allocated memory used for the linked list
    while (data != NULL)
    {
        dna *temp = data;
        data = data->next;
        free(temp);
    }
}

bool comp_two_str(dna dna1, dna dna2)
{
    // simple comparasion between the STR counts in each dna and returns false if there was any difference
    for (int i = 0; i < STRs_number; i++)
    {
        if (dna1.STR[i] != dna2.STR[i])
        {
            return false;
        }
    }
    return true;
}

void display_database(dna **data)
{
    int count = 0;
    // iterate through the linked list and print the info of each node
    while (data != NULL)
    {
        printf("Name: %s\n", data->name);
        printf("STR counts: ");
        for (int i = 0; i < STRs_number; i++)
        {
            printf("%d ", data->STR[i]);
        }
        printf("\n");
        data = data->next;
        count++;
    }
    // print the number of nodes in the database
    printf("There are %d people in the database\n", count);
}

void save_database(dna **data, char *filename)
{
    // save the current structure into a csv file with the same name of the given file if any
    // open the file
    FILE *file = fopen(filename, "w");
    // iterate through the linked list and print the info of each node
    while (data != NULL)
    {
        fprintf(file, "%s,", data->name);
        for (int i = 0; i < STRs_number; i++)
        {
            fprintf(file, "%d,", data->STR[i]);
        }
        fprintf(file, "\n");
        data = data->next;
    }
    // close the file
    fclose(file);

}

void print_dna(dna *data)
{
        // print the content of data
    printf("Name: %s\n", data->name);
    printf("STR counts: ");
    for (int i = 0; i < STRs_number; i++)
    {
        printf("%d ", data->STR[i]);
    }
    printf("\n");
}