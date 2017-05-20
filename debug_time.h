#ifndef  _DEBUG_TIME_H_
#define _DEBUG_TIME_H_

#define ENABLE_TIME_DEBUG

#ifdef ENABLE_TIME_DEBUG

#ifndef WIN32
#include <sys/time.h>

/*#else
#ifndef timeval
	typedef struct timeval {
        long    tv_sec;         
        long    tv_usec;        
	}timeval;
#endif*/
#else
#include <time.h>
#include <windows.h> //I've ommited this line.
#include <WinSock.h>
#if defined(_MSC_VER) || defined(_MSC_EXTENSIONS)
  #define DELTA_EPOCH_IN_MICROSECS  11644473600000000Ui64
#else
  #define DELTA_EPOCH_IN_MICROSECS  11644473600000000ULL
#endif

struct timezone 
{
  int  tz_minuteswest; /* minutes W of Greenwich */
  int  tz_dsttime;     /* type of dst correction */
};

int gettimeofday(struct timeval *tv, struct timezone *tz);

#endif

#define DEBUG_TIME_INIT timeval before,after,final,accum;
#define DEBUG_TIME_INIT_V(n) timeval before[n],after[n],final[n],accum[n];

#define DEBUG_TIME_RESET_ACCUM \
              accum.tv_sec=0; \
              accum.tv_usec=0; \

#define DEBUG_TIME_START \
              before.tv_sec=0; \
              before.tv_usec=0; \
              after.tv_sec=0; \
              after.tv_usec=0; \
              gettimeofday(&before,NULL); \


#define DEBUG_TIME_START_V(n) \
              before[n].tv_sec=0; \
              before[n].tv_usec=0; \
              after[n].tv_sec=0; \
              after[n].tv_usec=0; \
              gettimeofday(&before[n],NULL); \


#define DEBUG_TIME_END \
                gettimeofday(&after,NULL); \
                final.tv_sec=after.tv_sec-before.tv_sec; \
                final.tv_usec=after.tv_usec-before.tv_usec; \
                if(final.tv_usec<0) \
                 {\
                    final.tv_usec+=1000000; \
                    final.tv_sec-=1; \
                } \


#define DEBUG_TIME_END_V(n)  \
    gettimeofday(&after[n],NULL); \
                final[n].tv_sec=after[n].tv_sec-before[n].tv_sec; \
                final[n].tv_usec=after[n].tv_usec-before[n].tv_usec; \
                if(final[n].tv_usec<0) \
                 {\
                    final[n].tv_usec+=1000000; \
                    final[n].tv_sec-=1; \
                } \



#define DEBUG_TIME_ACCUM \
    accum.tv_sec=accum.tv_sec + final.tv_sec; \
    accum.tv_usec=accum.tv_usec + final.tv_usec; \
    if(accum.tv_usec>1000000) \
    { \
        accum.tv_usec-=1000000; \
        accum.tv_sec+=1;\
    }\
	

#define DEBUG_TIME_ACCUM_V(n) \
    accum[n].tv_sec=accum[n].tv_sec + final[n].tv_sec; \
    accum[n].tv_usec=accum[n].tv_usec + final[n].tv_usec; \
    if(accum[n].tv_usec>1000000) \
    { \
        accum[n].tv_usec-=1000000; \
        accum[n].tv_sec+=1;\
    }\


#define DEBUG_TIME_ACCUM_PARAM(ac)\
    ac.tv_sec=ac.tv_sec + final.tv_sec; \
    ac.tv_usec=ac.tv_usec + final.tv_usec; \
    if(ac.tv_usec>1000000) \
    {\
        ac.tv_usec-=1000000;\
        ac.tv_sec+=1;\
    }\

#define DEBUG_TIME_ACCUM_PARAM_V(n,ac)\
    ac.tv_sec=ac.tv_sec + final[n].tv_sec; \
    ac.tv_usec=ac.tv_usec + final[n].tv_usec; \
    if(ac.tv_usec>1000000) \
    {\
        ac.tv_usec-=1000000;\
        ac.tv_sec+=1;\
    }\


#define DEBUG_PRINT_FINALTIME(message)  printf("%s time: %d.%06d \n",message,(int)final.tv_sec,(int)final.tv_usec);
#define DEBUG_PRINT_FINALTIME_PARAM(message,ac)  printf("%s time: %d.%06d \n",message,(int)ac.tv_sec,(int)ac.tv_usec);
#define DEBUG_PRINT_AVERAGE_FINALTIME_PARAM(message,ac,average) printf("%s average time: %f \n",message,((float)ac.tv_sec+((float)ac.tv_usec/1000000.0))/(float)average);
#define DEBUG_PRINT_ACCUMTIME(message)  printf("%s time: %d.%06d \n",message,(int)accum.tv_sec,(int)accum.tv_usec);

#else

#define DEBUG_TIME_INIT
#define DEBUG_TIME_RESET_ACCUM
#define DEBUG_TIME_START
#define DEBUG_TIME_END
#define DEBUG_TIME_ACCUM
#define DEBUG_TIME_ACCUM_PARAM(ac)
#define DEBUG_PRINT_FINALTIME(message)
#define DEBUG_PRINT_FINALTIME_PARAM(message,ac)
#define DEBUG_PRINT_ACCUMTIME(message)

#endif
#endif

