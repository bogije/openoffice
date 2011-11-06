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



#ifndef _XIMPBODY_HXX
#define _XIMPBODY_HXX

#ifndef _XMLOFF_XMLICTXT_HXX
#include "xmlictxt.hxx"
#endif

#ifndef _SDXMLIMP_IMPL_HXX
#include "sdxmlimp_impl.hxx"
#endif

#ifndef _XMLOFF_NMSPMAP_HXX
#include "nmspmap.hxx"
#endif

#ifndef _XIMPPAGE_HXX
#include "ximppage.hxx"
#endif
namespace binfilter {

//////////////////////////////////////////////////////////////////////////////
// draw:page context

class SdXMLDrawPageContext : public SdXMLGenericPageContext
{
	::rtl::OUString				maName;
	::rtl::OUString				maStyleName;
	::rtl::OUString				maMasterPageName;
	::rtl::OUString				maHREF;

public:
	SdXMLDrawPageContext( SdXMLImport& rImport, USHORT nPrfx,
		const ::rtl::OUString& rLocalName, 
		const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList>& xAttrList,
		::com::sun::star::uno::Reference< ::com::sun::star::drawing::XShapes >& rShapes);
	virtual ~SdXMLDrawPageContext();

	virtual SvXMLImportContext *CreateChildContext( 
		USHORT nPrefix, const ::rtl::OUString& rLocalName,
		const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList>& xAttrList );
	virtual void EndElement();

};

//////////////////////////////////////////////////////////////////////////////
// office:body context

class SdXMLBodyContext : public SvXMLImportContext
{
	const SdXMLImport& GetSdImport() const { return (const SdXMLImport&)GetImport(); }
	SdXMLImport& GetSdImport() { return (SdXMLImport&)GetImport(); }

public:
	SdXMLBodyContext( SdXMLImport& rImport, USHORT nPrfx, const ::rtl::OUString& rLocalName );
	virtual ~SdXMLBodyContext();

	virtual SvXMLImportContext *CreateChildContext( 
		USHORT nPrefix, const ::rtl::OUString& rLocalName, 
		const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList>& xAttrList );
};


}//end of namespace binfilter
#endif	//  _XIMPBODY_HXX
