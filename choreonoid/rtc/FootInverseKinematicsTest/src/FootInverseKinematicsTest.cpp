#include "FootInverseKinematicsTest.h"

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

FootInverseKinematicsTest::FootInverseKinematicsTest(RTC::Manager* manager)
	: RTC::DataFlowComponentBase(manager),
	m_qCurIn("qCur", m_qCur),
	m_qRefOut("qRef", m_qRef),
	count(0)
{
}

FootInverseKinematicsTest::~FootInverseKinematicsTest()
{
}

RTC::ReturnCode_t FootInverseKinematicsTest::onInitialize()
{
	addInPort("qCur", m_qCurIn);
	
	addOutPort("qRef", m_qRefOut);

	FILE *fp;
	fp = fopen("foot_trajectory.csv", "r");

	double rx,ry,rz;
	double lx,ly,lz;
	while(fscanf(fp,"%lf %lf %lf %lf %lf %lf", &rx,&ry,&rz,&lx,&ly,&lz) != EOF)
	{
		rfoot_pos.push_back(Vector3d(rx,ry,rz));
		lfoot_pos.push_back(Vector3d(lx,ly,lz));
	}
	fclose(fp);

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

	target_R = RFLink;
	target_L = LFLink;

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

		target_R.p(1) = RFLink.p(1) + rfoot_pos[count](1)*1000;
		target_R.p(2) = RFLink.p(2) + rfoot_pos[count](2)*1000;
		target_L.p(1) = LFLink.p(1) + lfoot_pos[count](1)*1000;
		target_L.p(2) = LFLink.p(2) + lfoot_pos[count](2)*1000;
		count++;

		if(kine->calcInverseKinematics(RLEG_JOINT5, target_R) && kine->calcInverseKinematics(LLEG_JOINT5, target_L)){
			cout << target_R.p(1) << " " << target_R.p(2) << endl;
 			for(size_t i=0;i<12;i++)
				m_qRef.data[i] = ulink[i+1].q;
		}else{
			cout << "Inverse Kinematics Faild." << endl;
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


