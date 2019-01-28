#include "Flocking.h"
#include "../../Boid.h"
#include "../../Group.h"

DynamicSteeringOutput * FlockingSteering::GetSteeringOutput() const
{
	auto seperationOutput = mSeperation.GetSteeringOutput();

	mpBoid->mpTarget = &(mpBoid->mpLeader->mKinematic);
	auto seekLeaderOutput = mSeekLeader.GetSteeringOutput();

	mpBoid->mpTarget = &(mpBoid->mpGroup->mKinematic);
	auto seekCenterOutput = mSeekCenter.GetSteeringOutput();

	mpOutput->mLinear = (mSeperationWeight * seperationOutput->mLinear + mSeekLeaderWeight * seekLeaderOutput->mLinear +
		mSeekCenterWeight * seekCenterOutput->mLinear) / (mSeperationWeight + mSeekLeaderWeight + mSeekCenterWeight);
	mpOutput->mAngular = (mSeperationWeight * seperationOutput->mAngular + mSeekLeaderWeight * seekLeaderOutput->mAngular +
		mSeekCenterWeight * seekCenterOutput->mAngular) / (mSeperationWeight + mSeekLeaderWeight + mSeekCenterWeight);

	return mpOutput;
}
