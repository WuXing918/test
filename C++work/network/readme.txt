主机字节序：
			不同的CPU有不同的字节序类型，这些字节序是指整数在内存中保存的顺序，
	这个叫做主机序。最常见的有两种
			1．Little endian：低字节存高地址，高字节存低地址 
			2．Big endian：低字节存低地址，高字节存高地址
网络字节序
			网络字节顺序是TCP/IP中规定好的一种数据表示格式，它与具体的CPU类型、
	操作系统等无关，从而可以保证数据在不同主机之间传输时能够被正确解释。网络
	字节顺序采用big endian排序方式。


对于write，send，sendto，sendmsg；
ssize_t send(int sockfd, const void *buf, size_t len, int flags);

ssize_t sendto(int sockfd, const void *buf, size_t len, int flags,
                      const struct sockaddr *dest_addr, socklen_t addrlen);

ssize_t sendmsg(int sockfd, const struct msghdr *msg, int flags);
----------------------------------------------------------------------------
flags：
		MSG_CMSG_CLOEXEC 
 
      MSG_DONTWAIT  

      MSG_ERRQUEUE
 
		MSG_OOB
               
      MSG_PEEK
               
      MSG_TRUNC 
           
      MSG_WAITALL  
	
		MSG_EOR
             
      MSG_TRUNC
               
      MSG_CTRUNC
               
      MSG_OOB
              
      MSG_ERRQUEUE

-------------------------------------------------------------------

对于read，recv，recvfrom，recvmsg；

ssize_t recv(int sockfd, void *buf, size_t len, int flags);

ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags,
                        struct sockaddr *src_addr, socklen_t *addrlen);

ssize_t recvmsg(int sockfd, struct msghdr *msg, int flags);
--------------------------------------------------------------- 
flags：
		 MSG_CONFIRM  

       MSG_DONTROUTE
              
       MSG_DONTWAIT         

       MSG_EOR  
               
       MSG_MORE  
              
       MSG_NOSIGNAL  
              
       MSG_OOB
              











