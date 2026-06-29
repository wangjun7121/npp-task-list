#include "AboutDlg.h"

void AboutDialog::doDialog()
{
	if (!isCreated())
		create(IDD_ABOUT_DIALOG);

	// Adjust the position of AboutBox
	moveForDpiChange();
	goToCenter(SWP_SHOWWINDOW | SWP_NOSIZE);
}

intptr_t CALLBACK AboutDialog::run_dlgProc(UINT message, WPARAM wParam, LPARAM /*lParam*/)
{
	switch (message) {
	case WM_INITDIALOG:
		{
			_urlNppPlugin.init(_hInst, _hSelf);
			_urlNppPlugin.create(::GetDlgItem(_hSelf, IDC_ABOUT_URL), TEXT("https://github.com/Megabyteceer/npp-task-list"));

			return TRUE;
		}

	case WM_CTLCOLORDLG:
	case WM_CTLCOLORSTATIC:
		{
			return NppDarkMode::onCtlColorDarker(reinterpret_cast<HDC>(wParam));
		}

	case WM_PRINTCLIENT:
		{
			if (NppDarkMode::isEnabled())
			{
				return TRUE;
			}
			break;
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
