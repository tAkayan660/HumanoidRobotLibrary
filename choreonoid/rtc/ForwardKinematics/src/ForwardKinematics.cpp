#include "ForwardKinematics.h"

static const char* forwardkinematics_spec[] =
{
	"implementation_id", "ForwardKinematics",
	"type_name",         "ForwardKinematics",
	"description",       "test",
	"version",           "1.0.0",
	"vendor",            "CIT",
	"category",          "tes",
	"activity_type",     "PERIODIC",
	"kind",              "DataFlowComponent",
	"max_instance",      "1",
	"language",          "C++",
	"lang_type",         "compile",
	""
};

ForwardKinematics::ForwardKinematics(RTC::Manager* manager)
	: RTC::DataFlowComponentBase(manager),
	m_qInIn("qIn", m_qIn),
	m_qOutOut("qOut", m_qOut)
{
}

ForwardKinematics::~ForwardKinematics()
{
}



RTC::ReturnCode_t ForwardKinematics::onInitialize()
{
	addInPort("qIn", m_qInIn);

	addOutPort("qOut", m_qOutOut);

	return RTC::RTC_OK;
}

RTC::ReturnCode_t ForwardKinematics::onActivated(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}


RTC::ReturnCode_t ForwardKinematics::onDeactivated(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}


RTC::ReturnCode_t ForwardKinematics::onExecute(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}

extern "C"
{

	void ForwardKinematicsInit(RTC::Manager* manager)
	{
		coil::Properties profile(forwardkinematics_spec);
		manager->registerFactory(profile,
				RTC::Create<ForwardKinematics>,
				RTC::Delete<ForwardKinematics>);
	}

};


