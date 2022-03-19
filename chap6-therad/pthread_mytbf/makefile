CFLAGS+=-pthread
LDFLAGS= -pthread
all:mytbf
mytbf:main.o mtbf.o 
	gcc $^ -o $@ $(CFLAGS) $(LDFLAGS) 

clean:
	rm -rf *.o mytbf 