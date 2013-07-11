#include "PerfStat.h"


/*  self consistency test 
 *  (aka Unit test)
 *  does not validate the counter content inself;
 */



#include<iostream>


#define test_verify(expr)					\
  if (!(expr)) { std::cout << #expr << " failed" << std::endl;}

int main() {
  int ret = 0;

  std::cout << "we are " << (PerfStat::isINTEL() ? "on" : "not on") << " an Intel Machine" << std::endl; 



  PerfStat ps; 
  test_verify(0==ps.calls());
  test_verify(0==ps.callsTot());
  ps.read(); ps.calib();
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
  test_verify(ps.verify(0.01));


  ps.print(std::cout);

  ps.print(std::cout,true);


  return ret;

}
