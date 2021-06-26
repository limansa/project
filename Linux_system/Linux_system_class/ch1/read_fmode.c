//joseph add
       #include <sys/types.h>
       #include <sys/stat.h>
       #include <time.h>
       #include <stdio.h>
       #include <stdlib.h>
       #include <pwd.h>
       void show_rwx(short m);

       int
       main(int argc, char *argv[])
       {
           struct stat sb;
           struct passwd *pw;
           if (argc != 2) {
               fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
               exit(EXIT_FAILURE);
           }

           if (lstat(argv[1], &sb) == -1) {
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

         pw = getpwuid(sb.st_uid);



           printf(" %s  %ld",
                   pw->pw_name, (long) sb.st_gid);
		   


           printf(" %lld",
                   (long long) sb.st_size);

           printf(" %s\n", ctime(&sb.st_mtime));
#if 0
        time_t rawtime;
		struct tm * timeinfo;
	    time ( &rawtime );
	    timeinfo = localtime ( &rawtime );
        sprintf(file_name,"%02d%02d%02d.jpg",								        timeinfo->tm_hour,timeinfo->tm_min,timeinfo->tm_sec);

#endif

           exit(EXIT_SUCCESS);
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




