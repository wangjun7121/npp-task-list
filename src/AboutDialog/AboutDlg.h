#pragma once

#include "PluginInterface.h"
#include "URLCtrl.h"
#include "../resources/resource.h"
#include "StaticDialog.h"

class AboutDialog : public StaticDialog
{
public:
	AboutDialog() = default;

	void init( HINSTANCE hInst, NppData nppData )
	{
		_nppData = nppData;
		Window::init(hInst, nppData._nppHandle);
	};

	void doDialog();

	void destroy() override
	{
		_urlNppPlugin.destroy();
	};

protected:
	intptr_t CALLBACK run_dlgProc(UINT message, WPARAM wParam, LPARAM /*lParam*/) override;

private:
	// Handles
	NppData	_nppData;

	// Url control
	URLCtrl	_urlNppPlugin;
};
