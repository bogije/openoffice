#**************************************************************
#  
#  Licensed to the Apache Software Foundation (ASF) under one
#  or more contributor license agreements.  See the NOTICE file
#  distributed with this work for additional information
#  regarding copyright ownership.  The ASF licenses this file
#  to you under the Apache License, Version 2.0 (the
#  "License"); you may not use this file except in compliance
#  with the License.  You may obtain a copy of the License at
#  
#    http://www.apache.org/licenses/LICENSE-2.0
#  
#  Unless required by applicable law or agreed to in writing,
#  software distributed under the License is distributed on an
#  "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
#  KIND, either express or implied.  See the License for the
#  specific language governing permissions and limitations
#  under the License.
#  
#**************************************************************



PRJ=..$/..$/..

PRJNAME=shell
TARGET=macbe

LIBTARGET=NO
ENABLE_EXCEPTIONS=TRUE

COMP1TYPELIST=$(TARGET)

# --- Settings ---

.INCLUDE : settings.mk

DLLPRE =

# --- Files ---

.IF "$(OS)" != "MACOSX"

dummy:
	@echo "Nothing to build for OS $(OS)."

.INCLUDE : target.mk

.ELSE

CFLAGSCXX+=$(OBJCXXFLAGS)

SLOFILES= \
	$(SLO)$/macbecdef.obj \
    $(SLO)$/macbackend.obj

SHL1TARGET=$(TARGET)1.uno
SHL1OBJS=$(SLOFILES)
SHL1DEF=$(MISC)$/$(SHL1TARGET).def

SHL1IMPLIB=i$(SHL1TARGET)
SHL1STDLIBS= \
        $(CPPUHELPERLIB) \
        $(CPPULIB) \
        $(SALLIB) \
	-framework Cocoa -framework SystemConfiguration

SHL1VERSIONMAP=$(SOLARENV)/src/component.map
SHL1DEF=$(MISC)$/$(SHL1TARGET).def
DEF1NAME=$(SHL1TARGET)

# --- Targets ---

.INCLUDE : target.mk

.ENDIF # "$(OS)" != "MACOSX"

ALLTAR : $(MISC)/macbe1.component

$(MISC)/macbe1.component .ERRREMOVE : $(SOLARENV)/bin/createcomponent.xslt \
        macbe1.component
    $(XSLTPROC) --nonet --stringparam uri \
        '$(COMPONENTPREFIX_BASIS_NATIVE)$(SHL1TARGETN:f)' -o $@ \
        $(SOLARENV)/bin/createcomponent.xslt macbe1.component
