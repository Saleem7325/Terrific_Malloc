all : test

test: ../my_vm.h
	gcc test.c -L../ -lmy_vm -m32 -o test
	gcc multi_test.c -L../ -lmy_vm -m32 -o mtest -lpthread
	gcc mytest.c -L../ -lmy_vm -m32 -g -o mytest

clean:
	rm -rf test mtest mytest
