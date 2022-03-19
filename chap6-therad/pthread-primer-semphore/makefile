CFLAGS+=-pthread
LDFLAGS= -L pthread
main: 
	cc $(CFLAGS) $(LDFLAGS) main.c mysem.c -o main 
run:
	./main 
clean:
	rm main 