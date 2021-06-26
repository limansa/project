unsigned long crc32 (unsigned long, const unsigned char *, unsigned int);


    if(read(in, &environment, sizeof(environment))!=sizeof(environment)) {
        printf("read %s  error!\n",CONFIG_FILE);
        abort();
    }

    env_data = environment.data;
    env_crc = environment.crc;
    crc1=crc32(0, env_data, ENV_SIZE);
     if (crc1 != env_crc) {
                printf("Error: crc mismatch !\n");
                abort();
   }

void env_crc_update (void)
{

        uint32_t crc;
        uchar *env_data = environment.data;
        crc=crc32(0, env_data,ENV_SIZE);
        environment.crc=crc;
        //printf("wirte new crc=0x%08X\n\n",crc);

}

