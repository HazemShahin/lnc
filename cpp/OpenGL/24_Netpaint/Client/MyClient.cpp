#include "MyClient.h"

#include <ColorConversion.h>

#ifndef _WIN32
  #include "helvetica_neue.inc"
  FontRenderer MyClient::fr{fontImage, fontPos};
  bool acceptFastMousePosUpdates = true;
#else
  FontRenderer MyClient::fr{"helvetica_neue.bmp", "helvetica_neue.pos"};
  bool acceptFastMousePosUpdates = false;
#endif

MyClient::MyClient(const std::string& address, uint16_t port, const std::string& name) :
  Client{address, port , "", 5000},
  name{name},
  color{ColorConversion::hsvToRgb<float>({360*staticRand.rand01(),0.5f,1.0f}), 1.0f}
{
}

void MyClient::moveMouse(uint32_t userID, const Vec2& pos) {
  for (size_t i = 0;i<clientInfo.size();++i) {
    if (clientInfo[i].id == userID) {
      clientInfo[i].pos = pos;
      break;
    }
  }
}

void MyClient::addMouse(uint32_t userID, const std::string& name, const Vec4& color) {
  bool found{false};
  for (size_t i = 0;i<clientInfo.size();++i) {
    if (clientInfo[i].id == userID) {
      clientInfo[i].name = name;
      clientInfo[i].image = fr.render(name);
      clientInfo[i].color = color;
      found = true;
      break;
    }
  }
  if (!found) {
    clientInfo.push_back({userID, name, color, {0,0}, fr.render(name)});
  }
}

void MyClient::removeMouse(uint32_t userID) {
  for (size_t i = 0;i<clientInfo.size();++i) {
    if (clientInfo[i].id == userID) {
      clientInfo.erase(clientInfo.begin()+i);
      break;
    }
  }
}

void MyClient::initDataFromServer(const Image& serverImage,
                                  const std::vector<ClientInfo>& mi) {
  canvasImage = std::make_shared<Image>(serverImage);
  canvasDims = Dimensions{serverImage.width, serverImage.height};
  
  clientInfo.clear();
  for (const ClientInfo& m : mi) {
    clientInfo.push_back({m.id, m.name, m.color, m.pos, fr.render(m.name) });
  }
  initComplete = true;
}
  
void MyClient::handleNewConnection() {
  ConnectMessage l(name, color, acceptFastMousePosUpdates);
  sendMessage(l.toString());
}

void MyClient::handleServerMessage(const std::string& m) {
  const std::string message = m + char(1);  // HACK: support for old clients
  
  MessageType pt = identifyString(message);
     
  miMutex.lock();
  try {
    switch (pt) {
      case MessageType::MousePosMessage : {
        MousePosMessage l(message);
        moveMouse(l.userID, l.mousePos);
        break;
      }
      case MessageType::NewUserMessage  : {
        NewUserMessage l(message);
        addMouse(l.userID, l.name, l.color);
        break;
      }
      case MessageType::LostUserMessage : {
        LostUserMessage l(message);
        removeMouse(l.userID);
        break;
      }
      case MessageType::InitMessage : {
        InitMessage l(message);
        initDataFromServer(l.image, l.clientInfos);
        break;
      }
      case MessageType::CanvasUpdateMessage : {
        CanvasUpdateMessage l(message);
        const Vec2 normPos{(l.pos.x/float(canvasDims.width)-0.5f) * 2.0f,
                           (l.pos.y/float(canvasDims.height)-0.5f) * 2.0f};
        moveMouse(l.userID, normPos);
        paint(l.color, l.pos);
        break;
      }
      case MessageType::ConnectMessage : {
        std::cerr << "Netwerk Error: ConnectMessage should never be send to a client" << std::endl;
        break;
      }
      default:
        std::cerr << "Netwerk Error: unknown message " << int(pt) << " received" << std::endl;
        break;
    };
  } catch (const MessageException& e) {
    std::cerr << "MessageException: " << e.what() << std::endl;
  }

  miMutex.unlock();
}

void MyClient::setMousePos(const Vec2& normPos) {
  if (isConnecting() || !initComplete) {
    initComplete = false;
    return;
  }
  
  MousePosMessage m(normPos);
  sendMessage(m.toString());
}


void MyClient::paint(const Vec2i& pos) {
  if (isConnecting() || !initComplete) {
    initComplete = false;
    return;
  }

  paint(color, pos);
  CanvasUpdateMessage m{color, pos};
  sendMessage(m.toString());
}

const std::vector<ClientInfoClientSide>& MyClient::getClientInfos() const {
  if (!rendererLock) {
    throw std::runtime_error("getClientInfos called without lockData");
  }
  return clientInfo;
}
  
void MyClient::lockData() {
  if (rendererLock) {
    throw std::runtime_error("lockData called repeatedly without unlockData");
  }
  miMutex.lock();
  rendererLock = true;
}

void MyClient::unlockData() {
  if (!rendererLock) {
    throw std::runtime_error("unlockData called without lockData");
  }
  miMutex.unlock();
  rendererLock = false;
}

Vec4 MyClient::getColor() const {
  return color;
}

bool MyClient::isValid() const {
  return initComplete;
}

void MyClient::setColor(const Vec4& color) {
  this->color = color;
}

void MyClient::paint(const Vec4& color, const Vec2i& pos) {
  if (pos.x < 0 || uint32_t(pos.x) >= canvasDims.width) return;
  if (pos.y < 0 || uint32_t(pos.y) >= canvasDims.height) return;
    
  paintQueue.push({color,pos});
}
