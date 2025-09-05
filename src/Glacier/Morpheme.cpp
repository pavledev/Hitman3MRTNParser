#include <sstream>

#include "Glacier/Morpheme.h"

void NMP::StringTable::Locate()
{
	auto base = static_cast<const void*>(this);

	m_IDs = Relocate(m_IDs, base);
	m_Offsets = Relocate(m_Offsets, base);
	m_Data = Relocate(m_Data, base);
}

void NMP::StringTable::SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject)
{
	writer.StartObject();

	writer.String("m_NumEntrys");
	writer.Uint(m_NumEntrys);

	writer.String("m_DataLength");
	writer.Uint(m_DataLength);

	writer.String("m_IDs");
	writer.StartArray();

	for (uint32_t i = 0; i < m_NumEntrys; ++i)
	{
		writer.Uint(m_IDs[i]);
	}

	writer.EndArray();

	writer.String("m_Offsets");
	writer.StartArray();

	for (uint32_t i = 0; i < m_NumEntrys; ++i)
	{
		writer.Uint(m_Offsets[i]);
	}

	writer.EndArray();

	writer.String("m_Data");
	writer.StartArray();

	uint32_t length = 0;

	while (length < m_DataLength)
	{
		const char* name = m_Data + length;

		writer.String(m_Data + length);

		length += static_cast<uint32_t>(strlen(name)) + 1;
	}

	writer.EndArray();

	writer.EndObject();
}

void NMP::Vector3::SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject) const
{
	writer.StartObject();

	writer.String("x");
	writer.Double(x);

	writer.String("y");
	writer.Double(y);

	writer.String("z");
	writer.Double(z);

	writer.String("w");
	writer.Double(w);

	writer.EndObject();
}

void NMP::Quat::SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject) const
{
	writer.StartObject();

	writer.String("x");
	writer.Double(x);

	writer.String("y");
	writer.Double(y);

	writer.String("z");
	writer.Double(z);

	writer.String("w");
	writer.Double(w);

	writer.EndObject();
}

MR::Manager::Manager()
{
	nodeTypes.push_back(new NodeDefControlParamFloat(20));
	nodeTypes.push_back(new NodeDefControlParamVector3(21));
	nodeTypes.push_back(new NodeDefControlParamVector4(22));
	nodeTypes.push_back(new NodeDefOperatorFloat(110));
	nodeTypes.push_back(new NodeDefOperator2Float(111));
	nodeTypes.push_back(new NodeDefOperatorConst(112));
	nodeTypes.push_back(new NodeDefOperatorNoiseGen(113));
	nodeTypes.push_back(new NodeDefStateMachine(10));
	nodeTypes.push_back(new NodeDefAnim(103));
	nodeTypes.push_back(new NodeDefAnimWithEvents(104));
	nodeTypes.push_back(new NodeDefBlend2(107));
	nodeTypes.push_back(new NodeDefBlendN(108));
	nodeTypes.push_back(new NodeDefBlend2MatchEvents(101));
	nodeTypes.push_back(new NodeDefBlendNMatchEvents(102));
	nodeTypes.push_back(new NodeDefFilterTransforms(105));
	nodeTypes.push_back(new NodeDefModifyBoneAlpha(65546));
	nodeTypes.push_back(new NodeDefApplyBoneMask(65547));
	nodeTypes.push_back(new NodeDefSingleFrame(109));
	nodeTypes.push_back(new NodeDefComputeWorldTransforms(106));
	nodeTypes.push_back(new NodeDefFeatherBlend2(114));
	nodeTypes.push_back(new NodeDefLockFoot(121));
	nodeTypes.push_back(new NodeDefTwoBoneIK(120));
	nodeTypes.push_back(new NodeDefHeadLook(122));
	nodeTypes.push_back(new NodeDefApplyBindPose(115));
	nodeTypes.push_back(new NodeDefTransit(402));
	nodeTypes.push_back(new NodeDefTransitAtEvent(400));
	nodeTypes.push_back(new NodeDefTransitMatchEvents(401));
	nodeTypes.push_back(new NodeDefBlendTree(12));
	nodeTypes.push_back(new ZNodeDefAnimIOI(65536));
	nodeTypes.push_back(new ZNodeDefAnimIOICutSequence(65537));
	nodeTypes.push_back(new ZNodeDefVariationIOI(65538));
	nodeTypes.push_back(new ZNodeDefChildNetworkIOI(65539));
	nodeTypes.push_back(new ZNodeDefSelectiveFeatherBlend(65540));
	nodeTypes.push_back(new ZNodeDefSelectiveFeatherBlendForwardEvents(65541));
	nodeTypes.push_back(new MRSamples::NodeDefPlaySpeedModifier(125));
	nodeTypes.push_back(new ZNodeDefGroundRotation(65542));
	nodeTypes.push_back(new ZNodeDefScaleAnim(65545));
	nodeTypes.push_back(new ZIOINodeLookAtDef(131072));
	nodeTypes.push_back(new ZIOINodeSelectDef(131074));
	nodeTypes.push_back(new ZIOINodeSelectMatrixDef(131095));
	nodeTypes.push_back(new ZIOINodeSelectSnapBlendDef(131094));
	nodeTypes.push_back(new ZIOINodeSelectItemDef(131093));
	nodeTypes.push_back(new ZNodeDefTransitionSelect(65544));
	nodeTypes.push_back(new ZNodeDefIOITransit(131075));
	nodeTypes.push_back(new NodeDefIOIDeltaAnim(131078));
	nodeTypes.push_back(new NodeDefIOIDeltaAnimMatchEvents(131077));
	nodeTypes.push_back(new NodeDefIOIHeadController(131079));
	nodeTypes.push_back(new NodeDefIOIPelvisOffset(131080));
	nodeTypes.push_back(new NodeDefIOIMirror(131086));
	nodeTypes.push_back(new NodeDefIOIMirrorMatchEvents(131081));
	nodeTypes.push_back(new NodeDefIOIBlend2AndReTarget(131082));
	nodeTypes.push_back(new NodeDefPlaySpeedModifierMatchEvents(11));
	nodeTypes.push_back(new NodeDefIOIPartialMirrorAim(131084));
	nodeTypes.push_back(new NodeDefBlend2ForwardEvents(131085));
	nodeTypes.push_back(new ZNodeDefIOISneakModifier(131087));
	nodeTypes.push_back(new ZNodeDefIOITranslationScale(131088));
	nodeTypes.push_back(new ZNodeDefIOIWildCardTransitMatchEvents(131089));
	nodeTypes.push_back(new ZNodeDefIOIWildCardTransit(131090));
	nodeTypes.push_back(new ZNodeDefSelectMatchEvents(65543));
	nodeTypes.push_back(new NodeDefIOIParametricBlendNMatchEvents(131091));
	nodeTypes.push_back(new ZNodeDefIOIFeatherTransit(131092));

	transitConditionTypes.push_back(new TransitConditionDefFalse(607));
	transitConditionTypes.push_back(new TransitConditionDefOnRequest(601));
	transitConditionTypes.push_back(new TransitConditionDefInEventSegment(605));
	transitConditionTypes.push_back(new TransitConditionDefCrossedEventBoundary(604));
	transitConditionTypes.push_back(new TransitConditionDefCrossedDurationFraction(603));
	transitConditionTypes.push_back(new TransitConditionDefControlParamFloatGreater(606));
	transitConditionTypes.push_back(new TransitConditionDefControlParamFloatLess(608));
	transitConditionTypes.push_back(new TransitConditionDefControlParamFloatInRange(609));
	transitConditionTypes.push_back(new TransitConditionDefDiscreteEventTriggered(602));
	transitConditionTypes.push_back(new TransitConditionDefInEventRange(611));
	transitConditionTypes.push_back(new TransitConditionDefPercentageThroughSubtransition(131472));
}

MR::Manager::~Manager()
{
	for (size_t i = 0; i < nodeTypes.size(); ++i)
	{
		delete[] nodeTypes[i];
	}

	for (size_t i = 0; i < transitConditionTypes.size(); ++i)
	{
		delete[] transitConditionTypes[i];
	}
}

MR::Manager& MR::Manager::GetInstance()
{
	static Manager instance;

	return instance;
}

void MR::Manager::Construct(NodeDef* nodeDef)
{
	for (size_t i = 0; i < nodeTypes.size(); ++i)
	{
		/*if (nodeDef->GetTypeID() == 65547 ||
			nodeDef->GetTypeID() == 131095 ||
			nodeDef->GetTypeID() == 131094 ||
			nodeDef->GetTypeID() == 131093 ||
			nodeDef->GetTypeID() == 131092)
		{
			int a = 2;
		}*/

		if (nodeTypes[i]->GetTypeID() == nodeDef->GetTypeID())
		{
			void** vTable = *reinterpret_cast<void***>(nodeTypes[i]);
			*reinterpret_cast<void***>(nodeDef) = vTable;

			break;
		}
	}
}

void MR::Manager::Construct(TransitConditionDef* transitConditionDef)
{
	for (size_t i = 0; i < transitConditionTypes.size(); ++i)
	{
		if (transitConditionTypes[i]->GetType() == transitConditionDef->GetType())
		{
			void** vTable = *reinterpret_cast<void***>(transitConditionTypes[i]);
			*reinterpret_cast<void***>(transitConditionDef) = vTable;

			break;
		}
	}
}

MR::TransitConditionDef::TransitConditionDef(uint32_t nTypeId)
{
	m_type = nTypeId;
	m_offset = -1;
}

uint32_t MR::TransitConditionDef::GetType() const
{
	return m_type;
}

void MR::TransitConditionDef::SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject)
{
	writer.String("m_type");
	writer.Uint(m_type);

	writer.String("m_offset");
	writer.Uint64(m_offset);
}

MR::TransitConditionDefFalse::TransitConditionDefFalse(uint32_t nTypeId) : TransitConditionDef(nTypeId)
{
}

