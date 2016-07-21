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
 * This file was generated with makeClass. Edit only those parts inside 
 * of 'EXISTING_CODE' tags.
 */
#include "transaction.h"

//---------------------------------------------------------------------------
IMPLEMENT_NODE(CTransaction, CBaseNode, NO_SCHEMA);

//---------------------------------------------------------------------------
void CTransaction::Format(CExportContext& ctx, const SFString& fmtIn, void *data) const
{
	if (!isShowing())
		return;

	SFString fmt = (fmtIn.IsEmpty() ? defaultFormat() : fmtIn);
	if (handleCustomFormat(ctx, fmt, data))
		return;

	CTransactionNotify dn(this);
	while (!fmt.IsEmpty())
		ctx << getNextChunk(fmt, nextTransactionChunk, &dn);
}

//#define NICE
#ifdef NICE
SFString toNice(const SFString& in)
{
	if (!in.startsWith("0xb61d27f6")&&!in.startsWith("0xf00d4b5d"))
		return in;
	SFString input = in;
	SFString ret = (input.Left(10) + "<br>\n");
	input=input.Mid(10,1000000);
	while (!input.IsEmpty())
	{
		ret += (input.Left(128) + "<br>\n");
		input=input.Mid(128,100000);
	}
	return ret;
}
#endif

//---------------------------------------------------------------------------
SFString nextTransactionChunk(const SFString& fieldIn, SFBool& force, const void *data)
{
	CTransactionNotify *tr = (CTransactionNotify*)data;
	const CTransaction *tra = tr->getDataPtr();

	// Now give customized code a chance to override
	SFString ret = nextTransactionChunk_custom(fieldIn, force, data);
	if (!ret.IsEmpty())
		return ret;
	
	switch (tolower(fieldIn[0]))
	{
		case 'b':
			if ( fieldIn % "blockHash" ) return tra->blockHash;
			if ( fieldIn % "blockNumber" ) return asString(tra->blockNumber);
			break;
		case 'c':
			if ( fieldIn % "confirmations" ) return asString(tra->confirmations);
			if ( fieldIn % "contractAddress" ) return tra->contractAddress;
			if ( fieldIn % "cumulativeGasUsed" ) return tra->cumulativeGasUsed;
			break;
		case 'f':
			if ( fieldIn % "from" ) return tra->from;
			break;
		case 'g':
			if ( fieldIn % "gas" ) return tra->gas;
			if ( fieldIn % "gasPrice" ) return tra->gasPrice;
			if ( fieldIn % "gasUsed" ) return tra->gasUsed;
			break;
		case 'h':
			if ( fieldIn % "handle" ) return asString(tra->handle);
			if ( fieldIn % "hash" ) return tra->hash;
			break;
		case 'i':
#ifdef NICE
			if ( fieldIn % "input" ) return toNice(tra->input);
#else
			if ( fieldIn % "input" ) return tra->input;
#endif
			if ( fieldIn % "isError" ) return asString(tra->isError);
			if ( fieldIn % "isInternalTx" ) return asString(tra->isInternalTx);
			break;
		case 'n':
			if ( fieldIn % "nonce" ) return tra->nonce;
			break;
		case 't':
			if ( fieldIn % "timeStamp" ) return asString(tra->timeStamp);
			if ( fieldIn % "to" ) return tra->to;
			if ( fieldIn % "transactionIndex" ) return asString(tra->transactionIndex);
			break;
		case 'v':
			if ( fieldIn % "value" ) return tra->value;
			break;
	}
	
	// Finally, give the parent class a chance
	ret = nextBasenodeChunk(fieldIn, force, tra);
	if (!ret.IsEmpty())
		return ret;
	
	return "<span class=warning>Field not found: [{" + fieldIn + "}]</span>\n";
}

