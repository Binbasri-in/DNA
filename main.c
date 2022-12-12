#include <stdio.h>

char *STRs[8] = {"AGATC","TTTTTTCT","AATG","TCTAG","GATA","TATC","GAAA","TCTG"};

typedef struct _dna
{
    char name[20];
    int STR[8];
    struct _dna *next;
} dna;

