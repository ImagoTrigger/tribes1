#pragma once

#include "NetCSDelegate.h"

class PlayerManager;

namespace SimGui
{
	class JoinGameDelegate;
}

class FearCSDelegate : public Net::CSDelegate
{
	typedef CSDelegate Parent;

	friend class SimGui::JoinGameDelegate;

	DECLARE_PERSISTENT(FearCSDelegate);	

	// TODO: Value
	static const BYTE GameSpyPing = 0x00;
	static const BYTE GameSpyQuery1 = 0x62;

	// TODO: Value
	static const BYTE GameSpyPingResponse = 0x00;
	// TODO: Value
	static const BYTE GameSpyQuery1Response = 0x00;

public:		
	struct Info sealed
	{
		char buf[256];
	};

	struct ServerInfo sealed
	{
		char game[32];
		char name[64];
		char version[32];
		char missionName[32];
		char modName[32];
		char hostInfo[256];
		char missionType[32];
		int numPlayers;
		int maxPlayers;
		int pingTime;
		char transportAddress[31];
		bool correctVersion;

		bool dedicated;
		bool password;
		int scoreLimit;
		int timeLimit;
		bool status;
		bool favorite;
		bool neverPing;
		bool hasBuddy;

		int cpuSpeed;

		WORD key;

		Vector<Info> mInfoList;

		char teamScoreHeading[256];
		char clientScoreHeading[256];
	};

public: //private:

	UInt16 mPacketVersion;
	DNet::VC* vcConnection;
	PlayerManager* playerManager;

	Vector<ServerInfo> mServerList;

	virtual void cancelDuringConnection();

	virtual void removeServer(const char* address);
	virtual bool isNeverPing(const char * address);
	virtual void setNeverPing(const char* address);

	DNet::Error send(const char* addrString, char* data, int datalen)
	{
		return Session::send(addrString, (BYTE*)data, datalen);
	}

protected:
	void onGameInfoPacket(const char* transportAddress, BYTE* data, int datalen) override;
	bool processArguments(int argc, const char** argv) override;
	bool simConnect(const char* transportAddress) override;
	void onConnectionRequested(DNet::VC* vc, BYTE* data, int datalen) override;
	void addStreamClients(Net::PacketStream* ps) override;
	bool playDemo(const char* fileName) override;
	void onConnectionAccepted(DNet::VC* vc, BYTE* data, int datalen) override;
	bool onAdd() override;
	void onGhostAlwaysDone(Net::PacketStream* pstream) override;
	void onConnectionError(Net::PacketStream* pstream, const char* string) override;
	void simDisconnect() override;
	void onConnectionRejected(DNet::VC* vc, BYTE* data, int datalen) override;
	void onConnectionDropped(DNet::VC* vc, BYTE* data, int datalen, bool timeout) override;
	void kick(int playerId, const char* reason) override;
	void getPingInfo(PingInfo& pingInfo) override;
	int getGameInfo(GameInfo& gameInfo, int maxDataSize, int) override;
	void gotGameInfo(const GameInfo& gameInfo) override;
	void gotMasterServer(const char* address, const char* name, const char* motd, bool firstPacket) override;
	void gotPingInfo(const PingInfo& pingInfo) override;
	void serverPingTimeout(const char* address) override;

public:
	virtual ~FearCSDelegate();

	virtual void rebuildServerList();
};