//---------------------------------------------------------------------------------------------------
SFBool CTransaction::setValueByName(const SFString& fieldName, const SFString& fieldValue)
{
	// EXISTING_CODE
	if ( fieldName % "timeStamp" )
	{
		timeStamp = toLong(fieldValue);
		m_transDate = dateFromTimeStamp(timeStamp);
		return TRUE;
	}
	// EXISTING_CODE

	switch (tolower(fieldName[0]))
	{
		case 'b':
			if ( fieldName % "blockHash" ) { blockHash = fieldValue; return TRUE; }
			if ( fieldName % "blockNumber" ) { blockNumber = toLong(fieldValue); return TRUE; }
			break;
		case 'c':
			if ( fieldName % "confirmations" ) { confirmations = toLong(fieldValue); return TRUE; }
			if ( fieldName % "contractAddress" ) { contractAddress = fieldValue; return TRUE; }
			if ( fieldName % "cumulativeGasUsed" ) { cumulativeGasUsed = fieldValue; return TRUE; }
			break;
		case 'f':
			if ( fieldName % "from" ) { from = toLower(fieldValue); return TRUE; }
			break;
		case 'g':
			if ( fieldName % "gas" ) { gas = fieldValue; return TRUE; }
			if ( fieldName % "gasPrice" ) { gasPrice = fieldValue; return TRUE; }
			if ( fieldName % "gasUsed" ) { gasUsed = fieldValue; return TRUE; }
			break;
		case 'h':
			if ( fieldName % "handle" ) { handle = toLong(fieldValue); return TRUE; }
			if ( fieldName % "hash" ) { hash = fieldValue; return TRUE; }
			break;
		case 'i':
			if ( fieldName % "input" ) { input = fieldValue; return TRUE; }
			if ( fieldName % "isError" ) { isError = toBool(fieldValue); return TRUE; }
			if ( fieldName % "isInternalTx" ) { isInternalTx = toBool(fieldValue); return TRUE; }
			break;
		case 'n':
			if ( fieldName % "nonce" ) { nonce = fieldValue; return TRUE; }
			break;
		case 't':
			if ( fieldName % "timeStamp" ) { timeStamp = toLong(fieldValue); return TRUE; }
			if ( fieldName % "to" ) { to = toLower(fieldValue); return TRUE; }
			if ( fieldName % "transactionIndex" ) { transactionIndex = toLong(fieldValue); return TRUE; }
			break;
		case 'v':
			if ( fieldName % "value" ) { value = fieldValue; return TRUE; }
			break;
		default:
			break;
	}
	return FALSE;
}

//---------------------------------------------------------------------------------------------------
void CTransaction::finishParse()
{
	// EXISTING_CODE
	m_transDate = dateFromTimeStamp(timeStamp);
	// EXISTING_CODE
}

//---------------------------------------------------------------------------------------------------
void CTransaction::Serialize(SFArchive& archive)
{
	if (!SerializeHeader(archive))
		return;

	if (archive.isReading())
	{
		archive >> handle;
		archive >> blockHash;
		archive >> blockNumber;
		archive >> confirmations;
		archive >> contractAddress;
		archive >> cumulativeGasUsed;
		archive >> from;
		archive >> gas;
		archive >> gasPrice;
		archive >> gasUsed;
		archive >> hash;
		archive >> input;
		archive >> isError;
		archive >> isInternalTx;
		archive >> nonce;
		archive >> timeStamp;
		archive >> to;
		archive >> transactionIndex;
		archive >> value;
		finishParse();
	} else
	{
		archive << handle;
		archive << blockHash;
		archive << blockNumber;
		archive << confirmations;
		archive << contractAddress;
		archive << cumulativeGasUsed;
		archive << from;
		archive << gas;
		archive << gasPrice;
		archive << gasUsed;
		archive << hash;
		archive << input;
		archive << isError;
		archive << isInternalTx;
		archive << nonce;
		archive << timeStamp;
		archive << to;
		archive << transactionIndex;
		archive << value;

	}
}

