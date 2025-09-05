#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"

inline std::vector<std::string> mrtnReferences;

template <typename T>
static T* Relocate(T* ptr, const void* base)
{
	return reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(ptr) + reinterpret_cast<uintptr_t>(base));
}

namespace NMP
{
	class StringTable
	{
	public:
		void Locate();
		void SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject = true);

	private:
		uint32_t m_NumEntrys;
		uint32_t m_DataLength;
		uint32_t* m_IDs;
		uint32_t* m_Offsets;
		const char* m_Data;
	};

	class Vector3
	{
	public:
		void SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject = true) const;

	private:
		union
		{
			struct
			{
				float x;
				float y;
				float z;
				float w;
			};

			float f[4];
		};
	};

	class Quat
	{
	public:
		void SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject = true) const;

	private:
		float x;
		float y;
		float z;
		float w;
	};

	template <typename T>
	class Flags
	{
	public:
		void SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject = true) const
		{
			writer.StartObject();

			writer.Uint(m_flags);

			writer.EndObject();
		}

	private:
		T m_flags;
	};
}

namespace MR
{
	class NodeDef;
	class TransitConditionDef;

	class Manager
	{
	public:
		~Manager();
		static Manager& GetInstance();
		void Construct(TransitConditionDef* transitConditionDef);
		void Construct(NodeDef* nodeDef);

	private:
		Manager();
		Manager(const Manager& other) = delete;
		Manager& operator=(const Manager& other) = delete;

		std::vector<NodeDef*> nodeTypes;
		std::vector<TransitConditionDef*> transitConditionTypes;
	};

	class TransitConditionDef
	{
	public:
		TransitConditionDef(uint32_t nTypeId);
		virtual void Locate() = 0;
		uint32_t GetType() const;
		virtual void SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject = true);

