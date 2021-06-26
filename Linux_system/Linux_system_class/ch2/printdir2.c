/*  We start with the appropriate headers and then a function, printdir,
    which prints out the current directory.
    It will recurse for subdirectories, using the depth parameter is used for indentation.  */

#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>

static unsigned long ndirs=0, nfiles=0;

#define MAX_ENTRY 1024

int collect_entry(DIR *dp, struct dirent **entry)
{
    int cnt = 0;
    struct dirent *tmp_ent;
    while((tmp_ent = readdir(dp)) != NULL) {
        entry[cnt++] = tmp_ent;
    }
    return cnt;
}

void printdir(char *dir, int depth)
{
    DIR *dp;
    struct dirent *entry[MAX_ENTRY], *ent;
    struct stat statbuf;
    extern unsigned long ndirs, nfiles;
    int i = 0, cnt = 0;
    if((dp = opendir(dir)) == NULL) {
        fprintf(stderr,"cannot open directory: %s\n", dir);
        return;
    }
    chdir(dir);
    cnt = collect_entry(dp, entry); 
    for( i = 0; i < cnt; i++ ) {
        lstat(entry[i]->d_name,&statbuf);
        if(S_ISDIR(statbuf.st_mode)) {
            /* Found a directory, but ignore . and .. and .xxxxx hidden files*/
            if(strcmp(".",entry[i]->d_name) == 0 || entry[i]->d_name[0]=='.' ||
                strcmp("..",entry[i]->d_name) == 0)
                continue;
	    ndirs++;
            printf("%*s%s\n",depth," ",entry[i]->d_name);
            /* Recurse at a new indent level */
            printdir(entry[i]->d_name,depth+4);
		
        }
        else { 
 		 nfiles++;
		 printf("%*s%s\n",depth," ",entry[i]->d_name);
		 
             }
    }
    chdir("..");
    closedir(dp);
}

/*  Now we move onto the main function.  */

int main(int argc, char* argv[])
{
    char *topdir, pwd[2]=".";
    if (argc != 2)
        topdir=pwd;
    else
        topdir=argv[1];

    printf("Directory scan of %s\n",topdir);
    printdir(topdir,0);
    printf("done.\n");
    printf("\n %ld directories, %ld files\n",ndirs, nfiles);

    exit(0);
}


