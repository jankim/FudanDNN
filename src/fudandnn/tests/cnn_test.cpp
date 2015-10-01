#include "boost/test/unit_test.hpp"
#include "fudandnn/core/MasterControl.h"

BOOST_AUTO_TEST_SUITE(CNNTest)

BOOST_AUTO_TEST_CASE(LeNetTest) {
	MasterControl *master = new MasterControl();
	size_t cnnId = master->addCNN();
	//size_t kernelSize, size_t stride,size_t featureMapNum, size_t num, size_t visualRow, size_t visualColumn, size_t scheme
	size_t id1 = master->addCNN2DComponentToCNN(1, 1, 6, 1, 28, 28, 0, cnnId);
	size_t nonLinear1 = master->addNonLinearToCNN(28,28,6,0, cnnId);
	size_t pooling1 = master->addMaxPoolingComponentToCNN(2, 2, 28, 28, cnnId);

	size_t id2 = master->addCNN2DComponentToCNN(5, 1, 16, 6, 14, 14, 0, cnnId);
	size_t nonLinear2 = master->addNonLinearToCNN(10,10,16,0, cnnId);
	size_t pooling2 = master->addMaxPoolingComponentToCNN(2, 2, 10, 10, cnnId);

	size_t id3 = master->addCNN2DComponentToCNN(5, 1, 120, 16, 5, 5, 0, cnnId);
	size_t nonLinear3 = master->addNonLinearToCNN(1,1,120,0, cnnId);

	size_t cnnEdge1 = master->addEdgeInCNN(id1, nonLinear1, cnnId);
	size_t cnnEdge2 = master->addEdgeInCNN(nonLinear1,pooling1,cnnId);
	size_t cnnEdge3 = master->addEdgeInCNN(pooling1, id2, cnnId);

	size_t cnnEdge4 = master->addEdgeInCNN(id2, nonLinear2, cnnId);
	size_t cnnEdge5 = master->addEdgeInCNN(nonLinear2,pooling2,cnnId);
	size_t cnnEdge6 = master->addEdgeInCNN(pooling2, id3, cnnId);

	size_t cnnEdge7 = master->addEdgeInCNN(id3, nonLinear3, cnnId);

	size_t inputId = master->addInput("dataset/temp.xml");
	master->addInputEdge(inputId, cnnId);

	size_t layer1 = master->addLINEAR(120, 84, 0);
	size_t non1 = master->addNONLINEAR(84, 0);
	size_t layer2 = master->addLINEAR(84, 10, 0);
	size_t non2 = master->addNONLINEAR(10, 0);

	master->addEdge(cnnId, layer1);
	master->addEdge(layer1, non1);
	master->addEdge(non1, layer2);
	master->addEdge(layer2, non2);

	master->setCriteria(0, 10);
	master->setTrainingTimes(10000);
	master->setBatchSize(1);
	master->run();
}

BOOST_AUTO_TEST_SUITE_END()