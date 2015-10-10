#include "MasterControl.h"
#include "boost/lexical_cast.hpp"

size_t MasterControl::addRBM(size_t visualUnit, size_t hiddenUnit, size_t initScheme,
	size_t type, bool sparse, size_t batchSize, size_t preTrainingTimes, size_t nonLinearType){
	shared_ptr<RBM> rbm;
	switch (type){
	case Type::RBM:
		rbm = shared_ptr<RBM>(new RBM(visualUnit, hiddenUnit, nonLinearType, sparse, initScheme));
		rbm->setSelfBatchSize(batchSize);
		break;
	default:
		rbm = shared_ptr<RBM>(new RBM(visualUnit, hiddenUnit, nonLinearType, sparse, initScheme));
		rbm->setSelfBatchSize(batchSize);
		break;
	}
	shared_ptr<NetworkNode> node (new NetworkNode(currentId, rbm));
	idMap.insert(Node_Pair(currentId, node));
	currentId++;
	nodes.push_back(node);
	return node->getId();
}

size_t MasterControl::addAutoEncoder(size_t visualUnit, size_t hiddenUnit, size_t initScheme,
	size_t batchSize, size_t preTrainingTimes, size_t nonLinearType){
	shared_ptr<AutoEncoder> autoencoder;
	autoencoder = shared_ptr<AutoEncoder>(new AutoEncoder(visualUnit, hiddenUnit, initScheme, nonLinearType));
	autoencoder->setSelfBatchSize(batchSize);
	autoencoder->setPreTrainingTime(preTrainingTimes);
	shared_ptr<NetworkNode> node(new NetworkNode(currentId, autoencoder));
	idMap.insert(Node_Pair(currentId, node));
	currentId++;
	nodes.push_back(node);
	return node->getId();
}

size_t MasterControl::addSparseAutoEncoder(size_t visualUnit, size_t hiddenUnit, size_t init_scheme,
	size_t nonlinearType, size_t sparseRate, size_t sparsePercent, size_t preTrainingTimes, size_t batchSize){
	shared_ptr<SparseAutoEncoder> autoencoder;
	autoencoder =shared_ptr<SparseAutoEncoder>(new SparseAutoEncoder(visualUnit, hiddenUnit, init_scheme,
		nonlinearType, sparseRate, sparsePercent));
	autoencoder->setSelfBatchSize(batchSize);
	autoencoder->setPreTrainingTime(preTrainingTimes);
	shared_ptr<NetworkNode> node (new NetworkNode(currentId, autoencoder));
	idMap.insert(Node_Pair(currentId, node));
	currentId++;
	nodes.push_back(node);
	return node->getId();
}

size_t MasterControl::addContractiveAutoEncoder(size_t visualUnit, size_t hiddenUnit, size_t init_scheme,
	size_t nonlinearType, size_t jacobiPenalty, size_t preTrainingTimes, size_t batchSize){
	shared_ptr<ContractiveAutoEncoder> autoencoder;
	autoencoder =shared_ptr<ContractiveAutoEncoder>(new ContractiveAutoEncoder(visualUnit, hiddenUnit, init_scheme,
		nonlinearType, jacobiPenalty));
	autoencoder->setSelfBatchSize(batchSize);
	autoencoder->setPreTrainingTime(preTrainingTimes);
	shared_ptr<NetworkNode> node (new NetworkNode(currentId, autoencoder));
	idMap.insert(Node_Pair(currentId, node));
	currentId++;
	nodes.push_back(node);
	return node->getId();
}

size_t MasterControl::addDenoiseAutoEncoder(size_t visualUnit, size_t hiddenUnit, size_t init_scheme,
	size_t nonlinearType, size_t clearRate, size_t preTrainingTimes, size_t batchSize){
	shared_ptr<DenoiseAutoEncoder> autoencoder;
	autoencoder = shared_ptr<DenoiseAutoEncoder>(new DenoiseAutoEncoder(visualUnit, hiddenUnit, init_scheme,
		nonlinearType, clearRate));
	autoencoder->setSelfBatchSize(batchSize);
	autoencoder->setPreTrainingTime(preTrainingTimes);
	shared_ptr<NetworkNode> node (new NetworkNode(currentId, autoencoder));
	idMap.insert(Node_Pair(currentId, node));
	currentId++;
	nodes.push_back(node);
	return node->getId();
}

