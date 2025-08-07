#include "PanelTarget.h"
/////今回回転させたい回転量をクォータニオンで作る
//Quaternion rotPow = Quaternion();
//
//int rot = 0;
//if (goalRot_ == 90.0f)
//{
//	rot = 10;
//	rotPow = rotPow.Mult(
//		Quaternion::AngleAxis(
//			AsoUtility::Deg2RadF(AsoUtility::Deg2RadF(rot)), AsoUtility::AXIS_X
//		));
//}
//else if (goalRot_ == 0.0f)
//{
//	rot = -10;
//	rotPow = rotPow.Mult(
//		Quaternion::AngleAxis(
//			AsoUtility::Deg2RadF(AsoUtility::Deg2RadF(rot)), AsoUtility::AXIS_X
//		));
//}
//
//mRot_ += AsoUtility::Deg2RadF(rot);
//if (mRot_ >= 90.0f && goalRot_ == 90.0f)
//{
//	goalRot_ = 0.0f;
//}
//if (mRot_ <= 0.0f && goalRot_ == 0.0f)
//{
//	goalRot_ = 90.0f;
//}