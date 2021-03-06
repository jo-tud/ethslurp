/*--------------------------------------------------------------------------------
 The MIT License (MIT)

 Copyright (c) 2016 Great Hill Corporation

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 --------------------------------------------------------------------------------*/
/*
 * This file was generated with makeClass. Edit only those parts of the code inside
 * of 'EXISTING_CODE' tags.
 */
#include "receipt.h"
#include "etherlib.h"
//---------------------------------------------------------------------------
IMPLEMENT_NODE(CReceipt, CBaseNode, curVersion);

//---------------------------------------------------------------------------
void CReceipt::Format(CExportContext& ctx, const SFString& fmtIn, void *data) const
{
	if (!isShowing())
		return;

	if (fmtIn.IsEmpty())
	{
		ctx << toJson();
		return;
	}

	SFString fmt = fmtIn;
	if (handleCustomFormat(ctx, fmt, data))
		return;

	CReceiptNotify dn(this);
	while (!fmt.IsEmpty())
		ctx << getNextChunk(fmt, nextReceiptChunk, &dn);
}

//---------------------------------------------------------------------------
SFString nextReceiptChunk(const SFString& fieldIn, SFBool& force, const void *data)
{
	CReceiptNotify *re = (CReceiptNotify*)data;
	const CReceipt *rec = re->getDataPtr();

	// Now give customized code a chance to override
	SFString ret = nextReceiptChunk_custom(fieldIn, force, data);
	if (!ret.IsEmpty())
		return ret;

	switch (tolower(fieldIn[0]))
	{
		case 'b':
			if ( fieldIn % "blockHash" ) return rec->blockHash;
			if ( fieldIn % "blockNumber" ) return asString(rec->blockNumber);
			break;
		case 'c':
			if ( fieldIn % "contractAddress" ) return rec->contractAddress;
			if ( fieldIn % "cumulativeGasUsed" ) return asString(rec->cumulativeGasUsed);
			break;
		case 'f':
			if ( fieldIn % "from" ) return rec->from;
			break;
		case 'g':
			if ( fieldIn % "gasUsed" ) return asString(rec->gasUsed);
			break;
		case 'l':
			if ( fieldIn % "logs" )
			{
				SFInt32 cnt = rec->logs.getCount();
				if (!cnt) return EMPTY;
				SFString ret = "[\n";
				for (int i=0;i<cnt;i++)
				{
					ret += rec->logs[i].Format();
					ret += ((i<cnt-1) ? ",\n" : "\n");
				}
				return ret+"    ]";
			}
			break;
		case 'r':
			if ( fieldIn % "root" ) return rec->root;
			break;
		case 't':
			if ( fieldIn % "to" ) return rec->to;
			if ( fieldIn % "transactionHash" ) return rec->transactionHash;
			if ( fieldIn % "transactionIndex" ) return asString(rec->transactionIndex);
			break;
	}

	// Finally, give the parent class a chance
	ret = nextBasenodeChunk(fieldIn, force, rec);
	if (!ret.IsEmpty())
		return ret;

	return "<span class=warning>Field not found: [{" + fieldIn + "}]</span>\n";
}

//---------------------------------------------------------------------------------------------------
SFBool CReceipt::setValueByName(const SFString& fieldName, const SFString& fieldValue)
{
	// EXISTING_CODE
	if (fieldName % "logs")
	{
		char *p = (char *)(const char*)fieldValue;
		while (p && *p)
		{
			CLogEntry log;SFInt32 nFields=0;
			p = log.parseJson(p,nFields);
			if (nFields)
				logs[logs.getCount()] = log;
		}
		return TRUE;
	}
	// EXISTING_CODE

	switch (tolower(fieldName[0]))
	{
		case 'b':
			if ( fieldName % "blockHash" ) { blockHash = toLower(fieldValue); return TRUE; }
			if ( fieldName % "blockNumber" ) { blockNumber = toLong(fieldValue); return TRUE; }
			break;
		case 'c':
			if ( fieldName % "contractAddress" ) { contractAddress = toLower(fieldValue); return TRUE; }
			if ( fieldName % "cumulativeGasUsed" ) { cumulativeGasUsed = toLong(fieldValue); return TRUE; }
			break;
		case 'f':
			if ( fieldName % "from" ) { from = toLower(fieldValue); return TRUE; }
			break;
		case 'g':
			if ( fieldName % "gasUsed" ) { gasUsed = toLong(fieldValue); return TRUE; }
			break;
		case 'l':
			if ( fieldName % "logs" ) return TRUE;
			break;
		case 'r':
			if ( fieldName % "root" ) { root = fieldValue; return TRUE; }
			break;
		case 't':
			if ( fieldName % "to" ) { to = toLower(fieldValue); return TRUE; }
			if ( fieldName % "transactionHash" ) { transactionHash = toLower(fieldValue); return TRUE; }
			if ( fieldName % "transactionIndex" ) { transactionIndex = toLong(fieldValue); return TRUE; }
			break;
		default:
			break;
	}
	return FALSE;
}

