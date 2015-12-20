//  Created by anurag on 11/21/15.
//  Copyright © 2015 anurag. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include "dirent.h"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/nonfree/features2d.hpp"
#include "opencv2/nonfree/nonfree.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/ml/ml.hpp"

using namespace cv;
using namespace std;
/*
 * Enum to define different categories of Input Files
 */
enum ImageClassID {
	Butterfly = 0,
	Car,
	Face,
	Watch,
	Lilly
};

int kVal = 0;
int nVal = 0;

/*
 * Class to store all the information of the images
 */
class ImageDetails {
  public:
	string imagepath;
	Mat img;
	ImageClassID classID;
	vector<KeyPoint> siftKP;
	Mat siftDesc;
	Mat pcaSIFT;
	Mat hist;
};

/*
 * Class to store the histogram distances and the ImageDetails Objects
 */
class ImageDistance {
  public:
	double distance;
	ImageDetails *img;
};

vector<ImageDetails *> trImages;
vector<ImageDetails *> testImages;
map<ImageDetails *,vector<int>> classRanks;
Mat combPCASift;

int numPCAComp = 0;

/*
 * (OBSOLETE) Function to find the PCA-SIFT features of the input image
 */
void doPCA(ImageDetails* &img) {
	const Mat desc = img->siftDesc;
	Mat outMat,covarMean;
	Mat eigenVals,eigenVecs;
	int flags = CV_COVAR_NORMAL | CV_COVAR_ROWS;
	calcCovarMatrix(img->siftDesc, outMat, covarMean, flags, img->siftDesc.type());
	eigen(outMat, eigenVals, eigenVecs);
	
	Mat vecsPreserved(eigenVecs,Range(0, numPCAComp),Range::all());
	img->pcaSIFT = (img->siftDesc)*(vecsPreserved.t());
	
}

/*
 * Function to compute PCA-SIFT features: This function first forms a matrix that contains 
 * all the SIFT features of train+test images. Every row of this matrix represents one
 * SIFT feature. PCA is performed on this matrix to find the principal directions of the
 * entire data set. Using the input parameter, only a defined number of directions are preserved 
 * and the corresponding feature vectors are added to the ImageDetails matrix of the respective
 * image.
 */
void doPCA() {
	Mat desc;
	
	// Form a matrix of SIFT features from all train+test data
	for (int i=0; i<trImages.size(); i++) {
		desc.push_back(trImages[i]->siftDesc);
	}
	for (int i=0; i<testImages.size(); i++) {
		desc.push_back(testImages[i]->siftDesc);
	}
	
	// Compute principal directions and preserve the required number of directions
	Mat outMat,covarMean;
	Mat eigenVals,eigenVecs;
	int flags = CV_COVAR_NORMAL | CV_COVAR_ROWS;
	
	calcCovarMatrix(desc, outMat, covarMean, flags, desc.type());
	eigen(outMat, eigenVals, eigenVecs);
	
	Mat vecsPreserved(eigenVecs,Range(0, numPCAComp),Range::all());
	
	combPCASift = desc*(vecsPreserved.t());
	
	// Store the PCA-SIFT features into corresponding ImageDetails object
	int k = 0;
	for (int i=0; i<trImages.size(); i++) {
		for (int j=0; j<trImages[i]->siftKP.size(); j++) {
			trImages[i]->pcaSIFT.push_back(combPCASift.row(k));
			k++;
		}
	}
	for (int i=0; i<testImages.size(); i++) {
		for (int j=0; j<testImages[i]->siftKP.size(); j++) {
			testImages[i]->pcaSIFT.push_back(combPCASift.row(k));
			k++;
		}
	}
	
}

/*
 * Function to read the images into the ImageDetails Object and calculate 
 * SIFT features.
 * INPUT PARAMETERS:
 * cat_name = directory path input class
 * cat_type = input class type
 * dataType = train/test
 */
void loadCat(const char *cat_name, ImageClassID catType, string dataType) {
	DIR *dir;
	struct dirent *ent;
	
	// Loop through all files in the input directory
	if ((dir = opendir(cat_name)) != NULL) {
  
		while ((ent = readdir(dir)) != NULL) {
			string fileName(cat_name);
			fileName += "/";
			fileName += ent->d_name;
			
			if (fileName.find(".jpg") != string::npos) {
				// Build the image details object
				ImageDetails *newImg = new ImageDetails();
				newImg->imagepath = fileName;
				newImg->img = imread(fileName,CV_LOAD_IMAGE_GRAYSCALE);
				newImg->classID = catType;
				
				// Compute SIFT features
				SIFT sift;
				sift(newImg->img, cv::noArray(), newImg->siftKP, newImg->siftDesc, false);
				
				// Store the ImageDetails object in the appropriate global vector
				if (!dataType.compare("train")) {
					trImages.push_back(newImg);
				} else {
					testImages.push_back(newImg);
				}
			}
		}
		closedir (dir);
	} else {
		cout << "Could not open Directory";
	}
}

