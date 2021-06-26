int parse_args(int argc, char *argv[])
{

    int opt;
    extern char *optarg;
    extern int optind, opterr, optopt;
    opterr =0;  //disable getopt() error optput
     int has_output=0,i;

    while((opt = getopt(argc, argv, "o:")) != -1) {
        switch(opt) {

        case 'o':
            has_output=1;
           // sscanf(optarg, "%s", ROM_FILE);
            break;
        case ':':
            printf("option needs a value\n");
            break;
        case '?':
            printf("unknown option: %c\n", optopt);
            break;
        }
    }

   if (!has_output)  {
      printf("option: -o <output_file> is required\n");
      return -1;
   }


    for(i=0; optind < argc; i++,optind++) {
      printf("argument: %s %d\n", argv[optind],argc);  
    }

}
