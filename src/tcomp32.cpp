#include <tcomp32.hpp>
#include <CLContainer.hpp>
#include <iostream>
#include <string>
using namespace std;
using namespace TONY_CL_HOST;

 int64_t getRunningUs(struct timeval tstart, struct timeval tend)
 {
    int64_t s0, e0, s1, e1;
  s0 = tstart.tv_sec;
  s1 = tstart.tv_usec;
  e0 = tend.tv_sec;
  e1 = tend.tv_usec;
  return 1000000 * (e0 - s0) + (e1 - s1);
 }
void tcomp32_s1_cpu(uint32_t *in,uint32_t *out,uint32_t len)
{
    uint32_t i;
    struct timeval ts,te;
   gettimeofday(&ts, NULL);
    for(i=0;i<len;i++)
    {
        out[i]=__builtin_clz(in[i]);
    }
    gettimeofday(&te, NULL);
    cout<<"cpu time="+to_string(getRunningUs(ts,te))+"\r\n";
}
void tcomp32_s1_gpu(uint32_t *in,uint32_t *out,uint32_t len)
{
    CLContainer clc(1,CL_DEVICE_TYPE_DEFAULT,"tcomp32_s1");
    clc.addHostOutPara(HostPara(in,len*sizeof(uint32_t)));
    clc.addHostOutPara(HostPara(out,len*sizeof(uint32_t)));
    struct timeval ts,te;
    gettimeofday(&ts, NULL);
    clc.execute(len,512);
   gettimeofday(&te, NULL);
    cout<<"cl time="+to_string(getRunningUs(ts,te))+"\r\n";
    cout<<"cl_data time="+to_string(clc.tIn+clc.tOut)+"\r\n";
    cout<<"cl_execution time="+to_string(clc.tRun)+"\r\n";
} 
void nestedLoop_cpu(uint32_t *r,uint32_t *s,uint32_t *ru,uint32_t len)
{

    uint32_t i,j;
     struct timeval ts,te;
   gettimeofday(&ts, NULL);
    for(i=0;i<len;i++)
    {
        uint32_t tr=r[i];
        for(j=0;j<len;j++)
        {
            if(s[j]==tr)
            {
                ru[0]++;
            }
        }
    }
     gettimeofday(&te, NULL);
    cout<<"cpu time="+to_string(getRunningUs(ts,te))+"\r\n";
    cout<<"joined "+to_string(ru[0])+"tuples"+"\r\n";
}
size_t nestedLoop_gpu(uint32_t *r,uint32_t *s,uint32_t *ru,uint32_t len)
{

    CLContainer clc(1,CL_DEVICE_TYPE_DEFAULT,"nestedLoop");
    clc.addHostOutPara(HostPara(r,len*sizeof(uint32_t)));
    clc.addHostOutPara(HostPara(s,len*sizeof(uint32_t)));
     clc.addHostOutPara(HostPara(ru,1*sizeof(uint32_t)));
     uint32_t len2=len;
    clc.addHostOutPara(HostPara(&len2,1*sizeof(uint32_t)));
    struct timeval ts,te;
    gettimeofday(&ts, NULL);
    clc.execute(len,512);
   gettimeofday(&te, NULL);
    cout<<"cl time="+to_string(getRunningUs(ts,te))+"\r\n";
    cout<<"cl_data time="+to_string(clc.tIn+clc.tOut)+"\r\n";
    cout<<"cl_execution time="+to_string(clc.tRun)+"\r\n";
    cout<<"joined "+to_string(ru[0])+"tuples"+"\r\n";
    string logFname="gpu_"+to_string(len)+"_tuples.csv";
    FILE *fp=fopen(logFname.data(),"w+");
    fprintf(fp,"item,value\n");
    fprintf(fp,"dataIn,%s\n",to_string(clc.tIn).data());
    fprintf(fp,"run,%s\n",to_string(clc.tRun).data());
    fprintf(fp,"dataOut,%s\n",to_string(clc.tOut).data());
    fclose(fp);
    return clc.tIn;
}