CC=g++
LINK=g++
CFLAGS= -I.. -I../../../Common -I../../gen
LDFLAGS=
OBJS=\
	ed_c.o\
	ed_c_known_ie.o\
	UserDefinedDataTypes.o\
	ed_lib.o\
	ed_access.o\
	ts44.018_support.o\
	csn1clib.o\
	ed_c_access.o\
	bitencode.o\
	RRSysInfo.o\
	Layer3.o\
	main.o\
	CSN1DataTypes.o\
	ed_c_recog.o

test.exe: $(OBJS)
	$(LINK) $(OBJS) ${LDFLAGS} -o test.exe


ed_c.o: ../../gen/ed_c.c
	$(CC) -c $(CFLAGS) ../../gen/ed_c.c -o ed_c.o


ed_c_known_ie.o: ../../gen/ed_c_known_ie.c
	$(CC) -c $(CFLAGS) ../../gen/ed_c_known_ie.c -o ed_c_known_ie.o


UserDefinedDataTypes.o: ../../gen/UserDefinedDataTypes.c
	$(CC) -c $(CFLAGS) ../../gen/UserDefinedDataTypes.c -o UserDefinedDataTypes.o


ed_lib.o: ../../../Common/ed_lib.c
	$(CC) -c $(CFLAGS) ../../../Common/ed_lib.c -o ed_lib.o


ed_access.o: ../../../Common/ed_access.cpp
	$(CC) -c $(CFLAGS) ../../../Common/ed_access.cpp -o ed_access.o


ts44.018_support.o: ../../ts44.018_support.c
	$(CC) -c $(CFLAGS) ../../ts44.018_support.c -o ts44.018_support.o


csn1clib.o: ../../../Common/csn1clib.c
	$(CC) -c $(CFLAGS) ../../../Common/csn1clib.c -o csn1clib.o


ed_c_access.o: ../../gen/ed_c_access.cpp
	$(CC) -c $(CFLAGS) ../../gen/ed_c_access.cpp -o ed_c_access.o


bitencode.o: ../../../Common/bitencode.c
	$(CC) -c $(CFLAGS) ../../../Common/bitencode.c -o bitencode.o


RRSysInfo.o: ../../gen/RRSysInfo.c
	$(CC) -c $(CFLAGS) ../../gen/RRSysInfo.c -o RRSysInfo.o


Layer3.o: ../../gen/Layer3.c
	$(CC) -c $(CFLAGS) ../../gen/Layer3.c -o Layer3.o


main.o: ../main.cpp
	$(CC) -c $(CFLAGS) ../main.cpp -o main.o


CSN1DataTypes.o: ../../gen/CSN1DataTypes.c
	$(CC) -c $(CFLAGS) ../../gen/CSN1DataTypes.c -o CSN1DataTypes.o


ed_c_recog.o: ../../gen/ed_c_recog.c
	$(CC) -c $(CFLAGS) ../../gen/ed_c_recog.c -o ed_c_recog.o


clean:
	rm -f *.o
	rm -f test.exe
