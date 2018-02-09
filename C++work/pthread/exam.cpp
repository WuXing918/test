#include <pthread.h>
#include <stdio.h>
 
pthread_cond_t m_cond;
pthread_mutex_t m_lock;
 
void *threadFunc(void * pm_iPthreadId)
{
    pthread_mutex_lock(&m_lock);
    unsigned int iId = *(unsigned int *) pm_iPthreadId;
    printf("### No.%d pthread start exec; pthread id = %u !\n", iId, pthread_self());
    pthread_cond_signal(&m_cond);
      
    int cnt = 0;
    time_t iStartTime = time(NULL);
    while(1)
    {
        time_t iTempTime = time(NULL);
        if (iTempTime - iStartTime > 2) 
        {
            printf("$$$ NO.%d pthread cirle exec, cnt is %d !\n",*(unsigned int *)pm_iPthreadId, cnt);
            iStartTime = time(NULL);
            break;
        }
    }
    pthread_mutex_unlock(&m_lock);
}
 
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
    int
main ( int argc, char *argv[] )
{
    pthread_mutex_init(&m_lock, NULL);
    pthread_cond_init(&m_cond, NULL);
      
    pthread_t *pthreadId;
    pthreadId = new pthread_t[10];
    for (unsigned int i = 0; i < 10; i++)
    {
        pthread_mutex_lock(&m_lock);
        int iRet = pthread_create(pthreadId + i, NULL, threadFunc, &i);
        if (iRet == 0) 
        {
            printf("@@@ create No.%d pthread success, pthreadId = %u !\n", i, pthreadId + i);
        }
        pthread_cond_wait(&m_cond, &m_lock);
        pthread_mutex_unlock(&m_lock);
    }
 
    /*
    while(1)
    {
    }
    */
      
    return 0;
}
