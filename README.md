A project made back in 2021 consisting of a gyroscopic motion controller, designed to accompany its own arcade flight game.
Tilting the controller forward or backward controlled vertical motion, while tilting it sideways controlled horizontal motion.
Another button was used for recalibrating the controller, which had to be done frequently due to the motion sensor's low quality.

Note: this was a past learning experience and does not represent the way I currently write code.

Subsystems:
* test: Contains "SquareDemo.exe" used for testing the controller's calibration by rotating a cube.
* device: Controller code
* src: Game code


Hardware:
* [Teensy 4.1 Development Board](https://www.pjrc.com/teensy/) A tiny, cheap, powerful board compatible with the Arduino toolchain.
* MPU 6050 Motion Sensor

The other components of the controller came from a Freenove starter kit.

Libraries used:
* Arduino standard library
* [raylib](https://github.com/raysan5/raylib): Graphics rendering for the game
* [entt](https://github.com/skypjack/entt): ECS for use in the game

![What it looks like](https://github.com/Tonycons-dev/motion-project-2021/blob/main/photo.png)  
