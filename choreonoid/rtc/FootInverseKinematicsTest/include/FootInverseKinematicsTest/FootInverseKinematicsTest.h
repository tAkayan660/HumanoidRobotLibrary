#ifndef FOOTINVERSEKINEMATICSTEST_H
#define FOOTINVERSEKINEMATICSTEST_H

#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/ExtendedDataTypesSkel.h>
#include <rtm/idl/InterfaceDataTypesSkel.h>

#include <rtm/Manager.h>
#include <rtm/DataFlowComponentBase.h>
#include <rtm/CorbaPort.h>
#include <rtm/DataInPort.h>
#include <rtm/DataOutPort.h>

#include "Kinematics.h"
#include "Link.h"
#include "LinkParameter.h"

using namespace RTC;
using namespace MotionControl;

class FootInverseKinematicsTest
: public RTC::DataFlowComponentBase
{
	public:
		FootInverseKinematicsTest(RTC::Manager* manager);
		~FootInverseKinematicsTest();
		virtual RTC::ReturnCode_t onInitialize();
		virtual RTC::ReturnCode_t onActivated(RTC::UniqueId ec_id);
		virtual RTC::ReturnCode_t onDeactivated(RTC::UniqueId ec_id);
		virtual RTC::ReturnCode_t onExecute(RTC::UniqueId ec_id);

	protected:
		RTC::TimedDoubleSeq m_qCur;
		InPort<RTC::TimedDoubleSeq> m_qCurIn;

		RTC::TimedDoubleSeq m_qRef;
		OutPort<RTC::TimedDoubleSeq> m_qRefOut;
	private:
		int count;
		std::vector<Vector3d> rfoot_pos,lfoot_pos;
		Kinematics *kine;
		Link ulink[JOINT_NUM];
		Link RFLink, LFLink;
		Link target_R, target_L;
};


extern "C"
{
	DLL_EXPORT void FootInverseKinematicsTestInit(RTC::Manager* manager);
};

#endif // FOOTINVERSEKINEMATICSTEST_H
