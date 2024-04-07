#ifndef _MODAL_H_
#define _MODAL_H_

#include <iostream>
#include <vector>
#include <Eigen/Dense>

const float m_PI = 3.14159265359f;

class Modal
{
private:
    Eigen::MatrixXd massmatrix;
    Eigen::MatrixXd stiffnessmatrix;
    Eigen::VectorXd naturalfrequencies;
    Eigen::MatrixXd modeshapes;
public:
    Modal();
    ~Modal();

    void GenerateMassMatrix(std::vector<float>& Mass);
    void GenerateStiffnessMatrix(std::vector<float>& springonstants);
    void Run();
    
    Eigen::VectorXd GetNatralFreq();
    Eigen::VectorXd GetModeShapes();
};

#endif _MODAL_H_