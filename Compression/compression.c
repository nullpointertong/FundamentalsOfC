#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 

#define MAX 1000
#define DATABASE "Database.txt"
#define DATABASETEMP "Database.tmp"

char* upperToLower(char* process);

char * encrypt(char * encryptMessage)
{
void doEncryption()
{
    char* temp=malloc(sizeof(char)*10);
    FILE *fp = fopen(DATABASE, "r");
    char* finished =malloc(sizeof(char)*10);
    FILE *fpWrite = fopen(DATABASETEMP, "w");
    printf("\n");
    if(fp!=NULL)
    {
        while(!feof(fp))
        {
            fscanf(fp," %s ",temp);
				strcpy(finished, upperToLower(temp));
            strcpy(finished, encrypt(finished));
            fprintf(fpWrite, " %s ", finished);

            temp[0] = '\0';
            finished[0] = '\0';            
            
        }
	fclose(fp);
    fclose(fpWrite);

    remove(DATABASE);
    rename(DATABASETEMP, DATABASE);
    }
    else
    {
        printf("Cannot find database, please have a check\n");
    }
}


void doDecryption()
{
    char* temp=malloc(sizeof(char)*10);
    FILE *fp = fopen(DATABASE, "r");
    char* finished =malloc(sizeof(char)*10);
    FILE *fpWrite = fopen(DATABASETEMP, "w");
    printf("\n");
    if(fp!=NULL)
    {
        while(!feof(fp))
        {
            fscanf(fp," %s ",temp);

            strcpy(finished, encrypt(temp));
            fprintf(fpWrite, "%s ", finished);
            temp[0] = '\0';
            finished[0] = '\0';
        }
            fclose(fp);
    			fclose(fpWrite);

    			remove(DATABASE);
    			rename(DATABASETEMP, DATABASE);
    }
    else
    {
        printf("Cannot find database, please have a check\n");
    }
}

void showDatabase()
{
    char* temp=malloc(sizeof(char)*10);
    FILE *fp = fopen (DATABASE, "r");
    if(fp!=NULL)
    {
        while(!feof(fp))
        {
            fscanf(fp, " %s ", temp);
           	printf(" %s ", temp);
           	temp[0]='\0';
        }
    }
    fclose(fp); 
}

int lower(int a) 
{
    if ((a >= 0x41) && (a <= 0x5A))
        a |= 0x20; 
    return a;  
}

char* upperToLower(char* process)
{
	char* temp=malloc(sizeof(process)+1);
	int i;
	for(i=0; i<strlen(process);i++)
	{
		temp[i] = lower(process[i]);
	}
	temp[strlen(process)+1] = '\0';
	
	return temp;
}

char *encoding(char str[])
{
    int count;
    int strLength = strlen(str);
    char *encodedString = (char *)malloc(sizeof(char)*(strLength*2 + 1)); 
    char finalCount[MAX];
    char *number9 = (char *)malloc(sizeof(char)*(strLength*2 + 1)); 
    char *formatedString = (char *)malloc(sizeof(char)*(strLength*2 + 1)); 
    char *formatedStringRemain =  (char *)malloc(sizeof(char)*(strLength*2 + 1)); 
    int done = 0;
    char* numberRemain = (char *)malloc(sizeof(char)*(strLength*2 + 1));
    int remainInt = 0;

    int i;
    int j=0;
    for(i=0; i<strLength; i++)
    {
        encodedString[j++] = str[i];/* init the first occureences of a char*/
        count =1;/*init the count for each occureence*/

        /*if second char is equal to the previous char*/
        while(str[i] == str[i+1] && i+1<strLength)
        {
            count++;
            i++;
        }

        sprintf(finalCount, "%d", count);

        if(count>9)
        {
            int timeInt = count / 9;

            remainInt = count % 9;
            sprintf(numberRemain, "%d", remainInt);
           
            sprintf(number9, "%d", 9);
            sprintf(formatedString, "%c", str[i]);
            strcat(formatedString, number9);
            printf("\nformatedString is %s\n", formatedString);
             
            int l;
            for(l=0; l<timeInt; l++)
            {
                if (done==0)
                {
                    encodedString[j--] = '\0';
                    strcpy(finalCount, formatedString);
                    done=1;
                                printf("done0 finalCount is %s\n", finalCount);
                }
                else
                    strcat(finalCount, formatedString);
                    printf("done1 finalCount is %s", finalCount);
            }
            
            if(remainInt != 0 )
            {
                sprintf(formatedStringRemain, "%c", str[i]);
                sprintf(numberRemain, "%d", remainInt);
                strcat(formatedStringRemain, numberRemain);
                strcat(finalCount,formatedStringRemain);
            }

        }

        int k;
        for(k=0;*(finalCount+k); k++, j++)
        {
            encodedString[j] = finalCount[k]; /*coping each encoded char to new string */
        }
    }
    return encodedString;
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
    }

    final[strlen(final)+1] = '\0';
   
    
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

void init()
{
	doDecompress();
   doDecryption();
}

void terminate()
{
	doEncryption();
	doCompress();
}

int main()
{
    printf("Database before do encryption and compression\n");
    showDatabase();
    

  	terminate();
    printf("\nDatabase after do encryption and compression\n");
    showDatabase();

	

	init();
    printf("\nDatabase after do decryption and decompression\n");
    showDatabase();
     
     printf("\n");

    return 0;

}