void MR::TransitConditionDefFalse::Locate()
{

}

MR::TransitConditionDefOnRequest::TransitConditionDefOnRequest(uint32_t nTypeId) : TransitConditionDef(nTypeId)
{
	m_requestID = 0;
	m_onNotSet = false;
}

void MR::TransitConditionDefOnRequest::Locate()
{

}

void MR::TransitConditionDefOnRequest::SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject)
{
	writer.StartObject();

	TransitConditionDef::SerializeToJson(writer);

	writer.String("m_requestID");
	writer.Uint(m_requestID);

	writer.String("m_onNotSet");
	writer.Bool(m_onNotSet);

	writer.EndObject();
}

MR::TransitConditionDefInEventSegment::TransitConditionDefInEventSegment(uint32_t nTypeId) : TransitConditionDef(nTypeId)
{
	m_eventSegmentIndex = 0;
}

void MR::TransitConditionDefInEventSegment::Locate()
{

}

void MR::TransitConditionDefInEventSegment::SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject)
{
	writer.StartObject();

	TransitConditionDef::SerializeToJson(writer);

	writer.String("m_eventSegmentIndex");
	writer.Uint(m_eventSegmentIndex);

	writer.EndObject();
}

MR::TransitConditionDefCrossedEventBoundary::TransitConditionDefCrossedEventBoundary(uint32_t nTypeId) : TransitConditionDef(nTypeId)
{
	m_eventTriggerPosition = 0;
}

void MR::TransitConditionDefCrossedEventBoundary::Locate()
{

}

void MR::TransitConditionDefCrossedEventBoundary::SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject)
{
	writer.StartObject();

	TransitConditionDef::SerializeToJson(writer);

	writer.String("m_eventTriggerPosition");
	writer.Double(m_eventTriggerPosition);

	writer.EndObject();
}

MR::TransitConditionDefCrossedDurationFraction::TransitConditionDefCrossedDurationFraction(uint32_t nTypeId) : TransitConditionDef(nTypeId)
{
	m_durationFractionTrigger = 0;
}

void MR::TransitConditionDefCrossedDurationFraction::Locate()
{

}

void MR::TransitConditionDefCrossedDurationFraction::SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject)
{
	writer.StartObject();

	TransitConditionDef::SerializeToJson(writer);

	writer.String("m_durationFractionTrigger");
	writer.Double(m_durationFractionTrigger);

	writer.EndObject();
}

MR::TransitConditionDefControlParamFloatGreater::TransitConditionDefControlParamFloatGreater(uint32_t nTypeId) : TransitConditionDef(nTypeId)
{
	m_controlParamNodeID = 0;
	m_testValue = 0;
	m_orEqual = false;
}

void MR::TransitConditionDefControlParamFloatGreater::Locate()
{

}

void MR::TransitConditionDefControlParamFloatGreater::SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject)
{
	writer.StartObject();

	TransitConditionDef::SerializeToJson(writer);

	writer.String("m_controlParamNodeID");
	writer.Uint(m_controlParamNodeID);

	writer.String("m_testValue");
	writer.Double(m_testValue);

	writer.String("m_orEqual");
	writer.Double(m_orEqual);

	writer.EndObject();
}

MR::TransitConditionDefControlParamFloatLess::TransitConditionDefControlParamFloatLess(uint32_t nTypeId) : TransitConditionDef(nTypeId)
{
	m_controlParamNodeID = 0;
	m_testValue = 0;
	m_orEqual = false;
}

void MR::TransitConditionDefControlParamFloatLess::Locate()
{

}

void MR::TransitConditionDefControlParamFloatLess::SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject)
{
	writer.StartObject();

	TransitConditionDef::SerializeToJson(writer);

	writer.String("m_controlParamNodeID");
	writer.Uint(m_controlParamNodeID);

	writer.String("m_testValue");
	writer.Double(m_testValue);

	writer.String("m_orEqual");
	writer.Bool(m_orEqual);

	writer.EndObject();
}

MR::TransitConditionDefControlParamFloatInRange::TransitConditionDefControlParamFloatInRange(uint32_t nTypeId) : TransitConditionDef(nTypeId)
{
	m_controlParamNodeID = 0;
	m_lowerTestValue = 0;
	m_upperTestValue = 0;
	m_notInRange = false;
}

void MR::TransitConditionDefControlParamFloatInRange::Locate()
{

}

void MR::TransitConditionDefControlParamFloatInRange::SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject)
{
	writer.StartObject();

	TransitConditionDef::SerializeToJson(writer);

	writer.String("m_controlParamNodeID");
	writer.Uint(m_controlParamNodeID);

	writer.String("m_lowerTestValue");
	writer.Double(m_lowerTestValue);

	writer.String("m_upperTestValue");
	writer.Double(m_upperTestValue);

	writer.String("m_notInRange");
	writer.Double(m_notInRange);

	writer.EndObject();
}

MR::TransitConditionDefDiscreteEventTriggered::TransitConditionDefDiscreteEventTriggered(uint32_t nTypeId) : TransitConditionDef(nTypeId)
{
	m_eventUserData = 0;
	m_eventWeightThreshold = 0;
	m_orEqual = false;
}

void MR::TransitConditionDefDiscreteEventTriggered::Locate()
{

}

void MR::TransitConditionDefDiscreteEventTriggered::SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject)
{
	writer.StartObject();

	TransitConditionDef::SerializeToJson(writer);

	writer.String("m_eventUserData");
	writer.Uint(m_eventUserData);

	writer.String("m_eventWeightThreshold");
	writer.Double(m_eventWeightThreshold);

	writer.String("m_orEqual");
	writer.Bool(m_orEqual);

	writer.EndObject();
}

MR::TransitConditionDefInEventRange::TransitConditionDefInEventRange(uint32_t nTypeId) : TransitConditionDef(nTypeId)
{
	m_eventRangeStart = 0;
	m_eventRangeEnd = 0;
}

void MR::TransitConditionDefInEventRange::Locate()
{

}

void MR::TransitConditionDefInEventRange::SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject)
{
	writer.StartObject();

	TransitConditionDef::SerializeToJson(writer);

	writer.String("m_eventRangeStart");
	writer.Double(m_eventRangeStart);

	writer.String("m_eventRangeEnd");
	writer.Double(m_eventRangeEnd);

	writer.EndObject();
}

MR::TransitConditionDefPercentageThroughSubtransition::TransitConditionDefPercentageThroughSubtransition(uint32_t nTypeId) : TransitConditionDef(nTypeId)
{
	m_fPercentageThrough = 0;
	m_nSubStateID = 0;
	m_bUseTransitionSource = false;
	m_bLessThan = false;
}

void MR::TransitConditionDefPercentageThroughSubtransition::Locate()
{

}

void MR::TransitConditionDefPercentageThroughSubtransition::SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject)
{
	writer.StartObject();

	TransitConditionDef::SerializeToJson(writer);

	writer.String("m_fPercentageThrough");
	writer.Double(m_fPercentageThrough);

	writer.String("m_nSubStateID");
	writer.Uint(m_nSubStateID);

	writer.String("m_bUseTransitionSource");
	writer.Bool(m_bUseTransitionSource);

	writer.String("m_bLessThan");
	writer.Bool(m_bLessThan);

	writer.EndObject();
}

std::string MR::OperatorFloat::ConvertOperationTypeToString(OperationType operationType)
{
	switch (operationType)
	{
	case MR::OperatorFloat::OperationType::OPERATION_SIN:
		return "OPERATION_SIN";
	case MR::OperatorFloat::OperationType::OPERATION_COS:
		return "OPERATION_COS";
	case MR::OperatorFloat::OperationType::OPERATION_TAN:
		return "OPERATION_TAN";
	case MR::OperatorFloat::OperationType::OPERATION_EXP:
		return "OPERATION_EXP";
	case MR::OperatorFloat::OperationType::OPERATION_LOG:
		return "OPERATION_LOG";
	case MR::OperatorFloat::OperationType::OPERATION_SQRT:
		return "OPERATION_SQRT";
	case MR::OperatorFloat::OperationType::OPERATION_ABS:
		return "OPERATION_ABS";
	case MR::OperatorFloat::OperationType::OPERATION_RND:
		return "OPERATION_RND";
	case MR::OperatorFloat::OperationType::OPERATION_ROUND:
		return "OPERATION_ROUND";
	case MR::OperatorFloat::OperationType::OPERATION_NUMOPS:
		return "OPERATION_NUMOPS";
	case MR::OperatorFloat::OperationType::OPERATION_FORCEINTSIZE:
		return "OPERATION_FORCEINTSIZE";
	default:
		return "";
	}
}

std::string MR::Operator2Float::ConvertOperationTypeToString(OperationType operationType)
{
	switch (operationType)
	{
	case MR::Operator2Float::OPERATION_MULTIPLY:
		return "OPERATION_MULTIPLY";
	case MR::Operator2Float::OPERATION_ADD:
		return "OPERATION_ADD";
	case MR::Operator2Float::OPERATION_DIVIDE:
		return "OPERATION_DIVIDE";
	case MR::Operator2Float::OPERATION_SUBTRACT:
		return "OPERATION_SUBTRACT";
	case MR::Operator2Float::OPERATION_MIN:
		return "OPERATION_MIN";
	case MR::Operator2Float::OPERATION_MAX:
		return "OPERATION_MAX";
	case MR::Operator2Float::OPERATION_NUMOPS_0:
		return "OPERATION_NUMOPS_0";
	case MR::Operator2Float::OPERATION_FORCEINTSIZE_0:
		return "OPERATION_FORCEINTSIZE_0";
	default:
		return "";
	}
}

