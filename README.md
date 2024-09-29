# Octave Simulator

## Project Overview

The **Octave Simulator** is a matrix manipulation software inspired by the functionalities of GNU Octave. It allows users to perform a variety of matrix operations through a command-line interface. The program supports loading, printing, transposing, and performing arithmetic operations on matrices, as well as implementing Strassen's algorithm for matrix multiplication.

## Functionalities

### Matrix Operations

1. **Load Matrices**:
   - Users can load matrices into the program by providing the matrix's dimensions and its elements. Each loaded matrix is stored in memory with an associated index.

2. **Print Matrices**:
   - Users can print matrices stored in memory by referencing their index. The program will display the matrix in a readable format.

3. **Transpose Matrices**:
   - The program allows the transposition of matrices, switching rows and columns for the specified matrix index.

4. **Matrix Multiplication**:
   - Implemented using Strassen's algorithm, the software can multiply two square matrices of dimensions that are powers of two. The resulting matrix is stored in memory with a new index.
   - Error handling is in place to ensure that multiplication only occurs for compatible matrices.

5. **Resize Matrices**:
   - Users can resize existing matrices by specifying new dimensions and values. The program dynamically adjusts the matrix size while maintaining its data integrity.

6. **Sort Matrices**:
   - The program can sort matrices in memory based on the sum of their elements, allowing users to easily organize their data.

7. **Power of Matrices**:
   - Users can raise a matrix to a specified power, modifying the matrix in place.

8. **Release Resources**:
   - The program provides an option to deallocate all resources and terminate execution, ensuring proper cleanup of memory.

### Command Handling

- The program processes various commands from standard input, handling recognized commands effectively and providing error messages for unrecognized commands or invalid operations.
- Appropriate error messages are displayed for operations that cannot be performed, such as incompatible matrix dimensions or non-existent matrix indices.

## Conclusion

The project serves as a robust tool for performing matrix operations, supporting both basic functionalities and advanced features like Strassen's algorithm. It aims to provide a user-friendly command-line experience for matrix manipulation and analysis.
