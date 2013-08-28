#include "PerfStat.h"
#include<cmath>
#include<iostream>
#include<omp.h"

template<typename T>
// typedef float T;
inline T polyHorner(T y) {
  return  T(0x2.p0) + y * (T(0x2.p0) + y * (T(0x1.p0) + y * (T(0x5.55523p-4) + y * (T(0x1.5554dcp-4) + y * (T(0x4.48f41p-8) + y * T(0xb.6ad4p-12)))))) ;
}




int main() {

  std::cout << "number of threads " << OpenMP::GetMaxNumThreads() << std::endl;



 {
    PerfStat perf;
    // will vectorize 256 only with avx2 (because of the int)
    float s =0;
    for (int k=0; k!=100; ++k) {
      perf.start();
#pragma omp parallel reduction (+ : s)
      {
	float c = 1.f/1000000.f;
	float v=0;
	for (int i=1; i<10000001; ++i) s+= polyHorner((++v)*c);
      } // end omp parallel
      perf.stop();
    }
    ret &= s!=0;

   //std::cout << " " << s << std::endl;

   std::cout << "|Horner f  ";
   perf.print(std::cout,true);
}

  }	  

  return ret;

}
