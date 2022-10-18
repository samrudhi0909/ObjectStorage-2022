#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include "/home/esha/Downloads/isa-l_open_src_2.13/include/erasure_code.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define PERMPATH "/home/esha/folder"

int u = 0;
struct Nodell{
FILE *fp;
int uid;
char filetype[20];
int filesize;
struct Nodell *next;
char *filepath;
};

struct Nodell *head0 = NULL;
struct Nodell *head1 = NULL;
struct Nodell *head2 = NULL;
struct Nodell *head3 = NULL;
struct Nodell *head4 = NULL;
struct Nodell *last0 = NULL;
struct Nodell *last1 = NULL;
struct Nodell *last2 = NULL;
struct Nodell *last3 = NULL;
struct Nodell *last4 = NULL;
struct Nodell *head = NULL;
struct Nodell *last = NULL;

int map[20];
int Put(char path[]);
bool Get(int uid, char path[]);
//void List(int uid);
void Listall();
int generateUID(void);
int filesize(struct Nodell *newnode);
void readline(char comm[],char **st[]);
int* missing(int uid, int* ans);
void divide(struct Nodell *newnode);
int* missingfolder(int uid, int* ans);
int check_if_file_exists(char *newpath);
int isDir(char* newpath);

int bsize = 5;
unsigned char g_tbls[11 * 11 * 32]; //= (char *)malloc(size *sizeof(char));


int main(void)
{
    char *substring[3];
    size_t size = 50;
    char *command;
   //struct Nodell db[5];
    //FILE *fin = NULL;
    int z = 0;
    //int x = 0;

    unsigned char gen[11 * 11];// = (char *)malloc(size *sizeof(char));
   
    gf_gen_rs_matrix(gen, 11, 8);
   
    //printf("\n******************** GENERATOR MATRIX ********************\n");
   
    for(z = 0; z < 88; z++)
    {
if (z%8 == 0) {
//printf("\n");
}
   
  //  printf("----");
   
    //printf("%d ", gen[z]);
    }
   
    ec_init_tables(8, 3, &gen[8 * 8], g_tbls);

    command= (char *)malloc(size *sizeof(char));

    while(1){
        printf("\n");
        printf("\nObjstorage> ");
        printf("\n1. Type 'Put' and path of file for creating an Object");
        printf("\n2. Type 'Get', UID and path of file for getting an Object");
        printf("\n3. Type 'List' for getting the list of all objects in object storage");
        printf("\n4. 'Quit'\n");
        printf("\n>>");
        if(getline(&command, &size,stdin)==1)
        {
        }

        char cmd = command[0];
      //  int i = 1;

        readline(command,&substring);
        //printf("%c", cmd);
      //  struct Nodell *temp = NULL;

        switch(toupper(cmd)){
                    case 'P':printf("\n******************** You are now in PUT funt: ********************\n");

                    substring[1][strlen(substring[1]+1)] = '\0';
                             //fin = fopen(substring[1], "r");
                             printf("\nThis is the path of file: %s\n", substring[1]);

int unique = Put(substring[1]);
printf("\nFile stored with unique id %d\n", unique);


                             break;
                    case 'G' :printf("\n******************** You are now in GET funt: ********************\n");
                              printf("\nFile to be searched with uid : %d and put into path: %s",atoi(substring[1]),substring[2]);

                              if(Get(atoi(substring[1]),substring[2]))
                              {

                                  printf("File retrieved in specified path");
                              }
                              else
                              {
                                  printf("\nFile cannot be retrieved.");
                              }
                              break;

                    case 'Q':printf("\nThankyou, we end your session here!");
                             goto out;
                             break;

                    case 'L':

                                        Listall();
                             break;

                    case 'A':

                              break;

                    default: printf("\nInput not valid");
                             break;

                }
    }


    out: printf("\nTo restart,run the program again\n");
    return 0;
}

void readline(char comm[],char **st[]){
    int i = 0;
    char * token = strtok(comm, " ");

    while( token != NULL ){
      st[i] = token;
      i++;
      token = strtok(NULL, " ");
    }
}

