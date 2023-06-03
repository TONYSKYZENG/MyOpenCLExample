#pragma once
#ifndef _TCOMP32_HPP_
#define _TCOMP32_HPP_
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
void tcomp32_s1_cpu(uint32_t *in,uint32_t *out,uint32_t len);
void tcomp32_s1_gpu(uint32_t *in,uint32_t *out,uint32_t len);
void nestedLoop_cpu(uint32_t *r,uint32_t *s,uint32_t *ru,uint32_t len);
size_t nestedLoop_gpu(uint32_t *r,uint32_t *s,uint32_t *ru,uint32_t len);

#endif