// -*- C++ -*-
/*!
 * @file  FootInverseKinematicsTest.cpp
 * @brief  Test program check Inverse Kinematics 
 * @date $Date$
 *
 * $Id$
 */

#include "FootInverseKinematicsTest.h"

// Module specification
// <rtc-template block="module_spec">
static const char* footinversekinematicstest_spec[] =
{
	"implementation_id", "FootInverseKinematicsTest",
	"type_name",         "FootInverseKinematicsTest",
	"description",       " Test program check Inverse Kinematics ",
	"version",           "1.0.0",
	"vendor",            "CIT",
	"category",          "test",
	"activity_type",     "PERIODIC",
	"kind",              "DataFlowComponent",
	"max_instance",      "1",
	"language",          "C++",
	"lang_type",         "compile",
	""
};
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
FootInverseKinematicsTest::FootInverseKinematicsTest(RTC::Manager* manager)
	// <rtc-template block="initializer">
	: RTC::DataFlowComponentBase(manager),
	m_qCurIn("qCur", m_qCur),
	m_qRefOut("qRef", m_qRef)

	  // </rtc-template>
{
}

/*!
 * @brief destructor
 */
FootInverseKinematicsTest::~FootInverseKinematicsTest()
{
}



RTC::ReturnCode_t FootInverseKinematicsTest::onInitialize()
{
	addInPort("qCur", m_qCurIn);

	addOutPort("qRef", m_qRefOut);

	kine = new Kinematics(ulink);
	SetJointInfo(ulink);

	return RTC::RTC_OK;
}

RTC::ReturnCode_t FootInverseKinematicsTest::onActivated(RTC::UniqueId ec_id)
{
	if(m_qCurIn.isNew()){
		m_qCurIn.read();
		m_qRef.data.length((m_qCur.data.length()));
	}
	
	for(size_t i=0;i<JOINT_NUM;i++)
		ulink[i+1].q = m_qCur.data[i];
	for(size_t i=0;i<m_qCur.data.length();i++)
		m_qRef.data[i] = m_qCur.data[i];
	
	kine->calcForwardKinematics(WAIST);

	RFLink = ulink[RLEG_JOINT5];
	LFLink = ulink[LLEG_JOINT5];

	return RTC::RTC_OK;
}

RTC::ReturnCode_t FootInverseKinematicsTest::onDeactivated(RTC::UniqueId ec_id)
{
	cout << "Deacvated" << endl;
	return RTC::RTC_OK;
}


RTC::ReturnCode_t FootInverseKinematicsTest::onExecute(RTC::UniqueId ec_id)
{
	if(m_qCurIn.isNew()){
		m_qCurIn.read();
		
		for(size_t i=0;i<JOINT_NUM;i++)
			ulink[i+1].q = m_qCur.data[i];

		kine->calcForwardKinematics(WAIST);

		if(RFLink.p(2) < -650.0){
			RFLink.p(2) += 0.1; LFLink.p(2) += 0.1;

			if(kine->calcInverseKinematics(RLEG_JOINT5, RFLink) && kine->calcInverseKinematics(LLEG_JOINT5, LFLink)){
				for(size_t i=0;i<12;i++)
					m_qRef.data[i] = ulink[i+1].q;
				cout << RFLink.p(2) << " " << LFLink.p(2) << endl;
			}else{
				cout << "Inverse Kinematics Faild." << endl;
			}
		}
	}
	m_qRefOut.write();

	return RTC::RTC_OK;
}



extern "C"
{

	void FootInverseKinematicsTestInit(RTC::Manager* manager)
	{
		coil::Properties profile(footinversekinematicstest_spec);
		manager->registerFactory(profile,
				RTC::Create<FootInverseKinematicsTest>,
				RTC::Delete<FootInverseKinematicsTest>);
	}

};


