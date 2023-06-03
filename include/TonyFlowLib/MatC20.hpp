#pragma once
#ifndef _MATC20_HPP_
#define _MATC20_HPP_
#include <CLContainer.hpp>
#include <vector>
#include <stdint.h>
#include <iostream>
#include <memory>
using namespace std;
namespace TFL {
template<class dataType=float>
class MatC20 {
 private:
  /* data */

 public:
  static char isDivide(char *str) {
    if (*str == ' ' || *str == ',' || *str == ';' || *str == ';') {
      return 1;
    }
    return 0;
  }
  vector<vector<dataType> > myData;
  string clPrefix = "float";
  bool useCL = false;
  std::shared_ptr<dataType *> pa;
  std::shared_ptr<dataType *> pb;
  std::shared_ptr<dataType *> pc;
  MatC20()
  {
     myData = vector<vector<dataType> >(1);
     myData[0]= vector<dataType>(1);
  }
  MatC20(size_t rows, size_t cols) {
    myData = vector<vector<dataType> >(rows);
    for (size_t i = 0; i < rows; i++) {
      myData[i] = vector<dataType>(cols);
    }
  }
  void clear()
  {
    size_t r=rows();
    for (size_t i = 0; i < r; i++) {
       myData[i].clear();
    }
    myData.clear();
  }
  void reset(size_t rows, size_t cols)
  {  if(rows!=this->rows()||cols!=this->cols())
      {
        clear();
      }
       myData = vector<vector<dataType> >(rows);
    for (size_t i = 0; i < rows; i++) {
      myData[i] = vector<dataType>(cols);
    }
  }
  void reset(MatC20 value)
  {     size_t rows;
       rows=value.rows();
      if(rows!=this->rows())
      {
        clear();
        myData = vector<vector<dataType> >(rows);
      }
      
    for (size_t i = 0; i < rows; i++) {
      myData[i] = value.myData[i];
    }
  }
  //
  size_t rows() {
    return myData.size();
  }
  size_t cols() {
    return myData[0].size();
  }
  size_t size()
  {
      return myData.size()*myData[0].size();
  }
  vector<dataType> &operator[](size_t i) {
    return myData[i];
  }
  dataType &operator()(size_t i) {
    size_t r = i / rows();
    size_t c = i % rows();
    return myData[r][c];
  }
  // get the child mat
  MatC20 getChild(size_t rs,size_t re,size_t cs,size_t ce) {
      MatC20 ru(re-rs+1,ce-cs+1);
      size_t i;
      size_t j;
      for(i=rs;i<=re;i++)
      {
        for(j=cs;j<=ce;j++)
        {
            ru[i-rs][j-cs]=myData[i][j];
        }
      }
      return ru;
  }
  //rows from rs to re, cols from cs to ce
  dataType sum(size_t rs,size_t re,size_t cs,size_t ce)
  { dataType ru;
     size_t i;
      size_t j;
      for(i=rs;i<=re;i++)
      {
        for(j=cs;j<=ce;j++)
        {
            ru+=myData[i][j];
        }
      }
      return ru;
  }
  //void transFunction()
  friend ostream &operator<<(ostream &output,
                             MatC20 &mat) {
    // output << "row : " << mat.rows() << " col : " << mat.cols();
    for (size_t i = 0; i < mat.rows(); i++) {
      for (size_t j = 0; j < mat.cols(); j++) {
        output << mat[i][j] << ",";
      }
      output << "\n";
    }
    output << "\n";
    return output;
  }
  //arith + - * /
  friend MatC20  operator+(MatC20 &a, MatC20 &b) {
    MatC20 c(a.rows(), a.cols());
    for (size_t i = 0; i < a.rows(); i++) {
      for (size_t j = 0; j < a.cols(); j++) {
        c[i][j] = a[i][j] + b[i][j];
      }
    }
    return c;
  }
   friend MatC20 operator+(MatC20 &a, dataType b) {
    MatC20 c(a.rows(), a.cols());
    for (size_t i = 0; i < a.rows(); i++) {
      for (size_t j = 0; j < a.cols(); j++) {
        c[i][j] = a[i][j] +b;
      }
    }
    return c;
  }
  friend MatC20 operator-(MatC20 &a, MatC20 &b) {
    MatC20 c(a.rows(), a.cols());
    for (size_t i = 0; i < a.rows(); i++) {
      for (size_t j = 0; j < a.cols(); j++) {
        c[i][j] = a[i][j] - b[i][j];
      }
    }
    return c;
  }
   friend MatC20 operator-(MatC20 &a, dataType b) {
    MatC20 c(a.rows(), a.cols());
    for (size_t i = 0; i < a.rows(); i++) {
      for (size_t j = 0; j < a.cols(); j++) {
        c[i][j] = a[i][j] -b;
      }
    }
    return c;
  }
  friend MatC20 operator*(MatC20 &a, MatC20 &b) {
    MatC20 c(a.rows(), a.cols());
    for (size_t i = 0; i < a.rows(); i++) {
      for (size_t j = 0; j < a.cols(); j++) {
        c[i][j] = a[i][j] * b[i][j];
      }
    }
    return c;
  }
   friend MatC20 operator*(MatC20 &a,dataType b) {
    MatC20 c(a.rows(), a.cols());
    for (size_t i = 0; i < a.rows(); i++) {
      for (size_t j = 0; j < a.cols(); j++) {
        c[i][j] = a[i][j] * b;
      }
    }
    return c;
  }
  friend MatC20 operator*(dataType b,MatC20 &a) {
    MatC20 c(a.rows(), a.cols());
    for (size_t i = 0; i < a.rows(); i++) {
      for (size_t j = 0; j < a.cols(); j++) {
        c[i][j] = a[i][j] * b;
      }
    }
    return c;
  }
  friend MatC20 operator/(MatC20 &a, MatC20 &b) {
    MatC20 c(a.rows(), a.cols());
    for (size_t i = 0; i < a.rows(); i++) {
      for (size_t j = 0; j < a.cols(); j++) {
        c[i][j] = a[i][j] / b[i][j];
      }
    }
    return c;
  }
   friend MatC20 operator/(MatC20 &a,dataType b) {
    MatC20 c(a.rows(), a.cols());
    for (size_t i = 0; i < a.rows(); i++) {
      for (size_t j = 0; j < a.cols(); j++) {
        c[i][j] = a[i][j] /b;
      }
    }
    return c;
  }
  //dot %
  
