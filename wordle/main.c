#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<time.h>

#define MAX_NUM_OF_WORDS 100

FILE *datas=NULL;

char** wordlist=NULL;
char* word=NULL;
FILE* fp=NULL;
char* answer=NULL;
char* guess=NULL;

typedef struct {
    char name[50];
    char password[50];
    int score;
}players;

int match_password(char userName[],char userPassword[],players p[],int count)
{
    int i;
    for(i=0;i<count;i++)
    {
        if(!strcmp(userName,p[i].name))
        {
            if(!strcmp(userPassword,p[i].password))
            {
                //clrsrn();
                printf("welcome to the game !!!\n");
                return i;
            }
        }
    }
    return -1;   
}

void load_data(players p[],int *count)
{
    int i=0;
    datas=fopen("data.csv","r");
    if(datas==NULL)
    {
        printf("unable to open file\n");
        exit(0);
    }
    
    
    while( fscanf(datas, "%[^,]%*c%[^,]%*c%d%*c",p[i].name, p[i].password, &p[i].score) !=EOF)
    {
        printf("name: %s ,password: %s score:%d\n",p[i].name,p[i].password,p[i].score);
        i=i+1;
        
    }
    *count=i;
    fclose(datas);
}

void edit_data(players p[],int *count)
{
    int i;
    datas=fopen("data.csv","w");
    if(datas==NULL)
    {
        printf("unable to open file\n");
        exit(0);
    }
    for(i=0;i<*count;i++)
    {
        fprintf(datas,"%s,%s,%d\n",p[i].name,p[i].password,p[i].score);
    }
    fclose(datas);
}

void calculate_score(int num_of_guesses,int n,players p[],int key)
{
    int scores;
    scores=(int)n*50/num_of_guesses;
    p[key].score=p[key].score+scores;
}

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


void wordle_game(int n,players p[],int key)
{
    int wordcount=0,num_of_penalty_try,choice_of_penalty_try;
    int flag=1;
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
    answer=wordlist[rand()%wordcount];

    int num_of_guesses=0;
    bool guessed_correctly=false;
    guess=(char *)malloc((n+1)*sizeof(char));
    while(num_of_guesses<n && !guessed_correctly)
    {
        printf("input a %d letter word and press enter:\n",n);
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
        calculate_score(num_of_guesses,n,p,key);
    }
    else
    {
        printf("Sorry....You have used your guesses...\nThe correct word is %s\n",answer);
        if(p[key].score>=100 && num_of_penalty_try==0)
        {
            num_of_penalty_try++;
            printf("1.Continue the game by losing 50 points\n2.exit\n");
            printf("Enter your choice\n");
            scanf("%s",&choice_of_penalty_try);
            switch(choice_of_penalty_try)
            {
                case 1: p[key].score = p[key].score - 50;
                        printf("input a %d letter word and press enter:\n",n);
                        while(flag==1)
                        {
                            scanf("%s",guess);
                            flag=spell_checker(guess,wordlist,wordcount);
                        }
                        printf("you have guessed %s\n",guess);
                        num_of_guesses += 1;

                        guessed_correctly=processGuess(answer,guess,n,&flag);
                        if(guessed_correctly)
                        {   
                            printf("congratulations!!! You guessed the word in %d attempt\n",num_of_guesses);
                            calculate_score(num_of_guesses,n,p,key);
                        }
                        else
                        {
                            printf("Sorry....You have used your guesses...\nThe correct word is %s\n",answer);
                        }
                        break;
                case 2: break;
            }

        }

    }
    free(answer);
    free(wordlist);
    free(word);
    free(guess);

}
  
void sorting_scores(players p[],int count)
{
    int i,j,tempScore;
    char tempUsername[50],tempPassword[50];
    for(j=1;j<count;j++)
    {
        for(i=0;i<count-j;i++)
        {
            if(p[i].score<=p[i+1].score)
            {
                tempScore=p[i].score;
                p[i].score=p[i+1].score;
                p[i+1].score=tempScore;

                strcpy(tempUsername,p[i].name);
                strcpy(p[i].name,p[i+1].name);
                strcpy(p[i+1].name,tempUsername);

                strcpy(tempPassword,p[i].password);
                strcpy(p[i].password,p[i+1].password);
                strcpy(p[i+1].password,tempPassword);
            }
        }
    }
}

void main()
{
    int choice,i,count,key;
    int n;
    
    char userName[50],userPassword[50];
    //clrscr();
    players p[100];
    for(;;)
   {
    printf("1.Log in\n2.create a new account\n3.exit\n");
    printf("Enter your choice\n");
    scanf("%d",&choice);
    switch (choice)
    {
        case 1: 
                datas=fopen("data.csv","r");
                if(datas=NULL)
                {
                    printf("unable to open file\n");
                    exit(0);
                }
                load_data(p,&count);
                printf("%d\n",count);
                printf("Enter your name\n");
                scanf("%s",userName);
                printf("Enter your password\n");
                scanf("%s",userPassword);
                key=match_password(userName,userPassword,p,count);
                if(key==-1)
                {
                    printf("Incorrect password or username\n");
                    return;
                }
                //clrsrn();
                printf("Welcome to the game!!!!\n");
                printf("Enter the word length of the word which you want to guess\n");
                scanf("%d",&n);
                wordle_game(n,p,key);

                //score board
                sorting_scores(p,count);
                //clrsrn();
                printf("SCORE BOARD\n");
                for(i=0;i<count;i++)
                {
                    printf("%s\t%d\n",p[i].name,p[i].score);

                }


                break;
    
        case 2: load_data(p,&count);
                printf("Enter your name\n");
                scanf("%s",p[count].name);
                printf("create a new password\n");
                scanf("%s",p[count].password);
                p[count].score=0;                
                count++;
                edit_data(p,&count);
                
                

                break;

        case 3: exit(0);

    }
   }
}