#include "PerfStat.h"
#include<cmath>
#include<iostream>

template<typename T>
// typedef float T;
inline T polyHorner(T y) {
  return  T(0x2.p0) + y * (T(0x2.p0) + y * (T(0x1.p0) + y * (T(0x5.55523p-4) + y * (T(0x1.5554dcp-4) + y * (T(0x4.48f41p-8) + y * T(0xb.6ad4p-12)))))) ;
}

template<typename T>
inline T polyEstrin(T y) {
  T p56 = T(0x4.48f41p-8) + y * T(0xb.6ad4p-12);
  T p34 = T(0x5.55523p-4) + y * T(0x1.5554dcp-4);
  T y2 = y*y;
  T p12 = T(0x2.p0) + y; // By chance we save one operation here! Funny.
  T p36 = p34 + y2*p56;
  T p16 = p12 + y2*p36;
  T p =  T(0x2.p0) + y*p16;
  return p;
}


int main0() {

  std::cout << "T(i)" << std::endl;

  bool ret=true;
  {
    
    
    PerfStat perf;
    std::cout << "we are " << (PerfStat::isINTEL() ? "on" : "not on") << " an INTEL Machine" << std::endl; 
    PerfStat::header(std::cout,true);
    
    double s =0;
    for (int k=0; k!=100; ++k) {
      perf.start();    
      
      for (int i=1; i!=1000001; ++i) s+= std::log(i+1);
      
      perf.stop();
      
    } 
    ret &= s!=0;

   //std::cout << " " << s << std::endl;
    
    std::cout << "|log  ";
    perf.print(std::cout);

  }

  {
    PerfStat perf;
    
    
    double s =0;
    for (int k=0; k!=100; ++k) {
      perf.start();
      for (int i=1; i!=1000001; ++i) s+= std::log2(i+1);
      perf.stop();
      
    }
    
    ret &= s!=0;

   //std::cout << " " << s << std::endl;
    
    std::cout << "|log2  ";
    perf.print(std::cout);
    
  }
  

  {
    PerfStat perf;
    // will vectorize 256 only with avx2 (because of the int)
    float s =0;
    for (int k=0; k!=100; ++k) {
      perf.start();
      float c = 1.f/1000000.f;
      for (int i=1; i<10000001; ++i) s+= polyHorner((float(i)+1.f)*c);
      perf.stop();
    }
    ret &= s!=0;

   //std::cout << " " << s << std::endl;

   std::cout << "|Horner f  ";
   perf.print(std::cout,true);
}

  {
    PerfStat perf;
    // will vectorize 256 only with avx2 (because of the int)
    float s =0;
    for (int k=0; k!=100; ++k) {
      perf.start();
      float c = 1.f/1000000.f;
      for (int i=1; i<10000001; ++i) s+= polyEstrin((float(i)+1.f)*c);
      perf.stop();     
    }
    ret &= s!=0;

   //std::cout << " " << s << std::endl;

    
    std::cout << "|Estrin f  ";
    perf.print(std::cout,true);
  }


  {
    PerfStat perf;
    // double precision and int. it wil vectorize in mix 128 for int and 256 for double
    double s =0;
    for (int k=0; k!=100; ++k) {
      perf.start();
      double c = 1./1000000.;
      for (int i=1; i<10000001; ++i) s+= polyHorner((i+1)*c);
      perf.stop();                                                        
    }
    ret &= s!=0;

   //std::cout << " " << s << std::endl;

    
    std::cout << "|Horner d  ";
    perf.print(std::cout,true);
  }


  {
    PerfStat perf;
    // double precision and int. it wil vectorize in mix 128 for int and 256 for double
    double s =0;
    for (int k=0; k!=100; ++k) {
      perf.start();
      double c = 1./1000000.;
      for (int i=1; i<10000001; ++i) s+= polyEstrin((i+1)*c);
      perf.stop();      
    }
    ret &= s!=0;

   //std::cout << " " << s << std::endl;

    
    std::cout << "|Estrin d  ";
    perf.print(std::cout,true);
  }

  {
    PerfStat perf;
    // double precision and int. it wil vectorize in mix 128 for int and 256 for double
    double s =0;
    for (int k=0; k!=100; ++k) {
      perf.start();
      double c = 1./1000000.;
      for (int i=1; i<10000001; ++i) s+= polyEstrin((i+1.)*c);
      perf.stop();      
    }
    ret &= s!=0;

   //std::cout << " " << s << std::endl;

    
    std::cout << "|Estrin dd  ";
    perf.print(std::cout,true);
  }


  {
    PerfStat perf;
    // will vectorize 256 only with avx2 (because of the int)
    float s =0;
    for (int k=0; k!=100; ++k) {
      perf.start();
      for (int i=1; i<10000001; ++i) s+= 1.f/(float(i)+1.f);
      perf.stop();
    }
    ret &= s!=0;

   //std::cout << " " << s << std::endl;
    
   std::cout << "|inv f  ";
   perf.print(std::cout,true);
}


{
  PerfStat perf;
   // double precision and int. it wil vectorize in mix 128 for int and 256 for double          
   double s =0;
    for (int k=0; k!=100; ++k) {
     perf.start();
     for (int i=1; i<10000001; ++i) s+= 1./(i+1.);
     perf.stop();
     }

    ret &= s!=0;

   //std::cout << " " << s << std::endl;


   std::cout << "|inv d  ";
   perf.print(std::cout,true);
}


{
  PerfStat perf;
   // double precision and int. it wil vectorize in mix 128 for int and 256 for double
   double s =0;
   for (int k=0; k!=100; ++k) {
     perf.start();
     for (int i=1; i<10000001; ++i) s+= std::sqrt(i+1.);
     perf.stop();
   }
   
   ret &= s!=0;
   
   //std::cout << " " << s << std::endl;
   
   std::cout << "|sqrt d  ";
   perf.print(std::cout,true);
 }
 
 
 
 return ret ? 0 : -1;
}


