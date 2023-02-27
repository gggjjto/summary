# Liunx安装

## 虚拟网卡

2023/2/20

```shell
LrootElocalhost"] echo ONBOOT=yes >> rets/sysconf ig/network-scripts/ifcfg-ems33-bash: /ets/sysconf ig network-scripts/ifcf g-ens33: No such file or directory
```

打错了报错

```shell
echo ONBOOT=yes >> rec/sysconf ig/network-scripts/ifcfg-ems33
```

2023/2/21(发现前一天的操作错误，正确的方法)

```shell
vi /etc/sysconfig/network-scripts/ifcfg-ens33
#编辑文件，使用ins修改，ESC结束，：wq退出
#配置IP地址信息
IPADDR=192.168.48.130    #ip地址
NETMASK=255.255.255.0    #掩码
GATEWAY=192.168.48.2     #网关
#取消NetworkManager管理
NM_CONTROLLED=no
DNS1=114.114.114.114
DNS2=8.8.8.8
#最后使用重启网络服务
systemctl restart network
```

## 实现可视化界面

```shell
yum groupinstall "X Window System" 　//注意有引号
yum groupinstall "GNOME Desktop" "Graphical Administration Tools"
#使用命令进入图形化界面
startx
#以默认级别运行图形化界面
ln -sf /lib/systemd/system/runlevel5.target /etc/systemd/system/default.target
```

`wget`命令需要安装

```shell
#检查安装
rpm -qa|grep "wget"
#安装wget
yum -y install wget
#测试
wget -h
```

## yum的使用

yum用于下载liunx的软件

1. 使用 ` yum list | grep gcc`查找需要使用的软件
2. 使用`yum [-y] install gcc `下载，`-y`表示`yes`
3. 使用`yum [-y] remove gcc` 删除
4. `ls -l /etc/yum.repos.d/`查看配置yum源
5. `nano CentOS-Base.repo` 查看地址
6. `yum install -y epel-release` 安装扩展`yum`源

## c程序构造

- `touch xx_1.c`创建文件

- `madir learn`创建录目

- `pwd`查看路径

- `gcc xx_1.c -o xx_1.out`直接生成可执行文件（二进制）

- `gcc -e xx_1.c -o xx_1.i` （头文件展开，注释删除，#define宏定义替换）

- `gcc -s xx_1.i -o xx_1.s`（语法分析，词法分析，语义分析，符号分析）

- `gcc -c xx_1.s -o xx_1.o`（汇编指令-->二进制指令，形成符号表）

- `gcc xx_1.o  -o xx_1.out`（合并段表，符号表合并和重定位）

  

## 常见指令 

### 一、

命令行无限输入，停不下来，按`ctrl+c`，或者`ctrl+j`，或者`ctrl+d`解决

```shell
>> whoami		#知晓当前使用的用户
>> pwd			#显示当前所处的路径
>> mkdir [-p]	#在当前路径下，创建目录/文件夹,-p可以创建多级目录
>> rmdir		#删除一个空目录
>> rm			#删除文件和目录
>> touch		#创建指定文本文件
>> shutdown		#-h立即关机，-r重新启动，-t sec后面加秒数
>>cat /etc/redhat-release	#查看版本
>>ip addr		#查看ip地址
```

### 二、查看

```shell
>> ls []		#显示当前目录下所对应的文件列表
# -a 列出目录下的所以文件，包括.开头的隐藏文件【.】当前目录，【..】上级目录
# -l 详细信息，简写ll
# -d 显示目录
# -s 输出文件大小
# -k 以k字节的形式表示文件大小
# -n 用数字的UID，GID代替名称
# -F 在文件名后面用字符说明文件的类型（要大写），*普通文件，/目录，@连接，l表示FIFOs，=表示套接字
# -r 对目录反向排序
# -t 按时间排序
# -r 列出所有子目录的文件
# -1 每行输出1个名称，其他数不可以
>> man		#查询手册
```

### 三、路径

