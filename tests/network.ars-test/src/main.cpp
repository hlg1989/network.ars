#include "pch.h"
#include "Service/RLServiceJanus/RLServiceJanusCInterface.h"
#include <thread>
#include <iostream>
static void rl_bitrate_receive_callback(RLRecvType recv, void *ptr){
    std::cout << "addr: " << recv.addr << ", bitrate: " << recv.bitrate << std::endl;
}

int main(int argc, char** argv)
{
    /* code */
    void *handle = RLServiceUDPDelegateCreate("127.0.0.1");
    RLServiceUDPDelegateSetHandler(handle, rl_bitrate_receive_callback, nullptr);
    RLServiceUDPDelegateInitial(handle);
    RLServiceUDPDelegateStart(handle);
    std::thread([=] {
        while (true)
        {
            RLSTATE state;
            state.bitrate = 10000;
            state.recv_bitrate = 10000;
            state.buffer_size = 2000;
            state.delay = 10;
            state.packet_loss_rate = 0;
            state.nack_sent_count = 0;
            RLServiceUDPDelegateDealWith(handle, state, const_cast<char*>("12345"), 30);
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }).join();
    return 0;
}
