CXX = c++ ${ADDOPT} -std=gnu++11 -Wall -Wno-format  -Wstrict-overflow -Wunsafe-loop-optimizations -ftree-vectorizer-verbose=1 -ftree-loop-if-convert-stores -lrt



.PHONY : run all clean L3Mem  UnitTest

all : UnitTest L3Mem


L3Mem : L3Mem_O2 L3Mem_O2_avx L3Mem_O2_avx2  L3Mem_O3 L3Mem_O3_avx L3Mem_O3_avx2 L3Mem_fast L3Mem_fast_avx L3Mem_fast_avx2
UnitTest : UnitTest_O3


%_O2 : %.cpp
	$(CXX) $(INCDIR) $< -o $@ -O2 -march=corei7

%_O2_avx : %.cpp
	$(CXX) $(INCDIR) $< -o $@ -O2 -march=corei7-avx


%_O2_avx2 : %.cpp
	$(CXX) $(INCDIR) $< -o $@ -O2 -march=corei7-avx -mavx2 -mfma


%_O3 : %.cpp
	$(CXX) $(INCDIR) $< -o $@ -O3 -march=corei7

%_O3_avx : %.cpp
	$(CXX) $(INCDIR) $< -o $@ -O3 -march=corei7-avx


%_O3_avx2 : %.cpp
	$(CXX) $(INCDIR) $< -o $@ -O3 -march=corei7-avx -mavx2 -mfma



%_fast : %.cpp
	$(CXX) $(INCDIR) $< -o $@ -Ofast -march=corei7

%_fast_avx : %.cpp
	$(CXX) $(INCDIR) $< -o $@ -Ofast -march=corei7-avx


%_fast_avx2 : %.cpp
	$(CXX) $(INCDIR) $< -o $@ -Ofast -march=corei7-avx -mavx2 -mfma

run : all
	for exe in *_*; do echo "\nrunning " $${exe}; ./$${exe}; done;

clean:
	rm  *_O2 *_O3 *_fast *_avx *_avx2

