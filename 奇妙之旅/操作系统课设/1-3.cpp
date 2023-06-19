//�嵥1-3  ���ӽ��̵ļ�ͨ�ż���ֹ���̵�ʾ������
// procterm��Ŀ
# include <windows.h>
# include <iostream>
# include <stdio.h>
static LPCTSTR g_szMutexName = "w2kdg.ProcTerm.mutex.Suicide" ;
// ������ǰ���̵Ŀ�¡���̵ļ򵥷���
void StartClone()
{
    // ��ȡ��ǰ��ִ���ļ����ļ���
    TCHAR szFilename[MAX_PATH] ;
    GetModuleFileName(NULL, szFilename, MAX_PATH) ;

    // ��ʽ�������ӽ��̵������У��ַ�����child������Ϊ�βδ��ݸ��ӽ��̵�main����
    TCHAR szCmdLine[MAX_PATH] ;
	//ʵ��1-3����3�����¾��е��ַ���child��Ϊ����ַ��������±���ִ�У�ִ��ǰ���ȱ����Ѿ���ɵĹ���
    sprintf(szCmdLine, "\"%s\" child" , szFilename) ;
	//std::cout<<"szCmdLine[0]:"<<szCmdLine[0]<<'\n'; 
	//std::cout<<"szCmdLine[1]:"<<szCmdLine[1]<<'\n';
	//std::cout<<"szCmdLine"<<szCmdLine<<'\n'; 
    // �ӽ��̵�������Ϣ�ṹ
    STARTUPINFO si;
    ZeroMemory(&si,sizeof(si)) ;
    si.cb = sizeof(si) ;		// Ӧ���Ǵ˽ṹ�Ĵ�С

    // ���ص������ӽ��̵Ľ�����Ϣ
    PROCESS_INFORMATION pi;

    // ��ͬ���Ŀ�ִ���ļ����������д������̣���ָ������һ���ӽ���
    BOOL bCreateOK=CreateProcess(
        szFilename,				// ������Ӧ�ó�������� (��EXE�ļ�)
        szCmdLine,				// ������������һ���ӽ��̵ı�־
        NULL,					// ���ڽ��̵�ȱʡ�İ�ȫ��
        NULL,					// �����̵߳�ȱʡ��ȫ��
        FALSE,					// ���̳о��
        0,						//�����´���
        NULL,					// �»���
        NULL,					// ��ǰĿ¼
        &si,					// ������Ϣ�ṹ
        &pi ) ;					// ���صĽ�����Ϣ
    // �ͷ�ָ���ӽ��̵�����
    if (bCreateOK)
    {
        CloseHandle(pi.hProcess) ;
        CloseHandle(pi.hThread) ;
    }
}

void Parent()
{
    // ��������ɱ�����������
    HANDLE hMutexSuicide=CreateMutex(
        NULL,					// ȱʡ�İ�ȫ��
        TRUE,					// ���ӵ�е�
        g_szMutexName) ;		// ����������
    if (hMutexSuicide != NULL)
    {
        // �����ӽ���
        std :: cout << "Creating the child process. �����ӽ���" << '\n';
        StartClone() ;
        // ָ���ӽ��̡�ɱ��������
        std :: cout << "Telling the child process to quit. ָ���ӽ���ɱ������"<< std :: endl;
		//�ȴ������̵ļ�����Ӧ
        getchar() ;
		//�ͷŻ����������Ȩ������źŻᷢ�͸��ӽ��̵�WaitForSingleObject����
		ReleaseMutex(hMutexSuicide) ;
        // �������
        CloseHandle(hMutexSuicide) ;
    }
}

void Child()
{
    // �򿪡���ɱ��������
    HANDLE hMutexSuicide = OpenMutex(
        SYNCHRONIZE,			// ������ͬ��
        FALSE,					// ����Ҫ���´���
        g_szMutexName) ;		// ����
    if (hMutexSuicide != NULL)
    {
        // �����������ڵȴ�ָ��
        std :: cout <<"Child waiting for suicide instructions. �����������ڵȴ�ָ��" << std :: endl; 
       
		//�ӽ��̽�������״̬���ȴ�������ͨ�������巢�����ź�
	    WaitForSingleObject(hMutexSuicide, INFINITE) ;
	    //WaitForSingleObject(hMutexSuicide, 0) ;
	    //WaitForSingleObject(hMutexSuicide, 1000);
//ʵ��1-3����4�����Ͼ��ΪWaitForSingleObject(hMutexSuicide, 0) �����±���ִ��

        // ׼������ֹ��������
        std :: cout << "Child quiting. ������" << std :: endl;
        CloseHandle(hMutexSuicide) ;
    }
}

int main(int argc, char* argv[] )
{
    // ��������Ϊ�Ǹ����̻����ӽ���
	std::cout<<*argv<<"------------\n";
    if (argc>1 && :: strcmp(argv[1] , "child" )== 0)
    {
    	//�ӽ���
    	std::cout<<"�����ӽ���\n";
        Child() ;
    }
    else
    {
    	//������
    	std::cout<<"���Ǹ�����\n";
        Parent() ;
    }
return 0;

}