std::string MR::OperatorConst::ConvertOperationTypeToString(OperationType operationType)
{
	switch (operationType)
	{
	case MR::OperatorConst::OPERATION_MULTIPLY_0:
		return "OPERATION_MULTIPLY_0";
	case MR::OperatorConst::OPERATION_ADD_0:
		return "OPERATION_ADD_0";
	case MR::OperatorConst::OPERATION_DIVIDE_0:
		return "OPERATION_DIVIDE_0";
	case MR::OperatorConst::OPERATION_SUBTRACT_0:
		return "OPERATION_SUBTRACT_0";
	case MR::OperatorConst::OPERATION_NUMOPS_1:
		return "OPERATION_NUMOPS_1";
	case MR::OperatorConst::OPERATION_FORCEINTSIZE_1:
		return "OPERATION_FORCEINTSIZE_1";
	default:
		return "";
	}
}

MR::NodeDef::NodeDef(uint32_t typeID) : m_typeID(typeID), m_nodeID(-1), m_pName(nullptr), m_pParent(nullptr)
{
}

void MR::NodeDef::Locate()
{
	m_pName = Relocate(m_pName, this);

	if (m_pParent)
	{
		m_pParent = Relocate(m_pParent, this);
	}
}

uint32_t MR::NodeDef::GetTypeID() const
{
	return m_typeID;
}

void MR::NodeDef::SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject) const
{
	writer.String("m_typeID");
	writer.Uint(m_typeID);

	writer.String("m_nodeID");
	writer.Uint(m_nodeID);

	writer.String("m_pName");
	writer.String(m_pName);

	writer.String("m_pParent");

	if (m_pParent)
	{
		//m_pParent->SerializeToJson(writer);
		writer.String(m_pParent->m_pName);
	}
	else
	{
		writer.Null();
	}
}

MR::NodeDefControlParam::NodeDefControlParam(uint32_t typeID) : NodeDef(typeID)
{
}

MR::NodeDefControlParamFloat::NodeDefControlParamFloat(uint32_t typeID) : NodeDefControlParam(typeID)
{
	m_defaultVal = 0;
}

void MR::NodeDefControlParamFloat::SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject) const
{
	writer.StartObject();

	NodeDefControlParam::SerializeToJson(writer);

	writer.String("m_defaultVal");
	writer.Double(m_defaultVal);

	writer.EndObject();
}

MR::NodeDefControlParamVector3::NodeDefControlParamVector3(uint32_t typeID) : NodeDefControlParam(typeID)
{
}

void MR::NodeDefControlParamVector3::SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject) const
{
	writer.StartObject();

	NodeDefControlParam::SerializeToJson(writer);

	writer.String("m_defaultVal");
	m_defaultVal.SerializeToJson(writer);

	writer.EndObject();
}

MR::NodeDefControlParamVector4::NodeDefControlParamVector4(uint32_t typeID) : NodeDefControlParam(typeID)
{
}

void MR::NodeDefControlParamVector4::SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject) const
{
	writer.StartObject();

	NodeDefControlParam::SerializeToJson(writer);

	writer.String("m_defaultVal");
	m_defaultVal.SerializeToJson(writer);

	writer.EndObject();
}

MR::NodeDefOperatorFloat::NodeDefOperatorFloat(uint32_t typeID) : NodeDefControlParam(typeID)
{
}

void MR::NodeDefOperatorFloat::SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject) const
{
	writer.StartObject();

	NodeDefControlParam::SerializeToJson(writer);

	writer.String("m_input");
	writer.Uint(m_input);

	writer.String("m_operation");
	writer.String(OperatorFloat::ConvertOperationTypeToString(m_operation).c_str());

	writer.EndObject();
}

MR::NodeDefOperator2Float::NodeDefOperator2Float(uint32_t typeID) : NodeDefControlParam(typeID)
{
}

void MR::NodeDefOperator2Float::SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject) const
{
	writer.StartObject();

	NodeDefControlParam::SerializeToJson(writer);

	writer.String("m_input1");
	writer.Uint(m_input1);

	writer.String("m_input2");
	writer.Uint(m_input2);

	writer.String("m_operation");
	writer.String(Operator2Float::ConvertOperationTypeToString(m_operation).c_str());

	writer.EndObject();
}

MR::NodeDefOperatorConst::NodeDefOperatorConst(uint32_t typeID) : NodeDefControlParam(typeID)
{
}

void MR::NodeDefOperatorConst::SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject) const
{
	writer.StartObject();

	NodeDefControlParam::SerializeToJson(writer);

	writer.String("m_input");
	writer.Uint(m_input);

	writer.String("m_operation");
	writer.String(OperatorConst::ConvertOperationTypeToString(m_operation).c_str());

	writer.String("m_constValue");
	writer.Double(m_constValue);

	writer.EndObject();
}

MR::NodeDefOperatorNoiseGen::NodeDefOperatorNoiseGen(uint32_t typeID) : NodeDefControlParam(typeID)
{
}

void MR::NodeDefOperatorNoiseGen::Locate()
{
	NodeDef::Locate();

	auto base = static_cast<const void*>(this);

	m_table1 = Relocate(m_table1, base);
	m_table2 = Relocate(m_table2, base);
	m_table3 = Relocate(m_table3, base);
}

void MR::NodeDefOperatorNoiseGen::SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject) const
{
	writer.StartObject();

	NodeDefControlParam::SerializeToJson(writer);

	writer.String("m_input");
	writer.Uint(m_input);

	writer.String("m_frequency");
	writer.Double(m_frequency);

	writer.String("m_noiseFlags");
	writer.Uint(m_noiseFlags);

	writer.String("m_table1");
	writer.StartArray();

	for (uint32_t i = 0; i < 7; ++i)
	{
		writer.Double(m_table1[i]);
	}

	writer.EndArray();

	writer.String("m_table2");
	writer.StartArray();

	for (uint32_t i = 0; i < 19; ++i)
	{
		writer.Double(m_table2[i]);
	}

	writer.EndArray();

	writer.String("m_table3");
	writer.StartArray();

	for (uint32_t i = 0; i < 31; ++i)
	{
		writer.Double(m_table3[i]);
	}

	writer.EndArray();

	writer.EndObject();
}

MR::NodeDefPassThrough::NodeDefPassThrough(uint32_t typeID) : NodeDef(typeID)
{
}

void MR::NodeDefPassThrough::SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject) const
{
	NodeDef::SerializeToJson(writer);

	writer.String("m_nSourceNodeId");
	writer.Uint(m_nSourceNodeId);
}

void MR::StateChangeDef::Locate()
{
	m_conditionIndexes = Relocate(m_conditionIndexes, this);
}

void MR::StateChangeDef::SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject) const
{
	writer.StartObject();

	writer.String("m_destinationStateID");
	writer.Uint(m_destinationStateID);

	writer.String("m_numConditions");
	writer.Uint(m_numConditions);

	writer.String("m_conditionIndexes");
	writer.StartArray();

	for (uint32_t i = 0; i < m_numConditions; ++i)
	{
		writer.Uint(m_conditionIndexes[i]);
	}

	writer.EndArray();

	writer.EndObject();
}

void MR::StateDef::Locate()
{
	auto base = static_cast<const void*>(this);

	m_conditionIndexes = Relocate(m_conditionIndexes, base);
	m_stateChanges = Relocate(m_stateChanges, base);

	for (uint32_t i = 0; i < m_numStateChanges; ++i)
	{
		m_stateChanges[i].Locate();
	}
}

void MR::StateDef::SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject) const
{
	writer.StartObject();

	writer.String("m_nodeID");
	writer.Uint(m_nodeID);

	writer.String("m_numConditions");
	writer.Uint(m_numConditions);

	writer.String("m_conditionIndexes");
	writer.StartArray();

	for (uint32_t i = 0; i < m_numConditions; ++i)
	{
		writer.Uint(m_conditionIndexes[i]);
	}

	writer.EndArray();

	writer.String("m_numStateChanges");
	writer.Uint(m_numStateChanges);

	writer.String("m_stateChanges");
	writer.StartArray();

	for (uint32_t i = 0; i < m_numStateChanges; ++i)
	{
		m_stateChanges[i].SerializeToJson(writer);
	}

	writer.EndArray();

	writer.EndObject();
}

MR::NodeDefStateMachine::NodeDefStateMachine(uint32_t typeID) : NodeDefPassThrough(typeID)
{
}

void MR::NodeDefStateMachine::Locate()
{
	NodeDef::Locate();

	auto base = static_cast<const void*>(this);

	if (m_children)
	{
		m_children = Relocate(m_children, base);
	}

	for (uint32_t i = 0; i < m_numChildren; ++i)
	{
		m_children[i] = Relocate(m_children[i], base);
	}

	m_conditions = Relocate(m_conditions, base);

	for (uint32_t i = 0; i < m_numConditions; ++i)
	{
		m_conditions[i] = Relocate(m_conditions[i], base);
		Manager::GetInstance().Construct(m_conditions[i]);
		m_conditions[i]->Locate();
	}

	m_stateDefs = Relocate(m_stateDefs, base);

	for (uint32_t i = 0; i < m_numStates; ++i)
	{
		m_stateDefs[i].Locate();
	}
}

void MR::NodeDefStateMachine::SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject) const
{
	writer.StartObject();

	NodeDefPassThrough::SerializeToJson(writer);

	writer.String("m_numStates");
	writer.Uint(m_numStates);

	writer.String("m_stateDefs");
	writer.StartArray();

	for (uint32_t i = 0; i < m_numStates; ++i)
	{
		m_stateDefs[i].SerializeToJson(writer);
	}

	writer.EndArray();

	writer.String("m_numConditions");
	writer.Uint(m_numConditions);

	writer.String("m_conditions");
	writer.StartArray();

	for (uint32_t i = 0; i < m_numConditions; ++i)
	{
		m_conditions[i]->SerializeToJson(writer);
	}

	writer.EndArray();

	writer.String("m_numChildren");
	writer.Uint(m_numChildren);

	writer.String("m_children");
	writer.StartArray();

	for (uint32_t i = 0; i < m_numChildren; ++i)
	{
		m_children[i]->SerializeToJson(writer);
	}

	writer.EndArray();

	writer.EndObject();
}

