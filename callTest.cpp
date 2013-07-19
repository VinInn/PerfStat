#include <random>
#include <iostream>
#include "PerfStat.h"
#include<malloc.h>
#include<sstream>

struct A {
  A(){}
  A(int ii) : i(ii){}
  
  virtual ~A(){}
  
  int val() const;
  virtual int ival() const=0;
  virtual int jval() const=0;
  virtual int kval() const=0;

  int i;

};


struct B : public A {
  B(){}
 B(int ii) : A(ii){}

  virtual int ival() const override;
  virtual int jval() const final { return i;}
  virtual int kval() const final { return i;}

};

struct C : public A {
  C(){}
  C(int ii) : A(ii){}

  virtual int ival() const override;
  virtual int jval() const final { return i;}
  virtual int kval() const override { return i;}

};

#ifndef WITHLIB 
int A::val() const { return i;}
int B::ival() const { return i;}
int C::ival() const { return i;}

void modify(A**){}
void modify(C**){}
void modify(C*){}

void hello() { std::cout << "from main" << std::endl;}
#else
void modify(A**);
void modify(C**);
void modify(C*);

void hello();

#endif

int main(int argc, char** argv) {

  hello();

  bool nostring = argc>1;
  bool q1 = argc>2;
  bool q2 = argc>4;
  char * ww = argv[3];


  PerfStat c11, c12, c13;
  PerfStat c21, c22, c23;
  PerfStat c31, c32, c33;
  PerfStat c41, c42, c43;
  PerfStat if1;
  PerfStat mn, md, ss1, ss2;

  constexpr int NN =1024*4;
  A * a[NN];
  A * b[NN];
  C * c[NN];
  C  d[NN];

  PerfStat m1; m1.startAll();
  for (int i=0; i!=NN; i++) {
    b[i] = new B(i);
    c[i] = new C(i);
    d[i] = C(i);
  }
  m1.stopAll();
  std::cout <<"|new  "; m1.print(std::cout);  

   m1.startAll(); 
  for (int i=0; i!=NN; i+=2) {
    a[i]= new B(i);
    a[i+1]= new C(i);
  }
  m1.stopAll();
  std::cout <<"|new  ";	m1.print(std::cout);


  if (q1) {
    b[int(ww[3])] = a[int(ww[4])];

  }

  constexpr int KK=100000;


  bool err=false;
  int s[100];
  for (int ok=0; ok!=KK; ++ok) {
    auto k = ok%100; 
    s[k]=0;

  if (!nostring) {
    md.start();
    for (int i=0; i!=NN; i+=2) {
      delete a[i];
      delete a[i+1];
    }
    md.stop();
    
    mn.start();
    for (int i=0; i!=NN; i+=2) {
      a[i]= new B(i);
      a[i+1]= new C(i);
    }
    mn.stop();
  
    ss1.start();
    std::string st1,st2;
    bool sb=true;
    for (int i=0; i!=NN; i+=2) {
      char q = 50 - ok%10 + i%20;
      st1 += q;
      st2 += q;
      sb &= st1==st2;
    }
    if (sb) s[k]+=st1.size();
    ss1.stop();
    ss2.start();
    std::stringstream sss;
    for (int i=0; i!=NN; i+=2) {
      sss << i;
    }
    if (sss.str()==st1) s[k]+=st1.size();
    ss2.stop();  
  }

    modify(a);modify(b); modify(c);modify(d);
    if (q2) {
      b[int(ww[ok%32])] = a[int(ww[ok%64])];
      a[int(ww[ok%32])] = c[int(ww[ok%64])];
      d[int(ww[ok%32])] = *c[int(ww[ok%64])];
    }

    c11.start();
    for (int i=0;i!=NN;++i)
      s[k] += a[i]->val();
    c11.stop();
    c12.start();
    for (int i=0;i!=NN;++i)
      s[k] += a[i]->ival();
    c12.stop();
    c13.start();
    for (int i=0;i!=NN;++i)
      s[k] += a[i]->jval();
    c13.stop();

    c21.start();
    for (int i=0;i!=NN;++i)
      s[k] += b[i]->val();
    c21.stop();
    c22.start();
    for (int i=0;i!=NN;++i)
      s[k] += b[i]->ival();
    c22.stop();
    c23.start();
    for (int i=0;i!=NN;++i)
      s[k] += b[i]->jval();
    c23.stop();

    c31.start();
    for (int i=0;i!=NN;++i)
      s[k] += c[i]->val();
    c31.stop();
    c32.start();
    for (int i=0;i!=NN;++i)
      s[k] += c[i]->ival();
    c32.stop();
    c33.start();
    for (int i=0;i!=NN;++i)
      s[k] += c[i]->jval();
    c33.stop();

    c41.start();
    for (int i=0;i!=NN;++i)
      s[k] += d[i].val();
    c41.stop();
    c42.start();
    for (int i=0;i!=NN;++i)
      s[k] += d[i].ival();
    c42.stop();
    c43.start();
    for (int i=0;i!=NN;++i)
      s[k] += d[i].jval();
    c43.stop();

    if1.start();
    for (int i=0;i!=NN;++i) {
      if (0==(a[i]->ival()&1)) b[i]->i = c[i]->ival(); else b[i]->i = d[i].jval();
      if (b[i]->jval()&1) s[k] += d[c[i]->kval()].jval();
    }
    if1.stop();

    modify(a);modify(b); modify(c);modify(d);
    if (k>0 && s[k] != s[k-1]) err=true;

  }

  if (err) std::cout << "a mess " << std::endl;
  std::cout << "|kernel  "; PerfStat::header(std::cout,true);	
  std::cout << "|new     "; mn.print(std::cout);
  std::cout << "|delete  "; md.print(std::cout);
  std::cout << "|string  "; ss1.print(std::cout);
  std::cout << "|stream  "; ss2.print(std::cout);
  std::cout << "|a  val  "; c11.print(std::cout);
  std::cout << "|a ival  "; c12.print(std::cout);
  std::cout << "|a jval  "; c13.print(std::cout);
  std::cout << "|b  val  "; c21.print(std::cout);
  std::cout << "|b ival  "; c22.print(std::cout);
  std::cout << "|b jval  "; c23.print(std::cout);
  std::cout << "|c  val  "; c31.print(std::cout);
  std::cout << "|c ival  "; c32.print(std::cout);
  std::cout << "|c jval  "; c33.print(std::cout);
  std::cout << "|d  val  "; c41.print(std::cout);
  std::cout << "|d ival  "; c42.print(std::cout);
  std::cout << "|d jval  "; c43.print(std::cout);
  std::cout << "|if      "; if1.print(std::cout);

  return err ? -1 : 0;

}
