#pragma once

#include <functional>

namespace tmools
{
    struct Finally
    {
        Finally(std::function<void()> functionToExecuteAtTheEnd) 
            : functionToExecuteAtTheEnd(functionToExecuteAtTheEnd)
        {}

        ~Finally()
        {
            functionToExecuteAtTheEnd();
        }
private:
        std::function<void()> functionToExecuteAtTheEnd;
        Finally(const Finally&) = default;
        Finally& operator=(const Finally&) = default;
    };
}