MR::NodeDefAnim::NodeDefAnim(uint32_t typeID) : NodeDef(typeID)
{
}

void MR::NodeDefAnim::SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject) const
{
	if (startObject)
	{
		writer.StartObject();
	}

	NodeDef::SerializeToJson(writer);

	writer.String("m_generateDeltas");
	writer.Bool(m_generateDeltas);

	writer.String("m_loop");
	writer.Bool(m_loop);

	writer.String("m_playBackwards");
	writer.Bool(m_playBackwards);

	writer.String("m_clipStartFraction");
	writer.Double(m_clipStartFraction);

	writer.String("m_clipEndFraction");
	writer.Double(m_clipEndFraction);

	writer.String("m_animSource");
	writer.String(mrtnReferences[reinterpret_cast<size_t>(m_animSource)].c_str());

	if (startObject)
	{
		writer.EndObject();
	}
}

MR::NodeDefAnimWithEvents::NodeDefAnimWithEvents(uint32_t typeID) : NodeDefAnim(typeID)
{
}

void MR::NodeDefAnimWithEvents::SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject) const
{
	if (startObject)
	{
		writer.StartObject();
	}

	NodeDefAnim::SerializeToJson(writer, false);

	writer.String("m_startEventIndex");
	writer.Int(m_startEventIndex);

	if (startObject)
	{
		writer.EndObject();
	}
}

MR::NodeDefBlendBase::NodeDefBlendBase(uint32_t typeID) : NodeDef(typeID)
{
}

void MR::NodeDefBlendBase::SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject) const
{
	//writer.StartObject();

	NodeDef::SerializeToJson(writer);

	writer.String("m_aID");
	writer.Uint(m_aID);

	writer.String("m_bID");
	writer.Uint(m_bID);

	writer.String("m_UseSource1Additively");
	writer.Bool(m_UseSource1Additively);

	writer.String("m_Source0IsFullBody");
	writer.Bool(m_Source0IsFullBody);

	//writer.EndObject();
}

MR::NodeDefBlend2::NodeDefBlend2(uint32_t typeID) : NodeDefBlendBase(typeID)
{
}

void MR::NodeDefBlend2::SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject) const
{
	if (startObject)
	{
		writer.StartObject();
	}

	NodeDefBlendBase::SerializeToJson(writer);

	writer.String("m_weightNodeID");
	writer.Uint(m_weightNodeID);

	writer.String("m_loop");
	writer.Bool(m_loop);

	writer.String("m_additiveBlendAtt");
	writer.Bool(m_additiveBlendAtt);

	writer.String("m_additiveBlendPos");
	writer.Bool(m_additiveBlendPos);

	writer.String("m_slerpDeltaTrajTrans");
	writer.Bool(m_slerpDeltaTrajTrans);

	writer.String("m_source0BranchOptimization");
	writer.Bool(m_source0BranchOptimization);

	writer.String("m_source1BranchOptimization");
	writer.Bool(m_source1BranchOptimization);

	writer.String("m_ignoreSource0EventWeight");
	writer.Bool(m_ignoreSource0EventWeight);

	writer.String("m_ignoreSource1EventWeight");
	writer.Bool(m_ignoreSource1EventWeight);

	writer.String("m_bUpdateWeigthingOnce");
	writer.Bool(m_bUpdateWeigthingOnce);

	if (startObject)
	{
		writer.EndObject();
	}
}

MR::NodeDefBlendN::NodeDefBlendN(uint32_t typeID) : NodeDefBlend2(typeID)
{
}

void MR::NodeDefBlendN::SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject) const
{
	writer.StartObject();

	NodeDefBlend2::SerializeToJson(writer, false);

	writer.String("m_numSourceNodes");
	writer.Uint(m_numSourceNodes);

	writer.String("m_connectedSourceNode");
	m_connectedSourceNode[0].SerializeToJson(writer);

	writer.EndObject();
}

void MR::NodeDefBlendN::ConnectionDef::SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject) const
{
	writer.StartObject();

	writer.String("connectedNodeId");
	writer.Uint(connectedNodeId);

	writer.String("weight");
	writer.Double(weight);

	writer.EndObject();
}

MR::NodeDefBlend2MatchEvents::NodeDefBlend2MatchEvents(uint32_t typeID) : NodeDefBlend2(typeID)
{
}

void MR::NodeDefBlend2MatchEvents::SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject) const
{
	if (startObject)
	{
		writer.StartObject();
	}

	NodeDefBlend2::SerializeToJson(writer, false);

	writer.String("m_eventWeightNodeID");
	writer.Uint(m_eventWeightNodeID);

	writer.String("m_startEventIndex");
	writer.Int(m_startEventIndex);

	writer.String("m_durationEventMatchingType");
	writer.Uint(m_durationEventMatchingType);

	if (startObject)
	{
		writer.EndObject();
	}
}

MR::NodeDefBlendNMatchEvents::NodeDefBlendNMatchEvents(uint32_t typeID) : NodeDefBlend2MatchEvents(typeID)
{
}

void MR::NodeDefBlendNMatchEvents::SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject) const
{
	writer.StartObject();

	NodeDefBlend2MatchEvents::SerializeToJson(writer, false);

	writer.String("m_numSourceNodes");
	writer.Uint(m_numSourceNodes);

	writer.String("m_connectedSourceNode");
	m_connectedSourceNode[0].SerializeToJson(writer);

	writer.EndObject();
}

void MR::NodeDefBlendNMatchEvents::ConnectionDef::SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject) const
{
	writer.StartObject();

	writer.String("connectedNodeId");
	writer.Uint(connectedNodeId);

	writer.String("weight");
	writer.Double(weight);

	writer.EndObject();
}

MR::NodeDefPassThroughTransforms::NodeDefPassThroughTransforms(uint32_t typeID) : NodeDefPassThrough(typeID)
{
}

MR::NodeDefFilterTransforms::NodeDefFilterTransforms(uint32_t typeID) : NodeDefPassThroughTransforms(typeID)
{
}

void MR::NodeDefFilterTransforms::Locate()
{
	NodeDef::Locate();

	m_boneFilterIDs = Relocate(m_boneFilterIDs, this);
}

void MR::NodeDefFilterTransforms::SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject) const
{
	writer.StartObject();

	NodeDefPassThroughTransforms::SerializeToJson(writer);

	writer.String("m_numBoneFilterIDs");
	writer.Uint(m_numBoneFilterIDs);

	writer.String("m_boneFilterIDs");
	writer.StartArray();

	for (uint32_t i = 0; i < m_numBoneFilterIDs; ++i)
	{
		writer.Uint(m_boneFilterIDs[i]);
	}

	writer.EndArray();

	writer.EndObject();
}

MR::NodeDefSingleFrame::NodeDefSingleFrame(uint32_t typeID) : NodeDefPassThroughTransforms(typeID)
{
}

void MR::NodeDefSingleFrame::SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject) const
{
	writer.StartObject();

	NodeDefPassThroughTransforms::SerializeToJson(writer);

	writer.String("m_controlNodeID");
	writer.Uint(m_controlNodeID);

	writer.String("m_bUseTrajectory");
	writer.Bool(m_bUseTrajectory);

	writer.EndObject();
}

MR::NodeDefComputeWorldTransforms::NodeDefComputeWorldTransforms(uint32_t typeID) : NodeDefPassThroughTransforms(typeID)
{
}

void MR::NodeRef::SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject) const
{
	writer.StartObject();

	writer.String("m_nodeId");
	writer.Uint(m_nodeId);

	writer.EndObject();
}

MR::NodeDefFeatherBlend2::NodeDefFeatherBlend2(uint32_t typeID) : NodeDef(typeID)
{
}

void MR::NodeDefFeatherBlend2::SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject) const
{
	writer.StartObject();

	NodeDef::SerializeToJson(writer);

	writer.String("m_aID");
	m_aID.SerializeToJson(writer);

	writer.String("m_bID");
	m_bID.SerializeToJson(writer);

	writer.String("m_weightNodeID");
	m_weightNodeID.SerializeToJson(writer);

	writer.String("m_numBoneWeights");
	writer.Uint(m_numBoneWeights);

	writer.String("m_boneWeights");
	writer.StartArray();

	for (uint32_t i = 0; i < m_numBoneWeights; ++i)
	{
		writer.Double(m_boneWeights[i]);
	}

	writer.EndArray();

	writer.String("m_loop");
	writer.Bool(m_loop);

	writer.String("m_additiveBlendAtt");
	writer.Bool(m_additiveBlendAtt);

	writer.String("m_additiveBlendPos");
	writer.Bool(m_additiveBlendPos);

	writer.String("m_slerpDeltaTrajTrans");
	writer.Bool(m_slerpDeltaTrajTrans);

	writer.EndObject();
}

void MR::NodeDefFeatherBlend2::Locate()
{
	NodeDef::Locate();

	m_boneWeights = Relocate(m_boneWeights, this);
}

void MR::BoneId::SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject) const
{
	writer.StartObject();

	writer.String("m_boneId");
	writer.Uint(m_boneId);

	writer.EndObject();
}

MR::NodeDefLockFoot::NodeDefLockFoot(uint32_t typeID) : NodeDefPassThroughTransforms(typeID)
{
}

