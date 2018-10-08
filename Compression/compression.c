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

    new[j] = '\0';
    return new;
}

char *decoding(char str[])
{
   char temp[MAX];
   char* final = malloc(MAX);
   char* tempCurrentChar =malloc(sizeof(char)*1);
   
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
        strcat(final, temp);
    }

    return final;
}


void doCompress()
{
    char temp[100];
    FILE *fp = fopen(DATABASE, "r");
    FILE *fpWrite = fopen(DATABASETEMP, "w");
    if(fp != NULL)
    {
        while(!feof(fp))
        {
            fgets(temp, 100, fp);
            char *finished  = encoding(temp);
            fprintf(fpWrite, "%s\n", finished);
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
    if(fp!=NULL)
    {
        while(!feof(fp))
        {
            fgets(temp, 100, fp);
            char *finished  = decoding(temp);
            fprintf(fpWrite, " %s\n", finished);
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
            fgets(temp, 100, fp);
            printf("%s\n", temp);
        }
    }
}


int main()
{
    printf("\nDatabase before do compression\n");
    showDatabase();
    printf("\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\");

    doCompress();
    printf("\nDatabase after do compression\n");
    showDatabase();
    printf("\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\");

    doDecompress();
    printf("\nDatabase after do decompression\n");
    showDatabase();
        printf("\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\");

    return 0;

}