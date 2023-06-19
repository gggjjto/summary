/*  ʵ����Դ���� */
//�嵥5-1  �˽�ͼ����̵������ڴ�ռ�
// ����vmwalker
#include <windows.h>
#include <iostream>
#include <shlwapi.h>
#include <iomanip>
#pragma comment(lib, "Shlwapi.lib")

// �Կɶ���ʽ���û���ʾ�����ĸ���������
// ������Ǳ�ʾ����Ӧ�ó�����ڴ���з��ʵ�����
// �Լ�����ϵͳǿ�Ʒ��ʵ�����
inline bool TestSet(DWORD dwTarget, DWORD dwMask)
{
    return ((dwTarget &dwMask) == dwMask) ;
}
# define SHOWMASK(dwTarget, type) \
if (TestSet(dwTarget, PAGE_##type) ) \
    {std :: cout << ", " << #type; }

void ShowProtection(DWORD dwTarget)
{
    SHOWMASK(dwTarget, READONLY) ;
    SHOWMASK(dwTarget, GUARD) ;
    SHOWMASK(dwTarget, NOCACHE) ;
    SHOWMASK(dwTarget, READWRITE) ;
    SHOWMASK(dwTarget, WRITECOPY) ;
    SHOWMASK(dwTarget, EXECUTE) ;
    SHOWMASK(dwTarget, EXECUTE_READ) ;
    SHOWMASK(dwTarget, EXECUTE_READWRITE) ;
    SHOWMASK(dwTarget, EXECUTE_WRITECOPY) ;
    SHOWMASK(dwTarget, NOACCESS) ;
}

// �������������ڴ沢���û���ʾ�����ԵĹ�������ķ���
void WalkVM(HANDLE hProcess)
{
    // ���ȣ����ϵͳ��Ϣ
    SYSTEM_INFO si;
    :: ZeroMemory(&si, sizeof(si) ) ;
    :: GetSystemInfo(&si) ;

    // ����Ҫ�����Ϣ�Ļ�����
    MEMORY_BASIC_INFORMATION mbi;
    :: ZeroMemory(&mbi, sizeof(mbi) ) ;

    // ѭ������Ӧ�ó����ַ�ռ�
    LPCVOID pBlock = (LPVOID) si.lpMinimumApplicationAddress;
    while (pBlock < si.lpMaximumApplicationAddress)
    {
        // �����һ�������ڴ�����Ϣ
        if (:: VirtualQueryEx(
            hProcess,						// ��صĽ���
            pBlock,                         // ��ʼλ��
			&mbi,                           // ������
            sizeof(mbi))==sizeof(mbi) )		// ��С��ȷ��
        {
            // �����Ľ�β�����С
            LPCVOID pEnd = (PBYTE) pBlock + mbi.RegionSize;
			TCHAR szSize[MAX_PATH];
            :: StrFormatByteSize(mbi.RegionSize, szSize, MAX_PATH) ;

            // ��ʾ���ַ�ʹ�С
            std :: cout.fill ('0') ;
            std :: cout
                << std :: hex << std :: setw(8) << (DWORD_PTR) pBlock
                << "-"
                << std :: hex << std :: setw(8) << (DWORD_PTR) pEnd
                << (:: strlen(szSize)==7? " (" : " (") << szSize
                << ") " ;

            // ��ʾ���״̬
            switch(mbi.State)
            {
                case MEM_COMMIT :
					std :: cout << "Committed�ύ" ;
					break;
                case MEM_FREE :
					std :: cout << "Free����" ;
					break;
                case MEM_RESERVE :
					std :: cout << "Reserved����" ;
					break;
            }
            // ��ʾ����
			if(mbi.Protect==0 && mbi.State!=MEM_FREE)
            {    mbi.Protect=PAGE_READONLY;     }
			ShowProtection(mbi.Protect);
            // ��ʾ����
            switch(mbi.Type){
                case MEM_IMAGE :
					std :: cout << ", Imageӳ���ļ�ҳ��" ;
					break;
				case MEM_MAPPED:
					std :: cout << ", Mappedӳ���ļ�ҳ��";
					break;
                case MEM_PRIVATE :
					std :: cout << ", Private˽��ҳ��" ;
					break;
			}
            // �����ִ�е�Ӱ��
            TCHAR szFilename [MAX_PATH] ;
            if (:: GetModuleFileName (
                (HMODULE) pBlock,		// ʵ�������ڴ��ģ����
				szFilename,             //��ȫָ�����ļ�����
				MAX_PATH)>0)            //ʵ��ʹ�õĻ�������С
            {
                // ��ȥ·������ʾ
                :: PathStripPath(szFilename) ;
                std :: cout << ", Module: " << szFilename;
			}
            std :: cout << std :: endl;
			// �ƶ���ָ���Ի����һ�¸���
            pBlock = pEnd;
        }
    }
}

void ShowVirtualMemory()
{
    // ���ȣ������ǻ��ϵͳ��Ϣ
    SYSTEM_INFO si;
    :: ZeroMemory(&si, sizeof(si) ) ;
    :: GetSystemInfo(&si) ;
    // ʹ����Ǹ��������һЩ�ߴ���и�ʽ��
    TCHAR szPageSize[MAX_PATH];
    ::StrFormatByteSize(si.dwPageSize, szPageSize, MAX_PATH) ;
    DWORD dwMemSize = (DWORD_PTR)si.lpMaximumApplicationAddress -
          (DWORD_PTR) si.lpMinimumApplicationAddress;
    TCHAR szMemSize [MAX_PATH] ;
    :: StrFormatByteSize(dwMemSize, szMemSize, MAX_PATH) ;
    // ���ڴ���Ϣ��ʾ����
    std :: cout << "Virtual memory page size: " << szPageSize << std :: endl;

    std :: cout.fill ('0') ;
    std :: cout << "Minimum application address: 0x"
            << std :: hex << std :: setw(8)
            << (DWORD_PTR) si.lpMinimumApplicationAddress
            << std :: endl;
    std :: cout << "Maximum application address: 0x"
            << std :: hex << std :: setw(8)
            << (DWORD_PTR) si.lpMaximumApplicationAddress
            << std :: endl;

    std :: cout << "Total available virtual memory: "
            << szMemSize << std :: endl ;
}
int main()
{
	//��ʾ�����ڴ�Ļ�����Ϣ
	ShowVirtualMemory();
    // ������ǰ���̵������ڴ�
	::WalkVM(::GetCurrentProcess());
	getchar();
}



///*  ��¼��Դ���� */
///*  Remove newlines */
//#include <stdio.h>
//main()
//{
//  int c,n=0,max=1;
//  while((c=getchar())!=EOF)
//  {
//     if (c=='\n')
//       n++;
//     else
//       n=0;
//     if (n<=max)
//       putchar( c);
//   }
//}