int main1() {

  std::cout << "++v" << std::endl;

  bool ret=true;
  {
    
    
    PerfStat perf;
    std::cout << "we are " << (PerfStat::isINTEL() ? "on" : "not on") << " an INTEL Machine" << std::endl; 
    PerfStat::header(std::cout,true);
    
    double s =0;
    for (int k=0; k!=100; ++k) {
      perf.start();    
      double v=0;
      for (int i=1; i!=1000001; ++i) s+= std::log((++v));
      perf.stop();
      
    } 
    ret &= s!=0;

   //std::cout << " " << s << std::endl;
    
    std::cout << "|log  ";
    perf.print(std::cout);

  }

  {
    PerfStat perf;
    
    
    double s =0;
    for (int k=0; k!=100; ++k) {
      perf.start();
      double v=0;
      for (int i=1; i!=1000001; ++i) s+= std::log2((++v));
      perf.stop();
      
    }
    
    ret &= s!=0;

   //std::cout << " " << s << std::endl;
    
    std::cout << "|log2  ";
    perf.print(std::cout);
    
  }
  

  {
    PerfStat perf;
    // will vectorize 256 only with avx2 (because of the int)
    float s =0;
    for (int k=0; k!=100; ++k) {
      perf.start();
      float c = 1.f/1000000.f;
      float v=0;
      for (int i=1; i<10000001; ++i) s+= polyHorner((++v)*c);
      perf.stop();
    }
    ret &= s!=0;

   //std::cout << " " << s << std::endl;

   std::cout << "|Horner f  ";
   perf.print(std::cout,true);
}

  {
    PerfStat perf;
    // will vectorize 256 only with avx2 (because of the int)
    float s =0;
    for (int k=0; k!=100; ++k) {
      perf.start();
      float c = 1.f/1000000.f;
      float v=0;
      for (int i=1; i<10000001; ++i) s+= polyEstrin((++v)*c);
      perf.stop();     
    }
    ret &= s!=0;

   //std::cout << " " << s << std::endl;

    
    std::cout << "|Estrin f  ";
    perf.print(std::cout,true);
  }


  {
    PerfStat perf;
    // double precision and int. it wil vectorize in mix 128 for int and 256 for double
    double s =0;
    for (int k=0; k!=100; ++k) {
      perf.start();
      double c = 1./1000000.;
      double v=0;
      for (int i=1; i<10000001; ++i) s+= polyHorner((++v)*c);
      perf.stop();                                                        
    }
    ret &= s!=0;

   //std::cout << " " << s << std::endl;

    
    std::cout << "|Horner d  ";
    perf.print(std::cout,true);
  }


  {
    PerfStat perf;
    // double precision and int. it wil vectorize in mix 128 for int and 256 for double
    double s =0;
    for (int k=0; k!=100; ++k) {
      perf.start();
      double c = 1./1000000.;
      double v=0;
      for (int i=1; i<10000001; ++i) s+= polyEstrin((++v)*c);
      perf.stop();      
    }
    ret &= s!=0;

   //std::cout << " " << s << std::endl;

    
    std::cout << "|Estrin d  ";
    perf.print(std::cout,true);
  }


  {
    PerfStat perf;
    // will vectorize 256 only with avx2 (because of the int)
    float s =0;
    for (int k=0; k!=100; ++k) {
      perf.start();
      float v=0;
      for (int i=1; i<10000001; ++i) s+= 1.f/(++v);
      perf.stop();
    }
    ret &= s!=0;

   //std::cout << " " << s << std::endl;
    
   std::cout << "|inv f  ";
   perf.print(std::cout,true);
}


{
  PerfStat perf;
   // double precision and int. it wil vectorize in mix 128 for int and 256 for double          
   double s =0;
    for (int k=0; k!=100; ++k) {
     perf.start();
     double v=0;
     for (int i=1; i<10000001; ++i) s+= 1./(++v);
     perf.stop();
     }

    ret &= s!=0;

   //std::cout << " " << s << std::endl;


   std::cout << "|inv d  ";
   perf.print(std::cout,true);
}


{
  PerfStat perf;
   // double precision and int. it wil vectorize in mix 128 for int and 256 for double
   double s =0;
   for (int k=0; k!=100; ++k) {
     perf.start();
     double v=0;
     for (int i=1; i<10000001; ++i) s+= std::sqrt(++v);
     perf.stop();
   }
   
   ret &= s!=0;
   
   //std::cout << " " << s << std::endl;
   
   std::cout << "|sqrt d  ";
   perf.print(std::cout,true);
 }
 
 
 
 return ret ? 0 : -1;
}