int Put(char path[])
{
	struct Nodell *newnode = malloc(sizeof(struct Nodell));
	int j, hash;

	newnode->filepath = (char *)calloc(strlen(path),sizeof(char));
	for (j = 0; path[j]!='\0'; j++) 
	{
		newnode->filepath[j] = path[j];
	}

	newnode->fp = fopen(path, "r");
	newnode->uid = generateUID();

	fseek(newnode->fp,0,SEEK_END);
	newnode->filesize = ftell(newnode->fp);
	//int size = newnode->filesize;
	map[newnode->uid] = newnode->filesize/8;


	printf("File size is %d\n\n", newnode->filesize);
	fclose(newnode->fp);


	hash = newnode->uid % bsize;

	divide(newnode);

	switch(hash) 
	{
		case 0:
			if(head0 == NULL) 
			{
				head0 = newnode;
				last0 = newnode;
			} 
			else 
			{
				last0->next = newnode;
				last0 = newnode;
			}
				last0->next = NULL;
			break;

		case 1:
			if (head1 == NULL) 
			{
				head1 = newnode;
				last1 = newnode;
			} 
			else 
			{
				last1->next = newnode;
				last1= newnode;
			}
				last1->next = NULL;
			break;

		case 2:
			if (head2 == NULL) 
			{
				head2 = newnode;
				last2 = newnode;
			} 
			else 
			{
				last2->next = newnode;
				last2 = newnode;
			}
				last2->next = NULL;
			break;

		case 3:
			if (head3 == NULL) 
			{
				head3 = newnode;
				last3 = newnode;
			} 
			else 
			{
				last3->next = newnode;
				last3 = newnode;
			}
				last3->next = NULL;
			break;

		case 4:

			if (head4 == NULL) 
			{
				head4 = newnode;
				last4 = newnode;
			} 
			else 
			{
				last4->next = newnode;
				last4 = newnode;
			}
				last4->next = NULL;
			break;

		}
		return newnode->uid;
}

int generateUID(void)
{
    u = u + 1;
    return u;
}




