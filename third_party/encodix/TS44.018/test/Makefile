

# Generated by vcproj2mak.pl 1.003 from test.vcproj

#---------------------------------------------------
# O/S RECOGNITION
#---------------------------------------------------
OSNAME = $(shell uname -s)

ifeq '$(OSNAME)' 'Linux'
OS=LINUX
endif
ifeq '$(OSNAME)' 'Darwin'
OS=MACOS
endif 
ifeq '$(OSNAME)' 'CYGWIN_NT-5.1'
OS=WINDOWS
endif
ifeq '$(OSNAME)' 'WindowsNT'
OS=WINDOWS
endif
ifeq '$(OSNAME)' ''
OS=OTHER
endif
#---------------------------------------------------

CFLAGS=-Wall -pedantic -DED_DEBUG_ALLOC -D_CRT_SECURE_NO_WARNINGS -I. -I../gen_Rel12 -I../../../Encodix/Common -I../../../Encodix/testing
STRIP=strip
CPP=g++
CC=gcc
LD=g++
LDFLAGS=
OEXT=.o
OUTDIR=gccout
AR=ar
LINKLIB=${OUTDIR}/linklib.a
EXEDEPS=
EXENAME=${OUTDIR}/test${XEXT}

OBJS=\
  ${OUTDIR}/bitencode${OEXT}\
  ${OUTDIR}/csn1clib${OEXT}\
  ${OUTDIR}/ed_dynamic${OEXT}\
  ${OUTDIR}/ed_lib${OEXT}\
  ${OUTDIR}/CSN1DataTypes_RR${OEXT}\
  ${OUTDIR}/RRDownlink_RR${OEXT}\
  ${OUTDIR}/RRPLENDownlink_RR${OEXT}\
  ${OUTDIR}/RRShortPD_RR${OEXT}\
  ${OUTDIR}/RRUplink_RR${OEXT}\
  ${OUTDIR}/UserDefinedDataTypes_RR${OEXT}\
  ${OUTDIR}/ed_c_RR${OEXT}\
  ${OUTDIR}/ed_c_known_ie_RR${OEXT}\
  ${OUTDIR}/ed_c_recog_RR${OEXT}\
  ${OUTDIR}/main${OEXT}\
  ${OUTDIR}/ts44.018_support${OEXT}

CLEAN_OBJS=${OBJS}

${EXENAME}: ${OUTDIR} ${OBJS}
	${LD} ${LDFLAGS} -o ${EXENAME} ${OBJS} ${LIBS}

${OUTDIR}:
	mkdir ${OUTDIR}

${OUTDIR}/bitencode${OEXT}: ../../../Encodix/Common/bitencode.c
	${CC} ${CFLAGS} -c ../../../Encodix/Common/bitencode.c -o ${OUTDIR}/bitencode${OEXT}

${OUTDIR}/csn1clib${OEXT}: ../../../Encodix/Common/csn1clib.c
	${CC} ${CFLAGS} -c ../../../Encodix/Common/csn1clib.c -o ${OUTDIR}/csn1clib${OEXT}

${OUTDIR}/ed_dynamic${OEXT}: ../../../Encodix/Common/ed_dynamic.c
	${CC} ${CFLAGS} -c ../../../Encodix/Common/ed_dynamic.c -o ${OUTDIR}/ed_dynamic${OEXT}

${OUTDIR}/ed_lib${OEXT}: ../../../Encodix/Common/ed_lib.c
	${CC} ${CFLAGS} -c ../../../Encodix/Common/ed_lib.c -o ${OUTDIR}/ed_lib${OEXT}

${OUTDIR}/CSN1DataTypes_RR${OEXT}: ../gen_Rel12/CSN1DataTypes_RR.c
	${CC} ${CFLAGS} -c ../gen_Rel12/CSN1DataTypes_RR.c -o ${OUTDIR}/CSN1DataTypes_RR${OEXT}

${OUTDIR}/RRDownlink_RR${OEXT}: ../gen_Rel12/RRDownlink_RR.c
	${CC} ${CFLAGS} -c ../gen_Rel12/RRDownlink_RR.c -o ${OUTDIR}/RRDownlink_RR${OEXT}

${OUTDIR}/RRPLENDownlink_RR${OEXT}: ../gen_Rel12/RRPLENDownlink_RR.c
	${CC} ${CFLAGS} -c ../gen_Rel12/RRPLENDownlink_RR.c -o ${OUTDIR}/RRPLENDownlink_RR${OEXT}

${OUTDIR}/RRShortPD_RR${OEXT}: ../gen_Rel12/RRShortPD_RR.c
	${CC} ${CFLAGS} -c ../gen_Rel12/RRShortPD_RR.c -o ${OUTDIR}/RRShortPD_RR${OEXT}

${OUTDIR}/RRUplink_RR${OEXT}: ../gen_Rel12/RRUplink_RR.c
	${CC} ${CFLAGS} -c ../gen_Rel12/RRUplink_RR.c -o ${OUTDIR}/RRUplink_RR${OEXT}

${OUTDIR}/UserDefinedDataTypes_RR${OEXT}: ../gen_Rel12/UserDefinedDataTypes_RR.c
	${CC} ${CFLAGS} -c ../gen_Rel12/UserDefinedDataTypes_RR.c -o ${OUTDIR}/UserDefinedDataTypes_RR${OEXT}

${OUTDIR}/ed_c_RR${OEXT}: ../gen_Rel12/ed_c_RR.c
	${CC} ${CFLAGS} -c ../gen_Rel12/ed_c_RR.c -o ${OUTDIR}/ed_c_RR${OEXT}

${OUTDIR}/ed_c_dump_RR${OEXT}: ../gen_Rel12/ed_c_dump_RR.c
	${CC} ${CFLAGS} -c ../gen_Rel12/ed_c_dump_RR.c -o ${OUTDIR}/ed_c_dump_RR${OEXT}

${OUTDIR}/ed_c_known_ie_RR${OEXT}: ../gen_Rel12/ed_c_known_ie_RR.c
	${CC} ${CFLAGS} -c ../gen_Rel12/ed_c_known_ie_RR.c -o ${OUTDIR}/ed_c_known_ie_RR${OEXT}

${OUTDIR}/ed_c_recog_RR${OEXT}: ../gen_Rel12/ed_c_recog_RR.c
	${CC} ${CFLAGS} -c ../gen_Rel12/ed_c_recog_RR.c -o ${OUTDIR}/ed_c_recog_RR${OEXT}

${OUTDIR}/main${OEXT}: main.c
	${CPP} ${CFLAGS} -c main.c -o ${OUTDIR}/main${OEXT}

${OUTDIR}/ts44.018_support${OEXT}: ../ts44.018_support.c
	${CC} ${CFLAGS} -c ../ts44.018_support.c -o ${OUTDIR}/ts44.018_support${OEXT}

${LINKLIB}: ${OBJS}


clean:
	rm -f ${CLEAN_OBJS}
	rm -f ${LINKLIB}
	rm -f ${EXENAME}

