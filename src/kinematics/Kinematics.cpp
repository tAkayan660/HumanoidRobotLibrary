#include "Kinematics.h"
#include "Jacobian.h"

Matrix<double,3,3> Kinematics::Rodrigues(Matrix<double,3,1> a, double q)
{
	return AngleAxisd(q,a).toRotationMatrix();
}

Matrix<double,3,1> Kinematics::rot2omega(Matrix<double,3,3> R)
{
	double alpha = (R(0,0)+R(1,1)+R(2,2)-1)/2;
	double th;
	Matrix<double,3,1> vector_R(Matrix<double,3,1>::Zero());

	if(fabs(alpha-1) < eps)
		return Matrix<double,3,1>::Zero();

	th = acos(alpha);
	vector_R << R(2,1)-R(1,2), R(0,2)-R(2,0), R(1,0)-R(0,1);
	return 0.5*th/sin(th)*vector_R;
}

vector<int> Kinematics::FindRoute(int to)
{
	vector<int> idx;
	int link_num = to;

	while(link_num != 0)
	{
		idx.push_back(link_num);
		link_num = ulink[link_num].parent;
	}
	reverse(idx.begin(), idx.end());
	return idx;
}

Matrix<double,6,1> Kinematics::calcVWerr(Link Cref, Link Cnow)
{
	Matrix<double,3,1> perr = Cref.p - Cnow.p;
	Matrix<double,3,3> Rerr = Cref.R - Cnow.R;
	Matrix<double,3,1> werr = Cnow.R * rot2omega(Rerr);
	Matrix<double,6,1> err;

	err << perr,werr;
	return err;
}

void Kinematics::calcForwardKinematics(int rootlink)
{
	if(rootlink == -1)
		return ;
	if(rootlink != 0)
	{
		int parent = ulink[rootlink].parent;
		ulink[rootlink].p = ulink[parent].R * ulink[rootlink].b + ulink[parent].p;
		ulink[rootlink].R = ulink[parent].R * Rodrigues(ulink[rootlink].a, ulink[rootlink].q);
	}
	calcForwardKinematics(ulink[rootlink].sister);
	calcForwardKinematics(ulink[rootlink].child);
}

bool Kinematics::calcInverseKinematics(int to, Link target)
{
	MatrixXd J, dq;
	Matrix<double,6,1> err;

	ColPivHouseholderQR<MatrixXd> QR; //QR分解?
	const double dampingConstantSqr = 1.0e-12;
	const double lambda = 0.5;
	const int iteration = 100;
	
	calcForwardKinematics(WAIST);
	
	vector<int> idx = FindRoute(to);
	const int jsize = idx.size();
	
	J.resize(6,jsize); dq.resize(jsize,1);

	for(int n=0;n<iteration;n++){
		J = calcJacobian(ulink, idx);
		err = calcVWerr(target, ulink[to]);
		if(err.norm() < eps) return true;

		MatrixXd JJ = J*J.transpose()+dampingConstantSqr*MatrixXd::Identity(J.rows(),J.rows());
		dq = J.transpose() * QR.compute(JJ).solve(err) * lambda;
		
		for(size_t nn=0;nn<jsize;nn++){
			int j = idx[nn];
			ulink[j].q += dq(nn);
		}
		calcForwardKinematics(WAIST);
	}
	return false;
}
