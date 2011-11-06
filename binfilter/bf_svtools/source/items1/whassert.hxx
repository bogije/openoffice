/**************************************************************
 * 
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 * 
 *   http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 * 
 *************************************************************/


#ifndef _SFX_WHASSERT_HXX
#define _SFX_WHASSERT_HXX

#ifndef _TOOLS_DEBUG_HXX //autogen
#include <tools/debug.hxx>
#endif
#ifndef _STRING_HXX //autogen
#include <tools/string.hxx>
#endif

namespace binfilter
{

//------------------------------------------------------------------------

#ifdef DBG_UTIL
#define SFX_ASSERT( bCondition, nId, sMessage ) 							\
{																			\
	if ( DbgIsAssert() )													\
	{																		\
		if ( !(bCondition) )												\
		{																	\
			ByteString aMsg( sMessage );									\
			aMsg.Append(RTL_CONSTASCII_STRINGPARAM("\nwith Id/Pos: "));     \
			aMsg += ByteString::CreateFromInt32( nId );						\
			DbgOut( aMsg.GetBuffer(), DBG_OUT_ERROR, __FILE__, __LINE__);	\
		}																	\
	}																		\
}
#else
#define SFX_ASSERT( bCondition, nId, sMessage )
#endif

}

#endif
