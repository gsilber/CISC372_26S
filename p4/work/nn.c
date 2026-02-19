#include "config.h"
#include "file.h"

static float trainSamples[TRAIN_SAMPLE_COUNT][TRAIN_SAMPLE_SIZE];
static int   trainLabels[TRAIN_SAMPLE_COUNT];


void train(){
	loadData(FEATURE_FILE, (float**)trainSamples, LABEL_FILE, trainLabels, TRAIN_SAMPLE_COUNT);
	// init_weights();
	// trainNetwork();
	// saveModel();
}

void infer(){
	// loadModel();
	// predict();
}

int main(int argc, char** argv) {
	train();
	// infer();
	return 0;
}