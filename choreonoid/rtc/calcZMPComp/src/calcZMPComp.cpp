// -*- C++ -*-
/*!
 * @file  calcZMPComp.cpp
 * @brief ModuleDescription
 * @date $Date$
 *
 * $Id$
 */

#include "calcZMPComp.h"

// Module specification
// <rtc-template block="module_spec">
static const char* calczmpcomp_spec[] =
  {
    "implementation_id", "calcZMPComp",
    "type_name",         "calcZMPComp",
    "description",       "ModuleDescription",
    "version",           "1.0.0",
    "vendor",            "CIT",
    "category",          "Category",
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
calcZMPComp::calcZMPComp(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
calcZMPComp::~calcZMPComp()
{
}



RTC::ReturnCode_t calcZMPComp::onInitialize()
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
RTC::ReturnCode_t calcZMPComp::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t calcZMPComp::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t calcZMPComp::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t calcZMPComp::onActivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t calcZMPComp::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t calcZMPComp::onExecute(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t calcZMPComp::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t calcZMPComp::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t calcZMPComp::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t calcZMPComp::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t calcZMPComp::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void calcZMPCompInit(RTC::Manager* manager)
  {
    coil::Properties profile(calczmpcomp_spec);
    manager->registerFactory(profile,
                             RTC::Create<calcZMPComp>,
                             RTC::Delete<calcZMPComp>);
  }
  
};


