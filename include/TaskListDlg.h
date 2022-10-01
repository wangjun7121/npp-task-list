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
#include "PluginDefinition.h"
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
		if ( !isDarkMode() && !todoItems.empty() )
		{
		// 1 - addition of darkmode in NPP 8.4.3ff has produced an artifact (only) in regular 
			// display mode.  when list box contents is cleared via LB_RESETCONTENT it does not 
			// occur promptly.  moreover if the new contents are added too quickly they are written 
			// over the old contents - although the old contents are not selectable.
		// 2 - this code causes a 200 ms delay by clearing the current contents and using 
			// findTasks() to force a second update at next time tick.
		// 3 - I choose to add this delay code solely to fix the light mode problem since dark mode works fine - NeArnold
			todoItems.clear();
//			::RedrawWindow( _hList, 0, 0, RDW_ERASE | RDW_INVALIDATE );	// tried to force faster clearing
			findTasks();
			return;
		}
		todoItems.clear();
//		::RedrawWindow( _hList, 0, 0, RDW_ERASENOW | RDW_INVALIDATE );	// tried to force faster clearing

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
	bool isDarkMode();
};

#endif //GOTILINE_DLG_H
