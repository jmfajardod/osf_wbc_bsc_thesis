#pragma once

#include <iostream> 
#include <algorithm> 
#include <Eigen/Dense>
#include <math.h> 
#include <vector>

#include <dart/dart.hpp>
#include <dart/gui/osg/osg.hpp>
#include <dart/utils/urdf/urdf.hpp>
#include <dart/utils/utils.hpp>

namespace effort_tasks {

/*!
 * Class containing the Effort Task Algorithms
 */
class EffortTask {
public:
	/*!
	 * Constructor.
	 */
	EffortTask();

	/*!
	 * Destructor.
	 */
	virtual ~EffortTask();

    /*!
	 * Function to change the gains of the controller
     * KP_C and KD_C are the cartesian gains
     * KP_J and KD_J are the joint gains
	 */
	//void changeGains(double kp_c, double kd_c, double kp_j, double kd_j);

    /*!
	 * Function to change the maximum linear velocity of the end effector
	 */
    void changeMaxVel(double new_max_vel);

    /*!
	 * Function to change the joint margin for avoding joint limits
	 */
    void changeJointMargin(double new_margin);

    /*!
	 * Function to change the eta in FIRAS function for avoding joint limits
	 */
    void change_etaFIRAS(double new_eta);

    /*!
	 * Function to change the higher threshold for singularities
	 */
    void changeHighThSing(double new_high_thr);

    /*!
	 * Function to change the lower threshold for singularities
	 */
    void changeLowThSing(double new_low_thr);

    /***********************************************************************************/
    /***********************************************************************************/
    // Joint Tasks

    /*!
     * Effort Task
     * Hold/ Achieve a Joint Configuration
    */
    void AchieveJointConf(  Eigen::VectorXd q_desired, 
                            Eigen::MatrixXd M, 
                            Eigen::VectorXd C_t,
                            Eigen::VectorXd g_t,
                            dart::dynamics::SkeletonPtr mRobot,
                            dart::dynamics::BodyNode* mEndEffector,
                            Eigen::VectorXd *tau_total,
                            Eigen::MatrixXd *Null_space_iter);

    /*!
     * Effort Task
     * Avoid Joint Limits
    */
    void AvoidJointLimits(Eigen::MatrixXd M, 
                        Eigen::VectorXd C_t,
                        Eigen::VectorXd g_t,
                        dart::dynamics::SkeletonPtr mRobot,
                        dart::dynamics::BodyNode* mEndEffector,
                        Eigen::VectorXd *tau_total,
                        Eigen::MatrixXd *Null_space_iter);

    /***********************************************************************************/
    /***********************************************************************************/
    // Position tasks

    /*******************************************************/
    // Mobile manipulator tasks

    /*!
     * Effort Task
     * Cartesian Impedance for Position
    */
    void CartesianImpedance(  Eigen::Vector3d mTargetPos, 
                              Eigen::Vector3d mTargetVel,
                              Eigen::Vector3d mTargetAccel, 
                              double *svd_position,
                              Eigen::VectorXd tau_ext,
                              Eigen::MatrixXd M, 
                              Eigen::VectorXd C_t,
                              Eigen::VectorXd g_t,
                              dart::dynamics::SkeletonPtr mRobot,
                              dart::dynamics::BodyNode* mEndEffector,
                              Eigen::VectorXd *tau_total,
                              Eigen::MatrixXd *Null_space_iter);

    /*!
     * Effort Task
     * Hold/ Achieve a Cartesian Position
    */
    void AchieveCartesian(  Eigen::Vector3d mTargetPos, 
                            Eigen::Vector3d mTargetVel,
                            Eigen::Vector3d mTargetAccel, 
                            double *svd_position,
                            Eigen::MatrixXd M, 
                            Eigen::VectorXd C_t,
                            Eigen::VectorXd g_t,
                            dart::dynamics::SkeletonPtr mRobot,
                            dart::dynamics::BodyNode* mEndEffector,
                            Eigen::VectorXd *tau_total,
                            Eigen::MatrixXd *Null_space_iter);

    /*!
     * Effort Task
     * Go to a desired position with constant vel
    */
    void AchieveCartesianConstVel(  Eigen::Vector3d mTarget, 
                                    double *svd_position,
                                    Eigen::MatrixXd M,
                                    Eigen::VectorXd C_t,
                                    Eigen::VectorXd g_t,
                                    dart::dynamics::SkeletonPtr mRobot,
                                    dart::dynamics::BodyNode* mEndEffector,
                                    Eigen::VectorXd *tau_total,
                                    Eigen::MatrixXd *Null_space_iter);

    /*******************************************************/
    // Mobile robot tasks

