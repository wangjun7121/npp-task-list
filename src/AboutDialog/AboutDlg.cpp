#include "AboutDlg.h"
#include "PluginInterface.h"

void AboutDialog::doDialog()
{
	if (!isCreated())
		create(IDD_ABOUT_DIALOG);

	goToCenter();
}

INT_PTR CALLBACK AboutDialog::run_dlgProc(UINT message, WPARAM wParam, LPARAM /*lParam*/)
{
	switch (message) {
	case WM_INITDIALOG:
		{
			_urlNppPlugin.init(_hInst, _hSelf);
			_urlNppPlugin.create(::GetDlgItem(_hSelf, IDC_ABOUT_URL), TEXT("https://github.com/Megabyteceer/npp-task-list"));

			return TRUE;
		}
	case WM_COMMAND:
		{
			switch (wParam) {
			case IDOK:
				display(FALSE);
				return TRUE;
			default:
				break;
			}
		}
	}

	return FALSE;
}
