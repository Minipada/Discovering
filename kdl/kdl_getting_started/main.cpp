#include <iostream>
#include <kdl/chain.hpp>
#include <kdl/chainfksolver.hpp>
#include <kdl/chainfksolverpos_recursive.hpp>
#include <kdl/frames_io.hpp>


class KDL_ {
public:

  double roll = 10, pitch = 20, yaw = 30;
  double alpha = 10, beta = 20, gamma = 30;
  KDL_();   // This is the constructor declaration
  ~KDL_();  // This is the destructor: declaration
  KDL::Vector vector;
  double angle = 15;
  double Xx = 0, Yx = 0, Zx = 0, Xy = 0, Yy = 0, Zy = 0, Xz = 0, Yz = 0, Zz = 0;
  //    KDL::Vector vectorX(1,2,3), vectorY(2,3,4), vectorZ(3,4,5);
  KDL::Vector vectorX, vectorY, vectorZ;
  KDL::Vector v1, v2, v3, v4; //The default constructor, X-Y-Z are initialized to zero

  KDL::Rotation r1, r2, r3, r4, r5, r6, r7;
  KDL::Vector axis;
  KDL::Vector vecX, vecY, vecZ;

  void init_vector();
  void getting_values();
  void rotation();
  void inverting_rotations();
  void composing_rotations();
} kdl;

// Member functions definitions including constructor
KDL_::KDL_(void)
{
  std::cout << "Object is being created" << std::endl;
}

KDL_::~KDL_(void)
{
  std::cout << "Object is being deleted" << std::endl;
}

/*
 * Simple creation of vectors
 * http://www.orocos.org/kdl/usermanual/geometric-primitives
 */
void KDL_::init_vector()
{
  double x = 0, y = 0, z = 0;
  v1 = {0,0,0};
  v2 = {x, y, z}; //X-Y-Z are initialized with the given values
  v3 = v2; //The copy constructor
  v4 = KDL::Vector::Zero(); //All values are set to zero
}

void KDL_::getting_values()
{
  double Zx = r1(0,2); // Individual values, the indices go from 0..2

  // Getting EulerZYZ, Euler ZYX, Roll-Pitch-Yaw angles, equivalent rotation axis with angle
  r1.GetEulerZYZ(alpha,beta,gamma);
  r1.GetEulerZYX(alpha,beta,gamma);
  r1.GetRPY(roll,pitch,yaw);
  axis = r1.GetRot();//gives only rotation axis
  angle = r1.GetRotAngle(axis);//gives both angle and rotation axis

  //Getting the Unit vectors
  vecX=r1.UnitX();//or
  r1.UnitX(vecX);
  vecY=r1.UnitY();//or
  r1.UnitY(vecY);
  vecZ=r1.UnitZ();//or
  r1.UnitZ(vecZ);

}

/*
 * Safe ways to create a KDL::Rotation
 * The following result always in consistent KDL::Rotations.
 * This means the rows/columns are always normalized and orthogonal:
 *
 *
 */
void KDL_::rotation()
{
  r1; //The default constructor, initializes to an 3x3 identity matrix
  r1 = KDL::Rotation::Identity();//Identity KDL::Rotation = zero KDL::Rotation
  r2 = KDL::Rotation::RPY(roll,pitch,yaw); //KDL::Rotation built from Roll-Pitch-Yaw angles
  r3 = KDL::Rotation::EulerZYZ(alpha,beta,gamma); //KDL::Rotation built from Euler Z-Y-Z angles
  r4 = KDL::Rotation::EulerZYX(alpha,beta,gamma); //KDL::Rotation built from Euler Z-Y-X angles
  r5 = KDL::Rotation::Rot(vector,angle); //KDL::Rotation built from an equivalent axis(vector) and an angle.
  r6 = {Xx,Yx,Zx,Xy,Yy,Zy,Xz,Yz,Zz};//Give each individual element (Column-Major)
  r7 = {vectorX,vectorY,vectorZ};//Give each individual column
}


void KDL_::inverting_rotations()
{
  //Replacing a rotation by its inverse
  r1.SetInverse();//r1 is inverted and overwritten

  //Getting the inverse rotation without overwriting the original
  r2=r1.Inverse();//r2 is the inverse rotation of r1
}

void KDL_::composing_rotations()
{
  r3=r1*r2; //Compose two rotations to a new rotation, the order of the rotations is important

  //Compose a rotation with elementary rotations around X-Y-Z
  r1.DoRotX(angle);
  r2.DoRotY(angle);
  r3.DoRotZ(angle);

  //this is the shorthand version of
  r1 = r1*KDL::Rotation::RotX(angle);
}



int main(int argc, char *argv[])
{
  std::cout << "Hello World!" << std::endl;
  return 0;
}
