//this file is part of notepad++
//Copyright (C)2003 Don HO ( donho@altern.org )
//
//This program is free software; you can redistribute it and/or
//modify it under the terms of the GNU General Public License
//as published by the Free Software Foundation; either
//version 2 of the License, or (at your option) any later version.
//
//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with this program; if not, write to the Free Software
//Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

#ifndef GOTILINE_DLG_H
#define GOTILINE_DLG_H

#include "DockingDlgInterface.h"
#include "../resources/resource.h"
#include <codecvt>

typedef struct
{
	char* text;
	HWND hScintilla;
	long startPosition, endPosition;
} TodoItem;

#include <list>
#include <vector>

class TaskListDlg : public DockingDlgInterface
{
public :
	TaskListDlg() : DockingDlgInterface(IDD_TODOLIST_DIALOG){};

    virtual void display(bool toShow = true) const {
        DockingDlgInterface::display(toShow);
        if (toShow)
            ::SetFocus(::GetDlgItem(_hSelf, ID_GOLINE_EDIT));
    };

	void setParent(HWND parent2set){
		_hParent = parent2set;
	};

	void SetList(const std::list<TodoItem>& items)
	{
		HWND _hList = ::GetDlgItem( _hSelf, ID_TODO_LIST );
		if ( !_hList )
			return;
		//clear list LB_RESETCONTENT
		::SendMessage( _hList, LB_RESETCONTENT, NULL, NULL );
		todoItems.clear();

		//prepare for ut8 conversion
		using convert_typeX = std::codecvt_utf8<wchar_t>;
		std::wstring_convert<convert_typeX, wchar_t> converterX;
		//add list items LB_ADDSTRING
		for (const auto &it : items)
		{
			::SendMessage( _hList, LB_ADDSTRING, NULL, (LPARAM)converterX.from_bytes(it.text).c_str());
			todoItems.push_back(it);
		}
	};

protected :
	virtual INT_PTR CALLBACK run_dlgProc(UINT message, WPARAM wParam, LPARAM lParam);

private :
	std::vector<TodoItem> todoItems;
	HBRUSH hbrBackgnd = NULL;
	HWND GetCurScintilla();
};

#endif //GOTILINE_DLG_H