    /*!
     * Effort Task
     * Tasks using only the DOF of the mobile robot
    */

    void AchieveCartesianMobilRob( Eigen::Vector3d mTargetPos, 
                                    Eigen::Vector3d mTargetVel,
                                    Eigen::Vector3d mTargetAccel, 
                                    double *svd_position,
                                    Eigen::MatrixXd M, 
                                    Eigen::VectorXd C_t,
                                    Eigen::VectorXd g_t,
                                    dart::dynamics::SkeletonPtr mRobot,
                                    dart::dynamics::BodyNode* mEndEffector,
                                    Eigen::VectorXd *tau_total,
                                    Eigen::MatrixXd *Null_space_iter);

    void AchieveCartesianMobilRobConstVel(  Eigen::Vector3d mTargetPos,
                                            double *svd_position,
                                            Eigen::MatrixXd M, 
                                            Eigen::VectorXd C_t,
                                            Eigen::VectorXd g_t,
                                            dart::dynamics::SkeletonPtr mRobot,
                                            dart::dynamics::BodyNode* mEndEffector,
                                            Eigen::VectorXd *tau_total,
                                            Eigen::MatrixXd *Null_space_iter);

    /*******************************************************/
    // Manipulator tasks

    /*!
     * Effort Task
     * Tasks using only the DOF of the manipulator
    */

    void AchieveCartesianManipulator(Eigen::Vector3d mTargetPos, 
                                    Eigen::Vector3d mTargetVel,
                                    Eigen::Vector3d mTargetAccel, 
                                    double *svd_position,
                                    Eigen::MatrixXd M, 
                                    Eigen::VectorXd C_t,
                                    Eigen::VectorXd g_t,
                                    dart::dynamics::SkeletonPtr mRobot,
                                    dart::dynamics::BodyNode* mEndEffector,
                                    Eigen::VectorXd *tau_total,
                                    Eigen::MatrixXd *Null_space_iter);

    void AchieveCartManipulatorConstVel(Eigen::Vector3d mTarget, 
                                        double *svd_position,
                                        Eigen::MatrixXd M, 
                                        Eigen::VectorXd C_t,
                                        Eigen::VectorXd g_t,
                                        dart::dynamics::SkeletonPtr mRobot,
                                        dart::dynamics::BodyNode* mEndEffector,
                                        Eigen::VectorXd *tau_total,
                                        Eigen::MatrixXd *Null_space_iter);

    void AchievePosZ( Eigen::Vector3d mTargetPos, 
                      Eigen::Vector3d mTargetVel,
                      Eigen::Vector3d mTargetAccel, 
                      double *svd_position,
                      Eigen::MatrixXd M, 
                      Eigen::VectorXd C_t,
                      Eigen::VectorXd g_t,
                      dart::dynamics::SkeletonPtr mRobot,
                      dart::dynamics::BodyNode* mEndEffector,
                      Eigen::VectorXd *tau_total,
                      Eigen::MatrixXd *Null_space_iter);

    void AchievePosZConstVel( Eigen::Vector3d mTarget,
                              double *svd_position, 
                              Eigen::MatrixXd M, 
                              Eigen::VectorXd C_t,
                              Eigen::VectorXd g_t,
                              dart::dynamics::SkeletonPtr mRobot,
                              dart::dynamics::BodyNode* mEndEffector,
                              Eigen::VectorXd *tau_total,
                              Eigen::MatrixXd *Null_space_iter);


    /***********************************************************************************/
    /***********************************************************************************/
    // Orientation tasks

    /*******************************************************/
    // Mobile manipulator tasks

    /*!
     * Effort Task
     * Orientation Impedance
    */
    void OrientationImpedance(Eigen::Matrix3d rot_mat_desired, 
                              Eigen::Vector3d mTargetVel,
                              Eigen::Vector3d mTargetAccel,
                              double *svd_orientation,
                              Eigen::VectorXd tau_ext,
                              Eigen::MatrixXd M,
                              Eigen::VectorXd C_t,
                              Eigen::VectorXd g_t,
                              dart::dynamics::SkeletonPtr mRobot,
                              dart::dynamics::BodyNode* mEndEffector,
                              Eigen::VectorXd *tau_total,
                              Eigen::MatrixXd *Null_space_iter);

    /*!
     * Effort Task
     * Hold/ Achieve an Orientation
    */
    void AchieveOrientation(Eigen::Matrix3d rot_mat_desired, 
                            Eigen::Vector3d mTargetVel,
                            Eigen::Vector3d mTargetAccel,
                            double *svd_orientation,
                            Eigen::MatrixXd M,
                            Eigen::VectorXd C_t,
                            Eigen::VectorXd g_t,
                            dart::dynamics::SkeletonPtr mRobot,
                            dart::dynamics::BodyNode* mEndEffector,
                            Eigen::VectorXd *tau_total,
                            Eigen::MatrixXd *Null_space_iter);