bool Get(int uid, char path[])
{
	struct Nodell *temp = NULL;
	//struct Nodell *newnode = NULL;
	int ret = 1;
	char *newpath;
	char *newpath2;
	
	bool ans = false;
	int foldermissing = 0;
	FILE *fptr1, *fptr2, *fptr3;
	char c, cc, perm[80], regenpath[80];// permperm[80];
	int i, j, k;
	int v = 0;
	int arr[8];
	int z, t, h = 0;
	int* a = missingfolder(uid, arr);
	
	newpath = (char *)malloc(sizeof(strlen(path)));
	newpath2 = (char *)malloc(sizeof(strlen(path)));
	
	newpath = path;
	newpath2 = path;
	
	ret = isDir(newpath2);

	if (ret == 0)
	{
		printf("Given path is a directory\n");
		switch(uid%5)
		{
			case 0: for(temp = head0; temp != NULL; temp = temp->next)
				{
					if(uid == temp->uid)
					{
				
						//printf("%s", temp->filepath);
						
						
							char *token = strrchr(temp->filepath,'/')+1;
							      printf("%s\n",token);
					}
				}
				break;
				
			case 1: for(temp = head1; temp != NULL; temp = temp->next)
			{
				if(uid == temp->uid)
				{
			
					//printf("%s", temp->filepath);
					
					
						char *token = strrchr(temp->filepath,'/')+1;
							      printf("%s\n",token);
				}
			}
			break;
			
			case 2: for(temp = head2; temp != NULL; temp = temp->next)
				{
					if(uid == temp->uid)
					{
				
						//printf("%s", temp->filepath);
						
						
							char *token = strrchr(temp->filepath,'/')+1;
							      printf("%s\n",token);
					}
				}
				break;
				
				
				
			case 3: for(temp = head3; temp != NULL; temp = temp->next)
				{
					if(uid == temp->uid)
					{
				
						//printf("%s", temp->filepath);
						
						
							char *token = strrchr(temp->filepath,'/')+1;
							      printf("%s\n",token);
					}
				}
				break;
				
				
				
			case 4: for(temp = head4; temp != NULL; temp = temp->next)
				{
					if(uid == temp->uid)
					{
				
						//printf("%s", temp->filepath);
						
						
							char *token = strrchr(temp->filepath,'/')+1;
							      printf("%s\n",token);
					}
				}
				break;
						
		
		}
		
	}
	else
	{
		printf("Given path is a file\n");

		if(check_if_file_exists(newpath) == 1)
		{

			

			for(h = 0; h < 8; h++)
			{
				if(a[h] == 0 && h == 7)
				{
					a = missing(uid, arr);
					break;
				}
				
				if(a[h] == 0)
					continue;
					
				if(a[h] != 0)
				{
					foldermissing = 1;
					break;
				}
			}

		int aa = -1;

		//long int sum = 0;
		int e = 0;
		int marr[3];
		int newline = 0;
		int prints = 0;
		unsigned char gen[11 * 11];// = (char *)malloc(size *sizeof(char));
		   
		unsigned char recovery[64];
		unsigned char decode[64];
		unsigned char frdm[24];
		//unsigned char fd[8];
		unsigned char *temp_buffs[3];
		unsigned char *a_chunks[8];
		//unsigned char *b_chunks;
		//unsigned char mat[8][8];
		unsigned char r_tables[11 * 11 * 32];
		//int size = 0;


		int s = map[uid];

		for(k = 0; k < 8; ++k)
		{
			if(a[k] != 0)
			{
				aa = aa + 1;
			}
		}

		if(aa == -1)
		{
			ans = true;

			//len = strlen(path);
			//printf("path = %s abc len = %ld", path, strlen(path));

			//if (path[len - 1] != '\0')
			//{
			//path[len - 1] = '\0';
			//}

			//printf("path = %s abc len = %ld", path, strlen(path));
			// Open another file for writing
			fptr2 = fopen(path, "a");
			if (fptr2 == NULL)
			{
				printf("Cannot open file %s \n", path);
				exit(0);
			}
			
			printf("\n");

			for (k = 0; k < 8; ++k)
			{
				sprintf(perm, "%s%d/file%d_%d%c", PERMPATH, k, uid, k,'\0');
				//printf("Contents taken from chunk at path: %s\n", perm);

				fptr1 = fopen(perm, "r");
				if (fptr1 == NULL)
				{
					printf("Cannot open file %s \n", perm);
					exit(0);
				}

				// Read contents from file
				c = fgetc(fptr1);
				while (c != EOF)
				{
				   fputc(c, fptr2);
				   c = fgetc(fptr1);
				}
			}

			printf("\nAll contents merged into %s\n\n", path);
			printf("All chunks available. ");
			fclose(fptr1);
			fclose(fptr2);
		}
		else
		{
			//parity
			if(foldermissing == 1)
			printf("\nFolder(s) is/are missing\n");
			printf("\nThe missing data chunk number(s) is/are:");
			int m = 0;
			for(k = 0; k < 8; k++)
			{
				if(a[k] != 0)
				{
					printf("\n%d", k);
					marr[m] = k;
					m++;
				}
			}
			m--;
			
			printf("\n\nNumber of chunks missing: %d", m+1);

			if(aa > 2)
			{
				return ans;
			}

			for(i = 0; i < 8; i++)
			{
				a_chunks[i] = (unsigned char *)calloc(s, sizeof(unsigned char));
			}

			 
			e = 0;
		
			//printf("\n\nAvailable Chunks are: ");
			for (k = 0; k < 8; ++k)
			{
				if(a[k]!=0)
				continue;



				if(a[k]==0)
				//printf("\n\nAvailable Chunk is: ");

				//fptr2 = newnode->fp;

				sprintf(perm, "%s%d/file%d_%d%c", PERMPATH, k, uid, k,'\0');
				//printf("%s\n", perm);


				   fptr3 = fopen(perm, "r");
				   if (fptr3 == NULL)
				   {
					printf("Cannot open file %s \n", perm);
					exit(0);
				   }



				for(j = 0; j < s; j++)
				{

					cc = (char)fgetc(fptr3);
					a_chunks[e][j] = cc;

					//fputc(a_chunks[k][j], fptr1);
					//printf("%c", a_chunks[e][j]);

				}

				e++;

				fclose(fptr3);
			}


			for(h = 0; h < m + 1; h++)
			{
				//printf("\nParity Chunk is:\n");
				sprintf(perm, "%s%d/parityfile%d_%d%c", PERMPATH, h+8, uid, h+1,'\0');
				//printf("%s\n", perm);

				fptr3 = fopen(perm, "r");
				if (fptr3 == NULL)
				{
					printf("Cannot open file %s\n", perm);
					exit(0);
				}


				for(j = 0; j < s; j++)
				{
					// Read contents from file
					a_chunks[e][j] = (char)fgetc(fptr3);
					//printf("%c", a_chunks[e][j]);
					//fputc(parity[k][j], fptr3);

				}
				
				e++;
				//printf("\nContents copied to %s", perm);
				fclose(fptr3);
			}



			printf("\n\nAll available data chunks plus needed parity chunks:\n\n");
			for(i=0;i<8;i++)
			{
				printf("%s", a_chunks[i]);
			}
			printf("\n");

		 
		   
			    //printf("\nRecovery Matrix:\n");
			gf_gen_rs_matrix(gen, 11, 8);

			//for(h = 0; h < m+1; h++)
			//printf("%d", marr[h]);
			    h = 0;
			    newline = 0;
			    int ff = 0;
			for(z = 0; z < 88; z++)
			   {
			   
			if (z%8 == 0)
			{
				newline += 1;
			}


			if(newline == marr[h] + 1)
			{
				ff += 1;
				// printf("FFFF: %d", ff);
				if(ff % 8 == 0 && m !=h)
				{
					h++;
					//printf("--------");
				}

				continue;
			}

			   
			  // printf("----");
			 
			 
			    recovery[v] = gen[z];
			   
			    //printf("%d ", recovery[v]);
			    v++;
			   
			    prints += 1;
			    if(prints == 64)
			    break;
			   
			   }
		   
		   
		  /* for(v=0; v<64; v++)
		   {
		    if (v%8 == 0)
		{
		printf("\n");

		}
		    printf("%d ", recovery[v]);
		   
		   }
		   */

		     gf_invert_matrix(recovery, decode, 8);
		       
		  /* printf("\n\nInverse of Recovery Matrix(Decode Matrix):\n");
		   for(v = 0; v < 64; v++)
		   {
		   if(v % 8 == 0)
		    printf("\n");
		   printf("%d ", decode[v]);
		   }

		   
		printf("\n\nFailed_row_decode_matrix:\n\n");*/
		int mm = 0;
		t = 0;
		for(mm = 0; mm < m+1; mm++)
		{
		for(v=8*marr[mm]; v < 8*(marr[mm]+1); v++)
		{
		frdm[t] = decode[v];
		//printf("%d ", frdm[t]);
		t++;
		}
		//printf("\n");
		}

		ec_init_tables(8, 3, frdm, r_tables);

		printf("\n");

		//int s = filesize(

		for(i = 0; i < 3; i++)
		{
		temp_buffs[i] = (unsigned char *)calloc(s, sizeof(unsigned char));
		}


		ec_encode_data_base(s, 8, m+1, r_tables, a_chunks, temp_buffs);
		//ec_encode_data_base(s, 8, 3, g_tbls, data, parity);

		//printf("%s\n", temp_buffs[0]);
		//printf("%s\n", temp_buffs[1]);
		//printf("%s\n", temp_buffs[2]);


		printf("Missing Chunk(s) getting regenerated:");
		m = 0;
		for(k = 0; k < 8; k++)
		{
		if(a[k] != 0)
		{
		//printf("\n%d", k);
		marr[m] = k;
		m++;
		}
		}
		m--;

		printf("\n");

		if(foldermissing == 0)
		{
		for(h = 0; h < m+1; h++)
		{
		for(i=0;i<s;i++)
		{
		sprintf(regenpath, "%s%d/file%d_%d%c", PERMPATH, marr[h], uid, marr[h],'\0');
		fptr1 = fopen(regenpath, "a");
		if (fptr1 == NULL)
		{
		printf("Cannot open file %s \n", regenpath);
		exit(0);
		}


		//Put contents from file
		printf("%c", temp_buffs[h][i]);

		fputc(temp_buffs[h][i], fptr1);

		fclose(fptr1);


		}


		//printf("\nContents of renegrated chunk copied to regenerated file: %s\n", regenpath);

		}
		}


		for(i = 0; i < 8; i++)
			{
		free(a_chunks[i]);
			}

		//len = strlen(path);
		//printf("path = %s abc len = %ld", path, strlen(path));

		//if (path[len - 1] != '\0')
		//{
		//path[len - 1] = '\0';
		//}


		// Open another file for writing
		fptr2 = fopen(path, "a");
		if (fptr2 == NULL)
		{
		printf("Cannot open file %s \n", path);
		exit(0);
		}

		int hh = 0;
		for (k = 0; k < 8; ++k)
		{
		sprintf(perm, "%s%d/file%d_%d%c", PERMPATH, k, uid, k,'\0');

		fptr1 = fopen(perm, "r");
		if (fptr1 == NULL)
		{

		//printf("Cannot open file %s \n", perm);

		if(foldermissing == 1)
		{
		for(i=0;i<s;i++)
		{
		//Put contents from file
		printf("%c", temp_buffs[hh][i]);

		fputc(temp_buffs[hh][i], fptr2);
		}

		hh++;
		//printf("<---Folder was missing. Contents of path %s regenerated.\n", perm);
		if(k == 7)
		fptr1 = fopen(path, "r");
		}
		else
		{
		printf("Cannot open file %s \n", perm);
		exit(0);
		}
		}
		else
		{
		// Read contents from file
		c = fgetc(fptr1);
		while (c != EOF)
		{
		   fputc(c, fptr2);
		   c = fgetc(fptr1);
		}
		//printf("Contents taken from chunk at path: %s\n", perm);

		}

		}

		printf("\nAll contents after regeneration being merged into path given by user: %s\n\n", path);
		fclose(fptr1);
		fclose(fptr2);
		//printf("\nAll contents copied to %s\n\n", path);
		printf("\nChunk(s) were missing, parity calculated. ");

		for(i = 0; i < 3; i++)
			{
		free(temp_buffs[i]);
			}



		//ans = getafterparity(uid, path, temp_buffs);
		}

		ans = true;
		return ans;
		}
		else
			return false;
	}
	return false;
}


