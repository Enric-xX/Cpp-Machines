#include <boost/asio.hpp>
#include <iostream>
#include <vector>
#include <memory>

using boost::asio::ip::tcp;

class NodeServer {
public:
    NodeServer(short port) : acceptor_(io_context_, tcp::endpoint(tcp::v4(), port)) {
        start_accept();
    }

    void run() { io_context_.run(); }

private:
    void start_accept() {
        // Usamos smart pointers para gestionar la vida de la conexión automáticamente
        auto socket = std::make_shared<tcp::socket>(io_context_);
        acceptor_.async_accept(*socket, [this, socket](const boost::system::error_code& error) {
            if (!error) {
                handle_client(socket);
            }
            start_accept(); // Bucle de aceptación asíncrona
        });
    }

    void handle_client(std::shared_ptr<tcp::socket> socket) {
        auto buffer = std::make_shared<std::vector<char>>(1024);
        socket->async_read_some(boost::asio::buffer(*buffer),
            [socket, buffer](const boost::system::error_code& ec, std::size_t length) {
                if (!ec) {
                    std::string data(buffer->data(), length);
                    std::cout << "[Nodo] Ejecutando comando: " << data << std::endl;
                    
                    // Respondemos con el resultado del proceso
                    std::string response = "ACK: Comando ejecutado";
                    boost::asio::write(*socket, boost::asio::buffer(response));
                }
            });
    }

    boost::asio::io_context io_context_;
    tcp::acceptor acceptor_;
};
