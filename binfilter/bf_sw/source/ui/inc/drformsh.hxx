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



#ifndef _SWDRWFORMSH_HXX
#define _SWDRWFORMSH_HXX

#include "drwbassh.hxx"
namespace binfilter {

class SdrObject;
class SwDrawBaseShell;

class SwDrawFormShell: public SwDrawBaseShell
{
public:
	SFX_DECL_INTERFACE(SW_DRAWFORMSHELL);

	SwDrawFormShell(SwView &rView):SwDrawBaseShell(rView){DBG_BF_ASSERT(0, "STRIP");} ;//STRIP001 				SwDrawFormShell(SwView &rView);

};

} //namespace binfilter
#endif