/*int filesize(struct Nodell *newnode){

fseek(newnode->fp,0,SEEK_END);
int s = ftell(newnode->fp);
printf("File size is %d", newnode->filesize);
fclose(newnode->fp);
return s;
}*/


void Listall()
{
    struct Nodell *temp = NULL;

    printf("\nFilename    :     UID\n");
    printf("\nBucket 0:\n");
    for(temp = head0; temp != NULL; temp = temp->next)
       {
        char *token = strrchr(temp->filepath,'/')+1;
              printf("%s : %d\n",token,temp->uid);
       }
    printf("\nBucket 1:\n");
    for(temp = head1; temp != NULL; temp = temp->next)
    {
    char *token = strrchr(temp->filepath,'/')+1;
        printf("%s : %d\n",token,temp->uid);
    }
    printf("\nBucket 2:\n");
    for(temp = head2; temp != NULL; temp = temp->next)
    {
    char *token = strrchr(temp->filepath,'/')+1;

        printf("%s : %d\n",token,temp->uid);
    }
    printf("\nBucket 3:\n");
    for(temp = head3; temp != NULL; temp = temp->next)
    {
      char *token = strrchr(temp->filepath,'/')+1;

        printf("%s : %d\n",token,temp->uid);
    }
    printf("\nBucket 4:\n");
    for(temp = head4; temp != NULL; temp = temp->next)
    {
     char *token = strrchr(temp->filepath,'/')+1;

        printf("%s : %d\n",token,temp->uid);
    }
    


}

