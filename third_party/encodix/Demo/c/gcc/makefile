# Makefile for EnDec demo
CC=gcc
LINK=gcc
CPPFLAGS=-I../../gen-c -I../../../Common -I..
CFLAGS=
OBJ_EXT=.obj
OUT_DIR=./

OBJS = \
	$(OUT_DIR)main$(OBJ_EXT) \
	$(OUT_DIR)ed_c_dump$(OBJ_EXT) \
  $(OUT_DIR)CSN1DataTypes$(OBJ_EXT) \
	$(OUT_DIR)ed_c_recog$(OBJ_EXT) \
	$(OUT_DIR)Uplink$(OBJ_EXT) \
	$(OUT_DIR)Downlink$(OBJ_EXT) \
	$(OUT_DIR)ed_c_known_ie$(OBJ_EXT) \
	$(OUT_DIR)GSM0816$(OBJ_EXT) \
	$(OUT_DIR)UserDefinedDataTypes$(OBJ_EXT) \
	$(OUT_DIR)csn1clib$(OBJ_EXT) \
	$(OUT_DIR)ed_lib$(OBJ_EXT) \
	$(OUT_DIR)ed_dump$(OBJ_EXT) \
	$(OUT_DIR)ed_dump_file$(OBJ_EXT) \
	$(OUT_DIR)ed_dump_val$(OBJ_EXT)
	
endec_demo.exe: $(OBJS)
	$(LINK) $(OBJS) -o endec_demo.exe

$(OUT_DIR)main$(OBJ_EXT): ../main.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c ../main.c -o $(OUT_DIR)main$(OBJ_EXT)

$(OUT_DIR)ed_c_dump$(OBJ_EXT): ../../gen-c/ed_c_dump.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c ../../gen-c/ed_c_dump.c -o $(OUT_DIR)ed_c_dump$(OBJ_EXT)

$(OUT_DIR)CSN1DataTypes$(OBJ_EXT): ../../gen-c/CSN1DataTypes.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c ../../gen-c/CSN1DataTypes.c -o $(OUT_DIR)CSN1DataTypes$(OBJ_EXT)

$(OUT_DIR)ed_c_recog$(OBJ_EXT): ../../gen-c/ed_c_recog.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c ../../gen-c/ed_c_recog.c -o $(OUT_DIR)ed_c_recog$(OBJ_EXT)

$(OUT_DIR)Downlink$(OBJ_EXT): ../../gen-c/Downlink.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c ../../gen-c/Downlink.c -o $(OUT_DIR)Downlink$(OBJ_EXT)

$(OUT_DIR)GSM0816$(OBJ_EXT): ../../gen-c/GSM0816.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c ../../gen-c/GSM0816.c -o $(OUT_DIR)GSM0816$(OBJ_EXT)

$(OUT_DIR)Uplink$(OBJ_EXT): ../../gen-c/Uplink.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c ../../gen-c/Uplink.c -o $(OUT_DIR)Uplink$(OBJ_EXT)

$(OUT_DIR)ed_c_known_ie$(OBJ_EXT): ../../gen-c/ed_c_known_ie.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c ../../gen-c/ed_c_known_ie.c -o $(OUT_DIR)ed_c_known_ie$(OBJ_EXT)

$(OUT_DIR)UserDefinedDataTypes$(OBJ_EXT): ../../gen-c/UserDefinedDataTypes.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c ../../gen-c/UserDefinedDataTypes.c -o $(OUT_DIR)UserDefinedDataTypes$(OBJ_EXT)

$(OUT_DIR)csn1clib$(OBJ_EXT): ../../../Common/csn1clib.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c ../../../Common/csn1clib.c -o $(OUT_DIR)csn1clib$(OBJ_EXT)

$(OUT_DIR)ed_lib$(OBJ_EXT): ../../../Common/ed_lib.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c ../../../Common/ed_lib.c -o $(OUT_DIR)ed_lib$(OBJ_EXT)

$(OUT_DIR)ed_dump$(OBJ_EXT): ../../../Common/ed_dump.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c ../../../Common/ed_dump.c -o $(OUT_DIR)ed_dump$(OBJ_EXT)

$(OUT_DIR)ed_dump_val$(OBJ_EXT): ../../../Common/ed_dump_val.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c ../../../Common/ed_dump_val.c -o $(OUT_DIR)ed_dump_val$(OBJ_EXT)

$(OUT_DIR)ed_dump_file$(OBJ_EXT): ../../../Common/ed_dump_file.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c ../../../Common/ed_dump_file.c -o $(OUT_DIR)ed_dump_file$(OBJ_EXT)

clean:
	rm -f *.obj *.o endec_demo.exe