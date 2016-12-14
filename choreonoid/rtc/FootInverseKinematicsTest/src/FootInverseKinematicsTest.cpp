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
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("qCur", m_qCurIn);
  
  // Set OutPort buffer
  addOutPort("qRef", m_qRefOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t FootInverseKinematicsTest::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t FootInverseKinematicsTest::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t FootInverseKinematicsTest::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t FootInverseKinematicsTest::onActivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t FootInverseKinematicsTest::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t FootInverseKinematicsTest::onExecute(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t FootInverseKinematicsTest::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t FootInverseKinematicsTest::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t FootInverseKinematicsTest::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t FootInverseKinematicsTest::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t FootInverseKinematicsTest::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



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


