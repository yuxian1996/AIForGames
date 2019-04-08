#include "BTNode.h"
#include "BTTick.h"
#include "Blackboard.h"

void BTNode::Enter(BTTick inTick)
{
	OnEnter(inTick); 
	inTick.SetEnterNode(this);
}

void BTNode::Open(BTTick inTick)
{
	OnOpen(inTick); 
	inTick.OpenNode(this);
	// Todo: set blackboard
	inTick.GetBlackboard()->Set("isOpen", true, ID);
}

BT_State BTNode::Execute(BTTick inTick)
{
	BT_State state = OnExecute(inTick); 
	inTick.SetExecuteNode(this);
	return state;
}

void BTNode::Close(BTTick inTick)
{
	OnClose(inTick);
	inTick.CloseNode(this);
	inTick.GetBlackboard()->Set("isOpen", false, ID);
}

void BTNode::Exit(BTTick inTick)
{
	OnExit(inTick);
	inTick.SetExitNode(this);
}

BT_State BTNode::Run(BTTick inTick)
{
	Enter(inTick);
	bool isOpen = inTick.GetBlackboard()->Get("isOpen", ID);
	if (!isOpen)
		Open(inTick);
	BT_State state = Execute(inTick);
	if (state != BT_State::RUNNING)
		Close(inTick);
	Exit(inTick);
	return state;
}

