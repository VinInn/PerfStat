#include <random>
#include <iostream>
#include "PerfStat.h"
#include<malloc.h>

struct A {

  A(int ii) : i(ii){}
  
  ~A(){}
  
  int val() const;
  virtual int ival() const=0;
  virtual int ijval() const=0;

  int i;

};

int A::val() const { return i;}

struct B : public A {
 B(int ii) : A(ii){}

  virtual int ival() const override { return i;}
  virtual int ijval() const final { return i;}

};

struct C : public A {
  C(int ii) : A(ii){}

  virtual int ival() const override { return i;}
  virtual int ijval() const final { return i;}

};



int main(int argc, char**) {

 
  PerfStat c11, c12, c13;
  PerfStat c21, c22, c23;
  PerfStat c31, c32, c33;

  constexpr int NN =1024;
  A * a[NN];
  B * b[NN];
  C * c[NN];

  for (int i=0; i!=1024; i++) {
    b[i] = new B(i);
    c[i] = new C(i);
  }
  
  for (int i=0; i!=1024; i+=2) {
    a[i]= new B(i);
    a[i+1]= new C(i);
  }

  constexpr int KK=10000;


  bool err=false;
  int s[KK+3];
  for (int ok=0; ok!=KK+3; ++ok) {
    s[ok]=0;

    c11.start();
    for (int i=0;i!=NN;++i)
      s[ok] += a[i]->val();
    c11.stop();
    c12.start();
    for (int i=0;i!=NN;++i)
      s[ok] += a[i]->ival();
    c12.stop();
    c13.start();
    for (int i=0;i!=NN;++i)
      s[ok] += a[i]->jval();
    c13.stop();

    c21.start();
    for (int i=0;i!=NN;++i)
      s[ok] += b[i]->val();
    c21.stop();
    c22.start();
    for (int i=0;i!=NN;++i)
      s[ok] += b[i]->ival();
    c22.stop();
    c23.start();
    for (int i=0;i!=NN;++i)
      s[ok] += b[i]->jval();
    c23.stop();

    c31.start();
    for (int i=0;i!=NN;++i)
      s[ok] += c[i]->val();
    c31.stop();
    c32.start();
    for (int i=0;i!=NN;++i)
      s[ok] += c[i]->ival();
    c32.stop();
    c33.start();
    for (int i=0;i!=NN;++i)
      s[ok] += c[i]->jval();
    c33.stop();

    if (ok>0 && s[ok] != s[ok-1]) err=true;
    
  }

  if (err) std::cout << "a mess " << std::endl;
  PerfStat::header(std::cout);	
  std::cout << "|a  val  "; c11.print(std::cout);
  std::cout << "|a ival  "; c12.print(std::cout);
  std::cout << "|a jval  "; c13.print(std::cout);
  std::cout << "|b  val  "; c21.print(std::cout);
  std::cout << "|b ival  "; c22.print(std::cout);
  std::cout << "|b jval  "; c23.print(std::cout);
  std::cout << "|c  val  "; c31.print(std::cout);
  std::cout << "|c ival  "; c32.print(std::cout);
  std::cout << "|c jval  "; c33.print(std::cout);

  return err ? -1 : 0;

}
