#ifndef IFRAME_H_
# define IFRAME_H_

# include "../include/GameState.hpp"

class IFrame {
    public:
        virtual GameState Update(int dtms, void *sharedPtr = 0) = 0; // Return 0 if kept, else change frame
        virtual void Draw(void *dataPtr) = 0;
};

#endif