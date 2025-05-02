#pragma once
#include <string>
#include <vector>
#include <thread>
#include <variant>

#include "cl_listener.h"

namespace http_server
{
    template <typename LampdaHandler>
    void ServeHttp(net::io_context &ioc, const tcp::endpoint &endpoint, LampdaHandler &&handler)
    {
       /*
       http_server::ServeHttp(ioc, endpoint, [handler](auto &&req, auto &&send)
                                   { 
                                         //Handler из main  
                                         На вход принимает запрос req и функцию которая отправит ответ.
                                         
                                         handler->operator()(std::forward<decltype(req)>(req), std::forward<decltype(send)>(send)); 
                                   });
       */
       
        using MyListener = Listener<std::decay_t<LampdaHandler>>;
        std::make_shared<MyListener>(ioc, endpoint, std::forward<LampdaHandler>(handler))->Run();
    }
}