size_t MasterControl::addCNN(size_t dimension, size_t kernelSize, size_t stride,
	size_t featureMapNum, size_t type){

	return 0;
}

size_t MasterControl::addInput(string file){
	shared_ptr<Input> input (new Input(file, currentId));
	inputMap.insert(Input_Pair(currentId, input));
	currentId++;
	inputs.push_back(input);
	return input->getId();
}

size_t MasterControl::addLINEAR(size_t visualUnit, size_t hiddenUnit, size_t init_scheme){
	shared_ptr<LinearLayer> linearLayer;
	linearLayer = shared_ptr<LinearLayer>(new LinearLayer(visualUnit, hiddenUnit, init_scheme));
	shared_ptr<NetworkNode> node (new NetworkNode(currentId, linearLayer));
	idMap.insert(Node_Pair(currentId, node));
	currentId++;
	nodes.push_back(node);
	return node->getId();
}

size_t MasterControl::addNONLINEAR(size_t visualUnit, size_t type){
	shared_ptr<NonLinearLayer> nonlinearLayer;
	shared_ptr<NonLinearFactory> factory (new NonLinearFactory());
	nonlinearLayer = factory->createNonLinear(type, visualUnit);
	shared_ptr<NetworkNode> node (new NetworkNode(currentId, nonlinearLayer));
	idMap.insert(Node_Pair(currentId, node));
	currentId++;
	nodes.push_back(node);
	return node->getId();
}

size_t MasterControl::addEdge(size_t inID, size_t outID){
	shared_ptr<NetworkNode> inNode = idMap.find(inID)->second;
	shared_ptr<NetworkNode> outNode = idMap.find(outID)->second;
	inNode->addNextNode(outNode);
	outNode->addBeforeNode(inNode);
	return 0;
}

size_t MasterControl::addInputEdge(size_t inputID, size_t outID){
	shared_ptr<NetworkNode> outNode = idMap.find(outID)->second;
	outNode->addInput(inputMap.find(inputID)->second);
	inputMap.find(inputID)->second->setNodeId(outID);
	return 0;
}

size_t MasterControl::addCNN(){
	shared_ptr<ConvolutionalNetworkLayer> cnn;
	cnn = shared_ptr<ConvolutionalNetworkLayer>(new ConvolutionalNetworkLayer());
	shared_ptr<NetworkNode> node (new NetworkNode(currentId, cnn));
	idMap.insert(Node_Pair(currentId, node));
	currentId++;
	nodes.push_back(node);
	return node->getId();
}

size_t MasterControl::addCNN2DComponentToCNN(size_t kernelSize, size_t stride, size_t featureMap_Num,
	size_t num, size_t visualRow, size_t visualColumn, size_t scheme, size_t cnnId){
	shared_ptr<NetworkNode> node = idMap.find(cnnId)->second;
	shared_ptr<ConvolutionalNetworkLayer> cnn = dynamic_pointer_cast<ConvolutionalNetworkLayer>(node->getLayer());
	return cnn->addCNN2DComponentToCNN(kernelSize, stride, featureMap_Num, num,
		visualRow, visualColumn, scheme);
}

size_t MasterControl::addMaxPoolingComponentToCNN(size_t poolingSize, size_t stride,
	size_t visualRow, size_t visualColumn, size_t num, size_t cnnId){
	shared_ptr<NetworkNode> node = idMap.find(cnnId)->second;
	shared_ptr<ConvolutionalNetworkLayer> cnn = dynamic_pointer_cast<ConvolutionalNetworkLayer>(node->getLayer());
	return cnn->addMaxPoolingToCNN(poolingSize, stride, visualRow, visualColumn,num);
}

