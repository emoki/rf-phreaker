/**************************************************************************
	Access Dump Example - (c) Dafocus 2007
	
	Custom dump functions for specific types
**************************************************************************/
#include "ed_c_access.h"
#include "AccessDump.h"
#include "assert.h"

/*--------------------------------------------------------------------------
	Given a "structured" object, it returns the field id of the field with
	the given name or asserts if not found.
--------------------------------------------------------------------------*/
unsigned AccessDump_FindField (const TEDClassStructured* Class, const char* FieldName)
{
	unsigned i;
	for (i=0; i<Class->Count (); i++) {
		if (strcmp (Class->GetFieldInfo (i).GetFieldName (), FieldName) == 0) {
			return i;
		}
	}
	assert (0); // Field not found
	return i;   // In case of field not found, return Class->Count ().
}

/*--------------------------------------------------------------------------
	CUSTOM DUMP FUNCTION FOR THE "MobileId" TYPE.
--------------------------------------------------------------------------*/
void AccessDump_MobileId (const TEDDataBase* Data, ostream& out, unsigned indent)
{
	/* Retrieve the MobileId class descriptor and value */
	const TEDDataStruct* MobileIdData = (const TEDDataStruct*)Data;
	const TEDClassStruct* MobileIdClass = (const TEDClassStruct*)(MobileIdData->GetClass ());
	assert (MobileIdClass->GetType () == TED_ACC_STRUCT);

	/* Retrieve the IdentityDigit (element #0 of the MobileId structure) */
	const TEDDataSequence* IdentityDigitData = (const TEDDataSequence*)MobileIdData->GetElement (AccessDump_FindField (MobileIdClass, "IdentityDigit"));
	const TEDClassSequence* IdentityDigitClass = (const TEDClassSequence*)(IdentityDigitData->GetClass ());
	assert (IdentityDigitClass->GetType () == TED_ACC_SEQUENCE);

	/* Retrieve the IdentityType (element #1 of the MobileId structure) */
	const TEDDataEnumerated* IdentityTypeData = (const TEDDataEnumerated*)MobileIdData->GetElement (AccessDump_FindField (MobileIdClass, "IdentityType"));
	const TEDClassEnumerated* IdentityTypeClass = (const TEDClassEnumerated*)(IdentityTypeData->GetClass ());
	assert (IdentityTypeClass->GetType () == TED_ACC_ENUMERATED);

	/* Print the IdentityType enumeration */
	out << endl << INDENTP(indent+1) << "IdentityType=";
	AccessDump (IdentityTypeData, out, indent);

	/* Print the IdentityDigit sequence */
	out << INDENTP(indent+1) << "IdentityDigits=";
	unsigned i;
	for (i=0; i<IdentityDigitData->Count (); i++) {
		const TEDDataInteger* DigitData = (const TEDDataInteger*)(IdentityDigitData->GetElement (i));
		assert (DigitData->GetClass ()->GetType () == TED_ACC_INTEGER);
		out << DigitData->GetValue ();
	}
	out << endl;
}

