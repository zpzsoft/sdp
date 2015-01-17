all : file_util_test date_time_test convert_test
.PHONY : all

#targets
file_util_test : file_util_test.o file_util.o
	g++ -o file_util_test file_util_test.o file_util.o

date_time_test : date_time_test.o date_time.o
	g++ -o date_time_test date_time_test.o date_time.o

convert_test : convert_test.o
	g++ -o convert_test convert_test.o

#objects
file_util.o : ../../file_util.cpp ../../file_util.h
	g++ -c ../../file_util.cpp -I../../../../

file_util_test.o : ../file_util_test.cpp ../../file_util.h
	g++ -c ../file_util_test.cpp -I../../../../

date_time_test.o : ../date_time_test.cpp
	g++ -c ../date_time_test.cpp -I../../../../

date_time.o : ../../date_time.cpp
	g++ -c ../../date_time.cpp -I../../../../

convert_test.o : ../convert_test.cpp ../../convert.h
	g++ -c ../convert_test.cpp -I../../../../

#make clean
clean:
	-rm file_util_test file_util_test.o date_time_test file_util.o date_time_test.o date_time.o \
convert.o convert_test.o convert_test

