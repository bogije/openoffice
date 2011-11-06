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



#ifndef _EXTENSIONS_DBP_CONTROLWIZARD_HXX
#define _EXTENSIONS_DBP_CONTROLWIZARD_HXX

#include <svtools/wizardmachine.hxx>
#include <com/sun/star/lang/XMultiServiceFactory.hpp>
#include <com/sun/star/form/FormComponentType.hpp>
#include <com/sun/star/sdbc/XConnection.hpp>
#include <com/sun/star/task/XInteractionHandler.hpp>
#include <vcl/fixed.hxx>
#include <vcl/edit.hxx>
#ifndef _SV_BUTTON_HXX 
#include <vcl/button.hxx>
#endif
#include <vcl/lstbox.hxx>
#include <vcl/combobox.hxx>
#include "dbptypes.hxx"
#ifndef _EXTENSIONS_DBP_DBPRESID_HRC_
#include "dbpresid.hrc"
#endif
#include "componentmodule.hxx"
#include "wizardcontext.hxx"

class ResId;
//.........................................................................
namespace dbp
{
//.........................................................................

	//=====================================================================
	//= OControlWizardSettings
	//=====================================================================
	struct OControlWizardSettings
	{
		String		sControlLabel;
	};

	//=====================================================================
	//= OControlWizardPage
	//=====================================================================
	class OControlWizard;
	typedef ::svt::OWizardPage OControlWizardPage_Base;
	class OControlWizardPage : public OControlWizardPage_Base
	{
	protected:
		FixedLine*		m_pFormSettingsSeparator;
		FixedText*		m_pFormDatasourceLabel;
		FixedText*		m_pFormDatasource;
		FixedText*		m_pFormContentTypeLabel;
		FixedText*		m_pFormContentType;
		FixedText*		m_pFormTableLabel;
		FixedText*		m_pFormTable;

	protected:
		OControlWizard*					getDialog();
		const OControlWizard*			getDialog() const;
		const OControlWizardContext&	getContext();
		sal_Bool						updateContext();
		void							setFormConnection(const ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XConnection >& _rxConn, sal_Bool _bAutoDispose = sal_True );
		::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XConnection >
										getFormConnection() const;

	public:
		OControlWizardPage( OControlWizard* _pParent, const ResId& _rResId );
		~OControlWizardPage();

	protected:
		void fillListBox(
			ListBox& _rList,
			const ::com::sun::star::uno::Sequence< ::rtl::OUString >& _rItems,
			sal_Bool _bClear = sal_True);
		void fillListBox(
			ComboBox& _rList,
			const ::com::sun::star::uno::Sequence< ::rtl::OUString >& _rItems,
			sal_Bool _bClear = sal_True);

	protected:
		void enableFormDatasourceDisplay();
		void adjustControlForNoDSDisplay(Control* _pControl, sal_Bool bConstLowerDistance = sal_False);

	protected:
		// OWizardPage overridables
		virtual void		initializePage();
	};

	struct OAccessRegulator;
	//=====================================================================
	//= OControlWizard
	//=====================================================================
	typedef ::svt::OWizardMachine OControlWizard_Base;
	class OControlWizard : public OControlWizard_Base
	{
	private:
		OControlWizardContext	m_aContext;

	protected:
		::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >
					m_xORB;

	public:
		OControlWizard(
			Window* _pParent,
			const ResId& _rId,
			const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet >& _rxObjectModel,
			const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >& _rxORB
		);
		~OControlWizard();

		// make the some base class methods public
		sal_Bool	travelNext() { return OControlWizard_Base::travelNext(); }

	public:
		::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >
			getServiceFactory() const { return m_xORB; }

		const OControlWizardContext&	getContext() const { return m_aContext; }
		sal_Bool						updateContext(const OAccessRegulator&);
		void							setFormConnection(const OAccessRegulator&, const ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XConnection >& _rxConn, sal_Bool _bAutoDispose = sal_True );
		::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XConnection >
										getFormConnection(const OAccessRegulator&) const;

        /** returns the com.sun.star.task.InteractionHandler
            @param  _pWindow    The window will be used when an error message has to be shown.
        */
        ::com::sun::star::uno::Reference< ::com::sun::star::task::XInteractionHandler > getInteractionHandler(Window* _pWindow) const;

	protected:
		// initialize the derivees settings (which have to be derived from OControlWizardSettings)
		// with some common data extracted from the control model
		void initControlSettings(OControlWizardSettings* _pSettings);
		// commit the control-relevant settings
		void commitControlSettings(OControlWizardSettings* _pSettings);

		sal_Bool needDatasourceSelection();

        ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XConnection >
										getFormConnection() const;

		virtual sal_Bool approveControl(sal_Int16 _nClassId) = 0;

		// ModalDialog overridables
		virtual short	Execute();

	private:
		sal_Bool initContext();

		void implGetDSContext();
		void implDetermineForm();
		void implDeterminePage();
		void implDetermineShape();

		// made private. Not to be used by derived (or external) classes
		virtual void ActivatePage();
	};

//.........................................................................
}	// namespace dbp
//.........................................................................

#endif // _EXTENSIONS_DBP_CONTROLWIZARD_HXX

