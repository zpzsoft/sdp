#file_util_test : file_util_test.o file_util.o
#	g++ -o file_util_test file_util_test.o file_util.o

date_time_test : date_time_test.o date_time.o
	g++ -o date_time_test date_time_test.o date_time.o

file_util.o : ../../file_util.cc ../../file_util.h
	g++ -c ../../file_util.cc -I../../../../

file_util_test.o : ../file_util_test.cc ../../file_util.h
	g++ -c ../file_util_test.cc -I../../../../

date_time_test.o : ../date_time_test.cc
	g++ -c ../date_time_test.cc -I../../../../

date_time.o : ../../date_time.cc
	g++ -c ../../date_time.cc -I../../../../

clean:
	-rm file_util_test file_util_test.o file_util.o
