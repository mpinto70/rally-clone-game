#pragma once

#include <vector>

class AnimationSequence {
public:
    AnimationSequence(const char* seqFile);
    virtual ~AnimationSequence();

    bool nextAnimFrame();
    int getCurrFrameDuration();
    virtual void setAnimSeq(unsigned newAnimSeq);
    void resetAnimSeq(unsigned animSeq);

    BITMAP* getFrame(unsigned int frame_idx);

    struct FrameInfoSt {
        int frameNumber;
        int frameDuration;
    };

    std::vector<std::vector<FrameInfoSt>> getAnimSeq();

private:
    void loadSprites(const char* seqFile);
    void loadSequences(const char* seqFile);
    void unload();

    BITMAP* seqBmp;

    unsigned curAnimFrame;
    unsigned curAnimFrameDuration;
    unsigned curAnimSeq;

    std::vector<BITMAP*> seqFrames;
    std::vector<std::vector<FrameInfoSt>> anim_seqs;
};
