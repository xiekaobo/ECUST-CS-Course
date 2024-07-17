# Myshell

### 介绍

a shell for linux

##### 实现与未实现

1.各种外置命令实现了，内置命令暂时还没写完；
history完成  history别忘了该宏定义 HIST_FILE_PATH的路径
cd完成
pwd完成
2.重定向操作（输入和输出）完美实现；
3.管道操作可以实现多个；
4.cd的报错可以先忽略，能够正确cd（等内置命令实现后再改）；
5.对某些符号的处理$HOME可能要在读取后进行替换（应该不难）；
6.命令补全（命令补全加上了，文件名补全稍后加）；
7.后台执行（实现）

24/6/9 update by marston  
to-do list:  
unalias  
    外转内：  
    echo：环境变量 + others  
    cat  
    ls  
    grep  
    type  

Roy表示不想做： ∆∆Tab： 根目录+环境变量Δ
Roy表示我tmd Marston表示没办法 加油!

24/6/10 updated by Marston  
unalias和ls（-l）已做完  
后台执行输出PID进程号已实现  
还差：  echo  cat  grep  type  
  
24/6/15 updated by Marston  
即将完成：  type and echo  

24/6/16 by M  
type 已完成  发现Roy说pwd写了，其实根本没写！！！  
to-do list更新：  
cat grep   
done list更新：  
ls cd(parse) alias/unalias type history（进行了略微修改，现可以打印all） pwd   
echo实现了 echo $HOME /$USER/ $PATH 等  
      echo  字符串/filename  
      echo -n [...] 不换行输出  
      \n \t \\ \' \"  
21:35 cat也实现了 还剩个grep  
22：20 grep实现，剩管道调用+写入系统    
重定向 管道 命令补全(complection) 后台执行(&)  

22:44 实现了将myshell写入系统  congrats！ 
6/17 实现了多管道中第一条指令的输入重定向和最后的输出重定向（重定向符号前面要打空格）
    实现了文件目录补全和文件名补全，在文件目录补全时要主要目录名后面要加字符才行，不然会报错！
    比如：cat -l test/<tab> 会出错 ，其实原因很简单，但是Roy不想改了，今天很难受。 Roy要休息了！:|

        cat -l test/1<tab> 即可正常补全！
  
##### 预计时间和我的顺序

管道操作（2～3d）  **finished** 
后台执行（2～3d）  **finished** 
内置命令（2d）
剩下的事情（2d）
预计完成时间：6月10号（16周一～16周周三）

### 使用说明

cd到本文件夹，在bashshell中输入make命令，然后使用./shell命令执行  
！更改shell.h中PATH为自己本地文件夹路径   
！！！  将myshell植入系统环境变量并切换默认shell说明（以macOS为例）：  
1、将myshell可执行文件copy至/usr/local/bin：  sudo cp myshell /usr/local/bin/myshell  
2、将 myshell 添加到 /etc/shells ：  echo "/usr/local/bin/myshell" | sudo tee -a /etc/shells  
3、更改当前用户的默认 shell：  chsh -s /usr/local/bin/myshell  
4、退出重启可验证：  echo $SHELL  发现已转换shell至myshell  若想转回原zsh shell 重复3、4即可  
请在一行内输入完命令，否则delete键不方便使用   
多管道操作的实现：
![输入图片说明](%E6%88%AA%E5%B1%8F2024-06-03%2018.53.56.png)
后台（异步）执行的实现：
![输入图片说明](%E6%88%AA%E5%B1%8F2024-06-03%2020.13.23.png)

2024/06/12

Bug修复：解决了在Linux上无法使用多管道命令的问题，原因是在execute_pipe2函数中对char ***argus的处理不当，现在在Mac和Linux上都可以执行多管道命令了。

![输入图片说明](%E6%88%AA%E5%B1%8F2024-06-12%2022.41.01.png)