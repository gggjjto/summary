///*  ʵ��һԴ���� */
////�嵥1-1  һ���򵥵�Windows����̨Ӧ�ó���
//// hello��Ŀ
# include <iostream>
void main()
{
	std::cout << "Hello, Win32 Consol Application" << std::endl;
	//getchar();
}
//
//
////�嵥1-2  �����ӽ���
//#include <windows.h>
//#include <iostream>
//#include <stdio.h>
//
//// �������ݹ����Ľ��̵Ŀ�¡���̲�������IDֵ
//void StartClone(int nCloneID)
//{
//    // ��ȡ���ڵ�ǰ��ִ���ļ����ļ���
//    TCHAR szFilename[MAX_PATH] ;
//    GetModuleFileName(NULL, szFilename, MAX_PATH) ;
//	
//    // ��ʽ�������ӽ��̵������в�֪ͨ��EXE�ļ����Ϳ�¡ID
//    TCHAR szCmdLine[MAX_PATH];
//	sprintf(szCmdLine,"\"%s\" %d",szFilename,nCloneID);
//
//	// �����ӽ��̵�STARTUPINFO�ṹ
//    STARTUPINFO si;
//    ZeroMemory(&si , sizeof(si) ) ;
//    si.cb = sizeof(si) ;				// �����Ǳ��ṹ�Ĵ�С
//
//    // ���ص������ӽ��̵Ľ�����Ϣ
//    PROCESS_INFORMATION pi;
//
//    // ����ͬ���Ŀ�ִ���ļ��������д������̣����������ӽ��̵�����
//    BOOL bCreateOK=::CreateProcess(
//        szFilename,					// �������EXE��Ӧ�ó��������
//        szCmdLine,					// ��������Ϊ��һ���ӽ��̵ı�־
//        NULL,						// ȱʡ�Ľ��̰�ȫ��
//        NULL,						// ȱʡ���̰߳�ȫ��
//        FALSE,						// ���̳о��
//        CREATE_NEW_CONSOLE,			// ʹ���µĿ���̨
//        NULL,						// �µĻ���
//        NULL,						// ��ǰĿ¼
//        &si,						// ������Ϣ
//        &pi) ;						// ���صĽ�����Ϣ
//
//    // ���ӽ����ͷ�����
//    if (bCreateOK)
//    {
//        CloseHandle(pi.hProcess) ;
//        CloseHandle(pi.hThread) ;
//    }
//}
//
//int main(int argc, char* argv[] )
//{
//    // ȷ���������������̣������������ڽ����б��е�λ��
//    int nClone=0;
////�޸���䣺int nClone;
//
////��һ���޸ģ�nClone=0;
//    if (argc > 1)
//    {
//        // �ӵڶ�����������ȡ��¡ID
//        :: sscanf(argv[1] , "%d" , &nClone) ; //��sscanf_s����
//    }
//
////�ڶ����޸ģ�nClone=0;
//	// ��ʾ����λ��
//    std :: cout << "Process ID:" << :: GetCurrentProcessId()
//                << ", Clone ID:" << nClone
//                << std :: endl;
//	// ����Ƿ��д����ӽ��̵���Ҫ
//    const int c_nCloneMax=5;
//    if (nClone < c_nCloneMax)
//    {
//		// �����½��̵������кͿ�¡��
//       StartClone(++nClone) ;
//    }
//    // �ȴ���Ӧ���������������
//   	getchar();
//    return 0;
//}
//
////�嵥1-3  ���ӽ��̵ļ�ͨ�ż���ֹ���̵�ʾ������
//// procterm��Ŀ
//# include <windows.h>
//# include <iostream>
//# include <stdio.h>
//static LPCTSTR g_szMutexName = "w2kdg.ProcTerm.mutex.Suicide" ;
//
//// ������ǰ���̵Ŀ�¡���̵ļ򵥷���
//void StartClone()
//{
//    // ��ȡ��ǰ��ִ���ļ����ļ���
//    TCHAR szFilename[MAX_PATH] ;
//    GetModuleFileName(NULL, szFilename, MAX_PATH) ;
//
//    // ��ʽ�������ӽ��̵������У��ַ�����child������Ϊ�βδ��ݸ��ӽ��̵�main����
//    TCHAR szCmdLine[MAX_PATH] ;
////ʵ��1-3����3�����¾��е��ַ���child��Ϊ����ַ��������±���ִ�У�ִ��ǰ���ȱ����Ѿ���ɵĹ���
//    sprintf(szCmdLine, "\"%s\"child" , szFilename) ;
//
//    // �ӽ��̵�������Ϣ�ṹ
//    STARTUPINFO si;
//    ZeroMemory(&si,sizeof(si)) ;
//    si.cb = sizeof(si) ;		// Ӧ���Ǵ˽ṹ�Ĵ�С
//
//    // ���ص������ӽ��̵Ľ�����Ϣ
//    PROCESS_INFORMATION pi;
//
//    // ��ͬ���Ŀ�ִ���ļ����������д������̣���ָ������һ���ӽ���
//    BOOL bCreateOK=CreateProcess(
//        szFilename,				// ������Ӧ�ó�������� (��EXE�ļ�)
//        szCmdLine,				// ������������һ���ӽ��̵ı�־
//        NULL,					// ���ڽ��̵�ȱʡ�İ�ȫ��
//        NULL,					// �����̵߳�ȱʡ��ȫ��
//        FALSE,					// ���̳о��
//        CREATE_NEW_CONSOLE,		//�����´���
//        NULL,					// �»���
//        NULL,					// ��ǰĿ¼
//        &si,					// ������Ϣ�ṹ
//        &pi ) ;					// ���صĽ�����Ϣ
//    // �ͷ�ָ���ӽ��̵�����
//    if (bCreateOK)
//    {
//        CloseHandle(pi.hProcess) ;
//        CloseHandle(pi.hThread) ;
//    }
//}
//
//void Parent()
//{
//    // ��������ɱ�����������
//    HANDLE hMutexSuicide=CreateMutex(
//        NULL,					// ȱʡ�İ�ȫ��
//        TRUE,					// ���ӵ�е�
//        g_szMutexName) ;		// ����������
//    if (hMutexSuicide != NULL)
//    {
//        // �����ӽ���
//        std :: cout << "Creating the child process." << std :: endl;
//        StartClone() ;
//        // ָ���ӽ��̡�ɱ��������
//        std :: cout << "Telling the child process to quit. "<< std :: endl;
//		//�ȴ������̵ļ�����Ӧ
//        getchar() ;
//		//�ͷŻ����������Ȩ������źŻᷢ�͸��ӽ��̵�WaitForSingleObject����
//		ReleaseMutex(hMutexSuicide) ;
//        // �������
//        CloseHandle(hMutexSuicide) ;
//    }
//}
//
//void Child()
//{
//    // �򿪡���ɱ��������
//    HANDLE hMutexSuicide = OpenMutex(
//        SYNCHRONIZE,			// ������ͬ��
//        FALSE,					// ����Ҫ���´���
//        g_szMutexName) ;		// ����
//    if (hMutexSuicide != NULL)
//    {
//        // �����������ڵȴ�ָ��
//        std :: cout <<"Child waiting for suicide instructions. " << std :: endl;
//       
//		//�ӽ��̽�������״̬���ȴ�������ͨ�������巢�����ź�
//	    WaitForSingleObject(hMutexSuicide, INFINITE) ;
////ʵ��1-3����4�����Ͼ��ΪWaitForSingleObject(hMutexSuicide, 0) �����±���ִ��
//
//        // ׼������ֹ��������
//        std :: cout << "Child quiting." << std :: endl;
//        CloseHandle(hMutexSuicide) ;
//    }
//}
//
//int main(int argc, char* argv[] )
//{
//    // ��������Ϊ�Ǹ����̻����ӽ���
//    if (argc>1 && :: strcmp(argv[1] , "child" )== 0)
//    {
//        Child() ;
//    }
//    else
//    {
//        Parent() ;
//    }
//return 0;
//
//}
//
//
///*  ʵ���Դ���� */
////�嵥2-1  ��������
//#include <stdio.h>
//#include <stdlib.h>
//main()
//{
//  int x;
//  srand((unsigned)time(NULL));
//  while((x=fork())==-1);
//  if (x==0)
//  {	
//	sleep(rand() % 2);
//	printf("a");
//  }
//  else
//  {
//	sleep(rand() % 3);
//	printf("b");
//  }
//  printf("c");
//}
//
////�嵥2-2 �ӽ���ִ��������
//#include <sys/types.h>
//#include <stdio.h>
//#include <unistd.h>
//int main()
//{
//  pid_t pid;
//  /* fork a child process */
//  pid = fork();
//  if (pid < 0) 
//  { /* error occurred */
//    fprintf(stderr, "Fork Failed");
//    return 1;
//  }
//  else if (pid == 0) 
//  { /* �ӽ��� */
//    execlp("/bin/ls","ls",NULL);
//  }
//  else { /* ������ */
//  /* �����̽�һֱ�ȴ���ֱ���ӽ����������*/
//    wait(NULL);
//    printf("Child Complete");
//  }
//  return 0;
//}
//
//
//
///*  ʵ����Դ���� */
//#include <stdio.h>
//#include <sys/types.h>
//#include <sys/msg.h>
//#include <sys/ipc.h>
//#define MSGKEY 75
//struct msgform
//{
//	long mtype;
//	char mtext[1030];
//}msg;
//int msgqid,i;
//void CLIENT()
//{
//  int i;
//  msgqid=msgget(MSGKEY,0777);
//  for (i=10;i>=1;i--)
//  { 
//	msg.mtype=i;
//	printf("(client) sent \n");
//	msgsnd(msgqid,&msg,1024,0);
//  }
//  exit(0);
//}
//void SERVER()
//{
//  msgqid=msgget(MSGKEY,0777|IPC_CREAT);
//  do{
//  	msgrcv(msgqid,&msg,1030,0,0);
//	printf("(Server) recieved\n");
//
//  } while(msg.mtype!=1);
//  msgctl(msgqid,IPC_RMID,0);
//  exit(0);
//}
//void main()
//{
//  while((i=fork())==-1);
//  if(!i) SERVER();
//  while((i=fork())==-1);
//  if(!i) CLIENT();
//  wait(0);
//  wait(0);
//}
//
//
//
///*  ʵ����Դ���� */
////�嵥4-1 ����������������
//#include <windows.h>
//#include <iostream>
//
//const unsigned short SIZE_OF_BUFFER = 2; //����������
//unsigned short ProductID = 0;    //��Ʒ��
//unsigned short ConsumeID = 0;    //�������ĵĲ�Ʒ��
//unsigned short in = 0;      //��Ʒ��������ʱ�Ļ������±�
//unsigned short out = 0;      //��Ʒ��������ʱ�Ļ������±�
//
//int buffer[SIZE_OF_BUFFER];    //�������Ǹ�ѭ������
//bool p_ccontinue = true;      //���Ƴ������
//HANDLE Mutex;       //�����̼߳�Ļ���
//HANDLE FullSemaphore;     //����������ʱ��ʹ�����ߵȴ�
//HANDLE EmptySemaphore;     //����������ʱ��ʹ�����ߵȴ�
//
//DWORD WINAPI Producer(LPVOID);    //�������߳�
//DWORD WINAPI Consumer(LPVOID);    //�������߳�
//
//int main()
//{
//    //�������������ź�
//	//ע�⣬�����ź�����ͬ���ź����Ķ��巽����ͬ�������ź������õ���CreateMutex������ͬ���ź������õ���CreateSemaphore�����������ķ���ֵ���Ǿ����
//    Mutex = CreateMutex(NULL,FALSE,NULL);
//	EmptySemaphore = CreateSemaphore(NULL,SIZE_OF_BUFFER,SIZE_OF_BUFFER,NULL);
//    //���Ͼ��������޸ģ��������������
//	//EmptySemaphore = CreateSemaphore(NULL,0,SIZE_OF_BUFFER-1,NULL);
//    FullSemaphore = CreateSemaphore(NULL,0,SIZE_OF_BUFFER,NULL);
//
//    //�����������ֵ�����Է��֣��������߸������������߸���ʱ��
//    //�����ٶȿ죬�����߾����ȴ������ߣ���֮�������߾����ȴ� 
//    const unsigned short PRODUCERS_COUNT = 3;  //�����ߵĸ���
//    const unsigned short CONSUMERS_COUNT = 1;  //�����ߵĸ���
//
//    //�ܵ��߳���
//    const unsigned short THREADS_COUNT = PRODUCERS_COUNT+CONSUMERS_COUNT;
//
//    HANDLE hThreads[THREADS_COUNT]; //���̵߳�handle
//    DWORD producerID[PRODUCERS_COUNT]; //�������̵߳ı�ʶ��
//    DWORD consumerID[CONSUMERS_COUNT]; //�������̵߳ı�ʶ��
//
//	//�����������߳�
//    for (int i=0;i<PRODUCERS_COUNT;++i){
//        hThreads[i]=CreateThread(NULL,0,Producer,NULL,0,&producerID[i]);
//        if (hThreads[i]==NULL) return -1;
//    }
//    //�����������߳�
//    for (i=0;i<CONSUMERS_COUNT;++i){
//        hThreads[PRODUCERS_COUNT+i]=CreateThread(NULL,0,Consumer,NULL,0,&consumerID[i]);
//        if (hThreads[i]==NULL) return -1;
//    }
//
//    while(p_ccontinue){
//        if(getchar()){ //���س�����ֹ��������
//            p_ccontinue = false;
//        }
//    }
//    return 0;
//}
//
////����һ����Ʒ����ģ����һ�£�������²�Ʒ��ID��
//void Produce()
//{
//    std::cout << std::endl<< "Producing " << ++ProductID << " ... ";
//    std::cout << "Succeed" << std::endl;
//}
//
////���������Ĳ�Ʒ���뻺����
//void Append()
//{
//    std::cerr << "Appending a product ... ";
//    buffer[in] = ProductID;
//    in = (in+1)%SIZE_OF_BUFFER;
//    std::cerr << "Succeed" << std::endl;
//
//    //�����������ǰ��״̬
//    for (int i=0;i<SIZE_OF_BUFFER;++i){
//        std::cout << i <<": " << buffer[i];
//        if (i==in) std::cout << " <-- ����";
//        if (i==out) std::cout << " <-- ����";
//        std::cout << std::endl;
//    }
//}
//
////�ӻ�������ȡ��һ����Ʒ
//void Take()
//{
//    std::cerr << "Taking a product ... ";
//    ConsumeID = buffer[out];
//	buffer[out] = 0;
//    out = (out+1)%SIZE_OF_BUFFER;
//    std::cerr << "Succeed" << std::endl;
//
//    //�����������ǰ��״̬
//    for (int i=0;i<SIZE_OF_BUFFER;++i){
//        std::cout << i <<": " << buffer[i];
//        if (i==in) std::cout << " <-- ����";
//        if (i==out) std::cout << " <-- ����";
//        std::cout << std::endl;
//    }
//}
//
////����һ����Ʒ
//void Consume()
//{
//    std::cout << "Consuming " << ConsumeID << " ... ";
//    std::cout << "Succeed" << std::endl;
//}
//
////������
//DWORD  WINAPI Producer(LPVOID lpPara)
//{
//    while(p_ccontinue){
//        WaitForSingleObject(EmptySemaphore,INFINITE);	//p(empty);
//        WaitForSingleObject(Mutex,INFINITE);	//p(mutex);
//        Produce();
//        Append();
//        Sleep(1500);
//        ReleaseMutex(Mutex);	//V(mutex);
//        ReleaseSemaphore(FullSemaphore,1,NULL);	//V(full);
//    }
//    return 0;
//}
//
////������
//DWORD  WINAPI Consumer(LPVOID lpPara)
//{
//    while(p_ccontinue){
//        WaitForSingleObject(FullSemaphore,INFINITE);	//P(full);
//        WaitForSingleObject(Mutex,INFINITE);		//P(mutex);
//        Take();
//        Consume();
//        Sleep(1500);
//        ReleaseMutex(Mutex);		//V(mutex);
//        ReleaseSemaphore(EmptySemaphore,1,NULL);		//V(empty);
//    }
//    return 0;
//}
//
//
//
///*  ʵ����Դ���� */
////�嵥5-1  �˽�ͼ����̵������ڴ�ռ�
//// ����vmwalker
//#include <windows.h>
//#include <iostream>
//#include <shlwapi.h>
//#include <iomanip>
//#pragma comment(lib, "Shlwapi.lib")
//
//// �Կɶ���ʽ���û���ʾ�����ĸ���������
//// ������Ǳ�ʾ����Ӧ�ó�����ڴ���з��ʵ�����
//// �Լ�����ϵͳǿ�Ʒ��ʵ�����
//inline bool TestSet(DWORD dwTarget, DWORD dwMask)
//{
//    return ((dwTarget &dwMask) == dwMask) ;
//}
//# define SHOWMASK(dwTarget, type) \
//if (TestSet(dwTarget, PAGE_##type) ) \
//    {std :: cout << ", " << #type; }
//
//void ShowProtection(DWORD dwTarget)
//{
//    SHOWMASK(dwTarget, READONLY) ;
//    SHOWMASK(dwTarget, GUARD) ;
//    SHOWMASK(dwTarget, NOCACHE) ;
//    SHOWMASK(dwTarget, READWRITE) ;
//    SHOWMASK(dwTarget, WRITECOPY) ;
//    SHOWMASK(dwTarget, EXECUTE) ;
//    SHOWMASK(dwTarget, EXECUTE_READ) ;
//    SHOWMASK(dwTarget, EXECUTE_READWRITE) ;
//    SHOWMASK(dwTarget, EXECUTE_WRITECOPY) ;
//    SHOWMASK(dwTarget, NOACCESS) ;
//}
//
//// �������������ڴ沢���û���ʾ�����ԵĹ�������ķ���
//void WalkVM(HANDLE hProcess)
//{
//    // ���ȣ����ϵͳ��Ϣ
//    SYSTEM_INFO si;
//    :: ZeroMemory(&si, sizeof(si) ) ;
//    :: GetSystemInfo(&si) ;
//
//    // ����Ҫ�����Ϣ�Ļ�����
//    MEMORY_BASIC_INFORMATION mbi;
//    :: ZeroMemory(&mbi, sizeof(mbi) ) ;
//
//    // ѭ������Ӧ�ó����ַ�ռ�
//    LPCVOID pBlock = (LPVOID) si.lpMinimumApplicationAddress;
//    while (pBlock < si.lpMaximumApplicationAddress)
//    {
//        // �����һ�������ڴ�����Ϣ
//        if (:: VirtualQueryEx(
//            hProcess,						// ��صĽ���
//            pBlock,                         // ��ʼλ��
//			&mbi,                           // ������
//            sizeof(mbi))==sizeof(mbi) )		// ��С��ȷ��
//        {
//            // �����Ľ�β�����С
//            LPCVOID pEnd = (PBYTE) pBlock + mbi.RegionSize;
//			TCHAR szSize[MAX_PATH];
//            :: StrFormatByteSize(mbi.RegionSize, szSize, MAX_PATH) ;
//
//            // ��ʾ���ַ�ʹ�С
//            std :: cout.fill ('0') ;
//            std :: cout
//                << std :: hex << std :: setw(8) << (DWORD) pBlock
//                << "-"
//                << std :: hex << std :: setw(8) << (DWORD) pEnd
//                << (:: strlen(szSize)==7? " (" : " (") << szSize
//                << ") " ;
//
//            // ��ʾ���״̬
//            switch(mbi.State)
//            {
//                case MEM_COMMIT :
//					std :: cout << "Committed" ;
//					break;
//                case MEM_FREE :
//					std :: cout << "Free" ;
//					break;
//                case MEM_RESERVE :
//					std :: cout << "Reserved" ;
//					break;
//            }
//            // ��ʾ����
//			if(mbi.Protect==0 && mbi.State!=MEM_FREE)
//            {    mbi.Protect=PAGE_READONLY;     }
//			ShowProtection(mbi.Protect);
//            // ��ʾ����
//            switch(mbi.Type){
//                case MEM_IMAGE :
//					std :: cout << ", Image" ;
//					break;
//				case MEM_MAPPED:
//					std :: cout << ", Mapped";
//					break;
//                case MEM_PRIVATE :
//					std :: cout << ", Private" ;
//					break;
//			}
//            // �����ִ�е�Ӱ��
//            TCHAR szFilename [MAX_PATH] ;
//            if (:: GetModuleFileName (
//                (HMODULE) pBlock,		// ʵ�������ڴ��ģ����
//				szFilename,             //��ȫָ�����ļ�����
//				MAX_PATH)>0)            //ʵ��ʹ�õĻ�������С
//            {
//                // ��ȥ·������ʾ
//                :: PathStripPath(szFilename) ;
//                std :: cout << ", Module: " << szFilename;
//			}
//            std :: cout << std :: endl;
//			// �ƶ���ָ���Ի����һ�¸���
//            pBlock = pEnd;
//        }
//    }
//}
//
//void ShowVirtualMemory()
//{
//    // ���ȣ������ǻ��ϵͳ��Ϣ
//    SYSTEM_INFO si;
//    :: ZeroMemory(&si, sizeof(si) ) ;
//    :: GetSystemInfo(&si) ;
//    // ʹ����Ǹ��������һЩ�ߴ���и�ʽ��
//    TCHAR szPageSize[MAX_PATH];
//    ::StrFormatByteSize(si.dwPageSize, szPageSize, MAX_PATH) ;
//    DWORD dwMemSize = (DWORD)si.lpMaximumApplicationAddress -
//          (DWORD) si.lpMinimumApplicationAddress;
//    TCHAR szMemSize [MAX_PATH] ;
//    :: StrFormatByteSize(dwMemSize, szMemSize, MAX_PATH) ;
//    // ���ڴ���Ϣ��ʾ����
//    std :: cout << "Virtual memory page size: " << szPageSize << std :: endl;
//
//    std :: cout.fill ('0') ;
//    std :: cout << "Minimum application address: 0x"
//            << std :: hex << std :: setw(8)
//            << (DWORD) si.lpMinimumApplicationAddress
//            << std :: endl;
//    std :: cout << "Maximum application address: 0x"
//            << std :: hex << std :: setw(8)
//            << (DWORD) si.lpMaximumApplicationAddress
//            << std :: endl;
//
//    std :: cout << "Total available virtual memory: "
//            << szMemSize << std :: endl ;
//}
//void main()
//{
//	//��ʾ�����ڴ�Ļ�����Ϣ
//	ShowVirtualMemory();
//    // ������ǰ���̵������ڴ�
//	::WalkVM(::GetCurrentProcess());
//	getchar();
//}
//
//
//
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
