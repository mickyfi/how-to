/* This is an example how to add additional evaluation metrics to GraphLab Create using the SDK.
In this example, we developed seven evaluation metrics function for binary classifier. 
These functions get as input two SArrays with actual and predicted classifier values, and the label of the positive class, 
and are able to calculate the classifier's: true-positive (TP), False-Positive (FP),True-Negative (TN),false-negative (FN), precision score, recall score, and f1 score.

The file can be complied by using the following command:
g++ -std=c++11 metrics.cpp -I <graphlab-sdk directory> -shared -fPIC -o metrics.so

After compilation the file can be loaded to Python using the following line:
>>> import metrics

Python Code Example:
>>> import graphlab
>>> import metrics


>>> actual = graphlab.SArray([1,1,0,0,0])
>>> predicted = graphlab.SArray([0,1,0,0,1])
>>> metrics.true_positive(actual,predicted, 1) #1
>>> metrics.false_positive(actual,predicted, 1) # 1
>>> metrics.true_negative(actual,predicted, 1) # 2
>>> metrics.false_negative(actual,predicted, 1) # 2

>>> actual = graphlab.SArray(['a','b','a','a','a','b'])
>>> predicted = graphlab.SArray(['a','a','b','b','b','a'])
>>> metrics.true_positive(actual,predicted, 'a') # 1
>>> metrics.false_positive(actual,predicted, 'a') # 2
>>> metrics.true_negative(actual,predicted, 'a') # 0
>>> metrics.false_negative(actual,predicted, 'a') # 3


For more details please read:
https://dato.com/products/create/sdk/docs/index.html
https://github.com/dato-code/GraphLab-Create-SDK


Written by: Michael Fire
*/

#include <graphlab/sdk/toolkit_function_macros.hpp>
#include <graphlab/sdk/gl_sarray.hpp>
using namespace graphlab;
int true_positive(gl_sarray actual, gl_sarray predicted, flexible_type pos_label) {		
	if(actual.size() != predicted.size())
	{
		throw "Error: Cannot calculate True-Positive. Input arrays of different size";
	}	
	int tp = 0;
	for(int i=0;i<actual.size(); i++)
	{
		if(actual[i] == pos_label && actual[i] == predicted[i])
		{
			tp += 1;
		}
		
	}
	return tp;
}

int false_positive(gl_sarray actual, gl_sarray predicted, flexible_type pos_label) {		
	if(actual.size() != predicted.size())
	{
		throw "Error: Cannot calculate False-Positive. Input arrays of different size";
	}	
	int fp = 0;
	for(int i=0;i<actual.size(); i++)
	{
		if(predicted[i] == pos_label && actual[i] != pos_label)
		{
			fp += 1;
		}
		
	}
	return fp;
}

int true_negative(gl_sarray actual, gl_sarray predicted, flexible_type pos_label) {		
	if(actual.size() != predicted.size())
	{
		throw "Error: Cannot calculate True-Negative. Input arrays of different size";
	}	
	int tn = 0;
	for(int i=0;i<actual.size(); i++)
	{
		if(predicted[i] != pos_label && actual[i] != pos_label)
		{
			tn += 1;
		}
		
	}
	return tn;
}

int false_negative(gl_sarray actual, gl_sarray predicted, flexible_type pos_label) {		
	if(actual.size() != predicted.size())
	{
		throw "Error: Cannot calculate False-Negative. Input arrays of different size";
	}	
	int fn = 0;
	for(int i=0;i<actual.size(); i++)
	{
		if(predicted[i] != pos_label && actual[i] == pos_label)
		{
			fn += 1;
		}
		
	}
	return fn;
}

float precision_score(gl_sarray actual, gl_sarray predicted, flexible_type pos_label) {		
	float tp = (float) true_positive(actual,predicted,pos_label);
	float fp = (float) false_positive(actual,predicted,pos_label);
	return tp/(tp + fp);
}

float recall_score(gl_sarray actual, gl_sarray predicted, flexible_type pos_label) {		
	float tp = (float) true_positive(actual,predicted,pos_label);
	float fn = (float) false_negative(actual,predicted,pos_label);
	return tp/(tp + fn);
}

float f1_score(gl_sarray actual, gl_sarray predicted, flexible_type pos_label) {		
	float recall = recall_score(actual,predicted,pos_label);
	float precision = precision_score(actual,predicted,pos_label);
	return (2 * (precision * recall)) / (precision + recall);
}


BEGIN_FUNCTION_REGISTRATION
REGISTER_FUNCTION(true_positive, "actual", "predicted", "pos_label"); // provide named parameters
REGISTER_FUNCTION(false_positive, "actual", "predicted", "pos_label"); // provide named parameters
REGISTER_FUNCTION(true_negative, "actual", "predicted", "pos_label"); // provide named parameters
REGISTER_FUNCTION(false_negative, "actual", "predicted", "pos_label"); // provide named parameters
REGISTER_FUNCTION(precision_score, "actual", "predicted", "pos_label"); // provide named parameters
REGISTER_FUNCTION(recall_score, "actual", "predicted", "pos_label"); // provide named parameters
REGISTER_FUNCTION(f1_score, "actual", "predicted", "pos_label"); // provide named parameters
END_FUNCTION_REGISTRATION

