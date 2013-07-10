#include "PerfStat.h"


/*  self consistency test 
 *  (aka Unit test)
 */



#include<iostream>


int main() {
  int ret = 0;

  std::cout << "we are " << (PerfStat::isINTEL() ? "on" : "not on") << " an Intel Machine" << std::endl; 





  return ret;

}