#include <random>

int main2() {

  std::cout << "a[i]=f(r[i])" << std::endl;

  constexpr int NN = 1024*4;
  alignas(128) float rf[NN];
  alignas(128) double rd[NN];
  alignas(128) float of[NN];
  alignas(128) double od[NN];

  std::mt19937 eng;
  std::uniform_real_distribution<float> rgen(0.5,1.5);
  for (int i=0;i!=NN;++i)
    od[i]=of[i]=rd[i]=rf[i]=rgen(eng);



  bool ret=true;
  {
    
    
    PerfStat perf;
    std::cout << "we are " << (PerfStat::isINTEL() ? "on" : "not on") << " an INTEL Machine" << std::endl; 
    PerfStat::header(std::cout,true);
    
    double s =0;
    for (int k=0; k!=10000; ++k) {
      perf.start();    
      for (int i=0; i!=NN; ++i) od[i]+= std::log(rd[i]);
      perf.stop();
    } 
    for (int i=0; i!=NN; ++i) s+=od[i];
    ret &= s!=0;

   //std::cout << " " << s << std::endl;
    
    std::cout << "|log  ";
    perf.print(std::cout);

  }

  {
    PerfStat perf;
    
    
    double s =0;
    for (int k=0; k!=10000; ++k) {
      perf.start();
      for (int i=0; i!=NN; ++i) od[i]+= std::log2(rd[i]);
      perf.stop();
      
    }
    for (int i=0; i!=NN; ++i) s+=od[i];
    ret &= s!=0;

   //std::cout << " " << s << std::endl;
    
    std::cout << "|log2  ";
    perf.print(std::cout);
    
  }
  

  {
    PerfStat perf;
    // will vectorize 256 only with avx2 (because of the int)
    float s =0;
    for (int k=0; k!=10000; ++k) {
      perf.start();
      for (int i=0; i!=NN; ++i) of[i]+= polyHorner(rf[i]);
      perf.stop();
    }
   for (int i=0; i!=NN; ++i) s+=of[i];
   ret &= s!=0;

   //std::cout << " " << s << std::endl;

   std::cout << "|Horner f  ";
   perf.print(std::cout,true);
}

  {
    PerfStat perf;
    // 
    float s =0;
    for (int k=0; k!=10000; ++k) {
      perf.start();
      for (int i=0; i!=NN; ++i) of[i]+= polyEstrin(rf[i]);
      perf.stop();     
    }
   for (int i=0; i!=NN; ++i) s+=of[i];   
    ret &= s!=0;

   //std::cout << " " << s << std::endl;

    
    std::cout << "|Estrin f  ";
    perf.print(std::cout,true);
  }


  {
    PerfStat perf;
    //
    double s =0;
    for (int k=0; k!=10000; ++k) {
      perf.start();
      for (int i=0; i!=NN; ++i) od[i]+= polyHorner(rd[i]);
      perf.stop();                                                        
    }
    for (int i=0; i!=NN; ++i) s+=od[i];
    ret &= s!=0;

   //std::cout << " " << s << std::endl;

    
    std::cout << "|Horner d  ";
    perf.print(std::cout,true);
  }


  {
    PerfStat perf;
    // 
    double s =0;
    for (int k=0; k!=10000; ++k) {
      perf.start();
      for (int i=0; i!=NN; ++i) od[i]+= polyEstrin(rd[i]);
      perf.stop();      
    }
    for (int i=0; i!=NN; ++i) s+=od[i];
    ret &= s!=0;

   //std::cout << " " << s << std::endl;

    
    std::cout << "|Estrin d  ";
    perf.print(std::cout,true);
  }


  {
    PerfStat perf;
    //
    float s =0;
    for (int k=0; k!=10000; ++k) {
      perf.start();
      for (int i=0; i!=NN; ++i) of[i]+= 1.f/rf[i];
      perf.stop();
    }
   for (int i=0; i!=NN; ++i) s+=of[i];
    ret &= s!=0;

   //std::cout << " " << s << std::endl;
    
   std::cout << "|inv f  ";
   perf.print(std::cout,true);
}


{
  PerfStat perf;
   //  
   double s =0;
   for (int k=0; k!=10000; ++k) {
     perf.start();
     for (int i=0; i!=NN; ++i) od[i]+= 1./rd[i];
     perf.stop();
   }
   for (int i=0; i!=NN; ++i) s+=od[i];

    ret &= s!=0;

   //std::cout << " " << s << std::endl;


   std::cout << "|inv d  ";
   perf.print(std::cout,true);
}


{
  PerfStat perf;
   // 
   double s =0;
   for (int k=0; k!=10000; ++k) {
     perf.start();
     for (int i=0; i!=NN; ++i) od[i]+= std::sqrt(rd[i]);
     perf.stop();
   }
   for (int i=0; i!=NN; ++i) s+=od[i];
   
   ret &= s!=0;
   
   //std::cout << " " << s << std::endl;
   
   std::cout << "|sqrt d  ";
   perf.print(std::cout,true);
 }
 
 
 
 return ret ? 0 : -1;
}


int main() {
  return main0() + main1() + main2();


}
