#ifndef BONEFISH_DAEMON_HPP
#define BONEFISH_DAEMON_HPP

#include <bonefish/serialization/wamp_serializers.hpp>
#include <bonefish/serialization/msgpack_serializer.hpp>
#include <bonefish/router/wamp_routers.hpp>
#include <bonefish/websocket/websocket_server.hpp>

#include <boost/asio/io_service.hpp>
#include <boost/asio/signal_set.hpp>
#include <memory>

namespace bonefish
{

class tcp_server;
class wamp_routers;
class wamp_serializers;
class websocket_server;

class daemon
{
public:
    daemon();
    ~daemon();

    void run();
    void shutdown();
    boost::asio::io_service& io_service();

private:
    void shutdown_handler();
    void termination_signal_handler(
            const boost::system::error_code& error_code, int signal_number);

private:
    boost::asio::io_service m_io_service;
    std::shared_ptr<boost::asio::io_service::work> m_work;
    boost::asio::signal_set m_termination_signals;

    std::shared_ptr<bonefish::wamp_routers> m_routers;
    std::shared_ptr<bonefish::wamp_serializers> m_serializers;
    std::shared_ptr<bonefish::tcp_server> m_tcp_server;
    std::shared_ptr<bonefish::websocket_server> m_websocket_server;
};

} // namespace bonefish

#endif // BONEFISH_DAEMON_H