/*
 * Function to read all images from a directory
 * INPUT PARAMETERS
 * argv = path of the root directory
 * dataType = test/train
 */
void loadImages(const char * argv[], string dataType) {
	string root(argv[1]);
	string dirName = "";
	
	dirName = root+"/butterfly/"+dataType;
	loadCat(dirName.c_str(),Butterfly,dataType);
	
	dirName = root+"/car_side/"+dataType;
	loadCat(dirName.c_str(),Car,dataType);
	
	dirName = root+"/faces/"+dataType;
	loadCat(dirName.c_str(),Face,dataType);
	
	dirName = root+"/watch/"+dataType;
	loadCat(dirName.c_str(),Watch,dataType);
	
	dirName = root+"/water_lilly/"+dataType;
	loadCat(dirName.c_str(),Lilly,dataType);
}

/*
 * Function to compute histograms for test/train images
 * INPUT PARAMETERS:
 * bestLabels = Each row of this matrix determines the cluster id of the
 *				closest cluster
 * imageDetails = array of test/train ImageDetail objects
 */
void computeHistograms(Mat bestLabels, vector<ImageDetails *> &imageDetals) {
	cout << "Computing histograms" << endl;
	int k = 0;
	for (int i=0; i<imageDetals.size(); i++) {
		Mat histVec(1,kVal,4);
		
		for (int j=0; j<kVal; j++) {
			histVec.at<int>(0, j) = 0;
		}
		
		for (int j=0; j<imageDetals[i]->siftKP.size(); j++) {
			histVec.at<int>(0,bestLabels.at<int>(k,0)) = histVec.at<int>(0,bestLabels.at<int>(k,0))+1;
			k++;
		}
		
		imageDetals[i]->hist = histVec;
	}
}

/*
 * Function to perform Kmeans on training data
 * OUTPUT DETAILS:
 * centers = Matrix of the vectors of centers of clusters from Kmeans
 */
Mat doKMeans() {
	Mat inMat;
	Mat bestLabels;
	Mat centers;
	
	// Load all PCA-SIFT features of the training images into a single matrix
	for (int i=0; i<trImages.size(); i++) {
		inMat.push_back(trImages[i]->pcaSIFT);
	}
	
	// OpenCV funciton to perform Kmeans
	kmeans(inMat, kVal, bestLabels, TermCriteria(CV_TERMCRIT_EPS+CV_TERMCRIT_ITER, 10, 1.0), 10, KMEANS_RANDOM_CENTERS,centers);
	
	// Compute histograms for training data
	computeHistograms(bestLabels,trImages);
	
	return centers;

}

/*
 * Function to find the closest cluster centers for testing data
 */
void findTestCenters(Mat &centers) {
	Mat bestLabels;
	
	// Loop over all PCA-SIFT features of test images
	for (int i=0; i<testImages.size(); i++) {
		for (int j=0; j<testImages[i]->siftKP.size(); j++) {
			Mat temp(1,1,4);
			
			// Find the closest cluster using euclidean distance from centers
			double minDist = norm(centers.row(0),testImages[i]->pcaSIFT.row(j),NORM_L2);
			int minIndex = 0;
			
			for (int k=1; k<centers.rows; k++) {
				double dist = norm(centers.row(k),testImages[i]->pcaSIFT.row(j),NORM_L2);
				if (dist < minDist) {
					minDist = dist;
					minIndex = k;
				}
			}
			temp.at<int>(0,0) = minIndex;
			bestLabels.push_back(temp);
		}
	}
	
	// Compute histograms for training images
	computeHistograms(bestLabels, testImages);
}

/*
 * Custom sort function to sort ImageDistance objects
 */
bool sortFunc(ImageDistance *i, ImageDistance *j) {
	return (i->distance < j->distance);
}

/*
 * Function to find the rank of classes given scores
 */
void findRanks(vector<int> &ranks, vector<double> &scores) {
	// Create an ordered map to loop in increasing order of keys
	map<double,int> tempMap;
	for (int i=0; i<scores.size(); i++) {
		if (scores[i] >0) {
			tempMap[scores[i]] = i;
		}
	}
	
	int j = (int)tempMap.size();
	
	for (map<double,int>::iterator it=tempMap.begin(); it!=tempMap.end(); ++it) {
		ranks[it->second] = j;
		j--;
	}
}

/*
 * Function to classify using own implementation of K Nearest neighbors
 * INPUT PARAMETERS:
 * opt(2) = classify using summation of inverse eucledean distance
 * opt(3) = classify using novel weighted voting Gou et. all
 */
