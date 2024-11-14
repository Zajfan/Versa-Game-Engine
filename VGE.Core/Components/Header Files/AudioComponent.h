#ifndef AUDIOCOMPONENT_H
#define AUDIOCOMPONENT_H

#include "NodeComponent.h"

class AudioComponent : public NodeComponent
{
public:
    AudioComponent(Node* owner);

    // Properties specific to audio (e.g., sound file, volume, pitch)
    // ...

    // Methods for playing sounds, controlling audio, etc.
    // ...
};

#endif // AUDIOCOMPONENT_H#pragma once
