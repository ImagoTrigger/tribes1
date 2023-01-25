#pragma once

#include "PERSIST.H"
#include "SimPersistTags.h"
#include "esfObjectTypes.h"
#include "esfEvDcl.h"

#include "m_random.h"

extern Random random;

#define PlayerManagerId SimRangeNum(FearIdRange, 1)
#define SnowfallId SimRangeNum(FearIdRange, 2)
#define PlayerPSCId SimRangeNum(FearIdRange, 3)
#define MissionCenterPosId SimRangeNum(FearIdRange, 4)
#define MoveableSetId SimRangeNum(FearIdRange, 6)
// Somewhat guess
#define PlayerSetId SimRangeNum(FearIdRange, 7)
#define SensorManagerId SimRangeNum(FearIdRange, 8)
#define DataBlockManagerId SimRangeNum(FearIdRange, 9)
// Somewhat guess
#define SensorVisibleSetId SimRangeNum(FearIdRange, 11)
#define DecalManagerId SimRangeNum(FearIdRange, 12)
#define TargetableSetId SimRangeNum(FearIdRange, 13)
#define AIManagerId SimRangeNum(FearIdRange, 14)
#define ObserverSetId SimRangeNum(FearIdRange, 15)
#define SmokeManagerId SimRangeNum(FearIdRange, 16)
#define TribesSkyId SimRangeNum(FearIdRange, 17)


// TODO: Ensure this is correct
//#define MarkerObjectType SimMarkerObjectType
// TODO: Ensure this is correct
//#define TriggerObjectType SimTriggerObjectType

// These seem to follow a (256 << x) pattern. TODO: Find out why
#define ItemObjectType (256 << 13)
#define MoveableObjectType (256 << 14)
#define StaticObjectType (256 << 15)
#define MineObjectType (256 << 18)
//	TODO: This is a guess
#define MarkerObjectType (256 << 19)
//	TODO: This is a also a guess
#define TriggerObjectType (256 << 20)
#define VehicleObjectType (256 << 21)
// TODO: This is a guess.
#define CorpseObjectType (256 << 22)

#ifndef DEFAULT_FAR_PLANE
#define DEFAULT_FAR_PLANE 100000.0f
#endif

#ifndef DEFAULT_NEAR_PLANE
#define DEFAULT_NEAR_PLANE 1.0f
#endif

enum FearTypes
{
	TypeAnimData = NumCoreTypes,
	TypeItemBlock,
	TypeItemImageBlock,
	TypeProjectileBlock,
	TypeSequenceSound,
	TypeSoundFlags,
	TypeNormalVector,
	TypeSoundProfileBlock,
	TypeSoundBlock,
	TypeExplosionBlock,
	TypeDebrisBlock,
	TypeStaticDamage,
	TypeDamageSkinBlock,
	TypeLightAnimParam,
	TypeGrenadeDist
};

enum
{
	ImpactDamageType = -1,
	LandingDamageType = 0,
	BulletDamageType = 1,
	EnergyDamageType = 2,
	PlasmaDamageType = 3,
	ExplosionDamageType = 4,
	ShrapnelDamageType = 5,
	LaserDamageType = 6,
	MortarDamageType = 7,
	BlasterDamageType = 8,
	ElectricityDamageType = 9,
	CrushDamageType = 10,
	DebrisDamageType = 11,
	MissileDamageType = 12,
	MineDamageType = 13
};

// TODO: Figure these out...

#define CommonPersTagsRangeEnd       (SimPersTagsRangeEnd + 127)

#define FearPersTagsRange          (CommonPersTagsRangeEnd + 1)

// These guesses are based off esfDcl:

#define MarkerPersTag		SimRangeNum(FearPersTagsRange, 1)
#define DropPointPersTag	SimRangeNum(FearPersTagsRange, 2)
#define SoundSourcePersTag	SimRangeNum(FearPersTagsRange, 3)
#define TriggerPersTag		SimRangeNum(FearPersTagsRange, 4)
#define MagnetPersTag		SimRangeNum(FearPersTagsRange, 5)
#define VolumetricPersTag	SimRangeNum(FearPersTagsRange, 6)

// These guesses are completely random:

//#define CarPersTag SimRangeNum(FearPersTagsRange, 11)
//#define TankPersTag SimRangeNum(FearPersTagsRange, 17)

#define ExplosionPersTag SimRangeNum(FearPersTagsRange, 12)
#define DebrisPersTag SimRangeNum(FearPersTagsRange, 13)
#define DebrisCloudPersTag SimRangeNum(FearPersTagsRange, 14)

#define FearTurretPersTag 514
#define InteriorShapePersTag 522
#define SnowfallPersTag 534
#define PlayerPersTag 536
#define MinePersTag 542

