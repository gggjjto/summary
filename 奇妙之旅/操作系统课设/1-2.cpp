//清单1-2  创建子进程
#include <windows.h>
#include <iostream>
#include <stdio.h>

// 创建传递过来的进程的克隆过程并赋于其ID值
void StartClone(int nCloneID)
{
    // 提取用于当前可执行文件的文件名
    TCHAR szFilename[MAX_PATH] ;
    GetModuleFileName(NULL, szFilename, MAX_PATH) ;
    
	std::cout<<"szFilename[]="<<szFilename<<'\n';
	
    // 格式化用于子进程的命令行并通知其EXE文件名和克隆ID
    TCHAR szCmdLine[MAX_PATH];
	sprintf(szCmdLine,"\"%s\" %d",szFilename,nCloneID);
	
	std::cout<<"szCmdLine[1]="<<szCmdLine[1]<<'\n';
	
	// 用于子进程的STARTUPINFO结构
	
    STARTUPINFO si;
    ZeroMemory(&si , sizeof(si) ) ;
    si.cb = sizeof(si) ;				// 必须是本结构的大小
	std::cout<<"si.cd="<<si.cb<<'\n';
	
    // 返回的用于子进程的进程信息
    PROCESS_INFORMATION pi;

    // 利用同样的可执行文件和命令行创建进程，并赋于其子进程的性质
    BOOL bCreateOK=::CreateProcess(
        szFilename,					// 产生这个EXE的应用程序的名称	argc
        szCmdLine,					// 告诉其行为像一个子进程的标志	argv
        NULL,						// 缺省的进程安全性
        NULL,						// 缺省的线程安全性
        FALSE,						// 不继承句柄
        CREATE_NEW_CONSOLE,		// 使用新的控制台
		//0,			
        NULL,						// 新的环境
        NULL,						// 当前目录
        &si,						// 启动信息
        &pi) ;						// 返回的进程信息
        
	std::cout<<bCreateOK<<'\n';
    // 对子进程释放引用
    if (bCreateOK)
    {
        CloseHandle(pi.hProcess) ;
        CloseHandle(pi.hThread) ;
    }
}

int main(int argc, char* argv[] )
{
	//std::cout<<"mainbegin()-------------------\n" ;
    // 确定派生出几个进程，及派生进程在进程列表中的位置
    int nClone=0;
//修改语句：int nClone;
	
//第一次修改：nClone=0;
    if (argc > 1)
    {
        // 从第二个参数中提取克隆ID
        std:: sscanf(argv[1] , "%d" , &nClone) ; //用sscanf_s代替
        std::cout<<"argv[1]:"<<argv[1]<<"\nnClone:"<<nClone<<'\n';
    }

//第二次修改：nClone=0;
	// 显示进程位置
    std :: cout << "Process ID:" << :: GetCurrentProcessId()
                << ", Clone ID:" << nClone
                << '\n';
	// 检查是否有创建子进程的需要
    const int c_nCloneMax=5;
    
    if (nClone < c_nCloneMax)
    {
		// 发送新进程的命令行和克隆号
		std::cout<<"进入了第几次："<<nClone+1<<'\n';
       StartClone(++nClone) ;
    }
    //std::cout<<"mainend()----------------------------------------------\n";
    std::cout<<"----------------------------------------------\n";
    // 等待响应键盘输入结束进程
    getchar();
   	//char ch=getchar();
   	//std::cout<<"ch="<<ch<<'\n';
   	//getchar();
    return 0;
}
