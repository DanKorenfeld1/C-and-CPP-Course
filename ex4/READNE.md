# MLP Network for Digit Recognition

This project implements a Multi-Layer Perceptron (MLP) neural network for digit recognition using C++. The network is designed to process 28x28 pixel images and classify them into digits (0-9).

## Project Structure

The project consists of several key components:

- `Matrix`: A custom matrix class for efficient matrix operations.
- `Activation`: Implements activation functions (ReLU and Softmax).
- `Dense`: Represents a single dense layer in the neural network.
- `MlpNetwork`: The main class that combines multiple dense layers to form the complete neural network.

## Key Files

- `Matrix.h`: Defines the Matrix class with various matrix operations.
- `Activation.h`: Contains ReLU and Softmax activation functions.
- `Dense.h`: Implements a single dense layer of the neural network.
- `MlpNetwork.h`: Defines the structure of the entire MLP network.
- `main.cpp`: The entry point of the program, handling user input and network execution.

## Usage

To use the MLP network:

1. Compile the project using a C++ compiler (C++11 or later).
2. Run the executable with the following command-line arguments:
   ```
   ./mlpnetwork w1 w2 w3 w4 b1 b2 b3 b4
   ```
   Where:
   - `wi` are paths to weight matrices for each layer
   - `bi` are paths to bias vectors for each layer

3. Once running, the program will prompt you to enter the path to an image file.
4. The program will process the image and output the recognized digit along with the confidence probability.
5. Enter 'q' to quit the program.

## Network Architecture

The MLP network consists of 4 dense layers with the following dimensions:

- Input layer: 784 neurons (28x28 pixel image flattened)
- Hidden layer 1: 128 neurons
- Hidden layer 2: 64 neurons
- Hidden layer 3: 20 neurons
- Output layer: 10 neurons (one for each digit 0-9)

## Dependencies

This project uses standard C++ libraries and does not require any external dependencies.

## Error Handling

The program includes robust error handling for various scenarios, including:
- Invalid command-line arguments
- Issues with loading weight and bias files
- Problems with image input


