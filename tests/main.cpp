#include <iostream>
#include "../time_related.h"
#include "../logging.h"
#include "../optional/optional.hpp"
#include "../finally.h"

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

    int b = 0;
    tmools::Finally log_b([&b]{ LOG(DESC(b)); });
    b = 2;

    LOG(DESC(a.value()));


    {
        tmools::Finally f([]{ LOG("Exiting."); });
    }

    {
        LOG_SCOPE_ENDPOINTS("random brace");
    }

    return 0;
}