void classify(int opt) {
	vector<vector<int>> confusionMat(5,vector<int>(5,0));
	
	for (int i=0; i<testImages.size(); i++) {
		vector<ImageDistance *> distVec;
		
		for (int j=0; j<trImages.size(); j++) {
			ImageDistance *iDist = new ImageDistance;
			iDist->distance = norm(testImages[i]->hist,trImages[j]->hist,NORM_L2);
			iDist->img = trImages[j];
			distVec.push_back(iDist);
		}
		
		sort(distVec.begin(), distVec.end(), sortFunc);
		
		vector<double> scores(5,-1.0);
		
		if (opt == 2) {
			for (int j=0; j<nVal; j++) {
				if (scores[distVec[j]->img->classID] < 0) {
					scores[distVec[j]->img->classID] = 1/distVec[j]->distance;
				} else {
					scores[distVec[j]->img->classID] += (1/distVec[j]->distance);
				}
			}
		} else {
			for (int j=0; j<nVal; j++) {
				if (scores[distVec[j]->img->classID] < 0) {
					scores[distVec[j]->img->classID] = ((distVec[nVal-1]->distance) - (distVec[j]->distance))/(((distVec[nVal-1]->distance) - (distVec[0]->distance))*(j+1));
				} else {
					scores[distVec[j]->img->classID] += ((distVec[nVal-1]->distance) - (distVec[j]->distance))/(((distVec[nVal-1]->distance) - (distVec[0]->distance))*(j+1));;
				}
			}
		}
		
		vector<int> ranks(5,0);
		findRanks(ranks,scores);
		
		classRanks[testImages[i]] = ranks;
	}
	
	for (int i=0; i<testImages.size(); i++) {
		for (int j=0; j<5; j++) {
			if (classRanks[testImages[i]][j] == 1) {
				confusionMat[testImages[i]->classID][j]++;
			}
		}
	}
	
	cout << "Confusion Matrix: \n";
	for (int i=0; i<confusionMat.size(); i++) {
		for (int j=0; j<confusionMat[i].size(); j++) {
			cout << confusionMat[i][j] << " ";
		}
		cout << endl;
	}
	
	
}

/*
 * Function to classify using OpenCV's built-in K nearest neighbor API
 */
void classify() {
	CvKNearest knn;
	vector<vector<int>> confusionMat(5,vector<int>(5,0));
	Mat trainData,responses;
	
	vector<int> randomArray;
	
	for (int i=0; i<trImages.size(); i++) {
		randomArray.push_back(i);
	}
	random_shuffle(randomArray.begin(), randomArray.end());
	
	for (int i=0; i<trImages.size(); i++) {
		Mat tempRow(1,trImages[i]->hist.cols,CV_32FC1);
		for (int j=0; j<trImages[i]->hist.cols; j++) {
			tempRow.at<float>(0,j) = (float) trImages[randomArray[i]]->hist.at<int>(0, j);
		}
		trainData.push_back(tempRow);
		
		Mat tempResp(1,1,CV_32F);
		tempResp.at<float>(0, 0) = (float) trImages[randomArray[i]]->classID;
		responses.push_back(tempResp);
	}
	knn.train(trainData, responses);
	
	
	
	for (int i=0; i<testImages.size(); i++) {
		Mat tempRow(1,testImages[i]->hist.cols,CV_32FC1);
		for (int j=0; j<testImages[i]->hist.cols; j++) {
			tempRow.at<float>(0,j) = (float) testImages[i]->hist.at<int>(0, j);
		}
		
		float result = knn.find_nearest(tempRow, nVal);
		confusionMat[testImages[i]->classID][(int)result]++;
	}
	
	cout << "Confusion Matrix:\n";
	for (int i=0; i<5; i++) {
		for (int j=0; j<5; j++) {
			cout << confusionMat[i][j] << " ";
		}
		cout << endl;
	}
}

int main(int argc, const char * argv[]) {
	numPCAComp = atoi(argv[2]);
	kVal = atoi(argv[3]);
	nVal = atoi(argv[4]);
	int opt = atoi(argv[5]);
	string train = "train";
	string test = "test";
	
	cout << "Loading training Images" << endl;
	loadImages(argv,train);
	
	cout << "Loading test Images" << endl;
	loadImages(argv,test);
	
	cout << "Performing PCA" << endl;
	doPCA();

	cout << "Performing K Means" << endl;
	Mat kMeansCenters = doKMeans();
	
	cout << "Finding closest Cluster centers" << endl;
	findTestCenters(kMeansCenters);
	
	if (opt == 1) {
		classify();
	} else {
		classify(opt);
	}
	
    return 0;
}
