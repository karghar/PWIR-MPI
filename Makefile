CC      = mpicxx
CFLAGS  = -Wall -c --std=c++11 -O3  -Wno-unused-result -o
CXXFLAGS = $(CFLAGS)  -stdlib=libc++
LDFLAGS = -Wall -O3 --std=c++11
ALL     = matrixmul
O_FILES = densematgen.o sparsematrix.o

all: $(ALL)

$(ALL): %: %.o $(O_FILES)
	$(CC) $(LDFLAGS) $^ -o $@

%.o: %.cpp Makefile
	$(CC) $(CFLAGS) $@ $<

clean:
	rm -f *.o *core *~ *.out *.err $(ALL)