#ifndef __DEBUG_H__
#define __DEBUG_H__

#define _DEBUG

#ifdef _DEBUG
#define DEBUG(format, args...) printf("[%s:%d %s()] "format"\n", __FILE__, __LINE__, __FUNCTION__, ##args)
#define log_put(log_category, nfc_priority_trace, format, args...) printf("[%s:%d %s()] "format"\n", __FILE__, __LINE__, __FUNCTION__, ##args)
#else
#define DEBUG(args...)
#define log_put(log_category, nfc_priority_trace, format, args...)
//#define log_put(log_category, nfc_priority_trace, format, args...) printf("[%s:%d %s()] "format"\n", __FILE__, __LINE__, __FUNCTION__, ##args)
#endif


#endif  //__DEBUG_H__