	private:
		uint32_t m_type;
		size_t m_offset;
	};

	class TransitConditionDefFalse : public TransitConditionDef
	{
	public:
		TransitConditionDefFalse(uint32_t nTypeId);
		void Locate() override;
	};

	class TransitConditionDefOnRequest : public TransitConditionDef
	{
	public:
		TransitConditionDefOnRequest(uint32_t nTypeId);
		void Locate() override;
		void SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject = true) override;

	private:
		uint32_t m_requestID;
		bool m_onNotSet;
	};

	class TransitConditionDefInEventSegment : public TransitConditionDef
	{
	public:
		TransitConditionDefInEventSegment(uint32_t nTypeId);
		void Locate() override;
		void SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject = true) override;

	private:
		uint32_t m_eventSegmentIndex;
	};

	class TransitConditionDefCrossedEventBoundary : public TransitConditionDef
	{
	public:
		TransitConditionDefCrossedEventBoundary(uint32_t nTypeId);
		void Locate() override;
		void SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject = true) override;

	private:
		float m_eventTriggerPosition;
	};

	class TransitConditionDefCrossedDurationFraction : public TransitConditionDef
	{
	public:
		TransitConditionDefCrossedDurationFraction(uint32_t nTypeId);
		void Locate() override;
		void SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject = true) override;

	private:
		float m_durationFractionTrigger;
	};

	class TransitConditionDefControlParamFloatGreater : public TransitConditionDef
	{
	public:
		TransitConditionDefControlParamFloatGreater(uint32_t nTypeId);
		void Locate() override;
		void SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject = true) override;

	private:
		uint32_t m_controlParamNodeID;
		float m_testValue;
		bool m_orEqual;
	};

	class TransitConditionDefControlParamFloatLess : public TransitConditionDef
	{
	public:
		TransitConditionDefControlParamFloatLess(uint32_t nTypeId);
		void Locate() override;
		void SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject = true) override;

	private:
		uint32_t m_controlParamNodeID;
		float m_testValue;
		bool m_orEqual;
	};

	class TransitConditionDefControlParamFloatInRange : public TransitConditionDef
	{
	public:
		TransitConditionDefControlParamFloatInRange(uint32_t nTypeId);
		void Locate() override;
		void SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject = true) override;

	private:
		uint32_t m_controlParamNodeID;
		float m_lowerTestValue;
		float m_upperTestValue;
		bool m_notInRange;
	};

	class TransitConditionDefDiscreteEventTriggered : public TransitConditionDef
	{
	public:
		TransitConditionDefDiscreteEventTriggered(uint32_t nTypeId);
		void Locate() override;
		void SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject = true) override;

	private:
		uint32_t m_eventUserData;
		float m_eventWeightThreshold;
		bool m_orEqual;
	};

	class TransitConditionDefInEventRange : public TransitConditionDef
	{
	public:
		TransitConditionDefInEventRange(uint32_t nTypeId);
		void Locate() override;
		void SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject = true) override;

	private:
		float m_eventRangeStart;
		float m_eventRangeEnd;
	};

	class TransitConditionDefPercentageThroughSubtransition : public TransitConditionDef
	{
	public:
		TransitConditionDefPercentageThroughSubtransition(uint32_t nTypeId);
		void Locate() override;
		void SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject = true) override;

	private:
		float m_fPercentageThrough;
		uint32_t m_nSubStateID;
		bool m_bUseTransitionSource;
		bool m_bLessThan;
	};

	namespace OperatorFloat
	{
		enum class OperationType
		{
			OPERATION_SIN = 0,
			OPERATION_COS = 1,
			OPERATION_TAN = 2,
			OPERATION_EXP = 3,
			OPERATION_LOG = 4,
			OPERATION_SQRT = 5,
			OPERATION_ABS = 6,
			OPERATION_RND = 7,
			OPERATION_ROUND = 8,
			OPERATION_NUMOPS = 9,
			OPERATION_FORCEINTSIZE = -1
		};

		std::string ConvertOperationTypeToString(OperationType operationType);
	}

	namespace Operator2Float
	{
		enum OperationType
		{
			OPERATION_MULTIPLY = 0,
			OPERATION_ADD = 1,
			OPERATION_DIVIDE = 2,
			OPERATION_SUBTRACT = 3,
			OPERATION_MIN = 4,
			OPERATION_MAX = 5,
			OPERATION_NUMOPS_0 = 6,
			OPERATION_FORCEINTSIZE_0 = -1
		};

		std::string ConvertOperationTypeToString(OperationType operationType);
	}

	namespace OperatorConst
	{
		enum OperationType
		{
			OPERATION_MULTIPLY_0 = 0,
			OPERATION_ADD_0 = 1,
			OPERATION_DIVIDE_0 = 2,
			OPERATION_SUBTRACT_0 = 3,
			OPERATION_NUMOPS_1 = 4,
			OPERATION_FORCEINTSIZE_1 = -1
		};

		std::string ConvertOperationTypeToString(OperationType operationType);
	}

	class NodeDef
	{
	public:
		NodeDef(uint32_t typeID);
		virtual void Locate();
		uint32_t GetTypeID() const;
		virtual void SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject = true) const;

	private:
		uint32_t m_typeID;
		uint32_t m_nodeID;
		const char* m_pName;
		const NodeDef* m_pParent;
	};

	class NodeDefControlParam : public NodeDef
	{
	public:
		NodeDefControlParam(uint32_t typeID);
	};

	class NodeDefControlParamFloat : public NodeDefControlParam
	{
	public:
		NodeDefControlParamFloat(uint32_t typeID);
		void SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject = true) const override;

	private:
		float m_defaultVal;
	};

	class NodeDefControlParamVector3 : public NodeDefControlParam
	{
	public:
		NodeDefControlParamVector3(uint32_t typeID);
		void SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject = true) const override;

	private:
		NMP::Vector3 m_defaultVal;
	};

	class NodeDefControlParamVector4 : public NodeDefControlParam
	{
	public:
		NodeDefControlParamVector4(uint32_t typeID);
		void SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject = true) const override;

	private:
		NMP::Quat m_defaultVal;
	};

	class NodeDefOperatorFloat : public NodeDefControlParam
	{
	public:
		NodeDefOperatorFloat(uint32_t typeID);
		void SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject = true) const override;

	private:
		uint32_t m_input;
		OperatorFloat::OperationType m_operation;
	};

	class NodeDefOperator2Float : public NodeDefControlParam
	{
	public:
		NodeDefOperator2Float(uint32_t typeID);
		void SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject = true) const override;

	private:
		uint32_t m_input1;
		uint32_t m_input2;
		Operator2Float::OperationType m_operation;
	};

	class NodeDefOperatorConst : public NodeDefControlParam
	{
	public:
		NodeDefOperatorConst(uint32_t typeID);
		void SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject = true) const override;

	private:
		uint32_t m_input;
		OperatorConst::OperationType m_operation;
		float m_constValue;
	};

	class NodeDefOperatorNoiseGen : public NodeDefControlParam
	{
	public:
		NodeDefOperatorNoiseGen(uint32_t typeID);
		void Locate() override;
		void SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject = true) const override;

	private:
		uint32_t m_input;
		float m_frequency;
		uint32_t m_noiseFlags;
		float* m_table1;
		float* m_table2;
		float* m_table3;
	};

	class NodeDefPassThrough : public NodeDef
	{
	public:
		NodeDefPassThrough(uint32_t typeID);
		void SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject = true) const override;

	private:
		uint32_t m_nSourceNodeId;
		uint32_t m_nPad;
	};

	class StateChangeDef
	{
	public:
		void Locate();
		void SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject = true) const;

	private:
		uint32_t m_destinationStateID;
		uint32_t m_numConditions;
		uint32_t* m_conditionIndexes;
	};

	class StateDef
	{
	public:
		void Locate();
		void SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject = true) const;

	private:
		uint32_t m_nodeID;
		uint32_t m_numConditions;
		uint32_t* m_conditionIndexes;
		uint32_t m_numStateChanges;
		StateChangeDef* m_stateChanges;
	};

	class NodeDefStateMachine : public NodeDefPassThrough
	{
	public:
		NodeDefStateMachine(uint32_t typeID);
		void Locate() override;
		void SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject = true) const override;

	private:
		uint32_t m_numStates;
		StateDef* m_stateDefs;
		uint32_t m_numConditions;
		TransitConditionDef** m_conditions;
		uint32_t m_numChildren;
		NodeDef** m_children;
	};

	class IAnimSource;

	class NodeDefAnim : public NodeDef
	{
	public:
		NodeDefAnim(uint32_t typeID);
		void SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject = true) const override;

	private:
		bool m_generateDeltas;
		bool m_loop;
		bool m_playBackwards;
		float m_clipStartFraction;
		float m_clipEndFraction;
		IAnimSource* m_animSource;
	};

	class NodeDefAnimWithEvents : public NodeDefAnim
	{
	public:
		NodeDefAnimWithEvents(uint32_t typeID);
		void SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject = true) const override;

	private:
		int32_t m_startEventIndex;
	};

	class NodeDefBlendBase : public NodeDef
	{
	public:
		NodeDefBlendBase(uint32_t typeID);
		void SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject = true) const override;

	private:
		uint32_t m_aID;
		uint32_t m_bID;
		bool m_UseSource1Additively;
		bool m_Source0IsFullBody;
		uint8_t m_pad[6];
	};

	class NodeDefBlend2 : public NodeDefBlendBase
	{
	public:
		NodeDefBlend2(uint32_t typeID);
		void SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject = true) const override;

	private:
		uint32_t m_weightNodeID;
		bool m_loop;
		bool m_additiveBlendAtt;
		bool m_additiveBlendPos;
		bool m_slerpDeltaTrajTrans;
		bool m_source0BranchOptimization;
		bool m_source1BranchOptimization;
		bool m_ignoreSource0EventWeight;
		bool m_ignoreSource1EventWeight;
		bool m_bUpdateWeigthingOnce;
	};

	class NodeDefBlendN : public NodeDefBlend2
	{
	public:
		NodeDefBlendN(uint32_t typeID);
		void SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject = true) const override;
	
		struct ConnectionDef
		{
		public:
			void SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject = true) const;

		private:
			uint32_t connectedNodeId;
			float weight;
		};

	private:
		uint32_t m_numSourceNodes;
		ConnectionDef m_connectedSourceNode[1];
	};

	class NodeDefBlend2MatchEvents : public NodeDefBlend2
	{
	public:
		NodeDefBlend2MatchEvents(uint32_t typeID);
		void SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject = true) const override;

	private:
		uint32_t m_eventWeightNodeID;
		int32_t m_startEventIndex;
		uint32_t m_durationEventMatchingType;
	};

	class NodeDefBlendNMatchEvents : public NodeDefBlend2MatchEvents
	{
	public:
		class ConnectionDef
		{
		public:
			void SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject = true) const;

		private:
			uint32_t connectedNodeId;
			float weight;
		};

		NodeDefBlendNMatchEvents(uint32_t typeID);
		void SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject = true) const override;

	private:
		uint32_t m_numSourceNodes;
		ConnectionDef m_connectedSourceNode[1];
	};

	class NodeDefPassThroughTransforms : public NodeDefPassThrough
	{
	public:
		NodeDefPassThroughTransforms(uint32_t typeID);
	};

	class NodeDefFilterTransforms : public NodeDefPassThroughTransforms
	{
	public:
		NodeDefFilterTransforms(uint32_t typeID);
		void Locate() override;
		void SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject = true) const override;

	private:
		uint32_t m_numBoneFilterIDs;
		uint32_t* m_boneFilterIDs;
	};

	class NodeDefSingleFrame : public NodeDefPassThroughTransforms
	{
	public:
		NodeDefSingleFrame(uint32_t typeID);
		void SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject = true) const override;

	private:
		uint32_t m_controlNodeID;
		bool m_bUseTrajectory;
	};

	class NodeDefComputeWorldTransforms : public NodeDefPassThroughTransforms
	{
	public:
		NodeDefComputeWorldTransforms(uint32_t typeID);
	};

	struct NodeRef
	{
		void SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject = true) const;

		uint16_t m_nodeId;
	};

	class NodeDefFeatherBlend2 : public NodeDef
	{
	public:
		NodeDefFeatherBlend2(uint32_t typeID);
		void Locate() override;
		void SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject = true) const override;

	private:
		NodeRef m_aID;
		NodeRef m_bID;
		NodeRef m_weightNodeID;
		uint16_t m_numBoneWeights;
		float* m_boneWeights;
		bool m_loop;
		bool m_additiveBlendAtt;
		bool m_additiveBlendPos;
		bool m_slerpDeltaTrajTrans;
	};

	struct BoneId
	{
		void SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject = true) const;

		uint16_t m_boneId;
	};

	class NodeDefLockFoot : public NodeDefPassThroughTransforms
	{
	public:
		NodeDefLockFoot(uint32_t typeID);
		void SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject = true) const override;

	private:
		float m_catchupSpeedFactor;
		float m_snapToSourceDistance;
		float m_straightestLegFactor;
		int32_t m_footfallEventID;
		float m_lowerHeightBound;
		float m_toeLowerHeightBound;
		NMP::Vector3 m_kneeRotationAxis;
		NMP::Vector3 m_ballRotationAxis;
		NMP::Flags<unsigned int> m_upAxis;
		NodeRef m_IkFkBlendWeightNodeID;
		NodeRef m_swivelContributionToOrientationNodeID;
		uint16_t m_pad;
		BoneId m_hipIndex;
		BoneId m_kneeIndex;
		BoneId m_ankleIndex;
		BoneId m_ballIndex;
		BoneId m_toeIndex;
		bool m_fixGroundPenetration;
		bool m_flipKneeRotationDirection;
		bool m_useBallJoint;
		bool m_assumeSimpleHierarchy;
		bool m_fixToeGroundPenetration;
		bool m_valid;
	};

	class NodeDefTwoBoneIK : public NodeDefPassThroughTransforms
	{
	public:
		NodeDefTwoBoneIK(uint32_t typeID);
		void SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject = true) const override;

	private:
		BoneId m_endJointIndex;
		BoneId m_midJointIndex;
		BoneId m_rootJointIndex;
		BoneId m_referenceJointIndex;
		NodeRef m_effectorTargetNodeID;
		NodeRef m_targetOrientationNodeID;
		NodeRef m_swivelAngleNodeID;
		NodeRef m_IkFkBlendWeightNodeID;
		NodeRef m_swivelContributionToOrientationNodeID;
		float m_midJointRotationAxisX;
		float m_midJointRotationAxisY;
		float m_midJointRotationAxisZ;
		bool m_flipMidJointRotationDirection;
		bool m_assumeSimpleHierarchy;
		bool m_keepEndEffOrientation;
		bool m_endEffOrientationFromReferenceJoint;
		bool m_globalReferenceAxis;
		bool m_updateTargetByDeltas;
		float m_midJointReferenceAxisX;
		float m_midJointReferenceAxisY;
		float m_midJointReferenceAxisZ;
	};

	class NodeDefHeadLook : public NodeDefPassThroughTransforms
	{
	public:
		NodeDefHeadLook(uint32_t typeID);
		void SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject = true) const override;

	private:
		BoneId m_endJointIndex;
		BoneId m_rootJointIndex;
		BoneId m_pointingJointIndex;
		NodeRef m_targetNodeID;
		NodeRef m_pointingJointAxisNodeID;
		NodeRef m_pointingJointIDNodeID;
		NodeRef m_blendWeightNodeID;
		float m_pointingJointAxisX;
		float m_pointingJointAxisY;
		float m_pointingJointAxisZ;
		float m_bias;
		bool m_updateTargetByDeltas;
		bool m_pointingVectorInCS;
	};

	class NodeDefApplyBindPose : public NodeDefPassThroughTransforms
	{
	public:
		NodeDefApplyBindPose(uint32_t typeID);
	};

	class NodeDefTransit : public NodeDefBlendBase
	{
	public:
		NodeDefTransit(uint32_t typeID);
		void SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject = true) const override;

	private:
		float m_transitionDuration;
		bool m_bIgnoreSourceTrajectory;
		bool m_bEnableRealign;
		bool m_bSnapBlending;
	};

	class NodeDefTransitAtEvent : public NodeDefTransit
	{
	public:
		NodeDefTransitAtEvent(uint32_t typeID);
		void SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject = true) const override;

	private:
		uint32_t m_destStartEventIndex;
		bool m_startFromSetFractionOfDestEvent;
		float m_destStartEventFraction;
	};

	class NodeDefTransitMatchEvents : public NodeDefTransit
	{
	public:
		NodeDefTransitMatchEvents(uint32_t typeID);
		void SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject = true) const override;

	private:
		uint32_t m_destEventSequenceOffset;
		uint32_t m_destStartEventIndex;
		bool m_usingDestStartEventIndex;
		uint32_t m_durationEventMatchingType;
	};

	class NodeDefBlendTree : public NodeDef
	{
	public:
		NodeDefBlendTree(uint32_t typeID);
		void Locate() override;
		void SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject = true) const override;

	private:
		uint32_t m_nNumChildren;
		NodeDef** m_children;
		uint32_t m_nRootNodeId;
	};

	class Rig;

	struct TransformBuffersCount
	{
	public:
		void SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject = true);

	private:
		uint32_t m_numTranformBufferTypesUsed;
		uint32_t m_transformBufferTypes[8];
		uint32_t m_transformBufferCounts[8];
	};

	struct NetworkDef
	{
	public:
		void Locate();
		std::string SerializeToJson();

		struct _NetworkHash
		{
			uint8_t b[16];
		};

	private:
		uint32_t m_numAnimations;
		IAnimSource** m_animLibrary;
		Rig* m_rig;
		uint32_t m_numNodeNames;
		const char* m_nodeNames;
		uint32_t m_numNodeDefs;
		uint32_t m_numDummyBlendTreeDefs;
		NodeDef** m_nodeDefs;
		uint32_t m_maxDurationEventsPoolSize;
		uint32_t m_rootNodeID;
		uint32_t m_numNodeStateMachines;
		uint32_t* m_nodeStateMachineNodeIDs;
		uint32_t m_numInterfaceControlParameters;
		uint32_t* m_interfaceControlParameterNodeIDs;
		uint32_t m_numPersistentNodes;
		uint32_t* m_persistentNodeIDs;
		_NetworkHash m_networkHash;
		NMP::StringTable* m_requestIDStringTable;
		TransformBuffersCount m_maxTransformBufferReqs;
	};
}