size_t MasterControl::addNonLinearToCNN(int visualRow, int visualColumn, size_t num, size_t type, size_t cnnId){
	shared_ptr<NetworkNode> node = idMap.find(cnnId)->second;
	shared_ptr<ConvolutionalNetworkLayer> cnn = dynamic_pointer_cast<ConvolutionalNetworkLayer>(node->getLayer());
	return cnn->addNonLinearToCNN(visualRow,visualColumn, num, type);
}

size_t MasterControl::addEdgeInCNN(size_t inId, size_t outId, size_t cnnId){
	shared_ptr<NetworkNode> node = idMap.find(cnnId)->second;
	shared_ptr<ConvolutionalNetworkLayer> cnn = dynamic_pointer_cast<ConvolutionalNetworkLayer>(node->getLayer());
	return cnn->addEdgeInCNN(inId, outId);
}

size_t MasterControl::setCriteria(size_t type, size_t unitNum){
	this->criteria =shared_ptr<MSE>( new MSE(unitNum));
	return 0;
}

void MasterControl::setTrainingTimes(size_t trainingTimes){
	this->trainingTimes = trainingTimes;
}

void MasterControl::setBatchSize(size_t batchSize)
{
	this->batchSize = batchSize;
}

void MasterControl::run()
{
	topoSort();
	//preTraining();
	size_t times = 0;
	size_t sampleNum = inputs[0]->getSampleNum();
	double error = 0;
	double norm2 = 0;
	int correctNum = 0;
	while (times < trainingTimes)
	{
		times++;
		bool match = true;
		shared_ptr<AbstractMatrix> expectedOutput = nullptr;

		for (shared_ptr<NetworkNode> node : nodes)
		{
			size_t id = node->getId();

			shared_ptr<AbstractLayer> layer = node->getLayer();

			shared_ptr<AbstractMatrix> visualValue = nullptr;
			for (shared_ptr<NetworkNode> pred : node->getBeforeNode())
			{
				if (visualValue == nullptr){
					visualValue = pred->getLayer()->getHiddenValue();
				}
				else{
					visualValue = visualValue->mergeRow(pred->getLayer()->getHiddenValue());
				}
			}

			if (node->getInput() != nullptr)
			{
				if (node->getInput()->isEnd())
				{

					for (shared_ptr<NetworkNode> node : nodes)
					{
						shared_ptr<AbstractLayer> layer = node->getLayer();
						shared_ptr<AbstractNetworkLayer> networkLayer = dynamic_pointer_cast<AbstractNetworkLayer>(layer);
						if (networkLayer)
							networkLayer->update();
					}

				}
				shared_ptr<Sample> sample = node->getInput()->getNextSample();
				if (visualValue == nullptr){
					visualValue = sample->getInput();
				}
				else{
					visualValue = visualValue->mergeRow(sample->getInput());
				}
				if (nullptr == expectedOutput)
				{
					expectedOutput = sample->getOutput();
				}
				else
				{
					if (!expectedOutput->equals(sample->getOutput()))
					{
						match = false;
						break;
					}
				}
			}

			layer->setVisualValue(visualValue);
			layer->calculate();
		}

		if (!match)
		{
			continue;
		}

		shared_ptr<AbstractLayer> lastLayer = nodes.at(nodes.size() - 1)->getLayer();

		criteria->setExpectedValue(expectedOutput);
		criteria->setPredictValue(lastLayer->getHiddenValue());
		double singleError=criteria->computeError();
		criteria->gradient();
		if (criteria->getPredictType() == criteria->getExpectedType()){
			correctNum++;
		}
		//criteria->getPredictValue()->print();
		error += singleError;
		//cout << "error:" << singleError << endl;
		norm2 += criteria->getPredictGradient()->norm2();
		if (times%sampleNum == 0){
			cout << "times: " << times << "   error: " << error << "   correctNum:" << correctNum << endl;
			error = 0;
			norm2 = 0;
			correctNum = 0;
		}
		//criteria->getPredictGradient()->print();
		//criteria->getPredictGradient()->print();
		lastLayer->setHiddenGradient(criteria->getPredictGradient());
		for (int i = nodes.size() - 1; i >= 0; i--)
		{
			shared_ptr<NetworkNode> node = nodes.at(i);
			size_t id = node->getId();

			shared_ptr<AbstractLayer> layer = node->getLayer();

			layer->gradient();

			size_t preLength = 0;
			size_t currLength = 0;

			for (shared_ptr<NetworkNode> pred : node->getBeforeNode())
			{
				shared_ptr<AbstractLayer> predLayer = pred->getLayer();
				currLength = predLayer->getHiddenValue()->getRowSize();
				predLayer->setHiddenGradient(layer->getVisualGradient()->submatrix(preLength, preLength + currLength, 0, 1));
				preLength += currLength;
			}

			if (node->getInput() != nullptr) 
			{
				currLength = layer->getVisualGradient()->getRowSize();
				node->getInput()->setGradient(layer->getVisualGradient());
			}

		}

		if (times % batchSize == 0) {
			for (shared_ptr<NetworkNode> node : nodes)
			{
				shared_ptr<AbstractLayer> layer = node->getLayer();
				shared_ptr<AbstractNetworkLayer> networkLayer = dynamic_pointer_cast<AbstractNetworkLayer>(layer);
				if (networkLayer != nullptr)
				{
					networkLayer->update();
				}
			}
		}

	}


}