//---------------------------------------------------------------------------
void CTransaction::registerClass(void)
{
	static bool been_here=false;
	if (been_here) return;
	been_here=true;

	SFInt32 fieldNum=1000;
	ADD_FIELD(CTransaction, "schema",  T_NUMBER|TS_LABEL, ++fieldNum);
	ADD_FIELD(CTransaction, "deleted", T_RADIO|TS_LABEL,  ++fieldNum);
	ADD_FIELD(CTransaction, "handle", T_NUMBER|TS_LABEL,  ++fieldNum);
	ADD_FIELD(CTransaction, "blockHash", T_TEXT, ++fieldNum);
	ADD_FIELD(CTransaction, "blockNumber", T_NUMBER, ++fieldNum);
	ADD_FIELD(CTransaction, "confirmations", T_NUMBER, ++fieldNum);
	ADD_FIELD(CTransaction, "contractAddress", T_TEXT, ++fieldNum);
	ADD_FIELD(CTransaction, "cumulativeGasUsed", T_TEXT, ++fieldNum);
	ADD_FIELD(CTransaction, "from", T_TEXT, ++fieldNum);
	ADD_FIELD(CTransaction, "gas", T_TEXT, ++fieldNum);
	ADD_FIELD(CTransaction, "gasPrice", T_TEXT, ++fieldNum);
	ADD_FIELD(CTransaction, "gasUsed", T_TEXT, ++fieldNum);
	ADD_FIELD(CTransaction, "hash", T_TEXT, ++fieldNum);
	ADD_FIELD(CTransaction, "input", T_TEXT, ++fieldNum);
	ADD_FIELD(CTransaction, "isError", T_RADIO, ++fieldNum);
	ADD_FIELD(CTransaction, "isInternalTx", T_RADIO, ++fieldNum);
	ADD_FIELD(CTransaction, "nonce", T_TEXT, ++fieldNum);
	ADD_FIELD(CTransaction, "timeStamp", T_NUMBER, ++fieldNum);
	ADD_FIELD(CTransaction, "to", T_TEXT, ++fieldNum);
	ADD_FIELD(CTransaction, "transactionIndex", T_NUMBER, ++fieldNum);
	ADD_FIELD(CTransaction, "value", T_TEXT, ++fieldNum);

	// Hide our internal fields, user can turn them on if they like
	HIDE_FIELD(CTransaction, "schema");
	HIDE_FIELD(CTransaction, "deleted");
	HIDE_FIELD(CTransaction, "handle");

	// EXISTING_CODE
	ADD_FIELD(CTransaction, "date", T_DATE, ++fieldNum);
	ADD_FIELD(CTransaction, "ether", T_NUMBER, ++fieldNum);
	ADD_FIELD(CTransaction, "hitLimit", T_RADIO, ++fieldNum);
	ADD_FIELD(CTransaction, "inputLen", T_NUMBER, ++fieldNum);
	ADD_FIELD(CTransaction, "function", T_TEXT, ++fieldNum);
	ADD_FIELD(CTransaction, "recNum", T_NUMBER, ++fieldNum);

	// Hide fields we don't want to show by default
//	HIDE_FIELD(CTransaction, "date");
//	HIDE_FIELD(CTransaction, "ether");
	HIDE_FIELD(CTransaction, "confirmations");
//	HIDE_FIELD(CTransaction, "hitLimit");
//	HIDE_FIELD(CTransaction, "inputLen");
	HIDE_FIELD(CTransaction, "recNum");
	HIDE_FIELD(CTransaction, "function");
//	HIDE_FIELD(CTransaction, "isInternalTx");
//	HIDE_FIELD(CTransaction, "isError");
	// EXISTING_CODE
}

//---------------------------------------------------------------------------
int sortTransaction(const SFString& f1, const SFString& f2, const void *rr1, const void *rr2)
{
	CTransaction *g1 = (CTransaction*)rr1;
	CTransaction *g2 = (CTransaction*)rr2;

	SFString v1 = g1->getValueByName(f1);
	SFString v2 = g2->getValueByName(f1);
	SFInt32 s = v1.Compare(v2);
	if (s || f2.IsEmpty())
		return (int)s;

	v1 = g1->getValueByName(f2);
	v2 = g2->getValueByName(f2);
	return (int)v1.Compare(v2);
}
int sortTransactionByName(const void *rr1, const void *rr2) { return sortTransaction("tr_Name", "", rr1, rr2); }
int sortTransactionByID  (const void *rr1, const void *rr2) { return sortTransaction("transactionID", "", rr1, rr2); }

