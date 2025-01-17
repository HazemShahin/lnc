#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <queue>
#include <optional>

#include <Client.h>

#include "../25_GenericGameServer/NetGame.h"
#include "ShipPlacement.h"

enum class GameMessageType {
  Invalid = 0,
  EncryptedShipPlacement = 1,
  Aim = 2,
  Shot = 3,
  ShotResult = 4,
  ShipPlacementPassword = 5,
  ChatMessage = 6,
};

enum class ShotResult {
  HIT = 0,
  MISS = 1,
  SUNK = 2
};

class GameClient : public Client {
public:
  GameClient(const std::string& address, uint16_t port, const std::string& name, uint32_t level);

  virtual void handleNewConnection() override;
  virtual void handleServerMessage(const std::string& message) override;

  bool getInitMessageSend() const {
    return initMessageSend;
  }
  
  std::optional<std::pair<std::string, uint32_t>> getReceivedPairingInfo() const {
    return receivedPairingInfo;
  }
  
  std::optional<std::string> getEncryptedShipPlacement() const;
  void sendEncryptedShipPlacement(const std::string& sp);

  std::optional<std::string> getShipPlacementPassword() const;
  void sendShipPlacementPassword(const std::string& sp);
  
  std::vector<Vec2ui> getShotsReceived();
  void sendShotResult(const ShotResult& r);
  std::vector<ShotResult> getShotResults();
  Vec2ui getAim();
  
  void shootAt(const Vec2ui& pos);
  void aimAt(const Vec2ui& pos);
  
  void readyForNewPlayer();
  
  void sendChatMessage(const std::string& msg);
  std::vector<std::string> getChatMessages();
  
private:
  std::string name{""};
  uint32_t level{0};
  std::optional<std::string> otherShipPlacement{};
  std::optional<std::string> shipPlacementPassword{};
  
  std::mutex aimMutex;
  std::mutex shotsMutex;
  std::mutex chatMessageMutex;
  
  std::vector<std::string> chatMessages;
  Vec2ui aim{std::numeric_limits<uint32_t>::max(), std::numeric_limits<uint32_t>::max()};
  Vec2ui lastAim{std::numeric_limits<uint32_t>::max(), std::numeric_limits<uint32_t>::max()};
  std::vector<Vec2ui> shotsReceived;
  std::vector<ShotResult> shotResults;
  std::vector<Vec2ui> shotsFired;

  bool initMessageSend{false};
  std::optional<std::pair<std::string, uint32_t>> receivedPairingInfo{};
  
  void parseGameMessage(const std::string& m);
  void lostConnection();
  
  void sendGameMessage(GameMessageType mt, const std::vector<std::string>& data);
};
