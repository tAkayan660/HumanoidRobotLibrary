// -*- C++ -*-
/*!
 * @file  ForwardKinematics.cpp
 * @brief test
 * @date $Date$
 *
 * $Id$
 */

#include "ForwardKinematics.h"

// Module specification
// <rtc-template block="module_spec">
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
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
ForwardKinematics::ForwardKinematics(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_qInIn("qIn", m_qIn),
    m_qOutOut("qOut", m_qOut)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
ForwardKinematics::~ForwardKinematics()
{
}



RTC::ReturnCode_t ForwardKinematics::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("qIn", m_qInIn);
  
  // Set OutPort buffer
  addOutPort("qOut", m_qOutOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t ForwardKinematics::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ForwardKinematics::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ForwardKinematics::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


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

/*
RTC::ReturnCode_t ForwardKinematics::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ForwardKinematics::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ForwardKinematics::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ForwardKinematics::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ForwardKinematics::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



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


