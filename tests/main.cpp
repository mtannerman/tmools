#include <iostream>
#include "../time.h"
#include "../logging.h"
#include "../optional/optional.hpp"

int main()
{
    LOG(tmools::GetDateTimeStr());
    tmools::StopWatch sw;

    for (int i = 0; i < 1000; ++i) {
        std::cout << "";
    }

    std::cout << sw.ElapsedTime(tmools::StopWatch::Unit::NANOSEC) << std::endl;

    std::experimental::optional<int> a;
    a=2;

    LOG(DESC(a.value()));

    return 0;
}
