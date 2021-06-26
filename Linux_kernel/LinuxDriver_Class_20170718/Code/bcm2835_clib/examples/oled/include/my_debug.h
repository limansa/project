

#ifdef MYDEBUG
	#define DEBUGPRINTF(format, args...)  printf(format, ##args)
#else 
	#define DEBUGPRINTF(format, args...)  
#endif 
