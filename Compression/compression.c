#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 

#define MAX 256
#define DATABASE "Database.txt"
#define DATABASETEMP "Database.tmp"

char *encoding(char str[])
{
    int count;
    int strLength = strlen(str);
    char *new = (char *)malloc(sizeof(char)*(strLength*2 + 1)); 
    char finalCount[MAX];

    int i;
    int j=0;
    for(i=0; i<strLength; i++)
    {
        new[j++] = str[i];/* init the first occureences of a char*/
        count =1;

        while(str[i] == str[i+1] && i+1<strLength)
        {
            count++;
            i++;
        }

        sprintf(finalCount, "%d", count);

       
        int k;
        for(k=0;*(finalCount+k); k++, j++)
        {
            new[j] = finalCount[k];
        }

    }

    return new;
}
char *decoding(char str[])
{
   char temp[MAX];
   char* final = malloc(MAX);
   char* tempCurrentChar =malloc(sizeof(char)*1);
   int initdone = 0;
   
   int i;
   for(i=0; i<strlen(str); i=i+2)
   {
        int time = str[i+1] - '0';
        
        sprintf(tempCurrentChar, "%c", str[i]);
        strcpy(temp, tempCurrentChar);

        int j; 
        for(j = 1; j < time; j++)
        {
            char tempChar[2];
            tempChar[0] = str[i];
            tempChar[1] = '\0';
            strcat(temp, tempChar);
        }
        
        if(initdone == 1)
        {
         strcat(final, temp);
        }
        else
        {
         strcpy(final, temp);
         initdone =1;
        }
        
        printf("\nfinal keep tracking: \n%s\n", final);
    }

    final[strlen(final)+1] = '\0';
    
    printf("final in final: \n%s\n", final);
    
    return final;
}


void doCompress()
{
    char temp[100];
    FILE *fp = fopen(DATABASE, "r");
    FILE *fpWrite = fopen(DATABASETEMP, "w");
    char *finished= malloc(sizeof(char)*1);
    char space[2];
    space[0] = ' ';
    space[1] = '\0';
    
    if(fp != NULL)
    {
        while(!feof(fp))
        {
            fscanf(fp, "%s ", temp);
               finished   = encoding(temp);
                fputs(finished, fpWrite);
                fputs(space, fpWrite);
            
        }

    fclose(fp);	
    fclose(fpWrite);

    remove(DATABASE);
    rename(DATABASETEMP, DATABASE);

    }
    else
    {
        printf("Cannot find database, please have a check");
    }
}


void doDecompress()
{
    char temp[100];
    FILE *fp = fopen(DATABASE, "r");
    FILE *fpWrite = fopen(DATABASETEMP, "w");
    char *finished=malloc(sizeof(char)*1);
        char space[2];
    space[0] = ' ';
    space[1] = '\0';
    if(fp!=NULL)
    {
        while(!feof(fp))
        {
            fscanf(fp, "%s ", temp);
                 finished = decoding(temp);
                fputs(finished, fpWrite);
                fputs(space, fpWrite);    
        }
    fclose(fp);
    fclose(fpWrite);

    remove(DATABASE);
    rename(DATABASETEMP, DATABASE);
    }
    else
    {
        printf("Cannot find database, please have a check");
    }
}

void showDatabase()
{
    char temp[100];
    FILE *fp = fopen (DATABASE, "r");
    if(fp!=NULL)
    {
        while(!feof(fp))
        {
        fgets(temp, MAX, fp);
            printf("%s", temp);
           
        }
    }
}


int main()
{
    printf("\nDatabase before do compression\n");
    showDatabase();

    doCompress();
    printf("\nDatabase after do compression\n");
    showDatabase();
   

    doDecompress();
    printf("\nDatabase after do decompression\n");
    showDatabase();

    return 0;

}
