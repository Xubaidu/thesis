#include "network/socket.cpp"
#include "psi/psi_test.cpp"
#include "common/utils.cpp"
#include <unistd.h>

int main() {
    // 1. 创建socket
    int client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_fd == -1) {
        cout << "socket error" << endl;
    }

    // 2. connect
    socket_addr_in server_addr_in;
    memset(&server_addr_in, 0, sizeof(socket_addr_in));
    server_addr_in.sin_family = AF_INET;
    server_addr_in.sin_port = htons(PORT);
    server_addr_in.sin_addr.s_addr = inet_addr("127.0.0.1");
    int conn_fd = connect(client_fd, reinterpret_cast<socket_addr *>(&server_addr_in), sizeof(socket_addr_in));
    if (conn_fd == -1) {
        cout << "connect error" << endl;
    }

    // 3. bob's round.
    cout << "B = " << vector_to_string(v2) << endl;
    cout << "bob is calculating b_set" << endl;
    for (int i = 0; i < 10; ++i) {
        string send_str;
        send_str += random() % 2 + '0';
        auto actual_send_bytes = send_msg(client_fd, sender_client, send_str);
        string recv_str;
        auto actual_recv_bytes = recv_msg(client_fd, sender_client, recv_str);
    }

    // TODO: 这里有一个先后顺序
    // alice 要先发送，bob 才能接受
    // 但是进程模型没法保证这个顺序，需要想个办法

    cout << "bob is receicing a_set" << endl;
    string recv_str;
    auto actual_recv_bytes = recv_msg(client_fd, sender_client, recv_str);

    cout << "bob is calculating the intersection of a_set and b_set" << endl;
    auto si = test_PSI();

    cout << "bob is sending c_set to alice" << endl;
    string ans = vector_to_string(si);
    auto actual_send_bytes = send_msg(client_fd, sender_client, ans);

    // 4. close
    close(client_fd);
    return 0;
}