void MasterControl::preTraining()
{
	for (shared_ptr<Input> input : inputs){
		shared_ptr<NetworkNode> node = idMap.find(input->getNodeId())->second;
		shared_ptr<AbstractLayer> layer = node->getLayer();
		shared_ptr<RBM> rbm = dynamic_pointer_cast<RBM>(layer);
		shared_ptr<AutoEncoder> ae = dynamic_pointer_cast<AutoEncoder>(layer);
		if (rbm != NULL){
			for (size_t i = 0; i < rbm->getSelfTrainingTime(); i++)
			{
				shared_ptr<Sample> sample = nullptr;
				size_t index = 0;
				while (!input->isEnd())
				{
					sample = input->getNextSample();
					index++;
					rbm->singleTraining(sample->getInput());
					if (index % rbm->getSelfBatchSize() == 0)
						rbm->selfUpdate(false);
				}
				rbm->selfUpdate(true);
			}
		}
		else if (ae != NULL){
			for (size_t i = 0; i < ae->getPreTrainingTime(); i++)
			{
				shared_ptr<Sample> sample = nullptr;
				size_t index = 0;
				while (!input->isEnd())
				{
					sample = input->getNextSample();
					index++;
					ae->singleTraining(sample->getInput());
					if (index % ae->getSelfBatchSize() == 0)
						ae->selfUpdate(false);
				}
				ae->selfUpdate(true);
			}
		}
		else{
			continue;
		}
		vector<shared_ptr<NetworkNode>> nextNodes;
		while ((nextNodes = node->getNextNode()).size() != 0){
			shared_ptr<NetworkNode> nextNode = nextNodes[0];

			shared_ptr<AbstractLayer> layer = nextNode->getLayer();

			shared_ptr<RBM> rbm = dynamic_pointer_cast<RBM>(layer);
			shared_ptr<AutoEncoder> ae = dynamic_pointer_cast<AutoEncoder>(layer);

			if (rbm != NULL){
				shared_ptr<Sample> sample = nullptr;
				size_t index = 0;
				while (!input->isEnd())
				{
					sample = input->getNextSample();
					caculateFromTop(nextNode, sample->getInput());
					rbm->singleTraining(nextNode->getLayer()->getVisualValue());
					if (index % rbm->getSelfBatchSize() == 0)
						rbm->selfUpdate(false);
				}
			}
			else if (ae != NULL){
				shared_ptr<Sample> sample = nullptr;
				size_t index = 0;
				while (!input->isEnd())
				{
					sample = input->getNextSample();
					caculateFromTop(nextNode, sample->getInput());
					ae->singleTraining(nextNode->getLayer()->getVisualValue());
					if (index % ae->getSelfBatchSize() == 0)
						ae->selfUpdate(false);
				}
			}
			else{
				break;
			}
			node = node->getNextNode()[0];
		}
	}
}

