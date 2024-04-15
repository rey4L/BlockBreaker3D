# BlockBreaker3D

This game is designed as a semester project and built with the intention of bringing the clasic block breaker experience from my childhood into a 3D space. 

## Features

- **3D gameplay**: Experience the classic block breaker game in a whole new dimension.

## Setup

This repository uses an environment variable to manage paths in the Visual Studio project file (.vcxproj). This allows each user to have their own local settings without overwriting the settings of others when committing to the repository.

### Step 1: Define Your Environment Variable

On your local machine, define an environment variable named `VS_ENV_VAR` that points to the `Libraries` folder. For example, if you have a directory structure like this:
```
C:\MyProject
│
└───Libraries
    ├───include
    └───lib
```
`C:\MyProject\Libraries` is the directory you need to set the environment variable to.

Here’s how to do it on Windows:

1. Open the Control Panel.
2. In the search bar, type "Edit the system enviroment variables".
3. Click on the result to open the System Properties dialog box.
4. In the System Properties dialog, select the Environment Variables button.
5. Under System Variables, click New.
6. In the dialog that appears, enter `VS_ENV_VAR` as the Variable name and the path to the `Libraries` folder as the Variable value.
7. Confirm your entry by clicking OK.

**Important: The environment variable must be named `VS_ENV_VAR`. If you use a different name, it will overwrite the file and affect other users.**

### Step 2: Restart Visual Studio

After setting the environment variable, restart Visual Studio so it recognizes the new value.

## Acknowledgements

- Special thanks to Victor Gordon, his OpenGL tutorial [videos](<https://www.youtube.com/watch?v=XpBGwZNyUh0&list=PLPaoO-vpZnumdcb4tZc4x5Q-v7CkrQ6M->) were an invaluable resource during development.
- This project was inspired by classic block breaker games (e.g. the one that came preinstalled on old BlackBerry devices) but reimagined in a 3D space.
