#include <ReadMinist.hpp>
using namespace std;
ReadMinist::ReadMinist(string fileName) {
  FILE *fp = fopen(fileName.data(), "rb");
  if (!fp) {
    return;
  }
  uint32_t n;
  fread(&n, sizeof(uint32_t), 1, fp);
  printf("read %d samples\r\n", n);
   //MatC20 a(n,784);
  //trainData=a;
  label=vector<uint32_t>(n);
    trainData.reset(n,784);
  
   
  uint32_t *labelP = &label[0];
  
  fread(labelP, sizeof(uint32_t) * n, 1, fp);
  for (uint32_t i = 0; i < n; i++) {
    vector<float> a(784);
    float *ff = &a[0];
    fread(ff, sizeof(float) * 784, 1, fp);
    trainData[i] = a;
  }
 
  fclose(fp);
}
void ReadMinist::printData(size_t idx) {
  if (idx > trainData.rows()) {
    return;
  }
  printf("data:\r\n");
  float *ff = &trainData[idx][0];
  for (int i = 0; i < 28; i++) {
    for (int j = 0; j < 28; j++) {
      if (ff[i * 28 + j] != 0) {
        printf("* ");
      } else {
        printf("  ");
      }

    }
    printf("\r\n");
  }
  printf("label=%d\r\n", label[idx]);
}