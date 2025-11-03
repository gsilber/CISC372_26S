#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// XOR dataset
#define N 4     // number of samples
#define IN 2    // input size
#define H  4    // hidden layer size
#define OUT 1   // output size
#define EPOCHS 1000
#define LR 0.1f

// Activation function
float sigmoid(float x) { return 1.0f / (1.0f + expf(-x)); }
float dsigmoid(float y) { return y * (1.0f - y); }

void init_weights(float *w, int size) {
    for (int i = 0; i < size; i++) {
        w[i] = ((float) rand() / RAND_MAX - 0.5f) * 2.0f;
    }
}

int main() {
    float X[N][IN] = {{0,0},{0,1},{1,0},{1,1}};
    float Y[N][OUT] = {{0},{1},{1},{0}};

    float W1[IN*H], b1[H];
    float W2[H*OUT], b2[OUT];
    init_weights(W1, IN*H);
    init_weights(b1, H);
    init_weights(W2, H*OUT);
    init_weights(b2, OUT);

    for (int epoch = 0; epoch < EPOCHS; epoch++) {
        float loss = 0.0f;
        for (int n = 0; n < N; n++) {
            // ---------- Forward Pass ----------
            float hidden[H], hidden_act[H];
            for (int j = 0; j < H; j++) {
                hidden[j] = b1[j];
                for (int i = 0; i < IN; i++)
                    hidden[j] += X[n][i] * W1[i*H + j];
                hidden_act[j] = sigmoid(hidden[j]);
            }
            // CUDA HINT: This is a matrix-vector multiply (X[n] × W1).
            // Map each hidden neuron j to a thread. Use shared memory if batching.

            float out[OUT], out_act[OUT];
            for (int k = 0; k < OUT; k++) {
                out[k] = b2[k];
                for (int j = 0; j < H; j++)
                    out[k] += hidden_act[j] * W2[j*OUT + k];
                out_act[k] = sigmoid(out[k]);
            }
            // CUDA HINT: Another matrix-vector multiply (hidden × W2).
            // Each output neuron k can be computed by one thread.

            // ---------- Loss ----------
            for (int k = 0; k < OUT; k++) {
                float err = Y[n][k] - out_act[k];
                loss += err * err;
            }
            // CUDA HINT: Loss accumulation can use parallel reduction.

            // ---------- Backpropagation ----------
            float delta_out[OUT];
            for (int k = 0; k < OUT; k++) {
                float err = Y[n][k] - out_act[k];
                delta_out[k] = err * dsigmoid(out_act[k]);
            }
            // CUDA HINT: Element-wise ops → trivially parallel.

            float delta_hidden[H];
            for (int j = 0; j < H; j++) {
                float err = 0.0f;
                for (int k = 0; k < OUT; k++)
                    err += delta_out[k] * W2[j*OUT + k];
                delta_hidden[j] = err * dsigmoid(hidden_act[j]);
            }
            // CUDA HINT: Each hidden neuron j can be a thread.
            // Use shared memory to accumulate contributions from outputs.

            // ---------- Weight Updates ----------
            for (int j = 0; j < H; j++) {
                for (int k = 0; k < OUT; k++)
                    W2[j*OUT + k] += LR * delta_out[k] * hidden_act[j];
            }
            for (int k = 0; k < OUT; k++)
                b2[k] += LR * delta_out[k];
            // CUDA HINT: Parallelize across weight matrix W2.

            for (int i = 0; i < IN; i++) {
                for (int j = 0; j < H; j++)
                    W1[i*H + j] += LR * delta_hidden[j] * X[n][i];
            }
            for (int j = 0; j < H; j++)
                b1[j] += LR * delta_hidden[j];
            // CUDA HINT: Parallelize across W1 updates.
            // Watch out for race conditions if batching—may need atomics or reduction.
        }

        if (epoch % 100 == 0)
            printf("Epoch %d, Loss=%.4f\n", epoch, loss/N);
    }
    return 0;
}