//---------------------------------------------------------------------------
SFString nextTransactionChunk_custom(const SFString& fieldIn, SFBool& force, const void *data)
{
	CTransactionNotify *tr = (CTransactionNotify*)data;
	const CTransaction *tra = tr->getDataPtr();
	switch (tolower(fieldIn[0]))
	{
		// EXISTING_CODE
		case 'd':
			if (fieldIn % "date") return tra->m_transDate.Format("%Y-%m-%d %H:%M:%S UTC");
		case 'e':
			if ( fieldIn % "ether" )
			{
				// Make sure the wei number is at least 18 characters long. Once it is,
				// reverse it, put a decimal at the 18th position, reverse it back,
				// strip leading '0's except the tens digit.
				SFString ether = tra->value;
				if (ether.GetLength()<18)
					ether = padLeft(tra->value,18).Substitute(" ","0");
				ether.Reverse();
				ether = ether.Left(18) + "." + ether.Mid(18,1000);
				ether.Reverse();
				ether = StripLeading(ether, '0');
				if (ether.startsWith('.'))
					ether = "0" + ether;
				return ether;
			}
			break;
		case 'f':
			if ( fieldIn % "function" ) return tra->inputToFunction();
			break;
		case 'h':
			if ( fieldIn % "hitLimit" ) return ((tra->gas == tra->gasUsed) ? "TRUE" : "FALSE");
			break;
		case 'i':
			if ( fieldIn % "inputLen" ) return asString(tra->input.GetLength());
			break;
		case 'r':
			if ( fieldIn % "recNum" ) return asString(tra->handle);
			break;
		// EXISTING_CODE
		default:
			break;
	}
	
#pragma unused(tr)
#pragma unused(tra)

	return EMPTY;
}

//---------------------------------------------------------------------------
SFBool CTransaction::handleCustomFormat(CExportContext& ctx, const SFString& fmtIn, void *data) const
{
	// EXISTING_CODE
	// EXISTING_CODE
	return FALSE;
}

//---------------------------------------------------------------------------
// EXISTING_CODE
////---------------------------------------------------------------------------
#include "slurp.h"
SFBool CTransaction::isFunction(const SFString& func) const
{
	if (func.IsEmpty())
		return FALSE;
	
	switch (func[0])
	{
		case 'a':
			if ( func == "approve" ) return input.startsWith( "0x095ea7b3" );
			else return FALSE;
			break;
			
		case 'c':
			if ( func == "checkProposalCode" ) return input.startsWith( "0xeceb2945" );
			else if ( func == "createTokenProxy" ) return input.startsWith( "0xbaac5300" );
			else return FALSE;
			break;
			
		case 'e':
			if ( func == "executeProposal" ) return input.startsWith( "0x237e9492" );
			else return FALSE;
			break;
			
		case 'g':
			if ( func == "getMyReward" ) return input.startsWith( "0xcc9ae3f6" );
			else return FALSE;
			break;
			
		case 'h':
			if ( func == "halveMinQuorum" ) return input.startsWith( "0x78524b2e" );
			else return FALSE;
			break;
			
		case 'n':
			if ( func == "newProposal" ) return input.startsWith( "0x612e45a3" );
			else if ( func == "none" )
			{
				SFString ret = inputToFunction();
				if (ret.ContainsAny("acghrstuv"))
					return FALSE;
				return (ret == " ");
			}
			else return FALSE;
			break;

		case 'p':
			if ( func == "payOut" ) return input.startsWith( "0x0221038a" );
			else return FALSE;
			break;
			
		case 'r':
			if ( func == "receiveEther" ) return input.startsWith( "0xa3912ec8" );
			else if ( func == "refund" ) return input.startsWith( "0x590e1ae3" );
			else if ( func == "retrieveDAOReward" ) return input.startsWith( "0xa1da2fb9" );
			else return FALSE;
			break;
			
		case 's':
			if ( func == "splitDAO" ) return input.startsWith( "0x82661dc4" );
			else return FALSE;
			break;
			
		case 't':
			if ( func == "transfer" ) return input.startsWith( "0xa9059cbb" );
			else if ( func == "transferFrom" ) return input.startsWith( "0x23b872dd" );
			else if ( func == "transferFromWithoutReward" ) return input.startsWith( "0xdbde1988" );
			else if ( func == "transferWithoutReward" ) return input.startsWith( "0x4e10c3ee" );
			else return FALSE;
			break;
			
		case 'u':
			if ( func == "unblockMe" ) return input.startsWith( "0x2632bf20" );
			else return FALSE;
			break;
			
		case 'v':
			if ( func == "vote" ) return input.startsWith( "0xc9d27afe" );
			else return FALSE;
			break;
	}
	
	return FALSE;
}