namespace MRSamples
{
	class NodeDefPlaySpeedModifier : public MR::NodeDefPassThrough
	{
	public:
		NodeDefPlaySpeedModifier(uint32_t typeID);
		void SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject = true) const override;

	private:
		uint32_t m_playSpeedFactorID;
	};
}

class NodeDefModifyBoneAlpha : public MR::NodeDefPassThroughTransforms
{
public:
	NodeDefModifyBoneAlpha(uint32_t typeID);
	void Locate() override;
	void SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject = true) const override;

private:
	uint32_t m_nWeightNodeID;
	uint32_t m_numBones;
	float* m_boneAlphas;
};

class NodeDefApplyBoneMask : public MR::NodeDefPassThroughTransforms
{
public:
	NodeDefApplyBoneMask(uint32_t typeID);
	//void Locate() override;
	void SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject = true) const override;

private:
	uint8_t unk[16];
};

class ZNodeDefAnimIOI : public MR::NodeDefAnimWithEvents
{
public:
	ZNodeDefAnimIOI(uint32_t typeID);
};

class ZNodeDefAnimIOICutSequence : public MR::NodeDef
{
public:
	ZNodeDefAnimIOICutSequence(uint32_t typeID);
	void Locate() override;
	void SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject = true) const override;

