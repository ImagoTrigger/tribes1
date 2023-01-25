#pragma once

#include "tVector.h"
#include "PlayerManager.h"
#include "SimMovement.h"

#include "Player.h"
#include "FearPlayerPSC.h"
#include "Projectile.h"
#include "tMHashMap.h"

class AIObj : public SimMovement
{
	// TODO: SimMovement Guess... GameBase? Player?
	typedef SimMovement Parent;

	// Directive Callback, not to be confused with WinBase.h DCB.
	typedef StringTableEntry DCB;

	// TODO: Make sure is right
	static const int TicksPerSecond = 24;

	static const size_t VarNameBufSize = 256; // TODO: Figure out size
	static const int MaximumDirectives = 32; // TODO: Figure out real constant value.
	//static const int NumCallbacks = 32; // TODO: Figure out real constant value.

public:

	static const size_t MaxNameLen = 32; // TODO: Figure out size

	enum DirectiveType
	{
		// TODO enum order.
		WaypointDirective,
		FollowDirective,
		TargetDirective,
		GuardDirective
	};
public:
	enum
	{
		// AI CBs

		// TODO: enum order
		AiDied,
		AiBored,
		AiPeriodic,

		// Directive CBs TODO: Separate enum?

		// TODO: enum order
		WaypointReached,
		WaypointIntermittent,
		WaypointQueryFace,
		TargetAcquired,
		TargetKilled,
		TargetLOSLost,
		TargetLOSRegained,
		FollowDestReached,
		FollowOffsetReached,
		GuardBored,
		NumCallbacks
	};	
public: //private:



	
public:

	struct Waypoint;
	struct Target;
	
	struct Directive //: public Target, public Follow, public Waypoint
	{
		DirectiveType type;
		int subType;
		DCB CBs[NumCallbacks];
		int playerId;
		int order;

		Point3F pos;
		BitSet32 flags;
		int pri;

		float radius;

		Directive();
		virtual int operator<(const Directive& dir) const;
		virtual void getPointAndRadius(const char* in_PointAndRadius);

		virtual void printf();
		virtual void setDefaultCallbacks();

		operator Waypoint*() const { throw std::exception("NYI"); }
		operator Target*() const { throw std::exception("NYI"); }
	};

	struct Waypoint : public Directive
	{
	};

	struct Follow : public Directive
	{
	};


	struct Target : public Directive
	{
	public:
		// TODO: player,laser,point values.
		static const int player = 1;
		static const int laser = 2;
		static const int point = 3;

		virtual bool isPlayer() const
		{
			return this->subType == player;
		}

		Player* findPlayerObj();

		explicit Target(const int st = 0)
		{
			this->subType = st;
		}

		bool canGetLosTo(AIObj* fromAi);

		//Target()
		//{
		//	
		//}
	};

	typedef SortableVector<Directive> DirectiveList;

public: //private:

	static float getPercentBetween(const float, const float, const float)
	{
		throw std::exception("NYI");
	}

	// Guess as to what losCheck and periodicCbWait are.
	//struct Waiter
	//{

	//	bool timeToThink();
	//};

	struct Skill
	{
		virtual bool doIt(AIObj * ai, PlayerMove & pm);
	};

	struct JetSkill : public Skill
	{
		enum Stage
		{
			Jump,
			Jumped,
			StartFlight
		} stage;

		int jumpCount;
		int jumpWait;
		Point3F saveLinearVel;

		int pathLength;
		Point3F points[3];
		float vels[3];

		void incStage()
		{
			stage = static_cast<Stage>(stage + 1);
		}
		
		bool stageWas(const decltype(stage) s) const
		{
			return (this->stage - 1) == s;
		}

		void setStage(const decltype(stage) s)
		{
			this->stage = s;
		}

		JetSkill(const Point3F& startpoint, const Point3F& endpoint);

		JetSkill() : JetSkill(Point3F(), Point3F())
		{
		}
	} m_jetSkill;

	struct Trigger
	{
		int wasPressed;
		int counter;
		int windup;
		float percent;

		bool press();
		void preLoop();
	};

	class Incrementor
	{
		float increment;
		float reduce;
		float min_inc;

	public:
		float getInc(float absDiff);
		void init(float inc);
	};

	struct IQVariables
	{
		SimTime bestThinkWait = 0;
		SimTime worstThinkWait = 1;

		float spotDistOverride;
		SimTime thinkWait;

		float spotDist;
		float maxSpeed;

		Incrementor pitchInc;
		Incrementor turnInc;

		float vertDope[2];

		float smartGuyWeaponRange;
		float dumbGuyWeaponRange;
		float smartGuyMinAccuracy;

		float curWeaponRange;
		float curWeaponMinPct;
		float curWeaponMaxPct;

		IQVariables(bool isBest);
		void scale(float unitScale);
		float getWeaponAccuracy(float range);
		float spotDistance();

