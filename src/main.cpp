#include <tcomp32.hpp>
using namespace std;
int main(int argc,char *argv[])
{
  uint32_t amount=1000;
  if(argc>1)
  {
   amount=atoi(argv[1]);
  }
  uint32_t *in=(uint32_t *)malloc(amount*sizeof(uint32_t));
  uint32_t *inR=(uint32_t *)malloc(amount*sizeof(uint32_t));

  uint32_t *out=(uint32_t *)malloc(amount*sizeof(uint32_t));
  srand(999);
  for(uint32_t i=0;i<amount;i++)
  {
   in[i]=rand();
   if(i%200)
   {
    inR[i]=in[i];
   }
   else{
    inR[i]=rand();
   }
   
  }
  uint32_t joined=0;
   nestedLoop_cpu(inR,in,&joined,amount);
    nestedLoop_gpu(inR,in,&joined,amount);
   free(in);
  free(inR);
   free(out);
   return 0;
}