private:
	const char* m_pszSlotName;
};

class ZNodeDefVariationIOI : public ZNodeDefAnimIOI
{
public:
	ZNodeDefVariationIOI(uint32_t typeID);
	void Locate() override;
	void SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject = true) const override;

private:
	const char* m_pszVariationName;
	bool m_bBlendFromLastFrame;
};

class ZNodeDefChildNetworkIOI : public MR::NodeDef
{
public:
	ZNodeDefChildNetworkIOI(uint32_t typeID);
};

class ZNodeDefSelectiveFeatherBlend : public MR::NodeDefBlend2
{
public:
	ZNodeDefSelectiveFeatherBlend(uint32_t typeID);
	void Locate() override;
	void SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject = true) const override;

private:
	uint32_t m_featherWeightNodeID;
	uint32_t m_ignoreTrajectory0NodeID;
	uint32_t m_ignoreTrajectory1NodeID;
	uint32_t m_numBoneWeights;
	float* m_paBoneWeights;
};

class NodeDefBlend2ForwardEvents : public MR::NodeDefBlend2
{
public:
	NodeDefBlend2ForwardEvents(uint32_t typeID);
	void SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject = true) const override;

private:
	bool m_bUseGlobalDeltaTime;
};

class ZNodeDefSelectiveFeatherBlendForwardEvents : public NodeDefBlend2ForwardEvents
{
public:
	ZNodeDefSelectiveFeatherBlendForwardEvents(uint32_t typeID);
	void Locate() override;
	void SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject = true) const override;

