
       #include <sys/types.h>
       #include <sys/stat.h>
       #include <time.h>
       #include <stdio.h>
       #include <stdlib.h>
       #include <string.h>
       void show_rwx(short m);

       void long_list(char *fname)
       {
           struct stat sb;
			char *p;
           if (lstat(fname, &sb) == -1) {
               perror("stat");
               exit(EXIT_FAILURE);
           }

          

           switch (sb.st_mode & S_IFMT) {
           case S_IFBLK:  printf("b");            break;
           case S_IFCHR:  printf("c");        break;
           case S_IFDIR:  printf("d");               break;
           case S_IFIFO:  printf("p");               break;
           case S_IFLNK:  printf("l");                 break;
           case S_IFREG:  printf("-");            break;
           case S_IFSOCK: printf("s");                  break;
           }


           show_rwx(sb.st_mode);

           printf(" %ld", (long) sb.st_nlink);
           printf(" %ld  %4ld",
                   (long) sb.st_uid, (long) sb.st_gid);

           printf(" %5ld",

                   (long) sb.st_size);

		   p=ctime(&sb.st_atime);
		   p[strlen(p)-1]='\0';
           printf(" %s", p);
           printf(" %s", fname);
           printf("\n");

           
       }

void show_rwx(short m)
{

printf("%c",(m & S_IRUSR)?'r':'-');
printf("%c",(m & S_IWUSR)?'w':'-');
printf("%c",(m & S_IXUSR)?'x':'-');
printf("%c",(m & S_IRGRP)?'r':'-');
printf("%c",(m & S_IWGRP)?'w':'-');
printf("%c",(m & S_IXGRP)?'x':'-');
printf("%c",(m & S_IROTH)?'r':'-');
printf("%c",(m & S_IWOTH)?'w':'-');
printf("%c",(m & S_IXOTH)?'x':'-');



}