void MasterControl::caculateFromTop(shared_ptr<NetworkNode> node, shared_ptr<AbstractMatrix> matrix){
	if (node->getInput() == nullptr){
		caculateFromTop(node->getBeforeNode()[0], matrix);
		shared_ptr<AbstractLayer> layer = node->getLayer();
		shared_ptr<AbstractLayer> previousLayer = node->getBeforeNode()[0]->getLayer();
		layer->setVisualValue(previousLayer->getHiddenValue());
		layer->calculate();
	}
	else{
		shared_ptr<AbstractLayer> layer = node->getLayer();
		layer->setVisualValue(matrix);
		layer->calculate();
	}
}

bool MasterControl::saveToConfig(string path){
	return true;
}

void MasterControl::topoSort()
{

	for (shared_ptr<NetworkNode> node : nodes)
	{
		vector<shared_ptr<NetworkNode>> beforeNodes = node->getBeforeNode();
		this->inDegreeMap.insert(InDegree_Pair(node->getId(), beforeNodes.size()));
	}

	size_t i = 0;
	size_t size = nodes.size();
	while (i < size)
	{
		size_t inDegree_i = inDegreeMap.find(nodes[i]->getId())->second;
		if (inDegree_i == 0)
		{
			for (shared_ptr<NetworkNode> succ : nodes[i]->getNextNode())
			{
				size_t succId = succ->getId();
				size_t in_d = inDegreeMap.find(succId)->second - 1;
				inDegreeMap.erase(succId);
				inDegreeMap.insert(InDegree_Pair(succId, in_d));
			}
			i++;
			continue;
		}

		size_t j = i + 1;
		while (j < size)
		{
			size_t inDegree_j = inDegreeMap.find(nodes[i]->getId())->second;
			if (inDegree_j == 0)
			{
				break;
			}
			j++;
		}

		shared_ptr<NetworkNode> tmp = nodes[i];
		nodes[i] = nodes[j];
		nodes[j] = tmp;

	}

}

bool MasterControl::checkNetwork()
{
	if (inputs.size() == 0){
		return false;
	}
	if (criteria == nullptr){
		return false;
	}
	for (shared_ptr<NetworkNode> node : nodes)
	{
		shared_ptr<AbstractLayer> layer = node->getLayer();
		size_t predTotalInputSize = 0;
		for (shared_ptr<NetworkNode> pred : node->getBeforeNode())
		{
			shared_ptr<AbstractLayer> predLayer = pred->getLayer();
			predTotalInputSize += predLayer->getHiddenUnit();
		}
		if (layer->getHiddenUnit() != predTotalInputSize)
			return false;
	}
	return true;
}

void MasterControl::writeSelf(string filename)
{

	ofstream fout(filename, ios::out);

	fout << nodes.size();
	for (size_t i = 0; i < nodes.size(); i++)
	{
		fout << nodes.at(i)->getLayer()->getNetworkName() << '\n';
		for (size_t j = 0; j < nodes.at(i)->getNextNode().size(); j++)
		{
			fout << nodes.at(i)->getNextNode().at(j)->getId() << '\n';
		}
		fout << '\n';
		nodes.at(i)->getLayer()->writeSelf(boost::lexical_cast<string>(i));
	}

	fout << criteria->getType();
	criteria->writeSelf("criteria");

	fout.close();

}

