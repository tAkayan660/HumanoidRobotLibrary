// -*- C++ -*-
/*!
 * @file  ArmInverseKinematicsTest.cpp
 * @brief Test code for arm control using inverse kinematics
 * @date $Date$
 *
 * $Id$
 */

#include "ArmInverseKinematicsTest.h"

// Module specification
// <rtc-template block="module_spec">
static const char* arminversekinematicstest_spec[] =
  {
    "implementation_id", "ArmInverseKinematicsTest",
    "type_name",         "ArmInverseKinematicsTest",
    "description",       "Test code for arm control using inverse kinematics",
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
ArmInverseKinematicsTest::ArmInverseKinematicsTest(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
ArmInverseKinematicsTest::~ArmInverseKinematicsTest()
{
}



RTC::ReturnCode_t ArmInverseKinematicsTest::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  
  // Set OutPort buffer
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t ArmInverseKinematicsTest::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ArmInverseKinematicsTest::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ArmInverseKinematicsTest::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t ArmInverseKinematicsTest::onActivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t ArmInverseKinematicsTest::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t ArmInverseKinematicsTest::onExecute(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t ArmInverseKinematicsTest::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ArmInverseKinematicsTest::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ArmInverseKinematicsTest::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ArmInverseKinematicsTest::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ArmInverseKinematicsTest::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void ArmInverseKinematicsTestInit(RTC::Manager* manager)
  {
    coil::Properties profile(arminversekinematicstest_spec);
    manager->registerFactory(profile,
                             RTC::Create<ArmInverseKinematicsTest>,
                             RTC::Delete<ArmInverseKinematicsTest>);
  }
  
};


