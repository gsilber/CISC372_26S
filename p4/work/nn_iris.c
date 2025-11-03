#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "iris.h"

#define N 150    // number of samples in Iris
#define IN 4     // input features (sepal length/width, petal length/width)
#define H  8     // hidden layer size (tunable)
#define OUT 3    // output classes (Setosa, Versicolor, Virginica)
#define EPOCHS 50000
#define LR 0.05f

// Activation functions
float sigmoid(float x) { return 1.0f / (1.0f + expf(-x)); }
float dsigmoid(float y) { return y * (1.0f - y); }

// Softmax for output layer
void softmax(float *z, float *out, int len) {
    float max = z[0];
    for (int i = 1; i < len; i++) if (z[i] > max) max = z[i];
    float sum = 0.0f;
    for (int i = 0; i < len; i++) { out[i] = expf(z[i] - max); sum += out[i]; }
    for (int i = 0; i < len; i++) out[i] /= sum;
}

// One-hot labels: Y[n][OUT] = {1,0,0}, {0,1,0}, or {0,0,1}
extern const float X[N][IN];
extern const float Y[N][OUT];

// Initialize weights
void init_weights(float *w, int size) {
    for (int i = 0; i < size; i++)
        w[i] = ((float) rand() / RAND_MAX - 0.5f) * 2.0f;
}

int main() {
    // TODO: Load Iris dataset into X and Y arrays (normalized features, one-hot labels)

    float W1[IN*H], b1[H];
    float W2[H*OUT], b2[OUT];
    init_weights(W1, IN*H);
    init_weights(b1, H);
    init_weights(W2, H*OUT);
    init_weights(b2, OUT);

    for (int epoch = 0; epoch < EPOCHS; epoch++) {
        float loss = 0.0f;
        for (int n = 0; n < N; n++) {
            // ---------- Forward ----------
            float hidden[H], hidden_act[H];
            for (int j = 0; j < H; j++) {
                hidden[j] = b1[j];
                for (int i = 0; i < IN; i++)
                    hidden[j] += X[n][i] * W1[i*H + j];
                hidden_act[j] = sigmoid(hidden[j]);
            }

            float out[OUT], out_act[OUT];
            for (int k = 0; k < OUT; k++) {
                out[k] = b2[k];
                for (int j = 0; j < H; j++)
                    out[k] += hidden_act[j] * W2[j*OUT + k];
            }
            softmax(out, out_act, OUT);

            // ---------- Loss (cross-entropy) ----------
            for (int k = 0; k < OUT; k++) {
                loss -= Y[n][k] * logf(out_act[k] + 1e-8f);
            }

            // ---------- Backprop ----------
            float delta_out[OUT];
            for (int k = 0; k < OUT; k++)
                delta_out[k] = (Y[n][k] - out_act[k]); // derivative of CE+softmax

            float delta_hidden[H];
            for (int j = 0; j < H; j++) {
                float err = 0.0f;
                for (int k = 0; k < OUT; k++)
                    err += delta_out[k] * W2[j*OUT + k];
                delta_hidden[j] = err * dsigmoid(hidden_act[j]);
            }

            // ---------- Update ----------
            for (int j = 0; j < H; j++)
                for (int k = 0; k < OUT; k++)
                    W2[j*OUT + k] += LR * delta_out[k] * hidden_act[j];
            for (int k = 0; k < OUT; k++)
                b2[k] += LR * delta_out[k];

            for (int i = 0; i < IN; i++)
                for (int j = 0; j < H; j++)
                    W1[i*H + j] += LR * delta_hidden[j] * X[n][i];
            for (int j = 0; j < H; j++)
                b1[j] += LR * delta_hidden[j];
        }

        if (epoch % 50 == 0)
            printf("Epoch %d, Loss=%.4f\n", epoch, loss/N);
    }

    return 0;
}
