__kernel void nestedLoop        
  (__global uint* r, __global uint* s,__global uint* ru,__global uint* loopCnt)
{
int id = get_global_id(0);
    uint i,j;
    for(i=0;i<loopCnt[0];i++)
    {
        if(r[i]==s[id])
        {
            ru[0]++;
        }
    }
}