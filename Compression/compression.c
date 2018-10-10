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

    new[j-1] = '\0';
    printf("%sThis is in encoding", new);
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

    final[sizeof(final)] = '\0';
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
            if(fgets(temp, sizeof(temp), fp) != NULL && temp[0] != '\0' && temp[0] != '\n')
            {
               
                char *finished  = encoding(temp);
                fputs(finished, fpWrite);
            }
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
            if(fgets(temp, sizeof(temp), fp) != NULL && temp[0] != '\0' && temp[0] != '\n')
            {
               
                char *finished  = decoding(temp);
                fputs(finished, fpWrite);
            }
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
        while(!feof(fp) && fgets(temp, sizeof(temp), fp) != NULL)
        {
            printf("%s", temp);
           
        }
    }
}


int main()
{
    printf("\nDatabase before do compression\n");
    showDatabase();
    printf("\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n");

    doCompress();
    printf("\nDatabase after do compression\n");
    showDatabase();
    printf("\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n");

    doDecompress();
    printf("\nDatabase after do decompression\n");
    showDatabase();
        printf("\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n");

    return 0;

}
