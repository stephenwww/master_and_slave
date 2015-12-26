# 主从节点通信设计
 
摘要：通过boost.MPI实现了主节点广播任务、从节点接受任务，以及主节点阻塞地等待从节点完成任务。  
<br>

## I. 安装boost

在boost官网选择与系统对应的[tutorial](http://www.boost.org/doc/libs/1_60_0/more/getting_started/)进行安装。  
<br>

## II. 安装Open MPI

在[Open MPI官网](http://www.open-mpi.org/)选择与系统对应的版本进行安装。  

关于Open MPI的介绍，可参见我写的《Open MPI调研报告》。  
<br>

## III. 安装boost.MPI

以Mac OS X为例：

- 若使用brew, 则brew install boost --with-mpi --without-single即可。这样安装的是携带boost.MPI的整个boost
- 若在官方下载boost源，本地编译的话，则可继续参见boost官网的[tutorial](http://www.boost.org/doc/libs/1_60_0/more/getting_started/).  
<br>

## IV. 业务逻辑

### 4.1 master节点

master节点通过boost::mpi::broadcast阻塞地向各个节点广播消息，并阻塞等待在barrier栅栏上。

### 4.2 slave节点

slave节点通过boost::mpi::broadcast阻塞地等待master节点的广播，并阻塞等待在barrier栅栏上。  
<br>

## V. 编译与运行

    $ make 
    $ mpirun -np 1 master : -np 2 slave

编译后，在本地运行1个master进程，2个slave进程。  
<br>

## VI. 实验结果分析

    slave 1 action
    slave 2 action
    master issue
    slave 1 commit: ping
    slave 2 commit: ping
    master issue done

1. 三个进程（1个master进程，2个slave进程）的启动顺序是不确定的，所以前三行的输出顺序是不确定的。
2. master节点broadcast出命令（如ping），并阻塞等待在barrier栅栏上。
3. slave节点阻塞地等待master节点的广播，在获得信息后输出commit信息，并阻塞等待在barrier栅栏上。
4. 当所有节点都等待在栅栏上时，master知道工作完成，输出master issue done.