void MasterControl::readSelf(string filename)
{

	ifstream fin(filename, ios::in);

	int size;
	fin >> size;

	for (size_t i = 0; i < size; i++)
	{

		string name_s;
		fin >> name_s;
		const char *name = name_s.c_str();

		if (strcmp(name, "AutoEncoder") == 0)
		{
			shared_ptr<AbstractLayer> network (new AutoEncoder());
			network->readSelf(boost::lexical_cast<string>(i));
			nodes.push_back(shared_ptr<NetworkNode>(new NetworkNode(i, network)));
		}
		else if (strcmp(name, "RBM") == 0)
		{
			shared_ptr<AbstractLayer> network (new RBM());
			network->readSelf(boost::lexical_cast<string>(i));
			nodes.push_back(shared_ptr<NetworkNode>(new NetworkNode(i, network)));
		}
		else if (strcmp(name, "Linear") == 0)
		{
			shared_ptr<AbstractLayer> network (new LinearLayer());
			network->readSelf(boost::lexical_cast<string>(i));
			nodes.push_back(shared_ptr<NetworkNode>(new NetworkNode(i, network)));
		}
		else if (strcmp(name, "ContractiveAutoEncoder") == 0)
		{
			shared_ptr<AbstractLayer> network (new ContractiveAutoEncoder());
			network->readSelf(boost::lexical_cast<string>(i));
			nodes.push_back(shared_ptr<NetworkNode>(new NetworkNode(i, network)));
		}
		else if (strcmp(name, "DenoiseAutoEncoder") == 0)
		{
			shared_ptr<AbstractLayer> network (new DenoiseAutoEncoder());
			network->readSelf(boost::lexical_cast<string>(i));
			nodes.push_back(shared_ptr<NetworkNode>(new NetworkNode(i, network)));
		}
		else if (strcmp(name, "HardShrink") == 0)
		{
			shared_ptr<AbstractLayer> network (new HardShrink());
			network->readSelf(boost::lexical_cast<string>(i));
			nodes.push_back(shared_ptr<NetworkNode>(new NetworkNode(i, network)));
		}
		else if (strcmp(name, "HardTanH") == 0)
		{
			shared_ptr<AbstractLayer> network (new HardTanH());
			network->readSelf(boost::lexical_cast<string>(i));
			nodes.push_back(shared_ptr<NetworkNode>(new NetworkNode(i, network)));
		}
		else if (strcmp(name, "LogSigmoid") == 0)
		{
			shared_ptr<AbstractLayer> network (new LogSigmoid());
			network->readSelf(boost::lexical_cast<string>(i));
			nodes.push_back(shared_ptr<NetworkNode>(new NetworkNode(i, network)));
		}
		else if (strcmp(name, "PReLU") == 0)
		{
			shared_ptr<AbstractLayer> network (new PReLU());
			network->readSelf(boost::lexical_cast<string>(i));
			nodes.push_back(shared_ptr<NetworkNode>(new NetworkNode(i, network)));
		}
		else if (strcmp(name, "ReLU") == 0)
		{
			shared_ptr<AbstractLayer> network (new ReLU());
			network->readSelf(boost::lexical_cast<string>(i));
			nodes.push_back(shared_ptr<NetworkNode>(new NetworkNode(i, network)));
		}
		else if (strcmp(name, "Sigmoid") == 0)
		{
			shared_ptr<AbstractLayer> network (new Sigmoid());
			network->readSelf(boost::lexical_cast<string>(i));
			nodes.push_back(shared_ptr<NetworkNode>(new NetworkNode(i, network)));
		}
		else if (strcmp(name, "SoftShrink") == 0)
		{
			shared_ptr<AbstractLayer> network (new SoftShrink());
			network->readSelf(boost::lexical_cast<string>(i));
			nodes.push_back(shared_ptr<NetworkNode>(new NetworkNode(i, network)));
		}
		else if (strcmp(name, "SparseAutoEncoder") == 0)
		{
			shared_ptr<AbstractLayer> network (new SparseAutoEncoder());
			network->readSelf(boost::lexical_cast<string>(i));
			nodes.push_back(shared_ptr<NetworkNode>(new NetworkNode(i, network)));
		}

	}

	string cType_s;
	fin >> cType_s;
	const char *cType= cType_s.c_str();
	if (strcmp(cType, "MSE") == 1)
	{
		criteria = shared_ptr<MSE>(new MSE());
		criteria->readSelf("criteria");
	}

	fin.close();

}