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



#ifndef ARY_IDL_IK_SERVICE_HXX
#define ARY_IDL_IK_SERVICE_HXX



// USED SERVICES
    // BASE CLASSES
#include <ary/idl/ik_ce.hxx>
    // COMPONENTS
    // PARAMETERS


namespace ary
{
namespace idl
{

namespace ifc_service
{

using ifc_ce::Dyn_CeIterator;
using ifc_ce::DocText;


struct attr: public ifc_ce::attr
{
    static void         Get_IncludedServices(
                            Dyn_StdConstIterator<CommentedRelation> &
                                                o_result,
                            const CodeEntity &  i_ce );
    static void         Get_ExportedInterfaces(
                            Dyn_StdConstIterator<CommentedRelation> &
                                                o_result,
                            const CodeEntity &  i_ce );
    static void         Get_Properties(
                            Dyn_CeIterator &    o_result,
                            const CodeEntity &  i_ce );
};

struct xref : public ifc_ce::xref
{   
    static void         Get_IncludingServices(
                            Dyn_CeIterator &    o_result,
                            const CodeEntity &  i_ce );
    static void         Get_InstantiatingSingletons(
                            Dyn_CeIterator &    o_result,
                            const CodeEntity &  i_ce );
};

struct doc : public ifc_ce::doc
{
};
                     
                     
}   // namespace ifc_service                     
                    
}   // namespace idl
}   // namespace ary


#endif
