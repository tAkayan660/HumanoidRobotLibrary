#include "StateHolder.h"
#include <iostream>

using namespace std;

static const char* stateholder_spec[] =
  {
    "implementation_id", "StateHolder",
    "type_name",         "StateHolder",
    "description",       "test",
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

StateHolder::StateHolder(RTC::Manager* manager)
  : RTC::DataFlowComponentBase(manager),
    m_qInIn("qIn", m_qIn),
	m_gsensorIn("gsensor", m_gsensor),
	m_gyrometerIn("gyrometer", m_gyrometer),
	m_lfsensorIn("lfsensor", m_lfsensor),
	m_rfsensorIn("rfsensor", m_rfsensor),
	m_qOutOut("qOut", m_qOut)
{
}

StateHolder::~StateHolder()
{
}



RTC::ReturnCode_t StateHolder::onInitialize()
{
	addInPort("qIn", m_qInIn);

	addInPort("gsensor", m_gsensorIn);
	addInPort("gyrometer", m_gyrometerIn);
	addInPort("lfsensor", m_lfsensorIn);
	addInPort("rfsensor", m_rfsensorIn);
	addInPort("lfsensor", m_lfsensorIn);
	addOutPort("qOut", m_qOutOut);

	return RTC::RTC_OK;
}

RTC::ReturnCode_t StateHolder::onActivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t StateHolder::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t StateHolder::onExecute(RTC::UniqueId ec_id)
{
	if(m_qInIn.isNew())
		m_qInIn.read();
	
	for(size_t i=0;i<m_qIn.data.length();i++){
		m_qOut.data[i] = m_qIn.data[i];
		cout<<m_qIn.data[i]<<endl;	
	}
	m_qOutOut.write();

	if(m_gsensorIn.isNew())
		m_gsensorIn.read();
	
	if(m_gyrometerIn.isNew())
		m_gyrometerIn.read();
	
	if(m_lfsensorIn.isNew())
		m_lfsensorIn.read();
	
	if(m_rfsensorIn.isNew())
		m_rfsensorIn.read();

	for(size_t i=0;i<m_lfsensor.data.length();i++)
		cout<<m_lfsensor.data[i]<< " ";
	cout<<"\n";

	for(size_t i=0;i<m_rfsensor.data.length();i++)
		cout<<m_rfsensor.data[i]<< " ";
	cout<<"\n"; 

  return RTC::RTC_OK;
}

extern "C"
{
 
  void StateHolderInit(RTC::Manager* manager)
  {
    coil::Properties profile(stateholder_spec);
    manager->registerFactory(profile,
                             RTC::Create<StateHolder>,
                             RTC::Delete<StateHolder>);
  }
  
};


