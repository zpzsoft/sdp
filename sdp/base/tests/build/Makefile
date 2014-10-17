file_util_test : file_util_test.o file_util.o
	g++ -o file_util_test file_util_test.o file_util.o

file_util.o : ../../file_util.cc ../../file_util.h
	g++ -c ../../file_util.cc -I../../../../

file_util_test.o : ../file_util_test.cc ../../file_util.h
	g++ -c ../file_util_test.cc -I../../../../

clean:
	-rm file_util_test file_util_test.o file_util.o