/*
 * Divide the file into data chunks, calculate parity chunks and store the
 * chunks into data and parity folders.
 */
void divide(struct Nodell *newnode)
{
char *path = newnode->filepath;
int size = newnode->filesize;
FILE *f = fopen(path, "r");
int s = size/8;
char perm[80];
int k, i, j;
unsigned char *data[8], *parity[3];
FILE *fptr3;
int arr[8];
int foldermissing = 0;

for(i = 0; i < 8; i++)
{
data[i] = (unsigned char *)calloc(s, sizeof(unsigned char));
}

for (i = 0; i < 3; i++) {
parity[i] = (unsigned char *)calloc(s, sizeof(unsigned char));
}

int* a = missingfolder(newnode->uid, arr);
int h = 0;
for(h = 0; h < 8; h++)
{
if(a[h] == 0)
continue;
if(a[h] != 0)
{
foldermissing = 1;
break;
}
}

printf("--------------------Data Chunks:--------------------\n\n");

for(k = 0; k < 8; k++)
{
sprintf(perm, "%s%d/file%d_%d%c", PERMPATH, k, newnode->uid, k,'\0');
printf("Chunk number %d:", k);

// Open another file for writing
fptr3 = fopen(perm, "w");

if (fptr3 == NULL)
{

if(foldermissing == 1)
{

fptr3 = fopen(path, "r");
for(j = 0; j < s; j++)
{
data[k][j] = (char)fgetc(f);
printf("%c", data[k][j]);
}
//printf("<---Folder Missing. Chunk not stored.\n");
printf("\n");

continue;

}
else
{
printf("Cannot open file %s \n", perm);
exit(0);
}
}
else
{
for(j = 0; j < s; j++)
{
// Read contents from file

data[k][j] = (char)fgetc(f);
printf("%c", data[k][j]);

fputc(data[k][j], fptr3);

}

//printf("\nContents copied to %s\n", perm);
fclose(fptr3);
printf("\n");
}

}

fclose(f);
printf("--------------------Parity Chunks:--------------------\n");

ec_encode_data_base(s, 8, 3, g_tbls, data, parity);
printf("\nParity 0:\n");
for(i=0; i<s; i++)
{
printf("%c", parity[0][i]);
}
printf("\n\nParity 1:\n");
for(i=0; i<s; i++)
{
printf("%c", parity[1][i]);
}
printf("\n\nParity 2:\n");
for(i=0; i<s; i++)
{
printf("%c", parity[2][i]);
}
printf("\n\n");



//int ss = (sizeof(parity[0])+sizeof(parity[1])+sizeof(parity[2]))/sizeof(char);
int o = 1;
for(k = 8; k < 11; k++)
{

sprintf(perm, "%s%d/parityfile%d_%d%c", PERMPATH, k, newnode->uid, o,'\0');
//printf("%s\n", perm);

// Open another file for writing
fptr3 = fopen(perm, "w");
if (fptr3 == NULL)
{
printf("Cannot open file %s \n", perm);
exit(0);
}


for(j = 0; j < s; j++)
{
// Read contents from file
//parity[k][j] = (char)fgetc(f);
//printf("%c", parity[k-8][j]);
fputc(parity[k-8][j], fptr3);

}

//printf("\nContents copied to %s\n", perm);
fclose(fptr3);
//printf("\n");
o += 1;

}





        for(i = 0; i < 8; i++)
        {
free(data[i]);
        }

        for (i = 0; i < 3; i++)
        {
                free(parity[i]);
        }
}

