#ifndef MOUSEREADING_H
#define MOUSEREADING_H
struct MouseReading
{
    float xPressed, yPressed, xReleased, yReleased;
    bool pressedDone = false, releasedDone = false; // Used as a handshake
};
#endif // MOUSEREADING_H
