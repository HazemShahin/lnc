#pragma once

#include <sstream>
#include <string>
#include <memory>
#include <vector>
#include <exception>

#include <NetCommon.h>

constexpr uint16_t serverPort = 11003;

enum class GameIDs {
  InvalidID = 0,
  BattleShips = 1,
  BattleShips2 = 2
};

enum class MessageType {
  InvalidMessage = 0,
  BasicMessage = 1,
  ConnectMessage = 2,
  LostUserMessage = 3,
  PairedMessage = 4,
  ReadyForNewMessage = 5,
  GameMessage = 6
};

MessageType identifyString(const std::string& s);

struct BasicMessage {
  MessageType pt;
  uint32_t userID{0};
  Tokenizer tokenizer;

  BasicMessage(const std::string& message) :
    tokenizer{message}
  {
    if (tokenizer.nextString() != "game") throw MessageException("Invalid message");
    pt = MessageType(tokenizer.nextUint32());
    userID = tokenizer.nextUint32();
    pt = MessageType::BasicMessage;
  }
  
  BasicMessage() :
    tokenizer{""}
  {
    pt = MessageType::BasicMessage;
  }
  
  virtual ~BasicMessage() {}
  
  virtual std::string toString() {
    StringEncoder coder;
    coder.add("game");
    coder.add(int(pt));
    coder.add(userID);
    return coder.getEncodedMessage();
  }
};

struct LostUserMessage : public BasicMessage {
  
  LostUserMessage(const std::string& message) :
    BasicMessage(message)
  {
    pt = MessageType::LostUserMessage;
  }
  
  LostUserMessage() {
    pt = MessageType::LostUserMessage;
  }
  
  virtual ~LostUserMessage() {}
};


struct PairedMessage : public BasicMessage {
  std::string name;
  uint32_t level;

  PairedMessage(const std::string& message) :
    BasicMessage(message)
  {
    name = tokenizer.nextString();
    level = tokenizer.nextUint32();
    pt = MessageType::PairedMessage;
  }
  
  PairedMessage(const std::string& name, uint32_t level) :
    name(name),
    level(level)
  {
    pt = MessageType::PairedMessage;
  }
  
  virtual ~PairedMessage() {}
  
  virtual std::string toString() override {
    StringEncoder coder;
    coder.add(name);
    coder.add(level);
    return BasicMessage::toString() + coder.getEncodedMessage();
  }
};


struct ReadyForNewMessage : public BasicMessage {
  
  ReadyForNewMessage(const std::string& message) :
    BasicMessage(message)
  {
    pt = MessageType::ReadyForNewMessage;
  }
  
  ReadyForNewMessage() {
    pt = MessageType::ReadyForNewMessage;
  }
  
  virtual ~ReadyForNewMessage() {}
};

struct ConnectMessage : public BasicMessage {
  std::string name;
  GameIDs gameID;
  uint32_t level;
  
  ConnectMessage(const std::string& message) :
    BasicMessage(message)
  {
    name = tokenizer.nextString();
    gameID = (GameIDs)tokenizer.nextUint32();
    level = tokenizer.nextUint32();
    pt = MessageType::ConnectMessage;
  }
  
  ConnectMessage(const std::string& name, GameIDs gameID, uint32_t level) :
    name(name),
    gameID(gameID),
    level(level)
  {
    pt = MessageType::ConnectMessage;
  }
  
  virtual ~ConnectMessage() {}
  
  virtual std::string toString() override {
    StringEncoder coder;
    coder.add(name);
    coder.add(uint32_t(gameID));
    coder.add(level);
    return BasicMessage::toString() + coder.getEncodedMessage();
  }
};

struct GameMessage : public BasicMessage {
  std::string payload;
  
  GameMessage(const std::string& message) :
    BasicMessage(message)
  {
    payload = tokenizer.nextString();
    pt = MessageType::GameMessage;
  }
  
  GameMessage() :
    payload{}
  {
    pt = MessageType::GameMessage;
  }
  
  virtual ~GameMessage() {}
  
  virtual std::string toString() override {
    StringEncoder coder;
    coder.add(payload);
    return BasicMessage::toString() + coder.getEncodedMessage();
  }
};
