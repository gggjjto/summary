//清单1-3  父子进程的简单通信及终止进程的示例程序
// procterm项目
# include <windows.h>
# include <iostream>
# include <stdio.h>
static LPCTSTR g_szMutexName = "w2kdg.ProcTerm.mutex.Suicide" ;
// 创建当前进程的克隆进程的简单方法
void StartClone()
{
    // 提取当前可执行文件的文件名
    TCHAR szFilename[MAX_PATH] ;
    GetModuleFileName(NULL, szFilename, MAX_PATH) ;

    // 格式化用于子进程的命令行，字符串“child”将作为形参传递给子进程的main函数
    TCHAR szCmdLine[MAX_PATH] ;
	//实验1-3步骤3：将下句中的字符串child改为别的字符串，重新编译执行，执行前请先保存已经完成的工作
    sprintf(szCmdLine, "\"%s\" child" , szFilename) ;
	//std::cout<<"szCmdLine[0]:"<<szCmdLine[0]<<'\n'; 
	//std::cout<<"szCmdLine[1]:"<<szCmdLine[1]<<'\n';
	//std::cout<<"szCmdLine"<<szCmdLine<<'\n'; 
    // 子进程的启动信息结构
    STARTUPINFO si;
    ZeroMemory(&si,sizeof(si)) ;
    si.cb = sizeof(si) ;		// 应当是此结构的大小

    // 返回的用于子进程的进程信息
    PROCESS_INFORMATION pi;

    // 用同样的可执行文件名和命令行创建进程，并指明它是一个子进程
    BOOL bCreateOK=CreateProcess(
        szFilename,				// 产生的应用程序的名称 (本EXE文件)
        szCmdLine,				// 告诉我们这是一个子进程的标志
        NULL,					// 用于进程的缺省的安全性
        NULL,					// 用于线程的缺省安全性
        FALSE,					// 不继承句柄
        0,						//创建新窗口
        NULL,					// 新环境
        NULL,					// 当前目录
        &si,					// 启动信息结构
        &pi ) ;					// 返回的进程信息
    // 释放指向子进程的引用
    if (bCreateOK)
    {
        CloseHandle(pi.hProcess) ;
        CloseHandle(pi.hThread) ;
    }
}

void Parent()
{
    // 创建“自杀”互斥程序体
    HANDLE hMutexSuicide=CreateMutex(
        NULL,					// 缺省的安全性
        TRUE,					// 最初拥有的
        g_szMutexName) ;		// 互斥体名称
    if (hMutexSuicide != NULL)
    {
        // 创建子进程
        std :: cout << "Creating the child process. 创建子进程" << '\n';
        StartClone() ;
        // 指令子进程“杀”掉自身
        std :: cout << "Telling the child process to quit. 指令子进程杀掉自身"<< std :: endl;
		//等待父进程的键盘响应
        getchar() ;
		//释放互斥体的所有权，这个信号会发送给子进程的WaitForSingleObject过程
		ReleaseMutex(hMutexSuicide) ;
        // 消除句柄
        CloseHandle(hMutexSuicide) ;
    }
}

void Child()
{
    // 打开“自杀”互斥体
    HANDLE hMutexSuicide = OpenMutex(
        SYNCHRONIZE,			// 打开用于同步
        FALSE,					// 不需要向下传递
        g_szMutexName) ;		// 名称
    if (hMutexSuicide != NULL)
    {
        // 报告我们正在等待指令
        std :: cout <<"Child waiting for suicide instructions. 报告我们正在等待指令" << std :: endl; 
       
		//子进程进入阻塞状态，等待父进程通过互斥体发来的信号
	    WaitForSingleObject(hMutexSuicide, INFINITE) ;
	    //WaitForSingleObject(hMutexSuicide, 0) ;
	    //WaitForSingleObject(hMutexSuicide, 1000);
//实验1-3步骤4：将上句改为WaitForSingleObject(hMutexSuicide, 0) ，重新编译执行

        // 准备好终止，清除句柄
        std :: cout << "Child quiting. 清除句柄" << std :: endl;
        CloseHandle(hMutexSuicide) ;
    }
}

int main(int argc, char* argv[] )
{
    // 决定其行为是父进程还是子进程
	std::cout<<*argv<<"------------\n";
    if (argc>1 && :: strcmp(argv[1] , "child" )== 0)
    {
    	//子进程
    	std::cout<<"这是子进程\n";
        Child() ;
    }
    else
    {
    	//父进程
    	std::cout<<"这是父进程\n";
        Parent() ;
    }
return 0;

}