void MR::NodeDefLockFoot::SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject) const
{
	writer.StartObject();

	NodeDefPassThroughTransforms::SerializeToJson(writer);

	writer.String("m_catchupSpeedFactor");
	writer.Double(m_catchupSpeedFactor);

	writer.String("m_snapToSourceDistance");
	writer.Double(m_snapToSourceDistance);

	writer.String("m_straightestLegFactor");
	writer.Double(m_straightestLegFactor);

	writer.String("m_footfallEventID");
	writer.Int(m_footfallEventID);

	writer.String("m_lowerHeightBound");
	writer.Double(m_lowerHeightBound);

	writer.String("m_toeLowerHeightBound");
	writer.Double(m_toeLowerHeightBound);

	writer.String("m_kneeRotationAxis");
	m_kneeRotationAxis.SerializeToJson(writer);

	writer.String("m_ballRotationAxis");
	m_ballRotationAxis.SerializeToJson(writer);

	writer.String("m_upAxis");
	m_upAxis.SerializeToJson(writer);

	writer.String("m_IkFkBlendWeightNodeID");
	m_IkFkBlendWeightNodeID.SerializeToJson(writer);

	writer.String("m_swivelContributionToOrientationNodeID");
	m_swivelContributionToOrientationNodeID.SerializeToJson(writer);

	writer.String("m_pad");
	writer.Uint(m_pad);

	writer.String("m_hipIndex");
	m_hipIndex.SerializeToJson(writer);

	writer.String("m_kneeIndex");
	m_kneeIndex.SerializeToJson(writer);

	writer.String("m_ankleIndex");
	m_ankleIndex.SerializeToJson(writer);

	writer.String("m_ballIndex");
	m_ballIndex.SerializeToJson(writer);

	writer.String("m_toeIndex");
	m_toeIndex.SerializeToJson(writer);

	writer.String("m_fixGroundPenetration");
	writer.Bool(m_fixGroundPenetration);

	writer.String("m_flipKneeRotationDirection");
	writer.Bool(m_flipKneeRotationDirection);

	writer.String("m_useBallJoint");
	writer.Bool(m_useBallJoint);

	writer.String("m_assumeSimpleHierarchy");
	writer.Bool(m_assumeSimpleHierarchy);

	writer.String("m_fixToeGroundPenetration");
	writer.Bool(m_fixToeGroundPenetration);

	writer.String("m_valid");
	writer.Bool(m_valid);

	writer.EndObject();
}

MR::NodeDefTwoBoneIK::NodeDefTwoBoneIK(uint32_t typeID) : NodeDefPassThroughTransforms(typeID)
{
}

void MR::NodeDefTwoBoneIK::SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject) const
{
	writer.StartObject();

	NodeDefPassThroughTransforms::SerializeToJson(writer);

	writer.String("m_endJointIndex");
	m_endJointIndex.SerializeToJson(writer);

	writer.String("m_midJointIndex");
	m_midJointIndex.SerializeToJson(writer);

	writer.String("m_rootJointIndex");
	m_rootJointIndex.SerializeToJson(writer);

	writer.String("m_referenceJointIndex");
	m_referenceJointIndex.SerializeToJson(writer);

	writer.String("m_effectorTargetNodeID");
	m_effectorTargetNodeID.SerializeToJson(writer);

	writer.String("m_targetOrientationNodeID");
	m_targetOrientationNodeID.SerializeToJson(writer);

	writer.String("m_swivelAngleNodeID");
	m_swivelAngleNodeID.SerializeToJson(writer);

	writer.String("m_IkFkBlendWeightNodeID");
	m_IkFkBlendWeightNodeID.SerializeToJson(writer);

	writer.String("m_swivelContributionToOrientationNodeID");
	m_swivelContributionToOrientationNodeID.SerializeToJson(writer);

	writer.String("m_midJointRotationAxisX");
	writer.Double(m_midJointRotationAxisX);

	writer.String("m_midJointRotationAxisY");
	writer.Double(m_midJointRotationAxisY);

	writer.String("m_midJointRotationAxisZ");
	writer.Double(m_midJointRotationAxisZ);

	writer.String("m_flipMidJointRotationDirection");
	writer.Bool(m_flipMidJointRotationDirection);

	writer.String("m_assumeSimpleHierarchy");
	writer.Bool(m_assumeSimpleHierarchy);

	writer.String("m_keepEndEffOrientation");
	writer.Bool(m_keepEndEffOrientation);

	writer.String("m_endEffOrientationFromReferenceJoint");
	writer.Bool(m_endEffOrientationFromReferenceJoint);

	writer.String("m_globalReferenceAxis");
	writer.Bool(m_globalReferenceAxis);

	writer.String("m_updateTargetByDeltas");
	writer.Bool(m_updateTargetByDeltas);

	writer.String("m_midJointReferenceAxisX");
	writer.Double(m_midJointReferenceAxisX);

	writer.String("m_midJointReferenceAxisY");
	writer.Double(m_midJointReferenceAxisY);

	writer.String("m_midJointReferenceAxisZ");
	writer.Double(m_midJointReferenceAxisZ);

	writer.EndObject();
}

MR::NodeDefHeadLook::NodeDefHeadLook(uint32_t typeID) : NodeDefPassThroughTransforms(typeID)
{
}

void MR::NodeDefHeadLook::SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject) const
{
	writer.StartObject();

	NodeDefPassThroughTransforms::SerializeToJson(writer);

	writer.String("m_endJointIndex");
	m_endJointIndex.SerializeToJson(writer);

	writer.String("m_rootJointIndex");
	m_rootJointIndex.SerializeToJson(writer);

	writer.String("m_pointingJointIndex");
	m_pointingJointIndex.SerializeToJson(writer);

	writer.String("m_targetNodeID");
	m_targetNodeID.SerializeToJson(writer);

	writer.String("m_pointingJointAxisNodeID");
	m_pointingJointAxisNodeID.SerializeToJson(writer);

	writer.String("m_pointingJointIDNodeID");
	m_pointingJointIDNodeID.SerializeToJson(writer);

	writer.String("m_blendWeightNodeID");
	m_blendWeightNodeID.SerializeToJson(writer);

	writer.String("m_pointingJointAxisX");
	writer.Double(m_pointingJointAxisX);

	writer.String("m_pointingJointAxisY");
	writer.Double(m_pointingJointAxisY);

	writer.String("m_pointingJointAxisZ");
	writer.Double(m_pointingJointAxisZ);

	writer.String("m_bias");
	writer.Bool(m_bias);

	writer.String("m_updateTargetByDeltas");
	writer.Bool(m_updateTargetByDeltas);

	writer.String("m_pointingVectorInCS");
	writer.Bool(m_pointingVectorInCS);

	writer.EndObject();
}

MR::NodeDefApplyBindPose::NodeDefApplyBindPose(uint32_t typeID) : NodeDefPassThroughTransforms(typeID)
{
}

MR::NodeDefTransit::NodeDefTransit(uint32_t typeID) : NodeDefBlendBase(typeID)
{
}

void MR::NodeDefTransit::SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject) const
{
	if (startObject)
	{
		writer.StartObject();
	}

	NodeDefBlendBase::SerializeToJson(writer);

	writer.String("m_transitionDuration");
	writer.Double(m_transitionDuration);

	writer.String("m_bIgnoreSourceTrajectory");
	writer.Bool(m_bIgnoreSourceTrajectory);

	writer.String("m_bEnableRealign");
	writer.Bool(m_bEnableRealign);

	writer.String("m_bSnapBlending");
	writer.Bool(m_bSnapBlending);

	if (startObject)
	{
		writer.EndObject();
	}
}

MR::NodeDefTransitAtEvent::NodeDefTransitAtEvent(uint32_t typeID) : NodeDefTransit(typeID)
{
}

void MR::NodeDefTransitAtEvent::SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject) const
{
	writer.StartObject();

	NodeDefTransit::SerializeToJson(writer, false);

	writer.String("m_destStartEventIndex");
	writer.Uint(m_destStartEventIndex);

	writer.String("m_startFromSetFractionOfDestEvent");
	writer.Bool(m_startFromSetFractionOfDestEvent);

	writer.String("m_destStartEventFraction");
	writer.Double(m_destStartEventFraction);

	writer.EndObject();
}

MR::NodeDefTransitMatchEvents::NodeDefTransitMatchEvents(uint32_t typeID) : NodeDefTransit(typeID)
{
}

void MR::NodeDefTransitMatchEvents::SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject) const
{
	writer.StartObject();

	NodeDefTransit::SerializeToJson(writer, false);

	writer.String("m_destEventSequenceOffset");
	writer.Uint(m_destEventSequenceOffset);

	writer.String("m_destStartEventIndex");
	writer.Uint(m_destStartEventIndex);

	writer.String("m_usingDestStartEventIndex");
	writer.Bool(m_usingDestStartEventIndex);

	writer.String("m_durationEventMatchingType");
	writer.Uint(m_durationEventMatchingType);

	writer.EndObject();
}

MR::NodeDefBlendTree::NodeDefBlendTree(uint32_t typeID) : NodeDef(typeID)
{
}

void MR::NodeDefBlendTree::Locate()
{
	NodeDef::Locate();
	auto base = static_cast<const void*>(this);

	m_children = Relocate(m_children, base);

	for (uint32_t i = 0; i < m_nNumChildren; ++i)
	{
		m_children[i] = Relocate(m_children[i], base);
	}
}

void MR::NodeDefBlendTree::SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject) const
{
	writer.StartObject();

	NodeDef::SerializeToJson(writer);

	writer.String("m_nNumChildren");
	writer.Uint(m_nNumChildren);

	writer.String("m_children");
	writer.StartArray();

	for (uint32_t i = 0; i < m_nNumChildren; ++i)
	{
		m_children[i]->SerializeToJson(writer);
	}

	writer.EndArray();

	writer.String("m_nRootNodeId");
	writer.Uint(m_nRootNodeId);

	writer.EndObject();
}

void MR::TransformBuffersCount::SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject)
{
	writer.StartObject();

	writer.String("m_numTranformBufferTypesUsed");
	writer.Uint(m_numTranformBufferTypesUsed);

	writer.String("m_transformBufferTypes");
	writer.StartArray();

	for (uint32_t i = 0; i < 8; ++i)
	{
		writer.Uint(m_transformBufferTypes[i]);
	}

	writer.EndArray();

	writer.String("m_transformBufferCounts");
	writer.StartArray();

	for (uint32_t i = 0; i < 8; ++i)
	{
		writer.Uint(m_transformBufferCounts[i]);
	}

	writer.EndArray();

	writer.EndObject();
}

