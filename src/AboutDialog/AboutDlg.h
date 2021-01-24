#ifndef ABOUT_DLG_H
#define ABOUT_DLG_H

#include "PluginInterface.h"
#include "StaticDialog.h"
#include "URLCtrl.h"
#include "../resources/resource.h"

class AboutDialog : public StaticDialog
{
public:
	AboutDialog() : StaticDialog() {};

	void init( HINSTANCE hInst, NppData nppData )
	{
		_nppData = nppData;
		Window::init(hInst, nppData._nppHandle);
	};

	void doDialog();

	virtual void destroy()
	{
		_urlNppPlugin.destroy();
	};

protected:
	virtual INT_PTR CALLBACK run_dlgProc(UINT message, WPARAM wParam, LPARAM /*lParam*/);

private:
	// Handles
	NppData	_nppData;

	// Url control
	URLCtrl	_urlNppPlugin;
};

#endif //ABOUT_DLG_H
