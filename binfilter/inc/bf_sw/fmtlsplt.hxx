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


#ifndef _FMTTSPLT_HXX
#define _FMTTSPLT_HXX

#include <bf_svtools/bf_solar.h>

#ifndef _SFXENUMITEM_HXX //autogen
#include <bf_svtools/eitem.hxx>
#endif
#ifndef _FORMAT_HXX //autogen
#include <format.hxx>
#endif
class IntlWrapper; 
namespace binfilter {


class SwFmtLayoutSplit : public SfxBoolItem
{
public:
	SwFmtLayoutSplit( BOOL bSplit = TRUE ) : SfxBoolItem( RES_LAYOUT_SPLIT, bSplit ) {}

	// "pure virtual Methoden" vom SfxPoolItem
    virtual SfxPoolItem*    Clone( SfxItemPool *pPool = 0 ) const;
    virtual SfxPoolItem*    Create(SvStream &, USHORT) const;
    virtual SvStream&       Store(SvStream &, USHORT nItemVersion ) const;
	virtual USHORT			 GetVersion( USHORT nFFVer ) const;
};

#if !(defined(MACOSX) && ( __GNUC__ < 3 ))
// GrP moved to gcc_outl.cxx; revisit with gcc3
inline const SwFmtLayoutSplit &SwAttrSet::GetLayoutSplit(BOOL bInP) const
	{ return (const SwFmtLayoutSplit&)Get( RES_LAYOUT_SPLIT,bInP); }

inline const SwFmtLayoutSplit &SwFmt::GetLayoutSplit(BOOL bInP) const
	{ return aSet.GetLayoutSplit(bInP); }
#endif

} //namespace binfilter
#endif

