#ifndef RL_NET_DELEGATE_HPP
#define RL_NET_DELEGATE_HPP

#include "RLbase.h"
#include <stdlib.h>
#include <stdint.h>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <thread>

namespace RL {
	template<typename SendType, typename RecvType, typename HandlerType>
	class RLNetDelegate {
	public:
		// the m_socket is const
		RLNetDelegate(const std::string& remote_address = "127.0.0.1", unsigned int local_port = 0) 
			: m_remote_address(remote_address)
		{
			boost::asio::ip::address localaddr = boost::asio::ip::address::from_string(RLANYADDR);
			m_localport = boost::asio::ip::udp::endpoint(localaddr, local_port);
			m_socket = new boost::asio::ip::udp::socket(boost::asio::ip::udp::socket(m_io, m_localport));
		}

		~RLNetDelegate() { m_socket->close(); Stop(); m_socket = nullptr; }
		bool Initialize() {
			RLTRY;
			return true;
			RLCATCH;
			return false;
		};
		// start io_service, and we should the recv handler to deal with the recvd data
		bool Start() {
			RLTRY;
			if (!m_started) {
				recv_start();
				m_iothread = std::thread(std::bind(&RLNetDelegate::task, this));
				m_started = true;
			}
			return m_started;
			RLCATCH;
			return false;
		}
		// when stop, we need to stop the io_service and the thread
		bool Stop() {
			RLTRY;
			if (m_started) {
				m_io.stop();
				m_iothread.join();
				m_io.reset();
				m_started = false;
				return m_started == false;
			}
			RLCATCH;
			return false;
		}
		bool Started() {
			return m_started;
		}
		// handler, when we recvd the data, we will run handler with given param
		bool SetHandler(HandlerType handler,void *param) {
			RLTRY;
			m_handler = handler;
			m_param = param;
			return m_handler != nullptr && m_param != nullptr;
			RLCATCH;
			return false;
		}
		// send msg to const recvaddr if fps is not given
		bool DealWith(const SendType& se) {
			RLTRY;
			boost::asio::ip::udp::endpoint remoteport;
			boost::asio::ip::address remoteaddr = boost::asio::ip::address::from_string(m_remote_address);
			remoteport = boost::asio::ip::udp::endpoint(remoteaddr, RLCHECKPORT(REMOTE,BASE));
			size_t status = m_socket->send_to(boost::asio::buffer(&se, sizeof(SendType)), remoteport);
			return status;
			RLCATCH;
			return false;
		}
		// send msg to recvaddr if fps is given.
		// TODO: Only support 2 fps solution, if fps is not support we should give a message
		bool DealWith(const SendType& se, int fps) {
			RLTRY;
			boost::asio::ip::udp::endpoint remoteport;
			boost::asio::ip::udp::endpoint baseport;
			if (fps == 30) {
				remoteport = boost::asio::ip::udp::endpoint(
					boost::asio::ip::address::from_string(m_remote_address), RLCHECKPORT(REMOTE, 30));
			}
			if (fps == 60) {
				remoteport = boost::asio::ip::udp::endpoint(
					boost::asio::ip::address::from_string(m_remote_address), RLCHECKPORT(REMOTE, 60));
			}
			int status = m_socket->send_to(boost::asio::buffer(&se, sizeof(SendType)), remoteport);
			return remoteport == baseport && status;
			RLCATCH;
			return false;
		}
	private:
		void task() { m_io.run(); }
		// io_service task
		void recv_start() {
			m_socket->async_receive_from(boost::asio::buffer(&m_recvdata, sizeof(m_recvdata))
				, m_localport
				, boost::bind(&RLNetDelegate::recv_handler
					, this
					, boost::asio::placeholders::error));

		}
		void recv_handler(const boost::system::error_code &ec) {
			if (ec.value() == boost::system::errc::success) {
				if (m_handler)
					m_handler(m_recvdata, m_param);
				else
					printf("[RL]no matching handler!\n");
			}
			else {
				printf("[RL]No message recved.maybe python not run: %d\n", ec.value());
			}

			recv_start();
		}

	private:
		boost::asio::ip::udp::endpoint m_localport;
		boost::asio::ip::udp::socket *m_socket = nullptr;
		boost::asio::io_service m_io;
		std::thread m_iothread;
		RecvType m_recvdata;
		HandlerType m_handler = nullptr;
		void *m_param = nullptr;
		bool m_started = false;
		std::string m_remote_address;
	};
}



#endif
