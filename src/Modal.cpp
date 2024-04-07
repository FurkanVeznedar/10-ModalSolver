#include "Modal.h"

Modal::Modal()
{
}

Modal::~Modal()
{
}

void Modal::GenerateMassMatrix(std::vector<float>& Mass)
{
    int n = Mass.size();
    massmatrix.resize(n, n);
    massmatrix.setZero();
    
    for (int i = 0; i < n; ++i) {
        massmatrix(i, i) = Mass[i];
    }
}

void Modal::GenerateStiffnessMatrix(std::vector<float>& springconstants)
{
    int n = springconstants.size();
    stiffnessmatrix.resize(n, n);
    stiffnessmatrix.setZero();
    
    for (int i = 0; i < n; ++i) {
        stiffnessmatrix(i, i) = springconstants[i];
    }
}

void Modal::Run()
{
    Eigen::GeneralizedSelfAdjointEigenSolver<Eigen::MatrixXd> eigenSolver(stiffnessmatrix, massmatrix);
    if (eigenSolver.info() != Eigen::Success) {
        std::cerr << "Eigen solver failed!" << std::endl;
        return;
    }

    Eigen::VectorXd naturalFrequenciesRadPerSec = eigenSolver.eigenvalues().cwiseSqrt();
    naturalfrequencies = naturalFrequenciesRadPerSec / (2 * m_PI);
    modeshapes = eigenSolver.eigenvectors();
    
}

Eigen::VectorXd Modal::GetNatralFreq()
{
    return naturalfrequencies;
}

Eigen::VectorXd Modal::GetModeShapes()
{
    return modeshapes;
}