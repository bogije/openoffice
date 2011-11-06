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



#ifndef _XMLOFF_FORMLAYERIMPORT_HXX_
#define _XMLOFF_FORMLAYERIMPORT_HXX_

#ifndef _VOS_REFERNCE_HXX_
#include <vos/refernce.hxx>
#endif
#ifndef _COM_SUN_STAR_DRAWING_XDRAWPAGE_HPP_
#include <com/sun/star/drawing/XDrawPage.hpp>
#endif
#ifndef _COM_SUN_STAR_XML_SAX_XATTRIBUTELIST_HPP_
#include <com/sun/star/xml/sax/XAttributeList.hpp>
#endif
#ifndef _COM_SUN_STAR_BEANS_XPROPERTYSET_HPP_
#include <com/sun/star/beans/XPropertySet.hpp>
#endif
#ifndef _VOS_REF_HXX_
#include <vos/ref.hxx>
#endif
#ifndef _XMLOFF_XMLIMPPR_HXX
#include <bf_xmloff/xmlimppr.hxx>
#endif
namespace binfilter {

class SvXMLImport;
class SvXMLImportContext;
class SvXMLStylesContext;
class XMLPropStyleContext;

//.........................................................................
namespace xmloff
{
//.........................................................................

	//=====================================================================
	//= OFormLayerXMLImport
	//=====================================================================
	class OFormLayerXMLImport_Impl;
	/** allows you to import a &lt;form:form&gt; element
	*/
	class OFormLayerXMLImport
				:public ::vos::OReference
	{
		OFormLayerXMLImport_Impl*	m_pImpl;

	public:
		OFormLayerXMLImport(SvXMLImport& _rImporter);
		~OFormLayerXMLImport();

		/** retrieves the property mapper form form related auto styles.
		*/
		::vos::ORef< SvXMLImportPropertyMapper >
				getStylePropertyMapper() const;

		/** start importing the forms of the given page

			<p>starting the import of a new page (by using this method) invalidates the current page position
			you may have set with <method>seekPage</method>.</p>

			@see endPage
			@see seekPage
		*/
		void startPage(
			const ::com::sun::star::uno::Reference< ::com::sun::star::drawing::XDrawPage >& _rxDrawPage);

		/** creates an import context for the office:forms element
		*/
		SvXMLImportContext* createOfficeFormsContext(
			SvXMLImport& _rImport,
			sal_uInt16 _nPrefix,
			const ::rtl::OUString& _rLocalName);

		/** create an <type>SvXMLImportContext</type> instance which is able to import the &lt;form:form&gt;
			element.

			<p>You must have called <method>startPage</method> before you can create such an import context.</p>

			@see startPage
			@see endPage
		*/
		SvXMLImportContext* createContext(
			const sal_uInt16 _nPrefix,
			const ::rtl::OUString& _rLocalName,
			const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList >& _rxAttribs);

		/**
		*/
		XMLPropStyleContext* createControlStyleContext(
			sal_uInt16 _nPrefix, 
			const ::rtl::OUString& _rLocalName,
			const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList >& _rxAttrList,
			SvXMLStylesContext& _rParentStyles,
			sal_uInt16 _nFamily = 0,
		    sal_Bool _bDefaultStyle = sal_False
		);

		/** lookup a control given by id.

			<p>The control must be part of the page which is currently beeing imported, or you must have used
			seekPage for the page which the control belongs to.</p>

			<p>(And, of course, the control must have been imported already at the moment you call this.)</p>

			@see startPage
			@see seekPage
		*/
		::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet >
				lookupControl(const ::rtl::OUString& _rId);

		/** end importing the forms of the current page

			<p>You must call this method if you want the import to be finished correctly. Without calling
			it, you will lose information.</p>

			@see startPage
			@see seekPage
		*/
		void endPage();

		/** announces the auto-style context to the form importer
		*/
		void setAutoStyleContext(SvXMLStylesContext* _pNewContext);

		/** sets the given number style on the given control
			@param _rxControlModel
				the control model which's style is to be set
			@param _rControlNumerStyleName
				the style name for the control's number style
		*/
		void applyControlNumberStyle(
			const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet >& _rxControlModel,
			const ::rtl::OUString& _rControlNumerStyleName
		);

        /** to be called when the document has been completely imported

            <p>For some documents (currently: only some spreadsheet documents) it's necessary
            do to a post processing, since not all information from the file can be processed
            if the document is not completed, yet.</p>
        */
        void documentDone( );
	};

//.........................................................................
}	// namespace xmloff
//.........................................................................

}//end of namespace binfilter
#endif // _XMLOFF_FORMLAYERIMPORT_HXX_

