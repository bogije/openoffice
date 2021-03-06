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


#ifndef DBACCESS_CORE_API_ROWSETROW_HXX
#define DBACCESS_CORE_API_ROWSETROW_HXX

#ifndef _VOS_REF_HXX_
#include <vos/ref.hxx>
#endif
#ifndef _CONNECTIVITY_COMMONTOOLS_HXX_
#include <connectivity/CommonTools.hxx>
#endif
#ifndef _CONNECTIVITY_FILE_VALUE_HXX_
#include "connectivity/FValue.hxx"
#endif
#ifndef _COMPHELPER_TYPES_HXX_
#include <comphelper/types.hxx>
#endif

namespace dbaccess
{
	typedef connectivity::ORowVector< connectivity::ORowSetValue >	ORowSetValueVector;
	typedef ::vos::ORef< ORowSetValueVector >						ORowSetRow;
	typedef ::std::vector< ORowSetRow >								ORowSetMatrix;

	class ORowSetOldRowHelper
	{
		oslInterlockedCount			m_refCount;
		ORowSetRow					m_aRow;

		ORowSetOldRowHelper& operator=(const ORowSetOldRowHelper& _rRH);
		ORowSetOldRowHelper(const ORowSetOldRowHelper& _rRh);
	public:
		ORowSetOldRowHelper() : m_refCount(0){}
		ORowSetOldRowHelper(const ORowSetRow& _rRow) 
			: m_refCount(0)
			, m_aRow(_rRow)
		{}
//		ORowSetOldRowHelper(const ORowSetOldRowHelper& _rRh)
//			: m_refCount(0)
//			, m_aRow(_rRh.m_aRow)
//		{}

		void acquire()
		{
			osl_incrementInterlockedCount( &m_refCount );
		}
		void release()
		{
			if (! osl_decrementInterlockedCount( &m_refCount ))
				delete this;
		}
		inline ORowSetRow getRow() const { return m_aRow; }
		inline void clearRow() { m_aRow = NULL; }
		inline void setRow(const ORowSetRow& _rRow) { m_aRow = _rRow; }
	};

	typedef ::vos::ORef< ORowSetOldRowHelper >	TORowSetOldRowHelperRef;

	class ORowSetValueCompare
	{
		const ::com::sun::star::uno::Any& m_rAny;
	public:
		ORowSetValueCompare(const ::com::sun::star::uno::Any& _rAny) : m_rAny(_rAny){}

		sal_Bool operator ()(const ORowSetRow& _rRH)
		{
			switch((_rRH->get())[0].getTypeKind())
			{
				case ::com::sun::star::sdbc::DataType::TINYINT:
				case ::com::sun::star::sdbc::DataType::SMALLINT:
				case ::com::sun::star::sdbc::DataType::INTEGER:
					return comphelper::getINT32(m_rAny) == (sal_Int32)(_rRH->get())[0];
				default:
				{
					::com::sun::star::uno::Sequence<sal_Int8> aSeq;
					m_rAny >>= aSeq;
					return aSeq == (_rRH->get())[0];
				}
			}
		}
	};
}
#endif // DBACCESS_CORE_API_ROWSETROW_HXX

