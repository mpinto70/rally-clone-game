#pragma once

#include <vector>

class IAnimSequence {
    public:
        IAnimSequence(const char * seqFile);
        virtual ~IAnimSequence();

        bool nextAnimFrame();
        int getCurrFrameDuration();
        virtual void setAnimSeq(unsigned newAnimSeq);
        void resetAnimSeq(unsigned animSeq);

        BITMAP * getFrame(unsigned int frame_idx);

        std::vector<std::vector<FrameInfoSt>> getAnimSeq();

    private:
        struct FrameInfoSt {
            int frameNumber;
            int frameDuration;
        };

        void loadSprites(const char * seqFile);
        void loadSequences(const char * seqFile);
        void unload();

        BITMAP * seqBmp;

        unsigned curAnimFrame;
        unsigned curAnimFrameDuration;
        unsigned curAnimSeq;

        std::vector<BITMAP *> seqFrames;
        std::vector<std::vector<FrameInfoSt> > anim_seqs;
};
