#include<stdio.h>
#include<stdbool.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define MAX_NUM_OF_WORDS 100

struct player {
    int id;
    char name[20];
    int score;
    int rank;
};

int spell_checker(char* guess,char** wordlist,int wordcount);

bool processGuess(char* answer,char* guess,int n,int *flag)
{
    int i,j;
    char clue[n+1],virtualClue [n+1];;
    bool answerFlags[n]; 

    for(i=0;i<n;i++)
    {
        clue[i]='-';
    }
    clue[i]='\0';
    for(i=0;i<n;i++)
    {
        answerFlags[i]=false;
    }

    for(i=0;i<n;i++)
    {
        if(guess[i]==answer[i])
        {
            clue[i]='G';
        }
    }

    for(i=0;i<n;i++)
    {
        if(clue[i]=='-')
        {
           for(j=0;j<n;j++)
            {
                if(guess[i]==answer[j] && !answerFlags[j])
                {
                    clue[i]='Y';
                    answerFlags[j]= true;
                    break;
                }
            } 
        }
    }
    for(i=0;i<n;i++)
    {
        virtualClue[i]='G';
    }
    virtualClue[i]='\0';
    printf("%s\n",clue);
    *flag=1;
    return strcmp(clue,virtualClue)==0;
}

void main()
{
    int n,i,flag=1;
    printf("Enter the word length of the word which you want to guess\n");
    scanf("%d",&n);
    char** wordlist;
    char* word;
    FILE* fp;
    int wordcount=0;
    wordlist=(char**)calloc(MAX_NUM_OF_WORDS,sizeof(char*));
    word=(char*)malloc((n+1)*sizeof(char));
    switch(n)
    {
        case 5: fp=fopen("5_letter_word.txt","r");
                while(fscanf(fp,"%s",word)!=EOF && wordcount<MAX_NUM_OF_WORDS)
                {
                    wordlist[wordcount]=word;
                    wordcount++;
                    word=(char*)malloc((n+1)*sizeof(char));
                }
                fclose(fp);
                break;

        case 6: fp=fopen("6_letter_word.txt","r");
                while(fscanf(fp,"%s",word)!=EOF && wordcount<MAX_NUM_OF_WORDS)
                {
                    wordlist[wordcount]=word;
                    wordcount++;
                    word=(char*)malloc((n+1)*sizeof(char));
                }
                fclose(fp);
                break;

        case 7: fp=fopen("7_letter_word.txt","r");
                while(fscanf(fp,"%s",word)!=EOF && wordcount<MAX_NUM_OF_WORDS)
                {
                    wordlist[wordcount]=word;
                    wordcount++;
                    word=(char*)malloc((n+1)*sizeof(char));
                }
                fclose(fp);
                break;
    }

srand(time(NULL));
char* answer=wordlist[rand()%wordcount];

int num_of_guesses=0;
bool guessed_correctly=false;
char* guess=malloc((n+1)*sizeof(char));
while(num_of_guesses<n && !guessed_correctly)
{
    printf("input a %d letter word and press enter:",n);
    while(flag==1)
    {
        scanf("%s",guess);
        flag=spell_checker(guess,wordlist,wordcount);
    }
    printf("you have guessed %s\n",guess);
    num_of_guesses += 1;

    guessed_correctly=processGuess(answer,guess,n,&flag);

} 

if(guessed_correctly)
{
    printf("congratulations!!! You guessed the word in %d attempt\n",num_of_guesses);
}
else
    printf("Sorry....You have used your guesses...\nThe correct word is %s\n",answer);

free(answer);
free(wordlist);
free(word);
free(guess);
}

int spell_checker(char* guess,char** wordlist,int wordcount)
{
    int i;
    //tolower(guess)
    for(i=0;i<wordcount;i++)
    {
        //tolower(wordlist[i]);
        if(!strcmp(guess,wordlist[i]))
        {
            return 0;
        }
    }
    printf("Word not found in the dictionary\n");
    printf("Please re-enter!!!\n");
    return 1;
}