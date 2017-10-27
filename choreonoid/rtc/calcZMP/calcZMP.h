#ifndef CALCZMPCOMP_H
#define CALCZMPCOMP_H

#include <iostream>
#include <Eigen/Core>

#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/ExtendedDataTypesSkel.h>
#include <rtm/idl/InterfaceDataTypesSkel.h>

using namespace std;
using namespace Eigen;
using namespace RTC;

#include <rtm/Manager.h>
#include <rtm/DataFlowComponentBase.h>
#include <rtm/CorbaPort.h>
#include <rtm/DataInPort.h>
#include <rtm/DataOutPort.h>

class calcZMPComp
: public RTC::DataFlowComponentBase
{
	public:
		calcZMPComp(RTC::Manager* manager);
		virtual RTC::ReturnCode_t onInitialize();
		virtual RTC::ReturnCode_t onActivated(RTC::UniqueId ec_id);
		virtual RTC::ReturnCode_t onDeactivated(RTC::UniqueId ec_id);
		virtual RTC::ReturnCode_t onExecute(RTC::UniqueId ec_id);
	protected:
		TimedDoubleSeq m_rhsensor;
		InPort<TimedDoubleSeq> m_rhsensorIn;
		TimedDoubleSeq m_lhsensor;
		InPort<TimedDoubleSeq> m_lhsensorIn;
		TimedDoubleSeq m_rfsensor;
		InPort<TimedDoubleSeq> m_rfsensorIn;
		TimedDoubleSeq m_lfsensor;
		InPort<TimedDoubleSeq> m_lfsensorIn;
	private:
		Vector3d calcActualZmp(TimedDoubleSeq &m_rfsensor, TimedDoubleSeq &m_lfsensor);
};


extern "C"
{
	DLL_EXPORT void calcZMPCompInit(RTC::Manager* manager);
};

#endif // CALCZMPCOMP_H
