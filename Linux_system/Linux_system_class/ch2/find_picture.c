/*  We start with the appropriate headers and then a function, printdir,
    which prints out the current directory.
    It will recurse for subdirectories, using the depth parameter is used for indentation.  */

#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <strings.h>

int check_type(char *ext);
void printdir(char *dir, int depth);

#define MAX_FILES 1000
static char *s_imagetype[] = {
".jpg",
".bmp",
".gif",
".png",
0
};


void printdir(char *dir, int depth)
{
    DIR *dp;
    struct dirent *entry;
    struct stat statbuf;

    if((dp = opendir(dir)) == NULL) {
        fprintf(stderr,"cannot open directory: %s\n", dir);
        return;
    }
    chdir(dir);
    while((entry = readdir(dp)) != NULL) {
        lstat(entry->d_name,&statbuf);
        if(S_ISDIR(statbuf.st_mode)) {
            /* Found a directory, but ignore . and .. */
            if(strcmp(".",entry->d_name) == 0 || 
                strcmp("..",entry->d_name) == 0)
                continue;
            // printf("%*s%s/\n",depth,"",entry->d_name);
            /* Recurse at a new indent level */
            printdir(entry->d_name,depth+4);
        }
        else {

		char *p; 
		char buf[256];		
		char full_path[256];
		p=rindex(entry->d_name,'.');
		if( p != NULL)
		{    
			if (check_type(p)) {
			getcwd(buf,sizeof(buf));
			sprintf(full_path,"%s/%s\n",buf,entry->d_name);
			printf("%s",full_path);	
 			
			}
			
		}
		
//		 printf("%*s%s\n",depth,"",entry->d_name);


	}

    }
    chdir("..");
    closedir(dp);
}

int check_type(char *ext) 
{

 if( ext == NULL) return 0;

   int i;

    for (i=0;s_imagetype[i];i++) {
      if (!strcmp(ext,s_imagetype[i]))  
          return 1;

    }

  return 0;


 

}

/*  Now we move onto the main function.  */

int main(int argc, char* argv[])
{
    char *topdir, pwd[2]=".";
    if (argc != 2)
        topdir=pwd;
    else
        topdir=argv[1];

   // printf("Directory scan of %s\n",topdir);
    printdir(topdir,0);
   // printf("done.\n");

    exit(0);
}


