#ifndef __FUDANDNN_CONTRACTIVEAUTOENCODER_H
#define __FUDANDNN_CONTRACTIVEAUTOENCODER_H
#include "utils.h"
#include "AutoEncoder.h"
#include "NonLinearLayer.h"
#include "NonLinearFactory.h"
#include "XMLDataParser.h"

class ContractiveAutoEncoder : public AutoEncoder
{
public:
	ContractiveAutoEncoder(size_t visualUnit, size_t hiddenUnit, int init_scheme, size_t nonlinearType,
		size_t jacobiPenalty);
	ContractiveAutoEncoder() {};
	string getNetworkName() override;
	size_t getJacobiPenalty();
	void setJacobiPenalty(size_t jacobiPenalty);
	void singleTraining(shared_ptr<AbstractMatrix> v);
protected:
	size_t jacobiPenalty;
};
#endif