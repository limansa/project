char    screen[1024];
char *cursor = screen;
int once = 0;
inline void dbg(const char *fmt, ...)
{
    va_list args;
    uint    i;
    char    printbuffer[CFG_PBSIZE];

    if (!once) {
        memset(screen, 0, sizeof(screen));
        once++;
    }

    va_start(args, fmt);

    /* For this to work, printbuffer must be larger than
     * anything we ever want to print.
     */
    i = vsprintf(printbuffer, fmt, args);
    va_end(args);
    if ((screen + sizeof(screen) - 1 - cursor) < strlen(printbuffer)+1) {
        memset(screen, 0, sizeof(screen));
        cursor = screen;
    }
    sprintf(cursor, printbuffer);
    cursor += strlen(printbuffer);

}
#else
inline void dbg(const char *fmt, ...)
{
}