private:
	uint32_t m_featherWeightNodeID;
	uint32_t m_numBoneWeights;
	float* m_paBoneWeights;
};

class ZNodeDefGroundRotation : public MR::NodeDefPassThrough
{
public:
	ZNodeDefGroundRotation(uint32_t typeID);
	void SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject = true) const override;

private:
	uint32_t m_nAngleNodeId;
	uint32_t m_nTrajectoryNodeID;
	uint32_t m_nTranslationThresholdNodeID;
	uint32_t m_nAttitudeThresholdNodeID;
	bool m_bOverrideTrajectory;
	bool m_bCorrectiveTranslationModification;
	bool m_bCorrectiveAttitudeModification;
	bool m_bRotateTrajectory;
	bool m_bRotateTrajectoryToEndPosition;
	bool m_bApplyAsDeltaValue;
	bool m_bMirrorTrajectory;
	uint32_t m_nCorrectionStartEventID;
	uint32_t m_nCorrectionEndEventID;
};

class ZNodeDefScaleAnim : public MR::NodeDefPassThroughTransforms
{
public:
	ZNodeDefScaleAnim(uint32_t typeID);
	void SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject = true) const override;

private:
	uint32_t m_nBoneScaleNodeId;
	uint32_t m_nTrajectoryTranslationScaleNodeID;
	uint32_t m_nTrajectoryOrientationScaleNodeID;
	uint32_t m_nTimeScaleNodeId;
	MR::NodeRef m_nReferenceNodeId;
};