void MR::NetworkDef::Locate()
{
	auto base = static_cast<const void*>(this);

	m_nodeDefs = Relocate(m_nodeDefs, base);
	m_persistentNodeIDs = Relocate(m_persistentNodeIDs, base);

	if (m_numNodeStateMachines)
	{
		m_nodeStateMachineNodeIDs = Relocate(m_nodeStateMachineNodeIDs, base);
	}

	if (m_numInterfaceControlParameters)
	{
		m_interfaceControlParameterNodeIDs = Relocate(m_interfaceControlParameterNodeIDs, base);
	}

	if (m_requestIDStringTable)
	{
		m_requestIDStringTable = Relocate(m_requestIDStringTable, base);
		m_requestIDStringTable->Locate();
	}

	for (uint32_t i = 0; i < m_numNodeDefs + m_numDummyBlendTreeDefs; ++i)
	{
		m_nodeDefs[i] = Relocate(m_nodeDefs[i], base);
		Manager::GetInstance().Construct(m_nodeDefs[i]);
		m_nodeDefs[i]->Locate();
	}

	m_nodeNames = Relocate(m_nodeNames, base);
}

std::string MR::NetworkDef::SerializeToJson()
{
	rapidjson::StringBuffer stringBuffer;
	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(stringBuffer);

	writer.StartObject();

	writer.String("m_numAnimations");
	writer.Uint(m_numAnimations);

	writer.String("m_animLibrary");
	writer.Null();
	/*writer.StartArray();

	for (uint32_t i = 0; i < mrtnReferences.size(); ++i)
	{
		writer.String(mrtnReferences[i].c_str());
	}

	writer.EndArray();*/

	writer.String("m_rig");
	writer.String(mrtnReferences[mrtnReferences.size() - 1].c_str());

	writer.String("m_numNodeNames");
	writer.Uint(m_numNodeNames);

	writer.String("m_nodeNames");
	writer.StartArray();

	uint32_t length = 0;

	for (uint32_t i = 0; i < m_numNodeNames; ++i)
	{
		const char* nodeName = m_nodeNames + length;

		writer.String(nodeName);

		length += static_cast<uint32_t>(strlen(nodeName)) + 1;
	}

	writer.EndArray();

	writer.String("m_numNodeDefs");
	writer.Uint(m_numNodeDefs);

	writer.String("m_numDummyBlendTreeDefs");
	writer.Uint(m_numDummyBlendTreeDefs);

	writer.String("m_nodeDefs");
	writer.StartArray();

	for (uint32_t i = 0; i < m_numNodeDefs + m_numDummyBlendTreeDefs; ++i)
	{
		m_nodeDefs[i]->SerializeToJson(writer);
	}

	writer.EndArray();

	writer.String("m_maxDurationEventsPoolSize");
	writer.Uint(m_maxDurationEventsPoolSize);

	writer.String("m_rootNodeID");
	writer.Uint(m_rootNodeID);

	writer.String("m_numNodeStateMachines");
	writer.Uint(m_numNodeStateMachines);

	writer.String("m_nodeStateMachineNodeIDs");
	writer.StartArray();

	for (uint32_t i = 0; i < m_numNodeStateMachines; ++i)
	{
		writer.Uint(m_nodeStateMachineNodeIDs[i]);
	}

	writer.EndArray();

	writer.String("m_numInterfaceControlParameters");
	writer.Uint(m_numInterfaceControlParameters);

	writer.String("m_interfaceControlParameterNodeIDs");
	writer.StartArray();

	for (uint32_t i = 0; i < m_numInterfaceControlParameters; ++i)
	{
		writer.Uint(m_interfaceControlParameterNodeIDs[i]);
	}

	writer.EndArray();

	writer.String("m_numPersistentNodes");
	writer.Uint(m_numPersistentNodes);

	writer.String("m_persistentNodeIDs");
	writer.StartArray();

	for (uint32_t i = 0; i < m_numPersistentNodes; ++i)
	{
		writer.Uint(m_persistentNodeIDs[i]);
	}

	writer.EndArray();

	writer.String("m_networkHash");

	std::stringstream stringstream;

	stringstream << "0x" << std::hex << std::uppercase;

	for (uint32_t i = 0; i < 16; ++i)
	{
		stringstream << static_cast<int>(m_networkHash.b[i]);
	}

	writer.String(stringstream.str().c_str());

	writer.String("m_requestIDStringTable");
	m_requestIDStringTable->SerializeToJson(writer);

	writer.String("m_maxTransformBufferReqs");
	m_maxTransformBufferReqs.SerializeToJson(writer);

	writer.EndObject();

	return stringBuffer.GetString();
}

MRSamples::NodeDefPlaySpeedModifier::NodeDefPlaySpeedModifier(uint32_t typeID) : MR::NodeDefPassThrough(typeID)
{
}

void MRSamples::NodeDefPlaySpeedModifier::SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject) const
{
	writer.StartObject();

	MR::NodeDefPassThrough::SerializeToJson(writer);

	writer.String("m_playSpeedFactorID");
	writer.Uint(m_playSpeedFactorID);

	writer.EndObject();
}

NodeDefModifyBoneAlpha::NodeDefModifyBoneAlpha(uint32_t typeID) : MR::NodeDefPassThroughTransforms(typeID)
{
}

void NodeDefModifyBoneAlpha::Locate()
{
	MR::NodeDef::Locate();

	m_boneAlphas = Relocate(m_boneAlphas, this);
}

void NodeDefModifyBoneAlpha::SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject) const
{
	writer.StartObject();

	MR::NodeDefPassThroughTransforms::SerializeToJson(writer);

	writer.String("m_nWeightNodeID");
	writer.Uint(m_nWeightNodeID);

	writer.String("m_numBones");
	writer.Uint(m_numBones);

	writer.String("m_boneAlphas");
	writer.StartArray();

	for (uint32_t i = 0; i < m_numBones; ++i)
	{
		writer.Double(m_boneAlphas[i]);
	}

	writer.EndArray();

	writer.EndObject();
}

NodeDefApplyBoneMask::NodeDefApplyBoneMask(uint32_t typeID) : MR::NodeDefPassThroughTransforms(typeID)
{
}

void NodeDefApplyBoneMask::SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject) const
{
	writer.StartObject();

	MR::NodeDefPassThroughTransforms::SerializeToJson(writer);

	writer.String("unk");
	writer.StartArray();

	for (uint32_t i = 0; i < 16; ++i)
	{
		writer.Uint(unk[i]);
	}

	writer.EndArray();

	writer.EndObject();
}

ZNodeDefAnimIOI::ZNodeDefAnimIOI(uint32_t typeID) : NodeDefAnimWithEvents(typeID)
{
}

ZNodeDefAnimIOICutSequence::ZNodeDefAnimIOICutSequence(uint32_t typeID) : MR::NodeDef(typeID)
{
}

void ZNodeDefAnimIOICutSequence::Locate()
{
	MR::NodeDef::Locate();

	m_pszSlotName = Relocate(m_pszSlotName, this);
}

void ZNodeDefAnimIOICutSequence::SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject) const
{
	writer.StartObject();

	MR::NodeDef::SerializeToJson(writer);

	writer.String("m_pszSlotName");
	writer.String(m_pszSlotName);

	writer.EndObject();
}

ZNodeDefVariationIOI::ZNodeDefVariationIOI(uint32_t typeID) : ZNodeDefAnimIOI(typeID)
{
}

void ZNodeDefVariationIOI::Locate()
{
	MR::NodeDefAnimWithEvents::Locate();

	m_pszVariationName = Relocate(m_pszVariationName, this);
}

void ZNodeDefVariationIOI::SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject) const
{
	writer.StartObject();

	ZNodeDefAnimIOI::SerializeToJson(writer, false);

	writer.String("m_pszVariationName");
	writer.String(m_pszVariationName);

	writer.String("m_bBlendFromLastFrame");
	writer.Bool(m_bBlendFromLastFrame);

	writer.EndObject();
}

ZNodeDefChildNetworkIOI::ZNodeDefChildNetworkIOI(uint32_t typeID) : MR::NodeDef(typeID)
{
}

ZNodeDefSelectiveFeatherBlend::ZNodeDefSelectiveFeatherBlend(uint32_t typeID) : MR::NodeDefBlend2(typeID)
{
}

void ZNodeDefSelectiveFeatherBlend::Locate()
{
	MR::NodeDefBlend2::Locate();

	m_paBoneWeights = Relocate(m_paBoneWeights, this);
}

void ZNodeDefSelectiveFeatherBlend::SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject) const
{
	writer.StartObject();

	MR::NodeDefBlend2::SerializeToJson(writer, false);

	writer.String("m_featherWeightNodeID");
	writer.Uint(m_featherWeightNodeID);

	writer.String("m_ignoreTrajectory0NodeID");
	writer.Uint(m_ignoreTrajectory0NodeID);

	writer.String("m_ignoreTrajectory1NodeID");
	writer.Uint(m_ignoreTrajectory1NodeID);

	writer.String("m_numBoneWeights");
	writer.Uint(m_numBoneWeights);

	writer.String("m_paBoneWeights");
	writer.StartArray();

	for (uint32_t i = 0; i < m_numBoneWeights; ++i)
	{
		writer.Double(m_paBoneWeights[i]);
	}

	writer.EndArray();

	writer.EndObject();
}

NodeDefBlend2ForwardEvents::NodeDefBlend2ForwardEvents(uint32_t typeID) : MR::NodeDefBlend2(typeID)
{
}

void NodeDefBlend2ForwardEvents::SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject) const
{
	if (startObject)
	{
		writer.StartObject();
	}

	MR::NodeDefBlend2::SerializeToJson(writer, false);

	writer.String("m_bUseGlobalDeltaTime");
	writer.Bool(m_bUseGlobalDeltaTime);

	if (startObject)
	{
		writer.EndObject();
	}
}

