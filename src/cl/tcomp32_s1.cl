// OpenCL kernel. Each work item takes care of one element of c
__kernel void tcomp32_s1        
  (__global uint* A, __global uint* B)
{
int id = get_global_id(0);

 {B[id] = __builtin_clz(A[id]);
 }
}
