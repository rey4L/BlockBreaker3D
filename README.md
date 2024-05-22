# BlockBreaker3D

BlockBreaker3D is a semester project that brings the classic block breaker game from my childhood into an immersive 3D environment.

## Features

- **Immersive 3D gameplay**: Experience the classic block breaker game in a whole new dimension, complete with realistic sound effects for enhanced immersion.
- **Intuitive interface**: Enjoy a user-friendly GUI that seamlessly integrates score tracking, making it easy to keep track of your progress and aim for high scores.
- **Engaging audio**: Immerse yourself with sound effects for collisions, game over, level resets, and an exquisitely crafted main theme.

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

## Attributions

- Special thanks to Victor Gordon, his [OpenGL tutorial videos](<https://www.youtube.com/watch?v=XpBGwZNyUh0&list=PLPaoO-vpZnumdcb4tZc4x5Q-v7CkrQ6M->) and associated [repo](<https://github.com/VictorGordan/opengl-tutorials>) were an invaluable resource during development.
- The sound effects used are from [pixabay](<https://pixabay.com/sound-effects/>). 
