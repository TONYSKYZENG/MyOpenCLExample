// OpenCL kernel. Each work item takes care of one element of c
__kernel void vecAdd        
  (__global float* A, __global float* B, __global
float* C)
{
int id = get_global_id(0);

 {C[id] = A[id] + B[id];
//555
 }
}
