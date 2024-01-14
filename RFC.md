# RFC: Custom Network Packet Definitions

## 1. Introduction

R-type protocol made in cpp over udp

## 2. Packet Definitions

### 2.1 Server Packets

#### 2.1.1 `SERVER_HELLO`

   - **Packet Type:** `bool`
   - **Purpose:** Initiates the server-client handshake.

#### 2.1.2 `DEBUG_PACKET_SERVER`

   - **Packet Type:** `std::string`
   - **Purpose:** Facilitates debugging by transmitting textual information from the server to the client.

#### 2.1.3 `NOTIFY_NEW_CLIENT`

   - **Packet Type:** `int, components::Position`
   - **Purpose:** Notifies the server about a new client's presence.

#### 2.1.4 `CLIENT_BASE_INFO`

   - **Packet Type:** `int, components::Position`
   - **Purpose:** Sends basic information about a client to the server.

#### 2.1.5 `FORCE_SET_POS_VEL`

   - **Packet Type:** `int, components::Position, components::Velocity`
   - **Purpose:** Forces the specified position and velocity on the client.

#### 2.1.6 `SEND_POS_VEL`

   - **Packet Type:** `int, components::Position, components::Velocity`
   - **Purpose:** Sends the current position and velocity of a client to the server.

#### 2.1.7 `PLAYER_SHOOT_BULLET`

   - **Packet Type:** `int`
   - **Purpose:** Notifies the server when a player shoots a bullet.

#### 2.1.8 `SPAWN_ENEMY`

   - **Packet Type:** `int, components::Position`
   - **Purpose:** Informs the server to spawn an enemy at the specified position.

#### 2.1.9 `MOVE_ENEMY`

   - **Packet Type:** `int, components::Position, components::Velocity, bool`
   - **Purpose:** Instructs the server to move an enemy with specified position, velocity, and additional control information.

#### 2.1.10 `SHOOT_ENEMY`

   - **Packet Type:** `int`
   - **Purpose:** Notifies the server when an enemy shoots.

### 2.2 Client Packets

#### 2.2.1 `CLIENT_HELLO`

   - **Packet Type:** (Callback) `PacketCallbacks::helloCallback`
   - **Purpose:** Initiates the server-client handshake from the client side.

#### 2.2.2 `DEBUG_PACKET_CLIENT`

   - **Packet Type:** `std::string`
   - **Purpose:** Allows the client to send debug information to the server.

#### 2.2.3 `CLIENT_SEND_POS_VEL`

   - **Packet Type:** `components::Position, components::Velocity`
   - **Purpose:** Informs the server about the client's current position and velocity.

#### 2.2.4 `SHOOT_BULLET`

   - **Packet Type:** (Callback) `PacketCallbacks::playerShootCallback`
   - **Purpose:** Notifies the server when the client shoots a bullet.
