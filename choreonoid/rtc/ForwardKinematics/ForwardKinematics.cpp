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
	m_qInIn("qIn", m_qIn)
	//m_qOutOut("qOut", m_qOut)
{
}

ForwardKinematics::~ForwardKinematics()
{
}



RTC::ReturnCode_t ForwardKinematics::onInitialize()
{
	addInPort("qIn", m_qInIn);

	//addOutPort("qOut", m_qOutOut);
	
	kine = new Kinematics(ulink);
	SetJointInfo(ulink);

	return RTC::RTC_OK;
}

RTC::ReturnCode_t ForwardKinematics::onActivated(RTC::UniqueId ec_id)
{
	if(m_qInIn.isNew())
		m_qInIn.read();
	
	for(size_t i=0;i<JOINT_NUM;i++)
		kine->ulink[i].q = 0.0;
	for(size_t i=1;i<JOINT_NUM;i++)
		kine->ulink[i].q = m_qIn.data[i-1];
	
	kine->calcForwardKinematics(WAIST);

	return RTC::RTC_OK;
}


RTC::ReturnCode_t ForwardKinematics::onDeactivated(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}


RTC::ReturnCode_t ForwardKinematics::onExecute(RTC::UniqueId ec_id)
{
	if(m_qInIn.isNew())
		m_qInIn.read();
	
	for(size_t i=1;i<JOINT_NUM;i++)
		kine->ulink[i].q = m_qIn.data[i];

	kine->calcForwardKinematics(WAIST);

	cout << ulink[RLEG_JOINT5].p(0) << " " << ulink[RLEG_JOINT5].p(1) << " " << ulink[RLEG_JOINT5].p(2) << endl;
	cout << ulink[LLEG_JOINT5].p(0) << " " << ulink[LLEG_JOINT5].p(1) << " " << ulink[LLEG_JOINT5].p(2) << "\n" << endl;

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


