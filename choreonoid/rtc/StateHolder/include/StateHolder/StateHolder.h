#ifndef STATEHOLDER_H
#define STATEHOLDER_H

#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/ExtendedDataTypesSkel.h>
#include <rtm/idl/InterfaceDataTypesSkel.h>

using namespace RTC;

#include <rtm/Manager.h>
#include <rtm/DataFlowComponentBase.h>
#include <rtm/CorbaPort.h>
#include <rtm/DataInPort.h>
#include <rtm/DataOutPort.h>

class StateHolder
  : public RTC::DataFlowComponentBase
{
 public:
  StateHolder(RTC::Manager* manager);
  ~StateHolder();

   virtual RTC::ReturnCode_t onInitialize();
   virtual RTC::ReturnCode_t onActivated(RTC::UniqueId ec_id);
   virtual RTC::ReturnCode_t onDeactivated(RTC::UniqueId ec_id);
   virtual RTC::ReturnCode_t onExecute(RTC::UniqueId ec_id);

 protected:
  RTC::TimedDoubleSeq m_qIn;
  InPort<RTC::TimedDoubleSeq> m_qInIn;
  RTC::TimedDoubleSeq m_gsensor;
  InPort<RTC::TimedDoubleSeq> m_gsensorIn;
  RTC::TimedDoubleSeq m_gyrometer;
  InPort<RTC::TimedDoubleSeq> m_gyrometerIn;
  RTC::TimedDoubleSeq m_lfsensor;
  InPort<RTC::TimedDoubleSeq> m_lfsensorIn;
  RTC::TimedDoubleSeq m_rfsensor;
  InPort<RTC::TimedDoubleSeq> m_rfsensorIn;

  RTC::TimedDoubleSeq m_qOut;
  OutPort<RTC::TimedDoubleSeq> m_qOutOut;
 private:
};


extern "C"
{
  DLL_EXPORT void StateHolderInit(RTC::Manager* manager);
};

#endif // STATEHOLDER_H
