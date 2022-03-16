#include "network/socket.cpp"
#include "psi/psi_test.cpp"
#include "common/utils.cpp"

int main() {
    // 1. 创建socket
    int client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_fd == -1) {
        cout << "socket error" << endl;
    }

    // 2. connect
    socket_addr_in client_addr_in;
    memset(&client_addr_in, 0, sizeof(socket_addr_in));
    client_addr_in.sin_family = AF_INET;
    client_addr_in.sin_port = htons(PORT);
    client_addr_in.sin_addr.s_addr = inet_addr("127.0.0.1");
    int conn_fd = connect(client_fd, reinterpret_cast<socket_addr *>(&client_addr_in), sizeof(socket_addr_in));
    if (conn_fd == -1) {
        cout << "connect error" << endl;
    }

    // 3. bob's round.
    cout << "bob's round: calculate b_set" << endl;
    for (int i = 0; i < 10; ++i) {
        string send_str;
        send_str += random() % 2 + '0';
        auto actual_send_bytes = send_msg(client_fd, sender_client, send_str);
        string recv_str;
        auto actual_recv_bytes = recv_msg(client_fd, sender_client, recv_str);
    }

    cout << "bob's round: calculate the intersection of a_set and b_set" << endl;

    auto si = test_PSI();

    cout << "bob's round: send answer to alice" << endl;
    string ans = vector_to_string(si);
    auto actual_send_bytes = send_msg(client_fd, sender_client, ans);
    
    // 4. close
    close(client_fd);
    return 0;
}