    /*!
     * Effort Task
     * Go to a desired orientation with constant vel
    */
    void AchieveOrientationConstVel(Eigen::Matrix3d rot_mat_desired,
                                    double *svd_orientation,
                                    Eigen::MatrixXd M,
                                    Eigen::VectorXd C_t,
                                    Eigen::VectorXd g_t,
                                    dart::dynamics::SkeletonPtr mRobot,
                                    dart::dynamics::BodyNode* mEndEffector,
                                    Eigen::VectorXd *tau_total,
                                    Eigen::MatrixXd *Null_space_iter);

    /*******************************************************/
    // Manipulator tasks

    void AchieveOriManipulator( Eigen::Matrix3d rot_mat_desired, 
                                Eigen::Vector3d mTargetVel,
                                Eigen::Vector3d mTargetAccel,
                                double *svd_orientation,
                                Eigen::MatrixXd M,
                                Eigen::VectorXd C_t,
                                Eigen::VectorXd g_t,
                                dart::dynamics::SkeletonPtr mRobot,
                                dart::dynamics::BodyNode* mEndEffector,
                                Eigen::VectorXd *tau_total,
                                Eigen::MatrixXd *Null_space_iter);

    void AchieveOriManipulatorConstVel( Eigen::Matrix3d rot_mat_desired, 
                                        double *svd_orientation,
                                        Eigen::MatrixXd M,
                                        Eigen::VectorXd C_t,
                                        Eigen::VectorXd g_t,
                                        dart::dynamics::SkeletonPtr mRobot,
                                        dart::dynamics::BodyNode* mEndEffector,
                                        Eigen::VectorXd *tau_total,
                                        Eigen::MatrixXd *Null_space_iter);


    /*******************************************************/
    // Error Functions

    Eigen::Vector3d ErrorAngleAxis1(Eigen::Matrix3d rot_mat_desired, 
                                    dart::dynamics::SkeletonPtr mRobot,
                                    dart::dynamics::BodyNode* mEndEffector);

    Eigen::Vector3d ErrorAngleAxis2(Eigen::Matrix3d rot_mat_desired, 
                                    dart::dynamics::SkeletonPtr mRobot,
                                    dart::dynamics::BodyNode* mEndEffector);

    Eigen::Vector3d ErrorQuaternion1(Eigen::Matrix3d rot_mat_desired, 
                                    dart::dynamics::SkeletonPtr mRobot,
                                    dart::dynamics::BodyNode* mEndEffector);

    Eigen::Vector3d ErrorQuaternion2(Eigen::Matrix3d rot_mat_desired, 
                                    dart::dynamics::SkeletonPtr mRobot,
                                    dart::dynamics::BodyNode* mEndEffector);

    Eigen::Vector3d ErrorQuaternion3(Eigen::Matrix3d rot_mat_desired, 
                                    dart::dynamics::SkeletonPtr mRobot,
                                    dart::dynamics::BodyNode* mEndEffector);

    /***********************************************************************************/
    /***********************************************************************************/
    // Miscellaneous functions

    Eigen::MatrixXd calcInertiaMatrix(Eigen::MatrixXd Alpha_inv, double* min_svd);

    void calcInertiaMatrixHandling( Eigen::MatrixXd Alpha_inv,
                                    double* min_svd,
                                    double* act_param,
                                    Eigen::MatrixXd *Alpha_ns,
                                    Eigen::MatrixXd *Alpha_s,
                                    Eigen::MatrixXd *Alpha_s_dummy);

    Eigen::MatrixXd calcDampingMatrix(Eigen::MatrixXd Alpha, 
                                      Eigen::MatrixXd Stiffness, 
                                      Eigen::MatrixXd DampingCoeff);

    /***********************************************************************************/
    /***********************************************************************************/
    // Public variables

    bool compensate_topdown;
    bool compensate_jtspace;
    bool augmented_projections;

private:

    Eigen::MatrixXd kp_cartesian_;
    Eigen::MatrixXd kd_cartesian_;
    Eigen::MatrixXd kp_joints_;
    Eigen::MatrixXd kd_joints_;

    double max_lineal_vel_;
    double max_angular_vel_;

    double joint_margin_;
    double eta_firas_;

    double singularity_thres_high_;
    double singularity_thres_low_;

    int ori_error_mode;

};

} /* namespace */
