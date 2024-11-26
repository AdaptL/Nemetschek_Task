# C++ Project Setup for Visual Studio 2022 (C++14)

This repository contains a C++ project set up for use in Visual Studio 2022 with the C++14 standard (ISO/IEC 14882:2014). This guide will walk you through the process of setting up the project in your local environment.

## Prerequisites

Before you start, ensure that you have the following software installed:

- [Visual Studio 2022](https://visualstudio.microsoft.com/vs/)
  - Make sure to include the **Desktop development with C++** workload during installation.
  
- **C++14 Standard** (ISO/IEC 14882:2014)

## Getting Started

Follow these steps to set up the project:

### 1. Clone the Repository

First, clone this repository to your local machine using Git.

```bash
git clone https://github.com/AdaptL/Nemetschek_Task.git
cd your-repository
```
### 2. Open the Project in Visual Studio 2022

1. Launch **Visual Studio 2022**.
2. Go to `File` -> `Open` -> `Project/Solution`.
3. Navigate to the project directory and open the `.sln` (solution) file.

### 3. Set the C++ Standard to C++14

By default, Visual Studio 2022 may not use the C++14 standard. To ensure your project uses C++14, follow these steps:

1. In Visual Studio, go to `Project` -> `Properties`.
2. Under the **Configuration Properties** section, select `C/C++` -> `Language`.
3. Set **C++ Language Standard** to `ISO C++14 Standard (/std:c++14)`.

### 4. Build the Project

1. In Visual Studio, go to `Build` -> `Build Solution` (or press `Ctrl+Shift+B`).
2. Visual Studio will now compile the project using the C++14 standard.

### 5. Run the Project

Once the build process is complete, you can run the project:

- Click on `Debug` -> `Start Debugging` (or press `F5`) to run the project in debug mode.
- Alternatively, use `Ctrl+F5` to run without debugging.