int* missing(int uid, int* ans)
{
FILE *fptr1;
char perm[80];

int k = 0;

for(k = 0; k < 8; ++k)
{
sprintf(perm, "%s%d/file%d_%d%c", PERMPATH, k, uid, k,'\0');
//printf("%s\n", perm);

fptr1 = fopen(perm, "r");
if (fptr1 == NULL)
{
ans[k] = 1;
printf("%d", ans[k]);
//fclose(fptr1);
//printf("Cannot open file %s \n", perm);


continue;
}
else
{
ans[k]=0;
}
fclose(fptr1);
printf("%d", ans[k]);
}


return ans;
}


int* missingfolder(int uid, int* ans)
{
FILE *fptr1;
char perm[80];

int k = 0;

//printf("FOLDER MISSING");
for(k = 0; k < 8; ++k)
{
sprintf(perm, "%s%d%c", PERMPATH, k,'\0');
//printf("%s\n", perm);

fptr1 = fopen(perm, "r");
if (fptr1 == NULL)
{
ans[k] = 1;
//printf("%d", ans[k]);
//fclose(fptr1);
//printf("Cannot open file %s \n", perm);


continue;
}

else
{
ans[k]=0;
}
fclose(fptr1);
//printf("%d", ans[k]);
}


return ans;
}

int check_if_file_exists(char *newpath)
{
	newpath[strcspn(newpath, "\n")] = 0;
	
	//printf("%s", newpath);
	if(access(newpath, F_OK ) != -1)
	{
		//printf("%s", newpath);
		printf("\nFile already exists, try another name.\n");
		return -1;
	}
	else
	{
		//printf("%s", newpath);
		return 1;
	}
}


int isDir(char* newpath)
{

	int flag=0;
	int i = 0;
	for(i=0;i<strlen(newpath);++i)
	{
	    if(newpath[i] == '.')
	    { 
		flag=1;
		break;
	    }
	}
	return flag;
}