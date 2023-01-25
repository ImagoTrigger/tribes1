#pragma once

#include "Projectile.h"

class Lightning : public Projectile
{
	typedef Projectile Parent;

	DECLARE_PERSISTENT(Lightning);

public:
	struct LightningData : ProjectileData
	{
	private:
		typedef ProjectileData Parent;

	public:
		float boltLength;
		float coneAngle;
		float damagePerSec;
		float energyDrainPerSec;
		int segmentDivisions;
		float skipPercent;
		float displaceBias;
		float beamWidth;
		const char* pBitmapName;
		unsigned int numSegments;
		DWORD updateTime;

		LightningData();
		void pack(BitStream* bs);
		void unpack(BitStream* bs);
		float getTerminalVelocity() const;
	} *m_pLightningData;

	bool m_waitingForShutoff;
	ShapeBase* m_pCurrentTarget;

	struct LightningRenderImage : public SimRenderImage
	{
		Lightning* pLightning;
		Point3F m_endPoint;
		Point3F m_startPoint;
		bool m_attached;
		TMat3F m_baseTransform;

		struct Line
		{
			DWORD endTime;
			Point3F* m_points;
			Point3F* m_pointsAnim;
			DWORD createTime;
			bool createPhase;

			Line():
				endTime(0),
				m_points(nullptr),
				m_pointsAnim(nullptr),
				createTime(0),
				createPhase(false)
			{				
			}

			Point3F getPoint(int i, DWORD currentTime, const TMat3F& mat3F, float length)
			{
				const float progress = currentTime - createTime;
				const float range = endTime - createTime;
				float ratio = progress / range;

				Point3F start = m_points[i];
				Point3F end = m_points[i + 1];

				Point3F result(
					(start.x * (1.0 - ratio) + end.x * ratio) * length,
					(start.y * (1.0 - ratio) + end.y * ratio) * length,
					(start.z * (1.0 - ratio) + end.z * ratio) * length);

				m_Point3F_TMat3F_mul(&result, &mat3F, &result);
				return result;
			}
		} m_lines[8];


		void render(TS::RenderContext& io_rRC);
		void updateSegments();
		void createSegments(const int in_line);
		void subdivideLine(Point3F* in_pPoints, const int in_left, const int in_right);
		void clearPoints();
		virtual ~LightningRenderImage();

		virtual bool isCreated() const
		{
			// TODO: implement not important, just used for debugging / assertions
			return true;
		}
	} *m_pLightningImage;

	Point3F m_currentTargetPosition;
	DWORD m_lastTarget;
	DWORD m_ghostTimer;
	Resource<GFXBitmap> m_resBitmap;
	DWORD m_endInterpTime;
	int m_startInterpTime;
	Point3F m_targetOffsetPosition;
	Point3F m_prevOffsetPosition;

	enum
	{
		TargetMask = LastMaskBit,
		LastMaskBit = LastMaskBit << 1
	};

	static const DWORD csm_targetUpdateFreq;

	Lightning(const Int32 in_datFile);
	Lightning();
	virtual ~Lightning();
	bool isSustained() const;
	void shutOffProjectile();
	void determineTarget();
	void updateImageTransform(const TMat3F& in_rTrans);
	void loadResources(const bool in_isGhost);
	bool initResources(GameBase::GameBaseData* io_pDat);
	void initProjectile(const TMat3F& in_rTrans, const Point3F&, const SimObjectId in_shooterId);
	bool processQuery(SimQuery* query);
	bool onAdd();
	virtual bool isAttached()
	{
		return this->m_pCurrentTarget != nullptr;
	}
	void writeInitialPacket(Net::GhostManager* gm, BitStream* pStream);
	void readInitialPacket(Net::GhostManager* gm, BitStream* pStream);
	DWORD packUpdate(Net::GhostManager* gm, DWORD mask, BitStream* stream);
	void unpackUpdate(Net::GhostManager* gm, BitStream* stream);
	void clientProcess(DWORD);
	void serverProcess(DWORD in_currTime);
	void buildContainerBox(const TMat3F&, Box3F* out_pBox);
	Point3F getCurrentTargetPosition();
	bool onSimRenderQueryImage(SimRenderQueryImage* query);
	bool onSimLightQuery(SimLightQuery* query);
	int getDatGroup();
	void readExplosion(BitStream*);
	void writeExplosion(BitStream*);
	int getVictimGhostId(Net::GhostManager* gm);
	ShapeBase* getShooter();
	ShapeBase* getChargeTarget();
	bool canRender();
	void onDeleteNotify(SimObject* io_pDelete);
	void resetEndPoint();
};
