//�嵥1-2  �����ӽ���
#include <windows.h>
#include <iostream>
#include <stdio.h>

// �������ݹ����Ľ��̵Ŀ�¡���̲�������IDֵ
void StartClone(int nCloneID)
{
    // ��ȡ���ڵ�ǰ��ִ���ļ����ļ���
    TCHAR szFilename[MAX_PATH] ;
    GetModuleFileName(NULL, szFilename, MAX_PATH) ;
    
	std::cout<<"szFilename[]="<<szFilename<<'\n';
	
    // ��ʽ�������ӽ��̵������в�֪ͨ��EXE�ļ����Ϳ�¡ID
    TCHAR szCmdLine[MAX_PATH];
	sprintf(szCmdLine,"\"%s\" %d",szFilename,nCloneID);
	
	std::cout<<"szCmdLine[1]="<<szCmdLine[1]<<'\n';
	
	// �����ӽ��̵�STARTUPINFO�ṹ
	
    STARTUPINFO si;
    ZeroMemory(&si , sizeof(si) ) ;
    si.cb = sizeof(si) ;				// �����Ǳ��ṹ�Ĵ�С
	std::cout<<"si.cd="<<si.cb<<'\n';
	
    // ���ص������ӽ��̵Ľ�����Ϣ
    PROCESS_INFORMATION pi;

    // ����ͬ���Ŀ�ִ���ļ��������д������̣����������ӽ��̵�����
    BOOL bCreateOK=::CreateProcess(
        szFilename,					// �������EXE��Ӧ�ó��������	argc
        szCmdLine,					// ��������Ϊ��һ���ӽ��̵ı�־	argv
        NULL,						// ȱʡ�Ľ��̰�ȫ��
        NULL,						// ȱʡ���̰߳�ȫ��
        FALSE,						// ���̳о��
        CREATE_NEW_CONSOLE,		// ʹ���µĿ���̨
		//0,			
        NULL,						// �µĻ���
        NULL,						// ��ǰĿ¼
        &si,						// ������Ϣ
        &pi) ;						// ���صĽ�����Ϣ
        
	std::cout<<bCreateOK<<'\n';
    // ���ӽ����ͷ�����
    if (bCreateOK)
    {
        CloseHandle(pi.hProcess) ;
        CloseHandle(pi.hThread) ;
    }
}

int main(int argc, char* argv[] )
{
	//std::cout<<"mainbegin()-------------------\n" ;
    // ȷ���������������̣������������ڽ����б��е�λ��
    int nClone=0;
//�޸���䣺int nClone;
	
//��һ���޸ģ�nClone=0;
    if (argc > 1)
    {
        // �ӵڶ�����������ȡ��¡ID
        std:: sscanf(argv[1] , "%d" , &nClone) ; //��sscanf_s����
        std::cout<<"argv[1]:"<<argv[1]<<"\nnClone:"<<nClone<<'\n';
    }

//�ڶ����޸ģ�nClone=0;
	// ��ʾ����λ��
    std :: cout << "Process ID:" << :: GetCurrentProcessId()
                << ", Clone ID:" << nClone
                << '\n';
	// ����Ƿ��д����ӽ��̵���Ҫ
    const int c_nCloneMax=5;
    
    if (nClone < c_nCloneMax)
    {
		// �����½��̵������кͿ�¡��
		std::cout<<"�����˵ڼ��Σ�"<<nClone+1<<'\n';
       StartClone(++nClone) ;
    }
    //std::cout<<"mainend()----------------------------------------------\n";
    std::cout<<"----------------------------------------------\n";
    // �ȴ���Ӧ���������������
    getchar();
   	//char ch=getchar();
   	//std::cout<<"ch="<<ch<<'\n';
   	//getchar();
    return 0;
}
