#pragma once
// include the MZFC library header file
#include <mzfc_inc.h>

class UiFileDialogWnd : public CMzWndEx {
    MZ_DECLARE_DYNAMIC(UiFileDialogWnd);
public:
	UiFileDialogWnd(void){
		_title = NULL;
		_filename = NULL;
		_filesuffix = NULL;
		_folder = NULL;
	}
	~UiFileDialogWnd(void){
		if(_title) delete [] _title;
		if(_filename) delete [] _filename;
		if(_filesuffix) delete [] _filesuffix;
		if(_folder) delete [] _folder;
	}
public:
	UiCaption m_DialogTitle;
	UiSingleLineEdit m_FileName;
	UiButtonEx m_FolderPath;
	UiToolbar_Text m_Toolbar;
public:
	void SetTitle(LPCTSTR text);
	void SetInitFileName(LPCTSTR text);
	void SetInitFileSuffix(LPCTSTR text);
	void SetInitFolder(LPCTSTR text);

	//��ȡ������׺����·�����ļ�·��
	LPTSTR GetFullFileName();
private:
	bool checkFileName();	//����ļ����Ϸ���
	bool checkFileExist();	//����ļ��Ƿ��Ѿ�����
	void getfileInfo();
protected:
    // Initialization of the window (dialog)
    virtual BOOL OnInitDialog();

    // override the MZFC command handler
    virtual void OnMzCommand(WPARAM wParam, LPARAM lParam);
private:
	LPTSTR	_title;
	LPTSTR _filename;
	LPTSTR _filesuffix;
	LPTSTR _folder;
};