ZNodeDefSelectiveFeatherBlendForwardEvents::ZNodeDefSelectiveFeatherBlendForwardEvents(uint32_t typeID) : NodeDefBlend2ForwardEvents(typeID)
{
}

void ZNodeDefSelectiveFeatherBlendForwardEvents::Locate()
{
	MR::NodeDefBlend2::Locate();

	m_paBoneWeights = Relocate(m_paBoneWeights, this);
}

void ZNodeDefSelectiveFeatherBlendForwardEvents::SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject) const
{
	writer.StartObject();

	NodeDefBlend2ForwardEvents::SerializeToJson(writer, false);

	writer.String("m_featherWeightNodeID");
	writer.Uint(m_featherWeightNodeID);

	writer.String("m_numBoneWeights");
	writer.Uint(m_numBoneWeights);

	writer.String("m_paBoneWeights");
	writer.StartArray();

	for (uint32_t i = 0; i < m_numBoneWeights; ++i)
	{
		writer.Double(m_paBoneWeights[i]);
	}

	writer.EndArray();

	writer.EndObject();
}

ZNodeDefGroundRotation::ZNodeDefGroundRotation(uint32_t typeID) : MR::NodeDefPassThrough(typeID)
{
}

void ZNodeDefGroundRotation::SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject) const
{
	writer.StartObject();

	MR::NodeDefPassThrough::SerializeToJson(writer);

	writer.String("m_nAngleNodeId");
	writer.Uint(m_nAngleNodeId);

	writer.String("m_nTrajectoryNodeID");
	writer.Uint(m_nTrajectoryNodeID);

	writer.String("m_nTranslationThresholdNodeID");
	writer.Uint(m_nTranslationThresholdNodeID);

	writer.String("m_nAttitudeThresholdNodeID");
	writer.Uint(m_nAttitudeThresholdNodeID);

	writer.String("m_bOverrideTrajectory");
	writer.Bool(m_bOverrideTrajectory);

	writer.String("m_bCorrectiveTranslationModification");
	writer.Bool(m_bCorrectiveTranslationModification);

	writer.String("m_bCorrectiveAttitudeModification");
	writer.Bool(m_bCorrectiveAttitudeModification);

	writer.String("m_bRotateTrajectory");
	writer.Bool(m_bRotateTrajectory);

	writer.String("m_bRotateTrajectoryToEndPosition");
	writer.Bool(m_bRotateTrajectoryToEndPosition);

	writer.String("m_bApplyAsDeltaValue");
	writer.Bool(m_bApplyAsDeltaValue);

	writer.String("m_bMirrorTrajectory");
	writer.Bool(m_bMirrorTrajectory);

	writer.String("m_nCorrectionStartEventID");
	writer.Uint(m_nCorrectionStartEventID);

	writer.String("m_nCorrectionEndEventID");
	writer.Uint(m_nCorrectionEndEventID);

	writer.EndObject();
}

ZNodeDefScaleAnim::ZNodeDefScaleAnim(uint32_t typeID) : MR::NodeDefPassThroughTransforms(typeID)
{
}

void ZNodeDefScaleAnim::SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject) const
{
	writer.StartObject();

	MR::NodeDefPassThroughTransforms::SerializeToJson(writer);

	writer.String("m_nBoneScaleNodeId");
	writer.Uint(m_nBoneScaleNodeId);

	writer.String("m_nTrajectoryTranslationScaleNodeID");
	writer.Uint(m_nTrajectoryTranslationScaleNodeID);

	writer.String("m_nTrajectoryOrientationScaleNodeID");
	writer.Uint(m_nTrajectoryOrientationScaleNodeID);

	writer.String("m_nTimeScaleNodeId");
	writer.Uint(m_nTimeScaleNodeId);

	writer.String("m_nReferenceNodeId");
	m_nReferenceNodeId.SerializeToJson(writer);

	writer.EndObject();
}

void SNodeLookAtIDs::SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject) const
{
	writer.StartObject();

	writer.String("m_directionNodeID");
	writer.Uint(m_directionNodeID);

	writer.String("m_weightNodeID");
	writer.Uint(m_weightNodeID);

	writer.String("m_iHeadBoneIndex");
	writer.Uint(m_iHeadBoneIndex);

	writer.EndObject();
}

ZIOINodeLookAtDef::ZIOINodeLookAtDef(uint32_t typeID) : MR::NodeDefPassThroughTransforms(typeID)
{
}

void ZIOINodeLookAtDef::SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject) const
{
	writer.StartObject();

	MR::NodeDefPassThroughTransforms::SerializeToJson(writer);

	writer.String("m_NodeIDs");
	m_NodeIDs.SerializeToJson(writer);

	writer.EndObject();
}

void SNodeSelectIDs_V2::SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject) const
{
	writer.StartObject();

	writer.String("m_sourceNodeIDs");
	writer.StartArray();

	for (uint32_t i = 0; i < 35; ++i)
	{
		writer.Uint(m_sourceNodeIDs[i]);
	}

	writer.EndArray();

	writer.String("m_selectCtrlID");
	writer.Uint(m_selectCtrlID);

	writer.String("m_blendCtrlID");
	writer.Uint(m_blendCtrlID);

	writer.EndObject();
}

ZIOINodeSelectDef::ZIOINodeSelectDef(uint32_t typeID) : MR::NodeDef(typeID)
{
}

void ZIOINodeSelectDef::SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject) const
{
	writer.StartObject();

	MR::NodeDef::SerializeToJson(writer);

	writer.String("m_NodeIDs");
	m_NodeIDs.SerializeToJson(writer);

	writer.String("m_bRandomSelectAtInit");
	writer.Bool(m_bRandomSelectAtInit);

	writer.String("m_bUpdateSelectIndex");
	writer.Bool(m_bUpdateSelectIndex);

	writer.EndObject();
}

ZIOINodeSelectMatrixDef::ZIOINodeSelectMatrixDef(uint32_t typeID) : MR::NodeDef(typeID)
{
}

void ZIOINodeSelectMatrixDef::SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject) const
{
	writer.StartObject();

	MR::NodeDef::SerializeToJson(writer);

	writer.String("unk");
	writer.StartArray();

	for (uint32_t i = 0; i < 152; ++i)
	{
		writer.Uint(unk[i]);
	}

	writer.EndArray();

	writer.EndObject();
}

ZIOINodeSelectSnapBlendDef::ZIOINodeSelectSnapBlendDef(uint32_t typeID) : MR::NodeDef(typeID)
{
}

void ZIOINodeSelectSnapBlendDef::SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject) const
{
	writer.StartObject();

	MR::NodeDef::SerializeToJson(writer);

	writer.String("unk");
	writer.StartArray();

	for (uint32_t i = 0; i < 152; ++i)
	{
		writer.Uint(unk[i]);
	}

	writer.EndArray();

	writer.EndObject();
}

ZIOINodeSelectItemDef::ZIOINodeSelectItemDef(uint32_t typeID) : MR::NodeDef(typeID)
{
}

void ZIOINodeSelectItemDef::SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject) const
{
	writer.StartObject();

	MR::NodeDef::SerializeToJson(writer);

	writer.String("unk");
	writer.StartArray();

	for (uint32_t i = 0; i < 24; ++i)
	{
		writer.Uint(unk[i]);
	}

	writer.EndArray();

	writer.EndObject();
}

ZNodeDefTransitionSelect::ZNodeDefTransitionSelect(uint32_t typeID) : MR::NodeDefPassThrough(typeID)
{
}

void ZNodeDefTransitionSelect::SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject) const
{
	writer.StartObject();

	MR::NodeDefPassThrough::SerializeToJson(writer);

	writer.String("m_currentVelocityCtrlID");
	m_currentVelocityCtrlID.SerializeToJson(writer);

	writer.String("m_currentFootCtrlID");
	m_currentFootCtrlID.SerializeToJson(writer);

	writer.String("m_targetVelocityCtrlID");
	m_targetVelocityCtrlID.SerializeToJson(writer);

	writer.String("m_targetRotationOffsetCtrlID");
	m_targetRotationOffsetCtrlID.SerializeToJson(writer);

	writer.String("m_targetPositionOffsetCtrlID");
	m_targetPositionOffsetCtrlID.SerializeToJson(writer);

	writer.String("m_sourceNodeIDs");
	writer.StartArray();

	for (uint32_t i = 0; i < 24; ++i)
	{
		m_sourceNodeIDs[i].SerializeToJson(writer);
	}

	writer.EndArray();

	writer.EndObject();
}

ZNodeDefIOITransit::ZNodeDefIOITransit(uint32_t typeID) : MR::NodeDefTransit(typeID)
{
}

void ZNodeDefIOITransit::SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject) const
{
	writer.StartObject();

	MR::NodeDefTransit::SerializeToJson(writer, false);

	writer.String("m_bStartDestinationFromBeginning");
	writer.Bool(m_bStartDestinationFromBeginning);

	writer.String("m_bBlendFromLastFrame");
	writer.Bool(m_bBlendFromLastFrame);

	writer.EndObject();
}

NodeDefIOIDeltaAnim::NodeDefIOIDeltaAnim(uint32_t typeID) : MR::NodeDefBlend2(typeID)
{
}

NodeDefIOIDeltaAnimMatchEvents::NodeDefIOIDeltaAnimMatchEvents(uint32_t typeID) : MR::NodeDefBlend2MatchEvents(typeID)
{
}

NodeDefIOIHeadController::NodeDefIOIHeadController(uint32_t typeID) : MR::NodeDefPassThroughTransforms(typeID)
{
}