#define grabPart(a,b)       StripLeading((a).Mid(64*(b),64),'0')
#define grabBigNum(a,b)     strtoull((const char*)grabPart(a,b),NULL,16)
#define toAddr(a,b)         "0x"+grabPart(a,b)
#define toBigNum(a,b)       asStringULL(grabBigNum(a,b))
#define toBigNum3(a,b)      padNum3(grabBigNum(a,b))
#define toBool(a,b)         (grabBigNum(a,b)?"true":"false")
#define toVote(a,b)         (grabBigNum(a,b)?"Yea":"Nay")
#define theRest(a,b)        (a).Mid(64*(b),(a).GetLength());

//---------------------------------------------------------------------------
SFString parseParams(const SFString& which, const SFString& params)
{
	if (which=="approve")
	{
		//function approve(address _spender, uint256 _amount) returns (bool success) {  discuss
		return which + "|" + toAddr(params,0) + "|" + toBigNum(params,1);

	} else if (which=="splitDAO")
	{
		//function splitDAO(uint _proposalID, address _newCurator)
		return which + "|" + toBigNum3(params,0) + "|" + toAddr(params,1);

	} else if (which=="createTokenProxy")
	{
		//function createTokenProxy(address _tokenHolder)
		return which + "|" + toAddr(params,0);

	} else if (which=="transferFrom")
	{
		//function transferFrom(address _from, address _to, uint256 _amount)
		return which + "|" + toAddr(params,0) + "|" + toAddr(params,1) + "|" + toBigNum(params,2);

	} else if (which=="transfer")
	{
		//function transfer(address _to, uint256 _amount)
		return which + "|" + toAddr(params,0) + "|" + toBigNum(params,1);

	} else if (which=="getMyReward")
	{
		//function getMyReward()
		return which;
	
	} else if (which=="payOut")
	{
		//function payOut(address _recipient, uint _amount)
		return which + "|" + toAddr(params,0) + "|" + toBigNum(params,1);

	} else if (which=="receiveEther")
	{
		//function receiveEther()
		return which;
	
	} else if (which=="vote")
	{
		//function vote(uint _proposalID, bool _supportsProposal)
		return which + "|" + toBigNum3(params,0) + "|" + toVote(params,1);
	
	} else if (which=="executeProposal")
	{
		//function executeProposal(uint _proposalID, bytes _transactionData)
		return which + "|" + toBigNum3(params,0) + "|" + theRest(params,1);

	} else if (which=="newProposal")
	{
		//function newProposal(address _recipient, uint _amount, string _description, bytes _transactionData, uint _debatingPeriod, bool _newCurator)
		SFString recip = toAddr(params, 0);
		SFString amt = toBigNum(params,1);
		SFString part4 =      StripLeading(params.Right(128).Left(64), '0');
		SFString part5 =      StripLeading(params.Right(64),'0');
		SFString part3b = params;
		part3b.Replace(recip,"");
		part3b.Replace(amt,"");
		part3b.ReplaceReverse(part5,"");
		part3b.ReplaceReverse(part4,"");
		part3b = StripLeading(part3b,'0');
		SFString part3a = toAddr(part3b,0);
		part3b.Replace(part3a.Substitute("0x",""),"");
		return which + "|" + recip + "|" + amt + "|" + part3a + "|" + part4 + "|" + part5 + "|" + part3b;

	}

	return which;
}