#define FearMoveablePersTag 544
#define StaticShapePersTag 545
#define VehiclePersTag 546
#define FlierPersTag 547

#define SensorPersTag 553
#define ItemPersTag	554

#define PlanetPersTag 559
#define SkyPersTag 560
#define ObserverCamPersTag 561
#define StarFieldPersTag 562

#define BulletPersTag 600
#define GrenadePersTag 601
#define RocketDumbPersTag 602
#define LaserProjectilePersTag 603
#define TargetLaserPersTag 604
#define SeekingMissilePersTag 605
#define LightningPersTag 606
#define RepairEffectPersTag 607

#define FearPersTagsRangeEnd          (CommonPersTagsRangeEnd + 127)

#define FearMissionTeams "Teams"
#define NamedDropPoints "DropPoints"

// TODO: Figure out real values.
//#define SoundEventType SimRangeNum(FearTypeRange, 1)
//#define TargetNameEventType SimRangeNum(FearTypeRange, 2)
#define MoveableBaseObjectType SimRangeNum(FearTypeRange, 3)
#define AIObjectType SimRangeNum(FearTypeRange, 4)

//#define PingPLEventType SimRangeNum(FearTypeRange, 5)
//#define VoiceEventType SimRangeNum(FearTypeRange, 6)
//#define PlayerTeamChangeEventType SimRangeNum(FearTypeRange, 7)
//#define TeamObjectiveEventType SimRangeNum(FearTypeRange, 8)
//#define PlayerSkinEventType SimRangeNum(FearTypeRange, 9)
//#define PlayerCommandEventType SimRangeNum(FearTypeRange, 10)
//#define PlayerSelectCmdrEventType SimRangeNum(FearTypeRange, 11)
//#define PlayerSayEventType SimRangeNum(FearTypeRange, 12)
//#define DeltaScoreEventType SimRangeNum(FearTypeRange, 13)
//#define TeamAddEventType SimRangeNum(FearTypeRange, 14)
//#define PlayerAddEventType SimRangeNum(FearTypeRange, 15)
//#define PlayerRemoveEventType SimRangeNum(FearTypeRange, 16)
//#define MissionResetEventType SimRangeNum(FearTypeRange, 17)
//#define LocSoundEventType SimRangeNum(FearTypeRange, 18)
//#define DataBlockEventType SimRangeNum(FearTypeRange, 19)
#define DropPointQueryType SimRangeNum(FearTypeRange, 20)

// TODO: Real value
#define TribesJetForce (SimMovementAppForce << 1)
#define TribesRocketForce (SimMovementAppForce << 2)

// SimEvent Type ID
enum EventId
{
	//SimTimeEventType = 1024,
	//SimMessageEventType,
	//SimLoseFocusEventType,
	//SimGainFocusEventType,
	//SimGroupObjectIdEventType,
	//SimObjectTransformEventType,
	//SimFrameEndNotifyEventType,
	//SimGhostUpdateEventType,
	//SimConsoleEventType,
	//SimPingEventType,
	//SimTimerEventType,
	//SimActionEventType,
	//SimCollisionEventType,
	//SimCollisionWakeupEventType,
	//SimTerrainApplyEventType,
	//SimSoundFXEventType,
	//SimPreferenceEventType,
	//SimGuiMessageEventType,
	//SimGuiEventType,
	//SimCameraNetEventType,
	//SimCameraMountEventType,
	//SimCameraUnmountEventType,
	//SimInputEventType,
	//SimInputActivateEventType,
	//Sim3DMouseEventType,
	//SimEditEventType,
	//SimDebrisEventType,
	//SimITRTimerEventType,
	//SimDynamicLightUpdateEventType,
	//SimDynamicLightDecRefCntEventType,
	//SimIgnorableEventType,
	//SimMovementCollisionEventType,
	//SimTriggerEventType,
	//RemoteCreateEventType,
	//SimPolledUpdateEventType,
	//SimSoundSequenceEventType,
	//NetGhostAlwaysDoneEventType,
	//SimPathEventType,
	//SimCameraRemountEventType,
	//SimMCINotifyEventType,
	//SimMIXNotifyEventType,
	//SimRegisterTextureEventType,


	// TODO: Figure out real values. If a value has an assignment it has been figured out.


	//MoveableBaseObjectType,
	//AIObjectType,


	TeamObjectiveEventType = 1151, //  Needs testing.

	PlayerCommandEventType = 40000, //  Needs testing.
	PlayerSelectCmdrEventType = 50000, //  Needs testing.




	PlayerAddEventType = 1099, //  Confirmed correct.
	PlayerRemoveEventType = 1100, //  Confirmed correct.
	DeltaScoreEventType = 1101, //  Confirmed correct.
	TeamAddEventType = 1103, //  Confirmed correct.


