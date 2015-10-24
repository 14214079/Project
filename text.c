#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>
#include<error.h>

#define INITIALSIZE 1000 //initial size of the char array

typedef struct fileinfo
{
	int lineNumber;
	char *lineData;
	struct fileinfo *next;
} ds;

		//Number of lines in a file = N
int N = 0;
ds *head = NULL;
ds *tail = NULL;
void printmenu(){
	printf("q for quiet the editor ");
	printf("a for appending the text to file ");
	printf("w for saving the file");
	printf("r for removing");
}

int main(int argc, char *argv[])
{
    
	printmenu();
	if(argc != 2)
	{
		printf("Error: File name is not specified.\n");
	
		exit(1);
	}

    
	FILE *fp;

	    //Open a file for both reading and writing. The file must exist.
	fp = fopen(argv[argc-1], "r+");
	if(fp == NULL)
	{
    	   //File does not exist, so it will be created for reading and writing.
		fp = fopen(argv[argc-1], "w+");
	}
	else
	{
	     //If file already exists and is not empty, then upload the
   	    //  contents of the file into the data structure.
		int c = 0;
		int i = 0;
		int lineNum = 0;
		char charArray[INITIALSIZE] = {0}; //Initializes the array

        while( (c=getc(fp)) != EOF)
        {
                if(c == '\n')
                {
                	lineNum++;
                	N++;
                	charArray[i] = '\0';
                	i = 0;

                	if(head == NULL)
                	{
                	    	ds *node = malloc(sizeof(ds));
                	    	node->lineNumber = lineNum;
               			node->lineData = malloc(strlen(charArray)+1); 
                        	strcpy(node->lineData, charArray);
                	 	node->next = NULL;
                		head = node;
                	 	tail = node;
                	}
                	else //iterate through the linked-list
                	{
                		ds *curr = head;
                		while(curr->next != NULL)
                		{
                	        	curr = curr->next;
                	    	}
               		  	ds *node = malloc(sizeof(ds));
                		node->lineNumber = lineNum;
                		node->lineData = malloc(strlen(charArray)+1); 
                		strcpy(node->lineData, charArray);
                		node->next = NULL;
                		curr->next = node;
                		tail = node;
                	}

                	memset(charArray, 0, INITIALSIZE);
                	continue;
            	}	
            	charArray[i++] = c;
        }
	}

	char *command = NULL;
	size_t ec_size = 0;
       			 
	printf("TextEditor-%s-$ ", argv[argc-1]);
	while(1)
	{

		getline(&command, &ec_size, stdin);
		int ec_len = strlen(command);
		command[ec_len-1] = '\0';
		if(strcmp(command, "p") == 0)
		{
			//Print the contents of the file
			int n = 1;
			ds *temp = head;
			while(temp != NULL)
			{
				printf("%d", n);
				printf("%s\n", temp->lineData);
				n++;
				temp = temp->next;
			}
        	}
        	else if(command[0] == 'a')
        	{

            		char* dest = malloc(strlen(command)+1);
            		memset(dest, '\0', strlen(command)+1);
           		strcpy(dest, command);
          		const char delim = ' ';
            		char *token;
            		token = strtok(dest, &delim);
            		token = strtok(NULL, &delim);
            			if(token == NULL)
            			{
                			printf("Error: The format to append is: \"a <lineNumber> <textToAppend>\"\n");
                			exit(1);
            			}
            		int lineN = atoi(token);

       				//Now parse the text to be appended
        		char *ret1, *ret2;
       			ret1 = strchr(command, delim);
            		ret2 = strchr(ret1+1, delim);
            		if(ret2 == NULL)
            		{
                		printf("Error: The format to append is: \"a <lineNumber> <textToAppend>\"\n");
                		exit(1);
            		}
            		char *text = ret2 + 1;

            			//Now update the datastore (ds) with the new append data
           		ds *temp = head;
   		        if(lineN > N) //text to be appended at last line
        		{
        		        N++;
                		ds *node = malloc(sizeof(ds));
                		node->lineNumber = N;
                		node->lineData = malloc(strlen(text)+1); // 1 is added to make space for the terminating null character
                		strcpy(node->lineData, text);
                		node->next = NULL;
                		if(tail == NULL)
                		{
                    			head = node;
                    			tail = node;
                		}
                		else
                		{
                			tail->next = node;
                    			tail = node;
                		}
            			}
                 	else
            		{
                		while(temp != NULL)
                		{
                 			if(temp->lineNumber == lineN)
                    			{
                        			char *dest = malloc(strlen(temp->lineData) + strlen(text) + 1);
                        			strcat(dest, temp->lineData);
                        			strcat(dest, text);
                        			temp->lineData = dest;
                    			}
                    			temp = temp->next;
                		}
            		}
        	}
        	else if(strcmp(command, "w") == 0)
        	{
        	    //Write the changes back to the file (overwrites the file if it exists)
            		fp = fopen(argv[argc-1], "w+");
            		ds *temp = head;
            		while(temp != NULL)
            		{
                		fprintf(fp, "%s\n", temp->lineData);
                		temp = temp->next;
            		}
        	}
        	else if(strcmp(command, "q") == 0)
        	{
            		exit(0);
        	}
		else if(strcmp(command, "r") == 0)
		{
			ds *tmp = head;
			
			
			while(1){
				

			}
			
			
		}	
        free(command);
        command = NULL;
	}

	fclose(fp);

		
    return 0;
} 
//pritesh
