## Using GPIO
- 02 : 5V power : RED(MOTOR)
- 09 : Ground : BROWN(MOTOR)
- 35 : GPIO 19 : ORANGE(MOTOR)

## Camera.cpp
- [OpenCV]
sudo apt install libopencv-dev
sudo apt install cmake


## Moter.cpp
### Module
- [pigpio](https://qiita.com/fujita06/items/ca265fd4aa8f9474d966)
```
sudo apt-get install pigpio
sudo systemctl start pigpiod
sudo systemctl enable pigpiod
```

- [Wiring Pi]
```
sudo apt-get install libi2c-dev
sudo apt-get install git-core
cd ~
git clone https://github.com/WiringPi/WiringPi.git
cd WiringPi
./build
```

## Parts
- [Moter(SG90)](https://servodatabase.com/servo/towerpro/sg90)

