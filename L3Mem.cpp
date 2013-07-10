#include <random>
#include <x86intrin.h>
#include <iostream>
#include "PerfStat.h"


unsigned int taux=0;
inline volatile unsigned long long rdtsc() {
 return __rdtscp(&taux);
}


int main(int argc, char**) {
  std::mt19937 eng;

  std::uniform_real_distribution<float> rgen(0.,1.);

  constexpr int NN = 1024*1024;

  // alignas(128) float r[NN];
 float * r = new float[NN];



  std::cout << sizeof(r) << std::endl;
  PerfStat::header(std::cout);	
  PerfStat c1, c2, c11;
 long long t1=0;
 long long ts=0;

  c1.print(std::cout);
  c1.start();
  c1.stop();
  c1.print(std::cout);
  ts -= PerfStat::seconds();
  t1 -= rdtsc();
  c1.start();
  c1.stop();
  t1 += rdtsc();
  ts +=	PerfStat::seconds();
  std::cout << t1 << std::endl;
  std::cout << ts << std::endl;
  c1.print(std::cout);
  t1 -= rdtsc();
  c1.start();
  c1.stop();
  t1 += rdtsc();
  std::cout << t1 << std::endl;
  c1.print(std::cout);
  c1.print(std::cout,true);

 std::cout << std::endl;
 std::cout << "rgen" << std::endl;

  c11.start();
  for (int i=0;i!=NN;++i)
    r[i]=rgen(eng);
  c11.stop();
  c11.print(std::cout);
  c11.print(std::cout,true);

  c11.reset();

  std::cout << "reset" << std::endl;

  c11.start();
  for (int i=0;i!=NN;++i)
    r[i]=rgen(eng);
  c11.stop();
  c11.print(std::cout);
  c11.print(std::cout,true);


  std::cout << std::endl;
  std::cout << std::endl;

  constexpr int KK=10000;

  t1=0; ts=0;

  bool err=false;
  float s[KK+2];
  for (int ok=0; ok!=KK+2; ++ok) {
    s[ok]=0;
    ts -= PerfStat::seconds();
    c2.start();
    t1 -= rdtsc();
    for (int i=0;i!=NN;++i)
      s[ok]+=r[i];
    t1 += rdtsc();
    c2.stop();
    ts += PerfStat::seconds();
    if (ok>0 && s[ok] != s[ok-1]) err=true;
  
  if ( (ok%1000)==1) {
  std::cout << ok << " " << t1 << " " << t1/ok << std::endl;
  std::cout << ts << " " << double(t1)/double(ts) << " " << ts/ok << std::endl;

  c2.print(std::cout);
  c2.print(std::cout,true);
  if (err) std::cout << "a mess " << std::endl;
  }
  }

  std::cout << "end \n" << std::endl;
  c2.start();
  c2.stop();
  c2.print(std::cout);
  t1 -= rdtsc();
  c2.start();
  c2.stop();
  t1 += rdtsc();
  std::cout << t1 << std::endl;
  c2.print(std::cout);
  t1 -= rdtsc();
  c2.start();
  c2.stop();
  t1 += rdtsc();
  std::cout << t1 << std::endl;
  c2.print(std::cout);


  return 0;

}
