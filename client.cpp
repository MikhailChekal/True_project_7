#include <boost/asio.hpp>
#include <iostream>
using namespace std;
using namespace boost::asio;
using namespace boost::asio::ip;

string accept(tcp::socket& socket)
{
    boost::asio::streambuf buf;
    read_until(socket, buf, "\n");
    string data = buffer_cast<const char*>(buf.data());
    return data;
}

void send(tcp::socket& socket, const string& message)
{
    write(socket,buffer(message + "\n"));
}

int main()
{
    io_service io_service;
    ip::tcp::socket client_socket(io_service);
    client_socket.connect(tcp::endpoint(address::from_string("127.0.0.1"),65000));

    cout << "Enter your name: ";
    string u_name, reply, response;
    getline(cin, u_name);

    send(client_socket, u_name);

    while (true) {

        response = accept(client_socket);

        response.pop_back();

        if (response == "exit") {
            cout << "Connection terminated" << endl;
            break;
        }
        cout << "Server: " << response << endl;

        cout << u_name << ": ";
        getline(cin, reply);
        send(client_socket, reply);

        if (reply == "exit")
            break;
    }
    return 0;
}