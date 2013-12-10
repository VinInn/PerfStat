#include "PerfStat.h"


/*  self consistency test 
 *  (aka Unit test)
 *  does not validate the counter content inself;
 */



#include<iostream>


#define test_verify(expr)					\
  if (!(expr)) { std::cout << #expr << " failed" << std::endl;}




int main(int argc, char **) {
  int ret = 0;

  double resolution = 0.01;
  auto ok = [=](double x, double y) { return std::abs((x-y)/y)<resolution;};
 

  std::cout << "we are " << (PerfStat::isINTEL() ? "on" : "not on") << " an INTEL Machine. Model ";
  printf("%x",PerfStat::modelNumber()); std::cout<< std::endl; 
  std::cout << "|test   "; perf.header(std::cout);
  std::cout << "|test   "; perf.header(std::cout,true);

  bool debug = argc>1;

  PerfStat ps; 
  test_verify(0==ps.calls());
  test_verify(0==ps.callsTot());
  test_verify(0==ps.read()); ps.calib();
  test_verify(0==ps.calls());
  test_verify(0==ps.callsTot());
  test_verify(0==ps.cyclesRaw());
  test_verify(0==ps.instructionsRaw());
  test_verify(0==ps.taskTimeRaw());
  test_verify(0==ps.realTimeRaw());

  ps.start();ps.stop();
  ps.start();ps.stop();
  test_verify(2==ps.calls());
  test_verify(2==ps.callsTot());
  test_verify(0==ps.read()); ps.calib();
  if(debug) ps.print(std::cout,true,true);
 

  {
    PerfStat perf;
    double s =0;
    for (int k=0; k!=100; ++k) {
      perf.start();    
      for (int i=1; i!=1000001; ++i) s+= std::log(i+1);
      perf.stop();
      
    }
    ret &= (s!=0);
    test_verify(100==perf.calls());
    test_verify(100==perf.callsTot());
    perf.read(); perf.calib();
    test_verify(ok(perf.cyclesRaw(),perf.cyclesTot()));
    test_verify(ok(perf.cyclesRaw()/double(perf.calls()),perf.cycles()));
    // test_verify(perf.verify(0.01));
    std::cout <<"|default  "; perf.summary(std::cout); //std::cout << std::endl;
    std::cout <<"|default  "; perf.summary(std::cout,true); //std::cout << std::endl;
    if(debug) perf.print(std::cout,true,true);
  
    PerfStat perf1(true);
    s =0;
    for (int k=0; k!=100; ++k) {
      perf1.start();    
      for (int i=1; i!=1000001; ++i) s+= std::log(i+1);
      perf1.stop();
      
    }
    ret &= (s!=0);
    test_verify(100==perf1.calls());
    test_verify(100*PerfStat::ngroups()==perf1.callsTot());
    perf1.read(); perf1.calib();
    // test_verify(perf.verify(0.01));
    std::cout <<"|multi   "; perf1.summary(std::cout,true); //std::cout << std::endl;
    if(debug) perf1.print(std::cout,true,true);
  }
  {

    PerfStat perf1;
    PerfStat perf2;
    double s1 =0;
    double s2 =0;
    for (int k=0; k!=100; ++k) {
      perf1.start();    
      for (int i=1; i!=1000001; ++i) s1+= std::log(i+1);
      perf1.stop();
      perf2.start();    
      for (int i=1; i!=1000001; ++i) s2+= std::log2(i+1);
      perf2.stop();
      
    }
    ret &= (s1!=0);ret &= (s2!=0);
    test_verify(100==perf1.calls());
    test_verify(100==perf1.callsTot());
    test_verify(100==perf2.calls());
    test_verify(100==perf2.callsTot());
    perf1.read(); perf1.calib();
    perf2.read(); perf2.calib();
    // test_verify(perf.verify(0.01));
    std::cout <<"|one    ";perf1.summary(std::cout,true); //std::cout << std::endl;
    std::cout <<"|two    ";perf2.summary(std::cout,true);// std::cout << std::endl;


  }
  {

    PerfStat perf1;
    PerfStat perf2;
    double s1 =0;
    double s2 =0;
    for (int k=0; k!=100; ++k) {
      perf1.start(0);    
      for (int i=1; i!=1000001; ++i) s1+= std::log(i+1);
      perf1.stop();
      perf2.start(1);    
      for (int i=1; i!=1000001; ++i) s2+= std::log2(i+1);
      perf2.stop();
      
    }
    ret &= (s1!=0);ret &= (s2!=0);
    test_verify(100==perf1.calls());
    test_verify(100==perf1.callsTot());
    test_verify(100==perf2.calls());
    test_verify(100==perf2.callsTot());
    perf1.read(); perf1.calib();
    perf2.read(); perf2.calib();
    // test_verify(perf.verify(0.01));
    std::cout <<"|0      ";perf1.summary(std::cout,true); //std::cout << std::endl;
    std::cout <<"|1      ";perf2.summary(std::cout,true);// std::cout << std::endl;
    if(debug) perf1.print(std::cout,true,true);
    if(debug) perf2.print(std::cout,true,true);
  }

  {

    PerfStat perf1;
    double s1 =0;
    for (int k=0; k!=100; ++k) {
      perf1.start(0);    
      for (int i=1; i!=1000001; ++i) s1+= std::log(i+1);
      perf1.stop();
      perf1.start(k&1);    
      for (int i=1; i!=1000001; ++i) s1+= std::log2(i+1);
      perf1.stop();
      
    }
    test_verify(100*PerfStat::ngroups()==perf1.calls());
    test_verify(100*PerfStat::ngroups()==perf1.callsTot());
    ret &= (s1!=0);
    perf1.read(); perf1.calib();
    // test_verify(perf.verify(0.01));
    std::cout <<"|0/1    ";perf1.summary(std::cout,true);// std::cout << std::endl;
    if(debug) perf1.print(std::cout,true,true);

  }


  {

    PerfStat perf1;
    double s1 =0;
    double s2 =0;
    for (int k=0; k!=100; ++k) {
      perf1.start();    
      for (int i=1; i!=1000001; ++i) s1+= std::log(i+1);
      perf1.stop();
    }
    perf1.read(); perf1.calib();
    std::cout <<"|      ";perf1.summary(std::cout); //std::cout << std::endl;
    perf1.reset();
    for (int k=0; k!=100; ++k) {
      perf1.start();    
      for (int i=1; i!=1000001; ++i) s2+= std::log2(i+1);
      perf1.stop();
    }
    test_verify(100==perf1.calls());
    test_verify(100==perf1.callsTot());
    ret &= (s1!=0);ret &= (s2!=0);
    perf1.read(); perf1.calib();
    // test_verify(perf.verify(0.01));
    std::cout <<"|reset ";perf1.summary(std::cout,true);// std::cout << std::endl;


  }


  {
    // sharing
    PerfStat perf;
    PerfStat perf1(perf.fd());
    PerfStat perf2(perf.fd());
    double s1 =0;
    double s2 =0;
    for (int k=0; k!=100; ++k) {
      perf1.startDelta();    
      for (int i=1; i!=1000001; ++i) s1+= std::log(i+1);
      perf1.stopDelta();
      perf2.startDelta();    
      for (int i=1; i!=1000001; ++i) s2+= std::log2(i+1);
      perf2.stopDelta();
      perf.start();perf.stop();  
    }
    ret &= (s1!=0);ret &= (s2!=0);
    test_verify(100==perf.calls());
    test_verify(100==perf.callsTot());
    test_verify(100==perf1.calls());
    test_verify(100==perf1.callsTot());
    test_verify(100==perf2.calls());
    test_verify(100==perf2.callsTot());
//    perf1.calib();
//    perf2.calib();
    // test_verify(perf.verify(0.01));
    perf.read(); perf.calib();
    std::cout <<"|total  "; perf.summary(std::cout,true); //std::cout << std::endl;
    std::cout <<"|one sh ";perf1.summary(std::cout,true); //std::cout << std::endl;
    std::cout <<"|two sh ";perf2.summary(std::cout,true); //std::cout << std::endl;
    if(debug) perf.print(std::cout,true,true);

  }

  {
    // sharing multiplex
    PerfStat perf(true);
    PerfStat perf1(perf.fd());
    PerfStat perf2(perf.fd());
    double s1 =0;
    double s2 =0;
    for (int k=0; k!=100; ++k) {
      perf1.startDelta();    
      for (int i=1; i!=1000001; ++i) s1+= std::log(i+1);
      perf1.stopDelta();
      perf2.startDelta();    
      for (int i=1; i!=1000001; ++i) s2+= std::log2(i+1);
      perf2.stopDelta();
      perf.start();perf.stop();  
    }
    ret &= (s1!=0);ret &= (s2!=0);
    test_verify(100==perf.calls());
    test_verify(100*PerfStat::ngroups()==perf.callsTot());
    test_verify(100==perf1.calls());
    test_verify(100*PerfStat::ngroups()==perf1.callsTot());
    test_verify(100==perf2.calls());
    test_verify(100*PerfStat::ngroups()==perf2.callsTot());
//    perf1.calib();
//    perf2.calib();
    // test_verify(perf.verify(0.01));
    perf.read(); perf.calib();
    std::cout <<"|totmp  "; perf.summary(std::cout,true); //std::cout << std::endl;
    std::cout <<"|one mp ";perf1.summary(std::cout,true); //std::cout << std::endl;
    std::cout <<"|two mp ";perf2.summary(std::cout,true); //std::cout << std::endl;
    if(debug) perf.print(std::cout,true,true);

  }



  // ps.print(std::cout);

  // ps.print(std::cout,true);


  return ret;

}
