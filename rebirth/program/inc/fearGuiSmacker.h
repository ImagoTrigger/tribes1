#pragma once

#include "simGuiActiveCtrl.h"
#include "chunkedBitmap.h"

#define SMACKNEEDVOLUME 0x00040L
#define SMACKPRELOADALL 0x00200L

#define SMACKTRACK1 0x02000L
#define SMACKTRACK2 0x04000L
#define SMACKTRACK3 0x08000L
#define SMACKTRACK4 0x10000L
#define SMACKTRACK5 0x20000L
#define SMACKTRACK6 0x40000L
#define SMACKTRACK7 0x80000L
#define SMACKTRACKS (SMACKTRACK1|SMACKTRACK2|SMACKTRACK3|SMACKTRACK4|SMACKTRACK5|SMACKTRACK6|SMACKTRACK7)

#define SMACKAUTOEXTRA 0xffffffffL

namespace FearGui
{
	class SmackerCtrl : public SimGui::ActiveCtrl
	{
		typedef SimGui::ActiveCtrl Parent;

		typedef struct SmackTag {
			uint32_t Version;
			uint32_t Width;
			uint32_t Height;
			uint32_t Frames;
			uint32_t MSPerFrame;
			uint32_t SmackerType;
			uint32_t LargestInTrack[7];
			uint32_t tablesize;
			uint32_t codesize;
			uint32_t absize;
			uint32_t detailsize;
			uint32_t typesize;
			uint32_t TrackType[7];
			uint32_t extra;
			uint32_t NewPalette;
			uint8_t Palette[772];
			uint32_t PalType;
			uint32_t FrameNum;
			uint32_t FrameSize;
			uint32_t SndSize;
			int32_t LastRectx;
			int32_t LastRecty;
			int32_t LastRectw;
			int32_t LastRecth;
			uint32_t OpenFlags;
			uint32_t LeftOfs;
			uint32_t TopOfs;
			uint32_t LargestFrameSize;
			uint32_t Highest1SecRate;
			uint32_t Highest1SecFrame;
			uint32_t ReadError;
			uint32_t addr32;
		} Smack;

		typedef Smack* (*FN_SmackOpen)(const char* name, uint32_t flags, uint32_t extrabuf);
		typedef void (*FN_SmackClose)(Smack* smk);
		typedef uint32_t (*FN_SmackDoFrame)(Smack* smk);
		typedef void (*FN_SmackNextFrame)(Smack* smk);
		typedef void (*FN_SmackToBuffer)(Smack* smk, uint32_t left, uint32_t top, uint32_t Pitch, uint32_t destheight, const void* buf, uint32_t Flags);
		typedef uint32_t (*FN_SmackSoundOnOff)(Smack* smk, uint32_t on);
		typedef uint32_t (*FN_SmackWait)(Smack* smk);
		typedef uint32_t (*FN_SmackUseMMX)(uint32_t flag);
		typedef void (*FN_SmackColorTrans)(Smack* smk, const void* trans);
		typedef uint8_t (*FN_SmackSoundUseDirectSound)(void* dd);
		typedef void (*FN_SmackVolumePan)(Smack* smk, uint32_t trackflag, uint32_t volume, uint32_t pan);
		typedef void (*FN_SmackGoto)(Smack* smk, uint32_t frame);
		typedef void (*FN_SmackSimulate)(uint32_t sim);

		static HMODULE hSmacker;
		static int smackerInstanceCount;

		static FN_SmackOpen					SmackOpen;
		static FN_SmackClose				SmackClose;
		static FN_SmackDoFrame				SmackDoFrame;
		static FN_SmackNextFrame			SmackNextFrame;
		static FN_SmackToBuffer				SmackToBuffer;
		static FN_SmackSoundOnOff			SmackSoundOnOff;
		static FN_SmackWait					SmackWait;
		static FN_SmackUseMMX				SmackUseMMX;
		static FN_SmackColorTrans			SmackColorTrans;
		static FN_SmackSoundUseDirectSound	SmackSoundUseDirectSound;
		static FN_SmackVolumePan			SmackVolumePan;
		static FN_SmackGoto					SmackGoto;
		static FN_SmackSimulate				SmackSimulate;

		Smack* smk;
		GFXBitmap* bmp;

		bool loop;
		bool preload;
		bool stretch;
		int palStart;
		int palColors;
		SimTag smkTag;
		SimTag movieDoneTag;
		float volume;
		bool paused;
		bool finished;

		ChunkedBitmap cBmp;
		int remap[256];

		static int smackerCtrlVersion;

	public:
		SmackerCtrl();

		void openSmacker();
		void closeSmacker();
		void update(GFXSurface* sfc);
		void open(int tag);
		void open(const char* name);
		void close();
		void translate();
		bool onAdd();
		void onRemove();
		void onKeyDown(const SimGui::Event&);
		void onMouseDown(const SimGui::Event&);
		void onPreRender();
		void onClose();
		void onRender(GFXSurface* sfc, Point2I offset, const Box2I& updateRect);
		bool processEvent(const SimEvent* event);
		bool onSimMessageEvent(const SimMessageEvent*);
		void inspectRead(Inspect* insp);
		void inspectWrite(Inspect* insp);
		Persistent::Base::Error write(StreamIO& sio, int version, int user);
		Persistent::Base::Error read(StreamIO& sio, int version, int user);

		DECLARE_PERSISTENT(SmackerCtrl);
	};
}
