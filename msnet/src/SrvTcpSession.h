#ifndef TCPSESSION_H
#define TCPSESSION_H
#pragma once
#include "AsioBase.h"
//
#include "AVframeRtmp.h"
// #include "AVmp4.h"
#include "Common_Def.h"
#include "buffer.h"
#include <string>
class TcpSession : public std::enable_shared_from_this<TcpSession>, asio::noncopyable {
private:
    asio::ip::tcp::socket _socket;
    char                  _data[1024];
    std::string           _devId;
    bytes::Buffer         _recvBuffer;
    bytes::Buffer         _sendBuffer;
    AVframeRtmp           _rtmpPublisher;
    // AVmp4                 _mp4Writer;
    bool _isPublisherWait;

public:
    TcpSession(asio::ip::tcp::socket socket);
    TcpSession(asio::io_service& context);
    ~TcpSession();

    void                   start();
    bool                   dispatchMessage(char* data, int len);
    asio::ip::tcp::socket& socket();

private:
    void doRead();
    void doSocketWrite(char* data, int len);
    void doSocketBufferWrite(int len);
    // 消息头
    int doRspMsgHeader(ho::MsgHeader_t msg);
    // 处理心跳
    int doRspHeartbeat();
    // 媒体链路注册响应
    int doRspMediaRegister(char* req, int len);
};

#endif  // !TCPSESSION_H
