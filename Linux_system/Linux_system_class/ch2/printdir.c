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

void printdir(char *dir, int depth)
{
    DIR *dp;
    struct dirent *entry;
    struct stat statbuf;
    extern unsigned long ndirs, nfiles;
    if((dp = opendir(dir)) == NULL) {
        fprintf(stderr,"cannot open directory: %s\n", dir);
        return;
    }
    chdir(dir);
    while((entry = readdir(dp)) != NULL) {
        lstat(entry->d_name,&statbuf);
        if(S_ISDIR(statbuf.st_mode)) {
            /* Found a directory, but ignore . and .. and .xxxxx hidden files*/
            if(strcmp(".",entry->d_name) == 0 || entry->d_name[0]=='.' ||
                strcmp("..",entry->d_name) == 0)
                continue;
	    ndirs++;
            printf("%*s%s\n",depth," ",entry->d_name);
            /* Recurse at a new indent level */
            printdir(entry->d_name,depth+4);
		
        }
        else {   
 		 nfiles++;
		 printf("%*s%s\n",depth," ",entry->d_name);
		 
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


