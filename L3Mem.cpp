#include <random>
#include <iostream>
#include "PerfStat.h"
#include<malloc.h>


int main(int argc, char**) {

  std::mt19937 eng;

  std::uniform_real_distribution<float> rgen(0.,1.);

  constexpr int NN = 1024*1024;

  // alignas(128) float r[NN];
  float * r = (float*)__builtin_assume_aligned(::memalign(32,NN*sizeof(float)),32);


  std::cout << sizeof(r) << " " << alignof(r) << std::endl;
  PerfStat::header(std::cout);	
  PerfStat c12, c2, c11, c22;


 std::cout << std::endl;
 

  c11.startAll();
  for (int i=0;i!=NN;++i)
    r[i]=rgen(eng);
  c11.stopAll();
  std::cout << "|rgen  " << std::endl;
  c11.print(std::cout);

  c12.startAll();
  for (int i=0;i!=NN;++i)
    r[i]=rgen(eng);
  c12.stopAll();
  std::cout << "|rgen  " << std::endl;
  c12.print(std::cout);
 


  std::cout << std::endl;
  std::cout << std::endl;

  constexpr int KK=10000;


  bool err=false;
  float s[KK+3];
  for (int ok=0; ok!=KK+3; ++ok) {
    s[ok]=0;
    c2.start();
    for (int i=0;i!=NN;++i)
      s[ok]+=r[i];
    c2.stop();
    if (ok>0 && s[ok] != s[ok-1]) err=true;
    
    if ( (ok%1000)==2) {
      std::cout << "|sum " << ok << "  ";  c2.print(std::cout);
    }
  }
  
  if (err) std::cout << "a mess " << std::endl;
 
  std::cout << "end \n" << std::endl;
  
  c2.print(std::cout);

  ::free(r);

  return 0;

}