struct SNodeLookAtIDs
{
	void SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject = true) const;

	uint32_t m_directionNodeID;
	uint32_t m_weightNodeID;
	uint32_t m_iHeadBoneIndex;
};

class ZIOINodeLookAtDef : public MR::NodeDefPassThroughTransforms
{
public:
	ZIOINodeLookAtDef(uint32_t typeID);
	void SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject = true) const override;

private:
	SNodeLookAtIDs m_NodeIDs;
};

struct SNodeSelectIDs_V2
{
	void SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject = true) const;

	uint32_t m_sourceNodeIDs[35];
	uint32_t m_selectCtrlID;
	uint32_t m_blendCtrlID;
};

class ZIOINodeSelectDef : public MR::NodeDef
{
public:
	ZIOINodeSelectDef(uint32_t typeID);
	void SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject = true) const override;

private:
	SNodeSelectIDs_V2 m_NodeIDs;
	bool m_bRandomSelectAtInit;
	bool m_bUpdateSelectIndex;
};

class ZIOINodeSelectMatrixDef : public MR::NodeDef
{
public:
	ZIOINodeSelectMatrixDef(uint32_t typeID);
	void SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject = true) const override;

private:
	uint8_t unk[152];
};

class ZIOINodeSelectSnapBlendDef : public MR::NodeDef
{
public:
	ZIOINodeSelectSnapBlendDef(uint32_t typeID);
	void SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject = true) const override;