	PlayerTeamChangeEventType = 1106, //  Confirmed correct.
	PlayerSayEventType = 1107, //  Confirmed correct.

	DataBlockEventType = 1112, //  Confirmed correct.
	MissionResetEventType = 1113, //  Needs testing.
	LocSoundEventType = 1116, //  Confirmed correct.

	TargetNameEventType = 1117,


	VoiceEventType = 1119, //  Needs testing.
	SoundEventType = 1120,  // Confirmed correct.
	PingPLEventType = 1121, //  Confirmed correct.
	PlayerSkinEventType = 1122, //  Needs testing.
};

//enum Ids
//{
//	//SimIdRange = 1,
//	//SimTypeRange = 1 << SIM_ID_BLOCK_SHIFT,
//
//	//AppIdRange = 512,
//	//EsIdRange = AppIdRange + 100,
//	//FearIdRange = EsIdRange + 100,
//
//	//SimActionHandlerId = SimIdRange + 0,
//	//SimResourceObjectId = SimIdRange + 1,
//	//SimCanvasSetId = SimIdRange + 2,
//	//SimRouterSetId = SimIdRange + 3,
//	//SimLookupSetId = SimIdRange + 4,
//	//SimFrameEndNotifySetId = SimIdRange + 5,
//	//SimRootContainerId = SimIdRange + 6,
//	//SimTerrainId = SimIdRange + 7,
//	//SimCameraSetId = SimIdRange + 8,
//	//SimConsoleId = SimIdRange + 9,
//	//SimPingObjectId = SimIdRange + 10,
//	//SimTimerSetId = SimIdRange + 11,
//	//SimRenderSetId = SimIdRange + 12,
//	//SimLightSetId = SimIdRange + 13,
//	//SimPersistManSetId = SimIdRange + 14,
//	//SimCollisionManagerId = SimIdRange + 15,
//	//LSStampSetId = SimIdRange + 16,
//	//SimDefaultRouterId = SimIdRange + 17,
//	//SimToolSetId = SimIdRange + 18,
//	//SimTedSetId = SimIdRange + 19,
//	//SimSoundFXObjectId = SimIdRange + 20,
//	//SimPreferenceSetId = SimIdRange + 21,
//	//SimCameraMountSetId = SimIdRange + 22,
//	//SimInputManagerId = SimIdRange + 23,
//	//SimInputConsumerSetId = SimIdRange + 24,
//	//SimDefaultTagDictionaryId = SimIdRange + 25,
//	//SimEditSetId = SimIdRange + 26,
//	//SimMissionGroupId = SimIdRange + 27,
//	//SimDefaultDebrisTableId = SimIdRange + 28,
//	//SimDefaultExplosionTableId = SimIdRange + 29,
//	//SimMissionEditorId = SimIdRange + 30,
//	//SimTEDId = SimIdRange + 31,
//	//SimITRTimerSetId = SimIdRange + 32,
//	//SimGhostAlwaysSetId = SimIdRange + 33,
//	//SimCSDelegateId = SimIdRange + 34,
//	//GhostManagerSetId = SimIdRange + 35,
//	//GhostManagerId = SimIdRange + 36,
//	//PacketStreamSetId = SimIdRange + 37,
//	//SimSoundSequenceObjectId = SimIdRange + 38,
//	//SimCleanupSetId = SimIdRange + 39,
//	//SimDefaultFireTableId = SimIdRange + 40,
//	//SimPathManagerId = SimIdRange + 41,
//	//SimConsoleSchedulerId = SimIdRange + 42,
//	//NamedGuiSetId = SimIdRange + 43,
//	//TaggedGuiSetId = SimIdRange + 44,
//	//IRCClientObjectId = SimIdRange + 45,
//	//SimRedbookSetId = SimIdRange + 46,
//	//SimPreLoadManagerId = SimIdRange + 47,
//
//	//ServerManagerId = 2048,
//
//	//PlayerManagerId = FearIdRange + 1,
//	//SnowfallId = FearIdRange + 2,
//	//PlayerPSCId = FearIdRange + 3,
//	//MissionCenterPosId = FearIdRange + 4,
//	//MoveableSetId = FearIdRange + 6,
//	//PlayerSetId = FearIdRange + 7,
//	//SensorManagerId = FearIdRange + 8,
//	//DataBlockManagerId = FearIdRange + 9,
//	//SensorVisibleSetId = FearIdRange + 11,
//	//DecalManagerId = FearIdRange + 12,
//	//TargetableSetId = FearIdRange + 13,
//	//AIManagerId = FearIdRange + 14,
//	//ObserverSetId = FearIdRange + 15,
//	//SmokeManagerId = FearIdRange + 16,
//	//TribesSkyId = FearIdRange + 17
//};
