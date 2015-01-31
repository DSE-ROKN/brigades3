#ifndef BRIGADES_AISENSOR_HPP
#define BRIGADES_AISENSOR_HPP

#include <vector>

#include <common/Vector3.h>
#include <common/Clock.h>

#include "worldmap.hpp"
#include "soldierphysics.hpp"
#include "soldiers.hpp"

class SoldierKnowledge {
	public:
		SoldierKnowledge(unsigned int id, const Common::Vector3& knownpos, bool currentlyseen, float currtime);
		float timeSinceEntry(float currtime) const { return currtime - mEntryTime; }
		bool isCurrentlySeen() const { return mCurrentlySeen; }
		float entryTime() const { return mEntryTime; }
		const Common::Vector3& getPosition() const { return mLastKnownPosition; }
		unsigned int getID() const { return mID; }

	private:
		Common::Vector3 mLastKnownPosition;
		bool mCurrentlySeen;
		unsigned int mID;
		float mEntryTime;
};

class AISensor {
	public:
		AISensor();
		AISensor(const WorldMap* wmap, const Soldiers* soldiers, unsigned int id);
		void update(float dt);
		std::vector<SoldierKnowledge> getCurrentlySeenEnemies() const;
		std::vector<SoldierKnowledge> getEnemyEntries() const;
		bool LOSNotBlocked(unsigned int id) const;

	private:
		bool canSeeEnemy(unsigned int id);

		const WorldMap* mMap;
		const Soldiers* mSoldiers;
		const SoldierPhysics* mPhys;
		std::map<unsigned int, SoldierKnowledge> mSensedSoldiers;
		unsigned int mID;
		Common::SteadyTimer mTimer = Common::SteadyTimer(0.2f);
		float mCurrTime = 0.0f;
};

#endif