  friend MatC20 & operator%(MatC20 &m, MatC20 &n) {
    MatC20 ru(m.rows(), n.cols());
    size_t i, j, k;
    for (i = 0; i < ru.rows(); i++) {

      for (j = 0; j < ru.cols(); j++) {
        for (k = 0; k < m.cols(); k++) {
          ru[i][j] += m[i][k] * n[k][j];
        }
      }
      //	SYS_OUT("\n\t");
    }
    return ru;
  }
  //trans
  MatC20 operator! ()  
      {
         MatC20 ru(cols(),rows());
         for (size_t i = 0; i <rows(); i++) {
      for (size_t j = 0; j <cols(); j++) {
        ru[j][i] = myData[i][j];
      }
    }
     return ru;
      }

  ~MatC20() {

  }
  static MatC20 dot(MatC20 &m, MatC20 &n)
   {
      MatC20 ru(m.rows(), n.cols());
    size_t i, j, k;
    for (i = 0; i < ru.rows(); i++) {

      for (j = 0; j < ru.cols(); j++) {
        for (k = 0; k < m.cols(); k++) {
          ru[i][j] += m[i][k] * n[k][j];
        }
      }
      //	SYS_OUT("\n\t");
    }
    return ru;
   }
   //file operation
   int toTextFile(char *fname)
   {
     FILE *fp;
	  size_t i,j;
    size_t row=rows();
    size_t col=cols();
    if((fp=fopen((char*)fname,"w"))==NULL)
	{
		return 0;
	}  
	fprintf(fp,"r=%ld,c=%ld;\n",rows(),cols());
	  for(i=0;i<row;i++)
	  {
        for(j=0;j<col;j++)
           { fprintf(fp,"%lf",myData[i][j]);
		   	if(j!=col-1)
			   {
				   	 fprintf(fp," ");
			   }
		   }
		   if(i!=row-1)
			   {
				   	 fprintf(fp,"\n");
			   }
	  }
	  fclose(fp);
	  return 1;
   }
   int fromTextFile(char *fname)
{
	 FILE *fp;
	 size_t i,j;
	 size_t r,c;
   double t;
	   if((fp=fopen((char*)fname,"r"))==NULL)
	{
		return 0;
	} 
	fscanf(fp,"r=%ld,c=%ld;\n",&r,&c);
//	SYS_OUT("read r=%d,c=%d \r\n",r,c);
  this->reset(r,c);

	 for(i=0;i<r;i++)
	  {
        for(j=0;j<c;j++)
           { fscanf(fp,"%lf",&t);  //
		   	 myData[i][j]=t;
		   }
		   
	  }
		 fclose(fp);
	  return 1;
}
};
 
}
#endif
