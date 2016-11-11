#ifndef FORWARDKINEMATICS_H
#define FORWARDKINEMATICS_H

#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/ExtendedDataTypesSkel.h>
#include <rtm/idl/InterfaceDataTypesSkel.h>

using namespace RTC;

#include <rtm/Manager.h>
#include <rtm/DataFlowComponentBase.h>
#include <rtm/CorbaPort.h>
#include <rtm/DataInPort.h>
#include <rtm/DataOutPort.h>

class ForwardKinematics
: public RTC::DataFlowComponentBase
{
	public:
		ForwardKinematics(RTC::Manager* manager);
		~ForwardKinematics();

		virtual RTC::ReturnCode_t onInitialize();
		virtual RTC::ReturnCode_t onActivated(RTC::UniqueId ec_id);
		virtual RTC::ReturnCode_t onDeactivated(RTC::UniqueId ec_id);
		virtual RTC::ReturnCode_t onExecute(RTC::UniqueId ec_id);

	protected:

		RTC::TimedDoubleSeq m_qIn;
		InPort<RTC::TimedDoubleSeq> m_qInIn;

		RTC::TimedDoubleSeq m_qOut;
		OutPort<RTC::TimedDoubleSeq> m_qOutOut;
	private:
};


extern "C"
{
	DLL_EXPORT void ForwardKinematicsInit(RTC::Manager* manager);
};

#endif // FORWARDKINEMATICS_H