private:
	uint8_t unk[152];
};

class ZIOINodeSelectItemDef : public MR::NodeDef
{
public:
	ZIOINodeSelectItemDef(uint32_t typeID);
	void SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject = true) const override;

private:
	uint8_t unk[24];
};

class ZNodeDefTransitionSelect : public MR::NodeDefPassThrough
{
public:
	ZNodeDefTransitionSelect(uint32_t typeID);
	void SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject = true) const override;

private:
	MR::NodeRef m_currentVelocityCtrlID;
	MR::NodeRef m_currentFootCtrlID;
	MR::NodeRef m_targetVelocityCtrlID;
	MR::NodeRef m_targetRotationOffsetCtrlID;
	MR::NodeRef m_targetPositionOffsetCtrlID;
	MR::NodeRef m_sourceNodeIDs[24];
};

class ZNodeDefIOITransit : public MR::NodeDefTransit
{
public:
	ZNodeDefIOITransit(uint32_t typeID);
	void SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject = true) const override;

private:
	bool m_bStartDestinationFromBeginning;
	bool m_bBlendFromLastFrame;
};

class NodeDefIOIDeltaAnim : public MR::NodeDefBlend2
{
public:
	NodeDefIOIDeltaAnim(uint32_t typeID);
};

class NodeDefIOIDeltaAnimMatchEvents : public MR::NodeDefBlend2MatchEvents
{
public:
	NodeDefIOIDeltaAnimMatchEvents(uint32_t typeID);
};

class NodeDefIOIHeadController : public MR::NodeDefPassThroughTransforms
{
public:
	NodeDefIOIHeadController(uint32_t typeID);
	void SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject = true) const override;

private:
	float m_pointingVectorX;
	float m_pointingVectorY;
	float m_pointingVectorZ;
	float m_offsetX;
	float m_offsetY;
	float m_offsetZ;
	MR::BoneId m_headEndJoint;
	MR::BoneId m_headRootJoint;
	MR::BoneId m_leftEyeJoint;
	MR::BoneId m_rightEyeJoint;
	MR::BoneId m_leftEyelidJoint;
	MR::BoneId m_rightEyelidJoint;
	MR::BoneId m_leftEyebrowJoint;
	MR::BoneId m_rightEyebrowJoint;
	MR::NodeRef m_targetNodeID;
	MR::NodeRef m_targetNoiseNodeID;
	MR::NodeRef m_targetWeightNodeID;
	MR::NodeRef m_headBiasNodeID;
	MR::NodeRef m_drowsinessNodeID;
	MR::NodeRef m_blendWeightNodeID;
	bool m_updateTargetByDeltas;
};

class NodeDefIOIPelvisOffset : public MR::NodeDefPassThroughTransforms
{
public:
	NodeDefIOIPelvisOffset(uint32_t typeID);
	void Locate() override;
	void SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject = true) const override;

