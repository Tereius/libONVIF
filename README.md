[![Build status](https://ci.appveyor.com/api/projects/status/craw12co0chie6hn?svg=true)](https://ci.appveyor.com/project/Tereius/libonvif)
[![Build Status](https://travis-ci.org/Tereius/libONVIF.svg?branch=master)](https://travis-ci.org/Tereius/libONVIF)

# libONVIF

### Yet another ONVIF library

__This projects status is "work in progress". Don't expect binary compatibility. Actually don't expect anything other than major changes in the source code :-).__

What does ONVIF stand for:
> ONVIF (Open Network Video Interface Forum) is a global and open industry forum with the goal of facilitating the development and use of a global open standard for the interface of physical IP-based security products – or, in other words, to create a standard for how IP products within video surveillance and other physical security areas can communicate with each other. [Wikipedia](https://en.wikipedia.org/wiki/ONVIF)

The idea behind this library is to hide some complexity of gsoap and to provide 'high level' classes including QT5 goodness. Currently there are ten client side service methods implemented:

- ONVIF analytics http://www.onvif.org/ver20/analytics/wsdl
- ONVIF device http://www.onvif.org/ver10/device/wsdl
- ONVIF display http://www.onvif.org/ver10/display/wsdl
- ONVIF event http://www.onvif.org/ver10/events/wsdl
- ONVIF imaging http://www.onvif.org/ver20/imaging/wsdl
- ONVIF media http://www.onvif.org/ver10/media/wsdl
- ONVIF ptz http://www.onvif.org/ver20/ptz/wsdl
- ONVIF receiver http://www.onvif.org/ver10/receiver/wsdl
- ONVIF recording http://www.onvif.org/ver10/recording/wsdl
- ONVIF replay http://www.onvif.org/ver10/replay/wsdl

For every service exists a class following the naming scheme `Onvif*Client` (\* matches service name). These classes handle the RPCs. For the convenience of WS discovery and ONVIF (pull point) event handling there are two more classes: `OnvifDiscovery` and `OnvifPullPoint`.

Design thoughts:

- The most of this library is thread safe and should work in a multithreaded environment
- gsoap is 'hidden' from the user as much as possible
- RAII classes `Request<>`, `Response<>` wrapping the RPC parameters are responsible for the memory management
