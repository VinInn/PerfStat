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

int A::val() const { return i;}
int B::ival() const { return i;}
int C::ival() const { return i;}


void modify(A**){}
void modify(C**){}
void modify(C*){}

#include<iostream>
void hello() { std::cout << "from library" << std::endl;}

namespace {
  struct Q{
    Q() {
       std::cout << "library loaded" << std::endl;
    }
  };

}
