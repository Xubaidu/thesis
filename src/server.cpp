#include "network/socket.cpp"

void alice_round(int fd) {
    cout << "alice's round: send OPRF value to bob" << endl;
    int loop_cnt = 0;
    while (1) {
        loop_cnt++;
        string recv_str;
        auto actual_recv_bytes = recv_msg(fd, sender_server, recv_str);
        if (actual_recv_bytes <= 0) break;
        string send_str("OPRF" + std::to_string(loop_cnt));
        auto actual_send_bytes = send_msg(fd, sender_server, send_str); // 模板函数可以不显式地著名模板参数，实参演绎会自动推导
        if (actual_send_bytes <= 0) break;
    }

    cout << "alice's round: send a_set to bob" << endl;
    string send_str("a_set");
    auto actual_send_bytes = recv_msg(fd, sender_server, send_str);

    string recv_str;
    auto actual_recv_bytes = recv_msg(fd, sender_server, recv_str);
}

int main() {
    // 1. 注册 socket
    // AF_INET: IPV4
    // SOCK_STREAM: TCP
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        cout << "socket error" << endl;
    }

    // 2. bind 本地地址和端口
    socket_addr_in server_addr_in;
    memset(&server_addr_in, 0, sizeof(socket_addr_in));
    server_addr_in.sin_family = AF_INET;                // ipv4
    server_addr_in.sin_port = htons(PORT);              // 端口
    server_addr_in.sin_addr.s_addr = htonl(INADDR_ANY); // 填入本机 ip localhost
    int bind_ok = bind(server_fd, reinterpret_cast<socket_addr *>(&server_addr_in), sizeof(socket_addr_in));
    if (bind_ok == -1) {
        cout << "bind error" << endl;
    }

    // 3. listen 客户端
    int listen_ok = listen(server_fd, LISTEN_QUEUE_SISE);
    if (listen_ok == -1) {
        cout << "listen error" << endl;
    }

    while (1) {
        // clientaddr 获取客户端的地址信息，是传出参数
        socket_addr_in client_addr;
        memset(&server_addr_in, 0, sizeof(socket_addr_in));
        socklen_t client_addr_len = sizeof(socket_addr_in);

        // 4. accept 一个客户端
        int client_fd = accept(server_fd, reinterpret_cast<socket_addr *>(&client_addr), &client_addr_len);
        if (client_fd == -1) {
            cout << "accept error" << endl;
            continue;
        }
        show_client_info(&client_addr);

        // 5. Alice's round.
        alice_round(client_fd);

        // 6. close
        close(client_fd);
    }
    close(server_fd);
    return 0;
}