#pragma once

struct TechnologySelection {
    unsigned char numberOfRemainingChipTries;
    bool invalidSwipeOccured;
    union ServiceCodeMs* serviceCodeMs;
    bool contactlessAllowed;
    bool showUpfrontButton;
};