//---------------------------------------------------------------------------------------------------
void CReceipt::finishParse()
{
	// EXISTING_CODE
	// EXISTING_CODE
}

//---------------------------------------------------------------------------------------------------
void CReceipt::Serialize(SFArchive& archive)
{
	if (!SerializeHeader(archive))
		return;

	if (archive.isReading())
	{
		archive >> blockHash;
		archive >> blockNumber;
		archive >> contractAddress;
		archive >> cumulativeGasUsed;
		archive >> from;
		archive >> gasUsed;
		archive >> logs;
		archive >> root;
		archive >> to;
		archive >> transactionHash;
		archive >> transactionIndex;
		finishParse();
	} else
	{
		archive << blockHash;
		archive << blockNumber;
		archive << contractAddress;
		archive << cumulativeGasUsed;
		archive << from;
		archive << gasUsed;
		archive << logs;
		archive << root;
		archive << to;
		archive << transactionHash;
		archive << transactionIndex;

	}
}

//---------------------------------------------------------------------------
void CReceipt::registerClass(void)
{
	static bool been_here=false;
	if (been_here) return;
	been_here=true;

	SFInt32 fieldNum=1000;
	ADD_FIELD(CReceipt, "schema",  T_NUMBER|TS_LABEL, ++fieldNum);
	ADD_FIELD(CReceipt, "deleted", T_RADIO|TS_LABEL,  ++fieldNum);
	ADD_FIELD(CReceipt, "blockHash", T_TEXT, ++fieldNum);
	ADD_FIELD(CReceipt, "blockNumber", T_NUMBER, ++fieldNum);
	ADD_FIELD(CReceipt, "contractAddress", T_TEXT, ++fieldNum);
	ADD_FIELD(CReceipt, "cumulativeGasUsed", T_NUMBER, ++fieldNum);
	ADD_FIELD(CReceipt, "from", T_TEXT, ++fieldNum);
	ADD_FIELD(CReceipt, "gasUsed", T_NUMBER, ++fieldNum);
	ADD_FIELD(CReceipt, "logs", T_TEXT|TS_ARRAY, ++fieldNum);
	ADD_FIELD(CReceipt, "root", T_TEXT, ++fieldNum);
	ADD_FIELD(CReceipt, "to", T_TEXT, ++fieldNum);
	ADD_FIELD(CReceipt, "transactionHash", T_TEXT, ++fieldNum);
	ADD_FIELD(CReceipt, "transactionIndex", T_NUMBER, ++fieldNum);

	// Hide our internal fields, user can turn them on if they like
	HIDE_FIELD(CReceipt, "schema");
	HIDE_FIELD(CReceipt, "deleted");

	// EXISTING_CODE
	// EXISTING_CODE
}

//---------------------------------------------------------------------------
int sortReceipt(const SFString& f1, const SFString& f2, const void *rr1, const void *rr2)
{
	CReceipt *g1 = (CReceipt*)rr1;
	CReceipt *g2 = (CReceipt*)rr2;

	SFString v1 = g1->getValueByName(f1);
	SFString v2 = g2->getValueByName(f1);
	SFInt32 s = v1.Compare(v2);
	if (s || f2.IsEmpty())
		return (int)s;

	v1 = g1->getValueByName(f2);
	v2 = g2->getValueByName(f2);
	return (int)v1.Compare(v2);
}
int sortReceiptByName(const void *rr1, const void *rr2) { return sortReceipt("re_Name", "", rr1, rr2); }
int sortReceiptByID  (const void *rr1, const void *rr2) { return sortReceipt("receiptID", "", rr1, rr2); }

//---------------------------------------------------------------------------
SFString nextReceiptChunk_custom(const SFString& fieldIn, SFBool& force, const void *data)
{
	return EMPTY;
}

//---------------------------------------------------------------------------
SFBool CReceipt::handleCustomFormat(CExportContext& ctx, const SFString& fmtIn, void *data) const
{
	// EXISTING_CODE
	// EXISTING_CODE
	return FALSE;
}

//---------------------------------------------------------------------------
SFBool CReceipt::readBackLevel(SFArchive& archive)
{
	SFBool done=FALSE;
	// EXISTING_CODE
	// EXISTING_CODE
	return done;
}

//---------------------------------------------------------------------------
// EXISTING_CODE
// EXISTING_CODE
