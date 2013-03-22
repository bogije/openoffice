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

#include "svx/sidebar/ValueSetWithTextControl.hxx"

#include <sfx2/sidebar/Theme.hxx>

#include <i18npool/mslangid.hxx>

namespace svx { namespace sidebar {

ValueSetWithTextControl::ValueSetWithTextControl(
    const tControlType eControlType,
    Window* pParent,
    const ResId& rResId)
    : ValueSet( pParent, rResId )
    , meControlType( eControlType )
    , maItems()
{
    SetColCount( 1 );
}


ValueSetWithTextControl::~ValueSetWithTextControl(void)
{
}


void ValueSetWithTextControl::AddItem(
    const Image& rItemImage,
    const Image* pSelectedItemImage,
    const XubString& rItemText,
    const XubString* pItemHelpText )
{
    if ( meControlType != IMAGE_TEXT )
    {
        return;
    }

    ValueSetWithTextItem aItem;
    aItem.maItemImage = rItemImage;
    aItem.maSelectedItemImage = (pSelectedItemImage != 0)
                                ? *pSelectedItemImage
                                : rItemImage;
    aItem.maItemText = rItemText;

    maItems.push_back( aItem );

    InsertItem( maItems.size() );
    SetItemText( maItems.size(),
                    (pItemHelpText != 0) ? *pItemHelpText : rItemText );
}


void ValueSetWithTextControl::AddItem(
    const XubString& rItemText,
    const XubString& rItemText2,
    const XubString* pItemHelpText )
{
    if ( meControlType != TEXT_TEXT )
    {
        return;
    }

    ValueSetWithTextItem aItem;
    aItem.maItemText = rItemText;
    aItem.maItemText2 = rItemText2;

    maItems.push_back( aItem );

    InsertItem( maItems.size() );
    SetItemText( maItems.size(),
                    (pItemHelpText != 0) ? *pItemHelpText : rItemText );
}


void ValueSetWithTextControl::ReplaceItemImages(
    const sal_uInt16 nItemId,
    const Image& rItemImage,
    const Image* pSelectedItemImage )
{
    if ( meControlType != IMAGE_TEXT )
    {
        return;
    }

    if ( nItemId == 0 ||
         nItemId > maItems.size() )
    {
        return;
    }

    maItems[nItemId-1].maItemImage = rItemImage;
    maItems[nItemId-1].maSelectedItemImage = (pSelectedItemImage != 0)
                                             ? *pSelectedItemImage
                                             : rItemImage;
}

    
void ValueSetWithTextControl::UserDraw( const UserDrawEvent& rUDEvt )
{
    const Rectangle aRect = rUDEvt.GetRect();
    OutputDevice* pDev = rUDEvt.GetDevice();
    pDev->Push( PUSH_ALL );
    const sal_uInt16 nItemId = rUDEvt.GetItemId();

    const long nRectHeight = aRect.GetHeight();
    const Point aBLPos = aRect.TopLeft();

    Font aFont(OutputDevice::GetDefaultFont(DEFAULTFONT_UI_SANS, MsLangId::getSystemLanguage(), DEFAULTFONT_FLAGS_ONLYONE));
    {
        Size aSize = aFont.GetSize();
        aSize.Height() = (nRectHeight*4)/9;
        aFont.SetSize( aSize );
    }

    {
        //draw backgroud
        if ( GetSelectItemId() == nItemId )
        {
            Rectangle aBackRect = aRect;
            aBackRect.Top() += 3;
            aBackRect.Bottom() -= 2;
            pDev->SetFillColor( sfx2::sidebar::Theme::GetColor( sfx2::sidebar::Theme::Color_Highlight ) );
            pDev->DrawRect(aBackRect);
        }
        else
        {
            pDev->SetFillColor( COL_TRANSPARENT );
            pDev->DrawRect(aRect);
        }

        //draw image + text resp. text + text
        Image* pImage = 0;
        if ( GetSelectItemId() == nItemId )
        {
            aFont.SetColor( sfx2::sidebar::Theme::GetColor( sfx2::sidebar::Theme::Color_HighlightText ) );
            pImage = &maItems[nItemId-1].maSelectedItemImage;
        }
        else
        {
            aFont.SetColor( GetSettings().GetStyleSettings().GetFieldTextColor() );
            pImage = &maItems[nItemId-1].maItemImage;
        }

        Rectangle aStrRect = aRect;
        aStrRect.Top() += nRectHeight/4;
        aStrRect.Bottom() -= nRectHeight/4;

        switch ( meControlType )
        {
        case IMAGE_TEXT:
            {
                Point aImgStart(
                    aBLPos.X() + 4,
                    aBLPos.Y() + ( ( nRectHeight - pImage->GetSizePixel().Height() ) / 2 ) );
                pDev->DrawImage( aImgStart, *pImage );

                aStrRect.Left() += pImage->GetSizePixel().Width() + 12;
                pDev->SetFont(aFont);
                pDev->DrawText(aStrRect, maItems[nItemId-1].maItemText, TEXT_DRAW_ENDELLIPSIS);
            }
            break;
        case TEXT_TEXT:
            {
                const long nRectWidth = aRect.GetWidth();
                aStrRect.Left() += 8;
                aStrRect.Right() -= (nRectWidth*2)/3;
                pDev->SetFont(aFont);
                pDev->DrawText(aStrRect, maItems[nItemId-1].maItemText, TEXT_DRAW_ENDELLIPSIS);
                aStrRect.Left() += nRectWidth/3;
                aStrRect.Right() += (nRectWidth*2)/3;
                pDev->DrawText(aStrRect, maItems[nItemId-1].maItemText2, TEXT_DRAW_ENDELLIPSIS);
            }
            break;
        }
    }

    Invalidate( aRect );
    pDev->Pop();
}

} } // end of namespace svx::sidebar