/*--------------------------------------------------------------------------
	CUSTOM DUMP FUNCTION FOR THE "CellChannel" TYPE.
	
	STRATEGY
	========
	Here we have to print the TS 04.18, 10.5.2.1b CellChannel field.
	That field is a union that can have one of the following setups: BitMap0, 
	Range1024, Range512, Range256, Range128 and Variable.
	In this example, we choose to treat in a custom way the "Variable"
	setup.
--------------------------------------------------------------------------*/
void AccessDump_CellChannel (const TEDDataBase* Data, ostream& out, unsigned indent)
{
	/* Retrieve the MobileId class descriptor and value */
	const TEDDataUnion* CellChannelData = (const TEDDataUnion*)Data;
	const TEDClassUnion* CellChannelClass = (const TEDClassUnion*)(CellChannelData->GetClass ());
	assert (CellChannelClass->GetType () == TED_ACC_UNION);

	/* Retrieve the field that is currently active */
	const char* FieldName = CellChannelClass->GetFieldInfo (CellChannelData->GetActiveEntry ()).GetFieldName ();
	
	int i;
	bool firstEntry = true;
	out << endl << INDENTP(indent+1) << "Format: ";

	/*==========================================================*/
	/*  VARIABLE                                                */
	/*==========================================================*/
	if (strcmp (FieldName, "Variable") == 0) {

		/* Retrieve the Variable field */
		const TEDDataStruct* VariableData = (const TEDDataStruct*)CellChannelData->GetElement ();
		const TEDClassStruct* VariableClass = (const TEDClassStruct*)(VariableData->GetClass ());
		assert (VariableClass->GetType () == TED_ACC_STRUCT);

		/* Retrieve the OrigARFCN (element #0 of the Variable structure) */
		const TEDDataEnumerated* OrigARFCNData = (const TEDDataEnumerated*)VariableData->GetElement (AccessDump_FindField (VariableClass, "OrigARFCN"));
		const TEDClassEnumerated* OrigARFCNClass = (const TEDClassEnumerated*)(OrigARFCNData->GetClass ());
		assert (OrigARFCNClass->GetType () == TED_ACC_INTEGER);
		long OrigARFCN = OrigARFCNData->GetValue ();

		/* Retrieve the RRFCN (element #1 of the Variable structure) */
		const TEDDataSequence* RRFCNData = (const TEDDataSequence*)VariableData->GetElement (AccessDump_FindField (VariableClass, "RRFCN"));
		const TEDClassSequence* RRFCNClass = (const TEDClassSequence*)(RRFCNData->GetClass ());
		assert (RRFCNClass->GetType () == TED_ACC_SEQUENCE);

		/* Print the RRFCN sequence */
		out << "variable bit map";
		out << endl << INDENTP(indent+1) << "ARFCN's= " << OrigARFCN;
		for (i=0; i<(int)RRFCNData->Count (); i++) {
			const TEDDataInteger* DigitData = (const TEDDataInteger*)(RRFCNData->GetElement (i));
			assert (DigitData->GetClass ()->GetType () == TED_ACC_INTEGER);
			if (DigitData->GetValue ()) {
				out << ", " << i+1+OrigARFCN;
				firstEntry = false;
			}
		}
		out << endl;
	}
	/*==========================================================*/
	/*  BitMap0                                                */
	/*==========================================================*/
	else if (strcmp (FieldName, "BitMap0") == 0) {
		/* Retrieve the Variable field */
		const TEDDataSequence* BitMap0Data = (const TEDDataSequence*)CellChannelData->GetElement ();
		const TEDClassSequence* BitMap0Class = (const TEDClassSequence*)(BitMap0Data->GetClass ());
		assert (BitMap0Class->GetType () == TED_ACC_SEQUENCE);

		/* Print the RRFCN sequence */
		out << "bit map 0";
		out << endl << INDENTP(indent+1) << "ARFCN's=";

		for (i=BitMap0Data->Count ()-1; i>=0; i--) {
			const TEDDataInteger* DigitData = (const TEDDataInteger*)(BitMap0Data->GetElement (i));
			assert (DigitData->GetClass ()->GetType () == TED_ACC_INTEGER);
			if (DigitData->GetValue ()) {
				out << (firstEntry ? " " : ", ") << 124-i;
				firstEntry = false;
			}
		}
		out << endl;
	}
	/*==========================================================*/
	/*  DEFAULT                                                 */
	/*==========================================================*/
	else {
		if (strcmp (FieldName, "Range1024") == 0) {out << "1024 range";}
		else if (strcmp (FieldName, "Range512" ) == 0) {out << "512 range";}
		else if (strcmp (FieldName, "Range256" ) == 0) {out << "256 range";}
		else if (strcmp (FieldName, "Range128" ) == 0) {out << "128 range";}
		else {out << "unknown";}

		/* Otherwise, use the default AccessDump printout */
		AccessDump (Data, out, indent, true);
		return;
	}
}

