#pragma once

#include <array>
#include <vector>
#include <map>
#include <deque>

#include <Server.h>

struct ConnectionInfo {
  uint32_t id;
  std::string address;
  uint16_t port;
};

class FrontendServer : public Server<SizedClientConnection> {
public:
  FrontendServer(uint16_t port);
  
  virtual void handleClientConnection(uint32_t id, const std::string& address, uint16_t port) override;
  virtual void handleClientMessage(uint32_t id, const std::string& message) override;
  virtual void handleClientDisconnection(uint32_t id) override;
  
  void newInput(const std::string& name, const std::string& text);
  
  void sendKeepAlivePing();
  
private:
  std::map<uint32_t, ConnectionInfo> connectionInfos;
  
  std::string getTimeStr() const;
  std::string clean(const std::string& message) const;
};

class ChatRelayServer : public Server<HttpClientConnection> {
public:
  ChatRelayServer();
  virtual ~ChatRelayServer();
  virtual void handleClientMessage(uint32_t id, const std::string& message) override;

  void sendKeepAlivePing();
private:
  FrontendServer frontendConnections1{11006};
  FrontendServer frontendConnections2{11007};
    
  std::pair<std::string,std::string> parseParameter(const std::string& param) const;
  std::map<std::string,std::string> parseParameters(const std::string& params) const;
};
