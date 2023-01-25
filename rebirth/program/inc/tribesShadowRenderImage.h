#pragma once

#include "baseShadowRenderImage.h"

class SimContainer;
class InteriorShape;

#define ShadowItrFeeler 4

typedef BaseShadowRenderImage ShadowRenderImage;

class TribesShadowRenderImage : public BaseShadowRenderImage
{
	typedef BaseShadowRenderImage Parent;

	virtual void getItrShapePolys(InteriorShape* io_pContainer);

protected:
	TribesShadowRenderImage();
	void getUnknownPolys(SimContainer* io_pContainer) override;
};
