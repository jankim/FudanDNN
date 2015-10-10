#include "NonLinearComponent.h"
NonLinearComponent::NonLinearComponent(int visualRow,int visualColumn,int num,int type){
	this->num = num;
	this->type = type;
	this->visualRow = visualRow;
	this->visualColumn = visualColumn;
	this->hiddenRow = visualRow;
	this->hiddenColumn = visualColumn;
}
void NonLinearComponent::gradient(){
	visualGradient.clear();
	//cout << visualGradient.size() << endl;
	for (int i = 0; i < hiddenGradient.size(); i++){
		visualGradient.push_back(hiddenGradient[i]->map(sigmoidDerivative));
	}
	//cout << visualGradient.size() << endl;
	this->hiddenGradient.clear();
}
void NonLinearComponent::compute(){
	hiddenValue.clear();
	for (int i = 0; i < visualValue.size(); i++){
		hiddenValue.push_back(visualValue[i]->map(sigmoid));
	}
}
void NonLinearComponent::calculate(){
	hiddenValue.clear();
	/*for (int i = 0; i < visualValue.size(); i++){
		visualValue[i]->print();
	}*/
	for (int i = 0; i < visualValue.size(); i++){
		hiddenValue.push_back(visualValue[i]->map(sigmoid));
	}
}
void NonLinearComponent::update(){
	visualGradient.clear();
}
void NonLinearComponent::regularize(){

}
