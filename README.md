# unpv12e_dev
UNIX Network Programming, Volume 1 2e source
[root@localhost unpv12e_dev]# uname -r 
2.6.32-431.el6.x86_64
[root@localhost unpv12e_dev]# 

    cd unpv12e
    ./configure    # try to figure out all implementation differences

    cd lib         # build the basic library that all programs need
    make           # use "gmake" everywhere on BSD/OS systems

    cd ../libfree  # continue building the basic library
    make

    cd ../libgai   # the getaddrinfo() and getnameinfo() functions
    make
	
# renbin.guo added 开始运行一个实例

    cd ../intro    # build and test a basic client program
    make daytimetcpcli
    ./daytimetcpcli 127.0.0.1

	
	

问题1：

[root@localhost lib]# cd ../libfree/
[root@localhost libfree]# make
gcc -I../lib -g -O2 -D_REENTRANT -Wall   -c -o inet_ntop.o inet_ntop.c
inet_ntop.c: In function ‘inet_ntop’:
inet_ntop.c:61: error: argument ‘size’ doesn’t match prototype
/usr/include/arpa/inet.h:65: error: prototype declaration
make: *** [inet_ntop.o] Error 1
[root@localhost libfree]# 

解决：
 size_t size ->改成 socklen_t size 


# 问题2：

编译libgai
http://blog.csdn.net/robbie2046/article/details/7068302
找到下面一行注释掉
LIBGAI_OBJS="getaddrinfo.o getnameinfo.o freeaddrinfo.o gai_strerror.o"
然后用下面的代码代替注释掉的那行
LIBGAI_OBJS=
if test "$ac_cv_func_getaddrinfo" = no ; then
LIBGAI_OBJS="$LIBGAI_OBJS getaddrinfo.o"
fi
if test "$ac_cv_func_getnameinfo" = no ; then
LIBGAI_OBJS="$LIBGAI_OBJS getnameinfo.o"
fi
if test "$ac_cv_func_freeaddrinfo" = no ; then
LIBGAI_OBJS="$LIBGAI_OBJS freeaddrinfo.o"
fi
if test "$ac_cv_func_gai_strerror" = no ; then
LIBGAI_OBJS="$LIBGAI_OBJS gai_strerror.o"
fi

gedit Make.defines   
在文件末尾加上下面这句：
CFLAGS = -g -O2 -D_REENTRANT -Wall -D_GNU_SOURCE


# 问题3 
遇到unp.h 重复定义的问题

解决：	
	直接注释掉