`liunx`中的路径是左斜杆`/`，windows中的路径是右斜杠`\`.

```shell
>> tree		#表示文件树，需要安装
>> cd		# ~返回/root, - 撤回一步
```

### 四、文件操作

```shell
>> nano		#记事本
>> stat		#查看文件属性
>> cp(源文件/源目录)		#复制
>> rmdir	#删除文件空目录
>> rm		#删除，-r强制删除，-i询问删除，-r递归删除
>> mv(src1 dst[/src2])	#src1是目标文件，dst是目录，src2是移动后的文件名
>> cat		#打印文件内容
>> echo		#显示字符
# 输出重定向：
# echo "src" > 文件名 覆盖写入
# 追加重定向
# echo "src" >> 文件名 追加写入
>> more		#向下翻页（回车），q退出
>> less 	#分页
>> head 	#显示开头前n行
>> tail		#显示结尾后n行
#管道，多条命令集合，如：
>> head -520 x_1.txt | tail -20
>> date		#查看时间%Y%m%d%H%M%S，+%s时间戳，-d转化时间戳
>> cal		#查看日历
>> sort		#排序
>> unip		#相邻内容去重
>> find 	#按文件名查询文件
>> whereis	#在系统目录下搜索文件和指令，程序或指定的归档文件，压缩包
>> which 	#搜索对应指令的路径
>> alias 	#给特定的命令起别名
>> grep		#在文件中搜索字符串,-i忽略大小写，-n输出行号，-v反向选择
>> top 		#任务管理器
>> zip/unzip 	#压缩文件（夹）/解压,只对.zip文件起作用
>> wc		#统计文件中的字节数，字数，行数，统计输出
# -l统计行数，-c统计字节数，-m统计字符数，-w统计字数，-L最长行的长度。
>> tar 		#打包/解压,-c创建，-x解开，-t查看，-z是否需要gzip压缩，-j是否需要bzip2压缩
# -v 压缩显示文件，-f使用档名，-C解压到指定目录
# 一般两三条一起用 -czf 打包，-xzf解包，-cvf仅打包，-zcvf打包后，以gzip压缩，
# -ztvf 查询tar file内的文件，-zxvf直接解压
>> bc 		#进行浮点运算
>>uname		#获取电脑和操作系统的相关信息
```

## 五、热键

- `Top`命令提示（只记得一半的命令查一下）
- `ctrl+c`停止当前程序
- `ctrl+d`键盘结束输出，可以代替`exit`
- `ctrl+r`在历史命令中进行搜索
- `PageUp``PageDown`历史命令
- `history`历史所有的指令

## 六、dnf-新一代的RPM软件包管理器

DNF 并未默认安装在 RHEL 或 CentOS 7系统中，**DNF** 是新一代的rpm软件包管理器。他首先出现在 Fedora 18 这个发行版中。而最近，它取代了yum，正式成为 Fedora 22 的包管理器。

```shell
#为了安装 DNF ，您必须先安装并启用 epel-release 依赖(扩展）。
yum install epel-release
#使用 epel-release 依赖中的yum命令来安装 DNF 包。
yum install dnf
#查看系统中可用和不可用的所有的 DNF 软件库
dnf repolist all
#列出所有安装了的 RPM 包
dnf list
#检查系统软件包的更新
dnf check-update
#安装
dnf install
#升级所有的包
dnf update
#删除系统中指定的软件包
dnf remove
#删除缓存的无用软件包
dnf clean all
#查看 DNF 命令的执行历史
def history
```

## 七、安装git

```
dnf install git-all
```

## 八、用户和用户组管理

- Linux系统是一个**多用户多任务的分时操作系统**，任何一个要使用系统资源的用户，都必须首先向系统管理员申请一个账号，然后**以这个账号的身份进入系统**。
- 用户的账号一方面可以帮助系统管理员对使用系统的用户进行**跟踪**，并控制他们对系统资源的访问；另一方面也可以帮助用户**组织文件**，并为用户提供**安全性保护**。
- 每个用户账号都拥有**一个唯一的用户名和各自的口令。**
- 用户在登录时键入正确的用户名和口令后，就能够进入**系统和自己的主目录**

主要内容：

- 用户账号的添加，删除，修改
- 用户口令管理
- 用户组管理

### 1.用户管理

`/etc/passwd`文件是用户管理工作涉及的最重要的一个文件

```shell
# 添加新的用户账号使用useradd命令
useradd 选项 用户名
# -c comment 注释，-d 用户的主目录，-g 用户所属的用户组，-G 用户所属的附加组，-s Shell文件，-u 用户号 如果同时有-o选项，则可以重复使用其他用户的标识号。
#通常用户标识号的取值范围是0～65 535。0是超级用户root的标识号，1～99由系统保留，作为管理账号，普通用户的标识号从100开始。在Linux系统中，这个界限是500。
#删除账号
userdel	xx id #常用 -r和主目录一起删除
#修改账号
usermod xx id #常用的选项包括-c, -d, -m, -g, -G, -s, -u以及-o等，这些选项的意义与useradd命令中的选项一样,-l新用户名
# 用户口令管理
passwd xx id #-l禁用口令，-u口令解锁，-d账号无口令，-f强迫用户下次登入修改口令
#批量添加
#1.创建txt文件，格式：user001::600:100:user:/home/user001:/bin/bash
#2.以root身份执行命令 /usr/sbin/newusers，从刚创建的用户文件user.txt中导入数据，创建用户：
newusers < user.txt
#3.执行命令/usr/sbin/pwunconv,将 /etc/shadow 产生的 shadow 密码解码，然后回写到 /etc/passwd 中，并将/etc/shadow的shadow密码栏删掉。这是为了方便下一步的密码转换工作，即先取消 shadow password 功能。
pwunconv
#4.编辑每个用户的密码对照文件。txt:user001:123456
#5.以 root 身份执行命令 /usr/sbin/chpasswd
chpasswd < passwd.txt
#6.确定密码经编码写入/etc/passwd的密码栏后
pwconv
```

### 2.用户组管理

用户组的所有信息都存放在/`etc/group`文件中

```
#增加用户组
groupadd xx id	#-g Gid 指定组标识号，-o一般与-g选项同时使用，表示新用户组的GID可以与系统已有用户组的GID相同。
#删除
groupdel id
# 修改
groupmod xx id #-g,-o同groupadd，-n new id
```