		IQVariables() : IQVariables(true)
		{			
		}

	} iq;

public:
	struct FrameVariables
	{
		Point3F seekLoc;
		bool haveDest;
		Point3F ourCenter;

		FrameVariables();
	};
public: //private:
	struct AngleSeek
	{
		float current;
		float desired;
		float diff;
		float absDiff;

		explicit AngleSeek(const float des) :
			current(0),
			desired(des),
			diff(0),
			absDiff(0)
		{
			// TODO: Guessed default parameters
		}

		bool operator <(const float rhs) const
		{
			// TODO: Guess
			return this->current < rhs;
		}
	};

	enum
	{
		// TODO: get real values.
		AutomaticTargeting,
		ScriptedTargeting
	} targetingMode;

	enum
	{
		// TODO: Get real values.

		HaveColorName = BIT(27),
		ConsoleVarsInstalled = BIT(28),

		// These belong here?
		AiWasDead = BIT(29) ,
		TargetWasDead = BIT(30),
		HaveTargetLOS = BIT(31),
		HadTargetLOS = BIT(26),
		ValidLOSCandidate = BIT(25)
	};

	enum
	{
		// TODO: Get real value.
		Circular,
		TwoWay
	} pathType;

	enum
	{
		// TODO: get right indices
		DoNothing,		
		NeedToThink,
		FollowingPath,
		AttackTarget,
		AttackStill
	} state;
	
	enum
	{
		// TODO: get right indices
		WhileFollowingTarget,
		WhileFollowingPath
	} attackMode;

	Target* currentTarget;
	int currentTargetId;
	int lastLosCheckId;

	float projectileSpeed;
	float iqPercent;
	float wrappedFireAngle;
	float jetNavigation;

	
	StringTableEntry skin;

	struct
	{
		int operator[](int)
		{
			throw std::exception("NYI");
		}
		
		void set(int,int)
		{
			throw std::exception("NYI");
		}
		
		void clear()
		{
			throw std::exception("NYI");
		}
	} targetIdTracker;

	struct PCB
	{
		PCB()
		{
			throw std::exception("NYI");
		}

		PCB(int)
		{
			throw std::exception("NYI");
		}

		void init(int)
		{
			throw std::exception("NYI");
		}

		bool timeToThink()
		{
			throw std::exception("NYI");
		}

		bool operator >=(int rhs)
		{
			throw std::exception("NYI");
		}
	} losCheck, periodicCbWait;

	//Waiter losCheck;
	//SimTime periodicCbWait;
	//BitVector targetIdTracker;
	//SimIdDictionary targetIdTracker;

	int jetStage;
	Point3F jetSaveLinearVel;

	// TODO: type
	JetSkill* m_jsPtr;

	DCB CBs[NumCallbacks];

	static Random rand;
	static const Int32 collisionMask;

	// TODO: Default false?
	virtual float dist2d(const Point2F& loc1, const Point2F& loc2, bool forceAccurate = false);

	// TODO: Default false?
	virtual float dist3d(const Point3F& loc1, const Point3F& loc2, bool forceAccurate = false);
	float jetBetween(const Point3F& A, const Point3F& B, float startVelPct, float endVelPct, PlayerMove& pm, JetSkill& js);
	bool updateJetNavigation(JetSkill& js, PlayerMove& pm);
	Trigger trigger;
	Point3F seekLoc;
	Point3F lastWaypointLoc;
	Point3F seekOff;
	
	bool didFirstTimeSetup;
	int timeHere;
	int pathIndex;
	int pathDirection;
	
	int counter;
	
	bool doneWithPath;
	float iqScale;

	int ourTeam;
	DirectiveList directives;

	virtual char * makeVarName(char buf[VarNameBufSize], const char * vName);
	
	virtual bool removeVariables(CMDConsole*);
	
	virtual Waypoint* getWaypoint(int order);
	virtual Waypoint* setNextWaypoint(int previousPathIndex);
	virtual SphereF getFollowDestination(Waypoint* w);
	virtual bool timeToThink(bool force);
	virtual void scanTargetList();
	// TODO: default false?
	virtual Player* scanForOldTargets(bool force = false); 
	virtual void followPath();
	virtual void attackStill();
	virtual void attackTarget();
	virtual void rethinkState(bool force);
	virtual bool withinRange(const Point3F& destination);
	 
	virtual Point3F dopeOffset(Player* p, const Point3F* loc = nullptr);
	virtual float getDesiredRot(const Point3F& dest, const Point3F& source);
	// TODO: Guess default false
	virtual float getDesiredPitch(const Point3F& dest, const Point3F& source, bool fastMath = false);
	virtual void setMovementAction(PlayerMove& pm, const AngleSeek& heading, float speed);
	virtual float wrapRotation(float r, float rangeMin = 0);
	virtual bool setProjectileSpeed();
	virtual Point3F leadPosition(Point3F pos, Point3F vel);
	 
