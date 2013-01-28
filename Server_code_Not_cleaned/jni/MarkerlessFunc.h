#ifndef MARKERLESSFUNC_H
#define MARKERLESSFUNC_H
#include "KeyFrame.h"
bool newLKTrack(Mat & prev,Mat & next,std::vector<Point2f> & prevPts, std::vector<Point2f> & nextPts,double binTh=100.0,Size GaussSize=Size(5,5),double sigma1=1.0,double sigma2=0.0, Size winsize=Size(21,21), int maxLevel=3,TermCriteria criteria=TermCriteria(TermCriteria::COUNT+TermCriteria::EPS,30,0.01),double derivLambda =0.5, int flags=0, double minEigTh=1e-4,double FundConfi=0.99, double FundDist=3.0 );
bool newLKTrack(Mat & prev,Mat & next,std::vector<Point2f> & prevPts, std::vector<Point2f> & nextPts,std::vector<int> & finalGoodIndex,double binTh=100.0,Size GaussSize=Size(5,5),double sigma1=1.0,double sigma2=0.0, Size winsize=Size(21,21), int maxLevel=3,TermCriteria criteria=TermCriteria(TermCriteria::COUNT+TermCriteria::EPS,30,0.01),double derivLambda =0.5, int flags=0, double minEigTh=1e-4,double FundConfi=0.99, double FundDist=3.0 );
bool newLKTrack(Mat & prev,Mat & next,std::vector<Point2f> & prevPts, std::vector<Point2f> & nextPts,std::vector<int> & finalGoodIndex,double binTh=100.0,Size GaussSize=Size(5,5),double sigma1=1.0,double sigma2=0.0, Size winsize=Size(21,21), int maxLevel=3,TermCriteria criteria=TermCriteria(TermCriteria::COUNT+TermCriteria::EPS,30,0.01),double derivLambda =0.5, int flags=0, double minEigTh=1e-4);
bool trackFeatureInKFByNewOpticalflow(KeyFrame & KF,Mat & currentFrame,std::vector<Point3f> & select3f,std::vector<Point2f> & select2f,CVStuff & mCV,double binTh=100.0,Size GaussSize=Size(5,5),double sigma1=1.0,double sigma2=0.0, Size winsize=Size(21,21), int maxLevel=3,TermCriteria criteria=TermCriteria(TermCriteria::COUNT+TermCriteria::EPS,30,0.01),double derivLambda =0.5, int flags=0, double minEigTh=1e-4,double FundConfi=0.99, double FundDist=3.0 );
void LinearSTTriangulation(int numViews,CvMat* & cam_mat,std::vector<CvMat*> &Rots, std::vector<CvMat*> & Trans,std::vector<CvMat*> & ProjMat, std::vector<std::vector<Point2f> > & imgPts, std::vector<Point3f> & WPts);
void LinearSTTriangulation(int numViews,CvMat* & cam_mat,std::vector<CvMat*> &Rots, std::vector<CvMat*> & Trans, std::vector<std::vector<Point2f> > & imgPts, std::vector<Point3f> & WPts);
void IterativeLinearSTTriangulation(int numViews,CvMat* & cam_mat,std::vector<CvMat*> &Rots, std::vector<CvMat*> & Trans, std::vector<std::vector<Point2f> > & imgPts, std::vector<Point3f> & WPts);
int newTriangulationFrom2Views(CvMat* & cam_mat,CvMat* & distort_mat,CvMat* & firstRot,CvMat* & secRot, CvMat* & firstTrans,CvMat* & secTrans,std::vector<Point2f> & imgPts1,std::vector<Point2f> & imgPts2, std::vector<Point2f> & matchPts,std::vector<Point3f> & WPts);
bool FindCamPoseByKFRANSAC(CvMat* camera_matrix,CvMat* distortion_coeffs,std::vector<Point3f> & Pt3Ds, std::vector<Point2f> & imgPts,CvMat* & rot, CvMat* & trans);
void FindCamPoseByKF(const CvMat* camera_matrix,const CvMat* distortion_coeffs,std::vector<Point3f> & Pt3Ds, std::vector<Point2f> & imgPts,CvMat* & rot, CvMat* & trans);
void projectPoints(std::vector<Point3f> & objPts,CvMat* & rot,CvMat* & trans,CvMat* & cam_mat,CvMat* & distort,std::vector<Point2f> & result);
#endif
