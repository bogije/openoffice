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



#ifndef _XMLOFF_XMLEMBEDDEDOBJECTEXPORTFILTER_HXX
#define _XMLOFF_XMLEMBEDDEDOBJECTEXPORTFILTER_HXX

#ifndef _COM_SUN_STAR_XML_SAX_XEXTENDEDDOCUMENTHANDLER_HPP_
#include <com/sun/star/xml/sax/XExtendedDocumentHandler.hpp>
#endif
#ifndef _COM_SUN_STAR_LANG_XINITIALIZATION_HPP_
#include <com/sun/star/lang/XInitialization.hpp>
#endif
#ifndef _COM_SUN_STAR_LANG_XSERVICEINFO_HPP_
#include <com/sun/star/lang/XServiceInfo.hpp>
#endif

#ifndef _CPPUHELPER_IMPLBASE3_HXX_ 
#include <cppuhelper/implbase3.hxx>
#endif
namespace binfilter {

class XMLEmbeddedObjectExportFilter : public ::cppu::WeakImplHelper3<
			 ::com::sun::star::xml::sax::XExtendedDocumentHandler,
			 ::com::sun::star::lang::XServiceInfo,
			 ::com::sun::star::lang::XInitialization>
{
	::com::sun::star::uno::Reference<
		::com::sun::star::xml::sax::XDocumentHandler > xHandler;
	::com::sun::star::uno::Reference<
		::com::sun::star::xml::sax::XExtendedDocumentHandler > xExtHandler;

public:
	XMLEmbeddedObjectExportFilter( const ::com::sun::star::uno::Reference<
		::com::sun::star::xml::sax::XDocumentHandler > & rHandler ) throw();
	virtual ~XMLEmbeddedObjectExportFilter () throw();

	// ::com::sun::star::xml::sax::XDocumentHandler
	virtual void SAL_CALL startDocument(void)
		throw( ::com::sun::star::xml::sax::SAXException, ::com::sun::star::uno::RuntimeException );
	virtual void SAL_CALL endDocument(void)
		throw( ::com::sun::star::xml::sax::SAXException, ::com::sun::star::uno::RuntimeException );
	virtual void SAL_CALL startElement(const ::rtl::OUString& aName,
							  const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList > & xAttribs)
		throw( ::com::sun::star::xml::sax::SAXException, ::com::sun::star::uno::RuntimeException );
	virtual void SAL_CALL endElement(const ::rtl::OUString& aName)
		throw( ::com::sun::star::xml::sax::SAXException, ::com::sun::star::uno::RuntimeException );
	virtual void SAL_CALL characters(const ::rtl::OUString& aChars)
		throw( ::com::sun::star::xml::sax::SAXException, ::com::sun::star::uno::RuntimeException );
	virtual void SAL_CALL ignorableWhitespace(const ::rtl::OUString& aWhitespaces)
		throw( ::com::sun::star::xml::sax::SAXException, ::com::sun::star::uno::RuntimeException );
	virtual void SAL_CALL processingInstruction(const ::rtl::OUString& aTarget,
									   const ::rtl::OUString& aData)
		throw( ::com::sun::star::xml::sax::SAXException, ::com::sun::star::uno::RuntimeException );
	virtual void SAL_CALL setDocumentLocator(const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XLocator > & xLocator)
		throw( ::com::sun::star::xml::sax::SAXException, ::com::sun::star::uno::RuntimeException );

	// ::com::sun::star::xml::sax::XExtendedDocumentHandler
	virtual void SAL_CALL startCDATA(void) throw( ::com::sun::star::xml::sax::SAXException, ::com::sun::star::uno::RuntimeException );
	virtual void SAL_CALL endCDATA(void) throw( ::com::sun::star::uno::RuntimeException );
	virtual void SAL_CALL comment(const ::rtl::OUString& sComment)
		throw( ::com::sun::star::xml::sax::SAXException, ::com::sun::star::uno::RuntimeException );
	virtual void SAL_CALL allowLineBreak(void)
		throw( ::com::sun::star::xml::sax::SAXException, ::com::sun::star::uno::RuntimeException );
	virtual void SAL_CALL unknown(const ::rtl::OUString& sString)
		throw( ::com::sun::star::xml::sax::SAXException, ::com::sun::star::uno::RuntimeException );

	// XInitialization
    virtual void SAL_CALL initialize( const ::com::sun::star::uno::Sequence< ::com::sun::star::uno::Any >& aArguments ) throw(::com::sun::star::uno::Exception, ::com::sun::star::uno::RuntimeException);

	// XServiceInfo
    virtual ::rtl::OUString SAL_CALL getImplementationName(  ) throw(::com::sun::star::uno::RuntimeException);
    virtual sal_Bool SAL_CALL supportsService( const ::rtl::OUString& ServiceName ) throw(::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL getSupportedServiceNames(  ) throw(::com::sun::star::uno::RuntimeException);

};

}//end of namespace binfilter
#endif	//  _XMLOFF_XMLEMBEDDEDOBJECTEXPORTFILTER_HXX
