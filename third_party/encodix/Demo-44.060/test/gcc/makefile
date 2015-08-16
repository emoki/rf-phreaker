CC=g++
LINK=g++
CFLAGS= -I.. -I../../../Common -I../../gen
LDFLAGS=
OBJS=\
	ed_c.o\
	ed_c_known_ie.o\
	ed_lib.o\
	ed_access.o\
	ts44.060_support.o\
	ed_c_dump.o\
	csn1clib.o\
	ed_c_access.o\
	bitencode.o\
	Uplink_RLC_MAC.o\
	main.o\
	CSN1DataTypes.o\
	ed_dump_file.o\
	Downlink_RLC_MAC.o\
	ed_dump.o\
	ed_c_recog.o\
	ed_dump_val.o

test.exe: $(OBJS)
	$(LINK) $(OBJS) ${LDFLAGS} -o test.exe


ed_c.o: ../../gen/ed_c.c
	$(CC) -c $(CFLAGS) ../../gen/ed_c.c -o ed_c.o


ed_c_known_ie.o: ../../gen/ed_c_known_ie.c
	$(CC) -c $(CFLAGS) ../../gen/ed_c_known_ie.c -o ed_c_known_ie.o


ed_lib.o: ../../../Common/ed_lib.c
	$(CC) -c $(CFLAGS) ../../../Common/ed_lib.c -o ed_lib.o


ed_access.o: ../../../Common/ed_access.cpp
	$(CC) -c $(CFLAGS) ../../../Common/ed_access.cpp -o ed_access.o


ts44.060_support.o: ../../ts44.060_support.c
	$(CC) -c $(CFLAGS) ../../ts44.060_support.c -o ts44.060_support.o


ed_c_dump.o: ../../gen/ed_c_dump.c
	$(CC) -c $(CFLAGS) ../../gen/ed_c_dump.c -o ed_c_dump.o


csn1clib.o: ../../../Common/csn1clib.c
	$(CC) -c $(CFLAGS) ../../../Common/csn1clib.c -o csn1clib.o


ed_c_access.o: ../../gen/ed_c_access.cpp
	$(CC) -c $(CFLAGS) ../../gen/ed_c_access.cpp -o ed_c_access.o


bitencode.o: ../../../Common/bitencode.c
	$(CC) -c $(CFLAGS) ../../../Common/bitencode.c -o bitencode.o


Uplink_RLC_MAC.o: ../../gen/Uplink_RLC_MAC.c
	$(CC) -c $(CFLAGS) ../../gen/Uplink_RLC_MAC.c -o Uplink_RLC_MAC.o


main.o: ../main.cpp
	$(CC) -c $(CFLAGS) ../main.cpp -o main.o


CSN1DataTypes.o: ../../gen/CSN1DataTypes.c
	$(CC) -c $(CFLAGS) ../../gen/CSN1DataTypes.c -o CSN1DataTypes.o


ed_dump_file.o: ../../../Common/ed_dump_file.c
	$(CC) -c $(CFLAGS) ../../../Common/ed_dump_file.c -o ed_dump_file.o


Downlink_RLC_MAC.o: ../../gen/Downlink_RLC_MAC.c
	$(CC) -c $(CFLAGS) ../../gen/Downlink_RLC_MAC.c -o Downlink_RLC_MAC.o


ed_dump.o: ../../../Common/ed_dump.c
	$(CC) -c $(CFLAGS) ../../../Common/ed_dump.c -o ed_dump.o


ed_c_recog.o: ../../gen/ed_c_recog.c
	$(CC) -c $(CFLAGS) ../../gen/ed_c_recog.c -o ed_c_recog.o


ed_dump_val.o: ../../../Common/ed_dump_val.c
	$(CC) -c $(CFLAGS) ../../../Common/ed_dump_val.c -o ed_dump_val.o



clean:
	rm -f *.o
	rm -f test.exe