//---------------------------------------------------------------------------
SFString CTransaction::inputToFunction(void) const
{
	if (input.GetLength()<10)
		return " ";

	switch (input[2])
	{
		case '0': if (input.startsWith( "0x095ea7b3" )) return parseParams("approve",                   input.Mid(10,input.GetLength()));
		     else if (input.startsWith( "0x0221038a" )) return parseParams("payOut",                    input.Mid(10,input.GetLength())); break;

		case '2': if (input.startsWith( "0x237e9492" )) return parseParams("executeProposal",           input.Mid(10,input.GetLength()));
		     else if (input.startsWith( "0x23b872dd" )) return parseParams("transferFrom",              input.Mid(10,input.GetLength()));
		     else if (input.startsWith( "0x2632bf20" )) return parseParams("unblockMe",                 input.Mid(10,input.GetLength())); break;

		case '4': if (input.startsWith( "0x4e10c3ee" )) return parseParams("transferWithoutReward",     input.Mid(10,input.GetLength())); break;

		case '5': if (input.startsWith( "0x590e1ae3" )) return parseParams("refund",                    input.Mid(10,input.GetLength())); break;

		case '6': if (input.startsWith( "0x612e45a3" )) return parseParams("newProposal",               input.Mid(10,input.GetLength())); break;

		case '7': if (input.startsWith( "0x78524b2e" )) return parseParams("halveMinQuorum",            input.Mid(10,input.GetLength())); break;

		case '8': if (input.startsWith( "0x82661dc4" )) return parseParams("splitDAO",                  input.Mid(10,input.GetLength())); break;

		case 'a': if (input.startsWith( "0xa1da2fb9" )) return parseParams("retrieveDAOReward",         input.Mid(10,input.GetLength()));
		     else if (input.startsWith( "0xa3912ec8" )) return parseParams("receiveEther",              input.Mid(10,input.GetLength()));
		     else if (input.startsWith( "0xa9059cbb" )) return parseParams("transfer",                  input.Mid(10,input.GetLength())); break;

		case 'b': if (input.startsWith( "0xbaac5300" )) return parseParams("createTokenProxy",          input.Mid(10,input.GetLength())); break;

		case 'c': if (input.startsWith( "0xc9d27afe" )) return parseParams("vote",                      input.Mid(10,input.GetLength()));
		     else if (input.startsWith( "0xcc9ae3f6" )) return parseParams("getMyReward",               input.Mid(10,input.GetLength())); break;

		case 'd': if (input.startsWith( "0xdbde1988" )) return parseParams("transferFromWithoutReward", input.Mid(10,input.GetLength())); break;

		case 'e': if (input.startsWith( "0xeceb2945" )) return parseParams("checkProposalCode",         input.Mid(10,input.GetLength())); break;
	}

	for (int i=0;i<nFunctions;i++)
		if (input.Mid(2,8) == funcTable[i].encoding)
			return funcTable[i].Format("[{NAME}]");

	return " ";
}

//---------------------------------------------------------------------------
int sortTransactionsForWrite(const void *rr1, const void *rr2)
{
	CTransaction *tr1 = (CTransaction*)rr1;
	CTransaction *tr2 = (CTransaction*)rr2;

	SFInt32 ret;
	ret = tr1->timeStamp - tr2->timeStamp;         if (ret!=0) return (int)ret;
	ret = tr1->from.Compare(tr2->from);            if (ret!=0) return (int)ret;
	ret = toLong(tr1->nonce) - toLong(tr2->nonce); if (ret!=0) return (int)ret;

	return (int)tr1->hash.Compare(tr2->hash);
}
// EXISTING_CODE
