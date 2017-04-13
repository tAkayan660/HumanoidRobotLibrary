#include "calcZMP.h"

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

calcZMPComp::calcZMPComp(RTC::Manager* manager)
	: RTC::DataFlowComponentBase(manager),
		m_rhsensorIn("rhsensor", m_rhsensor),
		m_lhsensorIn("lhsensor", m_lhsensor),
		m_rfsensorIn("rfsensor", m_rfsensor),
		m_lfsensorIn("lfsensor", m_lfsensor)
{
}

RTC::ReturnCode_t calcZMPComp::onInitialize()
{
	addInPort("rhsensor", m_rhsensorIn);
	addInPort("lhsensor", m_lhsensorIn);
	addInPort("rfsensor", m_rfsensorIn);
	addInPort("lfsensor", m_lfsensorIn);

	m_rhsensor.data.length(6);
	m_lhsensor.data.length(6);
	m_rfsensor.data.length(6);
	m_lfsensor.data.length(6);

	return RTC::RTC_OK;
}


RTC::ReturnCode_t calcZMPComp::onActivated(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}

RTC::ReturnCode_t calcZMPComp::onDeactivated(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}

RTC::ReturnCode_t calcZMPComp::onExecute(RTC::UniqueId ec_id)
{
	if(m_rhsensorIn.isNew())
		m_rhsensorIn.read();
	if(m_lhsensorIn.isNew())
		m_lhsensorIn.read();
	if(m_rfsensorIn.isNew())
		m_rfsensorIn.read();
	if(m_lfsensorIn.isNew())
		m_lfsensorIn.read();

	Vector3d zmp = calcActualZmp(m_rfsensor, m_lfsensor);

	std::cout << "ZMP x:" << zmp[0] << " ZMP y:" << zmp[1] << std::endl;
	
	return RTC::RTC_OK;
}

// 6軸力センサの値からZMP値を計算する
Vector3d calcZMPComp::calcActualZmp(TimedDoubleSeq &m_rfsensor, TimedDoubleSeq &m_lfsensor)
{
	double d=0.01; // センサから足裏までの距離
	Vector3d zmp_r, zmp_l;	// 両脚それぞれのZMP
	Vector3d zmp;	// 両脚を考慮したZMP

	zmp_r << (-m_rfsensor.data[4]-m_rfsensor.data[0]*d) / m_rfsensor.data[2],
			(m_rfsensor.data[3]-m_rfsensor.data[1]*d) / m_rfsensor.data[2],
			0.0;
	zmp_l << (-m_lfsensor.data[4]-m_lfsensor.data[0]*d) / m_lfsensor.data[2],
			(m_lfsensor.data[3]-m_lfsensor.data[0]*d) / m_lfsensor.data[2],
			0.0;

	double force_vector = m_rfsensor.data[2] + m_lfsensor.data[2];
	zmp[0] = (zmp_r[0]*m_rfsensor.data[2] + zmp_l[0]*m_lfsensor.data[2]) / force_vector;
	zmp[1] = (zmp_r[1]*m_rfsensor.data[2] + zmp_l[1]*m_lfsensor.data[2]) / force_vector;
	zmp[2] = 0.0;

	return zmp;
}

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


