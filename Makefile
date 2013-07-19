CXX = c++ ${ADDOPT} -std=gnu++11 -Wall -Wno-format  -Wstrict-overflow -Wunsafe-loop-optimizations -ftree-vectorizer-verbose=1 -ftree-loop-if-convert-stores -lrt -fPIC -fvisibility-inlines-hidden



.PHONY : run all clean L3Mem UnitTest featureTest callTest libCall

all : UnitTest L3Mem featureTest callTest libCall callTest_O3_wl


L3Mem : L3Mem_O2 L3Mem_O2_avx L3Mem_O2_avx2  L3Mem_O3 L3Mem_O3_avx L3Mem_O3_avx2 L3Mem_fast L3Mem_fast_avx L3Mem_fast_avx2
UnitTest : UnitTest_O3
featureTest : featureTest_O2 featureTest_O2_avx featureTest_O2_avx2  featureTest_O3 featureTest_O3_avx featureTest_O3_avx2 featureTest_fast featureTest_fast_avx featureTest_fast_avx2
callTest : callTest_O2 callTest_O2_avx callTest_O2_avx2  callTest_O3 callTest_O3_avx callTest_O3_avx2 callTest_fast callTest_fast_avx callTest_fast_avx2
libCall : libCall_O3.so  libCall_O3_avx.so  libCall_O3_avx2.so

%_O2 : %.cpp
	$(CXX) $(INCDIR) $< -o $@ -O2 -march=corei7

%_O2_avx : %.cpp
	$(CXX) $(INCDIR) $< -o $@ -O2 -march=corei7-avx


%_O2_avx2 : %.cpp
	$(CXX) $(INCDIR) $< -o $@ -O2 -march=core-avx2


%_O3 : %.cpp
	$(CXX) $(INCDIR) $< -o $@ -O3 -march=corei7

%_O3_avx : %.cpp
	$(CXX) $(INCDIR) $< -o $@ -O3 -march=corei7-avx


%_O3_avx2 : %.cpp
	$(CXX) $(INCDIR) $< -o $@ -O3 -march=core-avx2




%_fast : %.cpp
	$(CXX) $(INCDIR) $< -o $@ -Ofast -march=corei7

%_fast_avx : %.cpp
	$(CXX) $(INCDIR) $< -o $@ -Ofast -march=corei7-avx


%_fast_avx2 : %.cpp
	$(CXX) $(INCDIR) $< -o $@ -Ofast -march=core-avx2


%_O3.so : %.cc
	$(CXX) $(INCDIR) $< -o $@ -O3 -march=corei7 -shared

%_O3_avx.so : %.cc
	$(CXX) $(INCDIR) $< -o $@ -O3 -march=corei7-avx -shared


%_O3_avx2.so : %.cc
	$(CXX) $(INCDIR) $< -o $@ -O3 -march=core-avx2 -shared

callTest_O3_wl : callTest.cpp  libCall_O3.so
	$(CXX) $(INCDIR) $< -o $@ -O3 -march=corei7 -L./ -lCall_O3 -Wl,-rpath ./ -DWITHLIB

run : all
	for exe in *_*; do echo "\nrunning " $${exe}; ./$${exe}; done;

clean:
	rm  *_O2 *_O3 *_fast *_avx *_avx2 *.so callTest_O3_wl

