#include "CLContainer.hpp"
using namespace TONY_CL_HOST;
#include <sys/time.h>
#include <ReadMinist.hpp>
#include <TonyFlowLib/MatC20.hpp>
#include <random>
#include <math.h>
#include <unordered_map>
#include <DupicatedHashTable.hpp>
void displayPlatformInfo(cl_platform_id id,
                         cl_platform_info param_name,
                         const char* paramNameAsStr) {
    cl_int error = 0;
    size_t paramSize = 0;
    error = clGetPlatformInfo( id, param_name, 0, NULL, &paramSize );
    char* moreInfo = (char*)alloca( sizeof(char) * paramSize);
    error = clGetPlatformInfo( id, param_name, paramSize, moreInfo, NULL );
    if (error != CL_SUCCESS ) {
        perror("Unable to find any OpenCL platform information");
        return;
    }
    printf("%s: %s\n", paramNameAsStr, moreInfo);
}
 int64_t getRunningUs(struct timeval tstart, struct timeval tend)
 {
    int64_t s0, e0, s1, e1;
  s0 = tstart.tv_sec;
  s1 = tstart.tv_usec;
  e0 = tend.tv_sec;
  e1 = tend.tv_usec;
  return 1000000 * (e0 - s0) + (e1 - s1);
 }
