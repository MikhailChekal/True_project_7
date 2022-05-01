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

    tcp::acceptor acceptor_server(
            io_service,tcp::endpoint(tcp::v4(), 65000));

    tcp::socket server_socket(io_service);

    acceptor_server.accept(server_socket);

    string u_name = accept(server_socket);
    u_name.pop_back();

    string response, reply;
    reply = "Hello " + u_name + "!";
    cout << "Server: " << reply << endl;
    send(server_socket, reply);

    while (true) {
        response = accept(server_socket);

        response.pop_back();

        if (response == "exit") {
            cout << u_name << " left!" << endl;
            break;
        }
        cout << u_name << ": " << response << endl;

        cout << "Server"
             << ": ";
        getline(cin, reply);
        send(server_socket, reply);

        if (reply == "exit")
            break;
    }
    return 0;
}