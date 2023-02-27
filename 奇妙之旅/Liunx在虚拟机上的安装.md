# Liunx在虚拟机上的安装

## 第一步

安装[VMware Workstation Pro]([Windows 虚拟机 | Workstation Pro | VMware | CN](https://www.vmware.com/cn/products/workstation-pro.html)),这是付费版（懂的都懂，百度VMware Workstation Pro17密钥大全）

密钥：MC60H-DWHD5-H80U9-6V85M-8280D

傻瓜式安装一路点即可，记得修改安装路径

## 第二步

[centos-7-isos-x86_64安装包下载_开源镜像站-阿里云 (aliyun.com)](https://mirrors.aliyun.com/centos/7/isos/x86_64/?spm=a2c6h.25603864.0.0.54ce45115NB9j2)

下载centos的Liunx版本-ios（网速不好要下很久）

如果自己电脑配置比较低，可以选择boot类型的iso镜像文件

## 第三步

1. 打开VMware
2. 创建新的虚拟机
3. 自定义
4. 硬件兼容Workstation 16.x（理论上来说硬件版本越高，兼容性越好）
5. 稍后安装操作系统
6. Linux
7. 自己输入名字和路径
8. 处理器配置：建议1 1 （处理器内核总数=处理器数量*每个处理器内核数量，根据自己电脑配置，合理选择数量，毕竟会影响电脑的运行速度）
9. 设置虚拟机内存。在推荐范围内均可
10. 网络类型：使用主机类型模式网络
11. 选择I/O控制器类型和磁盘类型均选择系统推荐的选项即可
12. 选择磁盘：创建新虚拟磁盘（对第一次安装），使用现有虚拟磁盘（第n次安装）
13. 指定磁盘容量。即分配给磁盘的空间大小。推荐大小就够用，将虚拟文件拆成多个文件即可（最后一步了）
14. 最后：选择ISO文件准备开机（在虚拟机设置里）

如有错误，才疏学浅，恳请指正。