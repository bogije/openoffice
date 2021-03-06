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


package com.sun.star.report.pentaho.parser.office;

import com.sun.star.report.pentaho.OfficeNamespaces;
import com.sun.star.report.pentaho.model.OfficeStylesCollection;
import com.sun.star.report.pentaho.parser.ElementReadHandler;
import com.sun.star.report.pentaho.parser.style.OfficeStylesReadHandler;

import org.jfree.report.structure.Element;

import org.pentaho.reporting.libraries.xmlns.parser.XmlReadHandler;

import org.xml.sax.Attributes;
import org.xml.sax.SAXException;

/**
 * The root parser for a 'styles.xml' document. This generates the global
 * (or common) style collection. These styles contain the named common styles
 * and the page layouts.
 *
 * @author Thomas Morgner
 * @since 08.03.2007
 */
public class DocumentStylesReadHandler extends ElementReadHandler
{

    private final OfficeStylesCollection officeStylesCollection;
    private FontFaceDeclsReadHandler fontFaceReadHandler;

    public DocumentStylesReadHandler()
    {
        officeStylesCollection = new OfficeStylesCollection();
    }

    /**
     * Returns the handler for a child element.
     *
     * @param tagName the tag name.
     * @param atts    the attributes.
     * @return the handler or null, if the tagname is invalid.
     *
     * @throws org.xml.sax.SAXException if there is a parsing error.
     */
    protected XmlReadHandler getHandlerForChild(final String uri,
            final String tagName,
            final Attributes atts)
            throws SAXException
    {
        if (!OfficeNamespaces.OFFICE_NS.equals(uri))
        {
            return null;
        }

        if ("font-face-decls".equals(tagName))
        {
            if (fontFaceReadHandler == null)
            {
                fontFaceReadHandler = new FontFaceDeclsReadHandler(officeStylesCollection.getFontFaceDecls());
            }
            return fontFaceReadHandler;
        }
        else if ("automatic-styles".equals(tagName))
        {
            return new OfficeStylesReadHandler(officeStylesCollection.getAutomaticStyles());
        }
        else if ("styles".equals(tagName))
        {
            return new OfficeStylesReadHandler(officeStylesCollection.getCommonStyles());
        }
        else if ("master-styles".equals(tagName))
        {
            return new MasterStylesReadHandler(officeStylesCollection.getMasterStyles());
        }
        return null;
    }

    public Element getElement()
    {
        return officeStylesCollection;
    }
}