/*--------------------------------------------------------------------------
	CUSTOM DUMP FUNCTION FOR THE "RequestReference" TYPE.
--------------------------------------------------------------------------*/
void AccessDump_RequestReference (const TEDDataBase* Data, ostream& out, unsigned indent)
{
	/* Retrieve the MobileId class descriptor and value */
	const TEDDataStruct* RequestReferenceData = (const TEDDataStruct*)Data;
	const TEDClassStruct* RequestReferenceClass = (const TEDClassStruct*)(RequestReferenceData->GetClass ());
	assert (RequestReferenceClass->GetType () == TED_ACC_STRUCT);

	/* Retrieve the RA (element #0 of the RequestReference structure) */
	const TEDDataInteger* RAData = (const TEDDataInteger*)RequestReferenceData->GetElement (AccessDump_FindField (RequestReferenceClass, "RA"));
	const TEDClassInteger* RAClass = (const TEDClassInteger*)(RAData->GetClass ());
	assert (RAClass->GetType () == TED_ACC_INTEGER);

	/* Retrieve the T1 (element #1 of the RequestReference structure) */
	const TEDDataInteger* T1Data = (const TEDDataInteger*)RequestReferenceData->GetElement (AccessDump_FindField (RequestReferenceClass, "T1"));
	const TEDClassInteger* T1Class = (const TEDClassInteger*)(T1Data->GetClass ());
	assert (T1Class->GetType () == TED_ACC_INTEGER);
	unsigned long T1 = (unsigned long)T1Data->GetValue ();

	/* Retrieve the T2 (element #3 of the RequestReference structure) */
	const TEDDataInteger* T2Data = (const TEDDataInteger*)RequestReferenceData->GetElement (AccessDump_FindField (RequestReferenceClass, "T2"));
	const TEDClassInteger* T2Class = (const TEDClassInteger*)(T2Data->GetClass ());
	assert (T2Class->GetType () == TED_ACC_INTEGER);
	unsigned long T2 = (unsigned long)T2Data->GetValue ();

	/* Retrieve the T3 (element #2 of the RequestReference structure) */
	const TEDDataInteger* T3Data = (const TEDDataInteger*)RequestReferenceData->GetElement (AccessDump_FindField (RequestReferenceClass, "T3"));
	const TEDClassInteger* T3Class = (const TEDClassInteger*)(T3Data->GetClass ());
	assert (T3Class->GetType () == TED_ACC_INTEGER);
	unsigned long T3 = (unsigned long)T3Data->GetValue ();

	/* Print the RA value */
	out << "{" << endl << INDENTP(indent+1) << "RA: " << (unsigned)RAData->GetValue () << endl;

	/*
		Calculate the frame number according to Table 10.5.2.30.1/3GPP TS 04.18
		FORMULA: 51x((T3-T2) mod 26)+T3+51x26xT1
	*/
	unsigned FrameNumber = 51 * ((T3-T2) % 26)+T3+51*26*T1;
	
	out << INDENTP(indent+1) << "FrameNumber: " << FrameNumber << endl << INDENTP(indent) << "}" << endl;
}

/*--------------------------------------------------------------------------
	CUSTOM DUMP FUNCTION FOR THE "TimingAdvance" TYPE.
--------------------------------------------------------------------------*/
void AccessDump_TimingAdvance (const TEDDataBase* Data, ostream& out, unsigned indent)
{
	/* Retrieve the MobileId class descriptor and value */
	const TEDDataStruct* TimingAdvanceData = (const TEDDataStruct*)Data;
	const TEDClassStruct* TimingAdvanceClass = (const TEDClassStruct*)(TimingAdvanceData->GetClass ());
	assert (TimingAdvanceClass->GetType () == TED_ACC_STRUCT);

	/* Retrieve the "value" (element #0 of the TimingAdvance structure) */
	const TEDDataInteger* ValueData = (const TEDDataInteger*)TimingAdvanceData->GetElement (AccessDump_FindField (TimingAdvanceClass, "value"));
	const TEDClassInteger* ValueClass = (const TEDClassInteger*)(ValueData->GetClass ());
	assert (ValueClass->GetType () == TED_ACC_INTEGER);

	/*
		Calculate the timing advance according to Table 10.5.2.40.1/3GPP TS 04.18
		FORMULA: 1 bit period = 48/13 us
	*/
	double TimingAdvance = ((unsigned)ValueData->GetValue ()) * 48.0 / 13.0;
	
	out << TimingAdvance << "us" << endl;
}


#define CUSTOM_ACCESS(TYPE) {&AccessClass_c_##TYPE, AccessDump_##TYPE},


/*--------------------------------------------------------------------------
	TABLE OF CUSTOM ACCESS DUMP FUNCTIONS
--------------------------------------------------------------------------*/
TAccessDumpCustom MyAccessDumpTable [] = {
	CUSTOM_ACCESS (MobileId)
	CUSTOM_ACCESS (CellChannel)
	CUSTOM_ACCESS (RequestReference)
	CUSTOM_ACCESS (TimingAdvance)
	{NULL, NULL}
};