void NodeDefIOIHeadController::SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject) const
{
	writer.StartObject();

	MR::NodeDefPassThroughTransforms::SerializeToJson(writer);

	writer.String("m_pointingVectorX");
	writer.Double(m_pointingVectorX);

	writer.String("m_pointingVectorY");
	writer.Double(m_pointingVectorY);

	writer.String("m_pointingVectorZ");
	writer.Double(m_pointingVectorZ);

	writer.String("m_offsetX");
	writer.Double(m_offsetX);

	writer.String("m_offsetY");
	writer.Double(m_offsetY);

	writer.String("m_offsetZ");
	writer.Double(m_offsetZ);

	writer.String("m_headEndJoint");
	m_headEndJoint.SerializeToJson(writer);

	writer.String("m_headRootJoint");
	m_headRootJoint.SerializeToJson(writer);

	writer.String("m_leftEyeJoint");
	m_leftEyeJoint.SerializeToJson(writer);

	writer.String("m_rightEyeJoint");
	m_rightEyeJoint.SerializeToJson(writer);

	writer.String("m_leftEyelidJoint");
	m_leftEyelidJoint.SerializeToJson(writer);

	writer.String("m_rightEyelidJoint");
	m_rightEyelidJoint.SerializeToJson(writer);

	writer.String("m_leftEyebrowJoint");
	m_leftEyebrowJoint.SerializeToJson(writer);

	writer.String("m_rightEyebrowJoint");
	m_rightEyebrowJoint.SerializeToJson(writer);

	writer.String("m_targetNodeID");
	m_targetNodeID.SerializeToJson(writer);

	writer.String("m_targetNoiseNodeID");
	m_targetNoiseNodeID.SerializeToJson(writer);

	writer.String("m_targetWeightNodeID");
	m_targetWeightNodeID.SerializeToJson(writer);

	writer.String("m_headBiasNodeID");
	m_headBiasNodeID.SerializeToJson(writer);

	writer.String("m_drowsinessNodeID");
	m_drowsinessNodeID.SerializeToJson(writer);

	writer.String("m_blendWeightNodeID");
	m_blendWeightNodeID.SerializeToJson(writer);

	writer.String("m_updateTargetByDeltas");
	writer.Bool(m_updateTargetByDeltas);

	writer.EndObject();
}

NodeDefIOIPelvisOffset::NodeDefIOIPelvisOffset(uint32_t typeID) : MR::NodeDefPassThroughTransforms(typeID)
{
}

void NodeDefIOIPelvisOffset::SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject) const
{
	writer.StartObject();

	MR::NodeDefPassThroughTransforms::SerializeToJson(writer);

	writer.String("m_OffsetWeightNodeID");
	writer.Uint(m_OffsetWeightNodeID);

	writer.String("m_OffsetVectorNodeID");
	writer.Uint(m_OffsetVectorNodeID);

	writer.String("m_pszBoneName");
	writer.String(m_pszBoneName);

	writer.EndObject();
}

void NodeDefIOIPelvisOffset::Locate()
{
	MR::NodeDef::Locate();

	m_pszBoneName = Relocate(m_pszBoneName, this);
}

NodeDefIOIMirror::NodeDefIOIMirror(uint32_t typeID) : MR::NodeDefPassThroughTransforms(typeID)
{
}

void NodeDefIOIMirror::SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject) const
{
	writer.StartObject();

	MR::NodeDefPassThroughTransforms::SerializeToJson(writer);

	writer.String("m_nDisableOptionID");
	m_nDisableOptionID.SerializeToJson(writer);

	writer.String("m_bSwapHandAttachers");
	writer.Bool(m_bSwapHandAttachers);

	writer.EndObject();
}

NodeDefIOIMirrorMatchEvents::NodeDefIOIMirrorMatchEvents(uint32_t typeID) : MR::NodeDefPassThroughTransforms(typeID)
{
}

void NodeDefIOIMirrorMatchEvents::SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject) const
{
	writer.StartObject();

	MR::NodeDefPassThroughTransforms::SerializeToJson(writer);

	writer.String("m_rightFootEvent");
	writer.Uint(m_rightFootEvent);

	writer.String("m_leftFootEvent");
	writer.Uint(m_leftFootEvent);

	writer.String("m_rightHandEvent");
	writer.Uint(m_rightHandEvent);

	writer.String("m_leftHandEvent");
	writer.Uint(m_leftHandEvent);

	writer.String("m_bSwapHandAttachers");
	writer.Bool(m_bSwapHandAttachers);

	writer.EndObject();
}

NodeDefIOIBlend2AndReTarget::NodeDefIOIBlend2AndReTarget(uint32_t typeID) : MR::NodeDefBlend2(typeID)
{
}

void NodeDefIOIBlend2AndReTarget::SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject) const
{
	writer.StartObject();

	MR::NodeDefBlend2::SerializeToJson(writer, false);

	writer.String("m_nReTargetFlags");
	writer.Uint(m_nReTargetFlags);

	writer.EndObject();
}

NodeDefPlaySpeedModifierMatchEvents::NodeDefPlaySpeedModifierMatchEvents(uint32_t typeID) : MR::NodeDefPassThrough(typeID)
{
}

void NodeDefPlaySpeedModifierMatchEvents::SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject) const
{
	writer.StartObject();

	MR::NodeDefPassThrough::SerializeToJson(writer);

	writer.String("m_playSpeedFactorID");
	writer.Uint(m_playSpeedFactorID);

	writer.EndObject();
}

NodeDefIOIPartialMirrorAim::NodeDefIOIPartialMirrorAim(uint32_t typeID) : MR::NodeDefPassThroughTransforms(typeID)
{
}

void NodeDefIOIPartialMirrorAim::SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject) const
{
	writer.StartObject();

	MR::NodeDefPassThroughTransforms::SerializeToJson(writer);

	writer.String("m_MirrorWeightNodeID");
	writer.Uint(m_MirrorWeightNodeID);

	writer.EndObject();
}

ZNodeDefIOISneakModifier::ZNodeDefIOISneakModifier(uint32_t typeID) : MR::NodeDefPassThroughTransforms(typeID)
{
}

void ZNodeDefIOISneakModifier::SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject) const
{
	writer.StartObject();

	MR::NodeDefPassThroughTransforms::SerializeToJson(writer);

	writer.String("m_nWeightNodeID");
	writer.Uint(m_nWeightNodeID);

	writer.String("m_nPelvisOffsetNodeID");
	writer.Uint(m_nPelvisOffsetNodeID);

	writer.String("m_nPelvisAngleNodeID");
	writer.Uint(m_nPelvisAngleNodeID);

	writer.String("m_nSpeedModifierNodeID");
	writer.Uint(m_nSpeedModifierNodeID);

	writer.String("m_nLeftHandQuatNodeID");
	writer.Uint(m_nLeftHandQuatNodeID);

	writer.EndObject();
}

ZNodeDefIOITranslationScale::ZNodeDefIOITranslationScale(uint32_t typeID) : MR::NodeDefPassThrough(typeID)
{
}

void ZNodeDefIOITranslationScale::SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject) const
{
	writer.StartObject();

	MR::NodeDefPassThrough::SerializeToJson(writer);

	writer.String("m_nScaleNodeId");
	writer.Uint(m_nScaleNodeId);

	writer.EndObject();
}

ZNodeDefIOIWildCardTransitMatchEvents::ZNodeDefIOIWildCardTransitMatchEvents(uint32_t typeID) : MR::NodeDefTransitMatchEvents(typeID)
{
}

ZNodeDefIOIWildCardTransit::ZNodeDefIOIWildCardTransit(uint32_t typeID) : MR::NodeDefTransit(typeID)
{
}

void SNodeSelectMatchEventsInfo_V2::SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject) const
{
	writer.StartObject();

	writer.String("m_sourceNodeIDs");
	writer.StartArray();

	for (uint32_t i = 0; i < 35; ++i)
	{
		m_sourceNodeIDs[i].SerializeToJson(writer);
	}

	writer.EndArray();

	writer.String("m_selectCtrlID");
	writer.Uint(m_selectCtrlID);

	writer.String("m_blendCtrlID");
	writer.Uint(m_blendCtrlID);

	writer.EndObject();
}

void SNodeSelectMatchEventsInfo::SNodeInfo::SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject) const
{
	writer.StartObject();

	writer.String("m_id");
	writer.Uint(m_id);

	writer.String("m_index");
	writer.Double(m_id);

	writer.EndObject();
}

ZNodeDefSelectMatchEvents::ZNodeDefSelectMatchEvents(uint32_t typeID) : MR::NodeDefTransitMatchEvents(typeID)
{
}

void ZNodeDefSelectMatchEvents::SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject) const
{
	writer.StartObject();

	writer.String("m_NodeIDs");
	m_NodeIDs.SerializeToJson(writer);

	writer.String("m_bRandomSelectAtInit");
	writer.Bool(m_bRandomSelectAtInit);

	writer.String("m_bUpdateSelectIndex");
	writer.Bool(m_bUpdateSelectIndex);

	writer.EndObject();
}

NodeDefIOIParametricBlendNMatchEvents::NodeDefIOIParametricBlendNMatchEvents(uint32_t typeID) : MR::NodeDefBlend2MatchEvents(typeID)
{
}

void NodeDefIOIParametricBlendNMatchEvents::SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject) const
{
	writer.StartObject();

	writer.String("m_numSourceNodes");
	writer.Uint(m_numSourceNodes);

	writer.String("m_connectedSourceNode");
	writer.Uint(m_connectedSourceNode[0]);

	writer.EndObject();
}

ZNodeDefIOIFeatherTransit::ZNodeDefIOIFeatherTransit(uint32_t typeID) : MR::NodeDefTransit(typeID)
{
}

void ZNodeDefIOIFeatherTransit::SerializeToJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const bool startObject) const
{
	writer.StartObject();

	MR::NodeDefTransit::SerializeToJson(writer, false);

	writer.String("unk");
	writer.StartArray();

	for (uint32_t i = 0; i < 24; ++i)
	{
		writer.Uint(unk[i]);
	}

	writer.EndArray();

	writer.EndObject();
}
