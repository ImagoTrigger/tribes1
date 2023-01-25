#pragma once
#include "projLightning.h"

class RepairEffect : public Lightning
{
	typedef Lightning Parent;
	DECLARE_PERSISTENT(RepairEffect);

public:
	struct RepairEffectData : LightningData
	{
		RepairEffectData();
	};

	struct RepairRenderImage : public LightningRenderImage
	{
		void updateSegments();
		~RepairRenderImage();
		void createSinSegments(const int in_line);
		void render(TS::RenderContext& io_rRC);

		Point3F getPoint(int j, int i, DWORD currentTime, const TMat3F& mat3F, float length)
		{
			throw std::exception("NYI");
			//const float progress = currentTime - createTime;
			//const float range = endTime - createTime;
			//float ratio = progress / range;

			//Point3F start = m_points[i];
			//Point3F end = m_points[i + 1];

			//Point3F result(
			//	(start.x * (1.0 - ratio) + end.x * ratio) * length,
			//	(start.y * (1.0 - ratio) + end.y * ratio) * length,
			//	(start.z * (1.0 - ratio) + end.z * ratio) * length);

			//m_Point3F_TMat3F_mul(&result, &mat3F, &result);
			//return result;
		}


	};

	bool m_targetEvaluated;

	RepairEffect(int in_datFileId);
	RepairEffect();
	int getDatGroup();
	void serverProcess(DWORD in_currTime);
	void determineTarget();
	void resetEndPoint();
	void shutOffProjectile();
	bool onSimRenderQueryImage(SimRenderQueryImage* query);
	bool processQuery(SimQuery* query);
};