void sum_cl(float *a,float *b,float *c,uint64_t n)
{
  CLContainer clc(1,CL_DEVICE_TYPE_GPU,"vecAdd");
  clc.addHostOutPara(HostPara(a,n*sizeof(float)));
  clc.addHostOutPara(HostPara(b,n*sizeof(float)));
  clc.addHostInPara(HostPara(c,n*sizeof(float)));
  //clc.addBoundaryValue(n);
  clc.execute(n,5);
}
void sum_cpu(float *a,float *b,float *c,uint64_t n)
{ 
   for(size_t i=0;i<n;i++)
   {
      //for(k=0;k<100;k++)
      {c[i] = a[i] + b[i];

      }
          
   }
}
int clccmain (int argc,char *argv[])
{ char *src;
   if(argc<2)
   {
      printf("input the cl file name, without .cl\r\n");
      char sname[256];
      scanf("%s",sname);
      src=sname;
   }
   else
   {
      src=argv[1];
   }
   string ins="";
   string outs="";
   ins+=src;
  
   outs=ins;
   outs+=".bin";
   printf("try to open %s.cl\r\n",ins.data());
  
   CLContainer clc(1,CL_DEVICE_TYPE_GPU,ins.data());
   clc.saveProgram(outs.data());
   return 0;
}
float lossFunc(MatC20 <float> predict,vector<uint32_t>lable)
{ 
   float ru=0;
   size_t N=predict.cols();
   float tn=N;
   for(size_t i=0;i<N;i++)
   {  
      uint32_t idx=lable[i];
      float s=predict[idx][i];
      ru+=-log(s);
     // printf("label=%d,value=%lf\r\n",lable[i],s);
   }
   ru=ru/tn;
   return ru;
}
MatC20 <float> softmax(MatC20 <float> a)
{
  MatC20 w=a;
   for(size_t i=0;i<w.cols();i++)
 {   float t=0.0;
     for(size_t j=0;j<w.rows();j++)
    {  t+=  exp(w[j][i]);
      
    }
    for(size_t j=0;j<w.rows();j++)
    {  w[j][i]=  exp(w[j][i])/t;
      
    }
 }
 return w;
}
int nnmain()
{
  /* vector <vector<float> > a(2);
   a[0]=vector<float>(2);
   a[1]=vector<float>(2);
   a[0][0]=1.0;
   a[1][1]=1.0;
   float *kt= &a[0][0];
   printf("%lf,\r\n",kt[0]);*/
    
  ReadMinist rm("mnist.bin");
  rm.printData(150);
  

  /*MatC20 a(2,2);
  
  a[0][1]=5.0;
  //a=a+1.0;
  cout<<a;
  MatC20 b=(a+7.0);
  cout <<b;
  //a.reset(a+b);
  a=a+7.52;
//MatC20 c=MatC20<float>::dot(a,b);
 cout<<a;*/
  std::random_device rd{};
    std::mt19937 gen{rd()};
 
    // values near the mean are the most likely
    // standard deviation affects the dispersion of generated values from the mean
    std::normal_distribution<> d{0,0.0001};
 MatC20 x=!rm.trainData;
 printf("r=%ld,c=%ld\r\n",x.rows(),x.cols());
 MatC20 w(10,x.rows());
 //MatC20 w(4,4);
 for(size_t i=0;i<w.rows();i++)
 {
    for(size_t j=0;j<w.cols();j++)
    {
       w[i][j]=d(gen);
    }
 }
 size_t times=200;
 
 MatC20 labelExtend(10,x.cols());
 for(size_t i=0;i<x.cols();i++)
 {
    labelExtend[rm.label[i]][i]=1.0;
 }
 //float delta=0.001;
 //MatC20 rowSet(1,10);
 //MatC20 colSet(1,784);
 MatC20 c;
 for(size_t m=0;m<times;m++)
 {
     c=MatC20<float>::dot(w,x);
    // c=c/784;
     c=softmax(c);  
     if(m%10)
     {
        printf("loss=%lf\r\n",lossFunc(c,rm.label));
     }
    for (size_t i = 0; i < 10; i++)
    {
           for (size_t j = 0; j < 784; j++)
            {float t=w[i][j];
            float fix=0.0;
             for(size_t u=0;u<x.cols();u++)
              {
                 fix+=(c[i][u]-labelExtend[i][u])*x[j][u];
              }
              fix=fix;
              /*float rt=rowSet[0][i];
              float st= colSet[0][j];
              float newt=t-0.001*rt*st;*/

               w[i][j]=t-0.001*fix;
            }

    }
    
   
 }
MatC20 testIn=rm.trainData.getChild(150,150,0,783);
testIn=!testIn;
cout<<testIn;
MatC20 expectLable=labelExtend.getChild(0,9,150,150);
cout<<expectLable;
MatC20 testOut=MatC20<float>::dot(w,testIn);
 testOut=softmax(testOut);
  cout<<testOut;
//printf("r=%ld,c=%ld\r\n",c.rows(),c.cols());

// cout<<c;
w.toTextFile("w.txt");
return 0;
}
int main(int argc, char *argv[])
{
   int n=1000000;
   uint32_t clTime,cpuTime;
 // size_t bytes = n*sizeof(float);
   float* h_a,*h_b,*h_c;
   vector <float>va(n);
    vector <float>vb(n);
     vector <float>vc(n);
     h_a=&va[0];
     h_b=&vb[0];
     h_c=&vc[0];
    // Allocate memory for each vector on host
 /* h_a = (float*)malloc(bytes);
    h_b = (float*)malloc(bytes);
    h_c = (float*)malloc(bytes);
 */
    // Initialize vectors on host
    int i;
    for( i = 0; i < n; i++ )
    {
        h_a[i] =1.0;
        h_b[i] = 2.0;
    }
    /*sum_cl(h_a,h_b,h_c,n);
    float ruk=0;
      for( i = 0; i < n; i++ )
    {
       ruk+=h_c[i];
    }
    printf("%lf\r\n",ruk);*/
    CLContainer clc2(1,CL_DEVICE_TYPE_DEFAULT,"vecAdd");
   // clc.saveProgram("vecAdd.bin");
    //CLContainer clc2(1,CL_DEVICE_TYPE_GPU,"vecAdd","vecAdd.bin");
   clc2.addHostOutPara(HostPara(h_a,n*sizeof(float)));
  clc2.addHostOutPara(HostPara(h_b,n*sizeof(float)));
  clc2.addHostInPara(HostPara(h_c,n*sizeof(float)));
  //clc.addBoundaryValue(n);
  struct timeval ts,te;
  float ruk=0;
   gettimeofday(&ts, NULL);
  int localSz;
  if(argc<=1)
  {
     localSz=2;
  }
  else{
     localSz=atoi(argv[1]);
  }
  cout<<"local size="+to_string(localSz)<<endl;
  clc2.execute(n,localSz);
   gettimeofday(&te, NULL);
   clTime=getRunningUs(ts,te);
   //printf("cl=%ld us \r\n",getRunningUs(ts,te));

 //printf("cl_in=%ld,cl_run=%ld,cl_out=%ld\r\n",clc2.tIn,clc2.tRun,clc2.tOut);
    gettimeofday(&ts, NULL);
     ruk=0;
   for( i = 0; i < n; i++ )
    {
       ruk+=h_c[i];
    }
    printf("cl=%lf\r\n",ruk);
   
      for( i = 0; i < n; i++ )
    {
      h_c[i]=0;
      h_a[i] =1.0;
      h_b[i] = 2.0;
    }
   sum_cpu(h_a,h_b,h_c,n);
   gettimeofday(&te, NULL);
   cpuTime=getRunningUs(ts,te);
   //printf("cpu=%ld us \r\n",getRunningUs(ts,te));
   ruk=0;
    for( i = 0; i < n; i++ )
    {
       ruk+=h_c[i];
    }
    printf("cpu=%lf\r\n",ruk);

    cout<<"cl Time="+to_string(clTime)+","+"CPU time="+to_string(cpuTime);
   return 0;
}