	virtual AngleSeek getAngleSeekZ(const Point3F & seekLoc);
	 
	virtual AngleSeek pitchAtTarget(const Point3F & seekLoc, PlayerMove & pm);
	virtual void fireAtPlayerTarget(PlayerMove& pm, Player* p);
	virtual void fireAtLaserTarget(PlayerMove& pm, Target* t);
	virtual void fireAtPointTarget(PlayerMove& pm, Target* t);
	virtual float getSpeed(float dist);
	virtual float moveTowardLoc(const SphereF& seekLoc, PlayerMove& pm);
	 
	virtual AngleSeek turnToLoc(const Point3F & seekLoc, PlayerMove & pm);
	virtual float seekLocation(const SphereF& sphere, PlayerMove& pm);
	virtual void onDeleteNotify(SimObject* object);
	virtual bool onAdd();
	virtual void onRemove();
	PlayerMove move;

	
	
	// TODO: is typeFilter INT_MAX default?
	virtual int findDirective(int order, int typeFilter = INT_MAX, bool getBeyond = false);
	virtual PlayerManager::ClientRep* getBaseRepPtr(int id);
	virtual void eraseDirectives(Vector<int>& eraseList);
	

	virtual void addDirective(Directive& newDirective, bool suppressSorting);
	virtual int getDirectiveList(int indices[MaximumDirectives], int ofTheGivenTypes);
	
	
	virtual int countDirectives(int ofTheGivenTypes);
	
	virtual void setDefaultCallbacks();
	virtual bool checkCallback(UInt16 whichCallback, Directive* dir = nullptr);
	virtual bool haveLOS(Player* from, Player* to);
	static bool randPct(float percent);

	virtual bool isEnemy(PlayerManager::BaseRep* br);

	static float scaleBetween(const float x, const float y, const float s)
	{
		return x * (1.0f - s) + y * s; 
	}

	bool frameAccurate;
	virtual bool isFrameAccurate() const
	{
		return this->frameAccurate;
	}

	virtual void setFrameAccurate()
	{
		this->frameAccurate = true;
	}

	virtual void clrFrameAccurate()
	{
		this->frameAccurate = false;
	}

	virtual bool circularPath() const
	{
		return this->pathType == Circular;
	}

public:
	static Player* findPlayerObject(int id, const char * name = NULL);

	AIObj();
	virtual ~AIObj();

	virtual const char* installDCB(int dcb, const char* func, const char* ordExpr, int dirMask);
	virtual void installCB(UInt16 whichCallback, const char* func);

	int seekFlag;
	char name[MaxNameLen];
	int repId;
	StringTableEntry voice;

	virtual bool nameMatches(const char* expr) const;
	virtual const char* getVar(CMDConsole* console, const char* var);
	virtual void setVar(CMDConsole* console, const char* var, const char* value);
	virtual void setAutomaticTargets();
	virtual void setScriptedTargets();
	virtual int listDirectives(int typeFilter = INT_MAX); // TODO: is default INT_MAX?
	virtual void doRecomputations();
	virtual void doSetupComputations();
	virtual void doPostLoopComputations();
	virtual void doPreLoopComputations();
	virtual bool onServerProc();
	virtual void timeSlicedOps();
	virtual void removeThis();

	virtual void addWaypoint(const Waypoint&)
	{
		throw std::exception("NYI");
	}
	virtual void addFollow(const Follow&)
	{
		throw std::exception("NYI");
	}
	virtual void addTarget(const Target&)
	{
		throw std::exception("NYI");
	}

	int curTargetId() const
	{
		return this->currentTargetId;
	}
	virtual bool removeDirectives(const char* ordExpr);
	FrameVariables* currently;
	Player* player;
	bool active;

	virtual Point3F ourCenter() const
	{
		return this->currently->ourCenter;
	}

	virtual float spottingDistance() const
	{
		throw std::exception("NYI");
	}

	virtual void setPeriodicDelay(const SimTime value)
	{
		throw std::exception("NYI");
		//this->periodicCbWait = value;
	}

	virtual void addVariables(CMDConsole*);
};

class AIManager : public SimContainer, public Vector<AIObj*> // TODO Vector? VectorPtr? Sortable?
{
	// TODO: Guess SimContainer
	typedef SimContainer Parent;

	friend class AIPlugin;

	typedef Vector<AIObj*> AIList;

	static AIManager* it;
	static bool recomputePulse;
	
	AIList list;
	int cyclingVar;

	AIManager();

public:
	virtual ~AIManager();
	static const char* doRecomputation(CMDConsole*, int, int, const char**);
	bool onAdd() override;
	void onDeleteNotify(SimObject* object) override;
	void doServerProcesses(DWORD);
};
