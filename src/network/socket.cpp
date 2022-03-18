#pragma once
#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>

#define PORT 8888
#define LISTEN_QUEUE_SISE 2

using socket_addr_in = sockaddr_in;
using socket_addr = sockaddr;
using std::cout;
using std::endl;
using std::string;

const string sender_server = "server";
const string sender_client = "client";

int send_msg(int fd, const string &sender, const string &send_str) {
    int actual_send_bytes = write(fd, send_str.c_str(), send_str.size());
    // sleep(1);
    if (actual_send_bytes > 0) {
        cout << sender + " send: " << send_str << endl;
    } else if (actual_send_bytes == 0) {
        cout << sender + " send closed!" << endl;
    } else {
        cout << sender + " send failed!" << endl;
    }
    return actual_send_bytes;
}

int recv_msg(int fd, const string &receiver, string &recv_str) {
    char str[1024];
    memset(str, 0, sizeof(str));
    int actual_recv_bytes = read(fd, str, sizeof(str));
    // sleep(1);
    if (actual_recv_bytes > 0) {
        recv_str = string(str);
        cout << receiver + " receive: " << recv_str << endl;
    } else if (actual_recv_bytes == 0) {
        cout << receiver + " receive closed!" << endl;
    } else {
        cout << receiver + " receive failed!" << endl;
    }
    return actual_recv_bytes;
}

void show_client_info(const socket_addr_in *outsockaddr) {
    char ipstr[16];
    memset(ipstr, 0, sizeof(ipstr));
    // 将地址从网络字节序转换为点分十进制
    inet_ntop(AF_INET, &(outsockaddr->sin_addr.s_addr), ipstr, sizeof(ipstr));
    cout << "Connected by " << ipstr << "(" << ntohs(outsockaddr->sin_port) << ")" << endl;
}