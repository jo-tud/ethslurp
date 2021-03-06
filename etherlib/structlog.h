#ifndef _STRUCTLOG_H_
#define _STRUCTLOG_H_
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
#include "utillib.h"
#include "ethtypes.h"

//--------------------------------------------------------------------------
class CStructLog;
typedef SFArrayBase<CStructLog>         CStructLogArray;
typedef SFList<CStructLog*>             CStructLogList;
typedef CNotifyClass<const CStructLog*> CStructLogNotify;
typedef SFUniqueList<CStructLog*>       CStructLogListU;

//---------------------------------------------------------------------------
extern int sortStructlog        (const SFString& f1, const SFString& f2, const void *rr1, const void *rr2);
extern int sortStructlogByName  (const void *rr1, const void *rr2);
extern int sortStructlogByID    (const void *rr1, const void *rr2);
extern int isDuplicateStructlog (const void *rr1, const void *rr2);

// EXISTING_CODE
// EXISTING_CODE

//--------------------------------------------------------------------------
class CStructLog : public CBaseNode
{
public:
	SFInt32 depth;
	SFBool error;
	SFInt32 gas;
	SFInt32 gasCost;
	SFStringArray memory;
	SFString op;
	SFInt32 pc;
	SFStringArray stack;
	SFStringArray storage;

public:
					CStructLog  (void);
					CStructLog  (const CStructLog& st);
				   ~CStructLog  (void);
	CStructLog&	operator= 		(const CStructLog& st);

	DECLARE_NODE (CStructLog);

	// EXISTING_CODE
	// EXISTING_CODE

protected:
	void			Clear      		(void);
	void			Init      		(void);
	void			Copy      		(const CStructLog& st);
	SFBool                  readBackLevel           (SFArchive& archive);

	// EXISTING_CODE
	// EXISTING_CODE
};

//--------------------------------------------------------------------------
inline CStructLog::CStructLog(void)
{
	Init();
	// EXISTING_CODE
	// EXISTING_CODE
}

//--------------------------------------------------------------------------
inline CStructLog::CStructLog(const CStructLog& st)
{
	// EXISTING_CODE
	// EXISTING_CODE
	Copy(st);
}

// EXISTING_CODE
// EXISTING_CODE

//--------------------------------------------------------------------------
inline CStructLog::~CStructLog(void)
{
	Clear();
	// EXISTING_CODE
	// EXISTING_CODE
}

//--------------------------------------------------------------------------
inline void CStructLog::Clear(void)
{
	// EXISTING_CODE
	// EXISTING_CODE
}

//--------------------------------------------------------------------------
inline void CStructLog::Init(void)
{
	CBaseNode::Init();

	depth = 0;
	error = 0;
	gas = 0;
	gasCost = 0;
//	memory = ??; /* unknown type: SFStringArray */
	op = EMPTY;
	pc = 0;
//	stack = ??; /* unknown type: SFStringArray */
//	storage = ??; /* unknown type: SFStringArray */

	// EXISTING_CODE
	// EXISTING_CODE
}

//--------------------------------------------------------------------------
inline void CStructLog::Copy(const CStructLog& st)
{
	Clear();

	CBaseNode::Copy(st);
	depth = st.depth;
	error = st.error;
	gas = st.gas;
	gasCost = st.gasCost;
	memory = st.memory;
	op = st.op;
	pc = st.pc;
	stack = st.stack;
	storage = st.storage;

	// EXISTING_CODE
	// EXISTING_CODE
	finishParse();
}

//--------------------------------------------------------------------------
inline CStructLog& CStructLog::operator=(const CStructLog& st)
{
	Copy(st);
	// EXISTING_CODE
	// EXISTING_CODE
	return *this;
}

//---------------------------------------------------------------------------
inline SFString CStructLog::getValueByName(const SFString& fieldName) const
{
	// EXISTING_CODE
	// EXISTING_CODE
	return Format("[{"+toUpper(fieldName)+"}]");
}

//---------------------------------------------------------------------------
extern SFString nextStructlogChunk(const SFString& fieldIn, SFBool& force, const void *data);

//---------------------------------------------------------------------------
IMPLEMENT_ARCHIVE_ARRAY(CStructLogArray);
IMPLEMENT_ARCHIVE_LIST(CStructLogList);

//---------------------------------------------------------------------------
extern SFString nextStructlogChunk_custom(const SFString& fieldIn, SFBool& force, const void *data);

//---------------------------------------------------------------------------
// EXISTING_CODE
// EXISTING_CODE

#endif