private:
	uint32_t m_OffsetWeightNodeID;
	uint32_t m_OffsetVectorNodeID;
	const char* m_pszBoneName;
};

class NodeDefIOIMirror : public MR::NodeDefPassThroughTransforms
{
public:
	NodeDefIOIMirror(uint32_t typeID);
	void SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject = true) const override;

private:
	MR::NodeRef m_nDisableOptionID;
	bool m_bSwapHandAttachers;
};

class NodeDefIOIMirrorMatchEvents : public MR::NodeDefPassThroughTransforms
{
public:
	NodeDefIOIMirrorMatchEvents(uint32_t typeID);
	void SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject = true) const override;

private:
	uint32_t m_rightFootEvent;
	uint32_t m_leftFootEvent;
	uint32_t m_rightHandEvent;
	uint32_t m_leftHandEvent;
	bool m_bSwapHandAttachers;
};

class NodeDefIOIBlend2AndReTarget : public MR::NodeDefBlend2
{
public:
	NodeDefIOIBlend2AndReTarget(uint32_t typeID);
	void SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject = true) const override;

private:
	uint32_t m_nReTargetFlags;
};

class NodeDefPlaySpeedModifierMatchEvents : public MR::NodeDefPassThrough
{
public:
	NodeDefPlaySpeedModifierMatchEvents(uint32_t typeID);
	void SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject = true) const override;

private:
	uint32_t m_playSpeedFactorID;
};

class NodeDefIOIPartialMirrorAim : public MR::NodeDefPassThroughTransforms
{
public:
	NodeDefIOIPartialMirrorAim(uint32_t typeID);
	void SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject = true) const override;

private:
	uint32_t m_MirrorWeightNodeID;
};

class ZNodeDefIOISneakModifier : public MR::NodeDefPassThroughTransforms
{
public:
	ZNodeDefIOISneakModifier(uint32_t typeID);
	void SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject = true) const override;

private:
	uint32_t m_nWeightNodeID;
	uint32_t m_nPelvisOffsetNodeID;
	uint32_t m_nPelvisAngleNodeID;
	uint32_t m_nSpeedModifierNodeID;
	uint32_t m_nLeftHandQuatNodeID;
};

class ZNodeDefIOITranslationScale : public MR::NodeDefPassThrough
{
public:
	ZNodeDefIOITranslationScale(uint32_t typeID);
	void SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject = true) const override;

private:
	uint32_t m_nScaleNodeId;
};

class ZNodeDefIOIWildCardTransitMatchEvents : public MR::NodeDefTransitMatchEvents
{
public:
	ZNodeDefIOIWildCardTransitMatchEvents(uint32_t typeID);
};

class ZNodeDefIOIWildCardTransit : public MR::NodeDefTransit
{
public:
	ZNodeDefIOIWildCardTransit(uint32_t typeID);
};

struct SNodeSelectMatchEventsInfo
{
	struct SNodeInfo
	{
		void SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject = true) const;

		uint32_t m_id;
		float m_index;
	};
};

struct SNodeSelectMatchEventsInfo_V2
{
	void SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject = true) const;

	SNodeSelectMatchEventsInfo::SNodeInfo m_sourceNodeIDs[35];
	uint32_t m_selectCtrlID;
	uint32_t m_blendCtrlID;
};

class ZNodeDefSelectMatchEvents : public MR::NodeDefTransitMatchEvents
{
public:
	ZNodeDefSelectMatchEvents(uint32_t typeID);
	void SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject = true) const override;

private:
	SNodeSelectMatchEventsInfo_V2 m_NodeIDs;
	bool m_bRandomSelectAtInit;
	bool m_bUpdateSelectIndex;
};

class NodeDefIOIParametricBlendNMatchEvents : public MR::NodeDefBlend2MatchEvents
{
public:
	NodeDefIOIParametricBlendNMatchEvents(uint32_t typeID);
	void SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject = true) const override;

private:
	uint32_t m_numSourceNodes;
	uint32_t m_connectedSourceNode[1];
};

class ZNodeDefIOIFeatherTransit : public MR::NodeDefTransit
{
public:
	ZNodeDefIOIFeatherTransit(uint32_t typeID);
	void SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject = true) const override;

private:
	uint8_t unk[24];
};
